#include "SnareVoice.h"
#include "KickVoice.h" // Para usar la tabla de senos g_sineTable
#include <cmath>
#include <algorithm>

void SnareVoice::initialize(double sampleRate) {
    m_sampleRate = sampleRate;

    fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(m_sampleRate)));
    fConst18 = 1.0f / fConst0;
    fConst15 = std::max<float>(1.0f, 0.05f * fConst0);
    fConst16 = 1.0f / fConst15;
    
    fConst63 = std::tan(28274.334f / fConst0);
    fConst64 = 2.0f * (1.0f - 1.0f / power2(fConst63));
    fConst65 = 1.0f / fConst63;
    fConst66 = (fConst65 + -1.4142135f) / fConst63 + 1.0f;
    fConst67 = 1.0f / ((fConst65 + 1.4142135f) / fConst63 + 1.0f);
    
    fConst68 = std::max<float>(1.0f, 0.0005f * fConst0);
    fConst69 = 1.0f / fConst68;
    fConst70 = 2233.421f / fConst0;
    fConst71 = 1210.8909f / fConst0;
    fConst61 = 3.1415927f / fConst0;

    clearState();
}

void SnareVoice::clearState() {
    std::fill(std::begin(iVec0), std::end(iVec0), 0);
    std::fill(std::begin(iVec27), std::end(iVec27), 0);
    std::fill(std::begin(iRec54), std::end(iRec54), 0);
    std::fill(std::begin(fRec57), std::end(fRec57), 0.0f);
    std::fill(std::begin(fRec58), std::end(fRec58), 0.0f);
    std::fill(std::begin(fRec59), std::end(fRec59), 0.0f);
    std::fill(std::begin(fRec53), std::end(fRec53), 0.0f);
    std::fill(std::begin(fRec52), std::end(fRec52), 0.0f);
    iRec39 = 0;
    
    m_triggered.store(false);
    m_triggerVelocity.store(0.0f);
    m_currentVelocity = 1.0f;
}

void SnareVoice::trigger(float velocity) {
    m_triggerVelocity.store(velocity);
    m_triggered.store(true);
}

void SnareVoice::setParameter(const std::string& name, float value) {
    if (name == "/snare/vol") m_volume.store(value);
    else if (name == "/snare/accent") m_accent.store(value);
    else if (name == "/snare/tune") m_tune.store(value);
    else if (name == "/snare/dec_cuerpo") m_decayBody.store(value);
    else if (name == "/snare/dec_resorte") m_decaySnare.store(value);
    else if (name == "/snare/hp") m_hp.store(value);
    else if (name == "/snare/freq") m_freq.store(value);
    else if (name == "/snare/mix") m_mix.store(value);
    else if (name == "/snare/nota") m_note.store(value);
    else if (name == "/snare/reloj") m_clockMult.store(value);
    else if (name == "/snare/q") m_q.store(value);
    else if (name == "/snare/drive") m_drive.store(value);
    else if (name == "/snare/swing") m_swing.store(value);
}

