#include "HiHatVoice.h"
#include <cmath>
#include <algorithm>

void HiHatVoice::initialize(double sampleRate) {
    m_sampleRate = sampleRate;

    fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(m_sampleRate)));
    fConst18 = 1.0f / fConst0;
    fConst61 = 3.1415927f / fConst0;
    fConst62 = 0.25f * fConst0;
    fConst19 = 0.5f * fConst0;

    clearState();
}

void HiHatVoice::clearState() {
    std::fill(std::begin(iVec0), std::end(iVec0), 0);
    std::fill(std::begin(iVec25), std::end(iVec25), 0);
    std::fill(std::begin(iRec51), std::end(iRec51), 0);
    std::fill(std::begin(fRec42), std::end(fRec42), 0.0f);

    std::fill(std::begin(fRec43), std::end(fRec43), 0.0f);
    std::fill(std::begin(fVec12), std::end(fVec12), 0.0f);
    std::fill(std::begin(fRec44), std::end(fRec44), 0.0f);
    std::fill(std::begin(fVec14), std::end(fVec14), 0.0f);
    std::fill(std::begin(fRec45), std::end(fRec45), 0.0f);
    std::fill(std::begin(fVec16), std::end(fVec16), 0.0f);
    std::fill(std::begin(fRec46), std::end(fRec46), 0.0f);
    std::fill(std::begin(fVec18), std::end(fVec18), 0.0f);
    std::fill(std::begin(fRec47), std::end(fRec47), 0.0f);
    std::fill(std::begin(fVec20), std::end(fVec20), 0.0f);
    std::fill(std::begin(fRec48), std::end(fRec48), 0.0f);
    std::fill(std::begin(fVec22), std::end(fVec22), 0.0f);

    fVec13.fill(0.0f);
    fVec15.fill(0.0f);
    fVec17.fill(0.0f);
    fVec19.fill(0.0f);
    fVec21.fill(0.0f);
    fVec23.fill(0.0f);

    IOTA0 = 0;
    iRec39 = 0;

    m_triggered.store(false);
    m_triggerVelocity.store(0.0f);
    m_currentVelocity = 1.0f;
}

void HiHatVoice::trigger(float velocity) {
    m_triggerVelocity.store(velocity);
    m_triggered.store(true);
}

void HiHatVoice::setParameter(const std::string& name, float value) {
    if (name == "/hat/vol") m_volume.store(value);
    else if (name == "/hat/accent") m_accent.store(value);
    else if (name == "/hat/tune") m_tune.store(value);
    else if (name == "/hat/ataque") m_attack.store(value);
    else if (name == "/hat/dec") m_decay.store(value);
    else if (name == "/hat/cutoff") m_cutoff.store(value);
    else if (name == "/hat/mix") m_mix.store(value);
    else if (name == "/hat/nota") m_note.store(value);
    else if (name == "/hat/reloj") m_clockMult.store(value);
    else if (name == "/hat/drive") m_drive.store(value);
    else if (name == "/hat/swing") m_swing.store(value);
}

