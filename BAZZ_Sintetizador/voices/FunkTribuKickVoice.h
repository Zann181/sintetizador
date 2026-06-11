#pragma once
#include "../core/IInstrumentVoice.h"
#include "../core/InstrumentDescriptor.h"
#include <atomic>
#include <memory>
#include <unordered_map>
#include <string>

// Forward declaration of the Faust DSP engine inside funktribu namespace
namespace funktribu {
    class mydsp;
}

namespace tribal_kick_params {
    static constexpr bazz::ParamInfo params[] = {
        BAZZ_PARAM("/kick/vol",         "Volumen",            "Sintesis",   0.0f,   1.0f,   0.85f,  0.01f, Slider),
        BAZZ_PARAM("/kick/accent",      "Accent",             "Sintesis",   0.0f,   1.0f,   0.50f,  0.01f, Knob),
        BAZZ_PARAM("/kick/accent_micro","Accent Micro",       "Sintesis",   0.0f,   1.0f,   0.20f,  0.01f, Knob),
        BAZZ_PARAM("/kick/pitch",       "Pitch Base",         "Sintesis",   30.0f,  100.0f, 52.0f,  0.1f,  Knob),
        BAZZ_PARAM("/kick/click",       "Click Speed",        "Sintesis",   0.005f, 1.0f,   0.68f,  0.001f,Knob),
        BAZZ_PARAM("/kick/decay",       "Decay Cuerpo",       "Sintesis",   0.1f,   1.5f,   0.50f,  0.01f, Knob),
        BAZZ_PARAM("/kick/drive",       "Saturación Drive",   "Sintesis",   1.0f,   10.0f,  7.50f,  0.1f,  Knob),
        BAZZ_PARAM("/kick/sub/freq",    "Sub Frecuencia",     "Sub Boost",  20.0f,  90.0f,  48.0f,  0.5f,  Knob),
        BAZZ_PARAM("/kick/sub/gain",    "Sub Ganancia",       "Sub Boost",  0.0f,   1.0f,   0.55f,  0.01f, Knob),
        BAZZ_PARAM("/kick/sub/decay",   "Sub Decaimiento",    "Sub Boost",  0.05f,  1.2f,   0.60f,  0.01f, Knob),
        BAZZ_PARAM("/kick/res/freq",    "Res Frecuencia",     "Resonancia", 30.0f,  120.0f, 55.0f,  0.5f,  Knob),
        BAZZ_PARAM("/kick/res/q",       "Res Q",              "Resonancia", 1.0f,   20.0f,  12.0f,  0.1f,  Knob),
        BAZZ_PARAM("/kick/res/mix",     "Res Mix",            "Resonancia", 0.0f,   1.0f,   0.40f,  0.01f, Knob),
        BAZZ_PARAM("/kick/lim/ceiling", "Lim Ceil",           "Limiter",    0.5f,   1.0f,   0.97f,  0.01f, Knob),
        BAZZ_PARAM("/kick/lim/attack",  "Lim Attack",         "Limiter",    0.001f, 0.02f,  0.002f, 0.001f,Knob),
        BAZZ_PARAM("/kick/lim/release", "Lim Release",        "Limiter",    0.05f,  0.5f,   0.15f,  0.01f, Knob),
        BAZZ_PARAM("/kick/nota",        "Nota",               "Sintesis",   36.0f,  47.0f,  36.0f,  1.0f,  Menu),
        BAZZ_PARAM("/kick/reloj",       "Reloj",              "Sintesis",   0.25f,  4.0f,   1.0f,   0.25f, Menu),
        BAZZ_PARAM("/kick/swing",       "Swing",              "Sintesis",   0.0f,   75.0f,  0.0f,   1.0f,  Knob),
    };

    static constexpr bazz::InstrumentDescriptor descriptor = {
        "kick_tribal",                          // typeName
        "Bombo Funk Tribu",                     // displayName
        "Bombo Funk Tribu con sub boost, filtro resonante y limiter lookahead", // description
        bazz::OutputType::Stereo,               // outputType
        params,                                 // params
        sizeof(params) / sizeof(params[0]),     // numParams
        0                                       // defaultChannel
    };
}

class FunkTribuKickVoice : public IInstrumentVoice {
private:
    double m_sampleRate = 44100.0;
    std::unique_ptr<funktribu::mydsp> m_dsp;

    // Direct pointers to parameters in the Faust engine
    float* m_ptrGate = nullptr;
    float* m_ptrPitch = nullptr;
    float* m_ptrClick = nullptr;
    float* m_ptrDecay = nullptr;
    float* m_ptrDrive = nullptr;
    float* m_ptrSubFreq = nullptr;
    float* m_ptrSubGain = nullptr;
    float* m_ptrSubDecay = nullptr;
    float* m_ptrResFreq = nullptr;
    float* m_ptrResQ = nullptr;
    float* m_ptrResMix = nullptr;
    float* m_ptrLimCeil = nullptr;
    float* m_ptrLimAtt = nullptr;
    float* m_ptrLimRel = nullptr;

    // Local atomic settings for thread safety and state management
    std::atomic<float> m_volume{0.85f};
    std::atomic<float> m_accent{0.50f};
    std::atomic<float> m_accentMicro{0.20f};
    std::atomic<float> m_pitch{52.0f};
    std::atomic<float> m_click{0.68f};
    std::atomic<float> m_decay{0.50f};
    std::atomic<float> m_drive{7.50f};
    std::atomic<float> m_subFreq{48.0f};
    std::atomic<float> m_subGain{0.55f};
    std::atomic<float> m_subDecay{0.60f};
    std::atomic<float> m_resFreq{55.0f};
    std::atomic<float> m_resQ{12.0f};
    std::atomic<float> m_resMix{0.40f};
    std::atomic<float> m_limCeil{0.97f};
    std::atomic<float> m_limAtt{0.002f};
    std::atomic<float> m_limRel{0.15f};
    
    // Sequencer and routing variables
    std::atomic<float> m_note{36.0f};
    std::atomic<float> m_clockMult{1.0f};
    std::atomic<float> m_swing{0.0f};

    // Trigger state
    std::atomic<float> m_triggerVelocity{0.0f};
    std::atomic<bool> m_triggered{false};
    float m_currentVelocity = 1.0f;
    bool m_gateActive = false;

public:
    FunkTribuKickVoice();
    ~FunkTribuKickVoice() override;

    void initialize(double sampleRate) override;
    void clearState() override;
    void trigger(float velocity) override;
    void processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer = nullptr) override;
    void setParameter(const std::string& name, float value) override;

    // ---- v2: Introspección y serialización ----
    const bazz::InstrumentDescriptor& getDescriptor() const override {
        return tribal_kick_params::descriptor;
    }

    void setParameterById(uint32_t paramId, float value) override;
    int getState(float* buffer, int maxParams) const override;
    void setState(const float* buffer, int numParams) override;
};
