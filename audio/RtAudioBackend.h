#pragma once

#include <string>
#include <memory>
#include <vector>
#include <utility>
#include "../audio/FaustUI.h"

// Declaración frontal para no incluir RtAudio.h en la cabecera (PIMPL)
namespace rt {
namespace audio {
class RtAudio;
}
}
class dsp; // De untitled.cpp

namespace audio {

class RtAudioBackend {
public:
    RtAudioBackend(dsp* faust_dsp, audio::FaustMapUI* ui);
    ~RtAudioBackend();

    // Enumera los dispositivos e imprime en consola
    void printAvailableDevices();

    // Inicia el flujo de audio en un dispositivo específico (0 = default)
    bool openDevice(int deviceId = 0);
    
    void start();
    void stop();

    // Cambia dinámicamente el dispositivo de audio
    bool changeDevice(int deviceId);

    // Obtiene el ID del dispositivo activo
    int getCurrentDeviceId() const { return m_currentDeviceId; }

    // Obtiene lista de dispositivos con canales de salida
    std::vector<std::pair<int, std::string>> getAvailableOutputs();

private:
    static int audioCallback(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
                             double streamTime, unsigned int status, void* userData);

    std::unique_ptr<rt::audio::RtAudio> m_dac;
    dsp* m_dsp;
    audio::FaustMapUI* m_ui;
    int m_currentDeviceId = 0;
};

} // namespace audio
