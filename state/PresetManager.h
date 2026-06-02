#pragma once

#include "../core/Synthesizer.h"
#include <string>
#include <fstream>
#include <sstream>

namespace state {

class PresetManager {
public:
    PresetManager(core::Synthesizer* synth) : m_synth(synth) {}

    // Guarda el estado de todos los parámetros en un archivo (JSON simple)
    bool savePreset(const std::string& filepath) {
        std::ofstream out(filepath);
        if (!out.is_open()) return false;

        out << "{\n";
        bool first = true;
        for (const auto& pair : m_synth->getAllParameters()) {
            if (!first) out << ",\n";
            out << "  \"" << pair.first << "\": " << pair.second->getValue();
            first = false;
        }
        out << "\n}\n";
        return true;
    }

    // Carga un archivo y actualiza los valores atómicos de los parámetros
    // (Parseo JSON simplificado para no añadir dependencias pesadas en el ejemplo)
    bool loadPreset(const std::string& filepath) {
        std::ifstream in(filepath);
        if (!in.is_open()) return false;

        std::string line;
        while (std::getline(in, line)) {
            // Buscamos formato básico "path": valor
            size_t quote1 = line.find('"');
            if (quote1 == std::string::npos) continue;
            size_t quote2 = line.find('"', quote1 + 1);
            if (quote2 == std::string::npos) continue;
            size_t colon = line.find(':', quote2 + 1);
            if (colon == std::string::npos) continue;

            std::string path = line.substr(quote1 + 1, quote2 - quote1 - 1);
            float value = std::stof(line.substr(colon + 1));

            auto param = m_synth->getParameter(path);
            if (param) {
                param->setValue(value);
            }
        }
        return true;
    }

private:
    core::Synthesizer* m_synth;
};

} // namespace state