void HiHatVoice::processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer) {
    float vol = m_volume.load();
    float tune = m_tune.load();
    float attack = m_attack.load();
    float decay = m_decay.load();
    float cutoff = m_cutoff.load();
    float mix = m_mix.load();
    float note = m_note.load();
    float drive = m_drive.load();

    // Filtro Paso Alto de Salida (IIR de 2do orden)
    float fSlow118 = std::tan(fConst61 * cutoff);
    float fSlow119 = power2(fSlow118);
    float fSlow120 = 2.0f * (1.0f - 1.0f / fSlow119);
    float fSlow121 = 1.0f / fSlow118;
    float fSlow122 = (fSlow121 - 1.4142135f) / fSlow118 + 1.0f;
    float fSlow123 = (fSlow121 + 1.4142135f) / fSlow118 + 1.0f;
    float fSlow124 = 1.0f / fSlow123;
    float fSlow225 = 2.0f * (vol / (fSlow119 * fSlow123));

    // Coeficientes del Metal Cluster (6 osciladores cuadrados en serie de delays)
    float fSlow125 = mix;
    float fSlow126 = 4.656613e-10f * fSlow125;
    float fSlow127 = std::pow(2.0f, 0.083333336f * (note - 69.0f)) * std::pow(2.0f, 0.083333336f * tune);
    
    // Frecuencias base de los 6 osciladores del cluster
    float fSlow128 = std::max<float>(19306.982f * fSlow127, 23.44895f);
    float fSlow129 = std::max<float>(20.0f, std::fabs(fSlow128));
    float fSlow130 = fConst18 * fSlow129;
    float fSlow131 = fConst62 / fSlow129;
    float fSlow132 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow128));
    int iSlow133 = static_cast<int>(fSlow132);
    float fSlow134 = std::floor(fSlow132);
    float fSlow135 = fSlow134 + (1.0f - fSlow132);

    float fSlow136 = std::max<float>(15940.032f * fSlow127, 23.44895f);
    float fSlow137 = std::max<float>(20.0f, std::fabs(fSlow136));
    float fSlow138 = fConst18 * fSlow137;
    float fSlow139 = fConst62 / fSlow137;
    float fSlow140 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow136));
    int iSlow141 = static_cast<int>(fSlow140);
    float fSlow142 = std::floor(fSlow140);
    float fSlow143 = fSlow142 + (1.0f - fSlow140);

    float fSlow144 = std::max<float>(12784.989f * fSlow127, 23.44895f);
    float fSlow145 = std::max<float>(20.0f, std::fabs(fSlow144));
    float fSlow146 = fConst18 * fSlow145;
    float fSlow147 = fConst62 / fSlow145;
    float fSlow148 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow144));
    int iSlow149 = static_cast<int>(fSlow148);
    float fSlow150 = std::floor(fSlow148);
    float fSlow151 = fSlow150 + (1.0f - fSlow148);

    float fSlow152 = std::max<float>(9794.762f * fSlow127, 23.44895f);
    float fSlow153 = std::max<float>(20.0f, std::fabs(fSlow152));
    float fSlow154 = fConst18 * fSlow153;
    float fSlow155 = fConst62 / fSlow153;
    float fSlow156 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow152));
    int iSlow157 = static_cast<int>(fSlow156);
    float fSlow158 = std::floor(fSlow156);
    float fSlow159 = fSlow158 + (1.0f - fSlow156);

    float fSlow160 = std::max<float>(7016.4395f * fSlow127, 23.44895f);
    float fSlow161 = std::max<float>(20.0f, std::fabs(fSlow160));
    float fSlow162 = fConst18 * fSlow161;
    float fSlow163 = fConst62 / fSlow161;
    float fSlow164 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow160));
    int iSlow165 = static_cast<int>(fSlow164);
    float fSlow166 = std::floor(fSlow164);
    float fSlow167 = fSlow166 + (1.0f - fSlow164);

    float fSlow168 = std::max<float>(4709.02f * fSlow127, 23.44895f);
    float fSlow169 = std::max<float>(20.0f, std::fabs(fSlow168));
    float fSlow170 = fConst18 * fSlow169;
    float fSlow171 = fConst62 / fSlow169;
    float fSlow172 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow168));
    int iSlow173 = static_cast<int>(fSlow172);
    int iSlow174 = iSlow173 + 1;
    float fSlow175 = std::floor(fSlow172);
    float fSlow176 = fSlow172 - fSlow175;
    float fSlow177 = fSlow175 + (1.0f - fSlow172);

    int iSlow178 = iSlow165 + 1;
    float fSlow179 = fSlow164 - fSlow166;
    int iSlow180 = iSlow157 + 1;
    float fSlow181 = fSlow156 - fSlow158;
    int iSlow182 = iSlow149 + 1;
    float fSlow183 = fSlow148 - fSlow150;
    int iSlow184 = iSlow141 + 1;
    float fSlow185 = fSlow140 - fSlow142;
    int iSlow186 = iSlow133 + 1;
    float fSlow187 = fSlow132 - fSlow134;

    float fSlow188 = 1.0f / fSlow129;
    float fSlow189 = 1.0f / fSlow137;
    float fSlow190 = 1.0f / fSlow145;
    float fSlow191 = 1.0f / fSlow153;
    float fSlow192 = 1.0f / fSlow161;
    float fSlow193 = 1.0f / fSlow169;
    float fSlow194 = 0.15f * (1.0f - fSlow125);
    float fSlow195 = 6.5f * drive;

    // Envolvente temporal
    float fSlow222 = std::max<float>(1.0f, fConst0 * attack);
    float fSlow223 = 1.0f / fSlow222;
    float fSlow224 = 1.0f / std::max<float>(1.0f, fConst0 * decay);

    for (int i0 = 0; i0 < numSamples; ++i0) {
        iVec0[0] = 1;
        int iTemp3 = (1 - iVec0[1]);
        float fTemp9 = static_cast<float>(iVec0[1]);

        // 1. Evaluar Trigger
        int iTemp65 = 0;
        if (triggerBuffer) {
            if (triggerBuffer[i0] > 0.0f) {
                iTemp65 = 1;
                m_currentVelocity = triggerBuffer[i0];
            }
        } else {
            if (m_triggered.exchange(false)) {
                iTemp65 = 1;
                m_currentVelocity = m_triggerVelocity.load();
            }
        }

        iVec25[0] = iTemp65;
        iRec51[0] = (iRec51[1] + (iRec51[1] > 0)) * (iTemp65 <= iVec25[1]) + (iTemp65 > iVec25[1]);
        float fTemp66 = static_cast<float>(iRec51[0]);

        // 2. Generar Ruido LCG
        iRec39 = 1103515245 * iRec39 + 12345;
        float fTemp37 = static_cast<float>(iRec39);

        // 3. Procesar las fases de los 6 osciladores del cluster
        float fTemp39 = ((iTemp3) ? 0.0f : fSlow130 + fRec43[1]);
        fRec43[0] = fTemp39 - std::floor(fTemp39);
        float fTemp40 = power2(2.0f * fRec43[0] - 1.0f);
        fVec12[0] = fTemp40;
        float fTemp41 = fTemp40 - fVec12[1];
        float fTemp42 = fSlow131 * fTemp9 * fTemp41;
        fVec13[IOTA0 & 127] = fTemp42;

        float fTemp43 = ((iTemp3) ? 0.0f : fSlow138 + fRec44[1]);
        fRec44[0] = fTemp43 - std::floor(fTemp43);
        float fTemp44 = power2(2.0f * fRec44[0] - 1.0f);
        fVec14[0] = fTemp44;
        float fTemp45 = fTemp44 - fVec14[1];
        float fTemp46 = fSlow139 * fTemp9 * fTemp45;
        fVec15[IOTA0 & 127] = fTemp46;

        float fTemp47 = ((iTemp3) ? 0.0f : fSlow146 + fRec45[1]);
        fRec45[0] = fTemp47 - std::floor(fTemp47);
        float fTemp48 = power2(2.0f * fRec45[0] - 1.0f);
        fVec16[0] = fTemp48;
        float fTemp49 = fTemp48 - fVec16[1];
        float fTemp50 = fSlow147 * fTemp9 * fTemp49;
        fVec17[IOTA0 & 127] = fTemp50;

        float fTemp51 = ((iTemp3) ? 0.0f : fSlow154 + fRec46[1]);
        fRec46[0] = fTemp51 - std::floor(fTemp51);
        float fTemp52 = power2(2.0f * fRec46[0] - 1.0f);
        fVec18[0] = fTemp52;
        float fTemp53 = fTemp52 - fVec18[1];
        float fTemp54 = fSlow155 * fTemp9 * fTemp53;
        fVec19[IOTA0 & 255] = fTemp54;

        float fTemp55 = ((iTemp3) ? 0.0f : fSlow162 + fRec47[1]);
        fRec47[0] = fTemp55 - std::floor(fTemp55);
        float fTemp56 = power2(2.0f * fRec47[0] - 1.0f);
        fVec20[0] = fTemp56;
        float fTemp57 = fTemp56 - fVec20[1];
        float fTemp58 = fSlow163 * fTemp9 * fTemp57;
        fVec21[IOTA0 & 255] = fTemp58;

        float fTemp59 = ((iTemp3) ? 0.0f : fSlow170 + fRec48[1]);
        fRec48[0] = fTemp59 - std::floor(fTemp59);
        float fTemp60 = power2(2.0f * fRec48[0] - 1.0f);
        fVec22[0] = fTemp60;
        float fTemp61 = fTemp60 - fVec22[1];
        float fTemp62 = fSlow171 * fTemp9 * fTemp61;
        fVec23[IOTA0 & 511] = fTemp62;

        // Suma del cluster metálico con atenuaciones y realimentaciones
        float fTemp63 = fSlow194 * (fConst62 * fTemp9 * (fSlow193 * fTemp61 + fSlow192 * fTemp57 + fSlow191 * fTemp53 + fSlow190 * fTemp49 + fSlow189 * fTemp45 + fSlow188 * fTemp41) - (fSlow187 * fVec13[(IOTA0 - iSlow186) & 127] + fSlow185 * fVec15[(IOTA0 - iSlow184) & 127] + fSlow183 * fVec17[(IOTA0 - iSlow182) & 127] + fSlow181 * fVec19[(IOTA0 - iSlow180) & 255] + fSlow179 * fVec21[(IOTA0 - iSlow178) & 255] + fSlow177 * fVec23[(IOTA0 - iSlow173) & 511] + fSlow176 * fVec23[(IOTA0 - iSlow174) & 511] + fSlow167 * fVec21[(IOTA0 - iSlow165) & 255] + fSlow159 * fVec19[(IOTA0 - iSlow157) & 255] + fSlow151 * fVec17[(IOTA0 - iSlow149) & 127] + fSlow143 * fVec15[(IOTA0 - iSlow141) & 127] + fSlow135 * fVec13[(IOTA0 - iSlow133) & 127])) + fSlow126 * fTemp37;

        // Envolvente de Platillos
        float env_val = std::max<float>(0.0f, std::min<float>(fSlow223 * fTemp66, fSlow224 * (fSlow222 - fTemp66) + 1.0f)) * m_currentVelocity;

        // Mezcla y Saturación no lineal
        float hat_raw = fTemp63 * env_val / (fSlow195 * std::fabs(fTemp63) + 1.0f);

        // Filtro paso alto de salida
        fRec42[0] = hat_raw - fSlow124 * (fSlow122 * fRec42[2] + fSlow120 * fRec42[1]);
        
        float hat_out = fSlow225 * (fRec42[2] + (fRec42[0] - 2.0f * fRec42[1]));

        // Sumar al buffer estéreo de salida
        outputBufferL[i0] += hat_out;
        outputBufferR[i0] += hat_out;

        // Actualizar estados
        iVec0[1] = iVec0[0];
        iVec25[1] = iVec25[0];
        iRec51[1] = iRec51[0];
        fRec42[2] = fRec42[1];
        fRec42[1] = fRec42[0];

        fRec43[1] = fRec43[0];
        fVec12[1] = fVec12[0];
        fRec44[1] = fRec44[0];
        fVec14[1] = fVec14[0];
        fRec45[1] = fRec45[0];
        fVec16[1] = fVec16[0];
        fRec46[1] = fRec46[0];
        fVec18[1] = fVec18[0];
        fRec47[1] = fRec47[0];
        fVec20[1] = fVec20[0];
        fRec48[1] = fRec48[0];
        fVec22[1] = fVec22[0];

        IOTA0 = IOTA0 + 1;
    }
}