void SnareVoice::processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer) {
    float vol = m_volume.load();
    float tune = m_tune.load();
    float decayBody = m_decayBody.load();
    float decaySnare = m_decaySnare.load();
    float hp = m_hp.load();
    float freq = m_freq.load();
    float mix = m_mix.load();
    float note = m_note.load();
    float q = m_q.load();
    float drive = m_drive.load();

    // Coeficientes variables del Snare
    float fSlow226 = std::tan(fConst61 * hp);
    float fSlow227 = power2(fSlow226);
    float fSlow228 = 2.0f * (1.0f - 1.0f / fSlow227);
    float fSlow229 = 1.0f / fSlow226;
    float fSlow230 = (fSlow229 - 1.4142135f) / fSlow226 + 1.0f;
    float fSlow231 = (fSlow229 + 1.4142135f) / fSlow226 + 1.0f;
    float fSlow232 = 1.0f / fSlow231;
    
    float fSlow258 = 1.0f / std::max<float>(1.0f, fConst0 * decaySnare);
    float fSlow259 = std::tan(fConst61 * freq);
    float fSlow260 = 2.0f * (1.0f - 1.0f / power2(fSlow259));
    float fSlow261 = 1.0f / q;
    float fSlow262 = 1.0f / fSlow259;
    float fSlow263 = (fSlow262 - fSlow261) / fSlow259 + 1.0f;
    float fSlow264 = (fSlow261 + fSlow262) / fSlow259 + 1.0f;
    float fSlow265 = 1.0f / fSlow264;
    
    float fSlow266 = mix;
    float fSlow267 = 2.34f * (fSlow266 / (fSlow259 * fSlow264));
    float fSlow268 = 1.0f / std::max<float>(1.0f, fConst0 * decayBody);
    float fSlow269 = std::pow(2.0f, 0.083333336f * (note - 69.0f)) * std::pow(2.0f, 0.083333336f * tune);
    float fSlow270 = fConst70 * fSlow269;
    float fSlow271 = fConst71 * fSlow269;
    float fSlow272 = 1.0f - fSlow266;
    float fSlow274 = drive;
    float fSlow275 = 1.0f / (fSlow227 * fSlow231);

    for (int i0 = 0; i0 < numSamples; ++i0) {
        iVec0[0] = 1;
        int iTemp3 = (1 - iVec0[1]);

        // 1. Evaluar Trigger
        int iTemp68 = 0;
        if (triggerBuffer) {
            if (triggerBuffer[i0] > 0.0f) {
                iTemp68 = 1;
                m_currentVelocity = triggerBuffer[i0];
            }
        } else {
            if (m_triggered.exchange(false)) {
                iTemp68 = 1;
                m_currentVelocity = m_triggerVelocity.load();
            }
        }

        iVec27[0] = iTemp68;
        iRec54[0] = (iRec54[1] + (iRec54[1] > 0)) * (iTemp68 <= iVec27[1]) + (iTemp68 > iVec27[1]);
        float fTemp69 = static_cast<float>(iRec54[0]);

        // 2. Generar Ruido Blanco usando el LCG
        iRec39 = 1103515245 * iRec39 + 12345;
        float fTemp37 = static_cast<float>(iRec39);
        
        // Filtro paso-banda del ruido para emular los resortes metálicos (snare wires)
        // 4.656613e-10f es la escala para pasar a float [-1, 1]
        fRec57[0] = 4.656613e-10f * fTemp37 - fSlow265 * (fSlow263 * fRec57[2] + fSlow260 * fRec57[1]);
        
        // 3. Cuerpo Tonal (Dos osciladores de onda sinusoidal a frecuencias de la caja)
        float fTemp70 = ((iTemp3) ? 0.0f : fSlow270 + fRec58[1]);
        fRec58[0] = fTemp70 - std::floor(fTemp70);
        float fTemp71 = ((iTemp3) ? 0.0f : fSlow271 + fRec59[1]);
        fRec59[0] = fTemp71 - std::floor(fTemp71);

        // Envolventes de Snare
        float env_cuerpo = std::max<float>(0.0f, std::min<float>(fConst69 * fTemp69, fSlow268 * (fConst68 - fTemp69) + 1.0f)) * m_currentVelocity;
        float env_resorte = std::max<float>(0.0f, std::min<float>(fConst16 * fTemp69, fSlow258 * (fConst15 - fTemp69) + 1.0f)) * m_currentVelocity;

        // Mezcla de Caja = Cuerpo Tonal + Ruido de Resortes
        float cuerpo_osc = (0.65f * g_sineTable.lookup(fRec59[0]) + 0.35f * g_sineTable.lookup(fRec58[0]));
        float resorte_fil = (fRec57[0] - fRec57[2]);
        
        float snare_raw = fSlow274 * (fSlow272 * cuerpo_osc * env_cuerpo + fSlow267 * resorte_fil * env_resorte);

        // Filtro paso alto de salida + Saturación de salida
        fRec53[0] = snare_raw - fSlow232 * (fSlow230 * fRec53[2] + fSlow228 * fRec53[1]);
        fRec52[0] = fSlow275 * (fRec53[2] + (fRec53[0] - 2.0f * fRec53[1])) - fConst67 * (fConst66 * fRec52[2] + fConst64 * fRec52[1]);

        float snare_out = std::tanh(fConst67 * (fRec52[2] + fRec52[0] + 2.0f * fRec52[1]));

        // Sumar al buffer estéreo de salida
        outputBufferL[i0] += snare_out * vol;
        outputBufferR[i0] += snare_out * vol;

        // Actualizar estados
        iVec0[1] = iVec0[0];
        iVec27[1] = iVec27[0];
        iRec54[1] = iRec54[0];
        fRec57[2] = fRec57[1];
        fRec57[1] = fRec57[0];
        fRec58[1] = fRec58[0];
        fRec59[1] = fRec59[0];
        fRec53[2] = fRec53[1];
        fRec53[1] = fRec53[0];
        fRec52[2] = fRec52[1];
        fRec52[1] = fRec52[0];
    }
}

