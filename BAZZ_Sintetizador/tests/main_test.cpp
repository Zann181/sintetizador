// =============================================================================
// main_test.cpp — Pruebas básicas del sintetizador BAZZ
// =============================================================================
//
// Ejecutable de prueba que verifica la compilación y el funcionamiento
// básico de los módulos principales: voces, secuenciador, y PresetManager.
//
// Uso:
//   mkdir build && cd build
//   cmake .. -DCMAKE_BUILD_TYPE=Debug
//   cmake --build .
//   ./bin/bazz_test
// =============================================================================

#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <memory>
#include <string>

// --- Módulos del sintetizador ---
#include "PresetManager.h"
#include "IInstrumentVoice.h"
#include "AudioMixer.h"
#include "Sequencer.h"
#include "Clock.h"
#include "KickVoice.h"
#include "SnareVoice.h"
#include "HiHatVoice.h"
#include "BassVoice.h"
#include "PsycheVoice.h"
#include "SiringeVoice.h"

// ---------------------------------------------------------------------------
// Utilidades de prueba
// ---------------------------------------------------------------------------

static int g_testsRun    = 0;
static int g_testsPassed = 0;

#define TEST(nombre, expresion)                                              \
    do {                                                                     \
        ++g_testsRun;                                                        \
        if (expresion) {                                                     \
            ++g_testsPassed;                                                 \
            std::cout << "  [OK]  " << (nombre) << "\n";                     \
        } else {                                                             \
            std::cerr << "  [FALLO] " << (nombre)                            \
                      << "  (" << __FILE__ << ":" << __LINE__ << ")\n";      \
        }                                                                    \
    } while (false)

// ---------------------------------------------------------------------------
// Prueba 1: Serialización y deserialización de presets (ida y vuelta)
// ---------------------------------------------------------------------------
static void testPresetRoundTrip()
{
    std::cout << "\n--- Prueba: PresetManager (ida y vuelta) ---\n";

    PresetManager mgr;

    // Crear un preset personalizado
    Preset original;
    original.name   = "Techno Oscuro";
    original.author = "DJ BAZZ";
    original.bpm    = 138.5f;

    // Configurar el canal 0 (Kick)
    auto& kick = original.channels[0];
    kick.instrumentName = "Kick";
    kick.swing = 15.0f;
    kick.parameters["volume"] = 0.9f;
    kick.parameters["decay"]  = 0.22f;
    kick.parameters["tune"]   = -0.5f;
    kick.steps = {true,false,false,false, true,false,false,false,
                  true,false,false,false, true,false,false,false};

    // Configurar canal 2 (HiHat)
    auto& hat = original.channels[2];
    hat.instrumentName = "HiHat";
    hat.parameters["openness"] = 0.4f;
    for (int i = 0; i < BAZZ_NUM_STEPS; i += 2) {
        hat.steps[static_cast<size_t>(i)] = true;
    }

    // --- Serializar ---
    std::string serialized = mgr.serializeToString(original);
    TEST("Serialización no vacía", !serialized.empty());

    // Imprimir el resultado para inspección visual
    std::cout << "\n  --- Salida serializada ---\n" << serialized
              << "  --- Fin de salida ---\n\n";

    // --- Deserializar ---
    Preset loaded;
    bool ok = mgr.deserializeFromString(serialized, loaded);
    TEST("Deserialización exitosa", ok);

    if (!ok) {
        std::cerr << "  Error: " << mgr.getLastError() << "\n";
        return;
    }

    // --- Verificar igualdad ---
    TEST("Nombre del preset", loaded.name == original.name);
    TEST("Autor del preset",  loaded.author == original.author);
    TEST("BPM del preset",    std::abs(loaded.bpm - original.bpm) < 0.01f);

    TEST("Nombre instrumento canal 0",
         loaded.channels[0].instrumentName == "Kick");
    TEST("Swing canal 0",
         std::abs(loaded.channels[0].swing - 15.0f) < 0.01f);
    TEST("Parámetro volume canal 0",
         std::abs(loaded.channels[0].parameters["volume"] - 0.9f) < 0.01f);
    TEST("Parámetro decay canal 0",
         std::abs(loaded.channels[0].parameters["decay"] - 0.22f) < 0.01f);
    TEST("Parámetro tune canal 0 (negativo)",
         std::abs(loaded.channels[0].parameters["tune"] - (-0.5f)) < 0.01f);

    // Verificar patrón de pasos del Kick
    bool stepsOk = true;
    for (int i = 0; i < BAZZ_NUM_STEPS; ++i) {
        if (loaded.channels[0].steps[static_cast<size_t>(i)] !=
            original.channels[0].steps[static_cast<size_t>(i)]) {
            stepsOk = false;
            break;
        }
    }
    TEST("Patrón de pasos canal 0 (Kick)", stepsOk);

    // Verificar HiHat
    TEST("Parámetro openness canal 2",
         std::abs(loaded.channels[2].parameters["openness"] - 0.4f) < 0.01f);
}

// ---------------------------------------------------------------------------
// Prueba 2: Preset por defecto
// ---------------------------------------------------------------------------
static void testDefaultPreset()
{
    std::cout << "\n--- Prueba: Preset por defecto ---\n";

    Preset def = PresetManager::createDefaultPreset();

    TEST("Nombre por defecto",  def.name == "Init");
    TEST("Autor por defecto",   def.author == "BAZZ");
    TEST("BPM por defecto",     std::abs(def.bpm - 140.0f) < 0.01f);
    TEST("Kick en paso 0",     def.channels[0].steps[0] == true);
    TEST("Kick en paso 1",     def.channels[0].steps[1] == false);
    TEST("Snare en paso 4",    def.channels[1].steps[4] == true);
    TEST("HiHat en paso 0",    def.channels[2].steps[0] == true);
    TEST("HiHat en paso 1",    def.channels[2].steps[1] == false);
}

