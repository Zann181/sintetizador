export class KnobDragHandler {
    constructor(stateManager) {
        this.stateManager = stateManager;
        this.activeKnob = null;
        this.startY = 0;
        this.startVal = 0;

        this.dragKnob = this.dragKnob.bind(this);
        this.stopKnobDrag = this.stopKnobDrag.bind(this);
    }

    startKnobDrag(e, knobElement) {
        this.activeKnob = knobElement;
        this.startY = e.clientY || (e.touches ? e.touches[0].clientY : 0);
        this.startVal = parseFloat(this.activeKnob.getAttribute('data-value'));
        
        document.addEventListener('mousemove', this.dragKnob);
        document.addEventListener('touchmove', this.dragKnob, { passive: false });
        document.addEventListener('mouseup', this.stopKnobDrag);
        document.addEventListener('touchend', this.stopKnobDrag);
        e.preventDefault();
    }

    dragKnob(e) {
        if (!this.activeKnob) return;
        const cy = e.clientY || (e.touches ? e.touches[0].clientY : 0);
        const deltaY = this.startY - cy;
        const min = parseFloat(this.activeKnob.getAttribute('data-min'));
        const max = parseFloat(this.activeKnob.getAttribute('data-max'));
        let nv = this.startVal + (deltaY / 200) * (max - min);
        nv = Math.max(min, Math.min(max, nv));

        const path = this.activeKnob.getAttribute('data-path');
        this.activeKnob.setAttribute('data-value', nv);
        
        this.updateKnobGraphics(this.activeKnob);
        
        this.stateManager.updateParamValue(path, nv);

        // Instant global master accent/swing sync feedback
        if (path === '/master/accent' || path === '/master/swing') {
            const k = path === '/master/accent' ? 'accent' : 'swing';
            document.querySelectorAll(`[id^="outer-inst-master-${k}-"]`).forEach(otherKnob => {
                if (otherKnob !== this.activeKnob) {
                    otherKnob.setAttribute('data-value', nv);
                    this.updateKnobGraphics(otherKnob);
                }
            });
        }
        if (e.cancelable) e.preventDefault();
    }

    stopKnobDrag() {
        this.activeKnob = null;
        document.removeEventListener('mousemove', this.dragKnob);
        document.removeEventListener('touchmove', this.dragKnob);
        document.removeEventListener('mouseup', this.stopKnobDrag);
        document.removeEventListener('touchend', this.stopKnobDrag);
    }

    updateKnobGraphics(knob) {
        const min = parseFloat(knob.getAttribute('data-min'));
        const max = parseFloat(knob.getAttribute('data-max'));
        const val = parseFloat(knob.getAttribute('data-value'));
        const pct = (val - min) / (max - min);
        const circ = 251.2;
        const arc = circ * 0.75;
        const offset = circ - pct * arc;
        
        const ring = knob.querySelector('.knob-active-ring');
        if (ring) {
            ring.setAttribute('stroke-dasharray', `${circ}`);
            ring.setAttribute('stroke-dashoffset', `${offset}`);
        }
        const dial = knob.querySelector('.knob-dial');
        if (dial) dial.style.transform = `rotate(${pct * 270 - 135}deg)`;

        const disp = knob.closest('.knob-widget-mini')?.querySelector('.mixer-val-mini') || knob.closest('.knob-widget')?.querySelector('.knob-value-display');
        if (disp) disp.innerText = val.toFixed(2);
    }
}
