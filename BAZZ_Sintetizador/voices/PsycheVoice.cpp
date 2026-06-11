#include "PsycheVoice.h"
#include "KickVoice.h" // Para usar la tabla de senos g_sineTable
#include <cmath>
#include <algorithm>

void PsycheVoice::initialize(double sampleRate) {
    m_sampleRate = sampleRate;

    fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(m_sampleRate)));
    fConst1 = std::tan(6283.1855f / fConst0);
    fConst2 = 2.0f * (1.0f - 1.0f / power2(fConst1));
    fConst3 = 1.0f / fConst1;
    fConst4 = (fConst3 + -1.4142135f) / fConst1 + 1.0f;
    fConst5 = 1.0f / ((fConst3 + 1.4142135f) / fConst1 + 1.0f);
    fConst6 = std::tan(188.49556f / fConst0);
    fConst7 = power2(fConst6);
    fConst8 = 2.0f * (1.0f - 1.0f / fConst7);
    fConst9 = 1.0f / fConst6;
    fConst10 = (fConst9 + -1.4142135f) / fConst6 + 1.0f;
    fConst11 = (fConst9 + 1.4142135f) / fConst6 + 1.0f;
    fConst12 = 1.0f / fConst11;
    fConst13 = 0.06666667f / fConst0;
    fConst14 = 0.075f * fConst0;
    fConst15 = std::max<float>(1.0f, 0.05f * fConst0);
    fConst16 = 1.0f / fConst15;
    fConst17 = 0.3f / fConst0;
    fConst18 = 1.0f / fConst0;
    fConst19 = 0.5f * fConst0;
    fConst20 = 0.08f / fConst0;
    fConst21 = 1.0f / (fConst7 * fConst11);

    // Constantes de la FDN y compresor de Synth 1
    fConst22 = std::tan(20420.352f / fConst0);
    fConst23 = 2.0f * (1.0f - 1.0f / power2(fConst22));
    fConst24 = 1.0f / fConst22;
    fConst25 = (fConst24 + -1.4142135f) / fConst22 + 1.0f;
    fConst26 = 1.0f / ((fConst24 + 1.4142135f) / fConst22 + 1.0f);
    fConst27 = std::tan(471.2389f / fConst0);
    fConst28 = power2(fConst27);
    fConst29 = 2.0f * (1.0f - 1.0f / fConst28);
    fConst30 = 1.0f / fConst27;
    fConst31 = (fConst30 + -1.4142135f) / fConst27 + 1.0f;
    fConst32 = (fConst30 + 1.4142135f) / fConst27 + 1.0f;
    fConst33 = 1.0f / fConst32;
    fConst34 = 1.0f / std::tan(10995.574f / fConst0);
    fConst35 = 1.0f - fConst34;
    fConst36 = 1.0f / (fConst34 + 1.0f);
    fConst37 = 1.0f / (fConst28 * fConst32);
    fConst61 = 3.1415927f / fConst0;

    clearState();
}

void PsycheVoice::clearState() {
    std::fill(std::begin(iVec0), std::end(iVec0), 0);
    std::fill(std::begin(iVec2), std::end(iVec2), 0);
    std::fill(std::begin(iRec5), std::end(iRec5), 0);
    
    std::fill(std::begin(fRec7), std::end(fRec7), 0.0f);
    std::fill(std::begin(fRec8), std::end(fRec8), 0.0f);
    std::fill(std::begin(fVec4), std::end(fVec4), 0.0f);
    fVec5.fill(0.0f);
    
    std::fill(std::begin(fRec11), std::end(fRec11), 0.0f);
    std::fill(std::begin(fRec9), std::end(fRec9), 0.0f);
    std::fill(std::begin(fRec2), std::end(fRec2), 0.0f);
    std::fill(std::begin(fRec1), std::end(fRec1), 0.0f);
    fVec6.fill(0.0f);
    
    std::fill(std::begin(fRec12), std::end(fRec12), 0.0f);

    IOTA0 = 0;

    m_triggered.store(false);
    m_triggerVelocity.store(0.0f);
    m_currentVelocity = 1.0f;
}

void PsycheVoice::trigger(float velocity) {
    m_triggerVelocity.store(velocity);
    m_triggered.store(true);
}

void PsycheVoice::setParameter(const std::string& name, float value) {
    if (name == "/syn1/vol") m_volume.store(value);
    else if (name == "/syn1/accent") m_accent.store(value);
    else if (name == "/syn1/dec") m_decay.store(value);
    else if (name == "/syn1/auto_v") m_autoVel.store(value);
    else if (name == "/syn1/auto_p") m_autoProf.store(value);
    else if (name == "/syn1/auto_r") m_autoRes.store(value);
    else if (name == "/syn1/nota") m_note.store(value);
    else if (name == "/syn1/reloj") m_clockMult.store(value);
    else if (name == "/syn1/osc1") m_osc1.store(value);
    else if (name == "/syn1/osc2") m_osc2.store(value);
    else if (name == "/syn1/swing") m_swing.store(value);
    else if (name == "/syn2/disp") m_disp.store(value);
}

