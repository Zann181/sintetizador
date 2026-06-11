import { BUILTIN_PERFS } from '../domain/Performance.js';
import { INSTRUMENTS } from '../domain/Sequencer.js';

export class PerformerService {
    constructor(stateManager, apiClient, storageRepo) {
        this.stateManager = stateManager;
        this.apiClient = apiClient;
        this.storageRepo = storageRepo;

        this.customPerfPresets = {};
        this.instrumentAutoState = {
            'bombo': true,
            'caja': true,
            'platillos': true,
            'bajo': true,
            'psycho': true,
            'siringe': true
        };

        this.activePerfKey = 'song-5m';
        this.perfActive = false;
        this.perfStartTime = 0;
        this.perfCurrentTime = 0;
        this.perfInterval = null;

        this.listeners = {
            statusChanged: [],
            timeUpdated: [],
            presetsReloaded: [],
            activePresetChanged: []
        };
    }

    on(event, cb) {
        if (this.listeners[event]) this.listeners[event].push(cb);
    }

    emit(event, data) {
        if (this.listeners[event]) this.listeners[event].forEach(cb => cb(data));
    }

    async init() {
        try {
            const data = await this.apiClient.loadPerformances();
            if (data && data.customPerfPresets) {
                this.customPerfPresets = data.customPerfPresets;
                this.storageRepo.saveCustomPerformances(this.customPerfPresets);
            }
            if (data && data.instrumentAutoState) {
                this.instrumentAutoState = Object.assign(this.instrumentAutoState, data.instrumentAutoState);
            }
        } catch (e) {
            console.warn("Server performances offline, loading local storage:", e.message);
            this.customPerfPresets = this.storageRepo.getCustomPerformances();
        }

        this.emit('presetsReloaded', this.getActivePerformances());
        this.loadSelectedPerformance(this.activePerfKey);
    }

    getActivePerformances() {
        return Object.assign({}, BUILTIN_PERFS, this.customPerfPresets);
    }

    async savePerformancesAndStates() {
        const dataToSave = {
            customPerfPresets: this.customPerfPresets,
            instrumentAutoState: this.instrumentAutoState
        };
        this.storageRepo.saveCustomPerformances(this.customPerfPresets);
        try {
            await this.apiClient.savePerformances(dataToSave);
        } catch (e) {
            console.error("Error saving performances to server:", e);
        }
    }

    loadSelectedPerformance(key) {
        this.activePerfKey = key;
        const all = this.getActivePerformances();
        const p = all[key];
        if (!p) return;

        this.emit('activePresetChanged', { key, preset: p });
    }

    startPerformance() {
        this.stopPerformance();
        const all = this.getActivePerformances();
        const p = all[this.activePerfKey];
        if (!p) return;

        this.perfActive = true;
        this.perfStartTime = Date.now();
        this.perfCurrentTime = 0;

        this.emit('statusChanged', { active: true, statusText: "ESTADO: Ejecutando", color: "#00ff00" });

        this.perfInterval = setInterval(() => {
            if (!this.perfActive) return;
            const elapsedMs = Date.now() - this.perfStartTime;
            this.perfCurrentTime = elapsedMs / 1000;

            if (this.perfCurrentTime >= p.duration) {
                this.perfCurrentTime = p.duration;
                this.stopPerformance();
                this.applyPerformanceTick(p, 100);
                return;
            }

            const activePct = (this.perfCurrentTime / p.duration) * 100;
            this.emit('timeUpdated', { currentTime: this.perfCurrentTime, duration: p.duration, percentage: activePct });

            this.applyPerformanceTick(p, activePct);
        }, 100);
    }

    stopPerformance() {
        this.perfActive = false;
        if (this.perfInterval) {
            clearInterval(this.perfInterval);
            this.perfInterval = null;
        }
        this.emit('statusChanged', { active: false, statusText: "ESTADO: Detenido", color: "#ffffff" });
    }

