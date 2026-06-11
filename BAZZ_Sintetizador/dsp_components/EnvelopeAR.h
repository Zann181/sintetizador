#pragma once
// ============================================================================
// EnvelopeAR.h — Envolvente Attack-Release para BAZZ Sintetizador
// ============================================================================
//
// Generador de envolvente de ataque-release (AR) que soporta los dos
// patrones principales usados en las voces del sintetizador Faust:
//
// PATRÓN 1: Envolvente por contador de muestras (KickVoice, SnareVoice, Siringe)
//   iRec76[0] = (iRec76[1] + (iRec76[1] > 0)) * (trigger <= prevTrigger)
//             + (trigger > prevTrigger);
//   float env = max(0, min(attackSlope * counter, releaseSlope * (max - counter) + 1));
//
//   Esto genera una rampa lineal de ataque seguida de una rampa lineal de
//   release, controladas por un contador de muestras que se reinicia al
//   detectar un flanco ascendente en el trigger.
//
// PATRÓN 2: Envolvente exponencial con tiempo (BassVoice)
//   fRec33[0] = (1/sr + fRec33[1]) * (1 - trigger);  // acumulador de tiempo
//   fRec32[0] = smooth * exp(-rate * fRec33[0]) + coeff * fRec32[1];
//
//   Esto genera una caída exponencial suavizada, donde el tiempo se
//   acumula desde el último trigger.
//
// Uso típico:
//   bazz_dsp::EnvelopeAR env;
//   env.setSampleRate(44100.0);
//   env.setAttack(0.005f);    // 5ms de ataque
//   env.setRelease(0.2f);     // 200ms de release
//   env.trigger(0.8f);        // disparar con velocidad 0.8
//   float level = env.process(); // llamar cada muestra
//
// Dependencias: <cmath>, <algorithm>
// Sin asignación dinámica de memoria. Seguro para tiempo real.
// ============================================================================

#include <cmath>
#include <algorithm>

namespace bazz_dsp {

// ──────────────────────────────────────────────────────────────────────────────
// Modo de envolvente
// ──────────────────────────────────────────────────────────────────────────────
enum class EnvelopeMode {
    // Ataque lineal + release lineal (patrón de contador Faust)
    // Usado en: KickVoice, SnareVoice, SiringeVoice
    LinearAR,

    // Ataque lineal + release exponencial
    // Usado en: BassVoice (con suavizado exponencial)
    LinearAttackExpRelease
};

// ──────────────────────────────────────────────────────────────────────────────
// EnvelopeAR — Envolvente Attack-Release
// ──────────────────────────────────────────────────────────────────────────────
//
// La envolvente tiene 3 fases:
//   1. Idle    — sin actividad, salida = 0
//   2. Attack  — rampa ascendente (lineal)
//   3. Release — caída descendente (lineal o exponencial según el modo)
//
// La velocidad del trigger escala la amplitud máxima de la envolvente.
//
// El patrón Faust de contador funciona así:
//   - Al detectar flanco ascendente (trigger > prevTrigger), el contador
//     se reinicia a 1.
//   - Cada muestra, el contador incrementa: counter = counter + 1
//   - Si no hay re-trigger: counter sigue incrementando
//   - Si hay re-trigger: counter vuelve a 1
//   - La envolvente se calcula como:
//     env = clamp(attackSlope * counter, releaseSlope * (maxSamples - counter) + 1)
//     donde min() selecciona la fase (ataque si counter es bajo, release si alto)
// ──────────────────────────────────────────────────────────────────────────────
class EnvelopeAR {
public:
    EnvelopeAR() = default;

    // ────────────────────────────────────────────────────────────────────────
    // setSampleRate() — Configura la frecuencia de muestreo
    // ────────────────────────────────────────────────────────────────────────
    // Debe llamarse antes de usar la envolvente y cada vez que cambie el sr.
    // Recalcula las constantes internas de tiempo.
    void setSampleRate(double sampleRate) {
        m_sampleRate = static_cast<float>(
            std::min(192000.0, std::max(1.0, sampleRate))
        );
        m_invSampleRate = 1.0f / m_sampleRate;
        recalculate();
    }

