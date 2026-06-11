import { INSTRUMENTS } from '../domain/Sequencer.js';
import { DEFAULT_GROOVES } from '../domain/Groove.js';

export class SequencerService {
    constructor(stateManager, apiClient, storageRepo, syncWebSocket) {
        this.stateManager = stateManager;
        this.apiClient = apiClient;
        this.storageRepo = storageRepo;
        this.syncWebSocket = syncWebSocket;

        this.customGrooves = {};
        this.playheadStep = -1;
        this.playheadRunning = false;
        this.playheadInterval = null;
        this.hasWebSocketSync = false;
        this.wsSyncTimeout = null;

        this.listeners = {
            stepTriggered: [],
            playheadMoved: [],
            groovesLoaded: [],
            clockTick: []
        };
    }

    on(event, cb) {
        if (this.listeners[event]) this.listeners[event].push(cb);
    }

    emit(event, data) {
        if (this.listeners[event]) this.listeners[event].forEach(cb => cb(data));
    }

    async init() {
        // Load grooves (server first, then fallback to local storage, then default library)
        let loaded = false;
        try {
            const serverGrooves = await this.apiClient.loadGrooves();
            if (serverGrooves && typeof serverGrooves === 'object' && Object.keys(serverGrooves).length > 0) {
                this.customGrooves = serverGrooves;
                this.storageRepo.saveCustomGrooves(serverGrooves);
                loaded = true;
            }
        } catch (e) {
            console.warn("Server grooves offline, loading local storage:", e.message);
        }

        if (!loaded) {
            const local = this.storageRepo.getCustomGrooves();
            if (local && Object.keys(local).length > 0) {
                this.customGrooves = local;
            } else {
                this.customGrooves = Object.assign({}, DEFAULT_GROOVES);
                this.storageRepo.saveCustomGrooves(this.customGrooves);
            }
        }

        // Setup WS Sync
        this.syncWebSocket.on('beat', (data) => this.handleWebSocketBeat(data));
        this.syncWebSocket.on('tx', (data) => this.emit('txPulse', data));
        this.syncWebSocket.on('rx', (data) => this.emit('rxPulse', data));
        this.syncWebSocket.connect();

        this.emit('groovesLoaded', this.customGrooves);
    }

    startPlayhead() {
        if (this.playheadInterval) clearInterval(this.playheadInterval);
        this.playheadRunning = true;

        this.playheadInterval = setInterval(async () => {
            if (!this.playheadRunning) return;
            try {
                const status = await this.apiClient.fetchStatus();
                if (status.currentStep !== undefined && status.currentStep >= 0 && status.currentStep !== this.playheadStep) {
                    this.playheadStep = status.currentStep;
                    this.emit('playheadMoved', this.playheadStep);
                }
                if (status.bpm > 20 && Math.round(status.bpm) !== Math.round(this.stateManager.currentBpm)) {
                    this.stateManager.currentBpm = status.bpm;
                    this.emit('bpmUpdated', status.bpm);
                }
            } catch (e) {
                // Server offline
            }
        }, 50);
    }

    stopPlayhead() {
        this.playheadRunning = false;
        if (this.playheadInterval) {
            clearInterval(this.playheadInterval);
            this.playheadInterval = null;
        }
        this.playheadStep = -1;
        this.emit('playheadMoved', -1);
    }

    handleWebSocketBeat(data) {
        this.hasWebSocketSync = true;
        const step = data.step % 16;
        if (step !== undefined && step >= 0 && step !== this.playheadStep) {
            this.playheadStep = step;
            this.emit('playheadMoved', this.playheadStep);
        }

        // Notify ticker LED flashing
        this.emit('ledFlash', data.step);

        if (this.wsSyncTimeout) clearTimeout(this.wsSyncTimeout);
        this.wsSyncTimeout = setTimeout(() => {
            this.hasWebSocketSync = false;
        }, 3000);
    }

    async togglePadStep(instKey, stepIndex) {
        const inst = INSTRUMENTS.find(i => i.key === instKey);
        if (!inst) return;

        const path = `${inst.prefix}step${stepIndex}`;
        const param = this.stateManager.getParameter(path);
        const currentVal = param ? param.value : 0.0;
        const newVal = currentVal > 0.0 ? 0.0 : 1.0;

        if (param) param.value = newVal;

        this.emit('stepTriggered', { instKey, stepIndex, value: newVal });
        await this.stateManager.updateParamValue(path, newVal);
        this.emit('grooveStepsChanged', instKey);
    }

