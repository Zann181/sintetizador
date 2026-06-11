import { BUILTIN_PERFS } from '../../domain/Performance.js';

export class PerformerUi {
    constructor(stateManager, performerService) {
        this.stateManager = stateManager;
        this.performerService = performerService;
    }

    init() {
        // Bind service events to UI updates
        this.performerService.on('presetsReloaded', (presets) => this.refreshPresetSelector(presets));
        
        this.performerService.on('activePresetChanged', ({ key, preset }) => {
            const descEl = document.getElementById('perf-description-text');
            if (descEl) descEl.innerText = preset.description || "";
            
            const editorEl = document.getElementById('perf-json-editor');
            if (editorEl) editorEl.value = JSON.stringify(preset, null, 2);

            const isCustom = !BUILTIN_PERFS[key];
            const delBtn = document.getElementById('btn-perf-delete');
            if (delBtn) delBtn.style.display = isCustom ? 'block' : 'none';

            if (!this.performerService.perfActive) {
                const timerEl = document.getElementById('perf-timer');
                if (timerEl) timerEl.innerText = `00:00 / ${this.formatTime(preset.duration)}`;
                
                const progBar = document.getElementById('perf-progress-bar');
                if (progBar) progBar.style.width = '0%';
                
                const phaseEl = document.getElementById('perf-phase-name');
                if (phaseEl) phaseEl.innerText = "Fase: Esperando...";
            }
        });

        this.performerService.on('statusChanged', ({ active, statusText, color }) => {
            const statusEl = document.getElementById('perf-status');
            if (statusEl) {
                statusEl.innerText = statusText;
                statusEl.style.color = color;
            }
            const playBtn = document.getElementById('btn-perf-play');
            if (playBtn) {
                playBtn.classList.toggle('btn-active', active);
            }
        });

        this.performerService.on('timeUpdated', ({ currentTime, duration, percentage }) => {
            const timerEl = document.getElementById('perf-timer');
            if (timerEl) timerEl.innerText = `${this.formatTime(currentTime)} / ${this.formatTime(duration)}`;
            
            const progBar = document.getElementById('perf-progress-bar');
            if (progBar) progBar.style.width = `${percentage}%`;

            // Calculate Phase Name visually
            let phaseName = "1. Inicio";
            const key = this.performerService.activePerfKey;
            if (key === 'song-5m') {
                if (percentage < 15) phaseName = "1. Suave Inicio";
                else if (percentage < 35) phaseName = "2. Ritmo & Base";
                else if (percentage < 55) phaseName = "3. Groove Completo";
                else if (percentage < 75) phaseName = "4. Descanso/Relax";
                else if (percentage < 90) phaseName = "5. CLÍMAX TECNOLÓGICO";
                else phaseName = "6. Fin & Fundido";
            } else {
                phaseName = `Fase Activa: ${Math.round(percentage)}%`;
            }
            const phaseEl = document.getElementById('perf-phase-name');
            if (phaseEl) phaseEl.innerText = phaseName;
        });
    }

    toggleDrawer() {
        const drawer = document.querySelector('.performer-drawer');
        if (!drawer) return;
        
        drawer.classList.toggle('open');
        const btn = document.getElementById('btn-performer-toggle');
        if (btn) btn.classList.toggle('btn-active', drawer.classList.contains('open'));

        // Close settings if open
        if (drawer.classList.contains('open')) {
            const settingsDrawer = document.querySelector('.right-col');
            if (settingsDrawer && settingsDrawer.classList.contains('open')) {
                window.toggleSettingsDrawer(); // Use global binding or direct query
            }
        }
    }

    refreshPresetSelector(presets) {
        const sel = document.getElementById('performer-preset-select');
        if (!sel) return;
        
        sel.innerHTML = Object.keys(presets).map(key => {
            const p = presets[key];
            const type = BUILTIN_PERFS[key] ? '[PRESET]' : '[CUSTOM]';
            return `<option value="${key}">${type} ${p.name}</option>`;
        }).join('');
        
        sel.value = this.performerService.activePerfKey;
    }

    formatTime(secs) {
        const m = Math.floor(secs / 60).toString().padStart(2, '0');
        const s = Math.floor(secs % 60).toString().padStart(2, '0');
        return `${m}:${s}`;
    }
}