// ---- v2: Despacho de parámetros por ID hash (sin strings en RT) ----
void HiHatVoice::setParameterById(uint32_t paramId, float value) {
    constexpr uint32_t ID_VOL     = bazz::paramHash("/hat/vol");
    constexpr uint32_t ID_ACCENT  = bazz::paramHash("/hat/accent");
    constexpr uint32_t ID_TUNE    = bazz::paramHash("/hat/tune");
    constexpr uint32_t ID_ATAQUE  = bazz::paramHash("/hat/ataque");
    constexpr uint32_t ID_DEC     = bazz::paramHash("/hat/dec");
    constexpr uint32_t ID_CUTOFF  = bazz::paramHash("/hat/cutoff");
    constexpr uint32_t ID_MIX     = bazz::paramHash("/hat/mix");
    constexpr uint32_t ID_NOTA    = bazz::paramHash("/hat/nota");
    constexpr uint32_t ID_RELOJ   = bazz::paramHash("/hat/reloj");
    constexpr uint32_t ID_DRIVE   = bazz::paramHash("/hat/drive");
    constexpr uint32_t ID_SWING   = bazz::paramHash("/hat/swing");

    switch (paramId) {
        case ID_VOL:     m_volume.store(value); break;
        case ID_ACCENT:  m_accent.store(value); break;
        case ID_TUNE:    m_tune.store(value); break;
        case ID_ATAQUE:  m_attack.store(value); break;
        case ID_DEC:     m_decay.store(value); break;
        case ID_CUTOFF:  m_cutoff.store(value); break;
        case ID_MIX:     m_mix.store(value); break;
        case ID_NOTA:    m_note.store(value); break;
        case ID_RELOJ:   m_clockMult.store(value); break;
        case ID_DRIVE:   m_drive.store(value); break;
        case ID_SWING:   m_swing.store(value); break;
        default: break;
    }
}

