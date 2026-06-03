# BAZZ Algorithmic Techno Station â€” DocumentaciÃ³n TÃ©cnica de Arquitectura

## AUTOR: Santiago Alexander Zambrano Chicunque

> **Bazz SynthServer** Â· EstaciÃ³n de ritmos algorÃ­tmica de baja latencia
> Motor DSP en C++17 Â· Faust Â· RtAudio Â· liblo OSC Â· uWebSockets Â· **Raspberry Pi 3 (BCM2837 / Cortex-A53)**

---

## Ãndice

1. [VisiÃ³n General del Sistema](#1-visiÃ³n-general-del-sistema)
2. [Diagrama de Arquitectura Global](#2-diagrama-de-arquitectura-global)
3. [Hardware: Raspberry Pi 3 â€” Especificaciones TÃ©cnicas](#3-hardware-raspberry-pi-3--especificaciones-tÃ©cnicas)
4. [MÃ³dulo Core â€” Dominio del Sintetizador](#4-mÃ³dulo-core--dominio-del-sintetizador)
5. [Motor DSP â€” Pipeline de Audio (Faust + RtAudio)](#5-motor-dsp--pipeline-de-audio-faust--rtaudio)
6. [DiseÃ±o del Buffer de Audio](#6-diseÃ±o-del-buffer-de-audio)
7. [Arquitectura AcÃºstica del Sintetizador](#7-arquitectura-acÃºstica-del-sintetizador)
8. [Sistema de Reloj Maestro (MasterClock)](#8-sistema-de-reloj-maestro-masterclock)
9. [Conexiones OSC â€” Protocolo y Rutas](#9-conexiones-osc--protocolo-y-rutas)
10. [Vista Completa desde Raspberry Pi 3](#10-vista-completa-desde-raspberry-pi-3)
11. [Vista desde Windows (WASAPI)](#11-vista-desde-windows-wasapi)
12. [SincronizaciÃ³n GPIO â€” Reloj de Hardware Externo](#12-sincronizaciÃ³n-gpio--reloj-de-hardware-externo)
13. [Sistema de Estado â€” Presets y AutomatizaciÃ³n](#13-sistema-de-estado--presets-y-automatizaciÃ³n)
14. [Flujo de Arranque Completo](#14-flujo-de-arranque-completo)
15. [Tablas de ParÃ¡metros](#15-tablas-de-parÃ¡metros)
16. [Dependencias y CompilaciÃ³n](#16-dependencias-y-compilaciÃ³n)

---

## 1. VisiÃ³n General del Sistema

**Bazz SynthServer** es un servidor de sÃ­ntesis de audio en tiempo real, inspirado en la TR-808 de Roland, diseÃ±ado como una caja de ritmos algorÃ­tmica con sÃ­ntesis procedural completamente en software. El sistema estÃ¡ optimizado para correr en modo **headless** (sin pantalla ni teclado) sobre una **Raspberry Pi 3**, actuando como instrumento de hardware dedicado, controlado remotamente vÃ­a red OSC desde cualquier dispositivo.

### Pilares tecnolÃ³gicos

| Pilar | TecnologÃ­a | Rol |
|---|---|---|
| **SÃ­ntesis DSP** | Faust â†’ C++ transpilado | Motor de sÃ­ntesis (untitled.cpp) |
| **E/S de Audio** | RtAudio + ALSA | ComunicaciÃ³n con el hardware DAC |
| **Control Remoto** | liblo (OSC/UDP) | ParÃ¡metros en tiempo real vÃ­a red |
| **Interfaz Web** | uWebSockets + libuv | UI en navegador por WebSocket |
| **Estado** | nlohmann/json | Persistencia de presets en disco |
| **SincronizaciÃ³n** | GPIO 17 + MasterClock | Reloj analÃ³gico desde hardware externo |

### FilosofÃ­a de diseÃ±o

- **Lock-free entre hilos**: todos los parÃ¡metros son `std::atomic<float>`, sin mutex en el camino de audio.
- **Tiempo real estricto**: el callback de audio nunca llama a `new`, `malloc`, ni E/S de disco.
- **Bajo consumo**: diseÃ±ado para el Cortex-A53 de la RPi 3, con vectorizaciÃ³n NEON explÃ­cita.
- **RecuperaciÃ³n automÃ¡tica**: al apagarse, guarda `preset.json`; al encender, lo restaura.

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
[ Controladores Externos ] â”€â”€UDP/WebSocketâ”€â”€â–¶ [ Capa OSC/Web ]
                                                      â”‚
                                                      â–¼ param->setValue() lock-free
                                              [ Capa Core - Synthesizer ]
                                              [ Parameter(atomic) + MasterClock ]
                                                      â”‚
                                          updateDSPValues() cada callback
                                                      â”‚
                                                      â–¼
                                           [ Capa Audio - Faust DSP ]
                                           compute(256 frames, in, out)
                                                      â”‚
                                                      â–¼
                                             [ Hardware DAC / ALSA ]
                                             Jack 3.5mm / USB Audio
```

---

## 3. Hardware: Raspberry Pi 3 â€” Especificaciones TÃ©cnicas

### SoC y CPU

| Componente | Detalle |
|---|---|
| **SoC** | Broadcom BCM2837 |
| **CPU** | ARM Cortex-A53 (ARMv8-A, 64-bit) |
| **NÃºcleos** | 4 nÃºcleos @ **1.2 GHz** (RPi 3B) / **1.4 GHz** (RPi 3B+) |
| **Arquitectura** | AArch64 (64-bit) / AArch32 compatible |
| **Cache L1** | 32 KB instrucciones + 32 KB datos por nÃºcleo |
| **Cache L2** | 512 KB compartida (todos los nÃºcleos) |
| **RAM** | **1 GB LPDDR2 @ 900 MHz** |
| **GPU** | VideoCore IV @ 400 MHz (no se usa para audio) |
| **SIMD** | ARM NEON (Advanced SIMD) â€” 128-bit vectorizaciÃ³n |

### Interfaces de conectividad

| Interfaz | Detalle RPi 3B | Detalle RPi 3B+ |
|---|---|---|
| **Ethernet** | 100 Mbps (LAN9514) | ~300 Mbps via USB3 (LAN7515) |
| **WiFi** | 802.11 b/g/n (2.4 GHz) | 802.11 b/g/n/ac (2.4 + 5 GHz) |
| **Bluetooth** | BT 4.1 + BLE | BT 4.2 + BLE |
| **USB** | 4x USB 2.0 (bus compartido) | 4x USB 2.0 (bus compartido) |
| **GPIO** | 40 pines (3.3V lÃ³gica) | 40 pines (3.3V lÃ³gica) |
| **Audio** | Jack 3.5mm (bcm2835 PWM) + HDMI | Ãdem |
| **Consumo** | ~2.5W tÃ­pico, ~6.7W mÃ¡x | ~2.5W tÃ­pico, ~6.7W mÃ¡x |
| **AlimentaciÃ³n** | 5V / 2.5A microUSB | 5V / 2.5A microUSB |

### Audio en la Raspberry Pi 3

La RPi 3 usa el driver `snd_bcm2835` que implementa dos salidas nativas:

```
BCM2837 SoC
â”œâ”€â”€ PWM0  â”€â”€â”€â”€â”€â”€â”
â”‚               â”œâ”€â”€ RC filter pasivo â”€â”€â”€â”€ Jack 3.5mm (snd_bcm2835 Headphones)
â””â”€â”€ PWM1  â”€â”€â”€â”€â”€â”€â”˜                         ResoluciÃ³n: 11-bit efectivos @ 48kHz
                                          SNR: ~70 dB (limitado por PWM)
â””â”€â”€ HDMI I2S â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ HDMI Audio (snd_bcm2835 HDMI)
                                          ResoluciÃ³n: 16-bit

[ USB DAC externo ]
â””â”€â”€ snd_usb_audio â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ USB 2.0 (Clase USB Audio)
                                          Hasta 24-bit / 192kHz (depende del DAC)
                                          RECOMENDADO para producciÃ³n
```

> **RecomendaciÃ³n**: Para audio de calidad usar un **USB DAC** (ej: Behringer UCA202, IQaudio DAC+, o cualquier interfaz clase USB Audio). El jack 3.5mm nativo tiene ruido PWM audible.

### Mapa de pines GPIO (40 pines)

```
Raspberry Pi 3 â€” Conector GPIO J8 (40 pines)
â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
â”‚ Pin FÃ­sâ”‚ GPIO â”‚ FunciÃ³n  â”‚ Uso en este proyecto                   â”‚
â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
â”‚  1     â”‚  â€”   â”‚ 3.3V PWR â”‚ AlimentaciÃ³n de lÃ³gica (NO usar como out)â”‚
â”‚  2     â”‚  â€”   â”‚ 5V PWR   â”‚ AlimentaciÃ³n 5V                        â”‚
â”‚  6     â”‚  â€”   â”‚ GND      â”‚ Masa general                           â”‚
â”‚  9     â”‚  â€”   â”‚ GND      â”‚ GND de referencia del reloj externo    â”‚
â”‚  11    â”‚  17  â”‚ GPIO IN  â”‚ *** CLOCK IN â€” Entrada de voltaje sync ***â”‚
â”‚  12    â”‚  18  â”‚ GPIO     â”‚ Disponible (PCM_CLK si se usa I2S DAC) â”‚
â”‚  14    â”‚  â€”   â”‚ GND      â”‚ Masa adicional                         â”‚
â”‚  19    â”‚  10  â”‚ SPI_MOSI â”‚ SPI (si se usa DAC por SPI)            â”‚
â”‚  21    â”‚  9   â”‚ SPI_MISO â”‚ SPI                                    â”‚
â”‚  23    â”‚  11  â”‚ SPI_CLK  â”‚ SPI                                    â”‚
â”‚  24    â”‚  8   â”‚ SPI_CE0  â”‚ SPI Chip Select 0                      â”‚
â”‚  35    â”‚  19  â”‚ PCM_FS   â”‚ I2S DAC Frame Sync                     â”‚
â”‚  38    â”‚  20  â”‚ PCM_DIN  â”‚ I2S DAC Data IN                        â”‚
â”‚  40    â”‚  21  â”‚ PCM_DOUT â”‚ I2S DAC Data OUT                       â”‚
â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

CONEXIÃ“N CRÃTICA:
  Pin 11 (GPIO 17) â”€â”€â”€â”€ SeÃ±al Clock/Gate externa (mÃ¡x 3.3V)
  Pin 9  (GND)     â”€â”€â”€â”€ Masa del dispositivo externo
```

### Rendimiento DSP en el Cortex-A53

El Cortex-A53 es un nÃºcleo **in-order** (a diferencia del out-of-order Cortex-A72 del RPi 4). Esto tiene implicaciones para el DSP:

```
Cortex-A53 @ 1.2 GHz:
  Ciclos por segundo:    1,200,000,000
  Muestras por segundo:  48,000
  Ciclos por muestra:    1,200,000,000 / 48,000 = 25,000 ciclos/muestra

NEON (Advanced SIMD):
  Procesa 4x float32 en paralelo por instrucciÃ³n VMUL/VADD
  Throughput VMUL.F32:  1 instrucciÃ³n por ciclo (pipeline completo)
  Throughput efectivo:  4 muestras Ã— 1.2 GHz = 4.8 GFLOPS de punto flotante

Tiempo de buffer (256 frames):
  Buffer de audio:  256 / 48000 = 5.33 ms disponibles por callback
  Uso tÃ­pico DSP:   ~2-3 ms (40-60% de CPU en RPi 3)
  Margen seguro:    ~2-3 ms (headroom para jitter del SO)
```

---

## 4. MÃ³dulo Core â€” Dominio del Sintetizador

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

### DiseÃ±o lock-free de parÃ¡metros

El diseÃ±o garantiza **cero bloqueos** entre el hilo de audio (tiempo real) y los hilos de red (OSC / WebSocket):

```
â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
â”‚                    MODELO DE CONCURRENCIA                           â”‚
â”‚                                                                     â”‚
â”‚  Hilo OSC (red, no RT)          Hilo Audio (RT, ALSA callback)     â”‚
â”‚  â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€          â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€     â”‚
â”‚  param->setValue(v)             ui->updateDSPValues()              â”‚
â”‚    â”‚                              â”‚                                 â”‚
â”‚    â–¼                              â–¼                                 â”‚
â”‚  m_value.store(v,               *dsp_zone = m_value.load(          â”‚
â”‚    memory_order_release)          memory_order_acquire)            â”‚
â”‚                                                                     â”‚
â”‚  GARANTÃA: release/acquire pair â”€â–¶ visibilidad total sin mutex     â”‚
â”‚  COSTO:    ~1 ciclo de CPU (una instrucciÃ³n DMB/STLR en AArch64)   â”‚
â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
```

**Instrucciones ARM generadas para RPi 3 (AArch64):**
```asm
; store con memory_order_release â†’ STLR (Store-Release)
STLR  W0, [X1]        ; atÃ³mica, barrera de memoria implÃ­cita

; load con memory_order_acquire â†’ LDAR (Load-Acquire)
LDAR  W0, [X1]        ; atÃ³mica, barrera de memoria implÃ­cita
```

Esto es mÃ¡s eficiente que `std::mutex` (que requiere syscalls `futex` costosas).

### Mapa de parÃ¡metros por ruta OSC

```
Synthesizer::m_parameters
â”œâ”€â”€ "/master/bpm"        â† Parameter(20.0, 999.0, 140.0)
â”œâ”€â”€ "/master/accent"     â† Parameter(0.0, 1.0, 0.5)
â”œâ”€â”€ "/kick/vol"          â† Parameter(0.0, 1.0, 0.114)
â”œâ”€â”€ "/kick/tune"         â† Parameter(0.0, 1.0, 0.463)
â”œâ”€â”€ "/kick/dec"          â† Parameter(0.01, 1.0, 0.07)
â”œâ”€â”€ "/kick/sweep"        â† Parameter(0.0, 500.0, 150.0)
â”œâ”€â”€ "/snare/vol"         â† Parameter(0.0, 1.0, 0.0)
â”œâ”€â”€ "/snare/dec_cuerpo"  â† Parameter(0.01, 1.0, 0.07)
â”œâ”€â”€ "/hat/vol"           â† Parameter(0.0, 1.0, 0.0)
â”œâ”€â”€ "/hat/cutoff"        â† Parameter(500.0, 20000.0, 4754.86)
â”œâ”€â”€ "/bass/vol"          â† Parameter(0.0, 1.0, 0.0)
â”œâ”€â”€ "/bass/detune"       â† Parameter(0.0, 0.5, 0.04)
â”œâ”€â”€ "/syn1/vol"          â† Parameter(0.0, 1.0, 0.03)
â”œâ”€â”€ "/syn2/vol"          â† Parameter(0.0, 1.0, 0.22)
â”œâ”€â”€ "/emulator/active"   â† Parameter(0.0, 1.0, 0.0)   [manual]
â””â”€â”€ "/emulator/bpm"      â† Parameter(60.0, 240.0, 137.0) [manual]
    ... (todos los parametros del DSP Faust)
```

---

## 5. Motor DSP â€” Pipeline de Audio (Faust + RtAudio)

### Diagrama de flujo del callback de audio

```mermaid
flowchart TD
    CB_START(["RtAudio llama audioCallback cada 5.33ms"])

    CB_START --> CLOCK_A
    CLOCK_A{"Hay inputBuffer con seÃ±al de voltaje?"}
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

    UPDATE_PARAMS["ui->updateDSPValues - Copiar atomicos a memoria DSP - *zone = param->getValue()"]
    UPDATE_PARAMS --> COMPUTE

    COMPUTE["faust_dsp->compute 256 frames - Motor Faust ejecuta 6 voces - Escribe outL y outR"]
    COMPUTE --> INTERLEAVE

    INTERLEAVE["Intercalar para RtAudio - out 2i = outL i - out 2i+1 = outR i"]
    INTERLEAVE --> RETURN(["return 0 - RtAudio envia al DAC ALSA"])
```

### ConfiguraciÃ³n del stream ALSA en Raspberry Pi 3

| ParÃ¡metro | Valor | JustificaciÃ³n para RPi 3 |
|---|---|---|
| **Sample Rate** | 48,000 Hz | Soportado nativamente por bcm2835 y USB DAC |
| **Buffer Size** | 256 frames | 5.33 ms â€” balance ideal CPU/latencia en Cortex-A53 |
| **Formato** | RTAUDIO_FLOAT32 | 32-bit float normalizado Â±1.0 |
| **Canales salida** | 2 (Stereo) | Definido por Faust `getNumOutputs()` |
| **Canales entrada** | 1 (Mono) | Para detecciÃ³n de voltaje de reloj analÃ³gico |
| **API Linux** | ALSA (`__LINUX_ALSA__`) | Driver nativo del kernel, sin PulseAudio overhead |
| **Dispositivo** | auto o ID manual | `0` = default, `1` = headphones, `2` = USB DAC |

### Hilo de audio en Linux (ALSA + POSIX RT)

```
RtAudio en Linux crea un hilo POSIX dedicado para el callback:

  POSIX thread (pthread_create)
  â”œâ”€â”€ PolÃ­tica de scheduling: SCHED_FIFO (tiempo real)
  â”œâ”€â”€ Prioridad: 80 (de 0 a 99, mayor = mÃ¡s prioritario)
  â”œâ”€â”€ CPU affinity: ninguna fija (SO asigna al nÃºcleo libre)
  â””â”€â”€ Stack size: default (~8 MB)

  En RPi 3 con 4 nÃºcleos Cortex-A53:
    NÃºcleo 0: generalmente reservado para interrupciones del SO
    NÃºcleo 1: hilo de audio (SCHED_FIFO, prioridad alta)
    NÃºcleo 2: hilo OSC + WebSocket
    NÃºcleo 3: hilo principal (consola) + systemd
```

---

## 6. DiseÃ±o del Buffer de Audio

### Problema: Intercalado vs No-intercalado

RtAudio y Faust usan formatos de buffer diferentes. El callback resuelve esto con buffers estÃ¡ticos intermedios:

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
Buffers estÃ¡ticos (static local, asignados al inicio):
  static float outL[4096]  â†’  4096 Ã— 4 bytes = 16,384 bytes = 16 KB
  static float outR[4096]  â†’  4096 Ã— 4 bytes = 16,384 bytes = 16 KB
  float* faustOut[2]       â†’  2 Ã— 8 bytes    =     16 bytes

  Total por callback: ~32 KB en stack estÃ¡tico

  RAM total disponible en RPi 3:  1,024 MB
  RAM usada por el proceso:       ~50-80 MB (cÃ³digo + Faust DSP)
  Headroom disponible:            ~900 MB (amplio margen)
```

> **Regla de tiempo real**: Los buffers usan `static` â€” el compilador los coloca en BSS/data segment, nunca en heap. En el callback de audio **no se llama a `new`, `malloc`, `free`, ni a ninguna funciÃ³n de E/S**. Esto es esencial para evitar *priority inversion* y *jitter* en ALSA.

### AnÃ¡lisis de latencia completa en Raspberry Pi 3

```
Cadena de latencia de audio (RPi 3, ALSA, 256 frames @ 48kHz):

  â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
  â”‚ Etapa                          â”‚ Latencia   â”‚ Notas        â”‚
  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
  â”‚ SÃ­ntesis Faust (6 voces)       â”‚ ~1.5-2 ms  â”‚ DSP puro     â”‚
  â”‚ Buffer RtAudio (256 frames)    â”‚  5.33 ms   â”‚ fijo         â”‚
  â”‚ Driver ALSA (snd_bcm2835)      â”‚  ~2-4 ms   â”‚ doble buffer â”‚
  â”‚ DAC bcm2835 PWM (jack 3.5mm)   â”‚  ~0.2 ms   â”‚ RC filter    â”‚
  â”‚ DAC USB externo (si se usa)    â”‚  ~1-3 ms   â”‚ USB latency  â”‚
  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
  â”‚ TOTAL (jack nativo)            â”‚  ~9-11 ms  â”‚ aceptable    â”‚
  â”‚ TOTAL (USB DAC)                â”‚  ~10-14 ms â”‚ OK para ritmoâ”‚
  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

Latencia musical percibida:
  A 140 BPM, un beat dura 428 ms.
  Una latencia de 10 ms = 10/428 = 2.3% del beat.
  Imperceptible musicalmente (umbral humano â‰ˆ 20-30 ms).
```

---

## 7. Arquitectura AcÃºstica del Sintetizador

El sintetizador implementa **6 voces de sÃ­ntesis** independientes, cada una con un modelo fÃ­sico/matemÃ¡tico propio:

### Mapa de voces y tÃ©cnicas

```mermaid
graph LR
    KICK["Kick - Bombo"] --> FM_SWEEP["FM Synthesis con Sweep exponencial"]
    SNARE["Snare - Caja"] --> BODY_NOISE["Resonador tonal + Ruido filtrado BPF"]
    HAT["Hat - Platillo"] --> METAL_OSC["6 Osciladores de frecuencia prima"]
    BASS["Bass - Bajo"] --> WAVEGUIDE["Karplus-Strong Waveguide extendido"]
    SYN1["Syn1 - Oscilador"] --> AM_LFO["Sintesis AM con modulacion LFO"]
    SYN2["Syn2 - FDN Synth"] --> FDN_NET["Feedback Delay Network Hadamard"]
```

### MatemÃ¡tica detallada de sÃ­ntesis por voz

#### Bombo (Kick) â€” FM + Sweep Exponencial

El bombo emula el comportamiento de una membrana percutida: alta frecuencia al inicio que decae exponencialmente.

```
MODELO FÃSICO: Membrana circular tensada (aproximaciÃ³n de modos)

Frecuencia instantÃ¡nea:
  f(t) = f_base + sweep Ã— e^(âˆ’t / Ï„_f)

  f_base  = nota_MIDI â†’ Hz = 440 Ã— 2^((nota âˆ’ 69) / 12)
  sweep   = barrido en Hz    â†’ parÃ¡metro /kick/sweep (0â€“500 Hz)
  Ï„_f     = constante de tiempo de frecuencia â‰ˆ dec/3
  t       = tiempo desde el trigger [segundos]

Ãngulo de fase acumulado (integraciÃ³n de la frecuencia instantÃ¡nea):
  Ï†(t) = 2Ï€ âˆ«â‚€áµ— f(Ï„) dÏ„
       = 2Ï€ [ f_baseÂ·t  âˆ’  sweepÂ·Ï„_fÂ·(e^(âˆ’t/Ï„_f) âˆ’ 1) ]

SeÃ±al de salida:
  y(t) = A(t) Ã— sin(Ï†(t))

Envolvente de amplitud (Percussive Exponential):
  A(t) = e^(âˆ’t / Ï„_A)
  Ï„_A = dec Ã— 1.5   â†’ parÃ¡metro /kick/dec

Compresor interno (Waveshaper):
  y_comp = sgn(y) Ã— (1 âˆ’ e^(âˆ’|y| Ã— drive))  si comp_thresh activo
```

#### Caja (Snare) â€” Modelo Cuerpo + Resorte

```
MODELO FÃSICO: Parche superior (tonal) + resortes de snare (ruido)

SeÃ±al total:
  y(t) = mix Ã— y_body(t) + (1 âˆ’ mix) Ã— y_spring(t)

--- CUERPO (componente tonal) ---
  y_body(t) = sin(2Ï€ Ã— f_body Ã— t) Ã— e^(âˆ’t / Ï„_body)

  f_body  = /snare/freq  (Hz)  â€” resonancia del parche
  Ï„_body  = /snare/dec_cuerpo

  Filtrado adicional:
  BPF centrado en f_body con Q = /snare/q
  HP a f = /snare/hp para eliminar sub-graves

--- RESORTES (componente de ruido) ---
  n(t) = ruido_blanco_uniforme()  âˆˆ [âˆ’1, 1]

  y_spring_raw(t) = BPF[fc=/snare/freq, Q=/snare/q]( n(t) )
  y_spring(t)     = y_spring_raw(t) Ã— e^(âˆ’t / Ï„_spring)
  Ï„_spring        = /snare/dec_resorte

  SaturaciÃ³n armÃ³nica (drive):
  y_spring = tanh(y_spring Ã— drive) / tanh(drive)

  AfinaciÃ³n: semitonos = /snare/tune
  TransposiciÃ³n: f_body = f_body Ã— 2^(tune/12)
```

#### Platillo (Hat) â€” Banco de Osciladores MetÃ¡licos

```
MODELO FÃSICO: Plato de metal con modos de vibraciÃ³n no armÃ³nicos

La metalicidad se logra con 6 osciladores a frecuencias primas (no armÃ³nicas):
  ratio_primos = [1.0, 1.413, 1.732, 2.145, 2.618, 3.000]

  f_n = f_base Ã— ratio_primos[n]    n = 0..5
  f_base se controla con /hat/tune

  SeÃ±al bruta:
  y_metal(t) = Î£(n=0 a 5) sin(2Ï€ Ã— f_n Ã— t)

  Filtrado:
  y_filt = HPF[fc=2000Hz](LPF[fc=/hat/cutoff](y_metal))

  Envolvente:
  A(t) = e^(âˆ’t / Ï„_hat)
  Ï„_hat = /hat/dec

  Mix open/closed:
  y(t) = mix Ã— A_closed(t) + (1âˆ’mix) Ã— A_open(t)

  SaturaciÃ³n: y = tanh(y Ã— drive)
```

#### Bajo Waveguide â€” Karplus-Strong Extendido

```
MODELO FÃSICO: Cuerda pulsada con reflexiÃ³n en los extremos

Algoritmo Karplus-Strong:
  InicializaciÃ³n (trigger):
    delay_line[0..L-1] = ruido_uniforme() Ã— 0.5

  Por cada muestra n:
    y[n] = 0.5 Ã— (delay_line[(n-L) mod L] + delay_line[(n-L-1) mod L])
    y[n] = y[n] Ã— g_decay               â† amortiguamiento
    delay_line[n mod L] = y[n]

  Longitud del delay (afinaciÃ³n):
    L = round(Fs / f_nota)
    f_nota = 440 Ã— 2^((nota âˆ’ 69) / 12)
    Fs = 48000 Hz

  Factor de decaimiento por muestra:
    g_decay = e^(âˆ’1 / (Ï„_dec Ã— Fs))
    Ï„_dec = /bass/dec

  EXTENSIÃ“N 1 â€” Detune (coro de 2 voces):
    L_1 = L
    L_2 = round(L Ã— (1 + detune))      â† /bass/detune
    Salida = (y_1 + y_2) / 2

  EXTENSIÃ“N 2 â€” SaturaciÃ³n armÃ³nica:
    y_out = tanh(y Ã— drive) / tanh(drive)  â† /bass/drive

  EXTENSIÃ“N 3 â€” LFO de modulaciÃ³n:
    f_lfo = 0.1 + lfo_depth Ã— 10        â† /bass/lfo
    L_mod = L Ã— (1 + 0.01 Ã— sin(2Ï€ Ã— f_lfo Ã— t))
```

#### Syn2 â€” FDN (Feedback Delay Network)

```
MODELO: ReverberaciÃ³n sintÃ©tica con densidad modal controlable

Red de N=4 delays con retroalimentaciÃ³n matricial:

  Para cada muestra n:
    x_in[i] = input[n]  +  Î£(j=0 a 3) H[i][j] Ã— y[n-1][j]
    y[n][i]  = x_in[i]   (despues de pasar por delay_line[i])

  Longitudes de delay (dispersivas, basadas en primos):
    primos = [29, 37, 41, 53]
    L_i = round(disp Ã— 48000 Ã— 0.005 Ã— primos[i] / 53)
    /syn2/disp controla la densidad de ecos (0.0 = muy seco, 1.0 = muy denso)

  Matriz de mezcla H (Hadamard normalizada 4Ã—4):
    H = (1/2) Ã— | 1  1  1  1 |
                 | 1 -1  1 -1 |
                 | 1  1 -1 -1 |
                 | 1 -1 -1  1 |

  La matriz Hadamard garantiza:
    - Mezcla perfecta sin cancelaciones de fase
    - Densidad modal uniforme
    - Estabilidad garantizada (valor singular mÃ¡ximo = 1)

  LFO de modulaciÃ³n de delays:
    Ï†_lfo[n] = 2Ï€ Ã— f_lfo Ã— n / Fs     â† /syn2/lfo_f y /syn2/lfo_p
    L_i_mod = L_i Ã— (1 + 0.005 Ã— sin(Ï†_lfo + Ï€Ã—i/2))

  Compresor de salida (limitador dinÃ¡mico):
    gain = 10^(comp_th / 20)            â† /syn2/comp_th en dBFS
    y_comp = limiter(y_out, gain, attack, release)
```

---

## 8. Sistema de Reloj Maestro (MasterClock)

El `MasterClock` es el corazÃ³n temporal del sistema. Recibe pulsos de **tres fuentes** y exporta el BPM suavizado a todo el motor DSP.

### Diagrama de decisiÃ³n del MasterClock

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

    BPM_CRUDO["new_bpm = 60000.0 / delta_ms"]
    BPM_CRUDO --> SUAVIZADO

    OSC_VALIDATE["Validar: 20 menor bpm menor 999"]
    OSC_VALIDATE --> EXT_ACTIVO{"Reloj externo activo en ultimos 2000ms?"}
    EXT_ACTIVO -->|"Si - hardware tiene prioridad"| IGNORAR["Ignorar OSC /master/bpm"]
    EXT_ACTIVO -->|"No - sin hardware"| STORE_DIRECTO["m_bpm.store directo sin suavizado"]

    EMU_CALC["interval_ms = 60000 / emu_bpm - Generar pulso periodico en audioCallback"]
    EMU_CALC --> SUAVIZADO

    SUAVIZADO["LPF: smoothed = prev x 0.7 + new_bpm x 0.3"]
    SUAVIZADO --> ATOMICO["m_bpm.store smoothed - memory_order_release - m_externalBpm.store smoothed - m_lastExternalPulseMs.store t_ms"]

    ATOMICO --> FAUST_SYNC["FaustMapUI.updateDSPValues - bpmParam->setValue m_bpm.load - *zone_bpm = bpm_actual"]
    STORE_DIRECTO --> FAUST_SYNC
```

### MatemÃ¡tica del filtro IIR de primer orden (suavizado de BPM)

El BPM crudo detectado tiene jitter (variaciÃ³n pulso a pulso). Se aplica un filtro paso-bajo exponencial:

```
FILTRO IIR DE PRIMER ORDEN (Exponential Moving Average):

  BPM_s[n] = Î± Ã— BPM_raw[n] + (1âˆ’Î±) Ã— BPM_s[nâˆ’1]

  Con Î± = 0.3:
  BPM_s[n] = 0.3 Ã— BPM_raw[n] + 0.7 Ã— BPM_s[nâˆ’1]

FUNCIÃ“N DE TRANSFERENCIA EN DOMINIO Z:
  H(z) = Î± / (1 âˆ’ (1âˆ’Î±)Â·zâ»Â¹)
       = 0.3 / (1 âˆ’ 0.7Â·zâ»Â¹)

  Polo en z = 0.7  â†’  estable (|polo| < 1)
  Frecuencia de corte: fc = arccos(0.7) / (2Ï€) Ã— f_Nyquist

CONVERGENCIA (respuesta al escalÃ³n de BPM):
  BPM_s[N] = BPM_final Ã— (1 âˆ’ 0.7^N)

  N = 1  â†’  30.0%  convergencia
  N = 3  â†’  65.7%  convergencia
  N = 5  â†’  83.2%  convergencia
  N = 10 â†’  97.2%  convergencia
  N = 20 â†’  99.9%  convergencia

TIEMPO DE RESPUESTA A 140 BPM:
  Intervalo entre pulsos = 60000 / 140 = 428.6 ms
  Al 83% (5 pulsos):  5 Ã— 428.6 ms = 2.14 segundos
  Al 97% (10 pulsos): 10 Ã— 428.6 ms = 4.29 segundos

JITTER ATENUADO:
  Si el jitter de un pulso es Â±5 ms (error relativo = 5/428 = 1.17%),
  el filtro lo atenÃºa en cada paso por factor 0.3:
  Jitter_filtrado â‰ˆ 0.3 Ã— 5 ms = 1.5 ms de variaciÃ³n residual.
  A 140 BPM esto representa < 0.35% de error de tempo.
```

### Timeout y prioridad de reloj

```
isExternalClockActive():
  now_ms      = steady_clock::now() en milisegundos
  last_pulse  = m_lastExternalPulseMs.load(acquire)
  return (now_ms âˆ’ last_pulse) < 2000.0

LÃ“GICA DE PRIORIDAD:
  1. Reloj analÃ³gico GPIO (mÃ¡xima prioridad)
     â†’ Si llega pulso de voltaje: syncPulse() y resetea el timeout
  2. Reloj OSC /master/bpm
     â†’ Solo actÃºa si isExternalClockActive() == false (timeout > 2s)
  3. Emulador interno (/emulator/active = 1)
     â†’ Genera pulsos periÃ³dicos en el callback de audio
     â†’ Puede coexistir con OSC, pero tiene menor prioridad que GPIO
```

---

## 9. Conexiones OSC â€” Protocolo y Rutas

### Â¿QuÃ© es OSC?

**Open Sound Control (OSC)** es un protocolo de comunicaciÃ³n para dispositivos musicales, sucesor espiritual del MIDI. Usa UDP sobre IP, lo que lo hace extremadamente rÃ¡pido y flexible. Cada mensaje OSC contiene:

```
Paquete UDP OSC:
â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
â”‚ Address Pattern: string terminado en null con padding    â”‚
â”‚   Ejemplo: "/kick/vol\0\0\0"  (mÃºltiplo de 4 bytes)      â”‚
â”‚                                                          â”‚
â”‚ Type Tag String: ",f\0\0" (coma + tipos + nulls)         â”‚
â”‚   f = float32, i = int32, s = string, b = blob           â”‚
â”‚                                                          â”‚
â”‚ Arguments: datos en big-endian                           â”‚
â”‚   float32: 4 bytes IEEE 754                              â”‚
â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

TamaÃ±o tÃ­pico de un mensaje /kick/vol con 1 float:
  12 bytes (address) + 8 bytes (type tag) + 4 bytes (float) = 24 bytes
  Esto es ~70x mÃ¡s compacto que JSON equivalente.
```

### Flujo del servidor OSC

```mermaid
flowchart TD
    CLIENT_OSC(["Cliente OSC - TouchOSC, Python, PD, MaxMSP"])
    CLIENT_OSC -->|"Paquete UDP a Puerto 8000"| RECV_UDP

    RECV_UDP["lo_server_thread recibe paquete UDP"]
    RECV_UDP --> PARSE_OSC["Parsear header OSC - Extraer path, types, argv"]
    PARSE_OSC --> ROUTE{"Ruta OSC recibida?"}

    ROUTE -->|"/clock/sync"| HANDLE_CLOCK["getClock()->syncPulse(timestamp_ms)"]
    ROUTE -->|"/master/bpm f"| HANDLE_BPM["clock->setBpm(argv0) si no hay reloj externo"]
    ROUTE -->|"/preset/save s"| HANDLE_SAVE["presetMgr->savePreset(filename)"]
    ROUTE -->|"/preset/load s"| HANDLE_LOAD["presetMgr->loadPreset(filename)"]
    ROUTE -->|"/automation/start"| HANDLE_AUTO_S["recorder->startRecording()"]
    ROUTE -->|"/automation/stop"| HANDLE_AUTO_E["recorder->stopRecording()"]
    ROUTE -->|"/audio/device i"| HANDLE_DEV["audioBackend->changeDevice(id)"]
    ROUTE -->|"Cualquier parametro DSP"| HANDLE_PARAM

    HANDLE_PARAM["param = synth->getParameter(path)"]
    HANDLE_PARAM --> EXISTS{"Parametro existe en el mapa?"}
    EXISTS -->|"No"| LOG_WARN["Log: Ruta OSC desconocida - ignorar"]
    EXISTS -->|"Si"| ATOMIC_SET["param->setValue(argv0->f) - store atomic release - lock-free"]

    ATOMIC_SET --> NEXT_CB(["Proximo audioCallback lee el valor actualizado"])
```

### Tabla de rutas OSC â€” Referencia completa

#### Globales / Master

| Ruta | Tipo | Rango | Default | DescripciÃ³n |
|---|---|---|---|---|
| `/master/bpm` | `f` | 20 â€“ 999 | 140.0 | Tempo maestro BPM |
| `/master/accent` | `f` | 0.0 â€“ 1.0 | 0.5 | AcentuaciÃ³n global |
| `/master/nota` | `f` | 0 â€“ 127 | 36 | Nota raÃ­z MIDI |
| `/master/groove` | `f` | 0 â€“ 6 | 0 | PatrÃ³n algorÃ­tmico |
| `/clock/sync` | â€” | â€” | â€” | Pulso de reloj externo |
| `/emulator/active` | `f` | 0 / 1 | 0 | Emulador de clock on/off |
| `/emulator/bpm` | `f` | 60 â€“ 240 | 137 | BPM del emulador |

#### Bombo (Kick)

| Ruta | Tipo | Rango | Default | DescripciÃ³n |
|---|---|---|---|---|
| `/kick/vol` | `f` | 0.0 â€“ 1.0 | 0.114 | Volumen |
| `/kick/tune` | `f` | 0.0 â€“ 1.0 | 0.463 | AfinaciÃ³n base |
| `/kick/dec` | `f` | 0.01 â€“ 1.0 | 0.07 | Decaimiento |
| `/kick/sweep` | `f` | 0 â€“ 500 | 150 | Barrido de frecuencia Hz |
| `/kick/mix` | `f` | 0.0 â€“ 1.0 | 0.425 | Mix cuerpo/tono |
| `/kick/groove` | `f` | 0 â€“ 6 | 2 | PatrÃ³n rÃ­tmico |
| `/kick/swing` | `f` | 0 â€“ 100 | 0 | Swing porcentaje |
| `/kick/accent` | `f` | 0.0 â€“ 1.0 | 0.5 | Velocidad de acento |
| `/kick/comp_thresh` | `f` | 0.0 â€“ 1.0 | 0.4 | Umbral compresor |
| `/kick/comp_ratio` | `f` | 1.0 â€“ 10.0 | 1.988 | Ratio compresion |
| `/kick/comp_drive` | `f` | 0.0 â€“ 5.0 | 1.036 | Drive saturacion |
| `/kick/comp_fmin` | `f` | 20 â€“ 500 | 100 | Freq min compresor |
| `/kick/comp_fmax` | `f` | 500 â€“ 20k | 7583 | Freq max compresor |
| `/kick/nota` | `f` | 0 â€“ 127 | 38 | Nota MIDI |
| `/kick/reloj` | `f` | 0.25 â€“ 4.0 | 0.25 | Division de tiempo |

#### Caja (Snare)

| Ruta | Tipo | Rango | Default | DescripciÃ³n |
|---|---|---|---|---|
| `/snare/vol` | `f` | 0.0 â€“ 1.0 | 0.0 | Volumen |
| `/snare/dec_cuerpo` | `f` | 0.01 â€“ 1.0 | 0.07 | Decay del cuerpo |
| `/snare/dec_resorte` | `f` | 0.01 â€“ 1.0 | 0.16 | Decay del resorte |
| `/snare/freq` | `f` | 100 â€“ 5000 | 1551 | Frecuencia resonancia |
| `/snare/q` | `f` | 0.1 â€“ 20.0 | 3.016 | Factor Q filtro |
| `/snare/hp` | `f` | 20 â€“ 500 | 184 | Corte highpass |
| `/snare/tune` | `f` | -24 â€“ +24 | -6.7 | Afinacion semitonos |
| `/snare/drive` | `f` | 0.0 â€“ 10.0 | 3.51 | Saturacion |
| `/snare/mix` | `f` | 0.0 â€“ 1.0 | 0.352 | Mix cuerpo-resorte |
| `/snare/groove` | `f` | 0 â€“ 6 | 4 | Patron ritmico |

#### Platillo (Hat)

| Ruta | Tipo | Rango | Default | DescripciÃ³n |
|---|---|---|---|---|
| `/hat/vol` | `f` | 0.0 â€“ 1.0 | 0.0 | Volumen |
| `/hat/dec` | `f` | 0.001 â€“ 2.0 | 0.15 | Decay |
| `/hat/tune` | `f` | -1.0 â€“ 1.0 | -0.005 | Afinacion osciladores |
| `/hat/cutoff` | `f` | 500 â€“ 20000 | 4754 | Cutoff filtro LP Hz |
| `/hat/mix` | `f` | 0.0 â€“ 1.0 | 0.611 | Mix closed/open |
| `/hat/drive` | `f` | 0.0 â€“ 1.0 | 0.206 | Saturacion |
| `/hat/ataque` | `f` | 0.001 â€“ 0.1 | 0.001 | Tiempo de ataque |
| `/hat/groove` | `f` | 0 â€“ 6 | 6 | Patron ritmico |
| `/hat/swing` | `f` | 0 â€“ 100 | 48.4 | Swing |

#### Bajo Waveguide (Bass)

| Ruta | Tipo | Rango | Default | DescripciÃ³n |
|---|---|---|---|---|
| `/bass/vol` | `f` | 0.0 â€“ 1.0 | 0.0 | Volumen |
| `/bass/nota` | `f` | 0 â€“ 127 | 43 | Nota MIDI base |
| `/bass/dec` | `f` | 0.01 â€“ 2.0 | 0.57 | Decaimiento waveguide |
| `/bass/detune` | `f` | 0.0 â€“ 0.5 | 0.04 | Detune efecto coro |
| `/bass/intervalo` | `f` | -24 â€“ +24 | -12 | Intervalo armonico |
| `/bass/drive` | `f` | 0.0 â€“ 2.0 | 0.65 | Saturacion armonica |
| `/bass/lfo` | `f` | 0.0 â€“ 1.0 | 0.45 | Profundidad LFO |
| `/bass/groove` | `f` | 0 â€“ 6 | 6 | Patron ritmico |
| `/bass/swing` | `f` | 0 â€“ 100 | 0 | Swing |

#### Sintetizador AM (Syn1)

| Ruta | Tipo | Rango | Default | DescripciÃ³n |
|---|---|---|---|---|
| `/syn1/vol` | `f` | 0.0 â€“ 1.0 | 0.03 | Volumen |
| `/syn1/nota` | `f` | 0 â€“ 127 | 45 | Nota base |
| `/syn1/dec` | `f` | 0.01 â€“ 2.0 | 0.12 | Decay |
| `/syn1/osc1` | `f` | 1 â€“ 100 | 11.01 | Ratio oscilador 1 |
| `/syn1/osc2` | `f` | 1 â€“ 100 | 18.63 | Ratio oscilador 2 |
| `/syn1/auto_p` | `f` | 0.0 â€“ 1.0 | 0.959 | Probabilidad auto |
| `/syn1/auto_r` | `f` | 0.0 â€“ 10.0 | 7.135 | Rango auto |
| `/syn1/auto_v` | `f` | 0.0 â€“ 1.0 | 0.805 | Velocidad auto |

#### Sintetizador FDN (Syn2)

| Ruta | Tipo | Rango | Default | DescripciÃ³n |
|---|---|---|---|---|
| `/syn2/vol` | `f` | 0.0 â€“ 1.0 | 0.22 | Volumen |
| `/syn2/dec` | `f` | 0.001 â€“ 2.0 | 0.01 | Decay ataque |
| `/syn2/nota` | `f` | 0 â€“ 127 | 24 | Nota base |
| `/syn2/disp` | `f` | 0.0 â€“ 1.0 | 0.654 | Dispersion modal FDN |
| `/syn2/lfo_f` | `f` | 0.1 â€“ 20.0 | 19.1 | Frecuencia LFO |
| `/syn2/lfo_p` | `f` | 0.0 â€“ 1.0 | 0.5 | Fase LFO |
| `/syn2/comp_th` | `f` | -60 â€“ 0 | -20 | Umbral compresor dBFS |
| `/syn2/comp_a` | `f` | 0.001 â€“ 1.0 | 0.069 | Attack compresor |
| `/syn2/comp_r` | `f` | 1 â€“ 20 | 6 | Ratio compresor |
| `/syn2/comp_rel` | `f` | 0.01 â€“ 2.0 | 0.1 | Release compresor |
| `/syn2/groove` | `f` | 0 â€“ 6 | 6 | Patron ritmico |

#### Control del sistema

| Ruta | Tipo | DescripciÃ³n |
|---|---|---|
| `/preset/save` | `s` | Guardar preset a archivo JSON |
| `/preset/load` | `s` | Cargar preset desde archivo JSON |
| `/automation/start` | â€” | Iniciar grabacion de automatizacion |
| `/automation/stop` | â€” | Detener grabacion |
| `/audio/device` | `i` | Cambiar dispositivo ALSA (ID entero) |

---

## 10. Vista Completa desde Raspberry Pi 3

### Diagrama de capas del sistema en RPi 3

```mermaid
graph TD
    LAN_CLIENT["Controlador Remoto - TouchOSC o Python - 192.168.x.y"]
    GPIO_DEVICE["Hardware Externo - Korg Volca o Eurorack"]

    subgraph RPI3["Raspberry Pi 3 - BCM2837 - Cortex-A53 - 1GB RAM"]
        ETH_WIFI["Ethernet 100Mbps o WiFi 802.11n"]
        GPIO17_NODE["Pin 11 GPIO17 - Entrada 3.3V max"]

        subgraph USER_SPACE["Espacio de Usuario - Raspbian OS"]
            SYNTH_PROC["BazzSynthServer proceso C++"]
            GPIO_DAEMON["pi_gpio_sync.py daemon"]
        end

        subgraph KERNEL_SPACE["Espacio de Kernel - Linux"]
            ALSA_DRIVER["ALSA - snd_bcm2835 o snd_usb_audio"]
            GPIO_DRIVER["GPIO driver - gpiochip0 - sysfs o gpiozero"]
            NET_STACK["Stack UDP-IP - loopback 127.0.0.1"]
        end

        subgraph HARDWARE_LAYER["Hardware BCM2837"]
            BCM_PWM["PWM0 y PWM1 - bcm2835 headphones"]
            BCM_I2S["I2S - Para DAC externo opcional"]
            USB_BUS["USB 2.0 bus - LAN9514 chip"]
        end
    end

    subgraph AUDIO_OUT["Salida de Audio"]
        JACK_35["Jack 3.5mm - Headphones"]
        USB_DAC["USB DAC externo - Recomendado"]
        HDMI_AUDIO["HDMI Audio - Monitor o TV"]
    end

    LAN_CLIENT -->|"UDP OSC Port 8000"| ETH_WIFI
    GPIO_DEVICE -->|"Gate 3.3V max"| GPIO17_NODE

    ETH_WIFI --> SYNTH_PROC
    GPIO17_NODE --> GPIO_DRIVER
    GPIO_DRIVER --> GPIO_DAEMON
    GPIO_DAEMON -->|"OSC /clock/sync - loopback UDP"| NET_STACK
    NET_STACK --> SYNTH_PROC

    SYNTH_PROC -->|"ALSA openStream 48kHz 256frames"| ALSA_DRIVER
    ALSA_DRIVER --> BCM_PWM
    ALSA_DRIVER --> USB_BUS
    ALSA_DRIVER --> BCM_I2S
    BCM_PWM --> JACK_35
    USB_BUS --> USB_DAC
    HDMI_AUDIO --> BCM_PWM
```

### Modelo de procesos y hilos en Raspberry Pi 3

```
Sistema Linux (Raspbian / Raspberry Pi OS)
â”‚
â”œâ”€â”€ PID xxx: BazzSynthServer (proceso principal)
â”‚   â”‚
â”‚   â”œâ”€â”€ Hilo 1: main() â€” hilo principal
â”‚   â”‚     PolÃ­tica: SCHED_OTHER (normal)
â”‚   â”‚     FunciÃ³n: bucle de consola stdin, carga/guarda preset
â”‚   â”‚
â”‚   â”œâ”€â”€ Hilo 2: RtAudio ALSA callback (hilo de audio)
â”‚   â”‚     PolÃ­tica: SCHED_FIFO prioridad 80 (tiempo real)
â”‚   â”‚     PerÃ­odo:  cada 5.33 ms (256 frames @ 48kHz)
â”‚   â”‚     CPU:      preferentemente nÃºcleo 1 o 2
â”‚   â”‚     FunciÃ³n:  detectar voltaje GPIO, actualizar params,
â”‚   â”‚               ejecutar Faust DSP, enviar a DAC
â”‚   â”‚
â”‚   â”œâ”€â”€ Hilo 3: lo_server_thread (OSC listener)
â”‚   â”‚     PolÃ­tica: SCHED_OTHER
â”‚   â”‚     Puerto:   UDP 8000
â”‚   â”‚     FunciÃ³n:  recibir mensajes OSC, actualizar parametros
â”‚   â”‚
â”‚   â””â”€â”€ Hilo 4: uWebSockets + libuv (WebSocket server)
â”‚         PolÃ­tica: SCHED_OTHER
â”‚         Puerto:   TCP 9001
â”‚         FunciÃ³n:  interfaz web en navegador
â”‚
â””â”€â”€ PID yyy: pi_gpio_sync.py (proceso Python daemon)
      PolÃ­tica: SCHED_OTHER (interrupciones gpiozero son rÃ¡pidas)
      FunciÃ³n:  monitoriza GPIO 17, envÃ­a /clock/sync por UDP loopback
```

### Flags de compilaciÃ³n especÃ­ficos para Cortex-A53 (RPi 3)

```cmake
# CMakeLists.txt â€” Bloque Linux (Raspberry Pi 3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
    -O3                      # OptimizaciÃ³n mÃ¡xima
    -ffast-math              # Relaxed IEEE 754: permite reordenamiento de operaciones FP
    -mcpu=cortex-a53         # Genera cÃ³digo optimizado para Cortex-A53 (RPi 3)
    -mtune=cortex-a53        # Ajusta pipeline scheduling al A53 (in-order)
    -mfpu=neon-fp-armv8      # Habilita instrucciones NEON ARMv8 (128-bit SIMD)
    -ftree-vectorize         # Auto-vectorizaciÃ³n de bucles con NEON
    -funroll-loops           # Desenrollar bucles (reduce branch overhead en A53 in-order)
")
```

**Diferencias con RPi 4 (Cortex-A72):**

| CaracterÃ­stica | RPi 3 (Cortex-A53) | RPi 4 (Cortex-A72) |
|---|---|---|
| **Arquitectura** | In-order | Out-of-order |
| **Flag CPU** | `-mcpu=cortex-a53` | `-mcpu=cortex-a72` |
| **Clock** | 1.2 / 1.4 GHz | 1.5 / 1.8 GHz |
| **IPC** | ~2 instrucciones/ciclo | ~3-4 instrucciones/ciclo |
| **NEON unidad** | 1 pipeline SIMD | 2 pipelines SIMD |
| **RAM** | 1 GB LPDDR2 | 2-8 GB LPDDR4 |
| **DSP overhead** | ~50-65% CPU | ~20-30% CPU |
| **Buffers seguros** | 256+ frames | 128+ frames |

> **Para RPi 3**: Se recomienda bufferSize de **256 o 512 frames** (no bajar de 256, el Cortex-A53 in-order necesita el margen adicional para evitar xruns ALSA).

### InstalaciÃ³n de dependencias en Raspberry Pi 3

```bash
# 1. Actualizar el sistema operativo
sudo apt update && sudo apt full-upgrade -y

# 2. Instalar herramientas de compilaciÃ³n
sudo apt install -y build-essential cmake git

# 3. Instalar ALSA (driver de audio nativo)
sudo apt install -y libasound2-dev

# 4. Instalar liblo (opcional, acelera compilaciÃ³n)
sudo apt install -y liblo-dev

# 5. Instalar Python y gpiozero (para el puente GPIO)
sudo apt install -y python3-pip python3-gpiozero
pip3 install python-osc

# 6. Configurar audio ALSA (seleccionar dispositivo por defecto)
# Para jack 3.5mm:
echo "options snd_bcm2835 index=0" | sudo tee /etc/modprobe.d/alsa-base.conf

# Para USB DAC (reemplaza al bcm2835 como default):
echo "options snd-usb-audio index=0" | sudo tee /etc/modprobe.d/alsa-base.conf
echo "options snd-bcm2835 index=1"  | sudo tee -a /etc/modprobe.d/alsa-base.conf
```

### CompilaciÃ³n en Raspberry Pi 3

```bash
# Navegar al directorio del proyecto
cd /home/pi/sintetizador

# Limpiar builds anteriores (importante si venÃ­a de Windows)
rm -rf build

# Configurar con CMake (detecta Linux y aplica flags Cortex-A53 automÃ¡ticamente)
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Compilar usando los 4 nÃºcleos del Cortex-A53
cmake --build build --config Release -j4

# El ejecutable queda en:
ls -lh build/BazzSynthServer
# TamaÃ±o tÃ­pico: 8-15 MB (incluye DSP Faust inlining)
```

### EjecuciÃ³n en Raspberry Pi 3

```bash
# Con selecciÃ³n automÃ¡tica de dispositivo (usa default ALSA):
./build/BazzSynthServer

# Con dispositivo especÃ­fico (ej: USB DAC = ID 2):
./build/BazzSynthServer 2

# Consola interactiva disponible:
synth-server> list          # Listar dispositivos ALSA
synth-server> set 2         # Cambiar a USB DAC
synth-server> emu on        # Activar emulador de reloj (sin hardware externo)
synth-server> emu bpm 128   # Establecer tempo del emulador
synth-server> status        # Ver estado completo
synth-server> exit          # Guardar preset y salir
```

### Servicio systemd â€” Modo Headless (RPi 3 como instrumento)

```bash
# Crear archivo de servicio del sintetizador
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
# Pasar el ID del dispositivo de audio (1=jack 3.5mm, 2=USB DAC)
ExecStart=/home/pi/sintetizador/build/BazzSynthServer 1
Restart=on-failure
RestartSec=5
# Prioridad elevada para el proceso (el hilo de audio sube a SCHED_FIFO internamente)
Nice=-10
LimitRTPRIO=95

[Install]
WantedBy=multi-user.target
```

```bash
# Crear servicio de sincronizaciÃ³n GPIO
sudo nano /etc/systemd/system/synthesizer-gpio.service
```

```ini
[Unit]
Description=BAZZ GPIO Clock Bridge - pi_gpio_sync.py
After=synthesizer.service
Requires=synthesizer.service

[Service]
Type=simple
User=pi
Group=gpio
WorkingDirectory=/home/pi/sintetizador
ExecStart=/usr/bin/python3 /home/pi/sintetizador/scratch/pi_gpio_sync.py
Restart=on-failure
RestartSec=3

[Install]
WantedBy=multi-user.target
```

```bash
# Activar ambos servicios
sudo systemctl daemon-reload
sudo systemctl enable synthesizer.service synthesizer-gpio.service
sudo systemctl start synthesizer.service synthesizer-gpio.service

# Verificar estado
sudo systemctl status synthesizer.service
sudo systemctl status synthesizer-gpio.service

# Ver logs en tiempo real
journalctl -u synthesizer.service -f
```

### Secuencia de arranque del RPi 3 (headless)

```
Encendido de la Raspberry Pi 3
         â”‚
         â–¼  ~5 segundos
  Bootloader (GPU firmware)
         â”‚
         â–¼  ~10-15 segundos
  Kernel Linux carga (Raspberry Pi OS)
         â”‚
         â–¼  ~20 segundos
  systemd multi-user.target
         â”‚
         â”œâ”€â”€â–¶ synthesizer.service
         â”‚         â”‚
         â”‚         â”œâ”€â”€ Carga preset.json (valores de perillas)
         â”‚         â”œâ”€â”€ Enumera dispositivos ALSA (snd_bcm2835 / USB)
         â”‚         â”œâ”€â”€ Abre stream ALSA @ 48kHz / 256 frames
         â”‚         â”œâ”€â”€ Inicia servidor OSC en UDP :8000
         â”‚         â””â”€â”€ Inicia WebSocket en TCP :9001
         â”‚
         â””â”€â”€â–¶ synthesizer-gpio.service (espera a synthesizer.service)
                   â”‚
                   â”œâ”€â”€ Configura GPIO 17 como entrada con pull-down
                   â”œâ”€â”€ Registra callback on when_activated
                   â””â”€â”€ Escucha pulsos y envÃ­a /clock/sync por loopback

  LISTO en ~30 segundos desde el encendido
  â†’ DSP activo, OSC escuchando, GPIO monitoreando
```

### Dispositivos de audio ALSA disponibles en RPi 3

| ID ALSA | Nombre del dispositivo | Canales | ResoluciÃ³n | Latencia tÃ­pica | Recomendado |
|---|---|---|---|---|---|
| `[0]` | bcm2835 HDMI 1 | Out: 2 | 16-bit | ~10-15 ms | TV / Monitor HDMI |
| `[1]` | bcm2835 Headphones | Out: 2 | ~11-bit efectivos | ~8-12 ms | Pruebas rÃ¡pidas |
| `[2]` | USB Audio (si conectado) | In+Out: 2 | 16-24 bit | ~5-8 ms | **ProducciÃ³n** |

> **Nota sobre el jack 3.5mm del RPi 3**: La salida usa PWM del BCM2837 con un filtro RC pasivo. La resoluciÃ³n efectiva es de aproximadamente **11 bits** (vs los 16 bits nominales), con un SNR de ~70 dB y ruido de fondo audible. Para producciÃ³n musical seria, usar siempre un **USB DAC externo**.

### ConfiguraciÃ³n de red para control OSC remoto

```bash
# Ver IP del RPi 3
ip addr show eth0    # Para Ethernet
ip addr show wlan0   # Para WiFi

# Ejemplo de salida:
# inet 192.168.1.42/24  â† esta es la IP del sintetizador

# Desde TouchOSC (iPad/Android):
#   Host: 192.168.1.42
#   Puerto: 8000
#   Protocolo: UDP

# Desde Python en el mismo equipo o en red:
from pythonosc import udp_client
client = udp_client.SimpleUDPClient("192.168.1.42", 8000)
client.send_message("/kick/vol", 0.8)
client.send_message("/master/bpm", 140.0)

# Para acceder a la interfaz WebSocket:
# Abrir en navegador: http://192.168.1.42:9001
```

---

## 11. Vista desde Windows (WASAPI)

### Diagrama de capas en Windows

```mermaid
graph TD
    UDP_IN["UDP Puerto 8000 - TouchOSC o Python"]
    WS_IN["TCP Puerto 9001 - Navegador Web"]

    subgraph WIN_PROC["Proceso BazzSynthServer.exe"]
        MAIN_T["Hilo 1 - main - Consola stdin"]
        OSC_T["Hilo 2 - OscServer - lo_server_thread"]
        AUDIO_T["Hilo 3 - RtAudio - WASAPI callback - RT priority"]
        WS_T["Hilo 4 - uWebSockets - libuv"]
    end

    subgraph WIN_DLLS["DLLs requeridas junto al exe"]
        DLL_LO["liblo.dll - OSC"]
        DLL_RT["librtaudio.dll - WASAPI"]
        DLL_GCC["libgcc_s_seh-1.dll - Runtime GCC"]
        DLL_STD["libstdc++6.dll - Libreria estandar C++"]
        DLL_PT["libwinpthread-1.dll - Hilos POSIX"]
    end

    WASAPI["WASAPI - Windows Audio Session API"]
    REALTEK["Realtek HD Audio - Altavoces o Jack"]

    UDP_IN --> OSC_T
    WS_IN --> WS_T
    MAIN_T --> OSC_T
    MAIN_T --> AUDIO_T
    MAIN_T --> WS_T
    AUDIO_T --> WASAPI
    WASAPI --> REALTEK
    WIN_PROC --> WIN_DLLS
```

### Modelo de hilos en Windows

```
BazzSynthServer.exe
â”œâ”€â”€ Hilo Principal (GUI thread)
â”‚     Prioridad: THREAD_PRIORITY_NORMAL
â”‚     FunciÃ³n: bucle de comandos por consola, SIGINT handler
â”‚
â”œâ”€â”€ Hilo de Audio (RtAudio / WASAPI)
â”‚     Prioridad: THREAD_PRIORITY_TIME_CRITICAL
â”‚     PerÃ­odo:   cada 5.33 ms (256 frames @ 48kHz)
â”‚     FunciÃ³n:   detectar voltaje, ejecutar Faust, enviar a WASAPI
â”‚
â”œâ”€â”€ Hilo OSC (lo_server_thread)
â”‚     Prioridad: THREAD_PRIORITY_ABOVE_NORMAL
â”‚     Puerto:    UDP 8000
â”‚     FunciÃ³n:   recibir mensajes OSC, actualizar parametros atomicos
â”‚
â””â”€â”€ Hilo WebSocket (uWebSockets + libuv event loop)
      Prioridad: THREAD_PRIORITY_NORMAL
      Puerto:    TCP 9001
      FunciÃ³n:   interfaz web, servir HTML/JS, WebSocket bidireccional
```

---

## 12. SincronizaciÃ³n GPIO â€” Reloj de Hardware Externo

### Diagrama completo de la cadena de sincronizaciÃ³n

```mermaid
flowchart LR
    EURORACK["Eurorack - Gate 5-12V"]
    VOLCA["Korg Volca - Sync 3.3-5V"]

    VOLTAGE_DIV["Divisor de Tension - R1=10k serie - R2=4.7k a GND"]

    GPIO17_PIN["Pin 11 GPIO17 - 3.3V MAX"]
    GND_PIN["Pin 9 GND - Masa comun"]

    GPIOZERO_CB["gpiozero InputDevice - when_activated callback - flanco ascendente"]

    OSC_SEND["python-osc send - /clock/sync - UDP 127.0.0.1:8000"]

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

### ConexiÃ³n elÃ©ctrica fÃ­sica al Raspberry Pi 3

```
CASO 1: Korg Volca / Pocket Operator (Sync Out 3.3V-5V)
â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”
  [ KORG VOLCA ]              [ RASPBERRY PI 3 ]
  Sync Out (+) â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–¶ Pin 11 (GPIO 17)
  GND          â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–¶ Pin 9  (GND)

  TensiÃ³n de sync Volca: ~3.5V peak
  Dentro del rango seguro del GPIO: âœ“ (mÃ¡x 3.3V, tolera hasta ~3.6V)

CASO 2: Eurorack Modular (Gate/Trigger 5V-12V)
â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”
  [ EURORACK ]               [ DIVISOR ]              [ RPi 3 ]
  Gate (+) â”€â”€â”€ R1=10kÎ© â”€â”€â”€ Nodo â”€â”€â”€ R2=4.7kÎ© â”€â”€â”€ GND
                                â”‚
                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–¶ Pin 11 (GPIO 17)
  GND â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–¶ Pin 9  (GND)

  CÃ¡lculo de tensiÃ³n:
  V_gpio = V_gate Ã— R2/(R1+R2) = V_gate Ã— 4700/14700 = V_gate Ã— 0.3197

  Ejemplos:
    V_gate = 5V  â†’ V_gpio = 1.60V  âœ“ (seguro, sobre el umbral de 0.3Ã—3.3=1.0V)
    V_gate = 8V  â†’ V_gpio = 2.56V  âœ“ (dentro de los 3.3V)
    V_gate = 12V â†’ V_gpio = 3.84V  âš  (demasiado, usar R1=15kÎ©)

  Para seÃ±ales de 12V usar: R1=15kÎ©, R2=4.7kÎ©
    V_gpio = 12 Ã— 4700/19700 = 12 Ã— 0.238 = 2.86V  âœ“

CASO 3: SeÃ±al de audio analÃ³gica (0 a +3.3V)
â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”â”
  Si el dispositivo de audio tiene entrada (inputChannels > 0),
  RtAudio captura la seÃ±al en el audioCallback.
  El cÃ³digo detecta flancos en el inputBuffer:
    if (currentSample > 0.4f && lastSample <= 0.4f)
  No se necesita GPIO, el reloj llega como seÃ±al de audio.
```

### Script Python del puente GPIO (pi_gpio_sync.py)

```python
#!/usr/bin/env python3
"""
pi_gpio_sync.py â€” Puente GPIO â†’ OSC para Raspberry Pi 3
Monitoriza GPIO 17 y envÃ­a /clock/sync al BazzSynthServer
"""

from gpiozero import InputDevice
from pythonosc import udp_client
import time
import signal
import sys

# ConfiguraciÃ³n
GPIO_PIN    = 17              # GPIO 17 = Pin fÃ­sico 11
OSC_IP      = "127.0.0.1"    # Loopback local (mismo RPi)
OSC_PORT    = 8000            # Puerto del BazzSynthServer
DEBOUNCE_MS = 50              # Antirrebote: ignorar pulsos < 50ms

# Inicializar cliente OSC (UDP, sin conexiÃ³n)
client = udp_client.SimpleUDPClient(OSC_IP, OSC_PORT)

# Inicializar GPIO 17 como entrada con pull-down
gpio_clock = InputDevice(GPIO_PIN, pull_up=False)

last_trigger_time = 0.0

def on_clock_pulse():
    """Callback invocado en cada flanco de subida del GPIO 17."""
    global last_trigger_time
    now = time.monotonic() * 1000.0  # tiempo en ms
    
    # Antirrebote: ignorar pulsos demasiado cercanos
    if (now - last_trigger_time) < DEBOUNCE_MS:
        return
    
    last_trigger_time = now
    
    # Enviar mensaje OSC /clock/sync al sintetizador
    client.send_message("/clock/sync", [])
    print(f"[GPIO SYNC] Pulso en GPIO17 â†’ /clock/sync enviado @ {now:.1f} ms")

# Registrar el callback de interrupciÃ³n
gpio_clock.when_activated = on_clock_pulse

def signal_handler(sig, frame):
    print("\n[GPIO SYNC] Deteniendo puente GPIO...")
    gpio_clock.close()
    sys.exit(0)

signal.signal(signal.SIGINT,  signal_handler)
signal.signal(signal.SIGTERM, signal_handler)

print(f"[GPIO SYNC] Escuchando en GPIO {GPIO_PIN} (Pin fÃ­sico 11)")
print(f"[GPIO SYNC] Enviando OSC /clock/sync a {OSC_IP}:{OSC_PORT}")
print("[GPIO SYNC] Presiona Ctrl+C para detener...")

# Bloquear el proceso (las interrupciones llaman al callback)
signal.pause()
```

### Cadena de latencia completa de sincronizaciÃ³n

```
MEDICIÃ“N DE LATENCIA EN RASPBERRY PI 3:

  1. Flanco de subida en Gate externo
     â”‚  ~0.1 ms  (rise time del gate hardware)
     â–¼
  2. InterrupciÃ³n del kernel Linux (GPIO sysfs/gpiozero)
     â”‚  ~0.3-0.8 ms  (latencia de interrupciÃ³n del kernel)
     â–¼
  3. Callback Python: on_clock_pulse()
     â”‚  ~0.2 ms  (context switch + ejecuciÃ³n Python)
     â–¼
  4. ConstrucciÃ³n y envÃ­o del paquete OSC (UDP loopback)
     â”‚  ~0.1 ms  (stack de red, loopback)
     â–¼
  5. RecepciÃ³n en OscServer.genericHandler()
     â”‚  ~0.05 ms (parse OSC + atomic store)
     â–¼
  6. Espera al prÃ³ximo audioCallback() (RtAudio ALSA)
     â”‚  0 â€“ 5.33 ms  (jitter de buffer de 256 frames @ 48kHz)
     â–¼
  7. updateDSPValues() copia BPM al DSP
     â”‚  ~0.01 ms (loop sobre todos los parametros)
     â–¼
  8. Faust DSP ejecuta con el nuevo BPM
     â”‚  ~1.5 ms (computo de sÃ­ntesis de 6 voces)
     â–¼
  9. SeÃ±al de audio sale por el DAC

  â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
  â”‚ LATENCIA MÃNIMA:  ~1 ms   (cuando el callback estÃ¡ justo)â”‚
  â”‚ LATENCIA MÃXIMA:  ~7.5 ms (espera al prÃ³ximo callback)   â”‚
  â”‚ LATENCIA PROMEDIO: ~4 ms  (estadÃ­sticamente uniforme)    â”‚
  â”‚                                                           â”‚
  â”‚ A 140 BPM: 1 beat = 428 ms                              â”‚
  â”‚ Error mÃ¡ximo de sync: 7.5 ms / 428 ms = 1.75% del beat  â”‚
  â”‚ Imperceptible musicalmente (umbral humano ~20ms)         â”‚
  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
```

---

## 13. Sistema de Estado â€” Presets y AutomatizaciÃ³n

### Diagrama de flujo del PresetManager

```mermaid
flowchart TD
    ARRANQUE(["Arranque del BazzSynthServer"])
    ARRANQUE --> EXISTE{"Existe preset.json en disco?"}

    EXISTE -->|"Si"| LEER["Leer JSON con nlohmann::json - Parsear mapa clave-valor"]
    EXISTE -->|"No"| DEFAULTS["Usar valores init de Faust DSP"]

    LEER --> LOOP["Para cada entrada en el JSON"]
    LOOP --> FIND_PARAM{"synth->getParameter(path) existe?"}
    FIND_PARAM -->|"Si"| SET_ATOMIC["param->setValue(value) - atomic store release"]
    FIND_PARAM -->|"No"| SKIP["Ignorar - parametro obsoleto o renombrado"]
    SET_ATOMIC --> LOOP
    SKIP --> LOOP

    SIGINT(["SIGINT o SIGTERM recibido - Ctrl+C o systemctl stop"])
    SIGINT --> HANDLER["signalHandler - guardar antes de morir"]
    HANDLER --> SAVE_JSON["presetMgr->savePreset preset.json - Serializar todos los parametros actuales"]
    SAVE_JSON --> EXIT_SAFE["std::exit(signum) - salida limpia"]

    CMD_EXIT(["Comando exit o quit en consola"])
    CMD_EXIT --> SAVE_FINAL["presetMgr->savePreset preset.json"]
    SAVE_FINAL --> STOP_AUDIO["audioBackend.stop - cerrar stream ALSA"]
    STOP_AUDIO --> STOP_OSC["oscServer.stop - cerrar UDP socket"]
    STOP_OSC --> RETURN_0(["return 0"])
```

### Formato del archivo preset.json

El archivo es un mapa plano JSON donde cada clave es una **ruta OSC** y el valor es un `float`. Esto permite interoperabilidad directa: los mismos paths que usas en TouchOSC son los que se guardan en disco.

```json
{
  "/bass/accent":      0.5,
  "/bass/dec":         0.57,
  "/bass/detune":      0.04,
  "/bass/drive":       0.65,
  "/bass/groove":      6,
  "/bass/intervalo":   -12,
  "/bass/lfo":         0.45,
  "/bass/nota":        43,
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
  "/snare/vol":        0.0,
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
    Note over FDSP,UI: Faust registra todos sus sliders via ui->addHorizontalSlider para cada parametro
    UI->>CORE: addParameter para cada slider con ruta OSC
    MAIN->>CORE: addParameter emulator-active
    MAIN->>CORE: addParameter emulator-bpm
    MAIN->>PRESET: PresetManager con puntero a synthCore
    MAIN->>PRESET: loadPreset preset.json
    PRESET->>CORE: param->setValue para cada entrada del JSON
    MAIN->>RTAUDIO: RtAudioBackend con synthDsp y ui
    RTAUDIO->>RTAUDIO: printAvailableDevices listar ALSA
    RTAUDIO->>RTAUDIO: openDevice con deviceId
    Note over RTAUDIO: Init Faust DSP a 48kHz, abrir stream ALSA con 256 frames
    MAIN->>OSC: OscServer con synth preset recorder audioBackend
    MAIN->>OSC: oscServer.start en puerto 8000
    OSC->>OSC: lo_server_thread_new puerto 8000
    OSC->>OSC: Iniciar HttpServer WebSockets en 9001
    MAIN->>RTAUDIO: audioBackend.start
    Note over RTAUDIO: Inicia callbacks ALSA cada 5.33ms en hilo RT SCHED_FIFO
    loop Bucle de consola infinito
        MAIN->>MAIN: getline cin esperando comandos
        MAIN->>CORE: Procesar list, set, emu on-off, status
    end
    MAIN->>PRESET: savePreset preset.json al salir
    MAIN->>RTAUDIO: stop cerrar stream ALSA
    MAIN->>OSC: stop cerrar UDP socket
```

---

## 15. Tablas de ParÃ¡metros

### Preset de fÃ¡brica completo

| Instrumento | Ruta OSC | Valor Default | Rango |
|---|---|---|---|
| **Master** | `/master/bpm` | 140.0 | 20â€“999 |
| **Kick** | `/kick/vol` | 0.114 | 0â€“1 |
| **Kick** | `/kick/tune` | 0.463 | 0â€“1 |
| **Kick** | `/kick/dec` | 0.07 | 0.01â€“1 |
| **Kick** | `/kick/sweep` | 150 | 0â€“500 |
| **Kick** | `/kick/comp_thresh` | 0.4 | 0â€“1 |
| **Kick** | `/kick/comp_ratio` | 1.988 | 1â€“10 |
| **Kick** | `/kick/groove` | 2 | 0â€“6 |
| **Snare** | `/snare/vol` | 0.0 | 0â€“1 |
| **Snare** | `/snare/dec_cuerpo` | 0.07 | 0.01â€“1 |
| **Snare** | `/snare/dec_resorte` | 0.16 | 0.01â€“1 |
| **Snare** | `/snare/drive` | 3.51 | 0â€“10 |
| **Snare** | `/snare/freq` | 1551 Hz | 100â€“5000 |
| **Hat** | `/hat/vol` | 0.0 | 0â€“1 |
| **Hat** | `/hat/dec` | 0.15 | 0.001â€“2 |
| **Hat** | `/hat/cutoff` | 4754.86 Hz | 500â€“20000 |
| **Bass** | `/bass/vol` | 0.0 | 0â€“1 |
| **Bass** | `/bass/dec` | 0.57 | 0.01â€“2 |
| **Bass** | `/bass/detune` | 0.04 | 0â€“0.5 |
| **Bass** | `/bass/drive` | 0.65 | 0â€“2 |
| **Syn1** | `/syn1/vol` | 0.03 | 0â€“1 |
| **Syn1** | `/syn1/osc1` | 11.01 | 1â€“100 |
| **Syn1** | `/syn1/osc2` | 18.63 | 1â€“100 |
| **Syn2** | `/syn2/vol` | 0.22 | 0â€“1 |
| **Syn2** | `/syn2/comp_th` | -20 dBFS | -60â€“0 |
| **Syn2** | `/syn2/disp` | 0.654 | 0â€“1 |
| **Emulador** | `/emulator/active` | 0 (off) | 0â€“1 |
| **Emulador** | `/emulator/bpm` | 137.0 | 60â€“240 |

---

## 16. Dependencias y CompilaciÃ³n

### Grafo de dependencias

```mermaid
graph TD
    EXE["BazzSynthServer - ejecutable final"]

    EXE --> RTAUDIO_DEP["RtAudio - github thestk/rtaudio - FetchContent - ALSA en Linux"]
    EXE --> LIBLO_DEP["liblo - github radarsat1/liblo - FetchContent - Protocolo OSC/UDP"]
    EXE --> NLOHMANN_DEP["nlohmann-json v3.11.3 - FetchContent - Presets JSON"]
    EXE --> UWS_DEP["uWebSockets v20.44.0 - FetchContent - WebSocket server"]
    EXE --> LIBUV_DEP["libuv v1.44.2 - FetchContent - Event loop async"]
    EXE --> FAUST_DEP["untitled.cpp - Codigo Faust transpilado a C++ - Motor DSP"]

    RTAUDIO_DEP -->|"Linux RPi3"| ALSA_SYS["libasound2-dev - apt package"]
    RTAUDIO_DEP -->|"Windows"| WASAPI_SYS["WASAPI built-in en Windows SDK"]
    LIBLO_DEP --> LO_OPT["liblo-dev opcional apt - mas rapido si esta instalado"]
    UWS_DEP --> LIBUV_DEP
```

### Stack tecnolÃ³gico

| Capa | TecnologÃ­a | VersiÃ³n | PropÃ³sito |
|---|---|---|---|
| Lenguaje | C++17 | â€” | Todo el servidor |
| DSP Source | Faust | 2.x | DiseÃ±o algorÃ­tmico del sintetizador |
| DSP Runtime | C++ generado por Faust | â€” | Motor de sÃ­ntesis (untitled.cpp) |
| Audio I/O | RtAudio | master | AbstracciÃ³n ALSA (Linux) / WASAPI (Win) |
| OSC | liblo | master | Open Sound Control sobre UDP |
| JSON | nlohmann/json | 3.11.3 | Presets y configuraciÃ³n |
| WebSocket | uWebSockets | 20.44.0 | Interfaz web en tiempo real |
| Async I/O | libuv | 1.44.2 | Event loop para uWebSockets |
| Build | CMake | â‰¥3.14 | Sistema de compilaciÃ³n cross-platform |
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
# En terminal MSYS2 UCRT64:
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja

# En PowerShell:
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
cmake -B build -S . -G "Ninja"
cmake --build build --config Release
.\build\BazzSynthServer.exe
```

---

> **Ver tambiÃ©n:**
> - [GUIA_RASPBERRY.md](./GUIA_RASPBERRY.md) â€” Guia de instalacion y GPIO sync en Raspberry Pi
> - [GUIA_WINDOWS.md](./GUIA_WINDOWS.md) â€” Instalacion en Windows con MSYS2 y WASAPI
> - [preset.json](./preset.json) â€” Configuracion de parametros persistida en disco
> - [untitled.dsp](./untitled.dsp) â€” Codigo fuente Faust del motor de sintesis
> - [core/MasterClock.h](./core/MasterClock.h) â€” Implementacion del reloj maestro lock-free
> - [audio/RtAudioBackend.cpp](./audio/RtAudioBackend.cpp) â€” Callback de audio y deteccion de voltaje
> - [osc/OscServer.cpp](./osc/OscServer.cpp) â€” Servidor OSC y routing de mensajes


