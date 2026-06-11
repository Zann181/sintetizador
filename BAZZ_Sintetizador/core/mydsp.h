#pragma once
#include "FaustDefs.h"
#include "IInstrumentVoice.h"
#include "VoiceFactory.h"
#include "../sequencer/Clock.h"
#include "../sequencer/Sequencer.h"
#include "AudioMixer.h"
#include <vector>
#include <memory>
#include <atomic>

class mydsp : public dsp {
public:
    // Sincronizaciones públicas requeridas por app/main.cpp y RtAudioBackend
    std::atomic<uint64_t> m_lastStep0TimeMs{0};
    std::atomic<uint64_t> m_lastBeatTimeMs{0};
    std::atomic<int> m_lastBeatStep{-1};
    std::atomic<bool> m_pendingReset{false};

    // Arrays de variables miembro mapeados por buildUserInterface
    FAUSTFLOAT fCheckbox[96];
    FAUSTFLOAT fHslider[128];

private:
    double m_sampleRate = 44100.0;
    
    // Módulos internos de la nueva arquitectura
    bazz::VoiceFactory m_factory;
    std::vector<std::shared_ptr<IInstrumentVoice>> m_voices;
    std::array<Clock, 6> m_clocks;
    Clock m_masterClock;
    Sequencer m_sequencer;
    AudioMixer m_mixer;
    
    // Estados de la modulación patch-bay cruzada
    float m_rec83Resonator[3] = {0.0f};
    float m_vec6PsycheRaw[256] = {0.0f};
    int m_iota0 = 0;

    // Historial para detección de cambios en sliders y checkboxes
    std::array<float, 80> m_prevHsliders;
    std::array<bool, 96> m_prevCheckboxes;

    void updateParameters();
    float getVoiceParamValue(int voiceIdx, const std::string& suffix, float defaultVal) const;

public:
    mydsp();
    ~mydsp() override = default;

    int getNumInputs() override { return 0; }
    int getNumOutputs() override { return 2; }
    void init(int sample_rate) override;
    void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override;
    void buildUserInterface(UI* ui_interface) override;

    // Métodos de sincronización del secuenciador
    int getCurrentStep() override;
    uint64_t getLastStep0TimeMs() override { return m_lastStep0TimeMs.load(); }
    uint64_t getLastBeatTimeMs() override { return m_lastBeatTimeMs.load(); }
    int getLastBeatStep() override { return m_lastBeatStep.load(); }
    void resetSequencer() override {
        m_pendingReset.store(true, std::memory_order_release);
    }
};
