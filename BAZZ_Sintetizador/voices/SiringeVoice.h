#pragma once
#include "../core/IInstrumentVoice.h"
#include "../core/InstrumentDescriptor.h"
#include <atomic>
#include <cmath>
#include <algorithm>
#include <array>

// ============================================================================
// Descriptor estático de Siringe FDN
// ============================================================================
namespace siringe_params {
    static constexpr bazz::ParamInfo params[] = {
        BAZZ_PARAM("/syn2/vol",        "Volumen",       "Sintesis",   0.0f,    1.0f,   0.22f,   0.01f, Slider),
        BAZZ_PARAM("/syn1/vol",        "Volumen Syn1",  "Sintesis",   0.0f,    1.0f,   0.85f,   0.01f, Slider),
        BAZZ_PARAM("/syn2/accent",     "Accent",        "Sintesis",   0.0f,    1.0f,   0.5f,    0.01f, Knob),
        BAZZ_PARAM("/syn2/dec",        "Decaimiento",   "Sintesis",   0.01f,   5.0f,   0.2f,    0.01f, Knob),
        BAZZ_PARAM("/syn2/disp",       "FM Dispersion", "Sintesis",   0.0f,    1.0f,   0.5f,    0.01f, Knob),
        BAZZ_PARAM("/syn2/lfo_f",      "LFO Frec",      "Modulacion", 0.1f,   20.0f,   2.0f,    0.1f,  Knob),
        BAZZ_PARAM("/syn2/lfo_p",      "LFO Prof",      "Modulacion", 0.0f,    1.0f,   0.5f,    0.01f, Knob),
        BAZZ_PARAM("/syn2/nota",       "Nota",          "Sintesis",   24.0f,  84.0f,   36.0f,   1.0f,  Menu),
        BAZZ_PARAM("/syn2/intervalo",  "Intervalo",     "Sintesis",   12.0f,  24.0f,   12.0f,   1.0f,  Knob),
        BAZZ_PARAM("/syn2/reloj",      "Reloj",         "Sintesis",   0.25f,   4.0f,   1.0f,    0.25f, Menu),
        BAZZ_PARAM("/syn2/swing",      "Swing",         "Sintesis",   0.0f,   75.0f,   0.0f,    1.0f,  Knob),
        BAZZ_PARAM("/syn2/comp_a",     "Comp Ataque",   "Dinamica",   0.0001f, 0.1f,   0.005f,  0.0005f,Knob),
        BAZZ_PARAM("/syn2/comp_rel",   "Comp Release",  "Dinamica",   0.01f,   1.0f,   0.1f,    0.01f, Knob),
        BAZZ_PARAM("/syn2/comp_r",     "Comp Ratio",    "Dinamica",   1.0f,   20.0f,   6.0f,    0.1f,  Knob),
        BAZZ_PARAM("/syn2/comp_th",    "Comp Umbral",   "Dinamica",   -60.0f,  0.0f,   -20.0f,  1.0f,  Knob),
    };

    static constexpr bazz::InstrumentDescriptor descriptor = {
        "siringe_fdn",                          // typeName
        "Siringe FDN",                          // displayName
        "Sintetizador con resonancia de guía de ondas feedback delay network de 4 canales y compresor", // description
        bazz::OutputType::Stereo,               // outputType
        params,                                 // params
        sizeof(params) / sizeof(params[0]),     // numParams
        5                                       // defaultChannel
    };
}

class SiringeVoice : public IInstrumentVoice {
private:
    double m_sampleRate = 44100.0;

    // Constantes de calibración de audio
    float fConst0;
    float fConst5;
    float fConst8;
    float fConst10;
    float fConst12;
    float fConst13;
    float fConst14;
    float fConst15;
    float fConst16;
    float fConst18;
    float fConst19;
    float fConst20;
    float fConst21;
    float fConst22;
    float fConst23;
    float fConst24;
    float fConst25;
    float fConst26;
    float fConst27;
    float fConst29;
    float fConst31;
    float fConst32;
    float fConst33;
    float fConst35;
    float fConst36;
    float fConst37;
    float fConst61;

    // Parámetros de control
    std::atomic<float> m_volume{0.22f};
    std::atomic<float> m_syn1Vol{0.85f};
    std::atomic<float> m_accent{0.5f};
    std::atomic<float> m_decay{0.2f};
    std::atomic<float> m_disp{0.5f};
    std::atomic<float> m_lfoFreq{2.0f};
    std::atomic<float> m_lfoProf{0.5f};
    std::atomic<float> m_noteInterval{12.0f};
    std::atomic<float> m_note{36.0f};
    std::atomic<float> m_clockMult{1.0f};
    std::atomic<float> m_swing{0.0f};
    
    // Parámetros del compresor
    std::atomic<float> m_compAtt{0.005f};
    std::atomic<float> m_compRel{0.1f};
    std::atomic<float> m_compRatio{6.0f};
    std::atomic<float> m_compThresh{-20.0f};

    // Estados del DSP
    int iVec0[2];
    int iVec8[2];
    int iRec25[2];
    float fRec22[2]; // Fase del oscilador

    // Siringe FDN (delays 1118, 1400, 1724, 2090)
    std::array<float, 2048> fRec18;
    std::array<float, 2048> fRec19;
    std::array<float, 2048> fRec20;
    std::array<float, 4096> fRec21;
    float fRec26[2];
    float fRec27[2];
    float fRec28[2];
    float fRec29[2];

    // LFO phase accumulator
    float fRec17[2];

    // Compressor
    float fRec16[2];
    float fRec15[2];
    float fRec14[3];
    float fRec13[3];

    int IOTA0 = 0; // Índice circular

    // Disparadores
    std::atomic<float> m_triggerVelocity{0.0f};
    std::atomic<bool> m_triggered{false};
    float m_currentVelocity = 1.0f;

    inline float power2(float value) { return value * value; }

public:
    SiringeVoice() = default;
    ~SiringeVoice() override = default;

    void initialize(double sampleRate) override;
    void clearState() override;
    void trigger(float velocity) override;
    void processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer = nullptr) override;
    void setParameter(const std::string& name, float value) override;

    // ---- v2: Introspección y serialización ----
    const bazz::InstrumentDescriptor& getDescriptor() const override {
        return siringe_params::descriptor;
    }

    void setParameterById(uint32_t paramId, float value) override;
    int getState(float* buffer, int maxParams) const override;
    void setState(const float* buffer, int numParams) override;
};
