#pragma once
// =============================================================================
// PresetManager.h — Gestión de presets del sintetizador BAZZ
// =============================================================================
//
// Permite guardar y cargar el estado completo del sintetizador en un formato
// de texto legible por humanos (similar a JSON, implementado a mano sin
// dependencias externas).
//
// IMPORTANTE: Esta clase NO es segura para el hilo de audio. Debe usarse
// exclusivamente desde el hilo de control/interfaz de usuario.
//
// Estructura de un preset:
//   - Nombre y autor del preset
//   - BPM global
//   - Para cada instrumento (canal 0..5):
//       · Swing individual del canal
//       · Mapa de parámetros de síntesis (nombre → valor)
//       · Patrón de pasos del secuenciador (16 pasos booleanos)
//
// Formato de serialización (ejemplo):
//   preset {
//       name = "Mi Preset"
//       author = "BAZZ"
//       bpm = 140.0
//       channel 0 {
//           instrument = "Kick"
//           swing = 25.0
//           params {
//               volume = 0.85
//               decay = 0.18
//               tune = 0.0
//           }
//           steps = [1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0]
//       }
//       ...
//   }
// =============================================================================

#include <string>
#include <vector>
#include <map>
#include <array>
#include <cstdint>

// ---------------------------------------------------------------------------
// Número de canales del secuenciador y pasos por canal
// ---------------------------------------------------------------------------
static constexpr int BAZZ_NUM_CHANNELS = 6;
static constexpr int BAZZ_NUM_STEPS    = 16;

// ---------------------------------------------------------------------------
// Nombres por defecto de los instrumentos (índice = canal)
// ---------------------------------------------------------------------------
static const char* const BAZZ_DEFAULT_INSTRUMENT_NAMES[BAZZ_NUM_CHANNELS] = {
    "Kick", "Snare", "HiHat", "Bass", "Psyche", "Siringe"
};

// ============================================================================
// Estructura que almacena el estado completo de un canal del secuenciador
// ============================================================================
struct ChannelPreset {
    /// Nombre del instrumento asignado a este canal (ej. "Kick", "Snare")
    std::string instrumentName;

    /// Valor de swing individual para este canal (0.0 – 75.0)
    float swing = 0.0f;

    /// Mapa de parámetros de síntesis: nombre → valor
    /// Ejemplo: { "volume": 0.85, "decay": 0.18, "tune": 0.0 }
    std::map<std::string, float> parameters;

    /// Patrón de pasos del secuenciador (true = activo, false = silencio)
    std::array<bool, BAZZ_NUM_STEPS> steps{};

    ChannelPreset() {
        steps.fill(false);
    }
};

// ============================================================================
// Estructura que almacena un preset completo del sintetizador
// ============================================================================
struct Preset {
    /// Nombre descriptivo del preset (ej. "Techno Oscuro")
    std::string name = "Init";

    /// Autor del preset
    std::string author = "BAZZ";

    /// Tempo global en beats por minuto
    float bpm = 140.0f;

    /// Estado de cada uno de los 6 canales
    std::array<ChannelPreset, BAZZ_NUM_CHANNELS> channels;

    Preset() {
        // Asignar nombres de instrumento por defecto
        for (int i = 0; i < BAZZ_NUM_CHANNELS; ++i) {
            channels[static_cast<size_t>(i)].instrumentName =
                BAZZ_DEFAULT_INSTRUMENT_NAMES[i];
        }
    }
};

// ============================================================================
// PresetManager — Clase principal de gestión de presets
// ============================================================================
class PresetManager {
public:
    PresetManager()  = default;
    ~PresetManager() = default;

    // No es copiable ni movible (gestiona estado de archivo)
    PresetManager(const PresetManager&)            = delete;
    PresetManager& operator=(const PresetManager&) = delete;
    PresetManager(PresetManager&&)                 = delete;
    PresetManager& operator=(PresetManager&&)      = delete;

    // -----------------------------------------------------------------------
    // Serialización ↔ Cadena de texto
    // -----------------------------------------------------------------------

    /// Serializa el preset a una cadena de texto legible por humanos.
    /// @param preset  El preset a serializar
    /// @return        Cadena con el preset completo en formato BAZZ
    [[nodiscard]]
    std::string serializeToString(const Preset& preset) const;

