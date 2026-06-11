export class Parameter {
    constructor(path, value, min, max, label) {
        this.path = path;
        this.value = parseFloat(value);
        this.min = parseFloat(min);
        this.max = parseFloat(max);
        this.label = label;
    }

    // Returns custom mapped boundaries or original limits
    getEffectiveRange(paramMappings) {
        if (paramMappings && paramMappings[this.path]) {
            return paramMappings[this.path];
        }
        return { min: this.min, max: this.max };
    }

    // Converts a standard visual control position [min, max] to a mapped DSP target value
    getEffectiveValue(sliderValue, paramMappings) {
        const eff = this.getEffectiveRange(paramMappings);
        let proportion = (parseFloat(sliderValue) - this.min) / (this.max - this.min);
        if (isNaN(proportion)) proportion = 0;
        proportion = Math.max(0, Math.min(1, proportion));
        return eff.min + proportion * (eff.max - eff.min);
    }

    // Converts a DSP target value back to a standard visual control position [min, max]
    getSliderValue(effValue, paramMappings) {
        const eff = this.getEffectiveRange(paramMappings);
        if (eff.min === eff.max) return this.min;
        let proportion = (parseFloat(effValue) - eff.min) / (eff.max - eff.min);
        if (isNaN(proportion)) proportion = 0;
        proportion = Math.max(0, Math.min(1, proportion));
        return this.min + proportion * (this.max - this.min);
    }
}
