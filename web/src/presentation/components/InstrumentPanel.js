import { INSTRUMENTS } from '../../domain/Sequencer.js';

export class InstrumentPanel {
    constructor(stateManager, knobDragHandler) {
        this.stateManager = stateManager;
        this.knobDragHandler = knobDragHandler;
    }

    render() {
        const container = document.getElementById('active-instrument-panel');
        if (!container || this.stateManager.parameters.length === 0) return;

        const currentActiveKey = this.stateManager.activeInstrumentKey;
        const inst = INSTRUMENTS.find(i => i.key === currentActiveKey);
        if (!inst) return;

        const allParams = this.stateManager.parameters.filter(p => p.path.startsWith(inst.prefix));
        
        // Excluded keys which are already mapped inside the mixer channel strip console
        const excludedKeys = ['vol', 'volume', 'decay', 'dec', 'dec_cuerpo', 'dec_resorte', 'ataque', 'attack', 'release', 'reloj', 'accent', 'swing', 'nota', 'nota_base', 'step'];
        const synthParams = allParams.filter(p => {
            const pk = p.path.split('/').pop().toLowerCase();
            return !excludedKeys.includes(pk) && !pk.startsWith('step');
        });

        container.innerHTML = `
            <!-- VERTICAL SYNTH PANEL (ADVANCED SYNTHESIS ONLY) -->
            <div class="active-synth-section">
                <div class="panel-header" style="font-size:0.7rem; border:none; margin:0; padding:0; color:var(--neutral-white) !important;">
                    CONTROLES DE SÍNTESIS AVANZADA: ${inst.name.toUpperCase()}
                </div>
                <div class="knobs-grid" id="synth-knobs-${inst.key}"></div>
                <div id="synth-sliders-${inst.key}" style="display:flex; flex-direction:column; gap:10px;"></div>
                <div id="synth-menus-${inst.key}" style="display:flex; flex-direction:column; gap:10px;"></div>
            </div>
        `;

        const knobGrid = document.getElementById(`synth-knobs-${inst.key}`);
        const sliderContainer = document.getElementById(`synth-sliders-${inst.key}`);
        const menuContainer = document.getElementById(`synth-menus-${inst.key}`);

        synthParams.forEach(p => {
            const parsed = this.parseStyle(p);
            const paramKey = p.path.split('/').pop();
            const cleanName = paramKey.replace(/_/g, ' ');
            const elemId = `synth-${inst.key}-${paramKey}`;

            if (parsed.style === 'knob') {
                const w = document.createElement('div');
                w.id = elemId;
                w.className = 'knob-widget';
                w.innerHTML = `
                    <span class="knob-label" title="${cleanName}">${cleanName}</span>
                    <div class="knob-outer" id="outer-${elemId}" data-path="${p.path}" data-min="${p.min}" data-max="${p.max}" data-value="${p.value}">
                        <svg class="knob-svg" viewBox="0 0 100 100">
                            <circle cx="50" cy="50" r="40" stroke="#121217" stroke-width="8" fill="none"/>
                            <circle class="knob-active-ring" cx="50" cy="50" r="40" stroke-width="8" fill="none" stroke-linecap="round"/>
                        </svg>
                        <div class="knob-dial"><div class="knob-pointer"></div></div>
                    </div>
                    <span class="knob-value-display" id="disp-${elemId}">${p.value.toFixed(2)}</span>
                `;
                knobGrid.appendChild(w);
                
                const ko = w.querySelector('.knob-outer');
                ko.addEventListener('mousedown', (e) => this.knobDragHandler.startKnobDrag(e, ko));
                ko.addEventListener('touchstart', (e) => this.knobDragHandler.startKnobDrag(e, ko), { passive: false });
                this.knobDragHandler.updateKnobGraphics(ko);
            
            } else if (parsed.style === 'menu') {
                const w = document.createElement('div');
                w.id = elemId;
                w.className = 'select-widget';
                const opts = parsed.menuItems.map(o => `<option value="${o.value}">${o.text}</option>`).join('');
                w.innerHTML = `
                    <span class="select-label">${cleanName}</span>
                    <select id="sel-${elemId}" onchange="window.onMixerUpdateParam('${p.path}', this.value)">${opts}</select>
                `;
                menuContainer.appendChild(w);
                const sel = document.getElementById(`sel-${elemId}`);
                if (sel) sel.value = p.value;
            
            } else {
                const w = document.createElement('div');
                w.id = elemId;
                w.className = 'slider-widget';
                w.innerHTML = `
                    <div class="slider-label-row">
                        <span>${cleanName}</span>
                        <span class="slider-val" id="disp-${elemId}">${p.value.toFixed(2)}</span>
                    </div>
                    <div class="slider-container">
                        <input type="range" id="inp-${elemId}" min="${p.min}" max="${p.max}" step="0.001" value="${p.getSliderValue(p.value, this.stateManager.paramMappings)}" 
                               oninput="window.onMixerUpdateParam('${p.path}', this.value, 'disp-${elemId}')">
                    </div>
                `;
                sliderContainer.appendChild(w);
            }
        });
    }

