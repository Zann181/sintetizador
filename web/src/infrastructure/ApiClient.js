export class ApiClient {
    constructor() {
        this.apiBase = window.location.protocol === 'file:' ? 'http://localhost:8000' : '';
    }

    async fetchParams() {
        const response = await fetch(this.apiBase + '/api/params');
        if (!response.ok) throw new Error('API fetchParams error');
        return await response.json();
    }

    async fetchStatus() {
        const response = await fetch(this.apiBase + '/api/status');
        if (!response.ok) throw new Error('API fetchStatus error');
        return await response.json();
    }

    async setParam(path, value) {
        const response = await fetch(this.apiBase + `/api/set?path=${encodeURIComponent(path)}&value=${parseFloat(value)}`);
        if (!response.ok) throw new Error('API setParam error');
        return await response.text();
    }

    async setAudioDevice(id) {
        const response = await fetch(this.apiBase + `/api/audio/set?id=${encodeURIComponent(id)}`);
        if (!response.ok) throw new Error('API setAudioDevice error');
        return await response.text();
    }

    async loadMappings() {
        const response = await fetch(this.apiBase + '/api/mappings/load');
        if (!response.ok) throw new Error('API loadMappings error');
        return await response.json();
    }

    async saveMappings(mappingsObj) {
        const jsonStr = JSON.stringify(mappingsObj);
        const response = await fetch(this.apiBase + `/api/mappings/save?data=${encodeURIComponent(jsonStr)}`);
        if (!response.ok) throw new Error('API saveMappings error');
        return await response.text();
    }

    async loadPerformances() {
        const response = await fetch(this.apiBase + '/api/performances/load');
        if (!response.ok) throw new Error('API loadPerformances error');
        return await response.json();
    }

    async savePerformances(perfsObj) {
        const jsonStr = JSON.stringify(perfsObj);
        const response = await fetch(this.apiBase + `/api/performances/save?data=${encodeURIComponent(jsonStr)}`);
        if (!response.ok) throw new Error('API savePerformances error');
        return await response.text();
    }

    async loadGrooves() {
        const response = await fetch(this.apiBase + '/api/grooves/load');
        if (!response.ok) throw new Error('API loadGrooves error');
        return await response.json();
    }

    async saveGrooves(groovesObj) {
        const jsonStr = JSON.stringify(groovesObj);
        const response = await fetch(this.apiBase + `/api/grooves/save?data=${encodeURIComponent(jsonStr)}`);
        if (!response.ok) throw new Error('API saveGrooves error');
        return await response.text();
    }
}
