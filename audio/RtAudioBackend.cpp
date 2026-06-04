#include "RtAudioBackend.h"
#include <RtAudio.h>
#include <iostream>

#include "../core/FaustDefs.h"

namespace audio {

RtAudioBackend::RtAudioBackend(dsp* faust_dsp, audio::FaustMapUI* ui)
    : m_dsp(faust_dsp), m_ui(ui) {
    m_dac = std::make_unique<rt::audio::RtAudio>();
}

RtAudioBackend::~RtAudioBackend() {
    stop();
}

void RtAudioBackend::printAvailableDevices() {
    std::cout << "--- Dispositivos de Audio Disponibles ---" << std::endl;
    std::vector<unsigned int> deviceIds = m_dac->getDeviceIds();
    for (unsigned int id : deviceIds) {
        rt::audio::RtAudio::DeviceInfo info = m_dac->getDeviceInfo(id);
        std::cout << "[" << id << "] " << info.name 
                  << " (In: " << info.inputChannels << ", Out: " << info.outputChannels << ")" 
                  << std::endl;
    }
    std::cout << "-----------------------------------------" << std::endl;
}

bool RtAudioBackend::openDevice(int deviceId) {
    if (m_dac->getDeviceCount() == 0) {
        std::cerr << "No se encontraron dispositivos de audio." << std::endl;
        return false;
    }

    std::vector<unsigned int> candidates;
    if (deviceId != 0) {
        candidates.push_back(static_cast<unsigned int>(deviceId));
    } else {
        // Primero intentamos con el dispositivo por defecto
        try {
            unsigned int default_device = m_dac->getDefaultOutputDevice();
            candidates.push_back(default_device);
        } catch (...) {}
        
        // Luego añadimos todos los demás dispositivos como alternativas de fallback
        std::vector<unsigned int> deviceIds = m_dac->getDeviceIds();
        for (unsigned int id : deviceIds) {
            bool alreadyInList = false;
            for (unsigned int c : candidates) {
                if (c == id) {
                    alreadyInList = true;
                    break;
                }
            }
            if (!alreadyInList) {
                candidates.push_back(id);
            }
        }
    }

    bool streamOpened = false;

    for (unsigned int id : candidates) {
        try {
            rt::audio::RtAudio::DeviceInfo info = m_dac->getDeviceInfo(id);
            if (info.outputChannels == 0) {
                continue; // No es un dispositivo de salida
            }

            std::cout << "Intentando abrir dispositivo de audio: [" << id << "] " << info.name << "..." << std::endl;

            rt::audio::RtAudio::StreamParameters out_parameters;
            out_parameters.deviceId = id;
            out_parameters.nChannels = m_dsp->getNumOutputs(); // Stereo (desde Faust)
            out_parameters.firstChannel = 0;

            rt::audio::RtAudio::StreamParameters in_parameters;
            bool hasInput = false;
            if (info.inputChannels > 0) {
                in_parameters.deviceId = id;
                in_parameters.nChannels = 1; // Mono es suficiente para recibir sincronización externa
                in_parameters.firstChannel = 0;
                hasInput = true;
            }

            unsigned int sampleRate = 48000;
            unsigned int bufferFrames = 256;

            m_dsp->init(sampleRate);

            rt::audio::RtAudioErrorType err = m_dac->openStream(
                &out_parameters,
                hasInput ? &in_parameters : nullptr,
                rt::audio::RTAUDIO_FLOAT32,
                sampleRate,
                &bufferFrames,
                &RtAudioBackend::audioCallback,
                this
            );

            if (err == rt::audio::RTAUDIO_NO_ERROR) {
                streamOpened = true;
                m_currentDeviceId = id;
                std::cout << "-> Dispositivo abierto con éxito: [" << id << "] " << info.name << std::endl;
                if (hasInput) {
                    std::cout << "CLOCK: Entrada de audio analógica habilitada para sincronización." << std::endl;
                }
                break; // Conexión exitosa, detenemos la búsqueda
            } else {
                std::cerr << "-> Falló al abrir flujo en [" << id << "]: " << m_dac->getErrorText() << std::endl;
            }
        } catch (...) {
            std::cerr << "-> Excepción o error desconocido al intentar abrir dispositivo ID " << id << std::endl;
        }
    }

    return streamOpened;
}
}

bool RtAudioBackend::changeDevice(int deviceId) {
    std::cout << "Cambiando dinámicamente de dispositivo de audio a: " << deviceId << "..." << std::endl;
    stop();
    if (openDevice(deviceId)) {
        start();
        std::cout << "Dispositivo de audio cambiado correctamente al ID [" << m_currentDeviceId << "]." << std::endl;
        return true;
    } else {
        std::cerr << "Error al cambiar al dispositivo " << deviceId << ". Reintentando con el anterior o por defecto..." << std::endl;
        openDevice(0);
        start();
        return false;
    }
}

