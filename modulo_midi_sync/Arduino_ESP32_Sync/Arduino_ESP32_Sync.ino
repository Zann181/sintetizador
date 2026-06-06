#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <Preferences.h>
#include <atomic>
#include <map>

// ==========================================
// Configuración de Hardware y Red (SoftAP)
// ==========================================
const char* ap_ssid = "BAZZ";
const char* ap_password = "motas177";
const int udpPort = 8888;

#define GPIO_SYNC_OUT 18 // Pin conectado a la Raspberry Pi / Sintetizador
hw_timer_t * timer = NULL;
volatile bool usbTrigger = false;
volatile bool manualTrigger = false;
volatile bool is_beat_1 = false;
volatile bool is_other_beat = false;
volatile uint64_t pulse_width_us = 10000;

// Variables atómicas y globales
std::atomic<float> nudge_ms(0.0f);
std::atomic<float> current_bpm(120.0f);
volatile unsigned long last_usb_rx_time = 0;

Preferences preferences;
bool nudge_changed = false;
unsigned long nudge_changed_time = 0;

std::map<String, unsigned long> active_clients;

// ==========================================
// Servidor Web
// ==========================================
WebServer server(80);

void updateClientIP() {
    String ip = server.client().remoteIP().toString();
    if (ip != "0.0.0.0" && ip != "") {
        active_clients[ip] = millis();
    }
}