    loadGroovePattern(name) {
        const pattern = this.customGrooves[name];
        if (!pattern) return;

        INSTRUMENTS.forEach(inst => {
            const arr = pattern[inst.key];
            if (!arr) return;
            for (let i = 0; i < 16; i++) {
                const newVal = arr[i] ? 1.0 : 0.0;
                const path = `${inst.prefix}step${i}`;
                const param = this.stateManager.getParameter(path);
                if (param) param.value = newVal;
                
                this.emit('stepTriggered', { instKey: inst.key, stepIndex: i, value: newVal });
                this.stateManager.updateParamValue(path, newVal);
            }
            this.emit('grooveStepsChanged', inst.key);
        });
    }

    loadInstrumentLocalGroove(instKey, name) {
        const pattern = this.customGrooves[name];
        const inst = INSTRUMENTS.find(i => i.key === instKey);
        if (!pattern || !inst) return;

        const arr = pattern[instKey];
        if (!arr) return;

        for (let i = 0; i < 16; i++) {
            const newVal = arr[i] ? 1.0 : 0.0;
            const path = `${inst.prefix}step${i}`;
            const param = this.stateManager.getParameter(path);
            if (param) param.value = newVal;

            this.emit('stepTriggered', { instKey, stepIndex: i, value: newVal });
            this.stateManager.updateParamValue(path, newVal);
        }
        this.emit('grooveStepsChanged', instKey);
    }

    getCurrentPadsState() {
        const state = {};
        INSTRUMENTS.forEach(inst => {
            state[inst.key] = [];
            for (let i = 0; i < 16; i++) {
                const p = this.stateManager.getParameter(`${inst.prefix}step${i}`);
                state[inst.key].push((p && p.value > 0.0) ? 1 : 0);
            }
        });
        return state;
    }

    async saveCurrentAsGroove(name) {
        if (!name || !name.trim()) return;
        const cleanName = name.trim();
        this.customGrooves[cleanName] = this.getCurrentPadsState();
        
        this.storageRepo.saveCustomGrooves(this.customGrooves);
        try {
            await this.apiClient.saveGrooves(this.customGrooves);
        } catch (e) {
            console.error('Error saving grooves to server:', e);
        }
        this.emit('groovesLoaded', this.customGrooves);
    }

    async renameGroove(oldName, newName) {
        if (!oldName || !newName || !newName.trim() || oldName === newName.trim()) return;
        const cleanNewName = newName.trim();
        this.customGrooves[cleanNewName] = this.customGrooves[oldName];
        delete this.customGrooves[oldName];

        this.storageRepo.saveCustomGrooves(this.customGrooves);
        try {
            await this.apiClient.saveGrooves(this.customGrooves);
        } catch (e) {
            console.error('Error renaming groove on server:', e);
        }
        this.emit('groovesLoaded', this.customGrooves);
    }

    async deleteGroove(name) {
        if (!name || !this.customGrooves[name]) return;
        delete this.customGrooves[name];

        this.storageRepo.saveCustomGrooves(this.customGrooves);
        try {
            await this.apiClient.saveGrooves(this.customGrooves);
        } catch (e) {
            console.error('Error deleting groove from server:', e);
        }
        this.emit('groovesLoaded', this.customGrooves);
    }

    randomizePads() {
        const densities = {
            'bombo': 0.28,
            'caja': 0.20,
            'platillos': 0.45,
            'bajo': 0.30,
            'psycho': 0.22,
            'siringe': 0.18
        };

        INSTRUMENTS.forEach(inst => {
            const density = densities[inst.key] || 0.25;
            for (let i = 0; i < 16; i++) {
                const newVal = Math.random() < density ? 1.0 : 0.0;
                const path = `${inst.prefix}step${i}`;
                const param = this.stateManager.getParameter(path);
                if (param) param.value = newVal;

                this.emit('stepTriggered', { instKey: inst.key, stepIndex: i, value: newVal });
                this.stateManager.updateParamValue(path, newVal);
            }
            this.emit('grooveStepsChanged', inst.key);
        });
    }

    clearAllSteps() {
        INSTRUMENTS.forEach(inst => {
            for (let i = 0; i < 16; i++) {
                const path = `${inst.prefix}step${i}`;
                const param = this.stateManager.getParameter(path);
                if (param) param.value = 0.0;

                this.emit('stepTriggered', { instKey: inst.key, stepIndex: i, value: 0.0 });
                this.stateManager.updateParamValue(path, 0.0);
            }
            this.emit('grooveStepsChanged', inst.key);
        });
    }
}
