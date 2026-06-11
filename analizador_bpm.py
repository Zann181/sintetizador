import numpy as np
from scipy.io import wavfile
from scipy.signal import find_peaks

def analyze_audio(file_path):
    print(f"Analizando: {file_path}")
    try:
        sample_rate, data = wavfile.read(file_path)
    except Exception as e:
        print(f"Error al leer el archivo: {e}")
        return

    if len(data.shape) > 1:
        data = data.mean(axis=1)

    data = data / np.max(np.abs(data))
    window_size = int(sample_rate * 0.01)
    envelope = np.convolve(np.abs(data), np.ones(window_size)/window_size, mode='same')

    # Detectar picos a la mínima distancia razonable (ej. 200 BPM = 0.3s)
    min_distance_samples = int(sample_rate * 0.3)
    peaks, _ = find_peaks(envelope, height=0.2, distance=min_distance_samples)

    if len(peaks) < 2:
        print("No se detectaron suficientes golpes para analizar.")
        return

    peak_times = peaks / sample_rate
    intervals = np.diff(peak_times)

    print(f"\nTotal de golpes detectados: {len(peaks)}")
    
    # El BPM detectado real será el basado en la mediana de los intervalos
    median_interval = np.median(intervals)
    detected_bpm = 60.0 / median_interval
    
    print(f"BPM Base Real Detectado (Mediana): {detected_bpm:.2f} BPM")
    
    # Calcular todos los BPMs
    bpms = 60.0 / intervals
    mean_bpm = np.mean(bpms)
    std_bpm = np.std(bpms)
    
    print(f"BPM Promedio: {mean_bpm:.2f} BPM")
    print(f"Desviación Estándar (Jitter): {std_bpm:.4f} BPM")
    print(f"Fluctuación: Min {np.min(bpms):.2f} | Max {np.max(bpms):.2f}")
    
    # Evaluar desfases reales contra la mediana
    threshold = median_interval * 0.05 # 5% de tolerancia (mucho más estricto)
    outliers = []
    for i, interval in enumerate(intervals):
        diff = abs(interval - median_interval)
        if diff > threshold:
            outliers.append((i+1, peak_times[i], peak_times[i+1], interval, 60.0/interval))
            
    if outliers:
        print(f"\nSe detectaron {len(outliers)} desfases verdaderos (>5% de fluctuación):")
        for out in outliers[:10]:
            print(f" - Entre golpe {out[0]} ({out[1]:.2f}s) y {out[0]+1} ({out[2]:.2f}s): "
                  f"intervalo de {out[3]:.3f}s -> equivale a {out[4]:.1f} BPM")
        if len(outliers) > 10:
            print(f"   ... y {len(outliers) - 10} más.")
    else:
        print("\n¡PERFECTO! El audio es 100% fluido. Ningún golpe se salió de tiempo de forma perceptible.")

if __name__ == '__main__':
    analyze_audio('prueba de sincronizacion/prueba2.wav')