void PsycheVoice::processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer) {
    float vol = m_volume.load();
    float decay = m_decay.load();
    float autoVel = m_autoVel.load();
    float autoProf = m_autoProf.load();
    float autoRes = m_autoRes.load();
    float note = m_note.load();
    float osc1 = m_osc1.load();
    float osc2 = m_osc2.load();

    float fSlow26 = 1.0f / std::max<float>(1.0f, fConst0 * decay);
    float fSlow27 = std::pow(2.0f, 0.083333336f * (note - 69.0f));
    float fSlow28 = 4.4e+02f * fSlow27 * std::pow(2.0f, 0.083333336f * osc1);
    float fSlow29 = 4.4e+02f * fSlow27 * std::pow(2.0f, 0.083333336f * osc2);
    
    float fSlow30 = fConst18 * autoVel;
    float fSlow31 = autoProf;

    for (int i0 = 0; i0 < numSamples; ++i0) {
        iVec0[0] = 1;
        int iTemp3 = (1 - iVec0[1]);

        // 1. Evaluar Trigger
        int iTemp1 = 0;
        if (triggerBuffer) {
            if (triggerBuffer[i0] > 0.0f) {
                iTemp1 = 1;
                m_currentVelocity = triggerBuffer[i0];
            }
        } else {
            if (m_triggered.exchange(false)) {
                iTemp1 = 1;
                m_currentVelocity = m_triggerVelocity.load();
            }
        }

        iVec2[0] = iTemp1;
        iRec5[0] = (iRec5[1] + (iRec5[1] > 0)) * (iTemp1 <= iVec2[1]) + (iTemp1 > iVec2[1]);
        float fTemp2 = static_cast<float>(iRec5[0]);

        // 2. Síntesis Saw + Square (Osc 1 y 2)
        // Acumulación de fase
        float fTemp4 = ((iTemp3) ? 0.0f : fConst17 + fRec7[1]);
        fRec7[0] = fTemp4 - std::floor(fTemp4);
        
        float fTemp5 = std::max<float>(fSlow28 + g_sineTable.lookup(fRec7[0]), 23.44895f);
        float fTemp6 = std::max<float>(20.0f, std::fabs(fTemp5));
        
        float fTemp7 = ((iTemp3) ? 0.0f : fRec8[1] + fConst18 * fTemp6);
        fRec8[0] = fTemp7 - std::floor(fTemp7);
        
        float fTemp8 = power2(2.0f * fRec8[0] - 1.0f);
        fVec4[0] = fTemp8;
        
        float fTemp9 = static_cast<float>(iVec0[1]);
        float fTemp10 = fTemp9 * (fTemp8 - fVec4[1]) / fTemp6;
        fVec5[IOTA0 & 2047] = fTemp10;
        
        float fTemp11 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fTemp5));
        int iTemp12 = static_cast<int>(fTemp11);
        float fTemp13 = std::floor(fTemp11);
        
        float fTemp14 = ((iTemp3) ? 0.0f : fConst20 + fRec11[1]);
        fRec11[0] = fTemp14 - std::floor(fTemp14);
        
        float fTemp15 = std::max<float>(1.1920929e-07f, std::fabs(fSlow29 + 2.0f * g_sineTable.lookup(fRec11[0])));
        float fTemp16 = fRec9[1] + fConst18 * fTemp15;
        float fTemp17 = fTemp16 - 1.0f;
        int iTemp18 = fTemp17 < 0.0f;
        fRec9[0] = ((iTemp18) ? fTemp16 : fTemp17);
        float fRec10 = ((iTemp18) ? fTemp16 : fTemp16 + fTemp17 * (1.0f - fConst0 / fTemp15));

        // Envolvente de volumen de Synth 1
        float env_val = std::max<float>(0.0f, std::min<float>(fConst16 * fTemp2, fSlow26 * (fConst15 - fTemp2) + 1.0f)) * m_currentVelocity;

        // Ecuaciones de los filtros resonantes paso bajo
        fRec2[0] = (0.6f * (2.0f * fRec10 - 1.0f) + fConst14 * (fTemp10 - fVec5[(IOTA0 - iTemp12) & 2047] * (fTemp13 + (1.0f - fTemp11)) - (fTemp11 - fTemp13) * fVec5[(IOTA0 - (iTemp12 + 1)) & 2047])) * env_val - fConst12 * (fConst10 * fRec2[2] + fConst8 * fRec2[1]);
        fRec1[0] = fConst21 * (fRec2[2] + (fRec2[0] - 2.0f * fRec2[1])) - fConst5 * (fConst4 * fRec1[2] + fConst2 * fRec1[1]);
        
        float fTemp19 = fRec1[2] + fRec1[0] + 2.0f * fRec1[1];
        fVec6[IOTA0 & 255] = fTemp19; // Señal cruda generada por los osciladores

        // LFO de paneo y de barrido del resonador
        float fTemp20 = ((iTemp3) ? 0.0f : fSlow30 + fRec12[1]);
        fRec12[0] = fTemp20 - std::floor(fTemp20);
        m_lfoPhase[i0] = fRec12[0];
        // Guardar outputs en los buffers miembro
        m_lfoPhase[i0] = fRec12[0];
        m_waveguideOut[i0] = fTemp19;

        // Actualizar estados
        iVec0[1] = iVec0[0];
        iVec2[1] = iVec2[0];
        iRec5[1] = iRec5[0];
        fRec7[1] = fRec7[0];
        fRec8[1] = fRec8[0];
        fVec4[1] = fVec4[0];
        fRec11[1] = fRec11[0];
        fRec9[1] = fRec9[0];
        fRec2[2] = fRec2[1];
        fRec2[1] = fRec2[0];
        fRec1[2] = fRec1[1];
        fRec1[1] = fRec1[0];
        fRec12[1] = fRec12[0];

        IOTA0 = IOTA0 + 1;
    }
}

