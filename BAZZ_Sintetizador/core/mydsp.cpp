#include "mydsp.h"
#include "InstrumentDescriptor.h"
#include "../voices/KickVoice.h"
#include "../voices/FunkTribuKickVoice.h"
#include "../voices/SnareVoice.h"
#include "../voices/HiHatVoice.h"
#include "../voices/BassVoice.h"
#include "../voices/PsycheVoice.h"
#include "../voices/SiringeVoice.h"
#include <chrono>
#include <iostream>

static const int kSequencerCheckboxOffsets[6] = { 80, 64, 48, 32, 0, 16 };

float mydsp::getVoiceParamValue(int voiceIdx, const std::string& suffix, float defaultVal) const {
    if (voiceIdx < 0 || voiceIdx >= static_cast<int>(m_voices.size()) || !m_voices[voiceIdx]) {
        return defaultVal;
    }
    const auto& desc = m_voices[voiceIdx]->getDescriptor();
    for (int p = 0; p < desc.numParams; ++p) {
        std::string path(desc.params[p].oscPath);
        if (path.length() >= suffix.length() && path.compare(path.length() - suffix.length(), suffix.length(), suffix) == 0) {
            return fHslider[voiceIdx * 20 + p];
        }
    }
    return defaultVal;
}

mydsp::mydsp() {
    // Inicializar arrays de parámetros a cero
    std::fill(std::begin(fCheckbox), std::end(fCheckbox), 0.0f);
    std::fill(std::begin(fHslider), std::end(fHslider), 0.0f);
    m_prevHsliders.fill(-999.0f);
    m_prevCheckboxes.fill(false);

    // Registrar los tipos de voz en la factory para modularidad
    m_factory.registerVoice<KickVoice>();
    m_factory.registerVoice<FunkTribuKickVoice>();
    m_factory.registerVoice<SnareVoice>();
    m_factory.registerVoice<HiHatVoice>();
    m_factory.registerVoice<BassVoice>();
    m_factory.registerVoice<PsycheVoice>();
    m_factory.registerVoice<SiringeVoice>();

    // Instanciar las 6 voces de síntesis utilizando el VoiceFactory
    m_voices.push_back(m_factory.create("kick_tribal"));
    m_voices.push_back(m_factory.create("snare_808"));
    m_voices.push_back(m_factory.create("hat_808"));
    m_voices.push_back(m_factory.create("bass_wg"));
    m_voices.push_back(m_factory.create("psyche_fm"));
    m_voices.push_back(m_factory.create("siringe_fdn"));
}

void mydsp::init(int sample_rate) {
    m_sampleRate = sample_rate;

    // Inicializar reloj maestro y relojes locales
    m_masterClock.initialize(m_sampleRate);
    for (int i = 0; i < 6; ++i) {
        m_clocks[i].initialize(m_sampleRate);
        m_voices[i]->initialize(m_sampleRate);

        // Inicializar dinámicamente los valores predeterminados de cada parámetro
        const auto& desc = m_voices[i]->getDescriptor();
        for (int p = 0; p < desc.numParams; ++p) {
            fHslider[i * 20 + p] = desc.params[p].defaultVal;
        }
    }
    m_mixer.reset();
    std::fill(std::begin(m_rec83Resonator), std::end(m_rec83Resonator), 0.0f);
    std::fill(std::begin(m_vec6PsycheRaw), std::end(m_vec6PsycheRaw), 0.0f);
    m_iota0 = 0;

    fHslider[127] = 140.0f; // BPM Maestro
}

