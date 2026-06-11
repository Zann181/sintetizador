#include "KickVoice.h"
#include <cmath>
#include <algorithm>

void KickVoice::initialize(double sampleRate) {
    m_sampleRate = sampleRate;
    
    fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(m_sampleRate)));
    float fConst1 = std::tan(6283.1855f / fConst0);
    float fConst2 = 2.0f * (1.0f - 1.0f / power2(fConst1));
    float fConst3 = 1.0f / fConst1;
    float fConst4 = (fConst3 + -1.4142135f) / fConst1 + 1.0f;
    fConst5 = 1.0f / ((fConst3 + 1.4142135f) / fConst1 + 1.0f);
    float fConst6 = std::tan(188.49556f / fConst0);
    float fConst7 = power2(fConst6);
    fConst8 = 2.0f * (1.0f - 1.0f / fConst7);
    float fConst9 = 1.0f / fConst6;
    fConst10 = (fConst9 + -1.4142135f) / fConst6 + 1.0f;
    float fConst11 = (fConst9 + 1.4142135f) / fConst6 + 1.0f;
    fConst12 = 1.0f / fConst11;
    float fConst13 = 0.06666667f / fConst0;
    fConst14 = 0.075f * fConst0;
    fConst15 = std::max<float>(1.0f, 0.05f * fConst0);
    fConst16 = 1.0f / fConst15;
    float fConst17 = 0.3f / fConst0;
    fConst18 = 1.0f / fConst0;
    fConst19 = 0.5f * fConst0;
    fConst20 = 0.08f / fConst0;
    fConst21 = 1.0f / (fConst7 * fConst11);

    float fConst34 = 1.0f / std::tan(10995.574f / fConst0);
    fConst35 = 1.0f - fConst34;
    fConst36 = 1.0f / (fConst34 + 1.0f);

    fConst43 = std::tan(62.831852f / fConst0);
    fConst44 = power2(fConst43);
    fConst45 = 2.0f * (1.0f - 1.0f / fConst44);
    float fConst46 = 1.0f / fConst43;
    fConst47 = (fConst46 + -1.4142135f) / fConst43 + 1.0f;
    fConst48 = (fConst46 + 1.4142135f) / fConst43 + 1.0f;
    fConst49 = 1.0f / fConst48;
    fConst60 = 1.0f / (fConst44 * fConst48);
    fConst61 = 3.1415927f / fConst0;

    fConst72 = std::tan(3769.9111f / fConst0);
    fConst73 = 2.0f * (1.0f - 1.0f / power2(fConst72));
    float fConst74 = 1.0f / fConst72;
    fConst75 = (fConst74 + -1.4142135f) / fConst72 + 1.0f;
    fConst76 = 1.0f / ((fConst74 + 1.4142135f) / fConst72 + 1.0f);

    fConst77 = std::tan(7853.9814f / fConst0);
    fConst78 = 2.0f * (1.0f - 1.0f / power2(fConst77));
    float fConst79 = 1.0f / fConst77;
    fConst80 = (fConst79 + -1.4142135f) / fConst77 + 1.0f;
    fConst81 = 1.0f / ((fConst79 + 1.4142135f) / fConst77 + 1.0f);

    fConst82 = std::exp(-(1e+02f / fConst0));
    fConst83 = 1.0f - fConst82;
    fConst84 = 1.0f - fConst3;
    fConst85 = 1.0f / (fConst3 + 1.0f);

    clearState();
}

