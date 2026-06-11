#include "FunkTribuKickVoice.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
#include <iostream>

// Faust interface bases are defined in core/FaustDefs.h
#include "../core/FaustDefs.h"

// Wrap Faust-generated kick code in its own namespace to avoid class mydsp conflicts
namespace funktribu {
    using ::dsp;
    using ::UI;
    using ::Meta;

    #include "../../plugin_instrumentos/kick/kick.cpp"
}

// Local helper UI subclass for mapping Faust parameters to pointers
class VoiceMapUI : public UI {
public:
    std::unordered_map<std::string, FAUSTFLOAT*> pathMap;
    std::string lastPath;

    void declare(FAUSTFLOAT* zone, const char* key, const char* val) override {
        if (std::string(key) == "osc") {
            std::string sVal(val);
            size_t spacePos = sVal.find(' ');
            if (spacePos != std::string::npos) {
                lastPath = sVal.substr(0, spacePos);
            } else {
                lastPath = sVal;
            }
            pathMap[lastPath] = zone;
        }
    }

    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        (void)init; (void)min; (void)max; (void)step;
        if (!lastPath.empty()) {
            pathMap[lastPath] = zone;
            lastPath.clear();
        } else {
            pathMap[label] = zone;
        }
    }

    void addCheckButton(const char* label, FAUSTFLOAT* zone) override {
        if (!lastPath.empty()) {
            pathMap[lastPath] = zone;
            lastPath.clear();
        } else {
            pathMap[label] = zone;
        }
    }
};

FunkTribuKickVoice::FunkTribuKickVoice() = default;

FunkTribuKickVoice::~FunkTribuKickVoice() {
    // Unique pointer handles clean destruction of funktribu::mydsp
}

void FunkTribuKickVoice::initialize(double sampleRate) {
    m_sampleRate = sampleRate;

    m_dsp = std::make_unique<funktribu::mydsp>();
    m_dsp->init(static_cast<int>(m_sampleRate));

    // Map Faust parameter zones using buildUserInterface
    VoiceMapUI mapUI;
    m_dsp->buildUserInterface(&mapUI);

    m_ptrGate     = mapUI.pathMap["/kick/gate"];
    m_ptrPitch    = mapUI.pathMap["/kick/pitch"];
    m_ptrClick    = mapUI.pathMap["/kick/click"];
    m_ptrDecay    = mapUI.pathMap["/kick/decay"];
    m_ptrDrive    = mapUI.pathMap["/kick/drive"];
    m_ptrSubFreq  = mapUI.pathMap["/kick/sub/freq"];
    m_ptrSubGain  = mapUI.pathMap["/kick/sub/gain"];
    m_ptrSubDecay = mapUI.pathMap["/kick/sub/decay"];
    m_ptrResFreq  = mapUI.pathMap["/kick/res/freq"];
    m_ptrResQ     = mapUI.pathMap["/kick/res/q"];
    m_ptrResMix   = mapUI.pathMap["/kick/res/mix"];
    m_ptrLimCeil  = mapUI.pathMap["/kick/lim/ceiling"];
    m_ptrLimAtt   = mapUI.pathMap["/kick/lim/attack"];
    m_ptrLimRel   = mapUI.pathMap["/kick/lim/release"];

    clearState();
}

void FunkTribuKickVoice::clearState() {
    if (m_dsp) {
        m_dsp->instanceClear();
    }
    m_triggered.store(false);
    m_triggerVelocity.store(0.0f);
    m_currentVelocity = 1.0f;
    m_gateActive = false;
}

void FunkTribuKickVoice::trigger(float velocity) {
    m_triggerVelocity.store(velocity);
    m_triggered.store(true);
}

void FunkTribuKickVoice::setParameter(const std::string& name, float value) {
    if (name == "/kick/vol") m_volume.store(value);
    else if (name == "/kick/accent") m_accent.store(value);
    else if (name == "/kick/accent_micro") m_accentMicro.store(value);
    else if (name == "/kick/pitch") m_pitch.store(value);
    else if (name == "/kick/click") m_click.store(value);
    else if (name == "/kick/decay") m_decay.store(value);
    else if (name == "/kick/drive") m_drive.store(value);
    else if (name == "/kick/sub/freq") m_subFreq.store(value);
    else if (name == "/kick/sub/gain") m_subGain.store(value);
    else if (name == "/kick/sub/decay") m_subDecay.store(value);
    else if (name == "/kick/res/freq") m_resFreq.store(value);
    else if (name == "/kick/res/q") m_resQ.store(value);
    else if (name == "/kick/res/mix") m_resMix.store(value);
    else if (name == "/kick/lim/ceiling") m_limCeil.store(value);
    else if (name == "/kick/lim/attack") m_limAtt.store(value);
    else if (name == "/kick/lim/release") m_limRel.store(value);
    else if (name == "/kick/nota") m_note.store(value);
    else if (name == "/kick/reloj") m_clockMult.store(value);
    else if (name == "/kick/swing") m_swing.store(value);
}