// ---------------------------------------------------------------------------
// Prueba 3: Instanciar y configurar voces
// ---------------------------------------------------------------------------
static void testVoiceInstantiation()
{
    std::cout << "\n--- Prueba: Instanciación de voces ---\n";

    constexpr double sampleRate = 44100.0;

    // Crear todas las voces del sintetizador
    std::vector<std::shared_ptr<IInstrumentVoice>> voices;
    voices.push_back(std::make_shared<KickVoice>());
    voices.push_back(std::make_shared<SnareVoice>());
    voices.push_back(std::make_shared<HiHatVoice>());
    voices.push_back(std::make_shared<BassVoice>());
    voices.push_back(std::make_shared<PsycheVoice>());
    voices.push_back(std::make_shared<SiringeVoice>());

    TEST("6 voces creadas", voices.size() == 6);

    // Inicializar cada voz
    for (auto& voice : voices) {
        voice->initialize(sampleRate);
        voice->clearState();
    }
    TEST("Todas las voces inicializadas", true);  // Si llega aquí, no hubo crash

    // Procesar un bloque de audio con el Kick
    constexpr int blockSize = 256;
    std::vector<float> bufferL(blockSize, 0.0f);
    std::vector<float> bufferR(blockSize, 0.0f);

    voices[0]->trigger(1.0f);  // Disparar el kick a velocidad máxima
    voices[0]->processBlock(bufferL.data(), bufferR.data(), blockSize);

    // Verificar que se generó alguna señal (no todo ceros)
    float sumL = 0.0f;
    for (int i = 0; i < blockSize; ++i) {
        sumL += std::abs(bufferL[static_cast<size_t>(i)]);
    }
    TEST("Kick genera señal de audio", sumL > 0.0f);
}

// ---------------------------------------------------------------------------
// Prueba 4: Secuenciador
// ---------------------------------------------------------------------------
static void testSequencer()
{
    std::cout << "\n--- Prueba: Secuenciador ---\n";

    Sequencer seq;
    seq.clearGrid();

    // Activar algunos pasos
    seq.setStep(0, 0, true);   // Kick en paso 0
    seq.setStep(0, 4, true);   // Kick en paso 4
    seq.setStep(1, 4, true);   // Snare en paso 4

    TEST("Kick paso 0 activo",    seq.getStep(0, 0) == true);
    TEST("Kick paso 1 inactivo",  seq.getStep(0, 1) == false);
    TEST("Kick paso 4 activo",    seq.getStep(0, 4) == true);
    TEST("Snare paso 4 activo",   seq.getStep(1, 4) == true);
    TEST("HiHat paso 0 inactivo", seq.getStep(2, 0) == false);

    // Limpiar y verificar
    seq.clearGrid();
    TEST("Kick paso 0 tras limpiar", seq.getStep(0, 0) == false);
}

// ---------------------------------------------------------------------------
// Prueba 5: Reloj (Clock)
// ---------------------------------------------------------------------------
static void testClock()
{
    std::cout << "\n--- Prueba: Clock ---\n";

    Clock clock;
    clock.initialize(44100.0);
    clock.setBpm(120.0f);
    clock.setSwing(0.0f);

    TEST("BPM configurado", std::abs(clock.getBpm() - 120.0f) < 0.01f);
    TEST("Swing configurado", std::abs(clock.getSwing() - 0.0f) < 0.01f);

    clock.reset();
    TEST("Clock reseteado", true);  // Si llega aquí sin crash, está bien
}

// ---------------------------------------------------------------------------
// Prueba 6: AudioMixer
// ---------------------------------------------------------------------------
static void testAudioMixer()
{
    std::cout << "\n--- Prueba: AudioMixer ---\n";

    AudioMixer mixer;
    mixer.reset();

    constexpr int blockSize = 64;
    std::vector<float> bufL(blockSize, 0.5f);   // Señal constante
    std::vector<float> bufR(blockSize, -0.5f);

    mixer.processMaster(bufL.data(), bufR.data(), blockSize);

    // Verificar que la salida no es todo ceros ni idéntica a la entrada
    bool modified = false;
    for (int i = 0; i < blockSize; ++i) {
        if (std::abs(bufL[static_cast<size_t>(i)] - 0.5f) > 0.001f) {
            modified = true;
            break;
        }
    }
    TEST("AudioMixer modifica la señal", modified);
}

// ---------------------------------------------------------------------------
// Punto de entrada
// ---------------------------------------------------------------------------
int main()
{
    std::cout << "============================================\n";
    std::cout << "  BAZZ_Sintetizador — Pruebas Básicas\n";
    std::cout << "============================================\n";

    testPresetRoundTrip();
    testDefaultPreset();
    testVoiceInstantiation();
    testSequencer();
    testClock();
    testAudioMixer();

    std::cout << "\n============================================\n";
    std::cout << "  Resultados: " << g_testsPassed << " / " << g_testsRun
              << " pruebas exitosas\n";
    std::cout << "============================================\n";

    return (g_testsPassed == g_testsRun) ? 0 : 1;
}