    // ────────────────────────────────────────────────────────────────────────
    // setMode() — Establece el modo de envolvente
    // ────────────────────────────────────────────────────────────────────────
    void setMode(EnvelopeMode mode) {
        m_mode = mode;
        recalculate();
    }

    // ────────────────────────────────────────────────────────────────────────
    // setAttack() — Configura el tiempo de ataque
    // ────────────────────────────────────────────────────────────────────────
    // Parámetros:
    //   seconds — Tiempo de ataque en segundos (ej: 0.005 = 5ms)
    //
    // Equivalente Faust (patrón contador):
    //   fConst15 = std::max(1.0f, 0.05f * fConst0);  // attackSamples
    //   fConst16 = 1.0f / fConst15;                    // attackSlope
    //
    // Un tiempo de 0 produce un ataque instantáneo (1 muestra).
    void setAttack(float seconds) {
        m_attackSeconds = std::max(0.0f, seconds);
        recalculate();
    }

    // ────────────────────────────────────────────────────────────────────────
    // setRelease() — Configura el tiempo de release
    // ────────────────────────────────────────────────────────────────────────
    // Parámetros:
    //   seconds — Tiempo de release en segundos (ej: 0.2 = 200ms)
    //
    // Equivalente Faust (patrón contador):
    //   fSlow305 = 1.0f / std::max(1.0f, fConst0 * decay);  // releaseSlope
    //
    // En modo exponencial (BassVoice):
    //   fConst50 = std::exp(-(200.0f / fConst0));  // coeficiente de suavizado
    //   rate = bpm / decay * constante;              // tasa de caída
    void setRelease(float seconds) {
        m_releaseSeconds = std::max(0.001f, seconds);
        recalculate();
    }

    // ────────────────────────────────────────────────────────────────────────
    // setExpSmoothFreq() — Frecuencia del filtro de suavizado exponencial
    // ────────────────────────────────────────────────────────────────────────
    // Solo aplica en modo LinearAttackExpRelease.
    // Equivalente Faust: fConst50 = std::exp(-(freq / fConst0));
    // Parámetros:
    //   freqHz — Frecuencia de corte del suavizado (ej: 200.0f para BassVoice)
    void setExpSmoothFreq(float freqHz) {
        m_expSmoothFreq = std::max(1.0f, freqHz);
        recalculate();
    }

    // ────────────────────────────────────────────────────────────────────────
    // trigger() — Dispara la envolvente con una velocidad dada
    // ────────────────────────────────────────────────────────────────────────
    // Parámetros:
    //   velocity — Amplitud del disparo [0.0 - 1.0]
    //              0.0 no dispara, > 0.0 inicia la envolvente
    //
    // Equivalente Faust:
    //   Al detectar flanco ascendente, el contador se reinicia a 1.
    //   iRec76[0] = 1 cuando trigger > prevTrigger
    void trigger(float velocity) {
        m_velocity = std::max(0.0f, std::min(1.0f, velocity));

        if (m_velocity > 0.0f) {
            // Reiniciar contador (patrón Faust: counter = 1 al re-trigger)
            m_counter = 1;
            m_phase = Phase::Attack;

            // Para modo exponencial
            m_timeAccum = 0.0f;
            m_expValue = 0.0f;
        }
    }

    // ────────────────────────────────────────────────────────────────────────
    // process() — Genera la siguiente muestra de la envolvente
    // ────────────────────────────────────────────────────────────────────────
    // Retorna: valor de la envolvente [0.0 - 1.0] × velocity
    //
    // Debe llamarse exactamente una vez por muestra.
    //
    // Equivalente Faust (patrón completo):
    //   float fTemp74 = static_cast<float>(iRec76[0]);
    //   float fTemp75 = fConst16 * fTemp74;  // attackSlope * counter
    //   float fTemp76 = fConst15 - fTemp74;  // attackSamples - counter
    //   float env = max(0, min(fTemp75, releaseSlope * fTemp76 + 1.0f));
    inline float process() {
        if (m_phase == Phase::Idle) {
            return 0.0f;
        }

        float output = 0.0f;

        switch (m_mode) {
            case EnvelopeMode::LinearAR:
                output = processLinearAR();
                break;
            case EnvelopeMode::LinearAttackExpRelease:
                output = processLinearAttackExpRelease();
                break;
        }

        return output * m_velocity;
    }