    updateValues() {
        if (this.stateManager.parameters.length === 0) return;
        const instKey = this.stateManager.activeInstrumentKey;
        const inst = INSTRUMENTS.find(i => i.key === instKey);
        if (!inst) return;

        const allParams = this.stateManager.parameters.filter(p => p.path.startsWith(inst.prefix));
        const excludedKeys = ['vol', 'volume', 'decay', 'dec', 'dec_cuerpo', 'dec_resorte', 'ataque', 'attack', 'release', 'reloj', 'accent', 'swing', 'nota', 'nota_base', 'step'];
        const synthParams = allParams.filter(p => {
            const pk = p.path.split('/').pop().toLowerCase();
            return !excludedKeys.includes(pk) && !pk.startsWith('step');
        });

        synthParams.forEach(p => {
            const parsed = this.parseStyle(p);
            const paramKey = p.path.split('/').pop();
            const elemId = `synth-${instKey}-${paramKey}`;

            if (parsed.style === 'knob') {
                const outer = document.getElementById(`outer-${elemId}`);
                if (outer && this.knobDragHandler.activeKnob !== outer) {
                    const rawVal = p.getSliderValue(p.value, this.stateManager.paramMappings);
                    outer.setAttribute('data-value', rawVal);
                    this.knobDragHandler.updateKnobGraphics(outer);
                }
                const disp = document.getElementById(`disp-${elemId}`);
                if (disp) disp.innerText = p.value.toFixed(2);
            } else if (parsed.style === 'menu') {
                const sel = document.getElementById(`sel-${elemId}`);
                if (sel && document.activeElement !== sel) {
                    sel.value = p.value;
                }
            } else {
                const inp = document.getElementById(`inp-${elemId}`);
                if (inp && document.activeElement !== inp) {
                    const rawVal = p.getSliderValue(p.value, this.stateManager.paramMappings);
                    inp.value = rawVal;
                }
                const disp = document.getElementById(`disp-${elemId}`);
                if (disp) disp.innerText = p.value.toFixed(2);
            }
        });
    }

    parseStyle(p) {
        const label = p.label || '';
        let style = 'slider';
        const menuItems = [];
        
        if (label.includes('style:knob')) {
            style = 'knob';
        } else if (label.includes('style:menu')) {
            style = 'menu';
            const m = label.match(/style:menu\s*\{([^}]+)\}/);
            if (m && m[1]) {
                m[1].split(';').forEach(item => {
                    const parts = item.split(':');
                    if (parts.length === 2) {
                        const text = parts[0].trim().replace(/['"]/g, '');
                        const val = parseFloat(parts[1].trim());
                        if (!isNaN(val)) menuItems.push({ text, value: val });
                    }
                });
            }
        }
        return { style, menuItems };
    }
}
