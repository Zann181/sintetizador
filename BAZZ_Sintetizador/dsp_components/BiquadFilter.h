#pragma once
// ============================================================================
// BiquadFilter.h — Filtro biquad reutilizable para BAZZ Sintetizador
// ============================================================================
//
// Filtro IIR de segundo orden (biquad) usando forma directa II transpuesta.
// Reemplaza los patrones repetitivos de filtros Faust como:
//
//   float fConst1 = std::tan(omega / fConst0);
//   float fConst3 = 1.0f / fConst1;
//   fRec[0] = input - coeff * (a2 * fRec[2] + a1 * fRec[1]);
//   output  = gain * (fRec[2] + fRec[0] + 2.0f * fRec[1]);  // LPF
//   output  = gain * (fRec[2] + fRec[0] - 2.0f * fRec[1]);  // HPF
//
// Uso típico:
//   bazz_dsp::BiquadFilter filtro;
//   filtro.setCoefficients(bazz_dsp::FilterType::LowPass, 1000.0f, 0.707f, 44100.0);
//   float y = filtro.process(x);
//
// También soporta el patrón Faust de pre-computar tan(pi*f/sr):
//   filtro.setFromFaust(fConst_tan, Q);
//
// Dependencias: <cmath>, <algorithm>
// Sin asignación dinámica de memoria. Seguro para tiempo real.
// ============================================================================

#include <cmath>
#include <algorithm>

namespace bazz_dsp {

// ──────────────────────────────────────────────────────────────────────────────
// Tipos de filtro soportados
// ──────────────────────────────────────────────────────────────────────────────
enum class FilterType {
    LowPass,   // Paso bajo  — deja pasar frecuencias bajas
    HighPass,  // Paso alto  — deja pasar frecuencias altas
    BandPass,  // Paso banda — deja pasar una banda central
    Notch      // Rechaza banda — elimina una banda central
};

// ──────────────────────────────────────────────────────────────────────────────
// BiquadFilter — Filtro biquad de forma directa II transpuesta
// ──────────────────────────────────────────────────────────────────────────────
//
// Ecuación de diferencia (forma directa II transpuesta):
//   w[n] = x[n] - a1*s1 - a2*s2
//   y[n] = b0*w[n] + b1*s1 + b2*s2
//   s2 = s1;  s1 = w[n]
//
// Donde s1, s2 son las dos variables de estado internas.
// Esta forma minimiza el error numérico para coeficientes cercanos a 1.
//
// Nota: internamente almacenamos los coeficientes normalizados por a0.
// ──────────────────────────────────────────────────────────────────────────────
class BiquadFilter {
public:
    BiquadFilter() { reset(); }

    // ────────────────────────────────────────────────────────────────────────
    // reset() — Limpia las variables de estado del filtro
    // ────────────────────────────────────────────────────────────────────────
    // Llamar después de cambiar el sample rate o cuando se necesite
    // eliminar artefactos de señal residual (ej: al re-disparar una voz).
    void reset() {
        m_s1 = 0.0f;
        m_s2 = 0.0f;
    }

    // ────────────────────────────────────────────────────────────────────────
    // setCoefficients() — Calcula coeficientes desde frecuencia y Q
    // ────────────────────────────────────────────────────────────────────────
    // Parámetros:
    //   type       — Tipo de filtro (LowPass, HighPass, BandPass, Notch)
    //   freqHz     — Frecuencia de corte o central en Hz
    //   Q          — Factor de calidad (resonancia). 0.707 = Butterworth
    //   sampleRate — Frecuencia de muestreo en Hz
    //
    // Internamente usa la transformada bilineal (BLT), igual que Faust tf2s.
    // El cálculo es: tan(pi * freq / sampleRate), que es exactamente el
    // patrón fConst = std::tan(omega / fConst0) del código generado.
    void setCoefficients(FilterType type, float freqHz, float Q, double sampleRate) {
        // Limitar frecuencia al rango válido (Nyquist - margen de seguridad)
        const float sr = static_cast<float>(
            std::min(192000.0, std::max(1.0, sampleRate))
        );
        const float nyquist = sr * 0.499f;
        const float f = std::max(1.0f, std::min(freqHz, nyquist));
        const float q = std::max(0.001f, Q);

        // Pre-warp: tan(pi * f / sr) — el corazón de la transformada bilineal
        // Este es exactamente el patrón de Faust: std::tan(omega / fConst0)
        const float w = std::tan(3.1415927f * f / sr);

        setFromTan(type, w, q);
    }