void mydsp::buildUserInterface(UI* ui_interface) {
    ui_interface->openVerticalBox("TR_808_ALGORITHMIC_STATION");
    
    // 0. Panel Maestro
    ui_interface->openVerticalBox("0_MASTER");
    ui_interface->declare(&fHslider[127], "osc", "/master/bpm");
    ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider[127], FAUSTFLOAT(140.0f), FAUSTFLOAT(60.0f), FAUSTFLOAT(240.0f), FAUSTFLOAT(1.0f));
    ui_interface->closeBox();

    ui_interface->openHorizontalBox("INSTRUMENTOS");

    // 1. Panel de cada instrumento por introspección
    for (int c = 0; c < 6; ++c) {
        if (c >= static_cast<int>(m_voices.size()) || !m_voices[c]) continue;
        const auto& desc = m_voices[c]->getDescriptor();

        ui_interface->declare(0, std::to_string(c + 1).c_str(), "");
        ui_interface->openVerticalBox(desc.displayName);

        // PAD del secuenciador para este instrumento
        ui_interface->openVerticalBox("PAD");
        int chOffset = kSequencerCheckboxOffsets[c];
        
        // Obtener el prefijo para los nombres de steps (ej: KICK, SNARE, HAT)
        std::string prefix = desc.typeName;
        if (prefix.rfind("kick_", 0) == 0) prefix = "KICK";
        else if (prefix.rfind("snare_", 0) == 0) prefix = "SNARE";
        else if (prefix.rfind("hat_", 0) == 0) prefix = "HAT";
        else if (prefix.rfind("bass_", 0) == 0) prefix = "BASS";
        else if (prefix.rfind("psyche_", 0) == 0) prefix = "SYN1";
        else if (prefix.rfind("siringe_", 0) == 0) prefix = "SYN2";
        else {
            // Transformar a mayúsculas como fallback
            for (auto& ch : prefix) ch = std::toupper(ch);
        }

        for (int s = 0; s < 16; ++s) {
            std::string name = prefix + "/" + (s < 10 ? "0" : "") + std::to_string(s);
            // El path OSC sigue el formato /instrumento/stepX
            std::string stepPath = "";
            if (prefix == "KICK") stepPath = "/kick/step" + std::to_string(s);
            else if (prefix == "SNARE") stepPath = "/snare/step" + std::to_string(s);
            else if (prefix == "HAT") stepPath = "/hat/step" + std::to_string(s);
            else if (prefix == "BASS") stepPath = "/bass/step" + std::to_string(s);
            else if (prefix == "SYN1") stepPath = "/syn1/step" + std::to_string(s);
            else if (prefix == "SYN2") stepPath = "/syn2/step" + std::to_string(s);
            else stepPath = "/" + std::string(desc.typeName) + "/step" + std::to_string(s);

            ui_interface->declare(&fCheckbox[chOffset + s], "osc", stepPath.c_str());
            ui_interface->addCheckButton(name.c_str(), &fCheckbox[chOffset + s]);
        }
        ui_interface->closeBox();

        // Parámetros dinámicos del descriptor
        for (int p = 0; p < desc.numParams; ++p) {
            const auto& param = desc.params[p];
            int sliderIdx = c * 20 + p;

            ui_interface->declare(&fHslider[sliderIdx], "osc", param.oscPath);
            if (param.style == bazz::ParamStyle::Knob) {
                ui_interface->declare(&fHslider[sliderIdx], "style", "knob");
            } else if (param.style == bazz::ParamStyle::Menu) {
                // Configurar el estilo de menú según corresponda
                if (std::string(param.oscPath).find("/nota") != std::string::npos) {
                    if (c == 5) {
                        ui_interface->declare(&fHslider[sliderIdx], "style", "menu{'Octava':12; 'Quinta Arriba':19; 'Doble Octava':24}");
                    } else {
                        ui_interface->declare(&fHslider[sliderIdx], "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
                    }
                } else if (std::string(param.oscPath).find("/reloj") != std::string::npos) {
                    ui_interface->declare(&fHslider[sliderIdx], "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
                }
            }

            std::string fullLabel = std::string(param.group) + "/" + param.displayName;
            ui_interface->addHorizontalSlider(fullLabel.c_str(), &fHslider[sliderIdx],
                                              FAUSTFLOAT(param.defaultVal),
                                              FAUSTFLOAT(param.minVal),
                                              FAUSTFLOAT(param.maxVal),
                                              FAUSTFLOAT(param.step));
        }

        ui_interface->closeBox();
    }

    ui_interface->closeBox();
    ui_interface->closeBox();
}

void mydsp::updateParameters() {
    // 1. Detectar actualizaciones de los checkboxes (Secuenciador)
    for (int c = 0; c < 6; ++c) {
        int offset = kSequencerCheckboxOffsets[c];
        for (int s = 0; s < 16; ++s) {
            bool val = (fCheckbox[offset + s] > 0.0f);
            if (val != m_prevCheckboxes[offset + s]) {
                m_sequencer.setStep(c, s, val);
                m_prevCheckboxes[offset + s] = val;
            }
        }
    }

    // 2. Actualizar BPM y propagarlo a los relojes
    float bpmVal = fHslider[127]; // BPM Maestro
    m_masterClock.setBpm(bpmVal);
    
    // 3. Propagar parámetros individuales de sliders a las voces dynamically
    for (int c = 0; c < 6; ++c) {
        if (c >= static_cast<int>(m_voices.size()) || !m_voices[c]) continue;
        const auto& desc = m_voices[c]->getDescriptor();
        
        for (int p = 0; p < desc.numParams; ++p) {
            const auto& param = desc.params[p];
            std::string path(param.oscPath);
            
            // Comprobación de modulación cruzada automática:
            // Si el path del parámetro se refiere a otra sección (ej. /syn1/vol en syn2),
            // copiamos el valor del slider del dueño original en lugar de su slider local.
            float value = fHslider[c * 20 + p];
            if (path.find("/kick/") == 0 && c != 0) {
                value = getVoiceParamValue(0, path.substr(5), value);
            } else if (path.find("/snare/") == 0 && c != 1) {
                value = getVoiceParamValue(1, path.substr(6), value);
            } else if (path.find("/hat/") == 0 && c != 2) {
                value = getVoiceParamValue(2, path.substr(4), value);
            } else if (path.find("/bass/") == 0 && c != 3) {
                value = getVoiceParamValue(3, path.substr(5), value);
            } else if (path.find("/syn1/") == 0 && c != 4) {
                value = getVoiceParamValue(4, path.substr(5), value);
            } else if (path.find("/syn2/") == 0 && c != 5) {
                value = getVoiceParamValue(5, path.substr(5), value);
            }
            
            m_voices[c]->setParameterById(param.id, value);
        }

        m_clocks[c].setBpm(bpmVal);
        m_clocks[c].setSwing(getVoiceParamValue(c, "/swing", 0.0f));
    }
}

void mydsp::compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
    // 1. Manejar reset de secuencia solicitado por el hilo de control
    if (m_pendingReset.exchange(false, std::memory_order_acq_rel)) {
        m_masterClock.reset();
        for (int i = 0; i < 6; ++i) {
            m_clocks[i].reset();
            m_voices[i]->clearState();
        }
    }

    // 2. Actualizar parámetros atómicamente antes de procesar el bloque de audio
    updateParameters();

    FAUSTFLOAT* outL = outputs[0];
    FAUSTFLOAT* outR = outputs[1];

    std::array<float, 6> clockMults;
    std::array<float, 6> accents;
    for (int c = 0; c < 6; ++c) {
        clockMults[c] = getVoiceParamValue(c, "/reloj", 1.0f);
        accents[c] = getVoiceParamValue(c, "/accent", 0.5f);
    }

    int offset = 0;
    while (offset < count) {
        int numSamplesToProcess = std::min(count - offset, 4096);

        // Limpiar buffers principales de mezcla a cero para esta porción
        std::fill(outL + offset, outL + offset + numSamplesToProcess, 0.0f);
        std::fill(outR + offset, outR + offset + numSamplesToProcess, 0.0f);

        // 3. Crear y limpiar trigger buffers para precisión de muestra
        float triggerBuffers[6][4096];
        for (int c = 0; c < 6; ++c) {
            std::fill(triggerBuffers[c], triggerBuffers[c] + numSamplesToProcess, 0.0f);
        }

        // 4. Evaluar relojes y rellenar trigger buffers muestra por muestra
        for (int i = 0; i < numSamplesToProcess; ++i) {
            // A. Actualizar Reloj Maestro para sincronización externa (main.cpp)
            int masterStep = 0;
            float masterTrigger = m_masterClock.processSample(1.0f, 0.0f, 0.0f, 36.0f, masterStep);
            if (masterTrigger > 0.0f) {
                uint64_t now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
                m_lastBeatTimeMs.store(now_ms);
                m_lastBeatStep.store(masterStep);
                if (masterStep == 0) {
                    m_lastStep0TimeMs.store(now_ms);
                }
            }

            // B. Evaluar relojes individuales por instrumento y llenar buffers de disparadores
            for (int c = 0; c < 6; ++c) {
                int step = 0;
                float accentGroove = getVoiceParamValue(c, "/accent", 0.5f);
                float accentMicro = getVoiceParamValue(c, "/accent_micro", 0.2f);
                float activeNote = getVoiceParamValue(c, "/nota", 36.0f);
                float triggerAmp = m_clocks[c].processSample(clockMults[c], accentGroove, accentMicro, activeNote, step);
                if (triggerAmp > 0.0f) {
                    // Obtener la velocidad/volumen del paso correspondiente en fCheckbox
                    int cbIdx = kSequencerCheckboxOffsets[c] + step;
                    float stepVel = fCheckbox[cbIdx];
                    if (stepVel > 0.0f) {
                        triggerBuffers[c][i] = triggerAmp * stepVel;
                    }
                }
            }
        }

        // 5. Ejecutar el DSP de cada voz por bloques.
        m_voices[0]->processBlock(outL + offset, outR + offset, numSamplesToProcess, triggerBuffers[0]); // Kick
        m_voices[1]->processBlock(outL + offset, outR + offset, numSamplesToProcess, triggerBuffers[1]); // Snare
        m_voices[2]->processBlock(outL + offset, outR + offset, numSamplesToProcess, triggerBuffers[2]); // HiHat
        m_voices[3]->processBlock(outL + offset, outR + offset, numSamplesToProcess, triggerBuffers[3]); // Bass
        m_voices[5]->processBlock(outL + offset, outR + offset, numSamplesToProcess, triggerBuffers[5]); // Siringe (Synth 2)

        // Ejecutar PsycheVoice (Synth 1) para que calcule su bloque de waveguide y LFO
        m_voices[4]->processBlock(nullptr, nullptr, numSamplesToProcess, triggerBuffers[4]);

        // 6. Obtener punteros específicos para la modulación patch-bay cruzada de Synth 1 (Psyche)
        auto psycheVoice = std::static_pointer_cast<PsycheVoice>(m_voices[4]);
        const float* waveguideOut = psycheVoice->getWaveguideOut();
        const float* syn1Lfo = psycheVoice->getLfoPhase();

        // Parámetros de la modulación patch-bay de Synth 1
        double fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(m_sampleRate)));
        float fConst1 = std::tan(6283.1855f / fConst0);
        float fConst3 = 1.0f / fConst1;
        float fConst5 = 1.0f / ((fConst3 + 1.4142135f) / fConst1 + 1.0f);
        float fConst61 = 3.1415927f / fConst0;

        float syn1AutoProf = getVoiceParamValue(4, "/auto_p", 0.7f);
        float syn1AutoRes = getVoiceParamValue(4, "/auto_r", 4.5f);
        float syn1Vol = getVoiceParamValue(4, "/vol", 0.85f);
        float fSlow33 = fConst5 * syn1Vol * (1.0f - 0.5f * syn1AutoProf);

        float fSlow316 = 5000.0f * syn1AutoProf;
        float fSlow317 = 1.0f / syn1AutoRes;
        float fSlow318 = 85.0f * syn1AutoProf;
        float fSlow319 = syn1AutoProf * syn1Vol;

        for (int i = 0; i < numSamplesToProcess; ++i) {
            float mono_sum = outL[offset + i]; // outL y outR contienen el mismo mono sum en este punto

            float lfo_phase = syn1Lfo[i];
            float rawWaveguideSample = waveguideOut[i];

            // Guardar pegada cruda en la línea de retardo circular de mydsp (fVec6 en Faust de tamaño 256)
            m_vec6PsycheRaw[m_iota0 & 255] = rawWaveguideSample;

            // Calcular resonador fRec83
            float fTemp93 = std::sin(3.1415927f * lfo_phase);
            float fTemp94 = std::tan(fConst61 * (fSlow316 * fTemp93 + 400.0f));
            float fTemp95 = 1.0f / fTemp94;
            float fTemp96 = (fSlow317 + fTemp95) / fTemp94 + 1.0f;
            float fTemp97 = fSlow318 * fTemp93;
            float fTemp98 = fTemp97 + 100.0f;
            int iTemp99 = static_cast<int>(fTemp98);
            float fTemp100 = std::floor(fTemp98);

            float delayedPsyche1 = m_vec6PsycheRaw[(m_iota0 - std::min<int>(4097, std::max<int>(0, iTemp99))) & 255];
            float delayedPsyche2 = m_vec6PsycheRaw[(m_iota0 - std::min<int>(4097, std::max<int>(0, iTemp99 + 1))) & 255];
            float interpolationPsyche = delayedPsyche1 * (fTemp100 + (-99.0f - fTemp97)) + (fTemp97 + (100.0f - fTemp100)) * delayedPsyche2;

            float power_term = fTemp94 * fTemp94;
            m_rec83Resonator[0] = fConst5 * interpolationPsyche - (m_rec83Resonator[2] * ((fTemp95 - fSlow317) / fTemp94 + 1.0f) + 2.0f * m_rec83Resonator[1] * (1.0f - 1.0f / power_term)) / fTemp96;

            // Moduladores estéreo de Synth 1 (Psyche)
            float leftMod = fSlow33 * std::sqrt(1.0f - lfo_phase) * rawWaveguideSample;
            float rightMod = fSlow319 * (std::sqrt(lfo_phase) * (m_rec83Resonator[0] - m_rec83Resonator[2]) / (fTemp94 * fTemp96));

            outL[offset + i] = mono_sum + leftMod;
            outR[offset + i] = mono_sum + rightMod;

            // Actualizar estados
            m_rec83Resonator[2] = m_rec83Resonator[1];
            m_rec83Resonator[1] = m_rec83Resonator[0];
            m_iota0++;
        }

        // 7. Aplicar efectos maestros para este chunk (Mixer: ganancia 1.5, volumen maestro, saturador tanh + DC blocker)
        m_mixer.processMaster(outL + offset, outR + offset, numSamplesToProcess);

        offset += numSamplesToProcess;
    }
}

int mydsp::getCurrentStep() {
    int step = 0;
    // Retornamos el paso actual del reloj de bombo (como hacíamos en Faust)
    float bpmVal = fHslider[0];
    int dummyStep = 0;
    // Simplemente leer el estado actual
    return m_lastBeatStep.load();
}

extern "C" dsp* newmydsp() {
    return new mydsp();
}

extern "C" void deletemydsp(dsp* d) {
    delete d;
}
