import { INSTRUMENTS } from '../../domain/Sequencer.js';
import { Parameter } from '../../domain/Parameter.js';

export class MixerConsole {
    constructor(stateManager, sequencerService, performerService, knobDragHandler) {
        this.stateManager = stateManager;
        this.sequencerService = sequencerService;
        this.performerService = performerService;
        this.knobDragHandler = knobDragHandler;
    }

    render() {
        const container = document.getElementById('master-mix-console');
        if (!container || this.stateManager.parameters.length === 0) return;

        const currentActiveKey = this.stateManager.activeInstrumentKey;

        let channelsHtml = '';
        INSTRUMENTS.forEach(inst => {
            const clkParam = this.stateManager.getParameter(inst.prefix + 'reloj') || new Parameter(inst.prefix + 'reloj', 1.0, 0.25, 4.0, 'reloj');
            const volParam = this.stateManager.getParameter(inst.prefix + 'vol') || new Parameter(inst.prefix + 'vol', 0.8, 0.0, 1.0, 'vol');
            
            const decayKey = inst.key === 'caja' ? 'dec_resorte' : (inst.key === 'bombo' ? (this.stateManager.getParameter('/kick/decay') ? 'decay' : 'dec') : (inst.key === 'bajo' ? 'dec' : 'dec'));
            const decayParam = this.stateManager.getParameter(inst.prefix + decayKey) || new Parameter(inst.prefix + decayKey, 0.2, 0.01, 2.0, decayKey);
            const decayName = decayParam.path.split('/').pop().toUpperCase();
            
            const activeStripClass = inst.key === currentActiveKey ? 'active-strip' : '';
            const isAutoActive = this.performerService.instrumentAutoState[inst.key] !== false;

            const accentVal = this.stateManager.getParameter(inst.prefix + 'accent')?.value || 0.5;
            const swingVal = this.stateManager.getParameter(inst.prefix + 'swing')?.value || 0.0;
            const currentNotaVal = this.stateManager.getParameter(inst.prefix + 'nota')?.value || 36;

            channelsHtml += `
                <div class="mixer-channel-strip ${activeStripClass}" id="chan-${inst.key}">
                    <div class="chan-title-row" onclick="window.onMixerTabSelect('${inst.key}')" title="Ver Síntesis Avanzada de ${inst.name.toUpperCase()}">
                        <span class="chan-title">${inst.name.toUpperCase()}</span>
                        <div class="toggle-switch-wrapper" onclick="window.onMixerToggleAuto('${inst.key}', event)" 
                             title="${isAutoActive ? 'Auto Activado' : 'Bypass (Manual)'}">
                            <div class="toggle-switch ${isAutoActive ? 'active' : ''}">
                                <div class="toggle-handle"></div>
                            </div>
                            <span class="toggle-lbl lbl-auto ${isAutoActive ? 'active-lbl' : ''}">AUTO</span>
                        </div>
                    </div>

                    <div class="mixer-widget-box">
                        <span class="mixer-lbl">Groove</span>
                        <select class="mixer-select" id="select-inst-master-groove-${inst.key}" onchange="window.onMixerLocalGroove('${inst.key}', this.value)">
                            <option value="">-- Groove --</option>
                            ${Object.keys(this.sequencerService.customGrooves).map(k => `<option value="${k}">${k}</option>`).join('')}
                        </select>
                    </div>
                    
                    <div class="mixer-widget-box">
                        <span class="mixer-lbl">Sync Reloj</span>
                        <div class="clk-btn-group-mini">
                            ${[0.25, 0.5, 1.0, 2.0, 4.0].map(val => {
                                const lbl = val === 0.25 ? '÷4' : (val === 0.5 ? '÷2' : (val === 1.0 ? 'x1' : (val === 2.0 ? 'x2' : 'x4')));
                                const activeClass = Math.abs(clkParam.value - val) < 0.05 ? 'active' : '';
                                return `<button class="clk-mini-btn ${activeClass}" onclick="window.onMixerUpdateParam('${clkParam.path}', ${val})">${lbl}</button>`;
                            }).join('')}
                        </div>
                    </div>

                    <div class="mixer-knob-row">
                        <div class="knob-widget-mini">
                            <span class="mixer-lbl">Accent</span>
                            <div class="knob-outer mini-knob" id="outer-inst-master-accent-${inst.key}"
                                 data-path="${inst.prefix}accent" data-min="0" data-max="1" data-value="${accentVal}">
                                 <svg class="knob-svg" viewBox="0 0 100 100">
                                     <circle cx="50" cy="50" r="40" stroke="#121217" stroke-width="10" fill="none"/>
                                     <circle class="knob-active-ring" cx="50" cy="50" r="40"
                                             stroke-width="10" fill="none" stroke-linecap="round"/>
                                 </svg>
                                 <div class="knob-dial dial-mini"><div class="knob-pointer pointer-mini"></div></div>
                             </div>
                             <span class="mixer-val-mini" id="display-inst-master-accent-${inst.key}">${accentVal.toFixed(2)}</span>
                        </div>

                        <div class="knob-widget-mini">
                            <span class="mixer-lbl">Swing</span>
                            <div class="knob-outer mini-knob" id="outer-inst-master-swing-${inst.key}"
                                 data-path="${inst.prefix}swing" data-min="0" data-max="75" data-value="${swingVal}">
                                 <svg class="knob-svg" viewBox="0 0 100 100">
                                     <circle cx="50" cy="50" r="40" stroke="#121217" stroke-width="10" fill="none"/>
                                     <circle class="knob-active-ring" cx="50" cy="50" r="40"
                                             stroke-width="10" fill="none" stroke-linecap="round"/>
                                 </svg>
                                 <div class="knob-dial dial-mini"><div class="knob-pointer pointer-mini"></div></div>
                             </div>
                             <span class="mixer-val-mini" id="display-inst-master-swing-${inst.key}">${swingVal.toFixed(2)}</span>
                        </div>
                    </div>

                    <div class="mixer-widget-box">
                        <span class="mixer-lbl">Tonalidad</span>
                        <select class="mixer-select" id="select-inst-master-nota-${inst.key}" onchange="window.onMixerUpdateParam('${inst.prefix}nota', this.value)">
                            <option value="36" ${currentNotaVal == 36 ? 'selected' : ''}>C (Do)</option>
                            <option value="37" ${currentNotaVal == 37 ? 'selected' : ''}>C# (Do#)</option>
                            <option value="38" ${currentNotaVal == 38 ? 'selected' : ''}>D (Re)</option>
                            <option value="39" ${currentNotaVal == 39 ? 'selected' : ''}>D# (Re#)</option>
                            <option value="40" ${currentNotaVal == 40 ? 'selected' : ''}>E (Mi)</option>
                            <option value="41" ${currentNotaVal == 41 ? 'selected' : ''}>F (Fa)</option>
                            <option value="42" ${currentNotaVal == 42 ? 'selected' : ''}>F# (Fa#)</option>
                            <option value="43" ${currentNotaVal == 43 ? 'selected' : ''}>G (Sol)</option>
                            <option value="44" ${currentNotaVal == 44 ? 'selected' : ''}>G# (Sol#)</option>
                            <option value="45" ${currentNotaVal == 45 ? 'selected' : ''}>A (La)</option>
                            <option value="46" ${currentNotaVal == 46 ? 'selected' : ''}>A# (La#)</option>
                            <option value="47" ${currentNotaVal == 47 ? 'selected' : ''}>B (Si)</option>
                        </select>
                    </div>

                    <!-- Decay Slider (Horizontal) -->
                    <div class="mixer-widget-box">
                        <div class="mixer-lbl-row">
                            <span class="mixer-lbl">${decayName.substring(0, 8)}</span>
                            <span class="mixer-val-txt" id="display-mixer-decay-${inst.key}">${decayParam.value.toFixed(2)}</span>
                        </div>
                        <input type="range" class="mixer-slider-h" id="slider-mixer-decay-${inst.key}"
                               min="${decayParam.min}" max="${decayParam.max}" step="0.01" value="${decayParam.getSliderValue(decayParam.value, this.stateManager.paramMappings)}"
                               oninput="window.onMixerUpdateParam('${decayParam.path}', this.value, 'display-mixer-decay-${inst.key}')">
                    </div>

                    <!-- Vertical Volume Fader -->
                    <div class="fader-widget-vertical">
                        <div class="fader-lbl-row">
                            <span class="mixer-lbl">VOLUME</span>
                            <span class="fader-val-txt" id="display-mixer-vol-${inst.key}">${volParam.value.toFixed(2)}</span>
                        </div>
                        <div class="fader-track-container">
                            <input type="range" class="fader-slider-v" id="slider-mixer-vol-${inst.key}"
                                   min="${volParam.min}" max="${volParam.max}" step="0.01" value="${volParam.getSliderValue(volParam.value, this.stateManager.paramMappings)}"
                                   oninput="window.onMixerUpdateParam('${volParam.path}', this.value, 'display-mixer-vol-${inst.key}')">
                        </div>
                    </div>
                </div>
            `;
        });

        container.innerHTML = `<div class="mixer-channels-grid">${channelsHtml}</div>`;

        // Bind knob mouse/touch drag events
        INSTRUMENTS.forEach(inst => {
            ['accent', 'swing'].forEach(k => {
                const ko = document.getElementById(`outer-inst-master-${k}-${inst.key}`);
                if (ko) {
                    ko.addEventListener('mousedown', (e) => this.knobDragHandler.startKnobDrag(e, ko));
                    ko.addEventListener('touchstart', (e) => this.knobDragHandler.startKnobDrag(e, ko), { passive: false });
                    this.knobDragHandler.updateKnobGraphics(ko);
                }
            });
        });

        this.syncDropdowns();
    }