void KickVoice::clearState() {
    std::fill(std::begin(iVec0), std::end(iVec0), 0);
    std::fill(std::begin(iVec29), std::end(iVec29), 0);
    std::fill(std::begin(iRec76), std::end(iRec76), 0);
    std::fill(std::begin(fRec77), std::end(fRec77), 0.0f);
    
    std::fill(std::begin(fRec73), std::end(fRec73), 0.0f);
    std::fill(std::begin(fRec72), std::end(fRec72), 0.0f);
    std::fill(std::begin(fVec30), std::end(fVec30), 0.0f);
    
    std::fill(std::begin(fRec71), std::end(fRec71), 0.0f);
    std::fill(std::begin(fRec70), std::end(fRec70), 0.0f);
    std::fill(std::begin(fRec69), std::end(fRec69), 0.0f);
    std::fill(std::begin(fRec68), std::end(fRec68), 0.0f);

    fRec64.fill(0.0f);
    fRec65.fill(0.0f);
    fRec66.fill(0.0f);
    fRec67.fill(0.0f);
    std::fill(std::begin(fRec78), std::end(fRec78), 0.0f);
    std::fill(std::begin(fRec79), std::end(fRec79), 0.0f);
    std::fill(std::begin(fRec80), std::end(fRec80), 0.0f);
    std::fill(std::begin(fRec81), std::end(fRec81), 0.0f);

    fVec31.fill(0.0f);
    fVec32.fill(0.0f);
    std::fill(std::begin(fRec62), std::end(fRec62), 0.0f);
    std::fill(std::begin(fRec60), std::end(fRec60), 0.0f);

    IOTA0 = 0;
    m_rumbleEnv = 0.0f;
    m_triggered.store(false);
    m_triggerVelocity.store(0.0f);
    m_currentVelocity = 1.0f;
    std::fill(std::begin(m_rawPunch), std::end(m_rawPunch), 0.0f);
}

void KickVoice::trigger(float velocity) {
    m_triggerVelocity.store(velocity);
    m_triggered.store(true);
}

void KickVoice::setParameter(const std::string& name, float value) {
    if (name == "/kick/vol") m_volume.store(value);
    else if (name == "/kick/accent") m_accent.store(value);
    else if (name == "/kick/tune") m_tune.store(value);
    else if (name == "/kick/dec") m_decay.store(value);
    else if (name == "/kick/mix") m_mixRumble.store(value);
    else if (name == "/kick/nota") m_note.store(value);
    else if (name == "/kick/reloj") m_clockMult.store(value);
    else if (name == "/kick/swing") m_swing.store(value);
    else if (name == "/kick/sweep") m_sweep.store(value);
    else if (name == "/kick/comp_fmax") m_compFMax.store(value);
    else if (name == "/kick/comp_fmin") m_compFMin.store(value);
    else if (name == "/kick/comp_ratio") m_compRatio.store(value);
    else if (name == "/kick/comp_thresh") m_compThresh.store(value);
    else if (name == "/kick/comp_drive") m_compDrive.store(value);
}

// Global table for sine wave emulating ftbl0mydspSIG0


