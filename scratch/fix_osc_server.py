import os

file_path = r"c:\Users\Motaz\Music\Nueva carpeta\sintetizador\osc\OscServer.cpp"

with open(file_path, "r", encoding="utf-8") as f:
    content = f.read()

# Buscamos la función renderMixerConsole
start_idx = content.find("function renderMixerConsole()")
if start_idx == -1:
    print("No se encontró function renderMixerConsole()")
    exit(1)

# Encontramos la llave de apertura
open_bracket_idx = content.find("{", start_idx)
if open_bracket_idx == -1:
    print("No se encontró {")
    exit(1)

# Contamos los brackets para encontrar el cierre exacto de la función
bracket_count = 1
end_idx = open_bracket_idx + 1
while bracket_count > 0 and end_idx < len(content):
    if content[end_idx] == '{':
        bracket_count += 1
    elif content[end_idx] == '}':
        bracket_count -= 1
    end_idx += 1

if bracket_count > 0:
    print("No se encontró el cierre de la función")
    exit(1)

# El bloque a reemplazar
original_block = content[start_idx:end_idx]

# La nueva implementación correcta y limpia
new_implementation = """function renderMixerConsole() {
            const container = document.getElementById('master-mix-console');
            if (!container || parameters.length === 0) return;
            
            container.innerHTML = `
                <div class="mixer-header">CONSOLA DE MEZCLA MAESTRA (MASTER MIX)</div>
                <div class="mixer-channels-grid">
                    ${INSTRUMENTS.map(inst => {
                        const clkParam = parameters.find(p => p.path === inst.prefix + 'reloj') || { value: 1.0 };
                        const volParam = parameters.find(p => p.path === inst.prefix + 'vol') || { value: 0.8, min: 0, max: 1 };
                        
                        const decayKey = inst.key === 'snare' ? 'dec_resorte' : (inst.key === 'bombo' ? 'dec' : (inst.key === 'bajo' ? 'dec' : 'dec'));
                        const decayParam = parameters.find(p => p.path === inst.prefix + decayKey) || parameters.find(p => p.path.endsWith('/dec')) || { value: 0.2, min: 0.01, max: 2.0 };
                        const decayName = decayParam ? decayParam.path.split('/').pop().toUpperCase() : 'DECAY';
                        const activeStripClass = inst.key === activeInstrumentKey ? 'active-strip' : '';

                        return `
                            <div class="mixer-channel-strip ${activeStripClass}" id="chan-${inst.key}">
                                <div class="chan-title-row" onclick="setActiveInstrument('${inst.key}')" style="cursor:pointer; display:flex; justify-content:space-between; align-items:center;" title="Ver Síntesis Avanzada de ${inst.name.toUpperCase()}">
                                    <span class="chan-title">${inst.name.toUpperCase()}</span>
                                    <div class="toggle-switch-wrapper" onclick="toggleInstrumentAuto('${inst.key}', event)" 
                                         title="${instrumentAutoState[inst.key] !== false ? 'Auto Activado' : 'Bypass (Manual)'}">
                                        <span class="toggle-lbl lbl-bypass ${instrumentAutoState[inst.key] === false ? 'active-lbl' : ''}">BYPASS</span>
                                        <div class="toggle-switch ${instrumentAutoState[inst.key] !== false ? 'active' : ''}">
                                            <div class="toggle-handle"></div>
                                        </div>
                                        <span class="toggle-lbl lbl-auto ${instrumentAutoState[inst.key] !== false ? 'active-lbl' : ''}">AUTO</span>
                                    </div>
                                </div>
                                
                                <!-- Reloj Multiplier -->
                                <div class="mixer-widget-box">
                                    <span class="mixer-lbl">Sync Reloj</span>
                                    <div class="clk-btn-group-mini">
                                        ${[0.25, 0.5, 1.0, 2.0, 4.0].map(val => {
                                            const lbl = val === 0.25 ? '÷4' : (val === 0.5 ? '÷2' : (val === 1.0 ? 'x1' : (val === 2.0 ? 'x2' : 'x4')));
                                            const active = Math.abs(clkParam.value - val) < 0.05 ? 'active' : '';
                                            return `<button class="clk-mini-btn ${active}" onclick="updateParam('${clkParam.path || inst.prefix + 'reloj'}', ${val})">${lbl}</button>`;
                                        }).join('')}
                                    </div>
                                </div>

                                <!-- Accent & Swing Knobs (DECOUPLED LOCAL CHANNELS) -->
                                <div class="mixer-knob-row">
                                    <div class="knob-widget-mini">
                                        <span class="mixer-lbl">Accent</span>
                                        <div class="knob-outer mini-knob" id="outer-inst-master-accent-${inst.key}"
                                             data-path="${inst.prefix}accent" data-min="0" data-max="1" data-value="${parameters.find(p => p.path === inst.prefix + 'accent')?.value || 0.5}">
                                             <svg class="knob-svg" viewBox="0 0 100 100">
                                                 <circle cx="50" cy="50" r="40" stroke="#121217" stroke-width="10" fill="none"/>
                                                 <circle class="knob-active-ring" cx="50" cy="50" r="40"
                                                         stroke-width="10" fill="none" stroke-linecap="round"/>
                                             </svg>
                                             <div class="knob-dial dial-mini"><div class="knob-pointer pointer-mini"></div></div>
                                         </div>
                                         <span class="mixer-val-mini" id="display-inst-master-accent-${inst.key}">0.50</span>
                                    </div>

                                    <div class="knob-widget-mini">
                                        <span class="mixer-lbl">Swing</span>
                                        <div class="knob-outer mini-knob" id="outer-inst-master-swing-${inst.key}"
                                             data-path="${inst.prefix}swing" data-min="0" data-max="75" data-value="${parameters.find(p => p.path === inst.prefix + 'swing')?.value || 0}">
                                             <svg class="knob-svg" viewBox="0 0 100 100">
                                                 <circle cx="50" cy="50" r="40" stroke="#121217" stroke-width="10" fill="none"/>
                                                 <circle class="knob-active-ring" cx="50" cy="50" r="40"
                                                         stroke-width="10" fill="none" stroke-linecap="round"/>
                                             </svg>
                                             <div class="knob-dial dial-mini"><div class="knob-pointer pointer-mini"></div></div>
                                         </div>
                                         <span class="mixer-val-mini" id="display-inst-master-swing-${inst.key}">0.00</span>
                                    </div>
                                </div>

                                <!-- Groove & Nota Selectors (DECOUPLED LOCAL CHANNELS) -->
                                <div class="mixer-widget-box">
                                    <span class="mixer-lbl">Tonalidad</span>
                                    <select class="mixer-select" id="select-inst-master-nota-${inst.key}" onchange="updateParam('${inst.prefix}nota', this.value)">
                                        <option value="36">C (Do)</option>
                                        <option value="37">C# (Do#)</option>
                                        <option value="38">D (Re)</option>
                                        <option value="39">D# (Re#)</option>
                                        <option value="40">E (Mi)</option>
                                        <option value="41">F (Fa)</option>
                                        <option value="42">F# (Fa#)</option>
                                        <option value="43">G (Sol)</option>
                                        <option value="44">G# (Sol#)</option>
                                        <option value="45">A (La)</option>
                                        <option value="46">A# (La#)</option>
                                        <option value="47">B (Si)</option>
                                    </select>
                                </div>

                                <div class="mixer-widget-box">
                                    <span class="mixer-lbl">Groove</span>
                                    <select class="mixer-select" id="select-inst-master-groove-${inst.key}" onchange="updateParam('${inst.prefix}groove', this.value)">
                                        <option value="0">1: Ultra Hipnótico</option>
                                        <option value="1">2: Deep Mental</option>
                                        <option value="2">3: Bucle Psíquico</option>
                                        <option value="3">4: Driving Techno</option>
                                        <option value="4">5: Tribal Funk</option>
                                        <option value="5">6: Hardgroove Tradicional</option>
                                        <option value="6">7: Hardgroove Frenético</option>
                                    </select>
                                </div>

                                <!-- Decay Slider (Horizontal) -->
                                <div class="mixer-widget-box">
                                    <div class="mixer-lbl-row">
                                        <span class="mixer-lbl">${decayName.substring(0, 8)}</span>
                                        <span class="mixer-val-txt" id="display-mixer-decay-${inst.key}">${decayParam.value.toFixed(2)}</span>
                                    </div>
                                    <input type="range" class="mixer-slider-h" id="slider-mixer-decay-${inst.key}"
                                           min="${decayParam.min}" max="${decayParam.max}" step="0.01" value="${decayParam.value}"
                                           oninput="updateParam('${decayParam.path}', this.value, 'display-mixer-decay-${inst.key}')">
                                </div>

                                <!-- Vertical Volume Fader -->
                                <div class="fader-widget-vertical">
                                    <div class="fader-lbl-row">
                                        <span class="mixer-lbl">VOLUME</span>
                                        <span class="fader-val-txt" id="display-mixer-vol-${inst.key}">${volParam.value.toFixed(2)}</span>
                                    </div>
                                    <div class="fader-track-container">
                                        <input type="range" class="fader-slider-v" id="slider-mixer-vol-${inst.key}"
                                               min="${volParam.min}" max="${volParam.max}" step="0.01" value="${volParam.value}"
                                               oninput="updateParam('${volParam.path}', this.value, 'display-mixer-vol-${inst.key}')">
                                    </div>
                                </div>
                            </div>
                        `;
                    }).join('')}
                </div>
            `;
            
            // Vincular eventos de drag a todos los knobs del mixer console
            INSTRUMENTS.forEach(inst => {
                ['accent', 'swing'].forEach(k => {
                    const ko = document.getElementById(`outer-inst-master-${k}-${inst.key}`);
                    if (ko) {
                        ko.addEventListener('mousedown', startKnobDrag);
                        ko.addEventListener('touchstart', startKnobDrag, { passive: false });
                        updateKnobGraphics(ko);
                    }
                });
            });
        }"""

# Hacemos el reemplazo
new_content = content[:start_idx] + new_implementation + content[end_idx:]

with open(file_path, "w", encoding="utf-8") as f:
    f.write(new_content)

print("Reemplazo realizado con éxito")
