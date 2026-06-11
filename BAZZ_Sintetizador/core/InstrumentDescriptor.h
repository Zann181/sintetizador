#pragma once
#include <cstdint>
#include <cstring>
#include <functional>

// ============================================================================
// InstrumentDescriptor.h
// Metadatos introspectables para cada voz/instrumento del sintetizador.
// Permite que el sistema descubra dinámicamente qué parámetros tiene cada
// instrumento sin depender de strings hardcodeados en el hilo de audio.
// ============================================================================

namespace bazz {

// ---- Utilidad para generar IDs de parámetros en compilación ----
// Genera un hash FNV-1a de 32 bits a partir de un string literal.
// Uso: constexpr uint32_t id = paramHash("/kick/vol");
constexpr uint32_t paramHash(const char* str) {
    uint32_t hash = 2166136261u;
    while (*str) {
        hash ^= static_cast<uint32_t>(*str++);
        hash *= 16777619u;
    }
    return hash;
}

// ---- Tipo de salida del instrumento ----
enum class OutputType : uint8_t {
    Mono   = 1,
    Stereo = 2
};

// ---- Estilo de control (para renderizado en la UI) ----
enum class ParamStyle : uint8_t {
    Slider,     // Control deslizante horizontal
    Knob,       // Potenciómetro rotativo
    Menu,       // Selector de opciones discretas
    Toggle      // Encendido/apagado
};

// ---- Descriptor de un solo parámetro ----
struct ParamInfo {
    uint32_t    id;             // Hash FNV-1a del path OSC (ej: paramHash("/kick/vol"))
    const char* oscPath;        // Path OSC completo (ej: "/kick/vol")
    const char* displayName;    // Nombre visible en la UI (ej: "Volumen")
    const char* group;          // Grupo de la UI (ej: "Sintesis", "Dinamica")
    float       minVal;         // Valor mínimo
    float       maxVal;         // Valor máximo
    float       defaultVal;     // Valor por defecto
    float       step;           // Incremento mínimo
    ParamStyle  style;          // Estilo de control
};

// ---- Descriptor completo del instrumento ----
struct InstrumentDescriptor {
    const char*       typeName;         // Identificador único del tipo (ej: "kick_808")
    const char*       displayName;      // Nombre visible (ej: "Bombo TR-808")
    const char*       description;      // Descripción breve
    OutputType        outputType;       // Mono o Stereo
    const ParamInfo*  params;           // Array estático de descriptores de parámetros
    int               numParams;        // Cantidad de parámetros
    int               defaultChannel;   // Canal por defecto del secuenciador (0-5)

    // Busca un parámetro por su ID hash
    const ParamInfo* findParamById(uint32_t id) const {
        for (int i = 0; i < numParams; ++i) {
            if (params[i].id == id) return &params[i];
        }
        return nullptr;
    }

    // Busca un parámetro por su path OSC
    const ParamInfo* findParamByPath(const char* path) const {
        for (int i = 0; i < numParams; ++i) {
            if (std::strcmp(params[i].oscPath, path) == 0) return &params[i];
        }
        return nullptr;
    }
};

// ============================================================================
// Macros de conveniencia para declarar parámetros estáticos en cada voz
// ============================================================================

// Declara un parámetro con hash automático
#define BAZZ_PARAM(path, label, group, min, max, def, stp, stl) \
    { bazz::paramHash(path), path, label, group, min, max, def, stp, bazz::ParamStyle::stl }

} // namespace bazz
