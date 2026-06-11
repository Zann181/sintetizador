export class LocalStorageRepo {
    getParamMappings() {
        try {
            return JSON.parse(localStorage.getItem("paramMappings") || "{}");
        } catch (e) {
            console.error("Error loading paramMappings from localStorage:", e);
            return {};
        }
    }

    saveParamMappings(mappings) {
        try {
            localStorage.setItem("paramMappings", JSON.stringify(mappings));
        } catch (e) {
            console.error("Error saving paramMappings to localStorage:", e);
        }
    }

    getCustomGrooves() {
        try {
            return JSON.parse(localStorage.getItem("customGrooves") || "{}");
        } catch (e) {
            console.error("Error loading customGrooves from localStorage:", e);
            return {};
        }
    }

    saveCustomGrooves(grooves) {
        try {
            localStorage.setItem("customGrooves", JSON.stringify(grooves));
        } catch (e) {
            console.error("Error saving customGrooves to localStorage:", e);
        }
    }

    getCustomPerformances() {
        try {
            return JSON.parse(localStorage.getItem("customPerfPresets") || "{}");
        } catch (e) {
            console.error("Error loading customPerfPresets from localStorage:", e);
            return {};
        }
    }

    saveCustomPerformances(performances) {
        try {
            localStorage.setItem("customPerfPresets", JSON.stringify(performances));
        } catch (e) {
            console.error("Error saving customPerfPresets to localStorage:", e);
        }
    }
}