    // ────────────────────────────────────────────────────────────────────────
    // setFromFaust() — Configura desde valores pre-computados al estilo Faust
    // ────────────────────────────────────────────────────────────────────────
    // Parámetros:
    //   fConst_tan — Valor de tan(pi * freq / sampleRate) ya computado
    //               (ej: fConst1 = std::tan(6283.1855f / fConst0))
    //   Q          — Factor de calidad. Usar 0.7071068f (1/sqrt(2)) para
    //               filtros Butterworth como los usados en el Kick y Siringe.
    //
    // Nota: el tipo por defecto es LowPass. Usa setFromFaustTyped() si
    // necesitas otro tipo.
    void setFromFaust(float fConst_tan, float Q) {
        setFromTan(FilterType::LowPass, fConst_tan, Q);
    }

    // ────────────────────────────────────────────────────────────────────────
    // setFromFaustTyped() — Como setFromFaust() pero con tipo explícito
    // ────────────────────────────────────────────────────────────────────────
    void setFromFaustTyped(FilterType type, float fConst_tan, float Q) {
        setFromTan(type, fConst_tan, Q);
    }

    // ────────────────────────────────────────────────────────────────────────
    // setRawCoefficients() — Configura coeficientes directamente
    // ────────────────────────────────────────────────────────────────────────
    // Para casos donde ya se tienen los coeficientes normalizados.
    // Todos los coeficientes deben estar normalizados por a0.
    //   b0, b1, b2 — coeficientes del numerador (feedforward)
    //   a1, a2     — coeficientes del denominador (feedback), ya negados
    void setRawCoefficients(float b0, float b1, float b2, float a1, float a2) {
        m_b0 = b0;
        m_b1 = b1;
        m_b2 = b2;
        m_a1 = a1;
        m_a2 = a2;
    }

    // ────────────────────────────────────────────────────────────────────────
    // process() — Procesa una muestra de entrada
    // ────────────────────────────────────────────────────────────────────────
    // Forma directa II transpuesta con 2 variables de estado.
    // Exactamente equivalente al patrón Faust de fRec[3]:
    //   fRec[0] = input - norm * (a2_n * fRec[2] + a1_n * fRec[1]);
    //   output  = gain * combinación_de(fRec[0], fRec[1], fRec[2]);
    //   fRec[2] = fRec[1]; fRec[1] = fRec[0];
    //
    // Retorna: la muestra filtrada
    inline float process(float input) {
        // Forma directa II transpuesta:
        //   y[n] = b0*x[n] + s1
        //   s1   = b1*x[n] - a1*y[n] + s2
        //   s2   = b2*x[n] - a2*y[n]
        const float y = m_b0 * input + m_s1;
        m_s1 = m_b1 * input - m_a1 * y + m_s2;
        m_s2 = m_b2 * input - m_a2 * y;
        return y;
    }

    // ────────────────────────────────────────────────────────────────────────
    // Accesores — para depuración o encadenamiento manual de filtros
    // ────────────────────────────────────────────────────────────────────────
    float getB0() const { return m_b0; }
    float getB1() const { return m_b1; }
    float getB2() const { return m_b2; }
    float getA1() const { return m_a1; }
    float getA2() const { return m_a2; }

    // ────────────────────────────────────────────────────────────────────────
    // getNormFactor() — Retorna 1/a0, el factor de normalización
    // ────────────────────────────────────────────────────────────────────────
    // Útil para el patrón Faust donde la ganancia se aplica externamente:
    //   output = fConst_norm * (fRec[2] + fRec[0] + 2.0f * fRec[1]);
    float getNormFactor() const { return m_norm; }

private:
    // Variables de estado (forma directa II transpuesta)
    float m_s1 = 0.0f;
    float m_s2 = 0.0f;

    // Coeficientes normalizados
    float m_b0 = 1.0f;
    float m_b1 = 0.0f;
    float m_b2 = 0.0f;
    float m_a1 = 0.0f;
    float m_a2 = 0.0f;

    // Factor de normalización (1/a0) — almacenado para consulta externa
    float m_norm = 1.0f;