    // ────────────────────────────────────────────────────────────────────────
    // processWithCounter() — Versión que acepta trigger externo por muestra
    // ────────────────────────────────────────────────────────────────────────
    // Replica exactamente el patrón Faust de detección de flanco:
    //   iRec76[0] = (iRec76[1] + (iRec76[1] > 0)) * (trigger <= prevTrigger)
    //             + (trigger > prevTrigger);
    //
    // Parámetros:
    //   triggerSignal — Señal de trigger (> 0 = activo)
    //
    // Retorna: valor de la envolvente escalado por velocity
    //
    // Nota: esta versión NO usa trigger() — maneja el trigger internamente
    // muestra a muestra, exactamente como el código Faust original.
    inline float processWithCounter(int triggerSignal) {
        // Detección de flanco ascendente (patrón Faust exacto)
        // iRec76[0] = (iRec76[1] + (iRec76[1] > 0)) * (trig <= prevTrig)
        //           + (trig > prevTrig);
        m_counter = (m_counter + (m_counter > 0))
                  * (triggerSignal <= m_prevTrigger)
                  + (triggerSignal > m_prevTrigger);
        m_prevTrigger = triggerSignal;

        if (m_counter <= 0) {
            return 0.0f;
        }

        const float fCounter = static_cast<float>(m_counter);

        // Envolvente: max(0, min(attackSlope * counter, releaseSlope * (attackMax - counter) + 1))
        const float attackPhase = m_attackSlope * fCounter;
        const float releasePhase = m_releaseSlope * (m_attackSamples - fCounter) + 1.0f;

        return std::max(0.0f, std::min(attackPhase, releasePhase));
    }

    // ────────────────────────────────────────────────────────────────────────
    // isActive() — ¿Está la envolvente activa (no en idle)?
    // ────────────────────────────────────────────────────────────────────────
    bool isActive() const {
        return m_phase != Phase::Idle;
    }

    // ────────────────────────────────────────────────────────────────────────
    // reset() — Reinicia la envolvente a estado idle
    // ────────────────────────────────────────────────────────────────────────
    void reset() {
        m_phase = Phase::Idle;
        m_counter = 0;
        m_prevTrigger = 0;
        m_velocity = 0.0f;
        m_timeAccum = 0.0f;
        m_expValue = 0.0f;
        m_smoothedValue = 0.0f;
    }

    // ────────────────────────────────────────────────────────────────────────
    // Acceso al contador interno (para depuración o uso externo)
    // ────────────────────────────────────────────────────────────────────────
    int getCounter() const { return m_counter; }

private:
    // Fases de la envolvente
    enum class Phase { Idle, Attack, Release };

    // Configuración
    float m_sampleRate = 44100.0f;
    float m_invSampleRate = 1.0f / 44100.0f;
    float m_attackSeconds = 0.005f;   // 5ms por defecto (como fConst15 = 0.05 * sr)
    float m_releaseSeconds = 0.2f;    // 200ms por defecto
    float m_expSmoothFreq = 200.0f;   // Frecuencia de suavizado exponencial
    EnvelopeMode m_mode = EnvelopeMode::LinearAR;

    // Estado
    Phase m_phase = Phase::Idle;
    int m_counter = 0;        // Contador de muestras (patrón iRec76)
    int m_prevTrigger = 0;    // Trigger de la muestra anterior (iVec29[1])
    float m_velocity = 0.0f;  // Velocidad del último disparo

    // Pre-computados (recalculados al cambiar parámetros)
    float m_attackSamples = 220.5f;  // = max(1, attackSeconds * sampleRate)
    float m_attackSlope = 0.0045f;   // = 1.0f / attackSamples
    float m_releaseSlope = 0.0001f;  // = 1.0f / max(1, releaseSeconds * sampleRate)

    // Estado para modo exponencial
    float m_timeAccum = 0.0f;      // Acumulador de tiempo (fRec33)
    float m_expValue = 0.0f;       // Valor exponencial bruto
    float m_smoothedValue = 0.0f;  // Valor suavizado (fRec32)
    float m_expSmooth = 0.0f;      // Coeficiente de suavizado
    float m_expSmoothInv = 1.0f;   // 1 - coeficiente de suavizado

