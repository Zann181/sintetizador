# Guía de Instalación y Ejecución en Raspberry Pi 🍓

Esta guía detalla los pasos para compilar, ejecutar y configurar el servidor del sintetizador **FaustSynthServer** en una Raspberry Pi (optimizado para **Raspberry Pi 4 / 400 / 5** con arquitectura de 64 bits).

---

## 1. Prerrequisitos del Sistema

Antes de comenzar, asegúrate de tener tu sistema actualizado e instalar las herramientas de compilación y las librerías de audio y OSC nativas de Linux.

Abre una terminal en tu Raspberry Pi y ejecuta:

```bash
# Actualizar el sistema
sudo apt update && sudo apt upgrade -y

# Instalar herramientas de compilación esenciales y CMake
sudo apt install -y build-essential cmake git

# Instalar librerías de desarrollo de ALSA (Audio nativo de Linux)
sudo apt install -y libasound2-dev

# Instalar la librería OSC liblo (opcional, pero agiliza la compilación)
sudo apt install -y liblo-dev
```

---

## 2. Compilación del Proyecto

Una vez que tengas todas las dependencias instaladas, puedes compilar el servidor directamente en la Raspberry Pi.

1. **Copiar los archivos del proyecto** a la Raspberry Pi (por ejemplo, en la carpeta `/home/pi/sintetizador`).
2. **Entrar al directorio** del proyecto:
   ```bash
   cd /home/pi/sintetizador
   ```
3. **Limpiar cachés antiguas** (si copiaste carpetas de Windows):
   ```bash
   rm -rf build
   ```
4. **Configurar el proyecto con CMake:**
   ```bash
   cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
   ```
   *Nota: CMake detectará automáticamente que estás en Linux y aplicará las banderas de optimización para Raspberry Pi (`-O3 -ffast-math -mcpu=cortex-a72...`) y activará el backend de audio de baja latencia **ALSA** (`__LINUX_ALSA__`).*

5. **Compilar el ejecutable:**
   ```bash
   cmake --build build --config Release -j$(nproc)
   ```
   *El parámetro `-j$(nproc)` utiliza todos los núcleos del procesador de la Raspberry Pi para compilar a máxima velocidad.*

---

## 3. Ejecución del Sintetizador

Una vez finalizada la compilación, el ejecutable estará disponible en la ruta `build/FaustSynthServer`.

### Ejecución manual:
```bash
./build/FaustSynthServer
```

Al iniciar, el programa listará las tarjetas de audio ALSA disponibles en tu Raspberry Pi. Por ejemplo:
```text
=== TR-808 Algorithmic Techno Station Server ===
--- Dispositivos de Audio Disponibles ---
[0] bcm2835 HDMI 1 (In: 0, Out: 2)
[1] Headphones (3.5mm jack) (In: 0, Out: 2)
[2] USB Audio Device (In: 2, Out: 2)
-----------------------------------------

Selecciona el ID del dispositivo de audio (ej. V8), o presiona Enter para usar [0]:
```

Escribe el ID correspondiente (por ejemplo, `1` para la salida de auriculares de 3.5mm o `2` si conectaste una tarjeta de sonido USB) y presiona **Enter**.

El flujo de audio se abrirá y el servidor OSC se iniciará de inmediato en el puerto **8000**.

---

## 4. Control Remoto mediante OSC

El sintetizador está diseñado para controlarse de forma remota a través de mensajes OSC utilizando la IP de tu Raspberry Pi en la red local y el puerto **8000**.

### Rutas OSC disponibles para control de volumen y parámetros:
* **Globales:**
  * `/master/bpm` (Tempo global, ej: `120.0`)
  * `/master/accent` (Acentuación, `0.0` a `1.0`)
  * `/master/nota` (Nota raíz MIDI, ej: `36` para Do)
  * `/master/groove` (Selección de patrón algorítmico, `0` a `6`)
* **Por Instrumento:**
  * **Bombo (Kick):** `/kick/vol`, `/kick/dec`, `/kick/tune`, `/kick/sweep`
  * **Caja (Snare):** `/snare/vol`, `/snare/dec_cuerpo`, `/snare/dec_resorte`
  * **Platillo (Hat):** `/hat/vol`, `/hat/dec`, `/hat/tune`
  * **Bajo Waveguide:** `/bass/vol`, `/bass/dec`, `/bass/detune`, `/bass/intervalo`
  * **Sintetizador FDN:** `/syn2/vol`, `/syn2/dec`, `/syn2/comp_th`

Puedes enviar estos comandos usando aplicaciones móviles de control OSC como **TouchOSC**, o scripts en Python (`python-osc`), **Node-RED**, **PureData** o **Max/MSP**.

---

## 5. Ejecución Automática al Iniciar (Headless Synth Mode) 🚀

Si deseas que el sintetizador se ejecute automáticamente cada vez que enciendas la Raspberry Pi (sin necesidad de tener pantalla, teclado ni sesión SSH abierta), puedes configurarlo como un servicio de sistema (`systemd`).

1. **Crear el archivo de servicio:**
   ```bash
   sudo nano /etc/systemd/system/synthesizer.service
   ```
2. **Pegar la siguiente configuración** (ajusta las rutas si guardaste el proyecto en otra carpeta):
   ```ini
   [Unit]
   Description=TR-808 Algorithmic Synth Server
   After=network.target sound.target

   [Service]
   Type=simple
   User=pi
   WorkingDirectory=/home/pi/sintetizador
   # Pasamos el ID del dispositivo de audio como argumento al ejecutable (ej: 1 para el jack de 3.5mm)
   ExecStart=/home/pi/sintetizador/build/FaustSynthServer 1
   Restart=on-failure
   RestartSec=5

   [Install]
   WantedBy=multi-user.target
   ```
