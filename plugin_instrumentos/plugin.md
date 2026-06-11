# Guía de Integración de Instrumentos (Plugins) en BAZZ

Esta guía describe el flujo de trabajo y las reglas arquitectónicas necesarias para integrar nuevos instrumentos de Faust como "plugins" modulares dentro del motor de síntesis de audio en C++ del sintetizador BAZZ.

---

## 1. Requisitos de la Estructura en Faust (`.dsp`)

Para que el sistema de mapeo dinámico y el secuenciador puedan comunicarse de forma nativa con tu código Faust, la estructura del archivo `.dsp` debe respetar las siguientes directrices:

### A. Mapeo de Parámetros por Metadatos OSC
El motor BAZZ descubre los parámetros del DSP a través del objeto `UI` de Faust. Cada control (`hslider`, `vslider`, `checkbox`) debe incluir obligatoriamente metadatos OSC con la ruta y rangos explícitos:
```faust
// Sintaxis requerida: [osc:/ruta/parametro min max]
pitch = hslider("pitch [osc:/kick/pitch 30 100][style:knob]", 52, 30, 100, 0.1);
```
*   **Nota**: BAZZ utiliza esta información para poblar automáticamente el mapeo en el objeto `Synthesizer` y exponerlos en el servidor HTTP (`/api/params`) que consume la web.

### B. El Canal de Disparo (Gate)
Todo instrumento rítmico o sintetizado debe exponer un parámetro booleano de disparo tipo `checkbox` con la ruta `/instrumento/gate`:
```faust
gate = checkbox("gate [osc:/kick/gate 0 1][style:toggle]");
```
*   Este canal de compuerta es el que el secuenciador activa para disparar las envolventes AR/ADSR internas del instrumento.

### C. Salida del Instrumento
El punto de entrada principal (`process`) debe dirigir la salida al bus estéreo:
```faust
// Para salida estéreo:
process = kick_full <: _,_ : limiter;

// Para salida mono (se duplicará en el wrapper C++):
process = kick_full;
```

---

## 2. Generación del Código C++

Una vez que tu archivo `.dsp` está listo, utiliza el compilador de Faust para generar el código C++ optimizado sin envoltorios de plataforma:

```bash
faust -lang cpp -es 1 -mcd 16 -single -ftz 0 mi_instrumento.dsp -o mi_instrumento.cpp
```
*   **`-lang cpp`**: Compila a código C++ puro.
*   **`-es 1`**: Habilita la simplificación y optimización de expresiones matemáticas.
*   **`-single`**: Usa aritmética de precisión simple (`float`), que es la usada por el motor de audio de BAZZ.
*   **`-ftz 0`**: Controla el tratamiento de números desnormalizados (subnormales).

---

## 3. Integración en el Engine C++ (Wrapper de Voz)

Dado que cada compilación de Faust genera una clase con el nombre hardcodeado `mydsp`, dos o más archivos de Faust compitiendo en el mismo proyecto C++ provocarían colisiones de símbolos y nombres duplicados. 

Para solucionar esto de forma elegante y limpia, implementamos la técnica **Namespace Wrapping**.

### A. Estructura de la Clase Wrapper (Header `.h`)
Declara una nueva clase en `BAZZ_Sintetizador/voices/` que herede de `IInstrumentVoice`:

```cpp
#pragma once
#include "../core/IInstrumentVoice.h"
#include "../core/InstrumentDescriptor.h"
#include <atomic>
#include <memory>

// Pre-declaramos la clase mydsp dentro de su propio namespace exclusivo
namespace mi_instrumento_ns {
    class mydsp;
}

class MiInstrumentoVoice : public IInstrumentVoice {
private:
    double m_sampleRate = 44100.0;
    std::unique_ptr<mi_instrumento_ns::mydsp> m_dsp;

    // Punteros directos a las variables de memoria del DSP de Faust
    float* m_ptrGate = nullptr;
    float* m_ptrPitch = nullptr;
    // ... otros punteros de parámetros

    // Variables atómicas de control local (hilo seguro)
    std::atomic<float> m_volume{0.8f};
    std::atomic<float> m_pitch{52.0f};

    // Estado del disparo
    std::atomic<float> m_triggerVelocity{0.0f};
    std::atomic<bool> m_triggered{false};
    float m_currentVelocity = 1.0f;
    bool m_gateActive = false;

public:
    MiInstrumentoVoice() = default;
    ~MiInstrumentoVoice() override;

    void initialize(double sampleRate) override;
    void clearState() override;
    void trigger(float velocity) override;
    void processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer = nullptr) override;
    void setParameter(const std::string& name, float value) override;
    void setParameterById(uint32_t paramId, float value) override;
    // ... métodos de descriptor y estado v2
};
```