    applyPerformanceTick(perf, activePct) {
        const allPaths = new Set();
        perf.keyframes.forEach(kf => {
            Object.keys(kf.params).forEach(p => allPaths.add(p));
        });

        allPaths.forEach(path => {
            // Check if the param is for a bypassed instrument
            let isInstrumentParam = false;
            let instrumentKey = null;
            for (let inst of INSTRUMENTS) {
                if (path.startsWith(inst.prefix)) {
                    isInstrumentParam = true;
                    instrumentKey = inst.key;
                    break;
                }
            }

            if (isInstrumentParam && instrumentKey && this.instrumentAutoState[instrumentKey] === false) {
                return; // Bypassed
            }

            const kfs = perf.keyframes.filter(kf => kf.params[path] !== undefined);
            if (kfs.length === 0) return;

            kfs.sort((a, b) => a.timePct - b.timePct);

            let prev = null, next = null;
            for (let i = 0; i < kfs.length; i++) {
                if (kfs[i].timePct <= activePct) {
                    prev = kfs[i];
                }
                if (kfs[i].timePct > activePct && !next) {
                    next = kfs[i];
                }
            }

            let finalVal = 0.0;
            if (!prev && next) {
                finalVal = next.params[path];
            } else if (prev && !next) {
                finalVal = prev.params[path];
            } else if (prev && next) {
                let ratio = (activePct - prev.timePct) / (next.timePct - prev.timePct);
                finalVal = prev.params[path] + ratio * (next.params[path] - prev.params[path]);
            }

            // Route update through StateManager
            this.stateManager.updateParamValue(path, finalVal);
        });
    }

    async toggleInstrumentAuto(key) {
        this.instrumentAutoState[key] = !this.instrumentAutoState[key];
        await this.savePerformancesAndStates();
        this.emit('instrumentAutoStateChanged', { key, state: this.instrumentAutoState[key] });
    }

    async saveActivePerformance(jsonText) {
        try {
            const parsed = JSON.parse(jsonText);
            if (!parsed.name || !parsed.duration || !parsed.keyframes) {
                throw new Error("El JSON debe contener name, duration y keyframes.");
            }

            const isCustom = !BUILTIN_PERFS[this.activePerfKey];
            if (!isCustom) {
                const newKey = 'custom_' + Date.now();
                this.customPerfPresets[newKey] = parsed;
                this.activePerfKey = newKey;
            } else {
                this.customPerfPresets[this.activePerfKey] = parsed;
            }

            await this.savePerformancesAndStates();
            this.emit('presetsReloaded', this.getActivePerformances());
            this.loadSelectedPerformance(this.activePerfKey);
            return { success: true };
        } catch (e) {
            return { success: false, error: e.message };
        }
    }

    async createNewPerformance() {
        const template = {
            name: "Nueva Automatización Custom",
            duration: 60,
            description: "Modulación de 60 segundos creada por el productor.",
            keyframes: [
                { timePct: 0, params: { "/master/bpm": 128, "/kick/vol": 0.8, "/bass/vol": 0.0 } },
                { timePct: 50, params: { "/kick/vol": 0.8, "/bass/vol": 0.7 } },
                { timePct: 100, params: { "/kick/vol": 0.0, "/bass/vol": 0.0 } }
            ]
        };
        const newKey = 'custom_' + Date.now();
        this.customPerfPresets[newKey] = template;
        this.activePerfKey = newKey;

        await this.savePerformancesAndStates();
        this.emit('presetsReloaded', this.getActivePerformances());
        this.loadSelectedPerformance(newKey);
        return newKey;
    }

    async deleteActivePerformance() {
        if (BUILTIN_PERFS[this.activePerfKey]) return;
        delete this.customPerfPresets[this.activePerfKey];
        this.activePerfKey = 'song-5m';
        await this.savePerformancesAndStates();
        this.emit('presetsReloaded', this.getActivePerformances());
        this.loadSelectedPerformance(this.activePerfKey);
    }
}