3. **Guardar y salir** (`Ctrl+O`, `Enter`, `Ctrl+X`).
4. **Habilitar e iniciar el servicio:**
   ```bash
   # Recargar el demonio de systemd
   sudo systemctl daemon-reload

   # Habilitar para que inicie en el arranque
   sudo systemctl enable synthesizer.service

   # Arrancar el servicio ahora mismo
   sudo systemctl start synthesizer.service
   ```
5. **Verificar el estado del servicio:**
   ```bash
   sudo systemctl status synthesizer.service
   ```

¡Listo! Tu Raspberry Pi ahora funciona como un **sintetizador de hardware dedicado**. Tan pronto como se encienda, cargará el motor DSP y estará lista en el puerto OSC 8000 para recibir tus comandos.

---

## 6. Sincronización por Hardware Externo (BPM GPIO Sync) 🍓🔌

Si tienes un sintetizador modular (Eurorack), un Korg Volca, Pocket Operator o cualquier secuenciador de hardware que emita pulsos de sincronización (Sync Gate), puedes conectar físicamente esa señal a tu **Raspberry Pi 3** para sincronizar el tempo (BPM) del sintetizador de forma fluida e instantánea.

### 🔌 A. Conexión Eléctrica (Hardware)

El puente de sincronización GPIO utiliza el **GPIO 17** (Pin Físico 11) como entrada de reloj externo y el **Pin Físico 9** (GND) como masa de referencia:

```text
  [ Secuenciador Externo ]               [ Raspberry Pi 3 (GPIO) ]
  (Salida Sync Out / Gate)               (Pines Físicos)
       ┌───────────┐                         ┌───────────────────┐
       │   Clock   │ ──────────────────────> │ Pin 11 (GPIO 17)  │
       │           │                         ├───────────────────┤
       │    GND    │ ──────────────────────> │ Pin 9 (GND)       │
       └───────────┘                         └───────────────────┘
```

> [!WARNING]
> **PROTECCIÓN DE VOLTAJE CRÍTICA**: Los pines GPIO de la Raspberry Pi funcionan a **3.3V de máximo**.
> * Si usas un Korg Volca o Pocket Operator (señal de 3.3V a 5V sutil), la Raspberry Pi lo tolera, pero es recomendable un divisor de tensión simple.
> * Si usas un sintetizador Eurorack modular (que emite gates de **5V, 8V o 12V**), **¡NO lo conectes directamente o quemarás la Raspberry Pi!** Debes usar un atenuador pasivo, un circuito integrado de nivel (Level Shifter) o un simple divisor de tensión con dos resistencias para bajar la señal a 3.0V - 3.3V:
>   - Conecta una resistencia de **10kΩ** en serie desde el clock externo al pin 11.
>   - Conecta una resistencia de **4.7kΩ** desde el pin 11 a GND.

---

### 💻 B. Ejecución del Puente en Raspberry Pi

Para actuar como puente ultra-rápido de baja latencia entre el pin físico de la Raspberry Pi y el motor DSP de Faust, implementamos un script daemon modular en `/scratch/pi_gpio_sync.py`.

Este script utiliza interrupts por flanco de subida en C (`gpiozero`) y envía paquetes OSC directos (`/clock/sync`) vía UDP raw para latencia cero y cero consumo de CPU.

#### 1. Probar el script manualmente:
Ejecuta el script en la Raspberry Pi para verificar que detecta tus pulsos:
```bash
python3 scratch/pi_gpio_sync.py
```
*Cuando envíes pulsos de sincronización desde tu hardware, la terminal imprimirá instantáneamente:*
`[*] Pulso de reloj recibido en GPIO 17 -> Sincronizado OSC a las HH:MM:SS`

---

### 🚀 C. Automatización Completa al Arrancar (Headless Dual-Service)

Puedes configurar el puente GPIO para que corra como un servicio del sistema junto con el sintetizador. Así, al encender la Raspberry Pi, tendrás audio y sincronización por hardware listos al instante:

1. **Crear el archivo de servicio de sincronización:**
   ```bash
   sudo nano /etc/systemd/system/synthesizer-sync.service
   ```
2. **Pegar la siguiente configuración:**
   ```ini
   [Unit]
   Description=TR-808 GPIO Sync Bridge
   After=network.target sound.target synthesizer.service
   Requires=synthesizer.service

   [Service]
   Type=simple
   User=pi
   WorkingDirectory=/home/pi/sintetizador
   ExecStart=/usr/bin/python3 /home/pi/sintetizador/scratch/pi_gpio_sync.py
   Restart=on-failure
   RestartSec=3

   [Install]
   WantedBy=multi-user.target
   ```
3. **Guardar y habilitar el servicio:**
   ```bash
   sudo systemctl daemon-reload
   sudo systemctl enable synthesizer-sync.service
   sudo systemctl start synthesizer-sync.service
   ```
4. **Verificar el estado de ambos servicios en paralelo:**
   ```bash
   sudo systemctl status synthesizer.service synthesizer-sync.service
   ```

¡Felicidades! Ahora tienes una **estación de ritmos algorítmica analógica-digital híbrida**. Puedes controlar la síntesis avanzada desde tu iPad o computadora usando el selector deslizable y el mezclador horizontal, mientras el tempo maestro sigue con precisión de muestra los pulsos de sincronización analógicos de tu hardware externo.
