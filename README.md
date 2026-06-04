# BAZZ Algorithmic Techno Station — Documentación Técnica de Arquitectura

## AUTOR: Santiago Alexander Zambrano Chicunque

> **Bazz SynthServer** · Estación de ritmos algorítmica de baja latencia
> Motor DSP en C++17 · Faust · RtAudio · liblo OSC · uWebSockets · **Raspberry Pi 3 (BCM2837 / Cortex-A53)**

---

## Índice

1. [Visión General del Sistema](#1-visión-general-del-sistema)
2. [Diagrama de Arquitectura Global](#2-diagrama-de-arquitectura-global)
3. [Hardware: Raspberry Pi 3 — Especificaciones Técnicas](#3-hardware-raspberry-pi-3--especificaciones-técnicas)
4. [Módulo Core — Dominio del Sintetizador](#4-módulo-core--dominio-del-sintetizador)
5. [Motor DSP — Pipeline de Audio (Faust + RtAudio)](#5-motor-dsp--pipeline-de-audio-faust--rtaudio)
6. [Diseño del Buffer de Audio](#6-diseño-del-buffer-de-audio)
7. [Arquitectura Acústica del Sintetizador](#7-arquitectura-acústica-del-sintetizador)
8. [Sistema de Reloj Maestro (MasterClock)](#8-sistema-de-reloj-maestro-masterclock)
9. [Conexiones OSC — Protocolo y Rutas](#9-conexiones-osc--protocolo-y-rutas)
10. [Vista Completa desde Raspberry Pi 3](#10-vista-completa-desde-raspberry-pi-3)
11. [Vista desde Windows (WASAPI)](#11-vista-desde-windows-wasapi)
12. [Sincronización GPIO — Reloj de Hardware Externo](#12-sincronización-gpio--reloj-de-hardware-externo)
13. [Sistema de Estado — Presets y Automatización](#13-sistema-de-estado--presets-y-automatización)
14. [Flujo de Arranque Completo](#14-flujo-de-arranque-completo)
15. [Tablas de Parámetros](#15-tablas-de-parámetros)
16. [Dependencias y Compilación](#16-dependencias-y-compilación)

---

## 1. Visión General del Sistema

**Bazz SynthServer** es un servidor de síntesis de audio en tiempo real, inspirado en la TR-808 de Roland, diseñado como una caja de ritmos algorítmica con síntesis procedural completamente en software. El sistema está optimizado para correr en modo **headless** (sin pantalla ni teclado) sobre una **Raspberry Pi 3**, actuando como instrumento de hardware dedicado, controlado remotamente vía red OSC desde cualquier dispositivo.

### Pilares tecnológicos

| Pilar | Tecnología | Rol |
|---|---|---|
| **Síntesis DSP** | Faust → C++ transpilado | Motor de síntesis (untitled.cpp) |
| **E/S de Audio** | RtAudio + ALSA | Comunicación con el hardware DAC |
| **Control Remoto** | liblo (OSC/UDP) | Parámetros en tiempo real vía red |
| **Interfaz Web** | uWebSockets + libuv | UI en navegador por WebSocket |
| **Estado** | nlohmann/json | Persistencia de presets en disco |
| **Sincronización** | GPIO 17 + MasterClock | Reloj analógico desde hardware externo |

### Filosofía de diseño

- **Lock-free entre hilos**: todos los parámetros son `std::atomic<float>`, sin mutex en el camino de audio.
- **Tiempo real estricto**: el callback de audio nunca llama a `new`, `malloc`, ni E/S de disco.
- **Bajo consumo**: diseñado para el Cortex-A53 de la RPi 3, con vectorización NEON explícita.
- **Recuperación automática**: al apagarse, guarda `preset.json`; al encender, lo restaura.

---

## 2. Diagrama de Arquitectura Global

> Diagrama compatible con GitHub Mermaid (sin `direction` dentro de subgraphs).

```mermaid
graph TD
    TOUCHOSC["TouchOSC / iPad"]
    PYTHON["Script Python / python-osc"]
    NODERED["Node-RED / PureData / MaxMSP"]
    HARDWARE_EXT["Hardware Externo - Eurorack / Korg Volca"]
    WEB_CLIENT["Navegador Web"]

    OSC_UDP["UDP Puerto 8000 - Mensajes OSC"]
    WS_TCP["TCP Puerto 9001 - WebSocket"]
    GPIO_IN["GPIO 17 Pin-11 - Entrada de voltaje 3.3V max"]

    OSC_SERVER["OscServer - lo_server_thread - osc/OscServer.cpp"]
    HTTP_SERVER["HttpServer - uWebSockets"]
    SYNTH["Synthesizer - Repositorio de parametros - core/Synthesizer.h"]
    MASTERCLOCK["MasterClock - BPM atomico lock-free - core/MasterClock.h"]
    PARAM["Parameter - atomic float por ruta OSC - core/Parameter.h"]
    FAUSTUI["FaustMapUI - Puente zone-Parameter - audio/FaustUI.h"]
    RTAUDIO["RtAudioBackend - audioCallback - audio/RtAudioBackend.cpp"]
    FAUSTDSP["Faust DSP - Motor C++ generado - untitled.cpp"]
    PRESET["PresetManager - preset.json - state/"]
    RECORDER["AutomationRecorder - state/"]

    DAC_ALSA["DAC via ALSA - Jack 3.5mm o USB Audio"]
    DAC_WIN["DAC via WASAPI - Realtek Windows"]

    TOUCHOSC -->|"OSC /kick/vol 0.8"| OSC_UDP
    PYTHON -->|"OSC /master/bpm 140"| OSC_UDP
    NODERED --> OSC_UDP
    WEB_CLIENT -->|"JSON params"| WS_TCP
    HARDWARE_EXT -->|"Gate / Sync Out"| GPIO_IN

    OSC_UDP --> OSC_SERVER
    WS_TCP --> HTTP_SERVER
    OSC_SERVER -->|"param setValue"| SYNTH
    HTTP_SERVER -->|"param setValue"| SYNTH

    SYNTH --- PARAM
    SYNTH --- MASTERCLOCK

    GPIO_IN -->|"flanco de subida"| RTAUDIO
    RTAUDIO -->|"syncPulse t-ms"| MASTERCLOCK
    MASTERCLOCK -->|"getBpm"| FAUSTUI
    FAUSTUI -->|"updateDSPValues - zone = param getValue"| FAUSTDSP
    RTAUDIO -->|"compute N-frames"| FAUSTDSP

    PRESET -->|"loadPreset"| SYNTH
    SYNTH -->|"savePreset"| PRESET
    RECORDER --> SYNTH

    FAUSTDSP -->|"float L-R 256 frames"| RTAUDIO
    RTAUDIO -->|"interleaved float32"| DAC_ALSA
    RTAUDIO -->|"interleaved float32"| DAC_WIN
```

### Flujo de datos por capas

```
[ Controladores Externos ] ──UDP/WebSocket──▶ [ Capa OSC/Web ]
                                                      │
                                                      ▼ param->setValue() lock-free
                                              [ Capa Core - Synthesizer ]
                                              [ Parameter(atomic) + MasterClock ]
                                                      │
                                          updateDSPValues() cada callback
                                                      │
                                                      ▼
                                           [ Capa Audio - Faust DSP ]
                                           compute(256 frames, in, out)
                                                      │
                                                      ▼
                                             [ Hardware DAC / ALSA ]
                                             Jack 3.5mm / USB Audio
```

---

## 3. Hardware: Raspberry Pi 3 — Especificaciones Técnicas

### SoC y CPU

| Componente | Detalle |
|---|---|
| **SoC** | Broadcom BCM2837 |
| **CPU** | ARM Cortex-A53 (ARMv8-A, 64-bit) |
| **Núcleos** | 4 núcleos @ **1.2 GHz** (RPi 3B) / **1.4 GHz** (RPi 3B+) |
| **Arquitectura** | AArch64 (64-bit) / AArch32 compatible |
| **Cache L1** | 32 KB instrucciones + 32 KB datos por núcleo |
| **Cache L2** | 512 KB compartida (todos los núcleos) |
| **RAM** | **1 GB LPDDR2 @ 900 MHz** |
| **GPU** | VideoCore IV @ 400 MHz (no se usa para audio) |
| **SIMD** | ARM NEON (Advanced SIMD) — 128-bit vectorización |

### Interfaces de conectividad

| Interfaz | Detalle RPi 3B | Detalle RPi 3B+ |
|---|---|---|
| **Ethernet** | 100 Mbps (LAN9514) | ~300 Mbps via USB3 (LAN7515) |
| **WiFi** | 802.11 b/g/n (2.4 GHz) | 802.11 b/g/n/ac (2.4 + 5 GHz) |
| **Bluetooth** | BT 4.1 + BLE | BT 4.2 + BLE |
| **USB** | 4x USB 2.0 (bus compartido) | 4x USB 2.0 (bus compartido) |
| **GPIO** | 40 pines (3.3V lógica) | 40 pines (3.3V lógica) |
| **Audio** | Jack 3.5mm (bcm2835 PWM) + HDMI | Ídem |
| **Consumo** | ~2.5W típico, ~6.7W máx | ~2.5W típico, ~6.7W máx |
| **Alimentación** | 5V / 2.5A microUSB | 5V / 2.5A microUSB |

### Audio en la Raspberry Pi 3

La RPi 3 usa el driver `snd_bcm2835` que implementa dos salidas nativas:

```
BCM2837 SoC
├── PWM0  ──────┐
│               ├── RC filter pasivo ──── Jack 3.5mm (snd_bcm2835 Headphones)
└── PWM1  ──────┘                         Resolución: 11-bit efectivos @ 48kHz
                                          SNR: ~70 dB (limitado por PWM)
└── HDMI I2S ─────────────────────────── HDMI Audio (snd_bcm2835 HDMI)
                                          Resolución: 16-bit

[ USB DAC externo ]
└── snd_usb_audio ────────────────────── USB 2.0 (Clase USB Audio)
                                          Hasta 24-bit / 192kHz (depende del DAC)
                                          RECOMENDADO para producción
```

> **Recomendación**: Para audio de calidad usar un **USB DAC** (ej: Behringer UCA202, IQaudio DAC+, o cualquier interfaz clase USB Audio). El jack 3.5mm nativo tiene ruido PWM audible.

### Mapa de pines GPIO (40 pines)

```
Raspberry Pi 3 — Conector GPIO J8 (40 pines)
┌────────┬──────┬──────────┬────────────────────────────────────────┐
│ Pin Fís│ GPIO │ Función  │ Uso en este proyecto                   │
├────────┼──────┼──────────┼────────────────────────────────────────┤
│  1     │  —   │ 3.3V PWR │ Alimentación de lógica (NO usar como out)│
│  2     │  —   │ 5V PWR   │ Alimentación 5V                        │
│  6     │  —   │ GND      │ Masa general                           │
│  9     │  —   │ GND      │ GND de referencia del reloj externo    │
│  11    │  17  │ GPIO IN  │ *** CLOCK IN — Entrada de voltaje sync ***│
│  12    │  18  │ GPIO     │ Disponible (PCM_CLK si se usa I2S DAC) │
│  14    │  —   │ GND      │ Masa adicional                         │
│  19    │  10  │ SPI_MOSI │ SPI (si se usa DAC por SPI)            │
│  21    │  9   │ SPI_MISO │ SPI                                    │
│  23    │  11  │ SPI_CLK  │ SPI                                    │
│  24    │  8   │ SPI_CE0  │ SPI Chip Select 0                      │
│  35    │  19  │ PCM_FS   │ I2S DAC Frame Sync                     │
│  38    │  20  │ PCM_DIN  │ I2S DAC Data IN                        │
│  40    │  21  │ PCM_DOUT │ I2S DAC Data OUT                       │
└────────┴──────┴──────────┴────────────────────────────────────────┘

CONEXIÓN CRÍTICA:
  Pin 11 (GPIO 17) ──── Señal Clock/Gate externa (máx 3.3V)
  Pin 9  (GND)     ──── Masa del dispositivo externo
```

### Rendimiento DSP en el Cortex-A53

El Cortex-A53 es un núcleo **in-order** (a diferencia del out-of-order Cortex-A72 del RPi 4). Esto tiene implicaciones para el DSP:

```
Cortex-A53 @ 1.2 GHz:
  Ciclos por segundo:    1,200,000,000
  Muestras por segundo:  48,000
  Ciclos por muestra:    1,200,000,000 / 48,000 = 25,000 ciclos/muestra

NEON (Advanced SIMD):
  Procesa 4x float32 en paralelo por instrucción VMUL/VADD
  Throughput VMUL.F32:  1 instrucción por ciclo (pipeline completo)
  Throughput efectivo:  4 muestras × 1.2 GHz = 4.8 GFLOPS de punto flotante

Tiempo de buffer (256 frames):
  Buffer de audio:  256 / 48000 = 5.33 ms disponibles por callback
  Uso típico DSP:   ~2-3 ms (40-60% de CPU en RPi 3)
  Margen seguro:    ~2-3 ms (headroom para jitter del SO)
```

---

## 4. Módulo Core — Dominio del Sintetizador

### Diagrama de clases

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
        +getParameter(string path) shared_ptr~Parameter~
        +getClock() MasterClock ptr
        +getAllParameters() map
    }

    Synthesizer "1" --> "1" MasterClock : owns unique_ptr
    Synthesizer "1" --> "*" Parameter : owns via shared_ptr map
```

### Diseño lock-free de parámetros

El diseño garantiza **cero bloqueos** entre el hilo de audio (tiempo real) y los hilos de red (OSC / WebSocket):

```
┌─────────────────────────────────────────────────────────────────────┐
│                    MODELO DE CONCURRENCIA                           │
│                                                                     │
│  Hilo OSC (red, no RT)          Hilo Audio (RT, ALSA callback)     │
│  ─────────────────────          ───────────────────────────────     │
│  param->setValue(v)             ui->updateDSPValues()              │
│    │                              │                                 │
│    ▼                              ▼                                 │
│  m_value.store(v,               *dsp_zone = m_value.load(          │
│    memory_order_release)          memory_order_acquire)            │
│                                                                     │
│  GARANTÍA: release/acquire pair ─▶ visibilidad total sin mutex     │
│  COSTO:    ~1 ciclo de CPU (una instrucción DMB/STLR en AArch64)   │
└─────────────────────────────────────────────────────────────────────┘
```

**Instrucciones ARM generadas para RPi 3 (AArch64):**
```asm
; store con memory_order_release → STLR (Store-Release)
STLR  W0, [X1]        ; atómica, barrera de memoria implícita

; load con memory_order_acquire → LDAR (Load-Acquire)
LDAR  W0, [X1]        ; atómica, barrera de memoria implícita
```

Esto es más eficiente que `std::mutex` (que requiere syscalls `futex` costosas).

### Mapa de parámetros por ruta OSC

```
Synthesizer::m_parameters
├── "/master/bpm"        ← Parameter(20.0, 999.0, 140.0)
├── "/master/accent"     ← Parameter(0.0, 1.0, 0.5)
├── "/kick/vol"          ← Parameter(0.0, 1.0, 0.114)
├── "/kick/tune"         ← Parameter(0.0, 1.0, 0.463)
├── "/kick/dec"          ← Parameter(0.01, 1.0, 0.07)
├── "/kick/sweep"        ← Parameter(0.0, 500.0, 150.0)
├── "/snare/vol"         ← Parameter(0.0, 1.0, 0.0)
├── "/snare/dec_cuerpo"  ← Parameter(0.01, 1.0, 0.07)
├── "/hat/vol"           ← Parameter(0.0, 1.0, 0.0)
├── "/hat/cutoff"        ← Parameter(500.0, 20000.0, 4754.86)
├── "/bass/vol"          ← Parameter(0.0, 1.0, 0.0)
├── "/bass/detune"       ← Parameter(0.0, 0.5, 0.04)
├── "/syn1/vol"          ← Parameter(0.0, 1.0, 0.03)
├── "/syn2/vol"          ← Parameter(0.0, 1.0, 0.22)
├── "/emulator/active"   ← Parameter(0.0, 1.0, 0.0)   [manual]
└── "/emulator/bpm"      ← Parameter(60.0, 240.0, 137.0) [manual]
    ... (todos los parametros del DSP Faust)
```

---

## 5. Motor DSP — Pipeline de Audio (Faust + RtAudio)

### Diagrama de flujo del callback de audio

```mermaid
flowchart TD
    CB_START(["RtAudio llama audioCallback cada 5.33ms"])

    CB_START --> CLOCK_A
    CLOCK_A{"Hay inputBuffer con señal de voltaje?"}
    CLOCK_A -->|"Si"| SCAN["Escanear frame a frame buscando flanco de subida"]
    CLOCK_A -->|"No"| EMU_CHECK

    SCAN --> EDGE{"currentSample mayor 0.4 Y lastSample menor igual 0.4"}
    EDGE -->|"Si - flanco detectado"| ANTI["Antirrebote: tiempo mayor 50ms desde ultimo trigger?"]
    EDGE -->|"No"| NEXT_SAMPLE["Siguiente muestra i+1"]
    NEXT_SAMPLE --> EDGE

    ANTI -->|"Si"| SYNC_ANA["syncPulse t_ms - Sincronizacion analogica BPM"]
    ANTI -->|"No"| EMU_CHECK
    SYNC_ANA --> EMU_CHECK

    EMU_CHECK{"emulator-active mayor 0.5?"}
    EMU_CHECK -->|"Si"| EMU_CALC["interval_ms = 60000 dividido emuBpm"]
    EMU_CALC --> EMU_FIRE{"t_actual menos t_ultimo mayor igual interval_ms?"}
    EMU_FIRE -->|"Si"| SYNC_EMU["syncPulse t_ms - Pulso de reloj logico"]
    EMU_FIRE -->|"No"| UPDATE_PARAMS
    SYNC_EMU --> UPDATE_PARAMS
    EMU_CHECK -->|"No"| UPDATE_PARAMS

    UPDATE_PARAMS["ui->updateDSPValues - Copiar atomicos a memoria DSP - zone = param getValue"]
    UPDATE_PARAMS --> COMPUTE

    COMPUTE["faust_dsp->compute 256 frames - Motor Faust ejecuta 6 voces - Escribe outL y outR"]
    COMPUTE --> INTERLEAVE

    INTERLEAVE["Intercalar para RtAudio - out 2i = outL i - out 2i+1 = outR i"]
    INTERLEAVE --> RETURN(["return 0 - RtAudio envia al DAC ALSA"])
```

### Configuración del stream ALSA en Raspberry Pi 3

| Parámetro | Valor | Justificación para RPi 3 |
|---|---|---|
| **Sample Rate** | 48,000 Hz | Soportado nativamente por bcm2835 y USB DAC |
| **Buffer Size** | 256 frames | 5.33 ms — balance ideal CPU/latencia en Cortex-A53 |
| **Formato** | RTAUDIO_FLOAT32 | 32-bit float normalizado ±1.0 |
| **Canales salida** | 2 (Stereo) | Definido por Faust `getNumOutputs()` |
| **Canales entrada** | 1 (Mono) | Para detección de voltaje de reloj analógico |
| **API Linux** | ALSA (`__LINUX_ALSA__`) | Driver nativo del kernel, sin PulseAudio overhead |
| **Dispositivo** | auto o ID manual | `0` = default, `1` = headphones, `2` = USB DAC |

### Hilo de audio en Linux (ALSA + POSIX RT)

```
RtAudio en Linux crea un hilo POSIX dedicado para el callback:

  POSIX thread (pthread_create)
  ├── Política de scheduling: SCHED_FIFO (tiempo real)
  ├── Prioridad: 80 (de 0 a 99, mayor = más prioritario)
  ├── CPU affinity: ninguna fija (SO asigna al núcleo libre)
  └── Stack size: default (~8 MB)

  En RPi 3 con 4 núcleos Cortex-A53:
    Núcleo 0: generalmente reservado para interrupciones del SO
    Núcleo 1: hilo de audio (SCHED_FIFO, prioridad alta)
    Núcleo 2: hilo OSC + WebSocket
    Núcleo 3: hilo principal (consola) + systemd
```

---

## 6. Diseño del Buffer de Audio

### Problema: Intercalado vs No-intercalado

RtAudio y Faust usan formatos de buffer diferentes. El callback resuelve esto con buffers estáticos intermedios:

```
FORMATO FAUST (no intercalado / planar):
  outL[256] = [ L[0], L[1], L[2], ..., L[255] ]   (canal izquierdo)
  outR[256] = [ R[0], R[1], R[2], ..., R[255] ]   (canal derecho)

FORMATO RTAUDIO (intercalado / interleaved):
  out[512]  = [ L[0], R[0], L[1], R[1], ..., L[255], R[255] ]

CONVERSION en el callback:
  for (unsigned int i = 0; i < 256; i++) {
      out[2 * i]     = outL[i];   // muestra izquierda
      out[2 * i + 1] = outR[i];   // muestra derecha
  }
```

### Memoria del buffer en la RPi 3

```
Buffers estáticos (static local, asignados al inicio):
  static float outL[4096]  →  4096 × 4 bytes = 16,384 bytes = 16 KB
  static float outR[4096]  →  4096 × 4 bytes = 16,384 bytes = 16 KB
  float* faustOut[2]       →  2 × 8 bytes    =     16 bytes

  Total por callback: ~32 KB en stack estático

  RAM total disponible en RPi 3:  1,024 MB
  RAM usada por el proceso:       ~50-80 MB (código + Faust DSP)
  Headroom disponible:            ~900 MB (amplio margen)
```

> **Regla de tiempo real**: Los buffers usan `static` — el compilador los coloca en BSS/data segment, nunca en heap. En el callback de audio **no se llama a `new`, `malloc`, `free`, ni a ninguna función de E/S**. Esto es esencial para evitar *priority inversion* y *jitter* en ALSA.

### Análisis de latencia completa en Raspberry Pi 3

```
Cadena de latencia de audio (RPi 3, ALSA, 256 frames @ 48kHz):

  ┌────────────────────────────────────────────────────────────┐
  │ Etapa                          │ Latencia   │ Notas        │
  ├────────────────────────────────┼────────────┼──────────────┤
  │ Síntesis Faust (6 voces)       │ ~1.5-2 ms  │ DSP puro     │
  │ Buffer RtAudio (256 frames)    │  5.33 ms   │ fijo         │
  │ Driver ALSA (snd_bcm2835)      │  ~2-4 ms   │ doble buffer │
  │ DAC bcm2835 PWM (jack 3.5mm)   │  ~0.2 ms   │ RC filter    │
  │ DAC USB externo (si se usa)    │  ~1-3 ms   │ USB latency  │
  ├────────────────────────────────┼────────────┼──────────────┤
  │ TOTAL (jack nativo)            │  ~9-11 ms  │ aceptable    │
  │ TOTAL (USB DAC)                │  ~10-14 ms │ OK para ritmo│
  └────────────────────────────────┴────────────┴──────────────┘

Latencia musical percibida:
  A 140 BPM, un beat dura 428 ms.
  Una latencia de 10 ms = 10/428 = 2.3% del beat.
  Imperceptible musicalmente (umbral humano ≈ 20-30 ms).
```

---

## 7. Arquitectura Acústica del Sintetizador

El sintetizador implementa **6 voces de síntesis** independientes, cada una con un modelo físico/matemático propio:

### Mapa de voces y técnicas

```mermaid
graph LR
    KICK["Kick - Bombo"] --> FM_SWEEP["FM Synthesis con Sweep exponencial"]
    SNARE["Snare - Caja"] --> BODY_NOISE["Resonador tonal + Ruido filtrado BPF"]
    HAT["Hat - Platillo"] --> METAL_OSC["6 Osciladores de frecuencia prima"]
    BASS["Bass - Bajo"] --> WAVEGUIDE["Karplus-Strong Waveguide extendido"]
    SYN1["Syn1 - Oscilador"] --> AM_LFO["Sintesis AM con modulacion LFO"]
    SYN2["Syn2 - FDN Synth"] --> FDN_NET["Feedback Delay Network Hadamard"]
```

### Matemática detallada de síntesis por voz

#### Bombo (Kick) — FM + Sweep Exponencial

```
MODELO FÍSICO: Membrana circular tensada (aproximación de modos)

Frecuencia instantánea:
  f(t) = f_base + sweep × e^(−t / τ_f)

  f_base  = nota_MIDI → Hz = 440 × 2^((nota − 69) / 12)
  sweep   = barrido en Hz    → parámetro /kick/sweep (0–500 Hz)
  τ_f     = constante de tiempo de frecuencia ≈ dec/3
  t       = tiempo desde el trigger [segundos]

Ángulo de fase acumulado (integración de la frecuencia instantánea):
  φ(t) = 2π ∫₀ᵗ f(τ) dτ
       = 2π [ f_base·t  −  sweep·τ_f·(e^(−t/τ_f) − 1) ]

Señal de salida:
  y(t) = A(t) × sin(φ(t))

Envolvente de amplitud (Percussive Exponential):
  A(t) = e^(−t / τ_A)
  τ_A = dec × 1.5   → parámetro /kick/dec

Compresor interno (Waveshaper):
  y_comp = sgn(y) × (1 − e^(−|y| × drive))  si comp_thresh activo
```

#### Caja (Snare) — Modelo Cuerpo + Resorte

```
MODELO FÍSICO: Parche superior (tonal) + resortes de snare (ruido)

Señal total:
  y(t) = mix × y_body(t) + (1 − mix) × y_spring(t)

--- CUERPO (componente tonal) ---
  y_body(t) = sin(2π × f_body × t) × e^(−t / τ_body)
  f_body  = /snare/freq  (Hz)
  τ_body  = /snare/dec_cuerpo
  BPF centrado en f_body con Q = /snare/q
  HP a f = /snare/hp para eliminar sub-graves

--- RESORTES (componente de ruido) ---
  n(t) = ruido_blanco_uniforme()  ∈ [−1, 1]
  y_spring_raw(t) = BPF[fc=/snare/freq, Q=/snare/q]( n(t) )
  y_spring(t)     = y_spring_raw(t) × e^(−t / τ_spring)
  τ_spring        = /snare/dec_resorte
  Saturación: y_spring = tanh(y_spring × drive) / tanh(drive)
```

#### Platillo (Hat) — Banco de Osciladores Metálicos

```
MODELO FÍSICO: Plato de metal con modos de vibración no armónicos

Frecuencias no armónicas (ratios primos):
  ratio_primos = [1.0, 1.413, 1.732, 2.145, 2.618, 3.000]
  f_n = f_base × ratio_primos[n],  n = 0..5

  y_metal(t) = Σ(n=0 a 5) sin(2π × f_n × t)
  y_filt = HPF[2000Hz]( LPF[/hat/cutoff]( y_metal ) )
  A(t) = e^(−t / /hat/dec)
  y = tanh(y_filt × drive)  — saturación
```

#### Bajo Waveguide — Karplus-Strong Extendido

```
MODELO FÍSICO: Cuerda pulsada con reflexión en los extremos

Algoritmo:
  L = round(Fs / f_nota)                    ← longitud del delay
  f_nota = 440 × 2^((nota − 69) / 12)      ← afinación MIDI → Hz
  g_decay = e^(−1 / (τ_dec × Fs))          ← amortiguamiento por muestra

  y[n] = 0.5 × (delay[(n-L) mod L] + delay[(n-L-1) mod L]) × g_decay
  delay[n mod L] = y[n]

  DETUNE (coro de 2 voces):
    L_2 = round(L × (1 + detune))
    Salida = (voz_1 + voz_2) / 2

  SATURACIÓN: y_out = tanh(y × drive) / tanh(drive)
  LFO: L_mod = L × (1 + 0.01 × sin(2π × f_lfo × t))
```

#### Syn2 — FDN (Feedback Delay Network)

```
MODELO: Reverberación sintética con densidad modal controlable

Red de N=4 delays con retroalimentación matricial Hadamard:

  Matriz H 4×4 normalizada:
  H = (1/2) × | 1  1  1  1 |
               | 1 -1  1 -1 |
               | 1  1 -1 -1 |
               | 1 -1 -1  1 |

  Longitudes de delay (primos dispersivos):
    primos = [29, 37, 41, 53]
    L_i = round(disp × 48000 × 0.005 × primos[i] / 53)

  La matriz Hadamard garantiza:
    - Mezcla perfecta sin cancelaciones de fase
    - Densidad modal uniforme
    - Estabilidad: valor singular máximo = 1

  LFO de modulación de delays:
    L_i_mod = L_i × (1 + 0.005 × sin(φ_lfo + π×i/2))
```

---

## 8. Sistema de Reloj Maestro (MasterClock)

El `MasterClock` es el corazón temporal del sistema. Recibe pulsos de **tres fuentes** y exporta el BPM suavizado a todo el motor DSP.

### Diagrama de decisión del MasterClock

```mermaid
flowchart TD
    NUEVA_FUENTE(["Nueva fuente de tempo detectada"])
    NUEVA_FUENTE --> ORIGEN{"Origen del pulso?"}

    ORIGEN -->|"Voltaje en GPIO 17"| ANA_DETECT
    ORIGEN -->|"Mensaje OSC /master/bpm"| OSC_VALIDATE
    ORIGEN -->|"Emulador activo /emulator/active"| EMU_CALC

    ANA_DETECT["Flanco ascendente detectado en inputBuffer - threshold 0.4 normalizado"]
    ANA_DETECT --> DELTA["delta_ms = t_actual menos t_anterior_pulso"]
    DELTA --> RANGO{"10ms menor delta_ms menor 3000ms"}
    RANGO -->|"No - fuera de rango"| DESCARTA["Descartar - ruido o glitch electrico"]
    RANGO -->|"Si - valido"| BPM_CRUDO

    BPM_CRUDO["new_bpm = 60000.0 dividido delta_ms"]
    BPM_CRUDO --> SUAVIZADO

    OSC_VALIDATE["Validar: 20 menor bpm menor 999"]
    OSC_VALIDATE --> EXT_ACTIVO{"Reloj externo activo en ultimos 2000ms?"}
    EXT_ACTIVO -->|"Si - hardware tiene prioridad"| IGNORAR["Ignorar OSC /master/bpm"]
    EXT_ACTIVO -->|"No - sin hardware"| STORE_DIRECTO["m_bpm.store directo sin suavizado"]

    EMU_CALC["interval_ms = 60000 dividido emu_bpm - Generar pulso periodico en audioCallback"]
    EMU_CALC --> SUAVIZADO

    SUAVIZADO["LPF: smoothed = prev x 0.7 + new_bpm x 0.3"]
    SUAVIZADO --> ATOMICO["m_bpm.store smoothed - memory_order_release"]

    ATOMICO --> FAUST_SYNC["FaustMapUI.updateDSPValues - zone_bpm = getBpm - Faust usa nuevo tempo"]
    STORE_DIRECTO --> FAUST_SYNC
```

### Matemática del filtro IIR de primer orden (suavizado de BPM)

```
FILTRO IIR DE PRIMER ORDEN (Exponential Moving Average):

  BPM_s[n] = α × BPM_raw[n] + (1−α) × BPM_s[n−1]
  Con α = 0.3:
  BPM_s[n] = 0.3 × BPM_raw[n] + 0.7 × BPM_s[n−1]

FUNCIÓN DE TRANSFERENCIA EN DOMINIO Z:
  H(z) = 0.3 / (1 − 0.7·z⁻¹)
  Polo en z = 0.7  →  estable (|polo| < 1)

CONVERGENCIA (respuesta al escalón de BPM):
  BPM_s[N] = BPM_final × (1 − 0.7^N)

  N = 1  →  30.0%  convergencia
  N = 3  →  65.7%  convergencia
  N = 5  →  83.2%  convergencia
  N = 10 →  97.2%  convergencia
  N = 20 →  99.9%  convergencia

TIEMPO DE RESPUESTA A 140 BPM:
  Intervalo entre pulsos = 60000 / 140 = 428.6 ms
  Al 83% (5 pulsos):  5 × 428.6 ms = 2.14 segundos
  Al 97% (10 pulsos): 10 × 428.6 ms = 4.29 segundos
```

### Timeout y prioridad de reloj

```
isExternalClockActive():
  return (now_ms − m_lastExternalPulseMs) < 2000.0

PRIORIDAD:
  1. Reloj analógico GPIO 17     → máxima prioridad, resetea el timeout
  2. Reloj OSC /master/bpm       → solo actúa si timeout > 2 segundos
  3. Emulador /emulator/active=1 → genera pulsos en el audioCallback
```

---

## 9. Conexiones OSC — Protocolo y Rutas

### ¿Qué es OSC?

**Open Sound Control (OSC)** es un protocolo de comunicación para dispositivos musicales. Usa UDP sobre IP, lo que lo hace extremadamente rápido y flexible. Cada mensaje OSC contiene:

```
Paquete UDP OSC:
┌──────────────────────────────────────────────────────────┐
│ Address Pattern: "/kick/vol\0\0\0"  (múltiplo de 4 bytes)│
│ Type Tag String: ",f\0\0"  (f=float32, i=int32, s=string)│
│ Arguments:       datos en big-endian (float32 = 4 bytes) │
│                                                          │
│ Tamaño típico de un mensaje con 1 float: ~24 bytes       │
│ 70x más compacto que JSON equivalente                    │
└──────────────────────────────────────────────────────────┘
```

### Flujo del servidor OSC

```mermaid
flowchart TD
    CLIENT_OSC(["Cliente OSC - TouchOSC, Python, PD, MaxMSP"])
    CLIENT_OSC -->|"Paquete UDP a Puerto 8000"| RECV_UDP

    RECV_UDP["lo_server_thread recibe paquete UDP"]
    RECV_UDP --> PARSE_OSC["Parsear header OSC - Extraer path, types, argv"]
    PARSE_OSC --> ROUTE{"Ruta OSC recibida?"}

    ROUTE -->|"/clock/sync"| HANDLE_CLOCK["getClock()->syncPulse timestamp_ms"]
    ROUTE -->|"/master/bpm f"| HANDLE_BPM["clock->setBpm si no hay reloj externo activo"]
    ROUTE -->|"/preset/save s"| HANDLE_SAVE["presetMgr->savePreset filename"]
    ROUTE -->|"/preset/load s"| HANDLE_LOAD["presetMgr->loadPreset filename"]
    ROUTE -->|"/automation/start"| HANDLE_AUTO_S["recorder->startRecording"]
    ROUTE -->|"/automation/stop"| HANDLE_AUTO_E["recorder->stopRecording"]
    ROUTE -->|"/audio/device i"| HANDLE_DEV["audioBackend->changeDevice id"]
    ROUTE -->|"Cualquier parametro DSP"| HANDLE_PARAM

    HANDLE_PARAM["param = synth->getParameter path"]
    HANDLE_PARAM --> EXISTS{"Parametro existe en el mapa?"}
    EXISTS -->|"No"| LOG_WARN["Log: Ruta OSC desconocida"]
    EXISTS -->|"Si"| ATOMIC_SET["param->setValue argv0-f - atomic store release - lock-free"]

    ATOMIC_SET --> NEXT_CB(["Proximo audioCallback lee el valor actualizado"])
```

### Tabla de rutas OSC — Referencia completa

#### Globales / Master

| Ruta | Tipo | Rango | Default | Descripción |
|---|---|---|---|---|
| `/master/bpm` | `f` | 20 – 999 | 140.0 | Tempo maestro BPM |
| `/master/accent` | `f` | 0.0 – 1.0 | 0.5 | Acentuación global |
| `/master/nota` | `f` | 0 – 127 | 36 | Nota raíz MIDI |
| `/master/groove` | `f` | 0 – 6 | 0 | Patrón algorítmico |
| `/clock/sync` | — | — | — | Pulso de reloj externo |
| `/emulator/active` | `f` | 0 / 1 | 0 | Emulador de clock on/off |
| `/emulator/bpm` | `f` | 60 – 240 | 137 | BPM del emulador |

#### Bombo (Kick)

| Ruta | Tipo | Rango | Default | Descripción |
|---|---|---|---|---|
| `/kick/vol` | `f` | 0.0 – 1.0 | 0.114 | Volumen |
| `/kick/tune` | `f` | 0.0 – 1.0 | 0.463 | Afinación base |
| `/kick/dec` | `f` | 0.01 – 1.0 | 0.07 | Decaimiento |
| `/kick/sweep` | `f` | 0 – 500 | 150 | Barrido de frecuencia Hz |
| `/kick/mix` | `f` | 0.0 – 1.0 | 0.425 | Mix cuerpo/tono |
| `/kick/groove` | `f` | 0 – 6 | 2 | Patrón rítmico |
| `/kick/swing` | `f` | 0 – 100 | 0 | Swing porcentaje |
| `/kick/accent` | `f` | 0.0 – 1.0 | 0.5 | Velocidad de acento |
| `/kick/comp_thresh` | `f` | 0.0 – 1.0 | 0.4 | Umbral compresor |
| `/kick/comp_ratio` | `f` | 1.0 – 10.0 | 1.988 | Ratio compresion |
| `/kick/comp_drive` | `f` | 0.0 – 5.0 | 1.036 | Drive saturacion |
| `/kick/nota` | `f` | 0 – 127 | 38 | Nota MIDI |
| `/kick/reloj` | `f` | 0.25 – 4.0 | 0.25 | Division de tiempo |

#### Caja (Snare)

| Ruta | Tipo | Rango | Default | Descripción |
|---|---|---|---|---|
| `/snare/vol` | `f` | 0.0 – 1.0 | 0.0 | Volumen |
| `/snare/dec_cuerpo` | `f` | 0.01 – 1.0 | 0.07 | Decay del cuerpo |
| `/snare/dec_resorte` | `f` | 0.01 – 1.0 | 0.16 | Decay del resorte |
| `/snare/freq` | `f` | 100 – 5000 | 1551 | Frecuencia resonancia |
| `/snare/q` | `f` | 0.1 – 20.0 | 3.016 | Factor Q filtro |
| `/snare/hp` | `f` | 20 – 500 | 184 | Corte highpass |
| `/snare/tune` | `f` | -24 – +24 | -6.7 | Afinacion semitonos |
| `/snare/drive` | `f` | 0.0 – 10.0 | 3.51 | Saturacion |
| `/snare/mix` | `f` | 0.0 – 1.0 | 0.352 | Mix cuerpo-resorte |
| `/snare/groove` | `f` | 0 – 6 | 4 | Patron ritmico |

#### Platillo (Hat)

| Ruta | Tipo | Rango | Default | Descripción |
|---|---|---|---|---|
| `/hat/vol` | `f` | 0.0 – 1.0 | 0.0 | Volumen |
| `/hat/dec` | `f` | 0.001 – 2.0 | 0.15 | Decay |
| `/hat/tune` | `f` | -1.0 – 1.0 | -0.005 | Afinacion osciladores |
| `/hat/cutoff` | `f` | 500 – 20000 | 4754 | Cutoff filtro LP Hz |
| `/hat/mix` | `f` | 0.0 – 1.0 | 0.611 | Mix closed/open |
| `/hat/drive` | `f` | 0.0 – 1.0 | 0.206 | Saturacion |
| `/hat/ataque` | `f` | 0.001 – 0.1 | 0.001 | Tiempo de ataque |
| `/hat/groove` | `f` | 0 – 6 | 6 | Patron ritmico |
| `/hat/swing` | `f` | 0 – 100 | 48.4 | Swing |

#### Bajo Waveguide (Bass)

| Ruta | Tipo | Rango | Default | Descripción |
|---|---|---|---|---|
| `/bass/vol` | `f` | 0.0 – 1.0 | 0.0 | Volumen |
| `/bass/nota` | `f` | 0 – 127 | 43 | Nota MIDI base |
| `/bass/dec` | `f` | 0.01 – 2.0 | 0.57 | Decaimiento waveguide |
| `/bass/detune` | `f` | 0.0 – 0.5 | 0.04 | Detune efecto coro |
| `/bass/intervalo` | `f` | -24 – +24 | -12 | Intervalo armonico |
| `/bass/drive` | `f` | 0.0 – 2.0 | 0.65 | Saturacion armonica |
| `/bass/lfo` | `f` | 0.0 – 1.0 | 0.45 | Profundidad LFO |
| `/bass/groove` | `f` | 0 – 6 | 6 | Patron ritmico |

#### Sintetizador AM (Syn1)

| Ruta | Tipo | Rango | Default | Descripción |
|---|---|---|---|---|
| `/syn1/vol` | `f` | 0.0 – 1.0 | 0.03 | Volumen |
| `/syn1/nota` | `f` | 0 – 127 | 45 | Nota base |
| `/syn1/dec` | `f` | 0.01 – 2.0 | 0.12 | Decay |
| `/syn1/osc1` | `f` | 1 – 100 | 11.01 | Ratio oscilador 1 |
| `/syn1/osc2` | `f` | 1 – 100 | 18.63 | Ratio oscilador 2 |
| `/syn1/auto_p` | `f` | 0.0 – 1.0 | 0.959 | Probabilidad auto |
| `/syn1/auto_r` | `f` | 0.0 – 10.0 | 7.135 | Rango auto |
| `/syn1/auto_v` | `f` | 0.0 – 1.0 | 0.805 | Velocidad auto |

#### Sintetizador FDN (Syn2)

| Ruta | Tipo | Rango | Default | Descripción |
|---|---|---|---|---|
| `/syn2/vol` | `f` | 0.0 – 1.0 | 0.22 | Volumen |
| `/syn2/dec` | `f` | 0.001 – 2.0 | 0.01 | Decay ataque |
| `/syn2/nota` | `f` | 0 – 127 | 24 | Nota base |
| `/syn2/disp` | `f` | 0.0 – 1.0 | 0.654 | Dispersion modal FDN |
| `/syn2/lfo_f` | `f` | 0.1 – 20.0 | 19.1 | Frecuencia LFO |
| `/syn2/lfo_p` | `f` | 0.0 – 1.0 | 0.5 | Fase LFO |
| `/syn2/comp_th` | `f` | -60 – 0 | -20 | Umbral compresor dBFS |
| `/syn2/comp_a` | `f` | 0.001 – 1.0 | 0.069 | Attack compresor |
| `/syn2/comp_r` | `f` | 1 – 20 | 6 | Ratio compresor |
| `/syn2/comp_rel` | `f` | 0.01 – 2.0 | 0.1 | Release compresor |
| `/syn2/groove` | `f` | 0 – 6 | 6 | Patron ritmico |

#### Control del sistema

| Ruta | Tipo | Descripción |
|---|---|---|
| `/preset/save` | `s` | Guardar preset a archivo JSON |
| `/preset/load` | `s` | Cargar preset desde archivo JSON |
| `/automation/start` | — | Iniciar grabacion de automatizacion |
| `/automation/stop` | — | Detener grabacion |
| `/audio/device` | `i` | Cambiar dispositivo ALSA (ID entero) |

---

## 10. Vista Completa desde Raspberry Pi 3

### Diagrama de capas del sistema en RPi 3

```mermaid
graph TD
    LAN_CLIENT["Controlador Remoto - TouchOSC o Python - 192.168.x.y"]
    GPIO_DEVICE["Hardware Externo - Korg Volca o Eurorack"]

    ETH_WIFI["Ethernet 100Mbps o WiFi 802.11n - RPi 3"]
    GPIO17_NODE["Pin 11 GPIO17 - Entrada 3.3V max"]

    SYNTH_PROC["BazzSynthServer proceso C++ - Usuario pi"]
    GPIO_DAEMON["pi_gpio_sync daemon C++ - Usuario pi"]

    ALSA_DRIVER["ALSA - snd_bcm2835 o snd_usb_audio - Kernel Linux"]
    GPIO_DRIVER["GPIO driver - gpiochip0 - Kernel Linux"]
    NET_STACK["Stack UDP-IP loopback 127.0.0.1 - Kernel Linux"]

    BCM_PWM["PWM0 y PWM1 - bcm2835 headphones - BCM2837"]
    USB_BUS["USB 2.0 bus - LAN9514 chip - BCM2837"]

    JACK_35["Jack 3.5mm - Headphones"]
    USB_DAC["USB DAC externo - Recomendado para produccion"]
    HDMI_AUDIO["HDMI Audio"]

    LAN_CLIENT -->|"UDP OSC Port 8000"| ETH_WIFI
    GPIO_DEVICE -->|"Gate max 3.3V"| GPIO17_NODE

    ETH_WIFI --> SYNTH_PROC
    GPIO17_NODE --> GPIO_DRIVER
    GPIO_DRIVER --> GPIO_DAEMON
    GPIO_DAEMON -->|"OSC /clock/sync loopback UDP"| NET_STACK
    NET_STACK --> SYNTH_PROC

    SYNTH_PROC -->|"ALSA openStream 48kHz 256frames"| ALSA_DRIVER
    ALSA_DRIVER --> BCM_PWM
    ALSA_DRIVER --> USB_BUS
    BCM_PWM --> JACK_35
    BCM_PWM --> HDMI_AUDIO
    USB_BUS --> USB_DAC
```

### Modelo de procesos y hilos en Raspberry Pi 3

```
Sistema Linux (Raspberry Pi OS)
│
├── PID xxx: BazzSynthServer (proceso principal)
│   │
│   ├── Hilo 1: main() — hilo principal
│   │     Política: SCHED_OTHER (normal)
│   │     Función: bucle de consola stdin, carga/guarda preset
│   │
│   ├── Hilo 2: RtAudio ALSA callback (hilo de audio)
│   │     Política: SCHED_FIFO prioridad 80 (tiempo real)
│   │     Período:  cada 5.33 ms (256 frames @ 48kHz)
│   │     CPU:      preferentemente núcleo 1 o 2
│   │     Función:  detectar voltaje GPIO, actualizar params,
│   │               ejecutar Faust DSP, enviar a DAC
│   │
│   ├── Hilo 3: lo_server_thread (OSC listener)
│   │     Política: SCHED_OTHER
│   │     Puerto:   UDP 8000
│   │     Función:  recibir mensajes OSC, actualizar parametros
│   │
│   └── Hilo 4: uWebSockets + libuv (WebSocket server)
│         Política: SCHED_OTHER
│         Puerto:   TCP 9001
│         Función:  interfaz web en navegador
│
└── PID yyy: pi_gpio_sync (proceso C++ daemon)
      Función: monitoriza GPIO 17, envía /clock/sync por UDP loopback
```

### Flags de compilación específicos para Cortex-A53 (RPi 3)

```cmake
# CMakeLists.txt — Bloque Linux (Raspberry Pi 3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
    -O3                      # Optimización máxima
    -ffast-math              # Relaxed IEEE 754: reordenamiento de operaciones FP
    -mcpu=cortex-a53         # Genera código optimizado para Cortex-A53 (RPi 3)
    -mtune=cortex-a53        # Ajusta pipeline scheduling al A53 (in-order)
    -mfpu=neon-fp-armv8      # Habilita instrucciones NEON ARMv8 (128-bit SIMD)
    -ftree-vectorize         # Auto-vectorización de bucles con NEON
    -funroll-loops           # Desenrollar bucles (reduce branch overhead en A53)
")
```

**Diferencias con RPi 4 (Cortex-A72):**

| Característica | RPi 3 (Cortex-A53) | RPi 4 (Cortex-A72) |
|---|---|---|
| **Arquitectura** | In-order | Out-of-order |
| **Flag CPU** | `-mcpu=cortex-a53` | `-mcpu=cortex-a72` |
| **Clock** | 1.2 / 1.4 GHz | 1.5 / 1.8 GHz |
| **IPC** | ~2 instrucciones/ciclo | ~3-4 instrucciones/ciclo |
| **NEON unidad** | 1 pipeline SIMD | 2 pipelines SIMD |
| **RAM** | 1 GB LPDDR2 | 2-8 GB LPDDR4 |
| **DSP overhead** | ~50-65% CPU | ~20-30% CPU |
| **Buffer mínimo seguro** | 256 frames | 128 frames |

### Instalación de dependencias en Raspberry Pi 3

```bash
# 1. Actualizar el sistema operativo
sudo apt update && sudo apt full-upgrade -y

# 2. Instalar herramientas de compilación
sudo apt install -y build-essential cmake git

# 3. Instalar ALSA (driver de audio nativo)
sudo apt install -y libasound2-dev

# 4. Instalar liblo (opcional, acelera compilación)
sudo apt install -y liblo-dev

# 5. Instalar gpiod y libgpiod-dev (para el puente GPIO en C++)
sudo apt install -y libgpiod-dev gpiod

# 6. Configurar dispositivo de audio por defecto
# Para jack 3.5mm como default:
echo "options snd_bcm2835 index=0" | sudo tee /etc/modprobe.d/alsa-base.conf

# Para USB DAC como default (reemplaza al bcm2835):
echo "options snd-usb-audio index=0" | sudo tee /etc/modprobe.d/alsa-base.conf
echo "options snd-bcm2835 index=1"  | sudo tee -a /etc/modprobe.d/alsa-base.conf
```

### Compilación en Raspberry Pi 3

```bash
cd /home/pi/sintetizador
rm -rf build                                         # Limpiar builds de Windows
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release       # CMake detecta Linux → flags A53
cmake --build build --config Release -j4             # Compilar con 4 núcleos
ls -lh build/BazzSynthServer                         # Tamaño típico: 8-15 MB
```

### Ejecución en Raspberry Pi 3

```bash
./build/BazzSynthServer          # Autodetección de dispositivo
./build/BazzSynthServer 1        # Jack 3.5mm (snd_bcm2835 Headphones)
./build/BazzSynthServer 2        # USB DAC externo (recomendado)

# Consola interactiva:
synth-server> list               # Listar dispositivos ALSA
synth-server> set 2              # Cambiar a USB DAC
synth-server> emu on             # Activar emulador de reloj
synth-server> emu bpm 128        # Establecer tempo del emulador
synth-server> status             # Ver estado completo
synth-server> exit               # Guardar preset y salir
```

### Servicio systemd — Modo Headless (RPi 3 como instrumento)

```bash
sudo nano /etc/systemd/system/synthesizer.service
```

```ini
[Unit]
Description=BAZZ Algorithmic Synth Server - BazzSynthServer
After=network.target sound.target
Wants=sound.target

[Service]
Type=simple
User=pi
Group=audio
WorkingDirectory=/home/pi/sintetizador
ExecStart=/home/pi/sintetizador/build/BazzSynthServer 1
Restart=on-failure
RestartSec=5
Nice=-10
LimitRTPRIO=95

[Install]
WantedBy=multi-user.target
```

```bash
sudo nano /etc/systemd/system/synthesizer-sync.service
```

```ini
[Unit]
Description=BAZZ GPIO Clock Bridge (C++)
After=synthesizer.service
Requires=synthesizer.service

[Service]
Type=simple
User=pi
Group=gpio
WorkingDirectory=/home/pi/sintetizador
ExecStart=/home/pi/sintetizador/build/pi_gpio_sync
Restart=on-failure
RestartSec=3

[Install]
WantedBy=multi-user.target
```

```bash
sudo systemctl daemon-reload
sudo systemctl enable synthesizer.service synthesizer-sync.service
sudo systemctl start  synthesizer.service synthesizer-sync.service
sudo systemctl status synthesizer.service
journalctl -u synthesizer.service -f    # Ver logs en tiempo real
```

### Secuencia de arranque del RPi 3 (headless)

```
Encendido de la Raspberry Pi 3
         │  ~5s
         ▼
  Bootloader GPU firmware
         │  ~15s
         ▼
  Kernel Linux (Raspberry Pi OS)
         │  ~20s
         ▼
  systemd → multi-user.target
         │
         ├──▶ synthesizer.service
         │     ├── Carga preset.json
         │     ├── Enumera dispositivos ALSA
         │     ├── Abre stream ALSA @ 48kHz / 256 frames
         │     ├── Inicia OSC en UDP :8000
         │     └── Inicia WebSocket en TCP :9001
         │
         └──▶ synthesizer-sync.service
               ├── Configura GPIO 17 como entrada
               ├── Monitorea interrupción de flanco ascendente (libgpiod)
               └── Escucha pulsos → envía /clock/sync loopback

  LISTO en ~30 segundos desde el encendido
```

### Dispositivos de audio ALSA en RPi 3

| ID ALSA | Nombre | Canales | Resolución | Latencia | Recomendado |
|---|---|---|---|---|---|
| `[0]` | bcm2835 HDMI 1 | Out: 2 | 16-bit | ~10-15 ms | TV / Monitor HDMI |
| `[1]` | bcm2835 Headphones | Out: 2 | ~11-bit efectivos | ~8-12 ms | Pruebas rápidas |
| `[2]` | USB Audio (si conectado) | In+Out: 2 | 16-24 bit | ~5-8 ms | **Producción** |

### Configuración de red para control OSC remoto

```bash
ip addr show eth0    # Ver IP Ethernet del RPi 3
ip addr show wlan0   # Ver IP WiFi del RPi 3
# Ejemplo: inet 192.168.1.42/24

# Desde Python en la red local:
from pythonosc import udp_client
client = udp_client.SimpleUDPClient("192.168.1.42", 8000)
client.send_message("/kick/vol", 0.8)
client.send_message("/master/bpm", 140.0)

# TouchOSC (iPad/Android):
#   Host: 192.168.1.42   Puerto: 8000   Protocolo: UDP

# Interfaz WebSocket en navegador:
#   http://192.168.1.42:9001
```

---

## 11. Vista desde Windows (WASAPI)

### Diagrama de capas en Windows

```mermaid
graph TD
    UDP_IN["UDP Puerto 8000 - TouchOSC o Python"]
    WS_IN["TCP Puerto 9001 - Navegador Web"]

    MAIN_T["Hilo 1 - main - Consola stdin - NORMAL priority"]
    OSC_T["Hilo 2 - OscServer - lo_server_thread - ABOVE_NORMAL"]
    AUDIO_T["Hilo 3 - RtAudio WASAPI callback - TIME_CRITICAL"]
    WS_T["Hilo 4 - uWebSockets libuv - NORMAL"]

    DLL_LO["liblo.dll - OSC"]
    DLL_RT["librtaudio.dll - WASAPI"]
    DLL_GCC["libgcc_s_seh-1.dll - Runtime GCC"]
    DLL_STD["libstdc++6.dll - C++ stdlib"]
    DLL_PT["libwinpthread-1.dll - POSIX threads"]

    WASAPI["WASAPI - Windows Audio Session API"]
    REALTEK["Realtek HD Audio - Altavoces o Jack"]

    UDP_IN --> OSC_T
    WS_IN --> WS_T
    MAIN_T --> OSC_T
    MAIN_T --> AUDIO_T
    MAIN_T --> WS_T
    AUDIO_T --> WASAPI
    WASAPI --> REALTEK

    DLL_LO -.-> MAIN_T
    DLL_RT -.-> MAIN_T
    DLL_GCC -.-> MAIN_T
    DLL_STD -.-> MAIN_T
    DLL_PT -.-> MAIN_T
```

### Comandos de consola disponibles (Windows y Linux)

```
synth-server> list               → Listar dispositivos de audio disponibles
synth-server> set <id>           → Cambiar dispositivo (hot-swap sin cortar audio)
synth-server> emu on             → Activar emulador de reloj interno
synth-server> emu off            → Desactivar emulador de reloj
synth-server> emu bpm <valor>    → Establecer tempo del emulador (ej: emu bpm 128.5)
synth-server> status             → Ver BPM activo, emulador, dispositivo activo
synth-server> exit               → Guardar preset.json y salir limpiamente
```

### Quickstart Windows (MSYS2 UCRT64)

```powershell
# En terminal MSYS2 UCRT64:
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja

# En PowerShell:
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
cmake -B build -S . -G "Ninja"
cmake --build build --config Release
.\build\BazzSynthServer.exe
```

---

## 12. Sincronización GPIO — Reloj de Hardware Externo

### Diagrama completo de la cadena de sincronización

```mermaid
flowchart LR
    EURORACK["Eurorack - Gate 5-12V"]
    VOLCA["Korg Volca - Sync 3.3-5V"]

    VOLTAGE_DIV["Divisor de Tension - R1=10k serie - R2=4.7k a GND"]

    GPIO17_PIN["Pin 11 GPIO17 - 3.3V MAX - Raspberry Pi 3"]
    GND_PIN["Pin 9 GND - Masa comun"]

    GPIOZERO_CB["libgpiod - wait_edge event - flanco ascendente"]

    OSC_SEND["pi_gpio_sync (C++) send - /clock/sync - UDP 127.0.0.1:8000"]

    OSC_RECV["OscServer genericHandler - recibe /clock/sync"]

    MASTERCLOCK_SYNC["MasterClock syncPulse t_ms - Calcula delta - Filtra LPF - Actualiza BPM atomico"]

    FAUST_BPM["FaustMapUI updateDSPValues - zone_bpm = getBpm - Faust usa nuevo tempo"]

    EURORACK --> VOLTAGE_DIV
    VOLCA -->|"3.3V-5V directo"| GPIO17_PIN
    VOLTAGE_DIV --> GPIO17_PIN
    GND_PIN -.->|"masa comun"| VOLTAGE_DIV

    GPIO17_PIN --> GPIOZERO_CB
    GPIOZERO_CB -->|"latencia kernel ~0.5ms"| OSC_SEND
    OSC_SEND -->|"UDP loopback < 0.1ms"| OSC_RECV
    OSC_RECV --> MASTERCLOCK_SYNC
    MASTERCLOCK_SYNC --> FAUST_BPM
```

### Conexión eléctrica física al Raspberry Pi 3

```
CASO 1: Korg Volca / Pocket Operator (Sync Out 3.3V-5V)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  [ KORG VOLCA ]              [ RASPBERRY PI 3 ]
  Sync Out (+) ─────────────▶ Pin 11 (GPIO 17)
  GND          ─────────────▶ Pin 9  (GND)

  Tensión de sync Volca: ~3.5V peak → dentro del rango: ✓

CASO 2: Eurorack Modular (Gate/Trigger 5V-12V)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  [ EURORACK ]              [ DIVISOR ]             [ RPi 3 ]
  Gate(+) ─── R1=10kΩ ─── Nodo ─── R2=4.7kΩ ─── GND
                               │
                               └────────────────▶ Pin 11 (GPIO 17)
  GND ───────────────────────────────────────────▶ Pin 9  (GND)

  Cálculo:
  V_gpio = V_gate × 4700 / (10000 + 4700) = V_gate × 0.3197

    V_gate = 5V  → V_gpio = 1.60V  ✓
    V_gate = 8V  → V_gpio = 2.56V  ✓
    V_gate = 12V → V_gpio = 3.84V  ⚠ (usar R1=15kΩ en su lugar)

  Para señales de 12V: R1=15kΩ, R2=4.7kΩ → V_gpio = 2.86V ✓
```

### Código C++ del puente GPIO (`app/pi_gpio_sync.cpp`)

```cpp
#include <gpiod.h>
#include <lo/lo.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <string>

volatile sig_atomic_t keep_running = 1;

void handle_signal(int sig) {
    keep_running = 0;
}

int main(int argc, char* argv[]) {
    int pin = 17;
    struct gpiod_chip *chip = nullptr;
    
    // Auto-detectar chip GPIO (RPi 5 usa gpiochip4, RPi 3/4 usa gpiochip0)
    int candidates[] = {4, 0, 1, 2, 3, 5};
    for (int c : candidates) {
        std::string chip_path = "/dev/gpiochip" + std::to_string(c);
        chip = gpiod_chip_open(chip_path.c_str());
        if (chip) {
            unsigned int num_lines = gpiod_chip_num_lines(chip);
            if (static_cast<unsigned int>(pin) < num_lines) break;
            gpiod_chip_close(chip);
            chip = nullptr;
        }
    }

    if (!chip) return 1;
    struct gpiod_line *line = gpiod_chip_get_line(chip, pin);
    if (!line) return 1;

    struct gpiod_line_request_config config;
    config.consumer = "pi_gpio_sync";
    config.request_type = GPIOD_LINE_REQUEST_EVENT_RISING_EDGE;
    config.flags = 0;

    if (gpiod_line_request_input_event(line, &config) < 0) return 1;

    lo_address target = lo_address_new("127.0.0.1", "8000");
    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    struct gpiod_line_event event;
    struct timespec timeout = {1, 0};
    double last_pulse_ms = 0.0;

    while (keep_running) {
        int res = gpiod_line_event_wait(line, &timeout);
        if (res > 0) {
            gpiod_line_event_read(line, &event);
            auto now = std::chrono::steady_clock::now();
            double now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
            if (now_ms - last_pulse_ms >= 40.0) {
                lo_send(target, "/clock/sync", "");
                last_pulse_ms = now_ms;
            }
        }
    }
    lo_address_free(target);
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}
```

### Cadena de latencia completa de sincronización

```
  Flanco de subida en Gate externo        ~0.1 ms  (rise time)
         │
  Interrupción kernel Linux (GPIO)        ~0.3-0.8 ms
         │
  Callback C++ on_clock_pulse()           ~0.05 ms
         │
  Envío OSC por UDP loopback              ~0.1 ms
         │
  OscServer.genericHandler()             ~0.05 ms
         │
  Espera al próximo audioCallback()       0 – 5.33 ms  (jitter de buffer)
         │
  updateDSPValues() + compute() Faust     ~1.5 ms
         │
  Señal de audio al DAC

  ┌───────────────────────────────────────────────────────────┐
  │ LATENCIA MÍNIMA:   ~1 ms   (callback justo a tiempo)     │
  │ LATENCIA MÁXIMA:   ~7.5 ms (espera al próximo buffer)    │
  │ LATENCIA PROMEDIO: ~4 ms   (distribución uniforme)       │
  │                                                           │
  │ A 140 BPM: 1 beat = 428 ms                               │
  │ Error máximo: 7.5 / 428 = 1.75% del beat                 │
  │ Imperceptible (umbral humano ~20 ms)                      │
  └───────────────────────────────────────────────────────────┘
```

---

## 13. Sistema de Estado — Presets y Automatización

### Diagrama de flujo del PresetManager

```mermaid
flowchart TD
    ARRANQUE(["Arranque de BazzSynthServer"])
    ARRANQUE --> EXISTE{"Existe preset.json en disco?"}

    EXISTE -->|"Si"| LEER["Leer JSON con nlohmann::json"]
    EXISTE -->|"No"| DEFAULTS["Usar valores init de Faust DSP"]

    LEER --> LOOP["Para cada entrada en el JSON"]
    LOOP --> FIND_PARAM{"synth->getParameter path existe?"}
    FIND_PARAM -->|"Si"| SET_ATOMIC["param->setValue value - atomic store release"]
    FIND_PARAM -->|"No"| SKIP["Ignorar - parametro obsoleto"]
    SET_ATOMIC --> LOOP
    SKIP --> LOOP

    SIGINT(["SIGINT o SIGTERM - Ctrl+C o systemctl stop"])
    SIGINT --> HANDLER["signalHandler guardar antes de morir"]
    HANDLER --> SAVE_JSON["presetMgr->savePreset preset.json"]
    SAVE_JSON --> EXIT_SAFE["std::exit signum - salida limpia"]

    CMD_EXIT(["Comando exit o quit en consola"])
    CMD_EXIT --> SAVE_FINAL["presetMgr->savePreset preset.json"]
    SAVE_FINAL --> STOP_AUDIO["audioBackend.stop - cerrar stream ALSA"]
    STOP_AUDIO --> STOP_OSC["oscServer.stop - cerrar UDP socket"]
    STOP_OSC --> RETURN_0(["return 0"])
```

### Formato del archivo preset.json

```json
{
  "/bass/dec":         0.57,
  "/bass/detune":      0.04,
  "/bass/drive":       0.65,
  "/bass/vol":         0.0,
  "/emulator/active":  0,
  "/emulator/bpm":     137,
  "/hat/cutoff":       4754.86,
  "/hat/dec":          0.15,
  "/hat/vol":          0.0,
  "/kick/dec":         0.07,
  "/kick/sweep":       150,
  "/kick/tune":        0.463,
  "/kick/vol":         0.114,
  "/master/bpm":       140,
  "/snare/dec_cuerpo": 0.07,
  "/snare/dec_resorte":0.16,
  "/snare/drive":      3.51,
  "/syn1/vol":         0.03,
  "/syn2/comp_th":     -20,
  "/syn2/vol":         0.22
}
```

---

## 14. Flujo de Arranque Completo

```mermaid
sequenceDiagram
    participant MAIN as main.cpp
    participant FDSP as Faust DSP untitled.cpp
    participant CORE as Synthesizer core
    participant UI as FaustMapUI audio
    participant PRESET as PresetManager state
    participant RTAUDIO as RtAudioBackend audio
    participant OSC as OscServer osc

    MAIN->>FDSP: newmydsp() instanciar motor DSP
    MAIN->>CORE: Synthesizer() crear dominio + MasterClock
    MAIN->>UI: FaustMapUI con puntero a synthCore
    MAIN->>FDSP: buildUserInterface puntero a ui
    Note over FDSP,UI: Faust registra todos sus sliders via addHorizontalSlider para cada parametro
    UI->>CORE: addParameter para cada slider con ruta OSC
    MAIN->>CORE: addParameter emulator-active y emulator-bpm
    MAIN->>PRESET: PresetManager con puntero a synthCore
    MAIN->>PRESET: loadPreset preset.json
    PRESET->>CORE: param->setValue para cada entrada del JSON
    MAIN->>RTAUDIO: RtAudioBackend con synthDsp y ui
    RTAUDIO->>RTAUDIO: printAvailableDevices listar ALSA
    RTAUDIO->>RTAUDIO: openDevice con deviceId
    Note over RTAUDIO: Init Faust DSP a 48kHz - Abrir stream ALSA 256 frames
    MAIN->>OSC: OscServer con synth preset recorder audioBackend
    MAIN->>OSC: oscServer.start en puerto 8000
    OSC->>OSC: lo_server_thread_new puerto 8000
    OSC->>OSC: Iniciar HttpServer WebSockets en 9001
    MAIN->>RTAUDIO: audioBackend.start
    Note over RTAUDIO: Inicia callbacks ALSA cada 5.33ms - Hilo RT SCHED_FIFO prioridad 80
    loop Bucle de consola
        MAIN->>MAIN: getline cin esperando comandos del usuario
        MAIN->>CORE: Procesar list set emu status exit
    end
    MAIN->>PRESET: savePreset preset.json al salir
    MAIN->>RTAUDIO: stop cerrar stream ALSA
    MAIN->>OSC: stop cerrar UDP socket
```

---

## 15. Tablas de Parámetros

### Preset de fábrica completo

| Instrumento | Ruta OSC | Default | Rango |
|---|---|---|---|
| **Master** | `/master/bpm` | 140.0 | 20–999 |
| **Kick** | `/kick/vol` | 0.114 | 0–1 |
| **Kick** | `/kick/tune` | 0.463 | 0–1 |
| **Kick** | `/kick/dec` | 0.07 | 0.01–1 |
| **Kick** | `/kick/sweep` | 150 Hz | 0–500 |
| **Kick** | `/kick/comp_thresh` | 0.4 | 0–1 |
| **Kick** | `/kick/comp_ratio` | 1.988 | 1–10 |
| **Kick** | `/kick/groove` | 2 | 0–6 |
| **Snare** | `/snare/vol` | 0.0 | 0–1 |
| **Snare** | `/snare/dec_cuerpo` | 0.07 | 0.01–1 |
| **Snare** | `/snare/dec_resorte` | 0.16 | 0.01–1 |
| **Snare** | `/snare/drive` | 3.51 | 0–10 |
| **Snare** | `/snare/freq` | 1551 Hz | 100–5000 |
| **Hat** | `/hat/vol` | 0.0 | 0–1 |
| **Hat** | `/hat/dec` | 0.15 | 0.001–2 |
| **Hat** | `/hat/cutoff` | 4754.86 Hz | 500–20000 |
| **Bass** | `/bass/vol` | 0.0 | 0–1 |
| **Bass** | `/bass/dec` | 0.57 | 0.01–2 |
| **Bass** | `/bass/detune` | 0.04 | 0–0.5 |
| **Bass** | `/bass/drive` | 0.65 | 0–2 |
| **Syn1** | `/syn1/vol` | 0.03 | 0–1 |
| **Syn1** | `/syn1/osc1` | 11.01 | 1–100 |
| **Syn1** | `/syn1/osc2` | 18.63 | 1–100 |
| **Syn2** | `/syn2/vol` | 0.22 | 0–1 |
| **Syn2** | `/syn2/comp_th` | -20 dBFS | -60–0 |
| **Syn2** | `/syn2/disp` | 0.654 | 0–1 |
| **Emulador** | `/emulator/active` | 0 (off) | 0–1 |
| **Emulador** | `/emulator/bpm` | 137.0 | 60–240 |

---

## 16. Dependencias y Compilación

### Grafo de dependencias

```mermaid
graph TD
    EXE["BazzSynthServer - ejecutable final"]

    EXE --> RTAUDIO_DEP["RtAudio - github thestk/rtaudio - FetchContent - ALSA en Linux"]
    EXE --> LIBLO_DEP["liblo - github radarsat1/liblo - FetchContent - Protocolo OSC UDP"]
    EXE --> NLOHMANN_DEP["nlohmann-json v3.11.3 - FetchContent - Presets JSON"]
    EXE --> UWS_DEP["uWebSockets v20.44.0 - FetchContent - WebSocket server"]
    EXE --> LIBUV_DEP["libuv v1.44.2 - FetchContent - Event loop async"]
    EXE --> FAUST_DEP["untitled.cpp - Codigo Faust transpilado a C++ - Motor DSP 6 voces"]

    RTAUDIO_DEP -->|"Linux RPi3"| ALSA_SYS["libasound2-dev - apt package"]
    RTAUDIO_DEP -->|"Windows"| WASAPI_SYS["WASAPI built-in Windows SDK"]
    LIBLO_DEP --> LO_OPT["liblo-dev opcional apt"]
    UWS_DEP --> LIBUV_DEP
```

### Stack tecnológico

| Capa | Tecnología | Versión | Propósito |
|---|---|---|---|
| Lenguaje | C++17 | — | Todo el servidor |
| DSP Source | Faust | 2.x | Diseño algorítmico del sintetizador |
| DSP Runtime | C++ generado | — | Motor de síntesis (untitled.cpp) |
| Audio I/O | RtAudio | master | Abstracción ALSA (Linux) / WASAPI (Win) |
| OSC | liblo | master | Open Sound Control sobre UDP |
| JSON | nlohmann/json | 3.11.3 | Presets y configuración |
| WebSocket | uWebSockets | 20.44.0 | Interfaz web en tiempo real |
| Async I/O | libuv | 1.44.2 | Event loop para uWebSockets |
| Build | CMake | ≥3.14 | Sistema de compilación cross-platform |
| Linux Audio | ALSA | kernel | Driver nativo Linux (RPi 3) |
| Windows Audio | WASAPI | Win 10+ | Ultra-baja latencia Windows |

### Quickstart Raspberry Pi 3

```bash
sudo apt update && sudo apt install -y build-essential cmake git libasound2-dev liblo-dev
cd /home/pi/sintetizador && rm -rf build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build -j4
./build/BazzSynthServer 1
```

### Quickstart Windows (MSYS2 UCRT64)

```powershell
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
cmake -B build -S . -G "Ninja"
cmake --build build --config Release
.\build\BazzSynthServer.exe
```

---

> **Ver también:**
> - [GUIA_RASPBERRY.md](./GUIA_RASPBERRY.md) — Guia de instalacion y GPIO sync en Raspberry Pi
> - [GUIA_WINDOWS.md](./GUIA_WINDOWS.md) — Instalacion en Windows con MSYS2 y WASAPI
> - [preset.json](./preset.json) — Configuracion de parametros persistida en disco
> - [untitled.dsp](./untitled.dsp) — Codigo fuente Faust del motor de sintesis
> - [core/MasterClock.h](./core/MasterClock.h) — Implementacion del reloj maestro lock-free
> - [audio/RtAudioBackend.cpp](./audio/RtAudioBackend.cpp) — Callback de audio y deteccion de voltaje
> - [osc/OscServer.cpp](./osc/OscServer.cpp) — Servidor OSC y routing de mensajes
