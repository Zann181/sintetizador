#pragma once
#include <atomic>
#include <array>

class Clock {
private:
    double m_sampleRate = 44100.0;
    std::atomic<float> m_bpm{140.0f};
    std::atomic<float> m_swing{0.0f}; // 0.0f a 75.0f

    // Estado del phasor
    double m_phase = 0.0;
    double m_prevPhase = 0.0;
    int m_step = 0;
    float m_prevNote = 36.0f;

    // Buffer circular para el retardo de swing de offbeats (steps 1, 3, 5, etc.)
    static constexpr int SWING_BUFFER_SIZE = 16384;
    std::array<float, SWING_BUFFER_SIZE> m_delayBuffer;
    int m_delayWriteIndex = 0;

public:
    void initialize(double sampleRate);
    void setBpm(float bpm);
    float getBpm() const;
    void setSwing(float swing);
    float getSwing() const;
    void reset();

    // Procesa una muestra.
    // Retorna > 0.0f (la velocidad del trigger) si hay disparo en esta muestra, y 0.0f en caso contrario.
    // outStep se actualiza con el número de paso actual (0-15).
    float processSample(float multiplier, float accentGroove, float accentMicro, float activeNote, int& outStep);
};
