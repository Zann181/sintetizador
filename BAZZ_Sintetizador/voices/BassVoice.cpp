#include "BassVoice.h"
#include <cmath>
#include <algorithm>

void BassVoice::initialize(double sampleRate) {
    m_sampleRate = sampleRate;

    fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(m_sampleRate)));
    fConst18 = 1.0f / fConst0;
    fConst42 = 1.0f / ((1.0f / fConst18 + 1.4142135f) / fConst18 + 1.0f); // wait, let's verify fConst42
    
    // De untitled.cpp:
    fConst38 = std::tan(2513.2742f / fConst0);
    fConst39 = 2.0f * (1.0f - 1.0f / power2(fConst38));
    fConst40 = 1.0f / fConst38;
    fConst41 = (fConst40 + -1.4142135f) / fConst38 + 1.0f;
    fConst42 = 1.0f / ((fConst40 + 1.4142135f) / fConst38 + 1.0f);
    
    fConst43 = std::tan(62.831852f / fConst0);
    fConst44 = power2(fConst43);
    fConst45 = 2.0f * (1.0f - 1.0f / fConst44);
    fConst46 = 1.0f / fConst43;
    fConst47 = (fConst46 + -1.4142135f) / fConst43 + 1.0f;
    fConst48 = (fConst46 + 1.4142135f) / fConst43 + 1.0f;
    fConst49 = 1.0f / fConst48;
    fConst50 = std::exp(-(2e+02f / fConst0));
    fConst51 = 1.0f - fConst50;
    fConst52 = std::max<float>(1.0f, 0.001f * fConst0);
    fConst53 = 1.0f / fConst52;
    fConst54 = 1.0f / std::max<float>(1.0f, 0.18f * fConst0);
    fConst55 = 1.0f / std::tan(4712.389f / fConst0);
    fConst56 = 1.0f - fConst55;
    fConst57 = 1.0f / (fConst55 + 1.0f);
    fConst58 = 0.0022727272f * fConst0;
    fConst59 = 3.0f / fConst0;
    fConst60 = 1.0f / (fConst44 * fConst48);
    fConst61 = 3.1415927f / fConst0;

    clearState();
}

void BassVoice::clearState() {
    std::fill(std::begin(iVec0), std::end(iVec0), 0);
    std::fill(std::begin(iVec10), std::end(iVec10), 0);
    std::fill(std::begin(fRec33), std::end(fRec33), 0.0f);
    std::fill(std::begin(fRec32), std::end(fRec32), 0.0f);
    std::fill(std::begin(iRec37), std::end(iRec37), 0);
    std::fill(std::begin(fRec38), std::end(fRec38), 0.0f);
    std::fill(std::begin(fRec41), std::end(fRec41), 0.0f);
    std::fill(std::begin(fRec40), std::end(fRec40), 0.0f);
    std::fill(std::begin(fRec31), std::end(fRec31), 0.0f);
    std::fill(std::begin(fRec30), std::end(fRec30), 0.0f);

    fRec36.fill(0.0f);
    IOTA0 = 0;
    iRec39 = 0;
    std::fill(std::begin(fVec11), std::end(fVec11), 0.0f);

    m_triggered.store(false);
    m_triggerVelocity.store(0.0f);
    m_currentVelocity = 1.0f;
}

void BassVoice::trigger(float velocity) {
    m_triggerVelocity.store(velocity);
    m_triggered.store(true);
}

void BassVoice::setParameter(const std::string& name, float value) {
    if (name == "/bass/vol") m_volume.store(value);
    else if (name == "/bass/accent") m_accent.store(value);
    else if (name == "/bass/dec") m_decay.store(value);
    else if (name == "/bass/detune") m_detune.store(value);
    else if (name == "/bass/lfo") m_lfo.store(value);
    else if (name == "/bass/intervalo") m_interval.store(value);
    else if (name == "/bass/nota") m_note.store(value);
    else if (name == "/bass/reloj") m_clockMult.store(value);
    else if (name == "/bass/drive") m_drive.store(value);
    else if (name == "/bass/swing") m_swing.store(value);
    else if (name == "/master/bpm") m_bpm.store(value);
}

