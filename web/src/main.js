import { ApiClient } from './infrastructure/ApiClient.js';
import { SyncWebSocket } from './infrastructure/SyncWebSocket.js';
import { LocalStorageRepo } from './infrastructure/LocalStorageRepo.js';

import { StateManager } from './application/StateManager.js';
import { SequencerService } from './application/SequencerService.js';
import { PerformerService } from './application/PerformerService.js';

import { KnobDragHandler } from './presentation/handlers/KnobDragHandler.js';
import { LcdTelemetry } from './presentation/components/LcdTelemetry.js';
import { MixerConsole } from './presentation/components/MixerConsole.js';
import { SequencerGrid } from './presentation/components/SequencerGrid.js';
import { InstrumentPanel } from './presentation/components/InstrumentPanel.js';
import { PerformerUi } from './presentation/components/PerformerUi.js';
import { MappingModal } from './presentation/components/MappingModal.js';

import { INSTRUMENTS } from './domain/Sequencer.js';

// 1. Instantiation
const apiClient = new ApiClient();
const syncWebSocket = new SyncWebSocket();
const storageRepo = new LocalStorageRepo();

const stateManager = new StateManager(apiClient, storageRepo);
const sequencerService = new SequencerService(stateManager, apiClient, storageRepo, syncWebSocket);
const performerService = new PerformerService(stateManager, apiClient, storageRepo);

const knobDragHandler = new KnobDragHandler(stateManager);

const lcdTelemetry = new LcdTelemetry(stateManager);
const mixerConsole = new MixerConsole(stateManager, sequencerService, performerService, knobDragHandler);
const sequencerGrid = new SequencerGrid(stateManager, sequencerService);
const instrumentPanel = new InstrumentPanel(stateManager, knobDragHandler);
const performerUi = new PerformerUi(stateManager, performerService);
const mappingModal = new MappingModal(stateManager);

// 2. Wiring events
stateManager.on('paramsChanged', () => {
    if (!stateManager.mixerConsoleRendered) {
        mixerConsole.render();
        stateManager.mixerConsoleRendered = true;
    } else {
        mixerConsole.updateValues();
    }
    
    if (!stateManager.activeInstrumentRendered) {
        instrumentPanel.render();
        stateManager.activeInstrumentRendered = true;
    } else {
        instrumentPanel.updateValues();
    }
});

stateManager.on('instrumentChanged', () => {
    stateManager.activeInstrumentRendered = false;
    stateManager.syncParams();
});

sequencerService.on('playheadMoved', (step) => {
    sequencerGrid.updatePlayhead(step);
});

sequencerService.on('stepTriggered', ({ instKey, stepIndex, value }) => {
    sequencerGrid.updateStepPadDOM(instKey, stepIndex, value);
});

sequencerService.on('grooveStepsChanged', (instKey) => {
    sequencerGrid.syncLocalDropdown(instKey);
    mixerConsole.syncInstrumentGrooveSelector(instKey);
});

sequencerService.on('ledFlash', (step) => {
    lcdTelemetry.triggerBpmLedFlash(step);
});

sequencerService.on('txPulse', (data) => {
    const ledTx = document.getElementById("led-tx");
    const trace = document.getElementById("web-osc-trace");
    if (!ledTx || !trace) return;

    if (data.pulse === 1) { // Phrase start beat pulse
        sequencerService.hasWebSocketSync = true;
        stateManager.hasWebSocketSync = true;
        lcdTelemetry.triggerBpmLedFlash(0);
        
        const c = data.color || "#00ff00";
        ledTx.style.background = c;
        ledTx.style.boxShadow = "0 0 5px " + c;
        trace.style.borderColor = c;
        trace.style.borderBottomColor = "transparent";
        trace.style.width = "40%";
    } else if (data.pulse === 2) {
        const c = data.color || "#00ffff";
        ledTx.style.background = c;
        ledTx.style.boxShadow = "0 0 5px " + c;
        trace.style.borderColor = c;
        trace.style.borderBottomColor = "transparent";
        trace.style.width = "10%";
    } else {
        ledTx.style.background = "#220000";
        ledTx.style.boxShadow = "none";
        trace.style.borderColor = "transparent";
    }
});

