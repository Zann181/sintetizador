#pragma once
#include "../core/IInstrumentVoice.h"
#include "../core/InstrumentDescriptor.h"
#include <atomic>
#include <cmath>
#include <algorithm>
#include <array>

// ============================================================================
// Descriptor estático de la voz de Bajo
// ============================================================================
namespace bass_params {
    static constexpr bazz::ParamInfo params[] = {
        BAZZ_PARAM("/bass/vol",       "Volumen",       "Sintesis", 0.0f,   1.0f,   0.55f,  0.01f, Slider),
        BAZZ_PARAM("/bass/accent",    "Accent",        "Sintesis", 0.0f,   1.0f,   0.5f,   0.01f, Knob),
        BAZZ_PARAM("/bass/dec",       "Decaimiento",   "Sintesis", 0.05f,  5.0f,   0.35f,  0.01f, Knob),
        BAZZ_PARAM("/bass/detune",    "Desafinación",  "Sintesis", 0.0f,   0.5f,   0.04f,  0.001f,Knob),
        BAZZ_PARAM("/bass/lfo",       "LFO Mod",       "Sintesis", 0.0f,   1.0f,   0.45f,  0.01f, Knob),
        BAZZ_PARAM("/bass/intervalo", "Intervalo",     "Sintesis", -24.0f, 24.0f, -12.0f,  1.0f,  Knob),
        BAZZ_PARAM("/bass/nota",      "Nota",          "Sintesis", 24.0f,  84.0f,  36.0f,  1.0f,  Menu),
        BAZZ_PARAM("/bass/reloj",     "Reloj",         "Sintesis", 0.25f,  4.0f,   1.0f,   0.25f, Menu),
        BAZZ_PARAM("/bass/drive",     "Saturación",    "Sintesis", 0.1f,   10.0f,  0.65f,  0.05f, Knob),
        BAZZ_PARAM("/bass/swing",     "Swing",         "Sintesis", 0.0f,   75.0f,  0.0f,   1.0f,  Knob),
        BAZZ_PARAM("/master/bpm",     "BPM",           "Global",   20.0f,  300.0f, 140.0f, 1.0f,  Slider),
    };

    static constexpr bazz::InstrumentDescriptor descriptor = {
        "bass_wg",                              // typeName
        "Bajo Guía de Onda",                    // displayName
        "Bajo por modelo físico de guía de ondas con excitación por ruido y realimentación filtrada", // description
        bazz::OutputType::Mono,                 // outputType
        params,                                 // params
        sizeof(params) / sizeof(params[0]),     // numParams
        3                                       // defaultChannel
    };
}

class BassVoice : public IInstrumentVoice {
private:
    double m_sampleRate = 44100.0;

    // Constantes de calibración de audio
    float fConst0;
    float fConst18;
    float fConst38;
    float fConst40;
    float fConst43;
    float fConst46;
    float fConst42;
    float fConst39;
    float fConst41;
    float fConst44;
    float fConst45;
    float fConst47;
    float fConst48;
    float fConst49;
    float fConst50;
    float fConst51;
    float fConst52;
    float fConst53;
    float fConst54;
    float fConst55;
    float fConst56;
    float fConst57;
    float fConst58;
    float fConst59;
    float fConst60;
    float fConst61;

    // Parámetros de control
    std::atomic<float> m_volume{0.55f};
    std::atomic<float> m_accent{0.5f};
    std::atomic<float> m_decay{0.35f};
    std::atomic<float> m_detune{0.04f};
    std::atomic<float> m_lfo{0.45f};
    std::atomic<float> m_interval{ -12.0f};
    std::atomic<float> m_note{36.0f};
    std::atomic<float> m_clockMult{1.0f};
    std::atomic<float> m_drive{0.65f};
    std::atomic<float> m_swing{0.0f};

    // Estados del DSP
    int iVec0[2];
    int iVec10[2];
    float fRec33[2]; // Contador de tiempo para envolvente exponencial
    float fRec32[2]; // Envolvente exponencial
    int iRec37[2];   // Contador de muestras desde trigger
    float fRec38[2]; // Filtro del ruido blanco
    float fRec41[2]; // Phasor del LFO
    float fRec40[2]; // Filtro del loop de realimentación
    float fRec31[3]; // Filtro de salida IIR
    float fRec30[3]; // Filtro de salida IIR

    // Guía de ondas (Waveguide) buffer circular
    std::array<float, 8192> fRec36;
    int IOTA0 = 0; // Índice de escritura circular

    // Ruido LCG y estado anterior
    int iRec39 = 0;
    float fVec11[2];

    // Disparadores
    std::atomic<float> m_triggerVelocity{0.0f};
    std::atomic<bool> m_triggered{false};
    float m_currentVelocity = 1.0f;

    // Parámetro de tempo global (compartido de forma atómica)
    std::atomic<float> m_bpm{140.0f};

    inline float power2(float value) { return value * value; }
    inline float semitono2ratio(float s) { return std::pow(2.0f, s / 12.0f); }

public:
    BassVoice() = default;
    ~BassVoice() override = default;

    void initialize(double sampleRate) override;
    void clearState() override;
    void trigger(float velocity) override;
    void processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer = nullptr) override;
    void setParameter(const std::string& name, float value) override;

    // Permite al orquestador actualizar el BPM para el cálculo de la envolvente temporal
    void setBpm(float bpm) { m_bpm.store(bpm); }

    // ---- v2: Introspección y serialización ----
    const bazz::InstrumentDescriptor& getDescriptor() const override {
        return bass_params::descriptor;
    }

    void setParameterById(uint32_t paramId, float value) override;
    int getState(float* buffer, int maxParams) const override;
    void setState(const float* buffer, int numParams) override;
};
