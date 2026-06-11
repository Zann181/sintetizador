#pragma once
#include "../core/IInstrumentVoice.h"
#include "../core/InstrumentDescriptor.h"
#include <atomic>
#include <cmath>
#include <algorithm>
#include <array>

// ============================================================================
// Descriptor estático del Synth Psyche FM
// ============================================================================
namespace psyche_params {
    static constexpr bazz::ParamInfo params[] = {
        BAZZ_PARAM("/syn1/vol",    "Volumen",       "Sintesis", 0.0f,   1.0f,   0.85f,  0.01f, Slider),
        BAZZ_PARAM("/syn1/accent", "Accent",        "Sintesis", 0.0f,   1.0f,   0.5f,   0.01f, Knob),
        BAZZ_PARAM("/syn1/dec",    "Decaimiento",   "Sintesis", 0.01f,  5.0f,   0.2f,   0.01f, Knob),
        BAZZ_PARAM("/syn1/auto_v", "Auto Pan Vel",  "Modulacion",0.0f,  20.0f,  0.5f,   0.05f, Knob),
        BAZZ_PARAM("/syn1/auto_p", "Auto Pan Prof", "Modulacion",0.0f,  1.0f,   0.7f,   0.01f, Knob),
        BAZZ_PARAM("/syn1/auto_r", "Pan Resonance", "Modulacion",0.1f,  20.0f,  4.5f,   0.1f,  Knob),
        BAZZ_PARAM("/syn1/nota",   "Nota",          "Sintesis", 24.0f,  84.0f,  36.0f,  1.0f,  Menu),
        BAZZ_PARAM("/syn1/reloj",  "Reloj",         "Sintesis", 0.25f,  4.0f,   1.0f,   0.25f, Menu),
        BAZZ_PARAM("/syn1/osc1",   "Afinación Osc1","Sintesis", -24.0f, 24.0f,  5.0f,   0.5f,  Knob),
        BAZZ_PARAM("/syn1/osc2",   "Afinación Osc2","Sintesis", -24.0f, 24.0f,  12.0f,  0.5f,  Knob),
        BAZZ_PARAM("/syn1/swing",  "Swing",         "Sintesis", 0.0f,   75.0f,  0.0f,   1.0f,  Knob),
        BAZZ_PARAM("/syn2/disp",   "FM Dispersion", "Sintesis", 0.0f,   1.0f,   0.5f,   0.01f, Knob),
    };

    static constexpr bazz::InstrumentDescriptor descriptor = {
        "psyche_fm",                            // typeName
        "Synth Psyche FM",                      // displayName
        "Sintetizador FM psicodélico de 2 operadores con modulación cruzada, autopanner y resonador", // description
        bazz::OutputType::Stereo,               // outputType
        params,                                 // params
        sizeof(params) / sizeof(params[0]),     // numParams
        4                                       // defaultChannel
    };
}

class PsycheVoice : public IInstrumentVoice {
private:
    double m_sampleRate = 44100.0;

    // Constantes de calibración de audio
    float fConst0;
    float fConst1;
    float fConst2;
    float fConst3;
    float fConst4;
    float fConst5;
    float fConst6;
    float fConst7;
    float fConst8;
    float fConst9;
    float fConst10;
    float fConst11;
    float fConst12;
    float fConst13;
    float fConst14;
    float fConst15;
    float fConst16;
    float fConst17;
    float fConst18;
    float fConst19;
    float fConst20;
    float fConst21;
    
    // Filtros de compresor y FDN
    float fConst22;
    float fConst23;
    float fConst24;
    float fConst25;
    float fConst26;
    float fConst27;
    float fConst28;
    float fConst29;
    float fConst30;
    float fConst31;
    float fConst32;
    float fConst33;
    float fConst34;
    float fConst35;
    float fConst36;
    float fConst37;
    float fConst61;

    // Parámetros de control (atómicos)
    std::atomic<float> m_volume{0.85f};
    std::atomic<float> m_accent{0.5f};
    std::atomic<float> m_decay{0.2f};
    std::atomic<float> m_autoVel{0.5f};
    std::atomic<float> m_autoProf{0.7f};
    std::atomic<float> m_autoRes{4.5f};
    std::atomic<float> m_note{36.0f};
    std::atomic<float> m_clockMult{1.0f};
    std::atomic<float> m_osc1{5.0f};
    std::atomic<float> m_osc2{12.0f};
    std::atomic<float> m_swing{0.0f};
    std::atomic<float> m_disp{0.5f};

    // Estados del DSP
    int iVec0[2];
    int iVec2[2];
    int iRec5[2];
    
    float fRec7[2]; // Osc 1 phase
    float fRec8[2]; // Osc 2 phase
    float fVec4[2]; // Diferenciador
    std::array<float, 2048> fVec5; // Delay del oscilador
    
    float fRec11[2]; // Viento phase
    float fRec9[2];  // Integrador
    float fRec2[3];  // Filtro
    float fRec1[3];  // Filtro
    std::array<float, 256> fVec6; // Delay de salida
    
    float fRec12[2]; // Auto panner LFO phase
    float fRec17[2]; // Doppler LFO phase
    float fRec24[2]; // Doppler tempo phase
    
    int iVec7[32768]; // Búfer de trigger doppler
    int iRec23[2];    // Contador doppler
    int iVec8[2];
    int iRec25[2];
    
    float fRec22[2]; // Osc 3 phase
    
    // FDN Reverb de 4 canales
    std::array<float, 2048> fRec18;
    std::array<float, 2048> fRec19;
    std::array<float, 2048> fRec20;
    std::array<float, 4096> fRec21;
    float fRec26[2];
    float fRec27[2];
    float fRec28[2];
    float fRec29[2];
    
    // Compressor
    float fRec16[2];
    float fRec15[2];
    float fRec14[3];
    float fRec13[3];

    int IOTA0 = 0; // Índice de escritura circular

    // Disparadores
    std::atomic<float> m_triggerVelocity{0.0f};
    std::atomic<bool> m_triggered{false};
    float m_currentVelocity = 1.0f;

    inline float power2(float value) { return value * value; }
    inline float semitono2ratio(float s) { return std::pow(2.0f, s / 12.0f); }

public:
    PsycheVoice() = default;
    ~PsycheVoice() override = default;

    void initialize(double sampleRate) override;
    void clearState() override;
    void trigger(float velocity) override;
    void processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer = nullptr) override;
    void setParameter(const std::string& name, float value) override;

    // ---- v2: Introspección y serialización ----
    const bazz::InstrumentDescriptor& getDescriptor() const override {
        return psyche_params::descriptor;
    }

    void setParameterById(uint32_t paramId, float value) override;
    int getState(float* buffer, int maxParams) const override;
    void setState(const float* buffer, int numParams) override;

    // Búferes del LFO y de la guía de ondas
    const float* getLfoPhase() const { return m_lfoPhase; }
    const float* getWaveguideOut() const { return m_waveguideOut; }

private:
    float m_lfoPhase[4096] = {0.0f};
    float m_waveguideOut[4096] = {0.0f};
};