void FunkTribuKickVoice::setParameterById(uint32_t paramId, float value) {
    constexpr uint32_t ID_VOL          = bazz::paramHash("/kick/vol");
    constexpr uint32_t ID_ACCENT       = bazz::paramHash("/kick/accent");
    constexpr uint32_t ID_ACCENT_MICRO = bazz::paramHash("/kick/accent_micro");
    constexpr uint32_t ID_PITCH        = bazz::paramHash("/kick/pitch");
    constexpr uint32_t ID_CLICK        = bazz::paramHash("/kick/click");
    constexpr uint32_t ID_DECAY        = bazz::paramHash("/kick/decay");
    constexpr uint32_t ID_DRIVE        = bazz::paramHash("/kick/drive");
    constexpr uint32_t ID_SUB_FREQ     = bazz::paramHash("/kick/sub/freq");
    constexpr uint32_t ID_SUB_GAIN     = bazz::paramHash("/kick/sub/gain");
    constexpr uint32_t ID_SUB_DECAY    = bazz::paramHash("/kick/sub/decay");
    constexpr uint32_t ID_RES_FREQ     = bazz::paramHash("/kick/res/freq");
    constexpr uint32_t ID_RES_Q        = bazz::paramHash("/kick/res/q");
    constexpr uint32_t ID_RES_MIX      = bazz::paramHash("/kick/res/mix");
    constexpr uint32_t ID_LIM_CEIL     = bazz::paramHash("/kick/lim/ceiling");
    constexpr uint32_t ID_LIM_ATT      = bazz::paramHash("/kick/lim/attack");
    constexpr uint32_t ID_LIM_REL      = bazz::paramHash("/kick/lim/release");
    constexpr uint32_t ID_NOTA         = bazz::paramHash("/kick/nota");
    constexpr uint32_t ID_RELOJ        = bazz::paramHash("/kick/reloj");
    constexpr uint32_t ID_SWING        = bazz::paramHash("/kick/swing");

    switch (paramId) {
        case ID_VOL:          m_volume.store(value); break;
        case ID_ACCENT:       m_accent.store(value); break;
        case ID_ACCENT_MICRO: m_accentMicro.store(value); break;
        case ID_PITCH:        m_pitch.store(value); break;
        case ID_CLICK:        m_click.store(value); break;
        case ID_DECAY:        m_decay.store(value); break;
        case ID_DRIVE:        m_drive.store(value); break;
        case ID_SUB_FREQ:     m_subFreq.store(value); break;
        case ID_SUB_GAIN:     m_subGain.store(value); break;
        case ID_SUB_DECAY:    m_subDecay.store(value); break;
        case ID_RES_FREQ:     m_resFreq.store(value); break;
        case ID_RES_Q:        m_resQ.store(value); break;
        case ID_RES_MIX:      m_resMix.store(value); break;
        case ID_LIM_CEIL:     m_limCeil.store(value); break;
        case ID_LIM_ATT:      m_limAtt.store(value); break;
        case ID_LIM_REL:      m_limRel.store(value); break;
        case ID_NOTA:         m_note.store(value); break;
        case ID_RELOJ:        m_clockMult.store(value); break;
        case ID_SWING:        m_swing.store(value); break;
        default: break;
    }
}