    // ────────────────────────────────────────────────────────────────────────
    // setFromTan() — Implementación interna de cálculo de coeficientes
    // ────────────────────────────────────────────────────────────────────────
    // Recibe w = tan(pi * f / sr) y Q, que es exactamente la transformada
    // bilineal del dominio-s al dominio-z usada por Faust (tf2s).
    //
    // Prototipo analógico LPF:  H(s) = 1 / (s² + s/Q + 1)
    // Tras BLT con pre-warp w:
    //   a0 = 1 + (1/Q)/w + 1/w²
    //   a1 = 2*(1 - 1/w²)
    //   a2 = 1 - (1/Q)/w + 1/w²
    //
    // Esto produce exactamente los mismos coeficientes que el código Faust:
    //   fConst3 = 1.0f / fConst1;  // 1/w
    //   fConst4 = (fConst3 + -1.4142135f) / fConst1 + 1.0f;  // a2
    //   fConst5 = 1.0f / ((fConst3 + 1.4142135f) / fConst1 + 1.0f); // 1/a0
    //   fConst2 = 2.0f * (1.0f - 1.0f / power2(fConst1));  // a1/a0
    void setFromTan(FilterType type, float w, float Q) {
        const float w2 = w * w;
        const float invW = 1.0f / w;
        const float invQ = 1.0f / Q;

        // Denominador común (a0) para todos los tipos
        const float a0 = (invW + invQ) / w + 1.0f;  // = 1/w² + (1/Q)/w + 1
        m_norm = 1.0f / a0;

        // a1, a2 son iguales para todos los tipos de filtro
        // a1 = 2*(1 - 1/w²) / a0
        // a2 = (1/w² - (1/Q)/w + 1) / a0  =  ((1/w - 1/Q)/w + 1) / a0
        m_a1 = 2.0f * (1.0f - 1.0f / w2) * m_norm;
        m_a2 = ((invW - invQ) / w + 1.0f) * m_norm;

        switch (type) {
            case FilterType::LowPass:
                // Numerador LPF: H(s) = 1/(s² + s/Q + 1)
                // Tras BLT: b0 = 1/a0,  b1 = 2/a0,  b2 = 1/a0
                // Patrón Faust: output = norm * (fRec[2] + fRec[0] + 2*fRec[1])
                m_b0 = m_norm;
                m_b1 = 2.0f * m_norm;
                m_b2 = m_norm;
                break;

            case FilterType::HighPass:
                // Numerador HPF: H(s) = s²/(s² + s/Q + 1)
                // Tras BLT: b0 = (1/w²)/a0,  b1 = -2*(1/w²)/a0,  b2 = (1/w²)/a0
                // Patrón Faust: output = norm2 * (fRec[2] + fRec[0] - 2*fRec[1])
                {
                    const float hpGain = (1.0f / w2) * m_norm;
                    m_b0 = hpGain;
                    m_b1 = -2.0f * hpGain;
                    m_b2 = hpGain;
                }
                break;

            case FilterType::BandPass:
                // Numerador BPF: H(s) = s/(s² + s/Q + 1)
                // Tras BLT: b0 = (1/w)/a0,  b1 = 0,  b2 = -(1/w)/a0
                // Patrón Faust: output = norm * (fRec[0] - fRec[2])
                {
                    const float bpGain = invW * m_norm;
                    m_b0 = bpGain;
                    m_b1 = 0.0f;
                    m_b2 = -bpGain;
                }
                break;

            case FilterType::Notch:
                // Numerador Notch: H(s) = (s² + 1)/(s² + s/Q + 1)
                // Tras BLT: b0 = (1 + 1/w²)/a0,  b1 = 2*(1 - 1/w²)/a0,  b2 = b0
                {
                    const float notchGain = (1.0f + 1.0f / w2) * m_norm;
                    m_b0 = notchGain;
                    m_b1 = 2.0f * (1.0f - 1.0f / w2) * m_norm;
                    m_b2 = notchGain;
                }
                break;
        }
    }
};

// ──────────────────────────────────────────────────────────────────────────────
// BiquadCascade<N> — Cadena de N filtros biquad en serie
// ──────────────────────────────────────────────────────────────────────────────
// Útil para replicar los filtros de 4to orden del proyecto (2 biquads en serie).
// Patrón Faust equivalente:
//   fRec31[0] = input - c1*(a2_1*fRec31[2] + a1_1*fRec31[1]);
//   fRec30[0] = g1*(...) - c2*(a2_2*fRec30[2] + a1_2*fRec30[1]);
//   output = g2 * (...);
//
// Uso:
//   bazz_dsp::BiquadCascade<2> filtro4to;
//   filtro4to.stage(0).setCoefficients(FilterType::HighPass, 10.0f, 0.707f, sr);
//   filtro4to.stage(1).setCoefficients(FilterType::LowPass, 800.0f, 0.707f, sr);
//   float y = filtro4to.process(x);
template<int N>
class BiquadCascade {
    static_assert(N >= 1, "La cascada necesita al menos 1 etapa");
public:
    BiquadCascade() = default;

    // Acceso a cada etapa individual para configuración
    BiquadFilter& stage(int index) { return m_stages[index]; }
    const BiquadFilter& stage(int index) const { return m_stages[index]; }

    // Procesa una muestra a través de toda la cadena
    inline float process(float input) {
        float x = input;
        for (int i = 0; i < N; ++i) {
            x = m_stages[i].process(x);
        }
        return x;
    }

    // Limpia el estado de todas las etapas
    void reset() {
        for (int i = 0; i < N; ++i) {
            m_stages[i].reset();
        }
    }

private:
    BiquadFilter m_stages[N];
};

} // namespace bazz_dsp