// ---- v2: Despacho de parámetros por ID hash (sin strings en RT) ----
void PsycheVoice::setParameterById(uint32_t paramId, float value) {
    constexpr uint32_t ID_VOL     = bazz::paramHash("/syn1/vol");
    constexpr uint32_t ID_ACCENT  = bazz::paramHash("/syn1/accent");
    constexpr uint32_t ID_DEC     = bazz::paramHash("/syn1/dec");
    constexpr uint32_t ID_AUTO_V  = bazz::paramHash("/syn1/auto_v");
    constexpr uint32_t ID_AUTO_P  = bazz::paramHash("/syn1/auto_p");
    constexpr uint32_t ID_AUTO_R  = bazz::paramHash("/syn1/auto_r");
    constexpr uint32_t ID_NOTA    = bazz::paramHash("/syn1/nota");
    constexpr uint32_t ID_RELOJ   = bazz::paramHash("/syn1/reloj");
    constexpr uint32_t ID_OSC1    = bazz::paramHash("/syn1/osc1");
    constexpr uint32_t ID_OSC2    = bazz::paramHash("/syn1/osc2");
    constexpr uint32_t ID_SWING   = bazz::paramHash("/syn1/swing");
    constexpr uint32_t ID_DISP    = bazz::paramHash("/syn2/disp");

    switch (paramId) {
        case ID_VOL:     m_volume.store(value); break;
        case ID_ACCENT:  m_accent.store(value); break;
        case ID_DEC:     m_decay.store(value); break;
        case ID_AUTO_V:  m_autoVel.store(value); break;
        case ID_AUTO_P:  m_autoProf.store(value); break;
        case ID_AUTO_R:  m_autoRes.store(value); break;
        case ID_NOTA:    m_note.store(value); break;
        case ID_RELOJ:   m_clockMult.store(value); break;
        case ID_OSC1:    m_osc1.store(value); break;
        case ID_OSC2:    m_osc2.store(value); break;
        case ID_SWING:   m_swing.store(value); break;
        case ID_DISP:    m_disp.store(value); break;
        default: break;
    }
}

// ---- v2: Serialización de estado ----
int PsycheVoice::getState(float* buffer, int maxParams) const {
    const auto& desc = getDescriptor();
    int count = std::min(maxParams, desc.numParams);

    if (count > 0)  buffer[0]  = m_volume.load();
    if (count > 1)  buffer[1]  = m_accent.load();
    if (count > 2)  buffer[2]  = m_decay.load();
    if (count > 3)  buffer[3]  = m_autoVel.load();
    if (count > 4)  buffer[4]  = m_autoProf.load();
    if (count > 5)  buffer[5]  = m_autoRes.load();
    if (count > 6)  buffer[6]  = m_note.load();
    if (count > 7)  buffer[7]  = m_clockMult.load();
    if (count > 8)  buffer[8]  = m_osc1.load();
    if (count > 9)  buffer[9]  = m_osc2.load();
    if (count > 10) buffer[10] = m_swing.load();
    if (count > 11) buffer[11] = m_disp.load();

    return count;
}

void PsycheVoice::setState(const float* buffer, int numParams) {
    if (numParams > 0)  m_volume.store(buffer[0]);
    if (numParams > 1)  m_accent.store(buffer[1]);
    if (numParams > 2)  m_decay.store(buffer[2]);
    if (numParams > 3)  m_autoVel.store(buffer[3]);
    if (numParams > 4)  m_autoProf.store(buffer[4]);
    if (numParams > 5)  m_autoRes.store(buffer[5]);
    if (numParams > 6)  m_note.store(buffer[6]);
    if (numParams > 7)  m_clockMult.store(buffer[7]);
    if (numParams > 8)  m_osc1.store(buffer[8]);
    if (numParams > 9)  m_osc2.store(buffer[9]);
    if (numParams > 10) m_swing.store(buffer[10]);
    if (numParams > 11) m_disp.store(buffer[11]);
}