void KickVoice::processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer) {
    float vol = m_volume.load();
    float tune = m_tune.load();
    float decay = m_decay.load();
    float rumbleMix = m_mixRumble.load();
    float note = m_note.load();
    float sweep = m_sweep.load();
    
    float compFMax = m_compFMax.load();
    float compFMin = m_compFMin.load();
    float compRatio = m_compRatio.load();
    float compThresh = m_compThresh.load();
    float compDrive = m_compDrive.load();

    // Coeficientes variables del Kick
    float fSlow305 = 1.0f / std::max<float>(1.0f, fConst0 * decay);
    float fSlow306 = sweep;
    float fSlow307 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (note - 69.0f)) * std::pow(2.0f, 0.083333336f * tune);
    
    float fSlow313 = 1.8f * rumbleMix;
    float fSlow314 = fConst60 * (1.0f - rumbleMix);

    // Threshold conversion in linear (direct amplitude threshold)
    float fSlow278 = compThresh;

    for (int i0 = 0; i0 < numSamples; ++i0) {
        iVec0[0] = 1;
        int iTemp3 = (1 - iVec0[1]);
        float fTemp9 = static_cast<float>(iVec0[1]);

        // 1. Evaluar Trigger
        int iTemp73 = 0;
        if (triggerBuffer) {
            if (triggerBuffer[i0] > 0.0f) {
                iTemp73 = 1;
                m_currentVelocity = triggerBuffer[i0];
            }
        } else {
            if (m_triggered.exchange(false)) {
                iTemp73 = 1;
                m_currentVelocity = m_triggerVelocity.load();
            }
        }

        iVec29[0] = iTemp73;
        iRec76[0] = (iRec76[1] + (iRec76[1] > 0)) * (iTemp73 <= iVec29[1]) + (iTemp73 > iVec29[1]);
        float fTemp74 = static_cast<float>(iRec76[0]);
        
        float fTemp75 = fConst16 * fTemp74; // fConst16 = 1.0f / std::max(1.0f, 0.05f * fConst0)
        float fTemp76 = fConst15 - fTemp74; // fConst15 = std::max(1.0f, 0.05f * fConst0)
        
        // Fase del oscilador con sweep de pitch (reiniciar fase a 0.0f si hay trigger para pegada constante y alineación de fase)
        float fTemp77 = ((iTemp3 || iTemp73) ? 0.0f : fRec77[1] + fConst18 * (fSlow307 + fSlow306 * std::pow(std::max<float>(0.0f, std::min<float>(fTemp75, fConst16 * fTemp76 + 1.0f)), 1.5f)));
        fRec77[0] = fTemp77 - std::floor(fTemp77);
        
        // Oscilador Kick
        float fTemp78 = g_sineTable.lookup(fRec77[0]) * std::max<float>(0.0f, std::min<float>(fTemp75, fSlow305 * fTemp76 + 1.0f)) * m_currentVelocity;

        // 2. Compresor de pegada
        fRec73[0] = fConst83 * std::fabs(fTemp78) + fConst82 * fRec73[1];
        float fTemp79 = std::max<float>(0.0f, fRec73[0] - fSlow278);
        float fTemp80 = 1.0f / std::tan(fConst61 * std::max<float>(compFMin, compFMax - compRatio * (compFMax - compFMin) * fTemp79));
        float fTemp81 = std::tanh(compDrive * (fTemp78 / (compRatio * fTemp79 + 1.0f)));

        // 3. Filtros pre-rumble
        fVec30[0] = fTemp81;
        fRec72[0] = -((fRec72[1] * (1.0f - fTemp80) - (fTemp81 + fVec30[1])) / (fTemp80 + 1.0f));
        fRec71[0] = fRec72[0] - fConst81 * (fConst80 * fRec71[2] + fConst78 * fRec71[1]);
        fRec70[0] = fConst81 * (fRec71[2] + fRec71[0] + 2.0f * fRec71[1]) - fConst49 * (fConst47 * fRec70[2] + fConst45 * fRec70[1]);
        
        float fTemp82 = fRec70[2] + (fRec70[0] - 2.0f * fRec70[1]); // Pegada seca del Kick
        m_rawPunch[i0] = fTemp82;

        fRec69[0] = fConst60 * fTemp82 - fConst12 * (fConst10 * fRec69[2] + fConst8 * fRec69[1]);
        fRec68[0] = fConst21 * (fRec69[2] + (fRec69[0] - 2.0f * fRec69[1])) - fConst76 * (fConst75 * fRec68[2] + fConst73 * fRec68[1]);
        float fTemp83 = fConst76 * (fRec68[2] + fRec68[0] + 2.0f * fRec68[1]); // Excitación FDN

        // 4. Rumble FDN (Reverb de 4 canales disipativa Hadamard con Compresor en la realimentación)
        fRec78[0] = -(fConst85 * (fConst84 * fRec78[1] - (fRec67[(IOTA0 - 702) & 1023] + fRec67[(IOTA0 - 703) & 1023])));
        fRec79[0] = -(fConst85 * (fConst84 * fRec79[1] - (fRec66[(IOTA0 - 594) & 1023] + fRec66[(IOTA0 - 595) & 1023])));
        fRec80[0] = -(fConst85 * (fConst84 * fRec80[1] - (fRec65[(IOTA0 - 462) & 511] + fRec65[(IOTA0 - 463) & 511])));
        fRec81[0] = -(fConst85 * (fConst84 * fRec81[1] - (fRec64[(IOTA0 - 348) & 511] + fRec64[(IOTA0 - 349) & 511])));

        // Seguidor de envolvente del Rumble FDN
        float sumAbs = std::abs(fRec78[0]) + std::abs(fRec79[0]) + std::abs(fRec80[0]) + std::abs(fRec81[0]);
        m_rumbleEnv = 0.999f * m_rumbleEnv + 0.001f * sumAbs;

        // Compresor/limitador suave de realimentación (para evitar distorsión no-lineal por tanh)
        float rumbleGain = 1.0f;
        float limitThresh = 0.35f; // Umbral de compresión
        if (m_rumbleEnv > limitThresh) {
            rumbleGain = limitThresh / m_rumbleEnv;
        }

        // Aplicar ganancia del compresor a las señales z-1 del bucle en lugar de saturarlas
        float fTemp84 = fRec78[0] * rumbleGain;
        float fTemp85 = fRec79[0] * rumbleGain;
        float fTemp86 = fRec80[0] * rumbleGain;
        float fTemp87 = fRec81[0] * rumbleGain;
        
        float fTemp88 = fTemp87 + fTemp86;
        fRec64[IOTA0 & 511] = 0.75f * (0.5f * (fTemp88 + fTemp85 + fTemp84) + fTemp83);
        fRec65[IOTA0 & 511] = 0.75f * (fTemp83 + 0.5f * (fTemp87 + fTemp85 - (fTemp86 + fTemp84)));
        fRec66[IOTA0 & 1023] = 0.75f * (fTemp83 + 0.5f * (fTemp88 - (fTemp85 + fTemp84)));
        fRec67[IOTA0 & 1023] = 0.75f * (fTemp83 + 0.5f * (fTemp87 + fTemp84 - (fTemp86 + fTemp85)));
        
        // 5. DC Blocker
        float fTemp89 = fRec64[IOTA0 & 511] + fRec65[IOTA0 & 511] + fRec66[IOTA0 & 1023] + fRec67[IOTA0 & 1023] - 0.5f * fRec62[1];
        fVec31[IOTA0 & 255] = fTemp89;
        fRec62[0] = fVec31[(IOTA0 - 130) & 255];
        
        float fRec63 = 0.5f * fTemp89;
        float fTemp90 = fRec63 + fRec62[1] - 0.5f * fRec60[1];
        fVec32[IOTA0 & 255] = fTemp90;
        fRec60[0] = fVec32[(IOTA0 - 190) & 255];
        
        float fRec61 = 0.5f * fTemp90; // Rumble húmedo de salida

        // 6. Mezcla final estéreo
        float kick_out = vol * (fSlow314 * fTemp82 + fSlow313 * (fRec61 + fRec60[1]));

        outputBufferL[i0] += kick_out;
        outputBufferR[i0] += kick_out;

        // Actualizar estados
        iVec0[1] = iVec0[0];
        iVec29[1] = iVec29[0];
        iRec76[1] = iRec76[0];
        fRec77[1] = fRec77[0];
        
        fRec73[1] = fRec73[0];
        fRec72[1] = fRec72[0];
        fVec30[1] = fVec30[0];
        
        fRec71[2] = fRec71[1];
        fRec71[1] = fRec71[0];
        fRec70[2] = fRec70[1];
        fRec70[1] = fRec70[0];
        fRec69[2] = fRec69[1];
        fRec69[1] = fRec69[0];
        fRec68[2] = fRec68[1];
        fRec68[1] = fRec68[0];
        
        fRec78[1] = fRec78[0];
        fRec79[1] = fRec79[0];
        fRec80[1] = fRec80[0];
        fRec81[1] = fRec81[0];
        
        fRec62[1] = fRec62[0];
        fRec60[1] = fRec60[0];

        IOTA0 = IOTA0 + 1;
    }
}