    // ────────────────────────────────────────────────────────────────────────
    // recalculate() — Recalcula constantes internas
    // ────────────────────────────────────────────────────────────────────────
    void recalculate() {
        // Patrón Faust: fConst15 = max(1.0f, attackTime * fConst0)
        m_attackSamples = std::max(1.0f, m_attackSeconds * m_sampleRate);
        m_attackSlope = 1.0f / m_attackSamples;

        // Patrón Faust: fSlow305 = 1.0f / max(1.0f, fConst0 * decay)
        const float releaseSamples = std::max(1.0f, m_releaseSeconds * m_sampleRate);
        m_releaseSlope = 1.0f / releaseSamples;

        // Coeficiente de suavizado exponencial (solo para modo exp)
        // Patrón Faust: fConst50 = exp(-(freq / sampleRate))
        m_expSmooth = std::exp(-(m_expSmoothFreq / m_sampleRate));
        m_expSmoothInv = 1.0f - m_expSmooth;
    }

    // ────────────────────────────────────────────────────────────────────────
    // processLinearAR() — Procesamiento en modo lineal AR
    // ────────────────────────────────────────────────────────────────────────
    // Replica exactamente:
    //   float env = max(0, min(attackSlope * counter,
    //                          releaseSlope * (attackMax - counter) + 1));
    inline float processLinearAR() {
        const float fCounter = static_cast<float>(m_counter);

        // Fase de ataque: rampa ascendente
        const float attackValue = m_attackSlope * fCounter;

        // Fase de release: rampa descendente desde 1.0
        const float totalSamples = m_attackSamples + (1.0f / m_releaseSlope);
        const float releaseValue = m_releaseSlope * (totalSamples - fCounter) + 1.0f;

        // min() selecciona automáticamente la fase correcta
        const float env = std::max(0.0f, std::min(attackValue, releaseValue));

        ++m_counter;

        // Verificar si la envolvente ha terminado
        if (env <= 0.0f && m_counter > 1) {
            m_phase = Phase::Idle;
            m_counter = 0;
            return 0.0f;
        }

        return env;
    }

    // ────────────────────────────────────────────────────────────────────────
    // processLinearAttackExpRelease() — Modo ataque lineal + release exp
    // ────────────────────────────────────────────────────────────────────────
    // Replica el patrón del BassVoice:
    //   fRec33[0] = (1/sr + fRec33[1]) * (1 - trigger);  // acumula tiempo
    //   fRec32[0] = smoothInv * exp(-rate * fRec33[0]) + smooth * fRec32[1];
    //
    // Fase de ataque: rampa lineal rápida
    // Fase de release: decaimiento exponencial suavizado
    inline float processLinearAttackExpRelease() {
        const float fCounter = static_cast<float>(m_counter);

        float env;

        if (m_phase == Phase::Attack) {
            // Rampa lineal de ataque
            env = m_attackSlope * fCounter;
            if (env >= 1.0f) {
                env = 1.0f;
                m_phase = Phase::Release;
                m_timeAccum = 0.0f;
            }
        } else {
            // Release exponencial suavizado
            // Acumular tiempo desde fin del ataque
            m_timeAccum += m_invSampleRate;

            // Exponencial: exp(-rate * time)
            // rate = 1/releaseSeconds (escalado para que a t=releaseSeconds, env ≈ 0.001)
            const float rate = 6.9078f / m_releaseSeconds; // ln(1000) ≈ 6.9078 → -60dB
            m_expValue = std::exp(-rate * m_timeAccum);

            // Suavizado del valor exponencial (patrón fRec32)
            m_smoothedValue = m_expSmoothInv * m_expValue + m_expSmooth * m_smoothedValue;
            env = m_smoothedValue;

            // Threshold de corte para pasar a idle
            if (env < 1.0e-6f) {
                m_phase = Phase::Idle;
                m_counter = 0;
                return 0.0f;
            }
        }

        ++m_counter;
        return env;
    }
};

} // namespace bazz_dsp
