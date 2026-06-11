#pragma once
#include "../core/IInstrumentVoice.h"
#include "../core/InstrumentDescriptor.h"
#include <atomic>
#include <cmath>
#include <algorithm>
#include <array>

// Tabla de senos global compartida para emular la tabla de Faust
struct SineTable {
    std::array<float, 65536> table;
    SineTable() {
        for (int i = 0; i < 65536; ++i) {
            table[i] = std::sin(i * 2.0f * 3.141592653589793f / 65536.0f);
        }
    }
    inline float lookup(float phase) const {
        float p = phase - std::floor(phase);
        int idx = std::max(0, std::min(static_cast<int>(p * 65536.0f), 65535));
        return table[idx];
    }
};

static const SineTable g_sineTable;

// ============================================================================
// Descriptor estático del Bombo TR-808
// Declara todos los parámetros del instrumento para introspección
// ============================================================================
namespace kick_params {
    static constexpr bazz::ParamInfo params[] = {
        BAZZ_PARAM("/kick/vol",         "Volumen",            "Sintesis",  0.0f,    1.0f,   0.85f,  0.01f, Slider),
        BAZZ_PARAM("/kick/accent",      "Accent",             "Sintesis",  0.0f,    1.0f,   0.5f,   0.01f, Knob),
        BAZZ_PARAM("/kick/tune",        "Afinación",          "Sintesis", -12.0f,  12.0f,   0.0f,   1.0f,  Knob),
        BAZZ_PARAM("/kick/dec",         "Decaimiento",        "Sintesis",  0.02f,   1.0f,   0.18f,  0.01f, Knob),
        BAZZ_PARAM("/kick/mix",         "Mix Rumble",         "Sintesis",  0.0f,    1.0f,   0.45f,  0.01f, Knob),
        BAZZ_PARAM("/kick/nota",        "Nota",               "Sintesis", 36.0f,   47.0f,  36.0f,   1.0f,  Menu),
        BAZZ_PARAM("/kick/reloj",       "Reloj",              "Sintesis",  0.25f,   4.0f,   1.0f,   0.25f, Menu),
        BAZZ_PARAM("/kick/swing",       "Swing",              "Sintesis",  0.0f,   75.0f,   0.0f,   1.0f,  Knob),
        BAZZ_PARAM("/kick/sweep",       "Transitorio",        "Sintesis",  0.0f,  300.0f, 150.0f,   1.0f,  Knob),
        BAZZ_PARAM("/kick/comp_fmax",   "Filtro Frec Max",    "Dinamica", 1000.0f, 8000.0f, 2500.0f, 10.0f, Knob),
        BAZZ_PARAM("/kick/comp_fmin",   "Filtro Frec Min",    "Dinamica",  100.0f, 2000.0f,  750.0f, 10.0f, Knob),
        BAZZ_PARAM("/kick/comp_ratio",  "Lim Ratio",          "Dinamica",    1.0f,   20.0f,    8.0f,  0.1f, Knob),
        BAZZ_PARAM("/kick/comp_thresh", "Lim Umbral",         "Dinamica",    0.01f,   1.0f,   0.4f,  0.01f, Knob),
        BAZZ_PARAM("/kick/comp_drive",  "Saturación Pegada",  "Dinamica",    0.5f,   8.0f,   3.5f,  0.1f, Knob),
    };

    static constexpr bazz::InstrumentDescriptor descriptor = {
        "kick_808",                             // typeName
        "Bombo TR-808",                         // displayName
        "Bombo analógico con pitch sweep, FDN rumble y compresor de pegada", // description
        bazz::OutputType::Mono,                 // outputType
        params,                                 // params
        sizeof(params) / sizeof(params[0]),      // numParams
        0                                       // defaultChannel
    };
}

class KickVoice : public IInstrumentVoice {
private:
    double m_sampleRate = 44100.0;

    // Constantes de calibración de audio
    float fConst0;
    float fConst5;
    float fConst8;
    float fConst10;
    float fConst12;
    float fConst14;
    float fConst15;
    float fConst16;
    float fConst18;
    float fConst19;
    float fConst20;
    float fConst21;
    float fConst35;
    float fConst36;
    
    float fConst43;
    float fConst44;
    float fConst45;
    float fConst47;
    float fConst48;
    float fConst49;
    float fConst60;
    float fConst61;
    
    float fConst72;
    float fConst73;
    float fConst75;
    float fConst76;
    float fConst77;
    float fConst78;
    float fConst80;
    float fConst81;
    
    float fConst82;
    float fConst83;
    float fConst84;
    float fConst85;

    // Parámetros de control
    std::atomic<float> m_volume{0.85f};
    std::atomic<float> m_accent{0.5f};
    std::atomic<float> m_tune{0.0f};
    std::atomic<float> m_decay{0.18f};
    std::atomic<float> m_mixRumble{0.45f};
    std::atomic<float> m_note{36.0f};
    std::atomic<float> m_clockMult{1.0f};
    std::atomic<float> m_swing{0.0f};
    std::atomic<float> m_sweep{150.0f};

    // Parámetros de la dinámica (compresor de pegada)
    std::atomic<float> m_compFMax{2500.0f};
    std::atomic<float> m_compFMin{750.0f};
    std::atomic<float> m_compRatio{8.0f};
    std::atomic<float> m_compThresh{0.4f};
    std::atomic<float> m_compDrive{3.5f};

    // Variables de estado del DSP para el Kick
    int iVec0[2];
    int iVec29[2];
    int iRec76[2];
    float fRec77[2]; // Fase del oscilador
    
    // Compresor/saturador
    float fRec73[2]; // Seguidor
    float fRec72[2]; // LPF
    float fVec30[2]; // Retraso
    
    // Filtros de realimentación resonantes
    float fRec71[3];
    float fRec70[3];
    float fRec69[3];
    float fRec68[3];

    // Rumble FDN
    std::array<float, 512> fRec64;
    std::array<float, 512> fRec65;
    std::array<float, 1024> fRec66;
    std::array<float, 1024> fRec67;
    float fRec78[2];
    float fRec79[2];
    float fRec80[2];
    float fRec81[2];

    // DC Blocker de salida del Rumble FDN
    std::array<float, 256> fVec31;
    std::array<float, 256> fVec32;
    float fRec62[2];
    float fRec60[2];

    int IOTA0 = 0; // Índice circular
    float m_rumbleEnv = 0.0f; // Envolvente para compresor de realimentación (rumble)

    // Disparadores
    std::atomic<float> m_triggerVelocity{0.0f};
    std::atomic<bool> m_triggered{false};
    float m_currentVelocity = 1.0f;

    inline float power2(float value) { return value * value; }
    
    // Buffer para exponer la pegada del Kick (por si acaso se requiere compatibilidad)
    float m_rawPunch[4096] = {0.0f};

public:
    KickVoice() = default;
    ~KickVoice() override = default;

    void initialize(double sampleRate) override;
    void clearState() override;
    void trigger(float velocity) override;
    void processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer = nullptr) override;
    void setParameter(const std::string& name, float value) override;

    // ---- v2: Introspección y serialización ----
    const bazz::InstrumentDescriptor& getDescriptor() const override {
        return kick_params::descriptor;
    }

    void setParameterById(uint32_t paramId, float value) override;
    int getState(float* buffer, int maxParams) const override;
    void setState(const float* buffer, int numParams) override;

    const float* getRawPunch() const { return m_rawPunch; }
};
