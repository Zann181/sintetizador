# Guía de Uso: Link Sync Bridge (Python)

Esta aplicación conecta Ableton Link con tu ESP32 mediante el puerto Serie (USB). 
Para asegurarnos de que todo funcione perfectamente y no haya conflictos con otras librerías de tu computadora, utilizamos un **entorno virtual** (virtual environment).

## Pasos para ejecutar la aplicación

### Opción 1: Ejecutar usando un archivo Batch (Recomendado)
Para hacerlo más fácil, puedes crear un archivo `.bat` (por ejemplo, `run.bat`) en la carpeta `pc_bridge` con el siguiente contenido:

```bat
@echo off
cd /d "%~dp0"
call venv\Scripts\activate
python gui.py
```
Solo tendrás que darle doble clic a ese archivo `.bat` y abrirá la aplicación automáticamente.

---

### Opción 2: Ejecutar manualmente desde la consola (PowerShell)

Si prefieres abrirlo desde la terminal de Windows o PowerShell, sigue estos pasos:

1. Abre una terminal (PowerShell o CMD) y navega hasta la carpeta del proyecto:
   ```ps1
   cd "c:\Users\Motaz\Music\Nueva carpeta\sintetizador\modulo_midi_sync\pc_bridge"
   ```

2. **Activa el entorno virtual**:
   Esto le dirá a tu consola que utilice las librerías correctas (como `pyserial`).
   ```ps1
   .\venv\Scripts\activate
   ```
   *(Sabrás que funcionó porque aparecerá un `(venv)` de color verde o blanco a la izquierda del texto en tu consola).*

3. **Inicia la aplicación**:
   ```ps1
   python gui.py
   ```

## Uso de la aplicación

- Al abrir, la aplicación **escaneará automáticamente** los puertos USB e intentará detectar la ESP32.
- Si por alguna razón la conectaste después de abrir la aplicación, dale al botón **BUSCAR** para refrescar la lista.
- Una vez seleccionado el puerto COM en la casilla, presiona **CONECTAR**.
- Podrás ver los parpadeos en los LEDs de la interfaz (LINK RX cuando reciba señal de Ableton Link, y ESP32 TX cuando la transmita exitosamente hacia tu sintetizador a través del cable USB).
