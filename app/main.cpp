#include "../core/Synthesizer.h"
#include "../state/PresetManager.h"
#include "../state/AutomationRecorder.h"
#include "../audio/FaustUI.h"
#include "../audio/RtAudioBackend.h"
#include "../osc/OscServer.h"

#include "../core/FaustDefs.h"

extern "C" dsp* newmydsp();
extern "C" void deletemydsp(dsp* d);

#include <iostream>
#include <string>
#include <thread>
#include <csignal>
#include <atomic>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

std::string getPrimaryIp() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        struct addrinfo hints, *res, *p;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        if (getaddrinfo(hostname, nullptr, &hints, &res) == 0) {
            for (p = res; p != nullptr; p = p->ai_next) {
                struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
                char ipstr[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
                std::string ip(ipstr);
                if (ip != "127.0.0.1" && ip != "0.0.0.0") {
                    freeaddrinfo(res);
                    return ip;
                }
            }
            freeaddrinfo(res);
        }
    }
    return "127.0.0.1";
}
#endif

static state::PresetManager* g_presetMgr = nullptr;

static void signalHandler(int signum) {
    std::cout << "\nSe recibio la senal de interrupcion (" << signum << ")..." << std::endl;
    if (g_presetMgr) {
        std::cout << "Guardando configuracion de perillas en preset.json de forma segura..." << std::endl;
        g_presetMgr->savePreset("preset.json");
    }
    std::exit(signum);
}

int main(int argc, char* argv[]) {
    std::cout << R"(
  ____    _     _____ _____ 
 |  _ \  / \   |__  /|__  / 
 | |_) |/ _ \    / /   / /  
 |  _ < / ___ \  / /_  / /_  
 |_| \_\_/   \_\/____|/____|
  TR-808 ALGORITHMIC STATION
)" << std::endl;
    std::cout << "=== TR-808 Algorithmic Techno Station Server ===" << std::endl;

    // 1. Instanciar DSP de Faust
    std::unique_ptr<dsp> synthDsp(newmydsp());

    // 2. Instanciar Dominio (Synthesizer)
    core::Synthesizer synthCore;

    // Inicializar el DSP antes de mapear la interfaz para poblar la memoria con valores por defecto
    synthDsp->init(44100);

    // 3. Crear UI de mapeo OSC/Faust
    audio::FaustMapUI ui(&synthCore);
    synthDsp->buildUserInterface(&ui); // Faust registra los sliders aquí

    // Registrar parámetros manuales para el Emulador de Reloj Externo
    synthCore.addParameter(std::make_shared<core::Parameter>("/emulator/active", 0.0f, 1.0f, 0.0f));
    synthCore.addParameter(std::make_shared<core::Parameter>("/emulator/bpm", 60.0f, 240.0f, 120.0f));

    // 4. Módulos de Estado
    state::PresetManager presetMgr(&synthCore);
    state::AutomationRecorder recorder(&synthCore);
    g_presetMgr = &presetMgr;

    // Registrar manejadores de señales para guardar el estado al salir
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    // Cargar automáticamente la configuración de las últimas perillas
    if (presetMgr.loadPreset("preset.json")) {
        std::cout << "Se cargo la ultima configuracion de perillas desde preset.json" << std::endl;
    } else {
        std::cout << "No se encontro preset.json. Usando valores predeterminados." << std::endl;
    }

    // 5. Backend de Audio (RtAudio)
    audio::RtAudioBackend audioBackend(synthDsp.get(), &ui);
    
    // Enumerar dispositivos de audio iniciales
    audioBackend.printAvailableDevices();

    // Seleccionar dispositivo (0 = autodetección del mejor dispositivo de salida de audio)
    int deviceId = 0;
    if (argc > 1) {
        try {
            deviceId = std::stoi(argv[1]);
        } catch (...) {
            std::cerr << "Advertencia: Argumento de ID de dispositivo no válido. Usando autodetección." << std::endl;
        }
    }

    std::cout << "\nIniciando conexión automática de audio..." << std::endl;
    if (!audioBackend.openDevice(deviceId)) {
        std::cerr << "Advertencia: No se pudo abrir un dispositivo de audio de salida válido al iniciar." << std::endl;
        std::cerr << "El servidor continuará ejecutándose para permitir la selección de dispositivo desde la interfaz web (puerto 8000/9001)." << std::endl;
    }

    // 6. Servidor OSC (pasando el backend de audio para controlarlo remotamente)
    osc::OscServer oscServer(&synthCore, &presetMgr, &recorder, &audioBackend);
    if (!oscServer.start("8000")) {
        std::cerr << "Error crítico: No se pudo iniciar el servidor OSC en el puerto 8000." << std::endl;
        return 1;
    }

    // Arrancar audio
    audioBackend.start();

#ifdef _WIN32
    // Desplegar el servidor automáticamente en el navegador predeterminado apuntando a la IP en red
    std::string ip = getPrimaryIp();
    std::string cmd = "start http://" + ip + ":8000";
    std::system(cmd.c_str());
