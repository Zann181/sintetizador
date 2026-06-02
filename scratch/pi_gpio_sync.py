#!/usr/bin/env python3
import time
import socket
from gpiozero import Button

# Configuración del Pin GPIO y Servidor OSC
GPIO_PIN = 17       # Pin físico 11 (GPIO 17) de la Raspberry Pi 3
OSC_IP = "127.0.0.1" # El servidor Faust corre en localhost
OSC_PORT = 8000

print("==================================================")
print("=== TR-808 Raspberry Pi 3 GPIO Sync Bridge ===")
print("==================================================")
print(f"Escuchando pulsos en GPIO {GPIO_PIN} (Pull-down interno activo)...")
print(f"Enviando senal de reloj OSC a {OSC_IP}:{OSC_PORT}")
print("==================================================")

# Crear socket UDP para comunicación OSC
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Crear el paquete OSC binario crudo para "/clock/sync" con 0 argumentos
# Address (11 bytes + 1 null = 12 bytes): "/clock/sync\x00"
# TypeTag (1 byte ',' + 3 nulls = 4 bytes): ",\x00\x00\x00"
OSC_PACKET = b"/clock/sync\x00,\x00\x00\x00"

# Inicializar pin usando gpiozero. Button activa pull-down por defecto (pull_up=False).
# Cuando reciba una señal alta (3.3V), se activará.
clk_pin = Button(GPIO_PIN, pull_up=False)

last_pulse_time = 0

def on_pulse():
    global last_pulse_time
    now = time.time()
    # Antirrebote simple de 50ms para evitar falsos gatillos de ruido eléctrico
    if now - last_pulse_time < 0.05:
        return
    last_pulse_time = now
    
    try:
        sock.sendto(OSC_PACKET, (OSC_IP, OSC_PORT))
        print(f"[*] Pulso de reloj recibido en GPIO {GPIO_PIN} -> Sincronizado OSC a las {time.strftime('%H:%M:%S')}")
    except Exception as e:
        print(f"[!] Error al enviar paquete OSC: {e}")

# Registrar la función callback para flancos de subida (rising edge)
clk_pin.when_activated = on_pulse

try:
    # Bucle infinito para mantener el script corriendo de manera headless
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    print("\nDeteniendo puente de sincronizacion GPIO...")
