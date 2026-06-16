import { Parameter } from '../domain/Parameter.js';

export class StateManager {
    constructor(apiClient, storageRepo) {
        this.apiClient = apiClient;
        this.storageRepo = storageRepo;

        this.parameters = [];
        this.paramMappings = {};
        this.customGrooves = {};
        
        this.activeInstrumentKey = 'bombo';
        this.isMappingMode = false;
        
        // HUD Stats
        this.currentBpm = 140;
        this.cpuLoad = '0.0%';
        this.ramUsage = '0.0 MB';
        this.masterLevelDb = -96;
        this.oscActive = false;
        this.midiActive = false;
        this.audioDevices = [];
        this.hasWebSocketSync = false;

        // UI trigger callbacks (decopuling Presentation from logic)
        this.listeners = {
            paramsChanged: [],
            telemetryChanged: [],
            mappingsChanged: [],
            mixerChanged: [],
            instrumentChanged: [],
            groovesChanged: [],
            triggerMappingModal: []
        };
    }

    on(event, cb) {
        if (!this.listeners[event]) {
            this.listeners[event] = [];
        }
        this.listeners[event].push(cb);
    }

    emit(event, data) {
        if (this.listeners[event]) {
            this.listeners[event].forEach(cb => cb(data));
        }
    }

    async init() {
        // Load custom parameter mappings (server first, local storage backup)
        try {
            const mappings = await this.apiClient.loadMappings();
            if (mappings && typeof mappings === 'object') {
                this.paramMappings = mappings;
                this.storageRepo.saveParamMappings(mappings);
            }
        } catch (e) {
            console.warn("Server mappings offline, loading local storage:", e.message);
            this.paramMappings = this.storageRepo.getParamMappings();
        }

        // Load parameter values
        await this.syncParams();

        this.emit('mappingsChanged', this.paramMappings);
    }

    async syncParams() {
        try {
            const data = await this.apiClient.fetchParams();
            if (data && Array.isArray(data)) {
                this.parameters = data.map(p => new Parameter(p.path, p.value, p.min, p.max, p.label));
                this.emit('paramsChanged', this.parameters);
            }
        } catch (e) {
            // Server offline, ignore or use defaults
        }
    }

    getParameter(path) {
        let resolvedPath = path;
        const hasPath = (p) => this.parameters.some(x => x.path === p);
        if (path === "/kick/dec" && !hasPath("/kick/dec")) resolvedPath = "/kick/decay";
        else if (path === "/kick/decay" && !hasPath("/kick/decay")) resolvedPath = "/kick/dec";
        else if (path === "/kick/sweep" && !hasPath("/kick/sweep")) resolvedPath = "/kick/click";
        else if (path === "/kick/comp_drive" && !hasPath("/kick/comp_drive")) resolvedPath = "/kick/drive";
        else if (path === "/kick/mix" && !hasPath("/kick/mix")) resolvedPath = "/kick/res/mix";
        else if (path === "/kick/tune" && !hasPath("/kick/tune")) resolvedPath = "/kick/pitch";
        else if (path === "/kick/comp_thresh" && !hasPath("/kick/comp_thresh")) resolvedPath = "/kick/lim/ceiling";
        return this.parameters.find(p => p.path === resolvedPath);
    }

    async updateParamValue(path, rawValue) {
        const param = this.getParameter(path);
        if (!param) return;

        if (this.isMappingMode) {
            // Block setting Faust DSP value, launch presentation mapping modal
            this.emit('triggerMappingModal', { path, min: param.min, max: param.max });
            return;
        }

        // Apply mapping calculations
        const effValue = param.getEffectiveValue(rawValue, this.paramMappings);
        param.value = effValue;

        try {
            await this.apiClient.setParam(path, effValue);
        } catch (e) {
            console.error('Error setting parameter:', e);
        }

        this.emit('paramsChanged', this.parameters);
    }

    async saveMapping(path, min, max) {
        this.paramMappings[path] = { min: parseFloat(min), max: parseFloat(max) };
        this.storageRepo.saveParamMappings(this.paramMappings);
        try {
            await this.apiClient.saveMappings(this.paramMappings);
        } catch (e) {
            console.error('Error saving mapping to server:', e);
        }
        this.emit('mappingsChanged', this.paramMappings);
        this.emit('paramsChanged', this.parameters);
    }

    setActiveInstrument(key) {
        this.activeInstrumentKey = key;
        this.emit('instrumentChanged', key);
    }

    toggleMappingMode() {
        this.isMappingMode = !this.isMappingMode;
        return this.isMappingMode;
    }
}
