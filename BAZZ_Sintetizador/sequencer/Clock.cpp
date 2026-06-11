#include "Clock.h"
#include <cmath>
#include <algorithm>

void Clock::initialize(double sampleRate) {
    m_sampleRate = sampleRate;
    reset();
}

void Clock::setBpm(float bpm) {
    m_bpm.store(bpm);
}

float Clock::getBpm() const {
    return m_bpm.load();
}

void Clock::setSwing(float swing) {
    m_swing.store(swing);
}

float Clock::getSwing() const {
    return m_swing.load();
}

void Clock::reset() {
    m_phase = 0.0;
    m_prevPhase = 999.0;
    m_step = 15;
    m_delayBuffer.fill(0.0f);
    m_delayWriteIndex = 0;
}

float Clock::processSample(float multiplier, float accentGroove, float accentMicro, float activeNote, int& outStep) {
    float bpm = m_bpm.load();
    float swing = m_swing.load();

    // Frecuencia de pasos: (BPM / 15.0) * multiplier
    double stepFreq = (bpm / 15.0) * multiplier;
    
    // Incrementar phasor de fase
    m_phase += stepFreq / m_sampleRate;
    if (m_phase >= 1.0) {
        m_phase -= std::floor(m_phase);
    }

    // Trigger crudo ocurre en el flanco de reset del phasor (phase < prevPhase)
    bool rawTrigger = (m_phase < m_prevPhase);
    m_prevPhase = m_phase;

    // Si hay trigger crudo, incrementamos el paso
    if (rawTrigger) {
        m_step = (m_step + 1) % 16;
    }

    outStep = m_step;

    // Phrasing Melódico y Tonalidad del "Piano Player"
    int interval = (static_cast<int>(std::round(activeNote)) - 36) % 12;
    if (interval < 0) interval += 12;
    
    // Tabla de tensión armónica (0.0 = consonante, 1.0 = disonancia/tensión)
    static constexpr float kTension[12] = { 0.0f, 0.9f, 0.6f, 0.3f, 0.2f, 0.4f, 1.0f, 0.1f, 0.5f, 0.3f, 0.7f, 0.9f };
    float tension = kTension[interval];
    
    float phrasingShift = 0.0f;
    if (rawTrigger) {
        float noteDiff = activeNote - m_prevNote;
        m_prevNote = activeNote;
        if (noteDiff > 0.1f) phrasingShift = -0.015f;      // Ascenso melódico: adelantar (rush)
        else if (noteDiff < -0.1f) phrasingShift = 0.015f;  // Descenso melódico: retrasar (drag)
    }

    // El factor tonal de groove influye en el swing. La tensión armónica "arrastra" y la consonancia "acelera".
    float tonalGroove = (tension * 0.12f) + phrasingShift;

    // Techno Groove Accent Profile (usando accentGroove para dinámica de volumen estructural):
    float baseAccent = 1.0f;
    if (m_step == 0 || m_step == 4 || m_step == 8 || m_step == 12) {
        baseAccent = 1.0f + accentGroove * 0.6f;  // Hasta +60% en downbeats
    } else if (m_step == 2 || m_step == 6 || m_step == 10 || m_step == 14) {
        baseAccent = 1.0f + accentGroove * 0.3f;  // Hasta +30% en upbeats
    } else if (m_step == 3 || m_step == 7 || m_step == 11 || m_step == 15) {
        baseAccent = 1.0f + accentGroove * 0.15f; // Hasta +15% en síncopas previas al golpe fuerte
    } else {
        baseAccent = 1.0f - accentGroove * 0.1f;  // Hasta -10% de atenuación en los pockets
    }

    // Micro-variaciones en el volumen del golpe (touch velocity de piano) dependiente de accentMicro:
    float randVelShift = 0.0f;
    if (rawTrigger) {
        // Generador pseudo-aleatorio rápido LCG
        uint32_t seed = static_cast<uint32_t>(m_step) * 2166136261u + 16777619 + m_delayWriteIndex;
        float randVal = static_cast<float>(seed % 100) / 100.0f - 0.5f;
        randVelShift = randVal * 0.15f * accentMicro; // Desvío aleatorio de hasta +/- 7.5% de velocidad
    }
    float triggerAmp = std::max(0.0f, baseAccent + randVelShift);

    // Escribir el trigger en el buffer de retardo
    float triggerVal = rawTrigger ? triggerAmp : 0.0f;
    m_delayBuffer[m_delayWriteIndex] = triggerVal;

    // Determinar si es paso par (offbeat) para aplicar swing delay
    bool isOffbeat = (m_step % 2 == 1);

    // Humanización del Swing con Micro-Timing Jitter:
    // El desvío de tiempo analógico (jitter) aumenta con accentMicro
    double jitterMs = 0.0;
    if (rawTrigger) {
        uint32_t seed = static_cast<uint32_t>(m_step) * 1103515245 + 12345 + m_delayWriteIndex;
        double randVal = static_cast<double>(seed % 1000) / 1000.0 - 0.5;
        jitterMs = randVal * 3.0 * accentMicro; // Desvío de tiempo aleatorio de hasta +/- 1.5ms
    }
    double jitterSamples = (jitterMs / 1000.0) * m_sampleRate;

    // Calcular retraso en muestras
    double samplesPerStep = m_sampleRate / stepFreq;
    
    // Dynamic swing modulation: swing base + groove accent (retraso sutil) + swing tonal armónico
    double swingFactor = swing / 100.0;
    double dynamicSwing = swingFactor + (accentGroove * 0.04f) + (tonalGroove * 0.1f);
    double delaySamples = 0.5 * std::max(0.0, std::min(0.9, dynamicSwing)) * samplesPerStep + jitterSamples;

    // Asegurar que el delay esté en un rango válido (0 a SWING_BUFFER_SIZE - 2)
    delaySamples = std::max(0.0, std::min(static_cast<double>(SWING_BUFFER_SIZE - 2), delaySamples));

    // Leer el valor retardado del buffer circular usando el índice redondeado más cercano
    double readPtr = static_cast<double>(m_delayWriteIndex) - delaySamples;
    if (readPtr < 0.0) {
        readPtr += SWING_BUFFER_SIZE;
    }

    int idx = static_cast<int>(std::round(readPtr)) % SWING_BUFFER_SIZE;
    float delayedTriggerVal = m_delayBuffer[idx];

    // Incrementar índice de escritura
    m_delayWriteIndex = (m_delayWriteIndex + 1) % SWING_BUFFER_SIZE;

    // Si es un offbeat, retornamos el trigger retardado.
    // Si es un downbeat/onbeat, retornamos el trigger crudo.
    if (isOffbeat) {
        return delayedTriggerVal;
    } else {
        return triggerVal;
    }
}
