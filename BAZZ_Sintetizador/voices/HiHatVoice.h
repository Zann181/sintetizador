#pragma once
#include "../core/IInstrumentVoice.h"
#include "../core/InstrumentDescriptor.h"
#include <atomic>
#include <cmath>
#include <algorithm>
#include <array>

// ============================================================================
// Descriptor estático de los Platillos TR-808
// ============================================================================
namespace hat_params {
    static constexpr bazz::ParamInfo params[] = {
        BAZZ_PARAM("/hat/vol",         "Volumen",         "Sintesis", 0.0f,    1.0f,    0.45f,  0.01f, Slider),
        BAZZ_PARAM("/hat/accent",      "Accent",          "Sintesis", 0.0f,    1.0f,    0.5f,   0.01f, Knob),
        BAZZ_PARAM("/hat/tune",        "Afinación",       "Sintesis", -12.0f,  12.0f,   0.0f,   0.1f,  Knob),
        BAZZ_PARAM("/hat/ataque",      "Ataque",          "Sintesis", 0.0001f, 0.1f,    0.001f, 0.0001f, Knob),
        BAZZ_PARAM("/hat/dec",         "Decaimiento",     "Sintesis", 0.005f,  1.0f,    0.04f,  0.005f, Knob),
        BAZZ_PARAM("/hat/cutoff",      "Filtro HP",       "Filtros",  1000.0f, 15000.0f,6500.0f,10.0f, Knob),
        BAZZ_PARAM("/hat/mix",         "Mix Ruido",       "Sintesis", 0.0f,    1.0f,    0.5f,   0.01f, Knob),
        BAZZ_PARAM("/hat/nota",        "Nota",            "Sintesis", 24.0f,   84.0f,   36.0f,  1.0f,  Menu),
        BAZZ_PARAM("/hat/reloj",       "Reloj",           "Sintesis", 0.25f,   4.0f,    1.0f,   0.25f, Menu),
        BAZZ_PARAM("/hat/drive",       "Saturación",      "Sintesis", 0.1f,    10.0f,   0.35f,  0.05f, Knob),
        BAZZ_PARAM("/hat/swing",       "Swing",           "Sintesis", 0.0f,    75.0f,   0.0f,   1.0f,  Knob),
    };

    static constexpr bazz::InstrumentDescriptor descriptor = {
        "hat_808",                              // typeName
        "Platillos TR-808",                     // displayName
        "Platillos analógicos con cluster de 6 osciladores metálicos y filtro paso alto resonante", // description
        bazz::OutputType::Mono,                 // outputType
        params,                                 // params
        sizeof(params) / sizeof(params[0]),     // numParams
        2                                       // defaultChannel
    };
}

class HiHatVoice : public IInstrumentVoice {
private:
    double m_sampleRate = 44100.0;

    // Constantes de calibración de audio
    float fConst0;
    float fConst18;
    float fConst61;
    float fConst62;
    float fConst19;

    // Parámetros de control
    std::atomic<float> m_volume{0.45f};
    std::atomic<float> m_accent{0.5f};
    std::atomic<float> m_tune{0.0f};
    std::atomic<float> m_attack{0.001f};
    std::atomic<float> m_decay{0.04f};
    std::atomic<float> m_cutoff{6500.0f};
    std::atomic<float> m_mix{0.5f};
    std::atomic<float> m_note{36.0f};
    std::atomic<float> m_clockMult{1.0f};
    std::atomic<float> m_drive{0.35f};
    std::atomic<float> m_swing{0.0f};

    // Estados del DSP
    int iVec0[2];
    int iVec25[2];
    int iRec51[2];
    float fRec42[3]; // Filtro IIR de salida

    // Fases y estados de diferenciadores para el cluster metálico (6 osciladores)
    float fRec43[2]; // Osc 0 phase
    float fVec12[2]; // Osc 0 diff state
    float fRec44[2]; // Osc 1 phase
    float fVec14[2]; // Osc 1 diff state
    float fRec45[2]; // Osc 2 phase
    float fVec16[2]; // Osc 2 diff state
    float fRec46[2]; // Osc 3 phase
    float fVec18[2]; // Osc 3 diff state
    float fRec47[2]; // Osc 4 phase
    float fVec20[2]; // Osc 4 diff state
    float fRec48[2]; // Osc 5 phase
    float fVec22[2]; // Osc 5 diff state

    // Búferes de delay circular para los osciladores del cluster
    std::array<float, 128> fVec13;
    std::array<float, 128> fVec15;
    std::array<float, 128> fVec17;
    std::array<float, 256> fVec19;
    std::array<float, 256> fVec21;
    std::array<float, 512> fVec23;

    int IOTA0 = 0; // Índice de escritura circular

    // Generador de ruido aleatorio LCG
    int iRec39 = 0;

    // Disparadores
    std::atomic<float> m_triggerVelocity{0.0f};
    std::atomic<bool> m_triggered{false};
    float m_currentVelocity = 1.0f;

    inline float power2(float value) { return value * value; }
    inline float semitono2ratio(float s) { return std::pow(2.0f, s / 12.0f); }

public:
    HiHatVoice() = default;
    ~HiHatVoice() override = default;

    void initialize(double sampleRate) override;
    void clearState() override;
    void trigger(float velocity) override;
    void processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer = nullptr) override;
    void setParameter(const std::string& name, float value) override;

    // ---- v2: Introspección y serialización ----
    const bazz::InstrumentDescriptor& getDescriptor() const override {
        return hat_params::descriptor;
    }

    void setParameterById(uint32_t paramId, float value) override;
    int getState(float* buffer, int maxParams) const override;
    void setState(const float* buffer, int numParams) override;
};
