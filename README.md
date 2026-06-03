# BAZZ Algorithmic Techno Station — Documentación Técnica de Arquitectura

## AUTOR: Santiago Alexander Zambrano Chicunque 

> **FaustSynthServer** · Estación de ritmos algorítmica de baja latencia  
> Motor DSP en C++17 · Faust · RtAudio · liblo OSC · uWebSockets

---

## Índice

1. [Visión General del Sistema](#1-visión-general-del-sistema)
2. [Diagrama de Arquitectura Global](#2-diagrama-de-arquitectura-global)
3. [Módulo Core — Dominio del Sintetizador](#3-módulo-core--dominio-del-sintetizador)
4. [Motor DSP — Pipeline de Audio (Faust + RtAudio)](#4-motor-dsp--pipeline-de-audio-faust--rtaudio)
5. [Diseño del Buffer de Audio](#5-diseño-del-buffer-de-audio)
6. [Arquitectura Acústica del Sintetizador](#6-arquitectura-acústica-del-sintetizador)
7. [Sistema de Reloj Maestro (MasterClock)](#7-sistema-de-reloj-maestro-masterclock)
8. [Conexiones OSC — Protocolo y Rutas](#8-conexiones-osc--protocolo-y-rutas)
9. [Vista desde Raspberry Pi (Linux / ALSA)](#9-vista-desde-raspberry-pi-linux--alsa)
10. [Vista desde Windows (WASAPI)](#10-vista-desde-windows-wasapi)
11. [Sincronización de Hardware Externo (GPIO Clock Sync)](#11-sincronización-de-hardware-externo-gpio-clock-sync)
12. [Sistema de Estado — Presets y Automatización](#12-sistema-de-estado--presets-y-automatización)
13. [Flujo de Arranque Completo](#13-flujo-de-arranque-completo)
14. [Tablas de Parámetros](#14-tablas-de-parámetros)
15. [Dependencias y Compilación](#15-dependencias-y-compilación)

---

## 1. Visión General del Sistema

**FaustSynthServer** es un servidor de síntesis de audio en tiempo real, inspirado en la TR-808 de Roland, diseñado como una caja de ritmos algorítmica con síntesis procedural. El sistema está construido sobre tres pilares tecnológicos:

| Pilar | Tecnología | Función |
|---|---|---|
| **Síntesis DSP** | Faust → C++ transpilado | Motor de síntesis de audio |
| **E/S de Audio** | RtAudio (ALSA / WASAPI) | Interfaz con el hardware de audio |
| **Control Remoto** | liblo OSC + uWebSockets | Comunicación bidireccional en red |

El servidor puede ejecutarse en **modo headless** (sin interfaz gráfica) sobre una Raspberry Pi 4/5, actuando como un instrumento de hardware autónomo, o sobre Windows con WASAPI de ultra-baja latencia.

---

## 2. Diagrama de Arquitectura Global

```mermaid
graph TB
    subgraph EXTERNOS["Controladores Externos"]
        TOUCHOSC["TouchOSC\n(iPad / Android)"]
        PYTHON["Script Python\npython-osc"]
        NODERED["Node-RED\n/ PureData"]
        HARDWARE["Hardware Externo\n(Eurorack / Korg Volca)"]
        WEB["Navegador Web\n(WebSocket UI)"]
    end

    subgraph RED["Red Local UDP / WebSocket"]
        OSC_UDP["UDP :8000\n(OSC Messages)"]
        WS_PORT["TCP :9001\n(WebSockets)"]
    end

    subgraph SERVIDOR["FaustSynthServer — Proceso Principal (C++)"]
        direction TB

        subgraph OSC_LAYER["Capa OSC  [osc/OscServer.cpp]"]
            OSC_SERVER["OscServer\n(lo_server_thread)"]
            HTTP_SERVER["HttpServer\n(uWebSockets)"]
        end

        subgraph CORE_LAYER["Capa Core  [core/]"]
            SYNTH["Synthesizer\n(repositorio de parámetros)"]
            MASTERCLOCK["MasterClock\n(BPM atómico)"]
            PARAM["Parameter\nstd::atomic<float>"]
        end

        subgraph AUDIO_LAYER["Capa Audio  [audio/]"]
            FAUSTUI["FaustMapUI\n(puente zone→Parameter)"]
            RTAUDIO["RtAudioBackend\n(audioCallback)"]
            FAUSTDSP["Faust DSP\n(untitled.cpp — motor C++)"]
        end

        subgraph STATE_LAYER["Capa Estado  [state/]"]
            PRESET["PresetManager\n(preset.json)"]
            RECORDER["AutomationRecorder"]
        end
    end

    subgraph HARDWARE_AUDIO["Hardware de Audio"]
        DAC_PI["DAC ALSA\n(Pi: bcm2835 / USB Audio)"]
        DAC_WIN["DAC WASAPI\n(Windows: Realtek / ASIO)"]
        GPIO_PIN["GPIO 17 (Pin 11)\n(Entrada de voltaje)"]
    end

    TOUCHOSC -->|"OSC /kick/vol 0.8"| OSC_UDP
    PYTHON -->|"OSC /master/bpm 140"| OSC_UDP
    NODERED --> OSC_UDP
    WEB -->|"JSON params"| WS_PORT
    HARDWARE -->|"Gate 3.3V / Sync Out"| GPIO_PIN

    OSC_UDP --> OSC_SERVER
    WS_PORT --> HTTP_SERVER
    OSC_SERVER -->|"param->setValue()"| SYNTH
    HTTP_SERVER -->|"param->setValue()"| SYNTH
    SYNTH --- PARAM
    SYNTH --- MASTERCLOCK

    GPIO_PIN -->|"flanco de subida"| RTAUDIO
    RTAUDIO -->|"syncPulse(t_ms)"| MASTERCLOCK
    MASTERCLOCK -->|"getBpm()"| FAUSTUI
    FAUSTUI -->|"updateDSPValues()\n*zone = param->getValue()"| FAUSTDSP
    RTAUDIO -->|"compute(N, in, out)"| FAUSTDSP

    PRESET -->|"loadPreset()"| SYNTH
    SYNTH -->|"savePreset()"| PRESET
    RECORDER -->|"snapshot parámetros"| SYNTH

    FAUSTDSP -->|"float[L/R][256]"| RTAUDIO
    RTAUDIO -->|"interleaved float32"| DAC_PI
    RTAUDIO -->|"interleaved float32"| DAC_WIN
```

---

## 3. Módulo Core — Dominio del Sintetizador

### Diagrama de clases del Core

```mermaid
classDiagram
    class Parameter {
        -string m_path
        -float m_min
        -float m_max
        -atomic~float~ m_value
        -string m_label
        +getValue() float
        +setValue(float val)
        +getPath() string
        +getMin() float
        +getMax() float
    }

    class MasterClock {
        -atomic~float~ m_bpm
        -atomic~float~ m_externalBpm
        -atomic~double~ m_lastExternalPulseMs
        -double m_lastPulseTime
        +syncPulse(double ts_ms)
        +setBpm(float bpm)
        +getBpm() float
        +isExternalClockActive() bool
        +getExternalBpm() float
    }

    class Synthesizer {
        -unique_ptr~MasterClock~ m_clock
        -map~string, shared_ptr~Parameter~~ m_parameters
        +addParameter(shared_ptr~Parameter~)
        +getParameter(string path) Parameter*
        +getClock() MasterClock*
        +getAllParameters() map
    }

    Synthesizer "1" --> "1" MasterClock : owns
    Synthesizer "1" --> "*" Parameter : owns (map by path)
```

### Lógica lock-free de parámetros

El diseño garantiza **cero bloqueos** entre el hilo de audio (tiempo real) y los hilos de red (OSC / WebSocket):

```
Hilo OSC/WebSocket:              Hilo de Audio (RtAudio callback):
┌──────────────────┐             ┌──────────────────────────────┐
│ param->setValue()│             │ updateDSPValues():           │
│                  │             │   *zone = param->getValue()  │
│ m_value.store(v, │ ─ atómica ─▶│   m_value.load(             │
│  memory_order_   │             │    memory_order_acquire)     │
│  release)        │             │                              │
└──────────────────┘             └──────────────────────────────┘
```

**Garantías de memoria C++17:**
- `store(..., memory_order_release)` → toda escritura anterior queda visible
- `load(..., memory_order_acquire)` → toda lectura posterior ve los cambios

---

## 4. Motor DSP — Pipeline de Audio (Faust + RtAudio)

### Diagrama de flujo del callback de audio

```mermaid
flowchart TD
    START(["RtAudio llama audioCallback()\ncada ~5.33 ms @ 48kHz/256"]) --> A

    A["¿Hay inputBuffer?\n(señal analógica de reloj)"] -->|Sí| B
    A -->|No| E

    B["Escanear muestra por muestra\nfor i in 0..nBufferFrames"] --> C
    C{"currentSample > 0.4f\nAND lastSample ≤ 0.4f\n(flanco de subida)"}
    C -->|Sí| D["synth->getClock()->syncPulse(t_ms)\nSincronización analógica de BPM"]
    C -->|No| B2["Siguiente muestra"]
    D --> E
    B2 --> B

    E{"¿Emulador de reloj\nactivo?\n/emulator/active > 0.5"}
    E -->|Sí| F["interval_ms = 60000 / emuBpm\n¿t_actual - t_ultimo ≥ interval_ms?"]
    F -->|Sí| G["synth->getClock()->syncPulse(t_ms)\nSincronización lógica de BPM"]
    F -->|No| H
    G --> H
    E -->|No| H

    H["ui->updateDSPValues()\nSincronizar parámetros atómicos\nal espacio de memoria del DSP"] --> I

    I["faust_dsp->compute(256, nullptr, faustOut)\nEjecutar síntesis DSP\nFaust genera outL[256] + outR[256]"] --> J

    J["Intercalar para RtAudio:\nfor i: out[2*i] = outL[i]\n       out[2*i+1] = outR[i]"] --> K

    K(["Retorna 0 → RtAudio\nenvía al DAC"])
```

### Configuración de stream

| Parámetro | Valor | Justificación |
|---|---|---|
| **Sample Rate** | 48,000 Hz | Estándar profesional, compatible con Pi/USB |
| **Buffer Size** | 256 frames | ~5.33 ms de latencia, balance CPU/latencia |
| **Formato** | RTAUDIO_FLOAT32 | Precisión de 32 bits, rango ±1.0 normalizado |
| **Canales salida** | 2 (Stereo L/R) | Definido por Faust `getNumOutputs()` |
| **Canales entrada** | 1 (Mono) | Detección de voltaje de reloj analógico |
| **API Audio (Linux)** | ALSA (`__LINUX_ALSA__`) | Nativo del kernel, baja latencia |
| **API Audio (Windows)** | WASAPI (`__WINDOWS_WASAPI__`) | Ultra-baja latencia, exclusivo |

---

## 5. Diseño del Buffer de Audio

### Problema: Intercalado vs No-intercalado

RtAudio y Faust usan formatos de buffer opuestos. La solución implementa buffers intermedios estáticos:

```
Faust (no intercalado):          RtAudio (intercalado):
outL[] = [L0, L1, L2, ... L255]  out[] = [L0, R0, L1, R1, ... L255, R255]
outR[] = [R0, R1, R2, ... R255]
         ↓  conversión en callback  ↓
         for i in 0..255:
             out[2*i]   = outL[i]
             out[2*i+1] = outR[i]
```

### Memoria del buffer

```
outL[4096]  →  4096 × 4 bytes = 16 KB  (estático, evita heap allocation en RT)
outR[4096]  →  4096 × 4 bytes = 16 KB
faustOut[2] →  punteros a outL y outR
Total stack   →  ~32 KB por callback
```

> **Diseño de tiempo real**: Los buffers son `static` dentro del callback — nunca se usa `new`/`malloc` en el hilo de audio, cumpliendo las reglas de programación de tiempo real (RTAI/POSIX RT).

### Latencia total estimada

```
Latencia de buffer   = bufferFrames / sampleRate
                     = 256 / 48000
                     = 5.33 ms

Latencia total estimada (sistema):
  ┌─────────────────────────────────────┐
  │ Cómputo DSP Faust  ≈  1-2 ms       │
  │ Buffer RtAudio     ≈  5.33 ms      │
  │ Driver ALSA/WASAPI ≈  0.5-2 ms     │
  │ DAC hardware       ≈  0.1 ms       │
  │ ──────────────────────────────────  │
  │ TOTAL              ≈  7-10 ms      │
  └─────────────────────────────────────┘
```

---

## 6. Arquitectura Acústica del Sintetizador

El sintetizador implementa **6 voces de síntesis independientes**, cada una con su propio modelo acústico:

### Mapa de voces y técnicas de síntesis

```mermaid
graph LR
    subgraph VOCES["Voces del Sintetizador"]
        KICK["🥁 Kick\n(Bombo)"]
        SNARE["🥁 Snare\n(Caja)"]
        HAT["🎵 Hat\n(Platillo)"]
        BASS["🎸 Bass\n(Bajo Waveguide)"]
        SYN1["🌊 Syn1\n(Oscilador AM)"]
        SYN2["🔊 Syn2\n(FDN Reverb Synth)"]
    end

    subgraph TECNICAS["Técnicas DSP"]
        FM["FM Synthesis\n+ Sweep exponencial"]
        NOISE["Ruido filtrado\n+ Body resonance"]
        NOISE2["Ruido metálico\n6 osciladores primo"]
        WG["Waveguide Synthesis\n(Karplus-Strong extendido)"]
        AM["Síntesis AM\n+ LFO modulación"]
        FDN["FDN — Feedback Delay Network\n(reverberación procedural)"]
    end

    KICK --> FM
    SNARE --> NOISE
    HAT --> NOISE2
    BASS --> WG
    SYN1 --> AM
    SYN2 --> FDN
```

### Matemática de síntesis por voz

#### 🥁 Bombo (Kick) — FM + Sweep

```
Frecuencia instantánea:
  f(t) = f_tune + sweep × e^(-t / dec)

Donde:
  f_tune  = frecuencia base [Hz], controlada por /kick/tune
  sweep   = barrido de frecuencia [Hz], controlada por /kick/sweep
  dec     = tiempo de decaimiento [s], controlada por /kick/dec
  t       = tiempo desde el trigger [s]

Señal de salida:
  y(t) = A(t) × sin(2π ∫f(t)dt)

Envolvente de amplitud:
  A(t) = e^(-t / dec_amp)
```

#### 🥁 Caja (Snare) — Cuerpo + Resorte

```
Señal total:
  y(t) = mix × y_body(t) + (1-mix) × y_spring(t)

Cuerpo (resonador tonal):
  y_body(t) = sin(2π × f_body × t) × e^(-t / dec_cuerpo)

Resorte (ruido filtrado):
  y_spring(t) = BPF[f=freq, Q=q]( noise(t) ) × e^(-t / dec_resorte)
  BPF aplicado con HP adicional a f=hp para eliminar sub-graves
```

#### 🎸 Bajo Waveguide — Karplus-Strong Extendido

```
Síntesis por guía de onda digital:
  y[n] = 0.5 × (y[n-L] + y[n-L-1]) × decay_factor

Donde:
  L = round(sampleRate / f_nota)   (longitud del delay en muestras)
  f_nota = A4 × 2^((nota - 69) / 12)   (afinación MIDI → Hz)
  decay_factor = e^(-1 / (dec × sampleRate))

Detune (coro):
  Voz_1: L_1 = L
  Voz_2: L_2 = L × (1 + detune)
  Salida = Voz_1 + Voz_2 (stereo spread)
```

#### 🔊 Syn2 — FDN (Feedback Delay Network)

```
Red de delays con retroalimentación matricial:

  x[n] = input[n] + H × y[n-1]

Donde H es la matriz de Hadamard normalizada (N×N, N=4 o 8):
  H_4 = (1/2) × [[1,1,1,1],[1,-1,1,-1],[1,1,-1,-1],[1,-1,-1,1]]

Cada canal i tiene un delay L_i = disp × primo_i muestras
La densidad modal del FDN determina la calidad de reverberación.
```

---

## 7. Sistema de Reloj Maestro (MasterClock)

### Diagrama de flujo del MasterClock

```mermaid
flowchart TD
    START(["Nueva fuente de tempo"]) --> A

    A{"¿Origen?"}
    A -->|"Señal analógica\n(GPIO / línea de audio)"| B
    A -->|"Mensaje OSC\n/master/bpm"| F
    A -->|"Emulador interno\n/emulator/active"| G

    B["Detectar flanco de subida\nen señal de voltaje\n(threshold: 0.4f normalizado)"]
    B --> C["Calcular delta_ms:\ndelta_ms = t_actual - t_anterior"]
    C --> D{"10 ms < delta_ms < 3000 ms\n(20 BPM a 6000 BPM)\n¿Rango válido?"}
    D -->|No| DISCARD["Descartar pulso\n(ruido / glitch)"]
    D -->|Sí| E

    E["Calcular BPM crudo:\nnew_bpm = 60000 / delta_ms"]
    E --> E2["Suavizado LPF exponencial:\nsmoothed = prev × 0.7 + new_bpm × 0.3"]
    E2 --> STORE["m_bpm.store(smoothed)\nm_externalBpm.store(smoothed)\nm_lastExternalPulseMs.store(t_actual)"]

    F["Validar rango:\n20 < bpm < 999"] --> F2{"¿Hay reloj externo\nactivo en últimos 2000 ms?"}
    F2 -->|No| STORE
    F2 -->|Sí| IGNORE["Ignorar — prioridad\nreloj externo hardware"]

    G["Calcular intervalo:\ninterval_ms = 60000 / emu_bpm"]
    G --> G2["Generar pulso\ncada interval_ms"]
    G2 --> STORE

    STORE --> FAUSTUI["FaustMapUI.updateDSPValues()\nSincronizar /master/bpm → *zone_bpm"]
```

### Matemática del filtro de suavizado de BPM

El filtro de primer orden (IIR) aplicado al BPM detectado:

```
Función de transferencia (dominio Z):
  H(z) = α / (1 - (1-α)z⁻¹)

Con α = 0.3 (coeficiente de suavizado):
  BPM_suavizado[n] = 0.7 × BPM_suavizado[n-1] + 0.3 × BPM_crudo[n]

Respuesta al escalón (convergencia):
  Después de N muestras (pulsos):
  BPM_suavizado[N] = BPM_final × (1 - 0.7^N)

  N=5  pulsos → 83.2% convergencia
  N=10 pulsos → 97.2% convergencia
  N=20 pulsos → 99.9% convergencia

Tiempo de respuesta a 140 BPM (pulso cada 428 ms):
  5 pulsos × 428 ms ≈ 2.1 segundos para estabilizar al 83%
```

### Detección de reloj externo activo

```
isExternalClockActive():
  now_ms = steady_clock::now() [ms]
  return (now_ms - m_lastExternalPulseMs) < 2000.0

Ventana de timeout: 2 segundos
→ Si no llega pulso en 2s, se considera reloj perdido
→ OSC /master/bpm vuelve a tener efecto
```

---

## 8. Conexiones OSC — Protocolo y Rutas

### Diagrama de flujo del servidor OSC

```mermaid
flowchart TD
    CLIENT(["Cliente OSC\n(TouchOSC / Python / PD)"]) -->|"UDP Packet\nPort 8000"| RECV

    RECV["lo_server_thread\nrecibe mensaje UDP"] --> PARSE

    PARSE["Parsear mensaje OSC:\n- path: string (ej: /kick/vol)\n- types: string (ej: 'f')\n- argv: array de argumentos"] --> ROUTE

    ROUTE{"Ruta del mensaje OSC"}

    ROUTE -->|"/clock/sync"| CLOCK["synth->getClock()->syncPulse(t_ms)\nSincronización de reloj externo"]
    ROUTE -->|"/master/bpm f"| BPM["clock->setBpm(argv[0]->f)\nEstablecer BPM manual"]
    ROUTE -->|"/preset/save s"| SAVE["presetMgr->savePreset(filename)"]
    ROUTE -->|"/preset/load s"| LOAD["presetMgr->loadPreset(filename)"]
    ROUTE -->|"/automation/start"| AUTO_S["recorder->startRecording()"]
    ROUTE -->|"/automation/stop"| AUTO_E["recorder->stopRecording()"]
    ROUTE -->|"/audio/device i"| AUDIO_D["audioBackend->changeDevice(id)"]
    ROUTE -->|"Cualquier otra\nruta registrada"| GENERIC

    GENERIC["param = synth->getParameter(path)"] --> CHECK{"¿Parámetro\nexiste?"}
    CHECK -->|No| WARN["Log warning:\nRuta desconocida"]
    CHECK -->|Sí| SET["param->setValue(argv[0]->f)\n(lock-free, atómico)"]

    SET --> NEXT["Próximo audioCallback()\nlee el valor actualizado"]
```

### Tabla completa de rutas OSC

#### Globales / Master

| Ruta OSC | Tipo | Rango | Descripción |
|---|---|---|---|
| `/master/bpm` | `f` | 20.0 – 999.0 | Tempo maestro en BPM |
| `/master/accent` | `f` | 0.0 – 1.0 | Acentuación global de patrones |
| `/master/nota` | `f` | 0 – 127 | Nota raíz MIDI del patrón |
| `/master/groove` | `f` | 0 – 6 | Selector de patrón algorítmico |
| `/clock/sync` | `(vacío)` | — | Pulso de reloj externo (BPM auto-detect) |

#### Bombo (Kick)

| Ruta OSC | Tipo | Rango | Descripción |
|---|---|---|---|
| `/kick/vol` | `f` | 0.0 – 1.0 | Volumen |
| `/kick/tune` | `f` | 0.0 – 1.0 | Afinación base |
| `/kick/dec` | `f` | 0.01 – 1.0 | Tiempo de decaimiento |
| `/kick/sweep` | `f` | 0 – 500 | Barrido de frecuencia (Hz) |
| `/kick/mix` | `f` | 0.0 – 1.0 | Mix body/tone |
| `/kick/comp_thresh` | `f` | 0.0 – 1.0 | Umbral del compresor interno |
| `/kick/comp_ratio` | `f` | 1.0 – 10.0 | Ratio de compresión |
| `/kick/groove` | `f` | 0 – 6 | Patrón rítmico del kick |
| `/kick/swing` | `f` | 0 – 100 | Swing / shuffle |

#### Caja (Snare)

| Ruta OSC | Tipo | Rango | Descripción |
|---|---|---|---|
| `/snare/vol` | `f` | 0.0 – 1.0 | Volumen |
| `/snare/dec_cuerpo` | `f` | 0.01 – 1.0 | Decay del cuerpo tonal |
| `/snare/dec_resorte` | `f` | 0.01 – 1.0 | Decay del resorte (ruido) |
| `/snare/freq` | `f` | 100 – 5000 | Frecuencia de resonancia cuerpo |
| `/snare/q` | `f` | 0.1 – 20.0 | Factor Q del filtro |
| `/snare/hp` | `f` | 20 – 500 | Highpass del ruido |
| `/snare/tune` | `f` | -24 – +24 | Afinación en semitonos |
| `/snare/drive` | `f` | 0.0 – 10.0 | Saturación / distorsión |

#### Platillo (Hat)

| Ruta OSC | Tipo | Rango | Descripción |
|---|---|---|---|
| `/hat/vol` | `f` | 0.0 – 1.0 | Volumen |
| `/hat/dec` | `f` | 0.001 – 2.0 | Decay |
| `/hat/tune` | `f` | -1.0 – 1.0 | Afinación del banco de osciladores |
| `/hat/cutoff` | `f` | 500 – 20000 | Frecuencia de corte del filtro |
| `/hat/mix` | `f` | 0.0 – 1.0 | Mix closed/open |
| `/hat/drive` | `f` | 0.0 – 1.0 | Saturación |

#### Bajo Waveguide (Bass)

| Ruta OSC | Tipo | Rango | Descripción |
|---|---|---|---|
| `/bass/vol` | `f` | 0.0 – 1.0 | Volumen |
| `/bass/nota` | `f` | 0 – 127 | Nota MIDI base |
| `/bass/dec` | `f` | 0.01 – 2.0 | Decaimiento del waveguide |
| `/bass/detune` | `f` | 0.0 – 0.5 | Detune para efecto coro |
| `/bass/intervalo` | `f` | -24 – +24 | Intervalo armónico |
| `/bass/drive` | `f` | 0.0 – 2.0 | Saturación armónica |
| `/bass/lfo` | `f` | 0.0 – 1.0 | Profundidad del LFO |

#### Sintetizador FDN (Syn2)

| Ruta OSC | Tipo | Rango | Descripción |
|---|---|---|---|
| `/syn2/vol` | `f` | 0.0 – 1.0 | Volumen |
| `/syn2/dec` | `f` | 0.001 – 2.0 | Decay del ataque |
| `/syn2/disp` | `f` | 0.0 – 1.0 | Dispersión modal del FDN |
| `/syn2/lfo_f` | `f` | 0.1 – 20.0 | Frecuencia del LFO |
| `/syn2/lfo_p` | `f` | 0.0 – 1.0 | Fase del LFO |
| `/syn2/comp_th` | `f` | -60 – 0 | Umbral del compresor (dBFS) |

#### Control del sistema

| Ruta OSC | Tipo | Descripción |
|---|---|---|
| `/preset/save` | `s` | Guardar preset a archivo |
| `/preset/load` | `s` | Cargar preset desde archivo |
| `/automation/start` | — | Iniciar grabación de automatización |
| `/automation/stop` | — | Detener grabación |
| `/audio/device` | `i` | Cambiar dispositivo de audio (ID entero) |
| `/emulator/active` | `f` | 0=off, 1=on — emulador de reloj interno |
| `/emulator/bpm` | `f` | BPM del emulador (60–240) |

---

## 9. Vista desde Raspberry Pi (Linux / ALSA)

### Diagrama de capas del sistema en Raspberry Pi

```mermaid
graph TB
    subgraph RPI["Raspberry Pi 4/5 (AArch64 Linux)"]
        direction TB

        subgraph USERSPACE["Espacio de Usuario"]
            APP["FaustSynthServer\n(proceso C++)"]
            PYBRIDGE["pi_gpio_sync.py\n(puente GPIO→OSC)"]
        end

        subgraph KERNEL["Espacio de Kernel"]
            ALSA_K["Subsistema ALSA\n(snd_bcm2835 / snd_usb_audio)"]
            GPIO_K["Subsistema GPIO\n(gpiozero / sysfs)"]
            NET_K["Stack UDP/IP\n(loopback 127.0.0.1)"]
        end

        subgraph HARDWARE_PI["Hardware"]
            JACK35["Jack 3.5mm\n(bcm2835 Headphones)"]
            USBDAC["USB DAC / Interfaz\n(snd_usb_audio)"]
            GPIO17["GPIO 17 (Pin 11)\n(Entrada de voltaje)"]
            HDMIOUT["HDMI Audio\n(bcm2835 HDMI 1)"]
        end
    end

    subgraph RED_PI["Red Local"]
        LAN["Ethernet / WiFi\n192.168.x.x:8000"]
    end

    APP -->|"ALSA openStream()\n48kHz / 256 frames"| ALSA_K
    PYBRIDGE -->|"gpiozero InputDevice\ninterrupt flanco↑"| GPIO_K
    PYBRIDGE -->|"lo_send() OSC\n/clock/sync"| NET_K
    NET_K -->|"UDP loopback"| APP

    ALSA_K --> JACK35
    ALSA_K --> USBDAC
    ALSA_K --> HDMIOUT
    GPIO_K --> GPIO17

    LAN -->|"OSC remoto"| APP
```

### Flags de compilación para Raspberry Pi 4

```cmake
# CMakeLists.txt — Sección Linux (AArch64)
-O3            # Optimización máxima del compilador
-ffast-math    # Aritmética de punto flotante relajada (IEEE 754 flexible)
-mcpu=cortex-a72   # Cortex-A72 = CPU del RPi 4 (1.5/1.8 GHz)
-mtune=cortex-a72  # Ajuste de scheduling a la microarquitectura
-mfpu=neon-fp-armv8  # Habilitar extensiones SIMD NEON (vectorización)
-ftree-vectorize     # Permitir auto-vectorización por el compilador
-funroll-loops       # Desenrollar loops (mejora throughput DSP)
```

**Impacto de -mcpu=cortex-a72 + NEON**: El compilador puede vectorizar bucles de audio procesando **4 muestras float32 en paralelo** por instrucción SIMD, cuadruplicando el throughput de cálculo.

### Configuración de servicio systemd (headless)

```
Arranque de la Raspberry Pi:
         │
         ▼
  systemd target: multi-user
         │
         ├─── synthesizer.service
         │         │
         │         └── FaustSynthServer [device_id]
         │                  │
         │                  ├── Carga preset.json
         │                  ├── Abre stream ALSA @ 48kHz/256
         │                  └── Escucha OSC :8000
         │
         └─── synthesizer-sync.service (requiere synthesizer.service)
                   │
                   └── pi_gpio_sync.py
                            │
                            ├── Monitoriza GPIO 17 (interrupts)
                            └── Envía /clock/sync por UDP loopback
```

### Dispositivos de audio ALSA disponibles

| ID | Dispositivo | Canales | Latencia típica | Recomendado para |
|---|---|---|---|---|
| `[0]` | bcm2835 HDMI 1 | Out: 2 | ~10 ms | Monitores por HDMI |
| `[1]` | Headphones (3.5mm) | Out: 2 | ~8 ms | Auriculares / mezcla |
| `[2]` | USB Audio Device | In/Out: 2 | ~5 ms | **Producción / DAW** |

---

## 10. Vista desde Windows (WASAPI)

### Diagrama de capas en Windows

```mermaid
graph TB
    subgraph WIN["Windows 10/11 (x86-64)"]
        direction TB

        subgraph PROC["Proceso: FaustSynthServer.exe"]
            MAIN_WIN["main.cpp\n(hilo principal + consola)"]
            OSC_WIN["OscServer\n(hilo lo_server_thread)"]
            AUDIO_WIN["RtAudioBackend\n(hilo de audio WASAPI)"]
            WS_WIN["HttpServer\n(hilo uWebSockets)"]
        end

        subgraph DLLS["DLLs requeridas (junto al .exe)"]
            LO_DLL["liblo.dll\n(OSC)"]
            RT_DLL["librtaudio.dll\n(WASAPI wrapper)"]
            GCC_DLL["libgcc_s_seh-1.dll"]
            STD_DLL["libstdc++-6.dll"]
            PT_DLL["libwinpthread-1.dll"]
        end

        subgraph WASAPI["WASAPI (Windows Audio Session API)"]
            WASAPI_EX["Modo Exclusivo\n(IAudioClient exclusive)"]
            WASAPI_SH["Modo Compartido\n(IAudioClient shared)"]
        end

        subgraph HW_WIN["Hardware"]
            REALTEK["Realtek HD Audio\n(Altavoces / Jack)"]
            ASIO_IF["Interfaz ASIO\n(Focusrite / RME)"]
        end
    end

    subgraph NET_WIN["Red"]
        UDP_WIN["UDP :8000\n(TouchOSC / Python)"]
        WS_WIN2["TCP :9001\n(Navegador Web)"]
    end

    MAIN_WIN --> OSC_WIN
    MAIN_WIN --> AUDIO_WIN
    MAIN_WIN --> WS_WIN
    AUDIO_WIN --> WASAPI_EX
    AUDIO_WIN --> WASAPI_SH
    WASAPI_EX --> REALTEK
    WASAPI_SH --> REALTEK
    WASAPI_EX --> ASIO_IF

    UDP_WIN --> OSC_WIN
    WS_WIN2 --> WS_WIN
    PROC --> LO_DLL
    PROC --> RT_DLL
```

### Modelo de hilos en Windows

```
Proceso FaustSynthServer.exe
├── Hilo Principal (main thread)
│     • Bucle de comandos de consola (stdin)
│     • Carga/guarda preset.json
│     • Manejo de señales SIGINT/SIGTERM
│
├── Hilo de Audio (RtAudio / WASAPI interno)
│     • Prioridad: THREAD_PRIORITY_TIME_CRITICAL
│     • Callback cada 5.33 ms (256 frames @ 48kHz)
│     • Lee parámetros atómicos → ejecuta Faust DSP → envía a DAC
│
├── Hilo OSC (lo_server_thread)
│     • Escucha UDP :8000
│     • Parsea mensajes OSC
│     • Actualiza parámetros atómicos (lock-free)
│
└── Hilo WebSocket (uWebSockets + libuv)
      • Escucha TCP :9001
      • Sirve interfaz web HTML
      • Despacha eventos JSON → parámetros
```

### Flags de compilación Windows (MSYS2 / GCC)

```cmake
# Para MSYS2/GCC en Windows:
-O3 -ffast-math
# Definiciones para activar el backend WASAPI:
__WINDOWS_WASAPI__
# Definiciones para uWebSockets:
UWS_NO_ZLIB
LIBUS_USE_LIBUV
LIBUS_NO_SSL
```

### Comandos de consola disponibles

```
synth-server> list               → Listar dispositivos de audio WASAPI
synth-server> set <id>           → Cambiar dispositivo (hot-swap sin interrumpir audio)
synth-server> emu on             → Activar emulador de reloj interno
synth-server> emu off            → Desactivar emulador de reloj
synth-server> emu bpm <valor>    → Establecer tempo del emulador (ej: emu bpm 128.5)
synth-server> status             → Ver BPM activo, estado del emulador, dispositivo
synth-server> exit               → Guardar preset.json y salir limpiamente
```

---

## 11. Sincronización de Hardware Externo (GPIO Clock Sync)

### Diagrama completo de la cadena de sincronización analógica

```mermaid
flowchart LR
    subgraph HW_EXT["Hardware Externo"]
        EURORACK["Sintetizador Eurorack\n(Gate: 5V - 12V)"]
        VOLCA["Korg Volca / PO\n(Sync: 3.3V - 5V)"]
        SEQ["Secuenciador MIDI\n(Clock Out)"]
    end

    subgraph PROTECCION["Circuito de Protección"]
        DIV["Divisor de tensión:\nR1=10kΩ (serie)\nR2=4.7kΩ (a GND)\nV_out = V_in × 4.7/(10+4.7)\n≈ 0.32 × V_in\n→ 12V → ~3.84V ✓"]
    end

    subgraph RPI_HW["Raspberry Pi GPIO"]
        PIN11["Pin 11 (GPIO 17)\nEntrada digital 3.3V MAX"]
        PIN9["Pin 9 (GND)\nReferencia de masa"]
    end

    subgraph SOFTWARE["Software (Python)"]
        GPIOZERO["gpiozero InputDevice\ngpio17.when_activated\n(interrupt flanco ↑)"]
        OSCPY["python-osc\nlo_send('/clock/sync')\nUDP → 127.0.0.1:8000"]
    end

    subgraph CPPSYN["C++ Synthesizer"]
        OSCRECV["OscServer\nrecibe /clock/sync"]
        MASTERCLOCK2["MasterClock\nsyncPulse(t_ms)"]
        BPM_UPDATE["BPM actualizado\natómicamente"]
    end

    EURORACK -->|"5-12V Gate"| PROTECCION
    VOLCA -->|"3.3-5V Sync"| PIN11
    PROTECCION --> PIN11
    PIN11 -->|"Flanco ↑"| GPIOZERO
    GPIOZERO -->|"UDP loopback\n< 1ms"| OSCPY
    OSCPY --> OSCRECV
    OSCRECV --> MASTERCLOCK2
    MASTERCLOCK2 --> BPM_UPDATE
```

### Cálculo del divisor de tensión para protección GPIO

```
Divisor resistivo para señales Eurorack (hasta 12V):

        V_in ─── R1 (10kΩ) ─── V_out ─── R2 (4.7kΩ) ─── GND

Formula:
  V_out = V_in × R2 / (R1 + R2)
  V_out = V_in × 4700 / (10000 + 4700)
  V_out = V_in × 0.3197

Casos de uso:
  V_in = 5V  (Volca)   → V_out = 1.60V  ✓ (seguro)
  V_in = 8V  (Eurorack)→ V_out = 2.56V  ✓ (seguro)
  V_in = 12V (Eurorack)→ V_out = 3.84V  ⚠️ (ligeramente alto)

Para 12V se recomienda:
  R1 = 15kΩ, R2 = 4.7kΩ → V_out = 12 × 0.238 = 2.86V ✓

Umbral de detección en el software:
  currentSample > 0.4f  (normalizado: 0.4 × V_max_ADC)
  Con V_max = 3.3V → umbral físico ≈ 1.32V
```

### Latencia de la cadena de sincronización

```
Cadena completa de sincronización:

  Pulso físico de clock
        │
        │  ~0.1 ms  (tiempo de rise del gate)
        ▼
  Interrupción GPIO (gpiozero)
        │
        │  ~0.5 ms  (latencia del kernel Linux GPIO)
        ▼
  Callback Python when_activated()
        │
        │  ~0.2 ms  (construcción y envío del paquete OSC)
        ▼
  Stack UDP loopback (127.0.0.1)
        │
        │  ~0.1 ms  (loopback es prácticamente instantáneo)
        ▼
  OscServer.genericHandler()
        │
        │  ~0.05 ms (atomic store del nuevo BPM)
        ▼
  Próximo audioCallback() (RtAudio)
        │
        │  0 – 5.33 ms (espera al próximo buffer de 256 frames)
        ▼
  Faust DSP con BPM actualizado

  LATENCIA TOTAL: ~1 ms + 0-5.33 ms de jitter de buffer
  LATENCIA PERCIBIDA: < 6 ms (imperceptible musicalmente)
```

---

## 12. Sistema de Estado — Presets y Automatización

### Diagrama de flujo del PresetManager

```mermaid
flowchart TD
    INIT["Arranque del servidor"] --> LOAD_CHECK{"¿Existe\npreset.json?"}
    LOAD_CHECK -->|Sí| LOAD_FILE["Leer JSON\nnlohmann::json"]
    LOAD_CHECK -->|No| DEFAULT["Usar valores\npor defecto de Faust"]

    LOAD_FILE --> ITER["Para cada clave/valor\nen el JSON:"]
    ITER --> FIND{"synth->getParameter(path)\n¿Existe?"}
    FIND -->|Sí| SET_P["param->setValue(value)\n(lock-free)"]
    FIND -->|No| SKIP["Ignorar\n(parámetro obsoleto)"]
    SET_P --> ITER
    SKIP --> ITER

    SIGINT["SIGINT / SIGTERM\n(Ctrl+C o systemctl stop)"] --> HANDLER["signalHandler()"]
    HANDLER --> SAVE["presetMgr->savePreset('preset.json')"]
    SAVE --> EXIT_CLEAN["std::exit() limpio"]

    NORMAL_EXIT["Comando 'exit'\nen consola"] --> SAVE2["presetMgr->savePreset('preset.json')"]
    SAVE2 --> STOP["audioBackend.stop()\noscServer.stop()"]
    STOP --> RETURN["return 0"]
```

### Formato del preset.json

El archivo `preset.json` es un mapa plano de rutas OSC a valores float:

```json
{
  "/kick/vol": 0.114,
  "/kick/tune": 0.463,
  "/kick/dec": 0.07,
  "/master/bpm": 140.0,
  "/emulator/active": 0,
  "/emulator/bpm": 137.0,
  ...
}
```

Esto permite **interoperabilidad directa** con clientes OSC — los mismos paths que se usan en mensajes de red son los que se persisten en disco.

---

## 13. Flujo de Arranque Completo

```mermaid
sequenceDiagram
    participant MAIN as main.cpp
    participant FDSP as Faust DSP (untitled.cpp)
    participant CORE as Synthesizer (core)
    participant UI as FaustMapUI (audio)
    participant PRESET as PresetManager (state)
    participant RTAUDIO as RtAudioBackend (audio)
    participant OSC as OscServer (osc)

    MAIN->>FDSP: newmydsp() — instanciar motor DSP
    MAIN->>CORE: Synthesizer() — crear dominio + MasterClock
    MAIN->>UI: FaustMapUI(&synthCore)
    MAIN->>FDSP: buildUserInterface(&ui)
    Note over FDSP,UI: Faust registra todos los sliders:<br/>ui->addHorizontalSlider() para cada parámetro
    UI->>CORE: addParameter() para cada slider registrado
    MAIN->>CORE: addParameter("/emulator/active")
    MAIN->>CORE: addParameter("/emulator/bpm")
    MAIN->>PRESET: PresetManager(&synthCore)
    MAIN->>PRESET: loadPreset("preset.json")
    PRESET->>CORE: param->setValue() para cada entrada
    MAIN->>RTAUDIO: RtAudioBackend(&synthDsp, &ui)
    RTAUDIO->>RTAUDIO: printAvailableDevices()
    RTAUDIO->>RTAUDIO: openDevice(deviceId)
    Note over RTAUDIO: Init Faust DSP @ 48kHz<br/>Abrir stream ALSA/WASAPI
    MAIN->>OSC: OscServer(&synth, &preset, &recorder, &audio)
    MAIN->>OSC: oscServer.start("8000")
    OSC->>OSC: lo_server_thread_new("8000")
    OSC->>OSC: Iniciar HttpServer (WebSockets)
    MAIN->>RTAUDIO: audioBackend.start()
    Note over RTAUDIO: Inicia callbacks de audio<br/>en hilo dedicado WASAPI/ALSA RT
    loop Bucle infinito de consola
        MAIN->>MAIN: getline(cin, line)
        MAIN->>CORE: Comandos: emu on/off, set device...
    end
    MAIN->>PRESET: savePreset("preset.json")
    MAIN->>RTAUDIO: stop()
    MAIN->>OSC: stop()
```

---

## 14. Tablas de Parámetros

### Preset de fábrica (valores iniciales)

| Instrumento | Parámetro | Valor Inicial | Rango |
|---|---|---|---|
| **Master** | `/master/bpm` | 140.0 | 20 – 999 |
| **Kick** | `/kick/vol` | 0.114 | 0 – 1 |
| **Kick** | `/kick/tune` | 0.463 | 0 – 1 |
| **Kick** | `/kick/dec` | 0.07 | 0.01 – 1 |
| **Kick** | `/kick/sweep` | 150 | 0 – 500 |
| **Kick** | `/kick/groove` | 2 | 0 – 6 |
| **Snare** | `/snare/vol` | 0.0 | 0 – 1 |
| **Snare** | `/snare/dec_cuerpo` | 0.07 | 0.01 – 1 |
| **Snare** | `/snare/dec_resorte` | 0.16 | 0.01 – 1 |
| **Snare** | `/snare/drive` | 3.51 | 0 – 10 |
| **Hat** | `/hat/vol` | 0.0 | 0 – 1 |
| **Hat** | `/hat/dec` | 0.15 | 0.001 – 2 |
| **Hat** | `/hat/cutoff` | 4754.86 Hz | 500 – 20k |
| **Bass** | `/bass/vol` | 0.0 | 0 – 1 |
| **Bass** | `/bass/dec` | 0.57 | 0.01 – 2 |
| **Bass** | `/bass/detune` | 0.04 | 0 – 0.5 |
| **Syn1** | `/syn1/vol` | 0.03 | 0 – 1 |
| **Syn2** | `/syn2/vol` | 0.22 | 0 – 1 |
| **Syn2** | `/syn2/comp_th` | -20 dBFS | -60 – 0 |
| **Emulador** | `/emulator/bpm` | 137.0 | 60 – 240 |

---

## 15. Dependencias y Compilación

### Grafo de dependencias

```mermaid
graph LR
    EXE["FaustSynthServer\n(ejecutable)"]

    EXE --> RTAUDIO_LIB["RtAudio\n(github:thestk/rtaudio)\nFetchContent"]
    EXE --> LIBLO["liblo\n(github:radarsat1/liblo)\nFetchContent"]
    EXE --> NLOHMANN["nlohmann/json\nv3.11.3\nFetchContent"]
    EXE --> UWS["uWebSockets\nv20.44.0\nFetchContent"]
    EXE --> LIBUV["libuv\nv1.44.2\nFetchContent"]
    EXE --> FAUST_CPP["untitled.cpp\n(código Faust transpilado\na C++ por faust2cpp)"]

    RTAUDIO_LIB -->|"Linux"| ALSA_DEP["libasound2-dev\n(paquete apt)"]
    RTAUDIO_LIB -->|"Windows"| WASAPI_DEP["WASAPI (built-in\nen Windows SDK)"]
    LIBLO -->|"Linux alternativo"| LIBLO_APT["liblo-dev\n(paquete apt)"]
    UWS --> LIBUV
```

### Stack tecnológico completo

| Capa | Tecnología | Versión | Propósito |
|---|---|---|---|
| Lenguaje | C++17 | — | Core del servidor |
| DSP Source | Faust | 2.x | Diseño del sintetizador |
| DSP Runtime | C++ generado | — | Motor de síntesis (untitled.cpp) |
| Audio I/O | RtAudio | master | Abstracción ALSA/WASAPI |
| OSC | liblo | master | Protocolo Open Sound Control |
| JSON | nlohmann/json | 3.11.3 | Presets y estado |
| WebSocket | uWebSockets | 20.44.0 | Interfaz web en tiempo real |
| Async I/O | libuv | 1.44.2 | Event loop para uWebSockets |
| Build | CMake | ≥3.14 | Sistema de compilación |
| Linux Audio | ALSA | kernel | Backend nativo Linux |
| Windows Audio | WASAPI | Win 10+ | Backend nativo Windows |

### Quickstart — Raspberry Pi

```bash
# 1. Instalar dependencias
sudo apt update && sudo apt install -y build-essential cmake git libasound2-dev liblo-dev

# 2. Compilar
cd /home/pi/sintetizador
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# 3. Ejecutar (con salida por jack 3.5mm = dispositivo 1)
./build/FaustSynthServer 1

# 4. Instalar como servicio headless
sudo systemctl enable synthesizer.service && sudo systemctl start synthesizer.service
```

### Quickstart — Windows (MSYS2)

```powershell
# 1. Instalar herramientas (en terminal MSYS2 UCRT64)
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja

# 2. Compilar (en PowerShell)
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
cmake -B build -S . -G "Ninja"
cmake --build build --config Release

# 3. Ejecutar
.\build\FaustSynthServer.exe
```

---

> **Ver también:**
> - [GUIA_RASPBERRY.md](./GUIA_RASPBERRY.md) — Instalación detallada en Raspberry Pi, GPIO sync, y servicio headless
> - [GUIA_WINDOWS.md](./GUIA_WINDOWS.md) — Instalación en Windows con MSYS2 y WASAPI
> - [preset.json](./preset.json) — Configuración de parámetros persistida
> - [untitled.dsp](./untitled.dsp) — Código fuente Faust del motor de síntesis