### B. Implementación C++ (Namespace-Wrap e Introspección `.cpp`)
En el archivo de implementación, encerramos la inclusión del archivo generado de Faust en el namespace pre-declarado, importando las bases de Faust:

```cpp
#include "MiInstrumentoVoice.h"
#include "../core/FaustDefs.h"
#include <unordered_map>

// ── TÉCNICA CLAVE: Envoltura de Namespace ────────────────────────────
namespace mi_instrumento_ns {
    using ::dsp;
    using ::UI;
    using ::Meta;

    #include "../../plugin_instrumentos/kick/kick.cpp" // ruta al cpp generado
}

// Clase auxiliar para capturar las direcciones de memoria de Faust
class VoiceMapUI : public UI {
public:
    std::unordered_map<std::string, float*> pathMap;
    std::string lastPath;

    void declare(float* zone, const char* key, const char* val) override {
        if (std::string(key) == "osc") {
            std::string sVal(val);
            size_t space = sVal.find(' ');
            lastPath = (space != std::string::npos) ? sVal.substr(0, space) : sVal;
            pathMap[lastPath] = zone;
        }
    }

    void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) override {
        if (!lastPath.empty()) { pathMap[lastPath] = zone; lastPath.clear(); }
        else { pathMap[label] = zone; }
    }
    // ... implementar addCheckButton de la misma forma
};

void MiInstrumentoVoice::initialize(double sampleRate) {
    m_sampleRate = sampleRate;
    m_dsp = std::make_unique<mi_instrumento_ns::mydsp>();
    m_dsp->init(static_cast<int>(m_sampleRate));

    // Mapear los punteros de Faust de forma dinámica pero segura en inicialización
    VoiceMapUI mapUI;
    m_dsp->buildUserInterface(&mapUI);

    m_ptrGate  = mapUI.pathMap["/kick/gate"];
    m_ptrPitch = mapUI.pathMap["/kick/pitch"];
}
```

### C. Procesamiento del Bloque de Audio
En `processBlock`, transferimos los valores atómicos de control al DSP y alimentamos el disparo simulando la bajada del gate a `0.0f` tras un bloque de disparo (`1.0f`) para reactivar la envolvente:

```cpp
void MiInstrumentoVoice::processBlock(float* outputBufferL, float* outputBufferR, int numSamples, const float* triggerBuffer) {
    if (!m_dsp) return;

    // 1. Transferencia lock-free al DSP
    if (m_ptrPitch) *m_ptrPitch = m_pitch.load();

    // 2. Control de flancos de disparo (0 -> 1 -> 0)
    bool triggered = false;
    float triggerVel = 1.0f;

    if (triggerBuffer) {
        for (int i = 0; i < numSamples; ++i) {
            if (triggerBuffer[i] > 0.0f) { triggered = true; triggerVel = triggerBuffer[i]; break; }
        }
    } else {
        if (m_triggered.exchange(false)) { triggered = true; triggerVel = m_triggerVelocity.load(); }
    }

    if (triggered) {
        if (m_ptrGate) *m_ptrGate = 1.0f;
        m_gateActive = true;
        m_currentVelocity = triggerVel;
    } else if (m_gateActive) {
        if (m_ptrGate) *m_ptrGate = 0.0f;
        m_gateActive = false;
    }

    // 3. Renderizar y escalar volumen
    alignas(16) float dspOutL[1024];
    alignas(16) float dspOutR[1024];
    float* outputs[2] = { dspOutL, dspOutR };

    int samplesProcessed = 0;
    float volumeScale = m_volume.load() * m_currentVelocity;

    while (samplesProcessed < numSamples) {
        int chunk = std::min(numSamples - samplesProcessed, 1024);
        m_dsp->compute(chunk, nullptr, outputs);

        for (int i = 0; i < chunk; ++i) {
            outputBufferL[samplesProcessed + i] += dspOutL[i] * volumeScale;
            outputBufferR[samplesProcessed + i] += dspOutR[i] * volumeScale;
        }
        samplesProcessed += chunk;
    }
}
```

---

## 4. Registro en el Sintetizador

Para que tu nuevo plugin esté disponible en la máquina y en la web, realiza estos tres pasos finales en `BAZZ_Sintetizador/core/mydsp.cpp`:

1.  **Añadir al Makefile/Build system**: Agrega el archivo `.cpp` de tu wrapper en `CMakeLists.txt` bajo la variable `BAZZ_VOICES_SOURCES`.
2.  **Registrar en el VoiceFactory**: Registra el tipo en el constructor de `mydsp::mydsp()`:
    ```cpp
    #include "../voices/MiInstrumentoVoice.h"
    // ...
    m_factory.registerVoice<MiInstrumentoVoice>();
    ```
3.  **Vincular a la UI de Faust**: Declara los parámetros del instrumento vinculados a los índices del buffer `fHslider` en `mydsp::buildUserInterface()` y enlázalos en `mydsp::updateParameters()`.