sequencerService.on('rxPulse', (data) => {
    const ledRx = document.getElementById("led-rx");
    if (!ledRx) return;
    ledRx.style.background = data.color;
    ledRx.style.boxShadow = "0 0 5px " + data.color;
    setTimeout(() => {
        ledRx.style.background = "#002200";
        ledRx.style.boxShadow = "none";
    }, 50);
});

performerService.on('instrumentAutoStateChanged', () => {
    mixerConsole.render();
});

// 3. Global Window Scope Event Bindings (To support existing inline HTML events without visual regressions)

window.onBpmAction = (action) => {
    if (stateManager.isMappingMode) return;
    let currentBpmNum = parseFloat(stateManager.currentBpm) || 140;
    let targetBpm = currentBpmNum;
    if (action === 'divide') targetBpm = Math.max(60, currentBpmNum / 2);
    else if (action === 'multiply') targetBpm = Math.min(240, currentBpmNum * 2);
    else if (action === 'dec') targetBpm = Math.max(60, currentBpmNum - 1);
    else if (action === 'inc') targetBpm = Math.min(240, currentBpmNum + 1);
    targetBpm = Math.round(targetBpm);
    stateManager.currentBpm = targetBpm;
    
    const display = document.getElementById('bpm-display');
    if (display) display.innerText = targetBpm;
    const bpmSlider = document.getElementById('master-bpm-slider');
    if (bpmSlider) bpmSlider.value = targetBpm;
    
    stateManager.updateParamValue('/master/bpm', targetBpm);
    lcdTelemetry.startInternalBpmBlinking();
};

window.onMasterBpmInput = (val) => {
    if (stateManager.isMappingMode) return;
    const display = document.getElementById('bpm-display');
    if (display) display.innerText = Math.round(val);
    stateManager.currentBpm = parseFloat(val);
    stateManager.updateParamValue('/master/bpm', val);
};

window.togglePerformerDrawer = () => {
    performerUi.toggleDrawer();
};

window.toggleSettingsDrawer = () => {
    const drawer = document.querySelector('.right-col');
    if (!drawer) return;
    
    drawer.classList.toggle('open');
    const btn = document.getElementById('btn-settings-toggle');
    if (btn) btn.classList.toggle('btn-active', drawer.classList.contains('open'));

    if (drawer.classList.contains('open')) {
        const perfDrawer = document.querySelector('.performer-drawer');
        if (perfDrawer && perfDrawer.classList.contains('open')) {
            window.togglePerformerDrawer();
        }
    }
};

window.toggleMainView = () => {
    const chk = document.getElementById('view-toggle-checkbox');
    const mixer = document.getElementById('master-mix-console');
    const pad = document.getElementById('pad-console');
    
    if (chk.checked) {
        mixer.style.display = 'none';
        pad.style.display = 'flex';
        if (!sequencerService.playheadRunning) {
            sequencerService.startPlayhead();
        }
    } else {
        pad.style.display = 'none';
        mixer.style.display = 'grid';
    }
};

window.loadSelectedPerformance = (val) => {
    performerService.loadSelectedPerformance(val);
};

window.startPerformance = () => {
    performerService.startPerformance();
};

window.stopPerformance = () => {
    performerService.stopPerformance();
};

window.saveActivePerformance = async () => {
    const editor = document.getElementById('perf-json-editor');
    if (!editor) return;
    const res = await performerService.saveActivePerformance(editor.value);
    if (res.success) {
        alert("Performance guardada con éxito en el servidor.");
    } else {
        alert("Error al guardar: " + res.error);
    }
};

window.createNewPerformance = async () => {
    const key = await performerService.createNewPerformance();
    performerUi.toggleDrawer();
};