// ---- v2: Despacho de parámetros por ID hash (sin strings en RT) ----
void SnareVoice::setParameterById(uint32_t paramId, float value) {
    constexpr uint32_t ID_VOL         = bazz::paramHash("/snare/vol");
    constexpr uint32_t ID_ACCENT      = bazz::paramHash("/snare/accent");
    constexpr uint32_t ID_TUNE        = bazz::paramHash("/snare/tune");
    constexpr uint32_t ID_DEC_CUERPO  = bazz::paramHash("/snare/dec_cuerpo");
    constexpr uint32_t ID_DEC_RESORTE = bazz::paramHash("/snare/dec_resorte");
    constexpr uint32_t ID_HP          = bazz::paramHash("/snare/hp");
    constexpr uint32_t ID_FREQ        = bazz::paramHash("/snare/freq");
    constexpr uint32_t ID_MIX         = bazz::paramHash("/snare/mix");
    constexpr uint32_t ID_NOTA        = bazz::paramHash("/snare/nota");
    constexpr uint32_t ID_RELOJ       = bazz::paramHash("/snare/reloj");
    constexpr uint32_t ID_Q           = bazz::paramHash("/snare/q");
    constexpr uint32_t ID_DRIVE       = bazz::paramHash("/snare/drive");
    constexpr uint32_t ID_SWING       = bazz::paramHash("/snare/swing");

    switch (paramId) {
        case ID_VOL:         m_volume.store(value); break;
        case ID_ACCENT:      m_accent.store(value); break;
        case ID_TUNE:        m_tune.store(value); break;
        case ID_DEC_CUERPO:  m_decayBody.store(value); break;
        case ID_DEC_RESORTE: m_decaySnare.store(value); break;
        case ID_HP:          m_hp.store(value); break;
        case ID_FREQ:        m_freq.store(value); break;
        case ID_MIX:         m_mix.store(value); break;
        case ID_NOTA:        m_note.store(value); break;
        case ID_RELOJ:       m_clockMult.store(value); break;
        case ID_Q:           m_q.store(value); break;
        case ID_DRIVE:       m_drive.store(value); break;
        case ID_SWING:       m_swing.store(value); break;
        default: break;
    }
}

// ---- v2: Serialización de estado ----
int SnareVoice::getState(float* buffer, int maxParams) const {
    const auto& desc = getDescriptor();
    int count = std::min(maxParams, desc.numParams);

    if (count > 0)  buffer[0]  = m_volume.load();
    if (count > 1)  buffer[1]  = m_accent.load();
    if (count > 2)  buffer[2]  = m_tune.load();
    if (count > 3)  buffer[3]  = m_decayBody.load();
    if (count > 4)  buffer[4]  = m_decaySnare.load();
    if (count > 5)  buffer[5]  = m_hp.load();
    if (count > 6)  buffer[6]  = m_freq.load();
    if (count > 7)  buffer[7]  = m_mix.load();
    if (count > 8)  buffer[8]  = m_note.load();
    if (count > 9)  buffer[9]  = m_clockMult.load();
    if (count > 10) buffer[10] = m_q.load();
    if (count > 11) buffer[11] = m_drive.load();
    if (count > 12) buffer[12] = m_swing.load();

    return count;
}

void SnareVoice::setState(const float* buffer, int numParams) {
    if (numParams > 0)  m_volume.store(buffer[0]);
    if (numParams > 1)  m_accent.store(buffer[1]);
    if (numParams > 2)  m_tune.store(buffer[2]);
    if (numParams > 3)  m_decayBody.store(buffer[3]);
    if (numParams > 4)  m_decaySnare.store(buffer[4]);
    if (numParams > 5)  m_hp.store(buffer[5]);
    if (numParams > 6)  m_freq.store(buffer[6]);
    if (numParams > 7)  m_mix.store(buffer[7]);
    if (numParams > 8)  m_note.store(buffer[8]);
    if (numParams > 9)  m_clockMult.store(buffer[9]);
    if (numParams > 10) m_q.store(buffer[10]);
    if (numParams > 11) m_drive.store(buffer[11]);
    if (numParams > 12) m_swing.store(buffer[12]);
}