// ---- v2: Serialización de estado ----
int HiHatVoice::getState(float* buffer, int maxParams) const {
    const auto& desc = getDescriptor();
    int count = std::min(maxParams, desc.numParams);

    if (count > 0)  buffer[0]  = m_volume.load();
    if (count > 1)  buffer[1]  = m_accent.load();
    if (count > 2)  buffer[2]  = m_tune.load();
    if (count > 3)  buffer[3]  = m_attack.load();
    if (count > 4)  buffer[4]  = m_decay.load();
    if (count > 5)  buffer[5]  = m_cutoff.load();
    if (count > 6)  buffer[6]  = m_mix.load();
    if (count > 7)  buffer[7]  = m_note.load();
    if (count > 8)  buffer[8]  = m_clockMult.load();
    if (count > 9)  buffer[9]  = m_drive.load();
    if (count > 10) buffer[10] = m_swing.load();

    return count;
}

void HiHatVoice::setState(const float* buffer, int numParams) {
    if (numParams > 0)  m_volume.store(buffer[0]);
    if (numParams > 1)  m_accent.store(buffer[1]);
    if (numParams > 2)  m_tune.store(buffer[2]);
    if (numParams > 3)  m_attack.store(buffer[3]);
    if (numParams > 4)  m_decay.store(buffer[4]);
    if (numParams > 5)  m_cutoff.store(buffer[5]);
    if (numParams > 6)  m_mix.store(buffer[6]);
    if (numParams > 7)  m_note.store(buffer[7]);
    if (numParams > 8)  m_clockMult.store(buffer[8]);
    if (numParams > 9)  m_drive.store(buffer[9]);
    if (numParams > 10) m_swing.store(buffer[10]);
}
