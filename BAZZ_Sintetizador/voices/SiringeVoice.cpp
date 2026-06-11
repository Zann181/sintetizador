#include "SiringeVoice.h"
#include "KickVoice.h" // Para usar la tabla de senos g_sineTable
#include <cmath>
#include <algorithm>

void SiringeVoice::initialize(double sampleRate) {
    m_sampleRate = sampleRate;

    fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(m_sampleRate)));
    fConst18 = 1.0f / fConst0;
    fConst61 = 3.1415927f / fConst0;
    
    // Constantes de filtros IIR compartidos
    float fConst1 = std::tan(6283.1855f / fConst0);
    float fConst3 = 1.0f / fConst1;
    fConst5 = 1.0f / ((fConst3 + 1.4142135f) / fConst1 + 1.0f);
    
    float fConst6 = std::tan(188.49556f / fConst0);
    float fConst7 = power2(fConst6);
    fConst8 = 2.0f * (1.0f - 1.0f / fConst7);
    float fConst9 = 1.0f / fConst6;
    fConst10 = (fConst9 + -1.4142135f) / fConst6 + 1.0f;
    float fConst11 = (fConst9 + 1.4142135f) / fConst6 + 1.0f;
    fConst12 = 1.0f / fConst11;
    fConst21 = 1.0f / (fConst7 * fConst11);

    fConst13 = 0.06666667f / fConst0;
    fConst14 = 0.075f * fConst0;
    fConst15 = std::max<float>(1.0f, 0.05f * fConst0);
    fConst16 = 1.0f / fConst15;

    // Constantes específicas de Siringe (Synth 2 FDN)
    fConst22 = std::tan(20420.352f / fConst0);
    fConst23 = 2.0f * (1.0f - 1.0f / power2(fConst22));
    fConst24 = 1.0f / fConst22;
    fConst25 = (fConst24 + -1.4142135f) / fConst22 + 1.0f;
    fConst26 = 1.0f / ((fConst24 + 1.4142135f) / fConst22 + 1.0f);
    
    fConst27 = std::tan(471.2389f / fConst0);
    float fConst28 = power2(fConst27);
    fConst29 = 2.0f * (1.0f - 1.0f / fConst27);
    float fConst30 = 1.0f / fConst27;
    fConst31 = (fConst30 + -1.4142135f) / fConst27 + 1.0f;
    fConst32 = (fConst30 + 1.4142135f) / fConst27 + 1.0f;
    fConst33 = 1.0f / fConst32;
    
    float fConst34 = 1.0f / std::tan(10995.574f / fConst0);
    fConst35 = 1.0f - fConst34;
    fConst36 = 1.0f / (fConst34 + 1.0f);
    
    fConst37 = 1.0f / (fConst28 * fConst32);

    clearState();
}

void SiringeVoice::clearState() {
    std::fill(std::begin(iVec0), std::end(iVec0), 0);
    std::fill(std::begin(iVec8), std::end(iVec8), 0);
    std::fill(std::begin(iRec25), std::end(iRec25), 0);
    std::fill(std::begin(fRec22), std::end(fRec22), 0.0f);
    
    fRec18.fill(0.0f);
    fRec19.fill(0.0f);
    fRec20.fill(0.0f);
    fRec21.fill(0.0f);
    std::fill(std::begin(fRec26), std::end(fRec26), 0.0f);
    std::fill(std::begin(fRec27), std::end(fRec27), 0.0f);
    std::fill(std::begin(fRec28), std::end(fRec28), 0.0f);
    std::fill(std::begin(fRec29), std::end(fRec29), 0.0f);
    
    std::fill(std::begin(fRec17), std::end(fRec17), 0.0f);
    std::fill(std::begin(fRec16), std::end(fRec16), 0.0f);
    std::fill(std::begin(fRec15), std::end(fRec15), 0.0f);
    std::fill(std::begin(fRec14), std::end(fRec14), 0.0f);
    std::fill(std::begin(fRec13), std::end(fRec13), 0.0f);

    IOTA0 = 0;
    m_triggered.store(false);
    m_triggerVelocity.store(0.0f);
    m_currentVelocity = 1.0f;
}

void SiringeVoice::trigger(float velocity) {
    m_triggerVelocity.store(velocity);
    m_triggered.store(true);
}

