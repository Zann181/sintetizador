export class MappingModal {
    constructor(stateManager) {
        this.stateManager = stateManager;
        this.currentMappingPath = "";
    }

    init() {
        this.stateManager.on('triggerMappingModal', ({ path, min, max }) => {
            this.open(path, min, max);
        });
    }

    open(path, defaultMin, defaultMax) {
        this.currentMappingPath = path;
        
        const pathEl = document.getElementById("modal-path");
        if (pathEl) pathEl.innerText = path;
        
        const map = this.stateManager.paramMappings[path] || { min: defaultMin, max: defaultMax };
        
        const minInp = document.getElementById("modal-min");
        const maxInp = document.getElementById("modal-max");
        if (minInp) minInp.value = map.min;
        if (maxInp) maxInp.value = map.max;
        
        const modal = document.getElementById("mapping-modal");
        if (modal) modal.style.display = "flex";
    }

    close() {
        const modal = document.getElementById("mapping-modal");
        if (modal) modal.style.display = "none";
    }

    async save() {
        const minVal = parseFloat(document.getElementById("modal-min").value);
        const maxVal = parseFloat(document.getElementById("modal-max").value);
        
        if (!isNaN(minVal) && !isNaN(maxVal)) {
            await this.stateManager.saveMapping(this.currentMappingPath, minVal, maxVal);
        }
        
        this.close();
    }
}