// ---- v2: Despacho de parámetros por ID hash (sin strings en RT) ----
void KickVoice::setParameterById(uint32_t paramId, float value) {
    // IDs pre-calculados en compilación via bazz::paramHash()
    constexpr uint32_t ID_VOL         = bazz::paramHash("/kick/vol");
    constexpr uint32_t ID_ACCENT      = bazz::paramHash("/kick/accent");
    constexpr uint32_t ID_TUNE        = bazz::paramHash("/kick/tune");
    constexpr uint32_t ID_DEC         = bazz::paramHash("/kick/dec");
    constexpr uint32_t ID_MIX         = bazz::paramHash("/kick/mix");
    constexpr uint32_t ID_NOTA        = bazz::paramHash("/kick/nota");
    constexpr uint32_t ID_RELOJ       = bazz::paramHash("/kick/reloj");
    constexpr uint32_t ID_SWING       = bazz::paramHash("/kick/swing");
    constexpr uint32_t ID_SWEEP       = bazz::paramHash("/kick/sweep");
    constexpr uint32_t ID_COMP_FMAX   = bazz::paramHash("/kick/comp_fmax");
    constexpr uint32_t ID_COMP_FMIN   = bazz::paramHash("/kick/comp_fmin");
    constexpr uint32_t ID_COMP_RATIO  = bazz::paramHash("/kick/comp_ratio");
    constexpr uint32_t ID_COMP_THRESH = bazz::paramHash("/kick/comp_thresh");
    constexpr uint32_t ID_COMP_DRIVE  = bazz::paramHash("/kick/comp_drive");

    switch (paramId) {
        case ID_VOL:         m_volume.store(value); break;
        case ID_ACCENT:      m_accent.store(value); break;
        case ID_TUNE:        m_tune.store(value); break;
        case ID_DEC:         m_decay.store(value); break;
        case ID_MIX:         m_mixRumble.store(value); break;
        case ID_NOTA:        m_note.store(value); break;
        case ID_RELOJ:       m_clockMult.store(value); break;
        case ID_SWING:       m_swing.store(value); break;
        case ID_SWEEP:       m_sweep.store(value); break;
        case ID_COMP_FMAX:   m_compFMax.store(value); break;
        case ID_COMP_FMIN:   m_compFMin.store(value); break;
        case ID_COMP_RATIO:  m_compRatio.store(value); break;
        case ID_COMP_THRESH: m_compThresh.store(value); break;
        case ID_COMP_DRIVE:  m_compDrive.store(value); break;
        default: break; // Parámetro no reconocido — ignorar silenciosamente
    }
}