void SiringeVoice::setParameter(const std::string& name, float value) {
    if (name == "/syn2/vol") m_volume.store(value);
    else if (name == "/syn1/vol") m_syn1Vol.store(value);
    else if (name == "/syn2/accent") m_accent.store(value);
    else if (name == "/syn2/dec") m_decay.store(value);
    else if (name == "/syn2/disp") m_disp.store(value);
    else if (name == "/syn2/lfo_f") m_lfoFreq.store(value);
    else if (name == "/syn2/lfo_p") m_lfoProf.store(value);
    else if (name == "/syn2/nota" && name.find("menu") == std::string::npos) {
        if (value >= 12.0f && value <= 24.0f) {
            m_noteInterval.store(value);
        } else {
            m_note.store(value);
        }
    }
    else if (name == "/syn2/reloj") m_clockMult.store(value);
    else if (name == "/syn2/swing") m_swing.store(value);
    else if (name == "/syn2/comp_a") m_compAtt.store(value);
    else if (name == "/syn2/comp_rel") m_compRel.store(value);
    else if (name == "/syn2/comp_r") m_compRatio.store(value);
    else if (name == "/syn2/comp_th") m_compThresh.store(value);
}



void SiringeVoice::processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer) {
    float vol = m_volume.load();
    float decay = m_decay.load();
    float disp = m_disp.load();
    float lfoFreq = m_lfoFreq.load();
    float lfoProf = m_lfoProf.load();
    float noteInterval = m_noteInterval.load();
    float note = m_note.load();
    
    float compAtt = m_compAtt.load();
    float compRel = m_compRel.load();
    float compRatio = m_compRatio.load();
    float compThresh = m_compThresh.load();

    float fSlow69 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (note - 69.0f)) * std::pow(2.0f, 0.083333336f * noteInterval);
    
    float fSlow70 = 0.5f * disp; // dispersion depth
    
    // Compressor parameters
    float fSlow39 = compThresh;
    float fSlow34 = compAtt;
    float fSlow71 = compRel;
    float fSlow76 = 1.0f / std::max<float>(1.1920929e-07f, compRatio) - 1.0f;
    
    // LFO parameters
    float fSlow40 = fConst18 * lfoFreq;
    float fSlow41 = lfoProf;
    
    // Auto LFO attack/release constants
    float fSlow35 = 0.5f * fSlow34;
    int iSlow36 = std::fabs(fSlow35) < 1.1920929e-07f;
    float fSlow37 = ((iSlow36) ? 0.0f : std::exp(-(fConst18 / ((iSlow36) ? 1.0f : fSlow35))));
    float fSlow38 = 1.0f - fSlow37;
    int iSlow72 = std::fabs(fSlow71) < 1.1920929e-07f;
    float fSlow73 = ((iSlow72) ? 0.0f : std::exp(-(fConst18 / ((iSlow72) ? 1.0f : fSlow71))));
    int iSlow74 = std::fabs(fSlow34) < 1.1920929e-07f;
    float fSlow75 = ((iSlow74) ? 0.0f : std::exp(-(fConst18 / ((iSlow74) ? 1.0f : fSlow34))));

    float fSlow68 = 1.0f / std::max<float>(1.0f, fConst0 * decay);
    float fSlow77 = fConst26 * vol; // Siringe volume scaled by fConst26

    for (int i0 = 0; i0 < numSamples; ++i0) {
        iVec0[0] = 1;
        int iTemp3 = (1 - iVec0[1]);

        // 1. Evaluar Trigger
        int iTemp23 = 0;
        if (triggerBuffer) {
            if (triggerBuffer[i0] > 0.0f) {
                iTemp23 = 1;
                m_currentVelocity = triggerBuffer[i0];
            }
        } else {
            if (m_triggered.exchange(false)) {
                iTemp23 = 1;
                m_currentVelocity = m_triggerVelocity.load();
            }
        }

        iVec8[0] = iTemp23;
        iRec25[0] = (iRec25[1] + (iRec25[1] > 0)) * (iTemp23 <= iVec8[1]) + (iTemp23 > iVec8[1]);
        float fTemp25 = static_cast<float>(iRec25[0]);
        
        float fTemp26 = std::max<float>(0.0f, std::min<float>(fConst16 * fTemp25, fSlow68 * (fConst15 - fTemp25) + 1.0f)) * m_currentVelocity;
        
        // Fase del oscilador con sweep de frecuencia instantáneo
        float fTemp27 = ((iTemp3) ? 0.0f : fRec22[1] + fConst18 * (fSlow69 + 1500.0f * fTemp26));
        fRec22[0] = fTemp27 - std::floor(fTemp27);
        
        // Oscilador Siringe
        float fTemp28 = fTemp26 * g_sineTable.lookup(fRec22[0]);

        // 2. Siringe FDN (realimentación matricial y filtros allpass)
        fRec26[0] = -(fConst36 * (fConst35 * fRec26[1] - (fRec19[(IOTA0 - 1400) & 2047] + fRec19[(IOTA0 - 1401) & 2047])));
        fRec27[0] = -(fConst36 * (fConst35 * fRec27[1] - (fRec18[(IOTA0 - 1118) & 2047] + fRec18[(IOTA0 - 1119) & 2047])));
        float fTemp29 = fRec27[0] + fRec26[0];
        fRec28[0] = -(fConst36 * (fConst35 * fRec28[1] - (fRec20[(IOTA0 - 1724) & 2047] + fRec20[(IOTA0 - 1725) & 2047])));
        fRec29[0] = -(fConst36 * (fConst35 * fRec29[1] - (fRec21[(IOTA0 - 2090) & 4095] + fRec21[(IOTA0 - 2091) & 4095])));
        
        fRec18[IOTA0 & 2047] = fSlow70 * (fRec29[0] + fRec28[0] + fTemp29) + fTemp28;
        float fTemp30 = fRec27[0] - fRec26[0];
        fRec19[IOTA0 & 2047] = fTemp28 - fSlow70 * (fRec29[0] - (fRec28[0] + fTemp30));
        fRec20[IOTA0 & 2047] = fTemp28 - fSlow70 * (fRec29[0] - (fTemp29 - fRec28[0]));
        fRec21[IOTA0 & 4095] = fTemp28 + fSlow70 * (fRec29[0] - (fRec28[0] - fTemp30));

        // Paneo / LFO Lento
        float fTemp20 = ((iTemp3) ? 0.0f : fSlow40 + fRec17[1]);
        fRec17[0] = fTemp20 - std::floor(fTemp20);

        // Suma de FDN modulada por LFO
        float fTemp31 = (fRec18[IOTA0 & 2047] + fRec19[IOTA0 & 2047] + fRec20[IOTA0 & 2047] + fRec21[IOTA0 & 4095]) * (fSlow41 * g_sineTable.lookup(fRec17[0]) + 1.0f);
        
        // 3. Dinámica del Compresor Mono
        float fTemp32 = std::fabs(0.25f * fTemp31);
        float fTemp33 = ((fTemp32 > fRec16[1]) ? fSlow75 : fSlow73);
        fRec16[0] = fTemp32 * (1.0f - fTemp33) + fRec16[1] * fTemp33;
        
        fRec15[0] = fSlow76 * std::max<float>(20.0f * std::log10(std::max<float>(1.1754944e-38f, fRec16[0])) - fSlow39, 0.0f) * fSlow38 + fSlow37 * fRec15[1];
        
        fRec14[0] = 0.25f * fTemp31 * std::pow(10.0f, 0.05f * fRec15[0]) - fConst33 * (fConst31 * fRec14[2] + fConst29 * fRec14[1]);
        fRec13[0] = fConst37 * (fRec14[2] + (fRec14[0] - 2.0f * fRec14[1])) - fConst26 * (fConst25 * fRec13[2] + fConst23 * fRec13[1]);

        // Siringe output
        float siringe_out = fSlow77 * (fRec13[2] + fRec13[0] + 2.0f * fRec13[1]);

        outputBufferL[i0] += siringe_out;
        outputBufferR[i0] += siringe_out;

        // Actualizar estados
        iVec0[1] = iVec0[0];
        iVec8[1] = iVec8[0];
        iRec25[1] = iRec25[0];
        fRec22[1] = fRec22[0];
        fRec26[1] = fRec26[0];
        fRec27[1] = fRec27[0];
        fRec28[1] = fRec28[0];
        fRec29[1] = fRec29[0];
        fRec17[1] = fRec17[0];
        fRec16[1] = fRec16[0];
        fRec15[1] = fRec15[0];
        fRec14[2] = fRec14[1];
        fRec14[1] = fRec14[0];
        fRec13[2] = fRec13[1];
        fRec13[1] = fRec13[0];

        IOTA0 = IOTA0 + 1;
    }
}