window.deleteActivePerformance = async () => {
    const all = performerService.getActivePerformances();
    const activeName = all[performerService.activePerfKey]?.name || '';
    if (!confirm(`¿Desea borrar la performance custom "${activeName}"?`)) return;
    await performerService.deleteActivePerformance();
};

window.applyGrooveGlobal = (val) => {
    sequencerService.loadGroovePattern(val);
};

window.promptSaveGroove = async () => {
    const name = prompt('Nombre del nuevo Groove (guarda todos los pads actuales):');
    if (!name || !name.trim()) return;
    await sequencerService.saveCurrentAsGroove(name);
};

window.promptRenameGroove = async () => {
    const gsel = document.getElementById('global-groove-select');
    const oldName = gsel ? gsel.value : '';
    if (!oldName) { alert('Selecciona un groove primero.'); return; }
    const newName = prompt(`Renombrar "${oldName}" a:`, oldName);
    if (!newName || !newName.trim() || newName.trim() === oldName) return;
    await sequencerService.renameGroove(oldName, newName);
};

window.confirmDeleteGroove = async () => {
    const gsel = document.getElementById('global-groove-select');
    const name = gsel ? gsel.value : '';
    if (!name) { alert('Selecciona un groove para borrar.'); return; }
    if (!confirm(`¿Borrar el groove "${name}"?`)) return;
    await sequencerService.deleteGroove(name);
};

window.randomizeGroove = () => {
    sequencerService.randomizePads();
};

window.clearAllSteps = () => {
    if (!confirm('¿Limpiar todos los pasos de todos los instrumentos?')) return;
    sequencerService.clearAllSteps();
};

window.setActiveInstrument = (key) => {
    stateManager.setActiveInstrument(key);
};

window.toggleMappingMode = () => {
    const active = stateManager.toggleMappingMode();
    const btn = document.getElementById("btn-mapeo");
    if (!btn) return;
    
    if (active) {
        btn.style.background = "var(--accent-cyan)";
        btn.innerText = "DESACTIVAR";
    } else {
        btn.style.background = "rgba(255,255,255,0.02)";
        btn.innerText = "ACTIVAR";
    }
};

window.closeMappingModal = () => {
    mappingModal.close();
};

window.saveMappingModal = () => {
    mappingModal.save();
};

window.triggerPreset = async (action) => {
    try {
        await apiClient.setParam('/preset/' + action, 1);
        alert(`Preset ${action === 'save' ? 'guardado' : 'cargado'} con éxito.`);
        setTimeout(() => stateManager.syncParams(), 300);
    } catch (e) {
        console.error(e);
    }
};

window.triggerAutomation = async (action) => {
    try {
        await apiClient.setParam('/automation/' + action, 1);
        ['btn-record', 'btn-play', 'btn-stop', 'btn-r-rec', 'btn-r-play', 'btn-r-stop'].forEach(id => {
            const el = document.getElementById(id);
            if (el) el.classList.remove('btn-active');
        });
        if (action === 'record') {
            const el = document.getElementById('btn-r-rec');
            if (el) el.classList.add('btn-active');
        } else if (action === 'play') {
            const el = document.getElementById('btn-r-play');
            if (el) el.classList.add('btn-active');
        }
    } catch (e) {
        console.error(e);
    }
};

window.toggleBpmLock = (checked) => {
    stateManager.isBpmLocked = checked;
    const bpmSlider = document.getElementById("master-bpm-slider");
    if (bpmSlider) bpmSlider.disabled = checked;
};

window.nudgeBpm = async (amount) => {
    if (stateManager.isBpmLocked) return;
    const bpmSlider = document.getElementById("master-bpm-slider");
    if (!bpmSlider) return;
    
    window.originalBpmBeforeNudge = parseFloat(bpmSlider.value) || 140;
    const newBpm = window.originalBpmBeforeNudge + amount;
    
    await apiClient.setParam('/master/bpm', newBpm);
};