    /// Reconstruye un preset a partir de una cadena serializada.
    /// @param data    Cadena de texto con el preset en formato BAZZ
    /// @param outPreset  Referencia donde se almacena el preset reconstruido
    /// @return        true si la deserialización fue exitosa, false si hubo
    ///                errores de formato
    [[nodiscard]]
    bool deserializeFromString(const std::string& data, Preset& outPreset) const;

    // -----------------------------------------------------------------------
    // Entrada / Salida de archivos
    // -----------------------------------------------------------------------

    /// Guarda el preset en un archivo de texto en el disco.
    /// @param filePath  Ruta completa del archivo destino (ej. "presets/mi_preset.bazz")
    /// @param preset    El preset a guardar
    /// @return          true si la escritura fue exitosa
    [[nodiscard]]
    bool saveToFile(const std::string& filePath, const Preset& preset) const;

    /// Carga un preset desde un archivo de texto.
    /// @param filePath   Ruta completa del archivo a leer
    /// @param outPreset  Referencia donde se almacena el preset leído
    /// @return           true si la lectura y deserialización fueron exitosas
    [[nodiscard]]
    bool loadFromFile(const std::string& filePath, Preset& outPreset) const;

    // -----------------------------------------------------------------------
    // Utilidades
    // -----------------------------------------------------------------------

    /// Crea un preset con valores por defecto (estado "Init")
    [[nodiscard]]
    static Preset createDefaultPreset();

    /// Devuelve una cadena con el último error encontrado durante la
    /// deserialización. Vacía si no hubo errores.
    [[nodiscard]]
    const std::string& getLastError() const { return m_lastError; }

private:
    // -----------------------------------------------------------------------
    // Estado interno mutable (para reportar errores de parseo)
    // -----------------------------------------------------------------------
    mutable std::string m_lastError;

    // -----------------------------------------------------------------------
    // Métodos auxiliares de serialización
    // -----------------------------------------------------------------------

    /// Escribe la sección de un canal con la indentación adecuada
    void writeChannel(std::string& out, const ChannelPreset& ch,
                      int channelIndex, int indent) const;

    /// Escribe el mapa de parámetros de un instrumento
    void writeParams(std::string& out, const std::map<std::string, float>& params,
                     int indent) const;

    /// Escribe el patrón de pasos como arreglo [1,0,0,1,...]
    void writeSteps(std::string& out, const std::array<bool, BAZZ_NUM_STEPS>& steps,
                    int indent) const;

    // -----------------------------------------------------------------------
    // Métodos auxiliares de deserialización (parser recursivo-descendente)
    // -----------------------------------------------------------------------

    /// Analiza el bloque raíz "preset { ... }"
    bool parsePresetBlock(const std::string& data, size_t& pos,
                          Preset& outPreset) const;

    /// Analiza un bloque "channel N { ... }"
    bool parseChannelBlock(const std::string& data, size_t& pos,
                           ChannelPreset& outChannel) const;

    /// Analiza un bloque "params { ... }"
    bool parseParamsBlock(const std::string& data, size_t& pos,
                          std::map<std::string, float>& outParams) const;

    /// Analiza un arreglo de pasos "[1,0,1,0,...]"
    bool parseStepsArray(const std::string& data, size_t& pos,
                         std::array<bool, BAZZ_NUM_STEPS>& outSteps) const;

    // -----------------------------------------------------------------------
    // Utilidades del parser
    // -----------------------------------------------------------------------

    /// Salta espacios en blanco, tabuladores y saltos de línea
    void skipWhitespace(const std::string& data, size_t& pos) const;

    /// Salta comentarios de línea (// ...)
    void skipLineComment(const std::string& data, size_t& pos) const;

    /// Salta todo espacio en blanco y comentarios
    void skipWhitespaceAndComments(const std::string& data, size_t& pos) const;

    /// Lee un token alfanumérico (letras, dígitos, guiones bajos)
    std::string readToken(const std::string& data, size_t& pos) const;

    /// Lee una cadena entre comillas dobles, con soporte de escape básico
    bool readQuotedString(const std::string& data, size_t& pos,
                          std::string& outStr) const;

    /// Lee un valor numérico (entero o decimal, positivo o negativo)
    bool readFloat(const std::string& data, size_t& pos, float& outVal) const;

    /// Espera y consume un carácter específico; reporta error si no coincide
    bool expectChar(const std::string& data, size_t& pos, char expected) const;

    /// Genera una cadena de indentación (4 espacios por nivel)
    static std::string indent(int level);

    /// Convierte un float a cadena legible (ej. "0.85", "140.0")
    static std::string floatToStr(float value);
};