// ---- v2: Despacho de parámetros por ID hash (sin strings en RT) ----
void SiringeVoice::setParameterById(uint32_t paramId, float value) {
    constexpr uint32_t ID_VOL        = bazz::paramHash("/syn2/vol");
    constexpr uint32_t ID_SYN1VOL    = bazz::paramHash("/syn1/vol");
    constexpr uint32_t ID_ACCENT     = bazz::paramHash("/syn2/accent");
    constexpr uint32_t ID_DEC        = bazz::paramHash("/syn2/dec");
    constexpr uint32_t ID_DISP       = bazz::paramHash("/syn2/disp");
    constexpr uint32_t ID_LFO_F      = bazz::paramHash("/syn2/lfo_f");
    constexpr uint32_t ID_LFO_P      = bazz::paramHash("/syn2/lfo_p");
    constexpr uint32_t ID_NOTA       = bazz::paramHash("/syn2/nota");
    constexpr uint32_t ID_INTERVALO  = bazz::paramHash("/syn2/intervalo");
    constexpr uint32_t ID_RELOJ      = bazz::paramHash("/syn2/reloj");
    constexpr uint32_t ID_SWING      = bazz::paramHash("/syn2/swing");
    constexpr uint32_t ID_COMP_A     = bazz::paramHash("/syn2/comp_a");
    constexpr uint32_t ID_COMP_REL   = bazz::paramHash("/syn2/comp_rel");
    constexpr uint32_t ID_COMP_R     = bazz::paramHash("/syn2/comp_r");
    constexpr uint32_t ID_COMP_TH    = bazz::paramHash("/syn2/comp_th");

    switch (paramId) {
        case ID_VOL:        m_volume.store(value); break;
        case ID_SYN1VOL:    m_syn1Vol.store(value); break;
        case ID_ACCENT:     m_accent.store(value); break;
        case ID_DEC:        m_decay.store(value); break;
        case ID_DISP:       m_disp.store(value); break;
        case ID_LFO_F:      m_lfoFreq.store(value); break;
        case ID_LFO_P:      m_lfoProf.store(value); break;
        case ID_NOTA:       m_note.store(value); break;
        case ID_INTERVALO:  m_noteInterval.store(value); break;
        case ID_RELOJ:      m_clockMult.store(value); break;
        case ID_SWING:      m_swing.store(value); break;
        case ID_COMP_A:     m_compAtt.store(value); break;
        case ID_COMP_REL:   m_compRel.store(value); break;
        case ID_COMP_R:     m_compRatio.store(value); break;
        case ID_COMP_TH:    m_compThresh.store(value); break;
        default: break;
    }
}