window.resetNudge = async () => {
    if (stateManager.isBpmLocked) return;
    if (window.originalBpmBeforeNudge) {
        await apiClient.setParam('/master/bpm', window.originalBpmBeforeNudge);
    }
};

window.toggleEmulator = (checked) => {
    stateManager.updateParamValue('/emulator/active', checked ? 1 : 0);
};

window.setEmulatorBpm = (bpm) => {
    const disp = document.getElementById('emu-bpm-display');
    if (disp) disp.innerText = Math.round(bpm);
    stateManager.updateParamValue('/emulator/bpm', bpm);
};

window.setAudioDevice = (id) => {
    if (!id) return;
    apiClient.setAudioDevice(id);
};

window.onMixerTabSelect = (key) => {
    window.setActiveInstrument(key);
};

window.onMixerToggleAuto = (key, event) => {
    if (event) event.stopPropagation(); // Avoid triggering tab selection click
    performerService.toggleInstrumentAuto(key);
};

window.onMixerLocalGroove = (instKey, val) => {
    sequencerService.loadInstrumentLocalGroove(instKey, val);
};

window.onMixerUpdateParam = (path, val, displayId) => {
    stateManager.updateParamValue(path, val);
    if (displayId) {
        const param = stateManager.getParameter(path);
        if (param) {
            const effValue = param.getEffectiveValue(val, stateManager.paramMappings);
            const el = document.getElementById(displayId);
            if (el) el.innerText = effValue.toFixed(2);
        } else {
            const el = document.getElementById(displayId);
            if (el) el.innerText = parseFloat(val).toFixed(2);
        }
    }
};

window.onSequencerLocalGroove = (instKey, val) => {
    sequencerService.loadInstrumentLocalGroove(instKey, val);
};

window.onSequencerToggleStep = (instKey, i) => {
    sequencerService.togglePadStep(instKey, i);
};

// Bind tab selection from instrument tabs header
window.onTabButtonClick = (key) => {
    window.setActiveInstrument(key);
};

// 4. Initialization Startup
async function start() {
    // Register UI component listeners first so they catch startup load events
    mappingModal.init();
    performerUi.init();
    lcdTelemetry.init();

    await stateManager.init();
    await sequencerService.init();
    await performerService.init();

    // Render components
    mixerConsole.render();
    sequencerGrid.render();
    instrumentPanel.render();

    // Telemetry polling
    setInterval(() => stateManager.syncParams(), 1000);
    
    // Status polling (Link Sync details, MIDI & OSC)
    setInterval(async () => {
        try {
            const st = await apiClient.fetchStatus();
            
            // Audio output device list
            const select = document.getElementById('audio-device-select');
            if (select && st.devices) {
                if (select.options.length <= 1) {
                    stateManager.audioDevices = st.devices;
                    let html = '';
                    st.devices.forEach(d => {
                        const sel = d.active ? 'selected' : '';
                        html += `<option value="${d.id}" ${sel}>${d.name}</option>`;
                    });
                    select.innerHTML = html;
                } else {
                    const activeDev = st.devices.find(d => d.active);
                    if (activeDev && select.value !== String(activeDev.id)) {
                        select.value = activeDev.id;
                    }
                }
            }

            // Remote OSC IPs list
            const ipList = document.getElementById('ip-list');
            if (ipList && st.ips) {
                ipList.innerHTML = st.ips.map(ip => `<li>IP: <a href="http://${ip}:8000" target="_blank">${ip}</a></li>`).join('');
            }

            // Sync indicators
            const oscDot = document.getElementById('hud-osc');
            if (oscDot) oscDot.classList.toggle('active', !!st.oscActive);

            const midiDot = document.getElementById('hud-midi');
            if (midiDot) midiDot.classList.toggle('active', !!st.midiActive);

        } catch (e) {
            // Offline
        }
    }, 2000);

    lcdTelemetry.startInternalBpmBlinking();
    setTimeout(() => {
        sequencerService.startPlayhead();
    }, 1500);
}

// Kick off
start();
