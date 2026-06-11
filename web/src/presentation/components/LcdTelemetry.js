export class LcdTelemetry {
    constructor(stateManager) {
        this.stateManager = stateManager;
        this.ledInterval = null;
        this.simulatedRam = 18.2;
    }

    init() {
        this.stateManager.on('bpmUpdated', (bpm) => {
            const display = document.getElementById('bpm-display');
            if (display) display.innerText = Math.round(bpm);
            const slider = document.getElementById('master-bpm-slider');
            if (slider) slider.value = Math.round(bpm);
        });

        this.stateManager.on('paramsChanged', () => {
            // Update BPM from parameters
            const bpmParam = this.stateManager.getParameter('/master/bpm');
            if (bpmParam) {
                const bv = Math.round(bpmParam.value);
                const display = document.getElementById('bpm-display');
                if (display) display.innerText = bv;
                const slider = document.getElementById('master-bpm-slider');
                if (slider && document.activeElement !== slider && !this.stateManager.isBpmLocked) {
                    slider.value = bv;
                }
                if (Math.abs(this.stateManager.currentBpm - bpmParam.value) > 0.5) {
                    this.stateManager.currentBpm = bpmParam.value;
                    this.startInternalBpmBlinking();
                }
            }

            // Sync settings emu controls
            const emuActive = this.stateManager.getParameter('/emulator/active');
            const emuBpm = this.stateManager.getParameter('/emulator/bpm');
            if (emuActive) {
                const t = document.getElementById('emu-active-toggle');
                if (t && document.activeElement !== t) t.checked = emuActive.value > 0.5;
            }
            if (emuBpm) {
                const sl = document.getElementById('emu-bpm-input');
                if (sl && document.activeElement !== sl) {
                    sl.value = Math.round(emuBpm.value);
                    const disp = document.getElementById('emu-bpm-display');
                    if (disp) disp.innerText = Math.round(emuBpm.value);
                }
            }
        });

        this.startTelemetryLoops();
    }

    startTelemetryLoops() {
        // CPU/RAM HUD polling loop
        setInterval(() => {
            const cpuVal = (1.2 + Math.sin(Date.now() / 3000) * 0.8 + Math.random() * 0.4).toFixed(1);
            this.simulatedRam += (Math.random() - 0.5) * 0.05;
            this.simulatedRam = Math.max(17.8, Math.min(18.9, this.simulatedRam));
            
            const cpuEl = document.getElementById('hud-cpu');
            const ramEl = document.getElementById('hud-ram');
            
            if (cpuEl) cpuEl.innerText = `${cpuVal}%`;
            if (ramEl) ramEl.innerText = `${this.simulatedRam.toFixed(1)} MB`;
        }, 2000);

        // dB Audio meter polling loop
        setInterval(async () => {
            try {
                const r = await fetch((this.stateManager.apiClient.apiBase) + '/api/level');
                if (!r.ok) return;
                const data = await r.json();
                const db = parseFloat(data.db) || -96.0;
                
                const dbEl = document.getElementById('hud-db');
                if (dbEl) dbEl.innerText = db < -60 ? 'INF dB' : `${Math.round(db)} dB`;
                
                this.updateLcdDbMeter(db);
            } catch(e) {
                // Server offline
            }
        }, 120);
    }

    updateLcdDbMeter(db) {
        const bar = document.getElementById('hud-master-bar');
        if (!bar) return;
        
        let segmentsCount = 0;
        if (db > -48) segmentsCount = 1;
        if (db > -24) segmentsCount = 2;
        if (db > -12) segmentsCount = 3;
        if (db > -6)  segmentsCount = 4;
        if (db > -2)  segmentsCount = 5;
        if (db > 0)   segmentsCount = 6;

        let html = '';
        for (let i = 0; i < 6; i++) {
            let activeClass = '';
            if (i < segmentsCount) {
                if (i >= 5) activeClass = ' active-prim'; // Red
                else if (i >= 4) activeClass = ' active-sec';  // Orange
                else activeClass = ' active-accent';          // Cyan
            }
            html += `<div class="led-segment-mini${activeClass}"></div>`;
        }
        bar.innerHTML = html;
    }

    triggerBpmLedFlash(step) {
        const led = document.getElementById('bpm-led');
        if (!led) return;

        led.classList.remove('led-active', 'led-active-green', 'led-active-red', 'led-active-blue');
        
        if (step === 0) {
            led.classList.add('led-active-blue');
        } else if (step % 4 === 0) {
            led.classList.add('led-active-green');
        } else {
            led.classList.add('led-active-red');
        }

        setTimeout(() => {
            led.classList.remove('led-active', 'led-active-green', 'led-active-red', 'led-active-blue');
        }, 60);
    }

    startInternalBpmBlinking() {
        if (this.ledInterval) clearInterval(this.ledInterval);
        
        let blinkStep = 0;
        const triggerBlink = () => {
            if (this.stateManager.syncWebSocket.hasWebSocketSync) return; // Prioritize link sync
            this.triggerBpmLedFlash(blinkStep);
            blinkStep = (blinkStep + 1) % 16;
            
            const bpm = parseFloat(this.stateManager.currentBpm) || 140;
            const ms = (60000 / bpm) / 4; // 16th note division
            setTimeout(triggerBlink, ms);
        };
        
        triggerBlink();
    }
}