    syncDropdowns() {
        INSTRUMENTS.forEach(inst => {
            this.syncInstrumentGrooveSelector(inst.key);
        });
    }

    syncInstrumentGrooveSelector(instKey) {
        const currentSteps = [];
        let hasParams = false;
        const inst = INSTRUMENTS.find(i => i.key === instKey);
        if (!inst) return;

        for (let i = 0; i < 16; i++) {
            const p = this.stateManager.getParameter(`${inst.prefix}step${i}`);
            if (p) {
                hasParams = true;
                currentSteps.push(p.value > 0.0 ? 1 : 0);
            } else {
                currentSteps.push(0);
            }
        }

        if (!hasParams) {
            for (let i = 0; i < 16; i++) {
                const padEl = document.getElementById(`big-pad-step-${instKey}-${i}`);
                currentSteps[i] = (padEl && padEl.classList.contains('active')) ? 1 : 0;
            }
        }

        let matchingName = "";
        for (const [name, groove] of Object.entries(this.sequencerService.customGrooves)) {
            const grooveSteps = groove[instKey];
            if (grooveSteps && grooveSteps.length === 16) {
                let match = true;
                for (let i = 0; i < 16; i++) {
                    if (currentSteps[i] !== (grooveSteps[i] ? 1 : 0)) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    matchingName = name;
                    break;
                }
            }
        }

        const selectEl = document.getElementById(`select-inst-master-groove-${instKey}`);
        if (selectEl && selectEl.value !== matchingName) {
            selectEl.value = matchingName;
        }

        const selectPadEl = document.getElementById(`pad-groove-sel-${instKey}`);
        if (selectPadEl && selectPadEl.value !== matchingName) {
            selectPadEl.value = matchingName;
        }
    }

