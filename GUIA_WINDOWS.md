# Guía de Instalación y Ejecución en Windows 🪟

Esta guía detalla los pasos para compilar, configurar y ejecutar el servidor del sintetizador **FaustSynthServer** en Windows utilizando el entorno de compilación **MSYS2 (UCRT64)** y **Ninja**.

---

## 1. Prerrequisitos del Sistema

Para compilar el proyecto en Windows de la misma forma en que está configurado, necesitaremos instalar el entorno de desarrollo de **MSYS2** que provee el compilador GCC y las herramientas necesarias.

1. **Descargar e instalar MSYS2:**
   * Descarga el instalador desde [msys2.org](https://www.msys2.org/).
   * Realiza la instalación por defecto (normalmente se instala en `C:\msys64`).

2. **Instalar el compilador y herramientas:**
   * Abre la terminal **"MSYS2 UCRT64"** (búscala en el menú inicio de Windows).
   * Ejecuta el siguiente comando para instalar GCC (C++), CMake, Ninja y Pkg-config:
     ```bash
     pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-pkg-config
     ```

---

## 2. Compilación del Proyecto

Puedes compilar el proyecto directamente desde **PowerShell** en Windows añadiendo la ruta del compilador de MSYS2 temporalmente a tu PATH.

1. Abre una terminal de **PowerShell**.
2. Navega hasta la carpeta del sintetizador:
   ```powershell
   cd "C:\Users\Motaz\Music\Nueva carpeta\sintetizador"
   ```
3. Configura las variables de entorno y ejecuta la configuración de CMake con el generador **Ninja**:
   ```powershell
   # Añadir MSYS2 temporalmente al PATH de esta sesión de terminal
   $env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH

   # Configurar la compilación
   cmake -B build -S . -G "Ninja"
   ```
   *Nota: CMake descargará automáticamente **RtAudio** y **liblo** (para soporte de OSC) desde sus repositorios y los compilará nativamente para Windows con WASAPI.*

4. Compila el ejecutable:
   ```powershell
   cmake --build build --config Release
   ```

---

## 3. Dependencias de Ejecución (Archivos DLL)

Dado que el programa se compila con GCC bajo MSYS2, el ejecutable requiere ciertas librerías dinámicas (`.dll`) para poder arrancar. 

Para tu comodidad, **ya he copiado estas DLLs al directorio `build`**, por lo que el programa funcionará de inmediato. Si en el futuro necesitas mover el ejecutable a otro equipo o carpeta, asegúrate de llevar contigo las siguientes DLLs al mismo nivel que `FaustSynthServer.exe`:

* **Desde MSYS2** (ubicadas en `C:\msys64\ucrt64\bin`):
  * `libgcc_s_seh-1.dll` (soporte de excepciones y runtime de GCC)
  * `libstdc++-6.dll` (librería estándar de C++)
  * `libwinpthread-1.dll` (soporte de hilos POSIX en Windows)
* **Desde la Compilación** (generadas en los subdirectorios de `build`):
  * `liblo.dll` (servidor OSC, copiado de `build/_deps/liblo-build/`)
  * `librtaudio.dll` (motor de audio WASAPI, copiado de `build/_deps/rtaudio-build/`)

---

## 4. Ejecución del Sintetizador

Para iniciar el servidor, ejecuta lo siguiente en **PowerShell**:

```powershell
.\build\FaustSynthServer.exe
```

El servidor detectará automáticamente tus tarjetas de sonido bajo la API de ultra-baja latencia **Windows WASAPI**. Mostrará una salida en consola similar a esta:

```text
=== TR-808 Algorithmic Techno Station Server ===
--- Dispositivos de Audio Disponibles ---
[129] Altavoces (2- Realtek(R) Audio) (In: 0, Out: 2)
[130] Varios micrófonos (2- Realtek(R) Audio) (In: 2, Out: 0)
-----------------------------------------

Selecciona el ID del dispositivo de audio (ej. V8), o presiona Enter para usar [0]:
```

1. Escribe el ID de tu salida de audio deseada (por ejemplo, `129` para tus altavoces) y presiona **Enter** (o simplemente presiona **Enter** directamente para usar el dispositivo de reproducción por defecto de Windows).
2. El servidor de audio se iniciará y el puerto OSC **8000** quedará abierto escuchando comandos.
3. Para apagar el servidor de forma segura, presiona **Enter** en la terminal.

---

## 5. Control Remoto mediante OSC

El sintetizador queda escuchando comandos OSC en el puerto **8000**. Puedes enviar comandos desde tu propia computadora (a la IP `127.0.0.1`) o desde dispositivos móviles conectados a la misma red local (usando la dirección IP local de tu PC).

Puedes enviarle mensajes con cualquier cliente OSC (como **TouchOSC**, scripts de Python, etc.) para alterar los sonidos en tiempo real, cambiar el Groove o variar el BPM.