void BassVoice::processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer) {
    float vol = m_volume.load();
    float decay = m_decay.load();
    float detune = m_detune.load();
    float lfo = m_lfo.load();
    float interval = m_interval.load();
    float note = m_note.load();
    float drive = m_drive.load();
    float bpm = m_bpm.load();

    float fSlow104 = 0.004166667f * (bpm / decay);
    
    // Detune y cálculo de la longitud de la guía de ondas L_dinamico_bass
    float fSlow106 = detune;
    float fSlow107 = fConst58 * ((0.059f * fSlow106 + 1.0f) / (std::pow(2.0f, 0.083333336f * (note - 69.0f)) * std::pow(2.0f, 0.083333336f * interval)));
    
    int iSlow108 = static_cast<int>(fSlow107);
    int iSlow109 = std::min<int>(131073, std::max<int>(0, iSlow108 + 1)) + 1;
    float fSlow110 = std::floor(fSlow107);
    float fSlow111 = fSlow107 - fSlow110;
    int iSlow112 = std::min<int>(131073, std::max<int>(0, iSlow108)) + 1;
    float fSlow113 = fSlow110 + (1.0f - fSlow107);

    float fSlow114 = lfo;
    float fSlow115 = 3.0f * drive;
    float fSlow116 = (fSlow115 + 1.0f) * (0.014f * fSlow106 + 0.985f);
    float fSlow117 = fConst42 * vol;

    for (int i0 = 0; i0 < numSamples; ++i0) {
        iVec0[0] = 1;
        int iTemp3 = (1 - iVec0[1]);

        // 1. Evaluar Trigger
        int iTemp35 = 0;
        if (triggerBuffer) {
            if (triggerBuffer[i0] > 0.0f) {
                iTemp35 = 1;
                m_currentVelocity = triggerBuffer[i0];
            }
        } else {
            if (m_triggered.exchange(false)) {
                iTemp35 = 1;
                m_currentVelocity = m_triggerVelocity.load();
            }
        }

        iVec10[0] = iTemp35;
        
        // 2. Envolvente exponencial release
        fRec33[0] = (fConst18 + fRec33[1]) * (1.0f - static_cast<float>(iTemp35));
        fRec32[0] = fConst51 * std::exp(-(fSlow104 * fRec33[0])) + fConst50 * fRec32[1];
        
        iRec37[0] = (iRec37[1] + (iRec37[1] > 0)) * (iTemp35 <= iVec10[1]) + (iTemp35 > iVec10[1]);
        float fTemp36 = static_cast<float>(iRec37[0]);

        // Generar Ruido LCG
        iRec39 = 1103515245 * iRec39 + 12345;
        float fTemp37 = static_cast<float>(iRec39);
        fVec11[0] = fTemp37;
        
        // Filtro del ruido excitador
        fRec38[0] = fConst57 * (4.656613e-10f * (fTemp37 + fVec11[1]) - fConst56 * fRec38[1]);
        
        // LFO lento para modulación de fase/resonancia del filtro del loop
        fRec41[0] = fConst59 + fRec41[1] * static_cast<float>(1 - iTemp35);
        float fTemp38 = std::max<float>(0.01f, 0.6f - 0.15f * (fSlow106 - fSlow114 * std::sin(6.2831855f * (fRec41[0] - std::floor(fRec41[0])))));
        
        // Filtro paso bajo de realimentación interpolado
        fRec40[0] = fRec40[1] * (1.0f - fTemp38) + fTemp38 * (fSlow113 * fRec36[(IOTA0 - iSlow112) & 8191] + fSlow111 * fRec36[(IOTA0 - iSlow109) & 8191]);
        
        // Excitación + realimentación de la guía de ondas con saturador de tubo (tanh-like)
        float noise_input = fRec38[0] * std::max<float>(0.0f, std::min<float>(fConst53 * fTemp36, fConst54 * (fConst52 - fTemp36) + 1.0f)) * m_currentVelocity;
        
        fRec36[IOTA0 & 8191] = fSlow116 * (fRec40[0] / (fSlow115 * std::fabs(fRec40[0]) + 1.0f)) + noise_input;

        // Salida de la guía de ondas multiplicada por envolvente exponencial
        float bass_raw = fRec36[IOTA0 & 8191] * fRec32[0];

        // Filtro IIR de salida de 4to orden (LPF + HPF)
        fRec31[0] = bass_raw - fConst49 * (fConst47 * fRec31[2] + fConst45 * fRec31[1]);
        fRec30[0] = fConst60 * (fRec31[2] + (fRec31[0] - 2.0f * fRec31[1])) - fConst42 * (fConst41 * fRec30[2] + fConst39 * fRec30[1]);

        float bass_out = fSlow117 * (fRec30[2] + fRec30[0] + 2.0f * fRec30[1]);

        // Sumar al buffer estéreo de salida
        outputBufferL[i0] += bass_out;
        outputBufferR[i0] += bass_out;

        // Actualizar estados
        iVec0[1] = iVec0[0];
        iVec10[1] = iVec10[0];
        fRec33[1] = fRec33[0];
        fRec32[1] = fRec32[0];
        iRec37[1] = iRec37[0];
        fRec38[1] = fRec38[0];
        fRec41[1] = fRec41[0];
        fRec40[1] = fRec40[0];
        fRec31[2] = fRec31[1];
        fRec31[1] = fRec31[0];
        fRec30[2] = fRec30[1];
        fRec30[1] = fRec30[0];
        fVec11[1] = fVec11[0];

        IOTA0 = IOTA0 + 1;
    }
}

