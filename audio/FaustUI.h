#pragma once

#include "../core/Synthesizer.h"
#include <string>
#include <vector>
#include <iostream>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

// Interfaz mínima requerida por el código C++ generado de Faust
class UI {
public:
    virtual ~UI() {}
    virtual void openVerticalBox(const char* label) {}
    virtual void openHorizontalBox(const char* label) {}
    virtual void closeBox() {}
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
    
    // El método clave que invoca Faust para registrar los parámetros
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
    // Si Faust usara otros widgets, se podrían declarar aquí vacíos
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
    virtual void addToggleButton(const char* label, FAUSTFLOAT* zone) {}
};

// Extensión abstracta para declarar metadatos (necesaria para dsp)
class Meta {
public:
    virtual void declare(const char* key, const char* value) = 0;
};

// Implementación de UI que enlaza los punteros del DSP con nuestro Synthesizer
namespace audio {

class FaustMapUI : public UI {
public:
    FaustMapUI(core::Synthesizer* synth) : m_synth(synth) {}

    // Getter para acceder al sintetizador
    core::Synthesizer* getSynth() const { return m_synth; }

    // Interceptamos metadatos de OSC generados por Faust (ej: ui_interface->declare(&fHslider38, "osc", "/master/accent");)
    void declare(FAUSTFLOAT* zone, const char* key, const char* val) override {
        std::string sKey(key);
        if (sKey == "osc") {
            m_zoneToOscPath[zone] = std::string(val);
        } else if (sKey == "style") {
            m_zoneToStyle[zone] = std::string(val);
        }
    }

    // Interceptamos la creación del slider para crear el Parámetro en el Dominio
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {
        registerParameter(label, zone, init, min, max);
    }

    // Interceptamos los checkboxes (botones de step del pad)
    void addCheckButton(const char* label, FAUSTFLOAT* zone) override {
        std::cout << "addCheckButton called for: " << label << std::endl;
        registerParameter(label, zone, 0.0f, 0.0f, 1.0f);
    }

    // Método auxiliar para registrar el parámetro sin importar el tipo de UI
    void registerParameter(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max) {
        std::string path;
        
        // Verificamos si Faust declaró una ruta OSC para este zone
        auto it = m_zoneToOscPath.find(zone);
        if (it != m_zoneToOscPath.end()) {
            path = it->second;
        } else {
            // Fallback si no tiene ruta OSC explícita, usar el label
            path = std::string("/") + label;
        }

        std::string finalLabel = label;
        auto styleIt = m_zoneToStyle.find(zone);
        if (styleIt != m_zoneToStyle.end()) {
            finalLabel += " [style:" + styleIt->second + "]";
        }

        // Buscar si ya existe en el Synthesizer para reutilizar la misma instancia (ej. parámetros maestros compartidos)
        auto param = m_synth->getParameter(path);
        if (!param) {
            param = std::make_shared<core::Parameter>(path, min, max, *zone, finalLabel);
            m_synth->addParameter(param);
        }
        
        // Mapeamos el puntero del DSP (zone) con nuestra entidad Parameter
        m_zoneToParam[zone] = param;
    }

    // Llamar a este método en cada callback de audio para transferir los valores asíncronos (lock-free) al DSP
    void updateDSPValues() {
        // Sincronizar el BPM de MasterClock al parámetro /master/bpm
        auto bpmParam = m_synth->getParameter("/master/bpm");
        if (bpmParam) {
            bpmParam->setValue(m_synth->getClock()->getBpm());
        }

        for (const auto& pair : m_zoneToParam) {
            FAUSTFLOAT* zone = pair.first;
            std::shared_ptr<core::Parameter> param = pair.second;
            // Actualizamos la memoria del DSP con el valor atómico leído de forma segura
            *zone = param->getValue();
        }
    }

private:
    core::Synthesizer* m_synth;
    std::map<FAUSTFLOAT*, std::string> m_zoneToOscPath;
    std::map<FAUSTFLOAT*, std::string> m_zoneToStyle;
    std::map<FAUSTFLOAT*, std::shared_ptr<core::Parameter>> m_zoneToParam;
};

} // namespace audio