const char* index_html = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="utf-8">
  <title>ESP32 Sync Bridge</title>
  <style>
    body { background-color: #0f0a0a; color: #E0E0E0; font-family: 'Arial', sans-serif; text-align: center; margin-top: 30px; }
    h1 { color: #FF6600; font-weight: bold; }
    .btn { background-color: #2a1510; color: white; padding: 20px 40px; font-size: 18px; border: 2px solid #FF6600; cursor: pointer; border-radius: 10px; margin: 10px; font-weight: bold;}
    .btn:active { background-color: #FF6600; color: #000; }
    p { font-size: 1.2rem; }
    .led { display: inline-block; width: 20px; height: 20px; border-radius: 50%; background-color: #220000; border: 1px solid #FF6600; vertical-align: middle; margin-left: 10px; }
    .led.on { background-color: #FF0000; box-shadow: 0 0 10px #FF0000; }
    .slider { width: 80%; margin: 20px 0; }
    .panel { margin: 20px auto; padding: 20px; background-color: #1a1010; border-radius: 10px; display: inline-block; width: 80%; max-width: 400px; }
  </style>
</head>
<body>
  <h1>ESP32 PANEL</h1>
  <p>Estado de Red: <span style="color: #00FFCC;"><strong>ONLINE</strong></span></p>
  
  <div class="panel">
    <p>Serial RX: <span id="usb_led" class="led"></span></p>
    <p style="font-size: 24px; color: #00FFCC;"><strong id="bpm_val">0.0</strong> BPM</p>
  </div>

  <div class="panel">
    <p>Conectados al Servidor ESP32:</p>
    <div id="ip_list" style="color: #00FFCC; font-size: 14px; min-height: 20px;">Buscando...</div>
  </div>

  <div class="panel">
    <p>Phase Nudge: <strong id="nudge_val">0.0</strong> ms</p>
    <input type="range" min="-100" max="100" value="0" step="5" class="slider" id="nudgeSlider" oninput="updateNudge(this.value)" onchange="sendNudge(this.value)">
    <p style="font-size: 12px; color: #888;">Compensación de Latencia (Lag)</p>
  </div>

  <button class="btn" onclick="fetch('/trigger')">TEST PULSE</button>

  <script>
    fetch('/get_nudge').then(r => r.text()).then(val => {
      document.getElementById('nudgeSlider').value = val;
      document.getElementById('nudge_val').innerText = parseFloat(val).toFixed(1);
    });

    function updateNudge(val) {
      document.getElementById('nudge_val').innerText = parseFloat(val).toFixed(1);
    }
    function sendNudge(val) {
      fetch('/set_nudge?val=' + val);
    }
    setInterval(() => {
      fetch('/status').then(r => r.json()).then(data => {
        let led = document.getElementById('usb_led');
        if(data.usb_rx) { led.classList.add('on'); } 
        else { led.classList.remove('on'); }
        document.getElementById('bpm_val').innerText = data.bpm.toFixed(1);
        if(data.ips && data.ips.length > 0) {
          document.getElementById('ip_list').innerHTML = data.ips.join('<br>');
        } else {
          document.getElementById('ip_list').innerHTML = "Ninguno";
        }
      });
    }, 200);
  </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  updateClientIP();
  server.send(200, "text/html", index_html);
}

void handleTrigger() {
  manualTrigger = true;
  server.send(200, "text/plain", "Pulse Sent");
}

void handleStatus() {
  updateClientIP();
  
  bool usb_active = (millis() - last_usb_rx_time) < 500;
  
  String ip_list = "[";
  bool first = true;
  unsigned long now = millis();
  for (auto it = active_clients.begin(); it != active_clients.end(); ) {
      if (now - it->second > 5000) { // Eliminar tras 5 seg de inactividad
          it = active_clients.erase(it);
      } else {
          if (!first) ip_list += ",";
          ip_list += "\"" + it->first + "\"";
          first = false;
          ++it;
      }
  }
  ip_list += "]";

  String json = "{\"usb_rx\": " + String(usb_active ? "true" : "false") + ", \"bpm\": " + String(current_bpm.load()) + ", \"ips\": " + ip_list + "}";
  server.send(200, "application/json", json);
}

void handleSetNudge() {
  if (server.hasArg("val")) {
    float val = server.arg("val").toFloat();
    nudge_ms.store(val);
    nudge_changed = true;
    nudge_changed_time = millis();
  }
  server.send(200, "text/plain", "OK");
}

void handleGetNudge() {
  server.send(200, "text/plain", String(nudge_ms.load()));
}

WiFiUDP Udp;

// ==========================================
// Núcleo 0: Red y Control (Web + NVS)
// ==========================================
void TaskCore0(void *pvParameters) {
    IPAddress local_ip(192, 168, 4, 1); // IP estándar de ESP32
    IPAddress gateway(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);
    
    Serial.println("[WIFI] Configurando SoftAP...");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ap_ssid, ap_password);
    Udp.begin(udpPort);
    
    Serial.println("[WIFI] Punto de acceso iniciado: BAZZ");
    Serial.print("[WIFI] IP de la pagina web: ");
    Serial.println(WiFi.softAPIP());

    server.on("/", handleRoot);
    server.on("/trigger", handleTrigger);
    server.on("/status", handleStatus);
    server.on("/set_nudge", handleSetNudge);
    server.on("/get_nudge", handleGetNudge);
    server.begin();
    
    Serial.println("[WEB] Servidor web iniciado en el puerto 80. Sin clave de acceso.");

    for (;;) {
        server.handleClient();

        if (nudge_changed && (millis() - nudge_changed_time > 2000)) {
            preferences.begin("sync", false);
            preferences.putFloat("nudge", nudge_ms.load());
            preferences.end();
            nudge_changed = false;
            Serial.println("[NVS] Nueva calibracion guardada en memoria.");
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// ==========================================
// Núcleo 1: DSP, PLL Predictivo y Hardware Timer
// ==========================================
volatile bool pin_is_high = false;

void IRAM_ATTR onTimer() {
    if (!pin_is_high) {
        digitalWrite(GPIO_SYNC_OUT, HIGH);
        pin_is_high = true;
        // Nueva API de Timer para ESP32 Core v3
        timerAlarm(timer, pulse_width_us, false, 0); 
    } else {
        digitalWrite(GPIO_SYNC_OUT, LOW);
        pin_is_high = false;
    }
}

void TaskCore1(void *pvParameters) {
    pinMode(GPIO_SYNC_OUT, OUTPUT);
    digitalWrite(GPIO_SYNC_OUT, LOW);

    // Nueva API de Timer para ESP32 Core v3
    timer = timerBegin(1000000); // Frecuencia de 1MHz (1 tick = 1us)
    timerAttachInterrupt(timer, &onTimer);

    uint32_t history[24] = {0};
    for(int i=0; i<24; i++) history[i] = 20833; // 120 BPM default
    int h_idx = 0;
    uint32_t last_usb_us = 0;

    for (;;) {
        // Leer puerto serial (desde el script Python de PC Bridge)
        while (Serial.available()) {
            uint8_t byte_read = Serial.read();
            if (byte_read == 0xF7 || byte_read == 0xF8 || byte_read == 0xF9) {
                usbTrigger = true;
                is_beat_1 = (byte_read == 0xF9);
                is_other_beat = (byte_read == 0xF8);
                last_usb_rx_time = millis();
            }
        }

        if (usbTrigger) {
            usbTrigger = false;
            if (is_beat_1) {
                pulse_width_us = 50000;
            } else if (is_other_beat) {
                pulse_width_us = 20000; // Rojo: 20ms
            } else {
                pulse_width_us = 10000; // Azul: 10ms
            }
            uint32_t now_us = micros();
            
            if (last_usb_us != 0) {
                uint32_t delta = now_us - last_usb_us;
                if (delta > 100000 && delta < 2000000) { 
                    history[h_idx] = delta;
                    h_idx = (h_idx + 1) % 24;
                }
            }
            last_usb_us = now_us;

            uint32_t sum = 0;
            for(int i=0; i<24; i++) sum += history[i];
            uint32_t avg_delta = sum / 24;
            
            float calc_bpm = 60000000.0f / avg_delta;
            current_bpm.store(calc_bpm);

            // Predicción predictiva del PLL con Nudge
            float target_delay = avg_delta + (nudge_ms.load() * 1000.0f);
            
            while (target_delay < 1000.0f) {
                target_delay += avg_delta;
            }

            if (!pin_is_high) {
                timerWrite(timer, 0);
                timerAlarm(timer, (uint64_t)target_delay, false, 0);
            }
        }
        
        if (manualTrigger) {
            manualTrigger = false;
            if (!pin_is_high) {
                digitalWrite(GPIO_SYNC_OUT, HIGH);
                pin_is_high = true;
                timerWrite(timer, 0);
                timerAlarm(timer, 500, false, 0);
            }
        }
        
        vTaskDelay(1); // Pequeño delay para Watchdog, la precisión viene del timer de hardware
    }
}

void setup() {
    Serial.begin(115200);

    // Recuperar configuración de Flash
    preferences.begin("sync", true);
    nudge_ms.store(preferences.getFloat("nudge", 0.0f));
    preferences.end();

    xTaskCreatePinnedToCore(TaskCore0, "NetworkTask", 8192, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(TaskCore1, "DSPTask", 8192, NULL, configMAX_PRIORITIES - 1, NULL, 1);
}

void loop() {
    vTaskSuspend(NULL);
}
