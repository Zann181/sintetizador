#pragma once
#include "../core/IInstrumentVoice.h"
#include "../core/InstrumentDescriptor.h"
#include <atomic>
#include <cmath>
#include <algorithm>
#include <array>

// ============================================================================
// Descriptor estático de la Caja TR-808
// ============================================================================
namespace snare_params {
    static constexpr bazz::ParamInfo params[] = {
        BAZZ_PARAM("/snare/vol",         "Volumen",         "Sintesis", 0.0f,    1.0f,   0.65f,  0.01f, Slider),
        BAZZ_PARAM("/snare/accent",      "Accent",          "Sintesis", 0.0f,    1.0f,   0.5f,   0.01f, Knob),
        BAZZ_PARAM("/snare/tune",        "Afinación",       "Sintesis", -12.0f,  12.0f,  0.0f,   0.1f,  Knob),
        BAZZ_PARAM("/snare/dec_cuerpo",  "Dec Cuerp",       "Sintesis", 0.01f,   2.0f,   0.07f,  0.01f, Knob),
        BAZZ_PARAM("/snare/dec_resorte", "Dec Resor",       "Sintesis", 0.01f,   2.0f,   0.16f,  0.01f, Knob),
        BAZZ_PARAM("/snare/hp",          "Filtro HP",       "Filtros",  20.0f,  2000.0f, 160.0f, 1.0f,  Knob),
        BAZZ_PARAM("/snare/freq",        "Filtro Res",      "Filtros",  200.0f, 8000.0f, 1650.0f, 10.0f, Knob),
        BAZZ_PARAM("/snare/mix",         "Mix Snare",       "Sintesis", 0.0f,    1.0f,   0.55f,  0.01f, Knob),
        BAZZ_PARAM("/snare/nota",        "Nota",            "Sintesis", 24.0f,   84.0f,  36.0f,  1.0f,  Menu),
        BAZZ_PARAM("/snare/reloj",       "Reloj",           "Sintesis", 0.25f,   4.0f,   1.0f,   0.25f, Menu),
        BAZZ_PARAM("/snare/q",           "Q Resor",         "Filtros",  0.1f,   10.0f,   2.5f,   0.1f,  Knob),
        BAZZ_PARAM("/snare/drive",       "Saturación",      "Sintesis", 0.1f,   10.0f,   1.0f,   0.1f,  Knob),
        BAZZ_PARAM("/snare/swing",       "Swing",           "Sintesis", 0.0f,   75.0f,   0.0f,   1.0f,  Knob),
    };

    static constexpr bazz::InstrumentDescriptor descriptor = {
        "snare_808",                            // typeName
        "Caja TR-808",                          // displayName
        "Caja analógica con oscilador de cuerpo doble, generador de ruido paso banda y saturación", // description
        bazz::OutputType::Mono,                 // outputType
        params,                                 // params
        sizeof(params) / sizeof(params[0]),     // numParams
        1                                       // defaultChannel
    };
}

class SnareVoice : public IInstrumentVoice {
private:
    double m_sampleRate = 44100.0;

    // Constantes de calibración de audio
    float fConst0;
    float fConst18;
    float fConst15;
    float fConst16;
    float fConst63;
    float fConst64;
    float fConst65;
    float fConst66;
    float fConst67;
    float fConst68;
    float fConst69;
    float fConst70;
    float fConst71;
    float fConst61;

    // Parámetros de control
    std::atomic<float> m_volume{0.65f};
    std::atomic<float> m_accent{0.5f};
    std::atomic<float> m_tune{0.0f};
    std::atomic<float> m_decayBody{0.07f};
    std::atomic<float> m_decaySnare{0.16f};
    std::atomic<float> m_hp{160.0f};
    std::atomic<float> m_freq{1650.0f};
    std::atomic<float> m_mix{0.55f};
    std::atomic<float> m_note{36.0f};
    std::atomic<float> m_clockMult{1.0f};
    std::atomic<float> m_q{2.5f};
    std::atomic<float> m_drive{1.0f};
    std::atomic<float> m_swing{0.0f};

    // Estados del DSP
    int iVec0[2];
    int iVec27[2];
    int iRec54[2];
    float fRec57[3];
    float fRec58[2];
    float fRec59[2];
    float fRec53[3];
    float fRec52[3];
    
    // Generador de ruido aleatorio LCG
    int iRec39 = 0;

    // Disparadores
    std::atomic<float> m_triggerVelocity{0.0f};
    std::atomic<bool> m_triggered{false};
    float m_currentVelocity = 1.0f;

    inline float power2(float value) { return value * value; }
    inline float semitono2ratio(float s) { return std::pow(2.0f, s / 12.0f); }

public:
    SnareVoice() = default;
    ~SnareVoice() override = default;

    void initialize(double sampleRate) override;
    void clearState() override;
    void trigger(float velocity) override;
    void processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer = nullptr) override;
    void setParameter(const std::string& name, float value) override;

    // ---- v2: Introspección y serialización ----
    const bazz::InstrumentDescriptor& getDescriptor() const override {
        return snare_params::descriptor;
    }

    void setParameterById(uint32_t paramId, float value) override;
    int getState(float* buffer, int maxParams) const override;
    void setState(const float* buffer, int numParams) override;
};