// ---- v2: Serialización de estado ----
int SiringeVoice::getState(float* buffer, int maxParams) const {
    const auto& desc = getDescriptor();
    int count = std::min(maxParams, desc.numParams);

    if (count > 0)  buffer[0]  = m_volume.load();
    if (count > 1)  buffer[1]  = m_syn1Vol.load();
    if (count > 2)  buffer[2]  = m_accent.load();
    if (count > 3)  buffer[3]  = m_decay.load();
    if (count > 4)  buffer[4]  = m_disp.load();
    if (count > 5)  buffer[5]  = m_lfoFreq.load();
    if (count > 6)  buffer[6]  = m_lfoProf.load();
    if (count > 7)  buffer[7]  = m_note.load();
    if (count > 8)  buffer[8]  = m_noteInterval.load();
    if (count > 9)  buffer[9]  = m_clockMult.load();
    if (count > 10) buffer[10] = m_swing.load();
    if (count > 11) buffer[11] = m_compAtt.load();
    if (count > 12) buffer[12] = m_compRel.load();
    if (count > 13) buffer[13] = m_compRatio.load();
    if (count > 14) buffer[14] = m_compThresh.load();

    return count;
}

void SiringeVoice::setState(const float* buffer, int numParams) {
    if (numParams > 0)  m_volume.store(buffer[0]);
    if (numParams > 1)  m_syn1Vol.store(buffer[1]);
    if (numParams > 2)  m_accent.store(buffer[2]);
    if (numParams > 3)  m_decay.store(buffer[3]);
    if (numParams > 4)  m_disp.store(buffer[4]);
    if (numParams > 5)  m_lfoFreq.store(buffer[5]);
    if (numParams > 6)  m_lfoProf.store(buffer[6]);
    if (numParams > 7)  m_note.store(buffer[7]);
    if (numParams > 8)  m_noteInterval.store(buffer[8]);
    if (numParams > 9)  m_clockMult.store(buffer[9]);
    if (numParams > 10) m_swing.store(buffer[10]);
    if (numParams > 11) m_compAtt.store(buffer[11]);
    if (numParams > 12) m_compRel.store(buffer[12]);
    if (numParams > 13) m_compRatio.store(buffer[13]);
    if (numParams > 14) m_compThresh.store(buffer[14]);
}