// ---- v2: Despacho de parámetros por ID hash (sin strings en RT) ----
void BassVoice::setParameterById(uint32_t paramId, float value) {
    constexpr uint32_t ID_VOL       = bazz::paramHash("/bass/vol");
    constexpr uint32_t ID_ACCENT    = bazz::paramHash("/bass/accent");
    constexpr uint32_t ID_DEC       = bazz::paramHash("/bass/dec");
    constexpr uint32_t ID_DETUNE    = bazz::paramHash("/bass/detune");
    constexpr uint32_t ID_LFO       = bazz::paramHash("/bass/lfo");
    constexpr uint32_t ID_INTERVALO = bazz::paramHash("/bass/intervalo");
    constexpr uint32_t ID_NOTA      = bazz::paramHash("/bass/nota");
    constexpr uint32_t ID_RELOJ     = bazz::paramHash("/bass/reloj");
    constexpr uint32_t ID_DRIVE     = bazz::paramHash("/bass/drive");
    constexpr uint32_t ID_SWING     = bazz::paramHash("/bass/swing");
    constexpr uint32_t ID_BPM       = bazz::paramHash("/master/bpm");

    switch (paramId) {
        case ID_VOL:       m_volume.store(value); break;
        case ID_ACCENT:    m_accent.store(value); break;
        case ID_DEC:       m_decay.store(value); break;
        case ID_DETUNE:    m_detune.store(value); break;
        case ID_LFO:       m_lfo.store(value); break;
        case ID_INTERVALO: m_interval.store(value); break;
        case ID_NOTA:      m_note.store(value); break;
        case ID_RELOJ:     m_clockMult.store(value); break;
        case ID_DRIVE:     m_drive.store(value); break;
        case ID_SWING:     m_swing.store(value); break;
        case ID_BPM:       m_bpm.store(value); break;
        default: break;
    }
}

// ---- v2: Serialización de estado ----
int BassVoice::getState(float* buffer, int maxParams) const {
    const auto& desc = getDescriptor();
    int count = std::min(maxParams, desc.numParams);

    if (count > 0)  buffer[0]  = m_volume.load();
    if (count > 1)  buffer[1]  = m_accent.load();
    if (count > 2)  buffer[2]  = m_decay.load();
    if (count > 3)  buffer[3]  = m_detune.load();
    if (count > 4)  buffer[4]  = m_lfo.load();
    if (count > 5)  buffer[5]  = m_interval.load();
    if (count > 6)  buffer[6]  = m_note.load();
    if (count > 7)  buffer[7]  = m_clockMult.load();
    if (count > 8)  buffer[8]  = m_drive.load();
    if (count > 9)  buffer[9]  = m_swing.load();
    if (count > 10) buffer[10] = m_bpm.load();

    return count;
}

void BassVoice::setState(const float* buffer, int numParams) {
    if (numParams > 0)  m_volume.store(buffer[0]);
    if (numParams > 1)  m_accent.store(buffer[1]);
    if (numParams > 2)  m_decay.store(buffer[2]);
    if (numParams > 3)  m_detune.store(buffer[3]);
    if (numParams > 4)  m_lfo.store(buffer[4]);
    if (numParams > 5)  m_interval.store(buffer[5]);
    if (numParams > 6)  m_note.store(buffer[6]);
    if (numParams > 7)  m_clockMult.store(buffer[7]);
    if (numParams > 8)  m_drive.store(buffer[8]);
    if (numParams > 9)  m_swing.store(buffer[9]);
    if (numParams > 10) m_bpm.store(buffer[10]);
}