    updateValues() {
        if (this.stateManager.parameters.length === 0) return;
        
        INSTRUMENTS.forEach(inst => {
            // Accent knob
            const accentParam = this.stateManager.getParameter(inst.prefix + 'accent');
            if (accentParam) {
                const outer = document.getElementById(`outer-inst-master-accent-${inst.key}`);
                if (outer && this.knobDragHandler.activeKnob !== outer) {
                    let rawVal = accentParam.getSliderValue(accentParam.value, this.stateManager.paramMappings);
                    outer.setAttribute('data-value', rawVal);
                    this.knobDragHandler.updateKnobGraphics(outer);
                }
                const disp = document.getElementById(`display-inst-master-accent-${inst.key}`);
                if (disp) disp.innerText = accentParam.value.toFixed(2);
            }

            // Swing knob
            const swingParam = this.stateManager.getParameter(inst.prefix + 'swing');
            if (swingParam) {
                const outer = document.getElementById(`outer-inst-master-swing-${inst.key}`);
                if (outer && this.knobDragHandler.activeKnob !== outer) {
                    let rawVal = swingParam.getSliderValue(swingParam.value, this.stateManager.paramMappings);
                    outer.setAttribute('data-value', rawVal);
                    this.knobDragHandler.updateKnobGraphics(outer);
                }
                const disp = document.getElementById(`display-inst-master-swing-${inst.key}`);
                if (disp) disp.innerText = swingParam.value.toFixed(2);
            }

            // Nota select
            const notaParam = this.stateManager.getParameter(inst.prefix + 'nota');
            if (notaParam) {
                const sel = document.getElementById(`select-inst-master-nota-${inst.key}`);
                if (sel && document.activeElement !== sel) {
                    sel.value = Math.round(notaParam.value);
                }
            }

            // Volume fader
            const volParam = this.stateManager.getParameter(inst.prefix + 'vol');
            if (volParam) {
                const disp = document.getElementById(`display-mixer-vol-${inst.key}`);
                if (disp) disp.innerText = volParam.value.toFixed(2);
                const sl = document.getElementById(`slider-mixer-vol-${inst.key}`);
                if (sl && document.activeElement !== sl) {
                    let rawVal = volParam.getSliderValue(volParam.value, this.stateManager.paramMappings);
                    sl.value = rawVal;
                }
            }

            // Decay slider
            const decayKey = inst.key === 'caja' ? 'dec_resorte' : (inst.key === 'bombo' ? (this.stateManager.getParameter('/kick/decay') ? 'decay' : 'dec') : (inst.key === 'bajo' ? 'dec' : 'dec'));
            const decayParam = this.stateManager.getParameter(inst.prefix + decayKey);
            if (decayParam) {
                const disp = document.getElementById(`display-mixer-decay-${inst.key}`);
                if (disp) disp.innerText = decayParam.value.toFixed(2);
                const sl = document.getElementById(`slider-mixer-decay-${inst.key}`);
                if (sl && document.activeElement !== sl) {
                    let rawVal = decayParam.getSliderValue(decayParam.value, this.stateManager.paramMappings);
                    sl.value = rawVal;
                }
            }

            // Clock sync buttons
            const clkParam = this.stateManager.getParameter(inst.prefix + 'reloj');
            if (clkParam) {
                const buttons = document.querySelectorAll(`button[onclick*="${clkParam.path}"]`);
                buttons.forEach(btn => {
                    if (btn.getAttribute('onclick').includes(clkParam.value.toString())) {
                        btn.classList.add('active');
                    } else {
                        btn.classList.remove('active');
                    }
                });
            }

            // Groove selector sync
            this.syncInstrumentGrooveSelector(inst.key);
        });
    }
}