// ---- v2: Serialización de estado ----
int KickVoice::getState(float* buffer, int maxParams) const {
    const auto& desc = getDescriptor();
    int count = std::min(maxParams, desc.numParams);

    // Orden fijo siguiendo el array params[] del descriptor
    if (count > 0)  buffer[0]  = m_volume.load();
    if (count > 1)  buffer[1]  = m_accent.load();
    if (count > 2)  buffer[2]  = m_tune.load();
    if (count > 3)  buffer[3]  = m_decay.load();
    if (count > 4)  buffer[4]  = m_mixRumble.load();
    if (count > 5)  buffer[5]  = m_note.load();
    if (count > 6)  buffer[6]  = m_clockMult.load();
    if (count > 7)  buffer[7]  = m_swing.load();
    if (count > 8)  buffer[8]  = m_sweep.load();
    if (count > 9)  buffer[9]  = m_compFMax.load();
    if (count > 10) buffer[10] = m_compFMin.load();
    if (count > 11) buffer[11] = m_compRatio.load();
    if (count > 12) buffer[12] = m_compThresh.load();
    if (count > 13) buffer[13] = m_compDrive.load();

    return count;
}

void KickVoice::setState(const float* buffer, int numParams) {
    if (numParams > 0)  m_volume.store(buffer[0]);
    if (numParams > 1)  m_accent.store(buffer[1]);
    if (numParams > 2)  m_tune.store(buffer[2]);
    if (numParams > 3)  m_decay.store(buffer[3]);
    if (numParams > 4)  m_mixRumble.store(buffer[4]);
    if (numParams > 5)  m_note.store(buffer[5]);
    if (numParams > 6)  m_clockMult.store(buffer[6]);
    if (numParams > 7)  m_swing.store(buffer[7]);
    if (numParams > 8)  m_sweep.store(buffer[8]);
    if (numParams > 9)  m_compFMax.store(buffer[9]);
    if (numParams > 10) m_compFMin.store(buffer[10]);
    if (numParams > 11) m_compRatio.store(buffer[11]);
    if (numParams > 12) m_compThresh.store(buffer[12]);
    if (numParams > 13) m_compDrive.store(buffer[13]);
}