#endif

    std::cout << "\n==========================================================" << std::endl;
    std::cout << "TR-808 Algorithmic Techno Station Server ACTIVO." << std::endl;
    std::cout << "Dispositivo de audio activo: [" << audioBackend.getCurrentDeviceId() << "]" << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "Comandos de consola disponibles:" << std::endl;
    std::cout << "  list          - Listar dispositivos de salida de audio" << std::endl;
    std::cout << "  set <id>      - Cambiar al dispositivo de audio indicado" << std::endl;
    std::cout << "  emu on / off  - Activar o desactivar emulación de reloj" << std::endl;
    std::cout << "  emu bpm <val> - Establecer tempo del emulador" << std::endl;
    std::cout << "  status        - Ver estado detallado en tiempo real" << std::endl;
    std::cout << "  exit / quit   - Detener el servidor y salir" << std::endl;
    std::cout << "==========================================================\n" << std::endl;

    std::string line;
    while (true) {
        std::cout << "synth-server> " << std::flush;
        if (!std::getline(std::cin, line)) {
            // Fin de entrada (ej: ejecutándose sin consola interactiva o en segundo plano)
            std::cout << "Entrada interactiva cerrada. Servidor ejecutándose en segundo plano..." << std::endl;
            // Bloquear infinitamente en este hilo para que los hilos de RtAudio y OSC sigan corriendo
            while (true) {
                std::this_thread::sleep_for(std::chrono::seconds(10));
            }
            break;
        }
        
        // Quitar espacios al inicio/final
        while (!line.empty() && std::isspace(line.front())) line.erase(line.begin());
        while (!line.empty() && std::isspace(line.back())) line.pop_back();

        if (line.empty()) continue;

        if (line == "exit" || line == "quit") {
            std::cout << "Deteniendo servidor..." << std::endl;
            break;
        } else if (line == "list") {
            std::cout << "\n--- Dispositivos de Salida de Audio Disponibles ---" << std::endl;
            auto outputs = audioBackend.getAvailableOutputs();
            int current = audioBackend.getCurrentDeviceId();
            for (const auto& dev : outputs) {
                std::cout << (dev.first == current ? " *-> " : "    ") 
                          << "[" << dev.first << "] " << dev.second << std::endl;
            }
            std::cout << "---------------------------------------------------\n" << std::endl;
        } else if (line.rfind("set ", 0) == 0) {
            try {
                int newId = std::stoi(line.substr(4));
                audioBackend.changeDevice(newId);
            } catch (...) {
                std::cout << "Error: ID no válido. Uso: set <id>" << std::endl;
            }
        } else if (line == "emu on") {
            auto param = synthCore.getParameter("/emulator/active");
            if (param) {
                param->setValue(1.0f);
                std::cout << "Emulador de reloj: ACTIVADO" << std::endl;
            }
        } else if (line == "emu off") {
            auto param = synthCore.getParameter("/emulator/active");
            if (param) {
                param->setValue(0.0f);
                std::cout << "Emulador de reloj: DESACTIVADO" << std::endl;
            }
        } else if (line.rfind("emu bpm ", 0) == 0) {
            try {
                float bpmVal = std::stof(line.substr(8));
                auto param = synthCore.getParameter("/emulator/bpm");
                if (param) {
                    param->setValue(bpmVal);
                    std::cout << "BPM del emulador establecido a: " << bpmVal << " BPM" << std::endl;
                }
            } catch (...) {
                std::cout << "Error: BPM no válido. Uso: emu bpm <valor>" << std::endl;
            }
        } else if (line == "status" || line == "emu status") {
            auto active = synthCore.getParameter("/emulator/active");
            auto bpm = synthCore.getParameter("/emulator/bpm");
            float curBpm = synthCore.getClock()->getBpm();
            std::cout << "\n--- Estado de la Estación TR-808 ---" << std::endl;
            std::cout << "  BPM Activo (Reloj):  " << curBpm << " BPM" << std::endl;
            std::cout << "  Emulador de Reloj:   " << (active && active->getValue() > 0.5f ? "ACTIVO" : "DESACTIVADO") << std::endl;
            std::cout << "  BPM del Emulador:    " << (bpm ? bpm->getValue() : 120.0f) << " BPM" << std::endl;
            std::cout << "  Salida de Audio Activa: [" << audioBackend.getCurrentDeviceId() << "]" << std::endl;
            std::cout << "------------------------------------\n" << std::endl;
        } else {
            std::cout << "Comando no reconocido. Comandos disponibles: list, set <id>, emu on, emu off, emu bpm <val>, status, exit" << std::endl;
        }
    }

    // Limpiar y guardar estado final
    std::cout << "Guardando configuracion final de perillas en preset.json..." << std::endl;
    presetMgr.savePreset("preset.json");
    g_presetMgr = nullptr;

    audioBackend.stop();
    oscServer.stop();

    return 0;
}
