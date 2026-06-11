import os
import sys
import glob
import wave
import struct
import math

def analyze_audio(file_path):
    print(f"\n========================================")
    print(f"Analizando archivo: {os.path.basename(file_path)}")
    print(f"========================================")
    
    try:
        with wave.open(file_path, 'rb') as wf:
            channels = wf.getnchannels()
            sampwidth = wf.getsampwidth()
            framerate = wf.getframerate()
            nframes = wf.getnframes()
            
            # Read audio data
            data = wf.readframes(nframes)
    except Exception as e:
        print(f"No se pudo leer {file_path}: {e}")
        return

    # Convert binary to list of floats
    samples = []
    fmt = "<" + ("h" if sampwidth == 2 else "i") * (len(data) // sampwidth)
    try:
        unpacked = struct.unpack(fmt, data)
    except:
        print("El formato de audio no está soportado (solo 16 o 32 bit PCM).")
        return

    # Mix down to mono if stereo
    if channels == 2:
        samples = [(unpacked[i] + unpacked[i+1]) / 2 for i in range(0, len(unpacked), 2)]
    else:
        samples = list(unpacked)
        
    # Normalize
    max_val = max(max(samples), abs(min(samples)))
    if max_val == 0:
        print("Audio vacío.")
        return
    samples = [s / max_val for s in samples]

    # Simple onset detection (energy envelope)
    window_size = int(framerate * 0.01) # 10ms
    energy = []
    for i in range(0, len(samples), window_size):
        chunk = samples[i:i+window_size]
        e = sum(x*x for x in chunk) / len(chunk)
        energy.append(e)

    # Find peaks (beats)
    threshold = 0.1
    peaks = []
    min_distance = int(framerate * 0.1) // window_size # At least 100ms between normal beats
    
    for i in range(1, len(energy) - 1):
        if energy[i] > threshold and energy[i] > energy[i-1] and energy[i] > energy[i+1]:
            # Peak detected
            if not peaks or (i - peaks[-1]) >= 2: # Very basic debounce of 20ms
                peaks.append(i)

    # Convert peak indices back to seconds
    times = [p * window_size / framerate for p in peaks]
    
    print(f"Se detectaron {len(times)} golpes (beats).")
    
    if len(times) < 2:
        print("No hay suficientes golpes para analizar el ritmo.")
        return

    # Calculate intervals
    intervals = [times[i] - times[i-1] for i in range(1, len(times))]
    avg_interval = sum(intervals) / len(intervals)
    bpm = 60.0 / avg_interval
    
    # Calculate Jitter (Standard Deviation)
    variance = sum((i - avg_interval) ** 2 for i in intervals) / len(intervals)
    jitter = math.sqrt(variance)
    
    print(f"BPM Promedio: {bpm:.2f}")
    print(f"Jitter (Desviación del ritmo): {jitter:.4f} segundos")
    
    # Detect double hits
    double_hits = [i for i in intervals if i < 0.15] # Less than 150ms
    if double_hits:
        print(f"ADVERTENCIA: Se detectaron {len(double_hits)} golpes dobles o tartamudeos (intervalo < 150ms).")
        print("   Esto indica problemas graves de sincronizacion o envios dobles de comandos.")
    else:
        print("OK: No se detectaron golpes dobles. La cadencia es consistente.")
        
    if jitter > 0.02:
        print("ADVERTENCIA: El Jitter es alto (> 20ms). La sincronizacion es inestable (fluctua).")
    else:
        print("OK: El Jitter es excelente (< 20ms). La sincronizacion es muy solida.")

def main():
    folder = sys.argv[1] if len(sys.argv) > 1 else "."
    files = glob.glob(os.path.join(folder, "*.wav"))
    if not files:
        print("No se encontraron archivos .wav en la carpeta especificada.")
    for f in files:
        analyze_audio(f)

if __name__ == "__main__":
    main()