std::vector<std::pair<int, std::string>> RtAudioBackend::getAvailableOutputs() {
    std::vector<std::pair<int, std::string>> outputs;
    std::vector<unsigned int> deviceIds = m_dac->getDeviceIds();
    for (unsigned int id : deviceIds) {
        try {
            rt::audio::RtAudio::DeviceInfo info = m_dac->getDeviceInfo(id);
            if (info.outputChannels > 0) {
                outputs.push_back({static_cast<int>(id), info.name});
            }
        } catch (...) {}
    }
    return outputs;
}

void RtAudioBackend::start() {
    if (!m_dac->isStreamOpen()) {
        std::cerr << "Advertencia: El flujo de audio no esta abierto. Use la interfaz web o el comando 'set <id>' para seleccionar un dispositivo." << std::endl;
        return;
    }
    rt::audio::RtAudioErrorType err = m_dac->startStream();
    if (err != rt::audio::RTAUDIO_NO_ERROR) {
        std::cerr << "Error al iniciar el audio: " << m_dac->getErrorText() << std::endl;
    } else {
        std::cout << "Flujo de audio iniciado correctamente." << std::endl;
    }
}

void RtAudioBackend::stop() {
    if (m_dac->isStreamRunning()) {
        m_dac->stopStream();
    }
    if (m_dac->isStreamOpen()) {
        m_dac->closeStream();
    }
}

int RtAudioBackend::audioCallback(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
                                  double streamTime, unsigned int status, void* userData) {
    RtAudioBackend* backend = static_cast<RtAudioBackend*>(userData);
    float* out = static_cast<float*>(outputBuffer);
    
    // 1. Procesar detección y emulación de reloj
    if (backend->m_ui) {
        core::Synthesizer* synth = backend->m_ui->getSynth();
        if (synth) {
            double sampleRate = 48000.0;
            double time_per_sample_ms = 1000.0 / sampleRate;
            
            // A. Detección física por señal de voltaje si hay entrada
            if (inputBuffer) {
                float* in = static_cast<float*>(inputBuffer);
                static float lastSample = 0.0f;
                static double lastTriggerTime = 0.0;
                
                for (unsigned int i = 0; i < nBufferFrames; i++) {
                    float currentSample = in[i];
                    
                    if (currentSample > 0.4f && lastSample <= 0.4f) {
                        double current_time_ms = (streamTime * 1000.0) + (i * time_per_sample_ms);
                        if (current_time_ms - lastTriggerTime > 50.0) {
                            std::cout << "\n[CLOCK ANALÓGICO] -> Voltaje detectado (" << currentSample << " V). Sincronizando BPM..." << std::endl;
                            synth->getClock()->syncPulse(current_time_ms);
                            lastTriggerTime = current_time_ms;
                        }
                    }
                    lastSample = currentSample;
                }
            }
            
            // B. Emulación lógica de reloj si el emulador está activo
            static bool emuActive = false;
            static float emuBpm = 120.0f;
            static double emuLastTriggerTime = 0.0;
            
            auto emuActiveParam = synth->getParameter("/emulator/active");
            auto emuBpmParam = synth->getParameter("/emulator/bpm");
            if (emuActiveParam) emuActive = (emuActiveParam->getValue() > 0.5f);
            if (emuBpmParam) emuBpm = emuBpmParam->getValue();
            
            if (emuActive && emuBpm > 20.0f) {
                double interval_ms = 60000.0 / emuBpm;
                double current_time_ms = streamTime * 1000.0;
                
                if (current_time_ms - emuLastTriggerTime >= interval_ms) {
                    std::cout << "\n[EMULADOR DE CLOCK] -> Generando pulso simulado a " << emuBpm << " BPM (" << current_time_ms << " ms)..." << std::endl;
                    synth->getClock()->syncPulse(current_time_ms);
                    emuLastTriggerTime = current_time_ms;
                }
            }
        }
    }
    
    // RtAudio usa buffers intercalados (L, R, L, R) pero Faust usa no intercalados (L_array, R_array)
    // Usaremos un buffer intermedio estático o variables temporales
    static float outL[4096];
    static float outR[4096];
    float* faustOut[2] = {outL, outR};
    
    // 2. Transferir valores atómicos (lock-free) al DSP
    backend->m_ui->updateDSPValues();
    
    // 3. Ejecutar Faust DSP
    backend->m_dsp->compute(nBufferFrames, nullptr, faustOut);
    
    // 4. Intercalar salida para RtAudio
    for (unsigned int i = 0; i < nBufferFrames; i++) {
        out[2 * i]     = outL[i];
        out[2 * i + 1] = outR[i];
    }
    
    return 0;
}

} // namespace audio
