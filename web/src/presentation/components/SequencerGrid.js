import { INSTRUMENTS } from '../../domain/Sequencer.js';

export class SequencerGrid {
    constructor(stateManager, sequencerService) {
        this.stateManager = stateManager;
        this.sequencerService = sequencerService;
    }

    render() {
        const container = document.getElementById('pad-grid-container');
        if (!container) return;

        const customGrooves = this.sequencerService.customGrooves;
        const grooveOpts = Object.keys(customGrooves)
            .map(k => `<option value="${k}">${k}</option>`).join('');

        let html = '';
        INSTRUMENTS.forEach(inst => {
            html += `
                <div class="pad-row-wrap">
                    <div class="pad-inst-lbl">${inst.name.toUpperCase()}</div>
                    <select class="pad-inst-groove-sel" id="pad-groove-sel-${inst.key}"
                            onchange="window.onSequencerLocalGroove('${inst.key}', this.value)">
                        <option value="">-- --</option>
                        ${grooveOpts}
                    </select>
                    <div class="pad-steps-row">
                        ${Array.from({ length: 16 }).map((_, i) => {
                            const isParam = this.stateManager.getParameter(`${inst.prefix}step${i}`);
                            const isActive = isParam && isParam.value > 0.0;
                            const groupSepClass = (i === 4 || i === 8 || i === 12) ? ' beat-4-sep' : '';
                            
                            return `<div id="big-pad-step-${inst.key}-${i}"
                                        class="seq-pad${groupSepClass}${isActive ? ' active' : ''}"
                                        onclick="window.onSequencerToggleStep('${inst.key}', ${i})"
                                        title="${inst.name} – Paso ${i + 1}">
                                        <span class="step-num">${i + 1}</span>
                                    </div>`;
                        }).join('')}
                    </div>
                </div>`;
        });

        container.innerHTML = html;

        // Sync dropdown selectors with matching grooves
        INSTRUMENTS.forEach(inst => {
            this.syncLocalDropdown(inst.key);
        });

        this.syncGlobalDropdown();
    }

    syncLocalDropdown(instKey) {
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

        const iselPad = document.getElementById(`pad-groove-sel-${instKey}`);
        if (iselPad && iselPad.value !== matchingName) {
            iselPad.value = matchingName;
        }

        const iselMixer = document.getElementById(`select-inst-master-groove-${instKey}`);
        if (iselMixer && iselMixer.value !== matchingName) {
            iselMixer.value = matchingName;
        }
    }

    syncGlobalDropdown() {
        let commonGroove = null;
        let matchAll = true;

        for (const inst of INSTRUMENTS) {
            const iselPad = document.getElementById(`pad-groove-sel-${inst.key}`);
            const iselMixer = document.getElementById(`select-inst-master-groove-${inst.key}`);
            const val = iselPad ? iselPad.value : (iselMixer ? iselMixer.value : "");
            
            if (commonGroove === null) {
                commonGroove = val;
            } else if (commonGroove !== val) {
                matchAll = false;
                break;
            }
        }

        const gsel = document.getElementById('global-groove-select');
        if (gsel) {
            gsel.value = matchAll ? (commonGroove || "") : "";
        }
    }

    updateStepPadDOM(instKey, stepIdx, value) {
        ['big-pad-step', 'pad-step'].forEach(pfx => {
            const el = document.getElementById(`${pfx}-${instKey}-${stepIdx}`);
            if (el) el.classList.toggle('active', value > 0.0);
        });
    }

    updatePlayhead(step) {
        // Remove playhead highlight class from all pads
        document.querySelectorAll('.seq-pad.playhead').forEach(el => el.classList.remove('playhead'));
        
        if (step === -1) return;

        // Highlight playhead step in all instrument grid rows
        INSTRUMENTS.forEach(inst => {
            const el = document.getElementById(`big-pad-step-${inst.key}-${step}`);
            if (el) el.classList.add('playhead');
        });
    }
}