void FunkTribuKickVoice::processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer) {
    if (!m_dsp) return;

    // 1. Update DSP values from local parameters with dynamic accent modulation
    float pitch = m_pitch.load();
    float click = m_click.load();
    float decay = m_decay.load();
    float drive = m_drive.load();
    float subFreq = m_subFreq.load();
    float subGain = m_subGain.load();
    float subDecay = m_subDecay.load();
    float resFreq = m_resFreq.load();
    float resQ = m_resQ.load();
    float resMix = m_resMix.load();
    float limCeil = m_limCeil.load();
    float limAtt = m_limAtt.load();
    float limRel = m_limRel.load();
    
    // Dynamic timbre modulation: higher accent increases decay, saturation drive, and sub-bass rumble
    float acc = m_accent.load();
    decay = decay * (1.0f + acc * 0.15f);
    drive = drive * (1.0f + acc * 0.20f);
    subGain = subGain * (1.0f + acc * 0.15f);
    
    if (m_ptrPitch)    *m_ptrPitch    = pitch;
    if (m_ptrClick)    *m_ptrClick    = click;
    if (m_ptrDecay)    *m_ptrDecay    = decay;
    if (m_ptrDrive)    *m_ptrDrive    = drive;
    if (m_ptrSubFreq)  *m_ptrSubFreq  = subFreq;
    if (m_ptrSubGain)  *m_ptrSubGain  = subGain;
    if (m_ptrSubDecay) *m_ptrSubDecay = subDecay;
    if (m_ptrResFreq)  *m_ptrResFreq  = resFreq;
    if (m_ptrResQ)     *m_ptrResQ     = resQ;
    if (m_ptrResMix)   *m_ptrResMix   = resMix;
    if (m_ptrLimCeil)  *m_ptrLimCeil  = limCeil;
    if (m_ptrLimAtt)   *m_ptrLimAtt   = limAtt;
    if (m_ptrLimRel)   *m_ptrLimRel   = limRel;

    // 2. Trigger detection and gate switching
    bool triggered = false;
    float triggerVel = 1.0f;

    if (triggerBuffer) {
        for (int i = 0; i < numSamples; ++i) {
            if (triggerBuffer[i] > 0.0f) {
                triggered = true;
                triggerVel = triggerBuffer[i];
                break;
            }
        }
    } else {
        if (m_triggered.exchange(false)) {
            triggered = true;
            triggerVel = m_triggerVelocity.load();
        }
    }

    if (triggered) {
        if (m_ptrGate) *m_ptrGate = 1.0f;
        m_gateActive = true;
        m_currentVelocity = triggerVel;
    } else if (m_gateActive) {
        // Automatically release the gate after one block
        if (m_ptrGate) *m_ptrGate = 0.0f;
        m_gateActive = false;
    }

    // 3. Setup pointers for Faust compute
    // Faust compute takes an array of pointers to output buffers
    // In our case, the kick generates stereo output
    alignas(16) float dspOutL[1024];
    alignas(16) float dspOutR[1024];
    float* outputs[2] = { dspOutL, dspOutR };

    int samplesProcessed = 0;
    float volumeScale = m_volume.load() * m_currentVelocity;

    while (samplesProcessed < numSamples) {
        int chunk = std::min(numSamples - samplesProcessed, 1024);
        m_dsp->compute(chunk, nullptr, outputs);

        for (int i = 0; i < chunk; ++i) {
            outputBufferL[samplesProcessed + i] += dspOutL[i] * volumeScale;
            outputBufferR[samplesProcessed + i] += dspOutR[i] * volumeScale;
        }

        samplesProcessed += chunk;
    }
}

int FunkTribuKickVoice::getState(float* buffer, int maxParams) const {
    const auto& desc = getDescriptor();
    int count = std::min(maxParams, desc.numParams);

    if (count > 0)  buffer[0]  = m_volume.load();
    if (count > 1)  buffer[1]  = m_accent.load();
    if (count > 2)  buffer[2]  = m_accentMicro.load();
    if (count > 3)  buffer[3]  = m_pitch.load();
    if (count > 4)  buffer[4]  = m_click.load();
    if (count > 5)  buffer[5]  = m_decay.load();
    if (count > 6)  buffer[6]  = m_drive.load();
    if (count > 7)  buffer[7]  = m_subFreq.load();
    if (count > 8)  buffer[8]  = m_subGain.load();
    if (count > 9)  buffer[9]  = m_subDecay.load();
    if (count > 10) buffer[10] = m_resFreq.load();
    if (count > 11) buffer[11] = m_resQ.load();
    if (count > 12) buffer[12] = m_resMix.load();
    if (count > 13) buffer[13] = m_limCeil.load();
    if (count > 14) buffer[14] = m_limAtt.load();
    if (count > 15) buffer[15] = m_limRel.load();
    if (count > 16) buffer[16] = m_note.load();
    if (count > 17) buffer[17] = m_clockMult.load();
    if (count > 18) buffer[18] = m_swing.load();

    return count;
}

void FunkTribuKickVoice::setState(const float* buffer, int numParams) {
    if (numParams > 0)  m_volume.store(buffer[0]);
    if (numParams > 1)  m_accent.store(buffer[1]);
    if (numParams > 2)  m_accentMicro.store(buffer[2]);
    if (numParams > 3)  m_pitch.store(buffer[3]);
    if (numParams > 4)  m_click.store(buffer[4]);
    if (numParams > 5)  m_decay.store(buffer[5]);
    if (numParams > 6)  m_drive.store(buffer[6]);
    if (numParams > 7)  m_subFreq.store(buffer[7]);
    if (numParams > 8)  m_subGain.store(buffer[8]);
    if (numParams > 9)  m_subDecay.store(buffer[9]);
    if (numParams > 10) m_resFreq.store(buffer[10]);
    if (numParams > 11) m_resQ.store(buffer[11]);
    if (numParams > 12) m_resMix.store(buffer[12]);
    if (numParams > 13) m_limCeil.store(buffer[13]);
    if (numParams > 14) m_limAtt.store(buffer[14]);
    if (numParams > 15) m_limRel.store(buffer[15]);
    if (numParams > 16) m_note.store(buffer[16]);
    if (numParams > 17) m_clockMult.store(buffer[17]);
    if (numParams > 18) m_swing.store(buffer[18]);
}
