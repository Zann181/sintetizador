// =============================================================================
// PresetManager.cpp — Implementación del gestor de presets de BAZZ
// =============================================================================
//
// Parser recursivo-descendente para un formato de texto legible por humanos.
// Sin dependencias externas: todo el análisis sintáctico está implementado
// a mano sobre std::string.
//
// NOTA: Esta clase NO debe invocarse desde el hilo de audio.
// =============================================================================

#include "PresetManager.h"

#include <fstream>
#include <sstream>
#include <charconv>
#include <cstring>
#include <algorithm>
#include <cctype>

// ============================================================================
//  SERIALIZACIÓN → CADENA DE TEXTO
// ============================================================================

std::string PresetManager::serializeToString(const Preset& preset) const
{
    std::string out;
    // Reservar espacio estimado para evitar realocaciones frecuentes
    out.reserve(4096);

    // ------- Encabezado -------
    out += "// ==============================================\n";
    out += "// Preset BAZZ_Sintetizador\n";
    out += "// Formato v1.0 — generado automáticamente\n";
    out += "// ==============================================\n\n";

    out += "preset {\n";

    // ------- Metadatos del preset -------
    out += indent(1) + "name = \"" + preset.name + "\"\n";
    out += indent(1) + "author = \"" + preset.author + "\"\n";
    out += indent(1) + "bpm = " + floatToStr(preset.bpm) + "\n";
    out += "\n";

    // ------- Canales (0..5) -------
    for (int ch = 0; ch < BAZZ_NUM_CHANNELS; ++ch) {
        writeChannel(out, preset.channels[static_cast<size_t>(ch)], ch, 1);
        out += "\n";
    }

    out += "}\n";
    return out;
}

// ============================================================================
//  DESERIALIZACIÓN ← CADENA DE TEXTO
// ============================================================================

bool PresetManager::deserializeFromString(const std::string& data,
                                          Preset& outPreset) const
{
    m_lastError.clear();
    outPreset = Preset{};   // Reiniciar a valores por defecto

    size_t pos = 0;
    skipWhitespaceAndComments(data, pos);

    // Esperamos el token "preset"
    std::string token = readToken(data, pos);
    if (token != "preset") {
        m_lastError = "Se esperaba el bloque 'preset' al inicio del archivo. "
                      "Se encontró: '" + token + "'";
        return false;
    }

    return parsePresetBlock(data, pos, outPreset);
}

// ============================================================================
//  ENTRADA / SALIDA DE ARCHIVOS
// ============================================================================

bool PresetManager::saveToFile(const std::string& filePath,
                               const Preset& preset) const
{
    std::ofstream file(filePath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        m_lastError = "No se pudo abrir el archivo para escritura: " + filePath;
        return false;
    }

    std::string content = serializeToString(preset);
    file << content;

    if (file.fail()) {
        m_lastError = "Error de escritura en el archivo: " + filePath;
        return false;
    }

    return true;
}

bool PresetManager::loadFromFile(const std::string& filePath,
                                 Preset& outPreset) const
{
    std::ifstream file(filePath, std::ios::in);
    if (!file.is_open()) {
        m_lastError = "No se pudo abrir el archivo para lectura: " + filePath;
        return false;
    }

    // Leer todo el contenido del archivo en una sola cadena
    std::ostringstream ss;
    ss << file.rdbuf();

    if (file.fail() && !file.eof()) {
        m_lastError = "Error de lectura del archivo: " + filePath;
        return false;
    }

    return deserializeFromString(ss.str(), outPreset);
}

// ============================================================================
//  UTILIDADES
// ============================================================================

Preset PresetManager::createDefaultPreset()
{
    Preset p;
    p.name   = "Init";
    p.author = "BAZZ";
    p.bpm    = 140.0f;

    // Canal 0 (Kick): patrón clásico de 4 en el suelo
    auto& kick = p.channels[0];
    kick.instrumentName = "Kick";
    kick.parameters["volume"]  = 0.85f;
    kick.parameters["decay"]   = 0.18f;
    kick.parameters["tune"]    = 0.0f;
    kick.parameters["accent"]  = 0.5f;
    kick.steps = {true,false,false,false, true,false,false,false,
                  true,false,false,false, true,false,false,false};

    // Canal 1 (Snare): golpes en pasos 4 y 12
    auto& snare = p.channels[1];
    snare.instrumentName = "Snare";
    snare.parameters["volume"] = 0.75f;
    snare.parameters["tone"]   = 0.5f;
    snare.parameters["snap"]   = 0.6f;
    snare.steps[4]  = true;
    snare.steps[12] = true;

    // Canal 2 (HiHat): cada dos pasos
    auto& hat = p.channels[2];
    hat.instrumentName = "HiHat";
    hat.parameters["volume"]   = 0.6f;
    hat.parameters["openness"] = 0.3f;
    for (int i = 0; i < BAZZ_NUM_STEPS; i += 2) {
        hat.steps[static_cast<size_t>(i)] = true;
    }

    // Canales 3–5: solo nombre de instrumento, sin patrón
    p.channels[3].instrumentName = "Bass";
    p.channels[4].instrumentName = "Psyche";
    p.channels[5].instrumentName = "Siringe";

    return p;
}

// ============================================================================
//  ESCRITURA DE SECCIONES (helpers de serialización)
// ============================================================================

void PresetManager::writeChannel(std::string& out, const ChannelPreset& ch,
                                 int channelIndex, int ind) const
{
    out += indent(ind) + "channel " + std::to_string(channelIndex) + " {\n";
    out += indent(ind + 1) + "instrument = \"" + ch.instrumentName + "\"\n";
    out += indent(ind + 1) + "swing = " + floatToStr(ch.swing) + "\n";

    // Parámetros de síntesis
    if (!ch.parameters.empty()) {
        writeParams(out, ch.parameters, ind + 1);
    }

    // Patrón de pasos
    writeSteps(out, ch.steps, ind + 1);

    out += indent(ind) + "}\n";
}

void PresetManager::writeParams(std::string& out,
                                const std::map<std::string, float>& params,
                                int ind) const
{
    out += indent(ind) + "params {\n";
    for (const auto& [key, value] : params) {
        out += indent(ind + 1) + key + " = " + floatToStr(value) + "\n";
    }
    out += indent(ind) + "}\n";
}

void PresetManager::writeSteps(std::string& out,
                               const std::array<bool, BAZZ_NUM_STEPS>& steps,
                               int ind) const
{
    out += indent(ind) + "steps = [";
    for (int i = 0; i < BAZZ_NUM_STEPS; ++i) {
        if (i > 0) out += ",";
        out += (steps[static_cast<size_t>(i)] ? "1" : "0");
    }
    out += "]\n";
}

// ============================================================================
//  PARSER RECURSIVO-DESCENDENTE
// ============================================================================

// ---------- Bloque raíz: preset { ... } ----------

bool PresetManager::parsePresetBlock(const std::string& data, size_t& pos,
                                     Preset& outPreset) const
{
    skipWhitespaceAndComments(data, pos);
    if (!expectChar(data, pos, '{')) return false;

    while (pos < data.size()) {
        skipWhitespaceAndComments(data, pos);

        // ¿Fin del bloque?
        if (pos < data.size() && data[pos] == '}') {
            ++pos;
            return true;
        }

        std::string key = readToken(data, pos);
        if (key.empty()) {
            m_lastError = "Token inesperado en el bloque 'preset' (posición "
                          + std::to_string(pos) + ")";
            return false;
        }

        if (key == "name") {
            skipWhitespaceAndComments(data, pos);
            if (!expectChar(data, pos, '=')) return false;
            skipWhitespaceAndComments(data, pos);
            if (!readQuotedString(data, pos, outPreset.name)) return false;

        } else if (key == "author") {
            skipWhitespaceAndComments(data, pos);
            if (!expectChar(data, pos, '=')) return false;
            skipWhitespaceAndComments(data, pos);
            if (!readQuotedString(data, pos, outPreset.author)) return false;

        } else if (key == "bpm") {
            skipWhitespaceAndComments(data, pos);
            if (!expectChar(data, pos, '=')) return false;
            skipWhitespaceAndComments(data, pos);
            if (!readFloat(data, pos, outPreset.bpm)) return false;

        } else if (key == "channel") {
            // Leer el índice del canal
            skipWhitespaceAndComments(data, pos);
            float channelIdx = 0.0f;
            if (!readFloat(data, pos, channelIdx)) return false;

            int ch = static_cast<int>(channelIdx);
            if (ch < 0 || ch >= BAZZ_NUM_CHANNELS) {
                m_lastError = "Índice de canal fuera de rango: "
                              + std::to_string(ch);
                return false;
            }

            skipWhitespaceAndComments(data, pos);
            if (!parseChannelBlock(data, pos,
                                   outPreset.channels[static_cast<size_t>(ch)])) {
                return false;
            }

        } else {
            m_lastError = "Clave desconocida en bloque 'preset': '" + key + "'";
            return false;
        }
    }

    m_lastError = "Fin de datos inesperado dentro del bloque 'preset'";
    return false;
}

// ---------- Bloque de canal: channel N { ... } ----------

bool PresetManager::parseChannelBlock(const std::string& data, size_t& pos,
                                      ChannelPreset& outChannel) const
{
    skipWhitespaceAndComments(data, pos);
    if (!expectChar(data, pos, '{')) return false;

    while (pos < data.size()) {
        skipWhitespaceAndComments(data, pos);

        if (pos < data.size() && data[pos] == '}') {
            ++pos;
            return true;
        }

        std::string key = readToken(data, pos);
        if (key.empty()) {
            m_lastError = "Token inesperado en bloque 'channel' (posición "
                          + std::to_string(pos) + ")";
            return false;
        }

        if (key == "instrument") {
            skipWhitespaceAndComments(data, pos);
            if (!expectChar(data, pos, '=')) return false;
            skipWhitespaceAndComments(data, pos);
            if (!readQuotedString(data, pos, outChannel.instrumentName)) return false;

        } else if (key == "swing") {
            skipWhitespaceAndComments(data, pos);
            if (!expectChar(data, pos, '=')) return false;
            skipWhitespaceAndComments(data, pos);
            if (!readFloat(data, pos, outChannel.swing)) return false;

        } else if (key == "params") {
            skipWhitespaceAndComments(data, pos);
            if (!parseParamsBlock(data, pos, outChannel.parameters)) return false;

        } else if (key == "steps") {
            skipWhitespaceAndComments(data, pos);
            if (!expectChar(data, pos, '=')) return false;
            skipWhitespaceAndComments(data, pos);
            if (!parseStepsArray(data, pos, outChannel.steps)) return false;

        } else {
            m_lastError = "Clave desconocida en bloque 'channel': '" + key + "'";
            return false;
        }
    }

    m_lastError = "Fin de datos inesperado dentro de bloque 'channel'";
    return false;
}

// ---------- Bloque de parámetros: params { ... } ----------

bool PresetManager::parseParamsBlock(const std::string& data, size_t& pos,
                                     std::map<std::string, float>& outParams) const
{
    skipWhitespaceAndComments(data, pos);
    if (!expectChar(data, pos, '{')) return false;

    while (pos < data.size()) {
        skipWhitespaceAndComments(data, pos);

        if (pos < data.size() && data[pos] == '}') {
            ++pos;
            return true;
        }

        // Leer nombre del parámetro
        std::string paramName = readToken(data, pos);
        if (paramName.empty()) {
            m_lastError = "Nombre de parámetro vacío en bloque 'params' (posición "
                          + std::to_string(pos) + ")";
            return false;
        }

        skipWhitespaceAndComments(data, pos);
        if (!expectChar(data, pos, '=')) return false;
        skipWhitespaceAndComments(data, pos);

        float value = 0.0f;
        if (!readFloat(data, pos, value)) return false;

        outParams[paramName] = value;
    }

    m_lastError = "Fin de datos inesperado dentro de bloque 'params'";
    return false;
}

// ---------- Arreglo de pasos: [1,0,1,0,...] ----------

bool PresetManager::parseStepsArray(const std::string& data, size_t& pos,
                                    std::array<bool, BAZZ_NUM_STEPS>& outSteps) const
{
    if (!expectChar(data, pos, '[')) return false;

    for (int i = 0; i < BAZZ_NUM_STEPS; ++i) {
        skipWhitespaceAndComments(data, pos);

        // Leer un dígito (0 ó 1)
        if (pos >= data.size()) {
            m_lastError = "Fin de datos inesperado dentro del arreglo de pasos";
            return false;
        }

        char c = data[pos];
        if (c == '1') {
            outSteps[static_cast<size_t>(i)] = true;
        } else if (c == '0') {
            outSteps[static_cast<size_t>(i)] = false;
        } else {
            m_lastError = "Valor de paso inválido (se esperaba 0 ó 1): '"
                          + std::string(1, c) + "'";
            return false;
        }
        ++pos;

        // Consumir la coma separadora (si no es el último paso)
        skipWhitespaceAndComments(data, pos);
        if (i < BAZZ_NUM_STEPS - 1) {
            if (pos < data.size() && data[pos] == ',') {
                ++pos;
            }
        }
    }

    skipWhitespaceAndComments(data, pos);
    if (!expectChar(data, pos, ']')) return false;

    return true;
}

// ============================================================================
//  UTILIDADES DEL PARSER
// ============================================================================

void PresetManager::skipWhitespace(const std::string& data, size_t& pos) const
{
    while (pos < data.size() && std::isspace(static_cast<unsigned char>(data[pos]))) {
        ++pos;
    }
}

void PresetManager::skipLineComment(const std::string& data, size_t& pos) const
{
    // Verificar si estamos ante "//"
    if (pos + 1 < data.size() && data[pos] == '/' && data[pos + 1] == '/') {
        pos += 2;
        // Avanzar hasta el fin de línea
        while (pos < data.size() && data[pos] != '\n') {
            ++pos;
        }
        // Saltar el '\n' también
        if (pos < data.size()) ++pos;
    }
}

void PresetManager::skipWhitespaceAndComments(const std::string& data,
                                              size_t& pos) const
{
    while (pos < data.size()) {
        // Saltar espacios en blanco
        if (std::isspace(static_cast<unsigned char>(data[pos]))) {
            ++pos;
            continue;
        }
        // Saltar comentarios de línea
        if (pos + 1 < data.size() && data[pos] == '/' && data[pos + 1] == '/') {
            skipLineComment(data, pos);
            continue;
        }
        // Carácter significativo — dejar de saltar
        break;
    }
}

std::string PresetManager::readToken(const std::string& data, size_t& pos) const
{
    skipWhitespaceAndComments(data, pos);
    std::string token;

    while (pos < data.size()) {
        char c = data[pos];
        // Un token puede contener letras, dígitos, guiones bajos y puntos
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '.') {
            token += c;
            ++pos;
        } else {
            break;
        }
    }

    return token;
}

bool PresetManager::readQuotedString(const std::string& data, size_t& pos,
                                     std::string& outStr) const
{
    if (pos >= data.size() || data[pos] != '"') {
        m_lastError = "Se esperaba una cadena entre comillas en la posición "
                      + std::to_string(pos);
        return false;
    }

    ++pos;  // Saltar la comilla de apertura
    outStr.clear();

    while (pos < data.size()) {
        char c = data[pos];

        if (c == '"') {
            ++pos;  // Saltar la comilla de cierre
            return true;
        }

        // Soporte básico de secuencias de escape
        if (c == '\\' && pos + 1 < data.size()) {
            ++pos;
            char escaped = data[pos];
            switch (escaped) {
                case '"':  outStr += '"';  break;
                case '\\': outStr += '\\'; break;
                case 'n':  outStr += '\n'; break;
                case 't':  outStr += '\t'; break;
                default:
                    // Carácter desconocido: incluirlo tal cual
                    outStr += escaped;
                    break;
            }
            ++pos;
            continue;
        }

        outStr += c;
        ++pos;
    }

    m_lastError = "Cadena sin cerrar (falta comilla de cierre)";
    return false;
}

bool PresetManager::readFloat(const std::string& data, size_t& pos,
                              float& outVal) const
{
    skipWhitespaceAndComments(data, pos);

    if (pos >= data.size()) {
        m_lastError = "Fin de datos al intentar leer un valor numérico";
        return false;
    }

    // Encontrar el rango de caracteres que forman el número
    size_t start = pos;

    // Signo opcional
    if (data[pos] == '-' || data[pos] == '+') ++pos;

    // Parte entera
    while (pos < data.size() && std::isdigit(static_cast<unsigned char>(data[pos]))) {
        ++pos;
    }

    // Parte decimal
    if (pos < data.size() && data[pos] == '.') {
        ++pos;
        while (pos < data.size() && std::isdigit(static_cast<unsigned char>(data[pos]))) {
            ++pos;
        }
    }

    if (pos == start) {
        m_lastError = "Se esperaba un valor numérico en la posición "
                      + std::to_string(pos);
        return false;
    }

    // Convertir la subcadena a float usando std::from_chars (C++17/C++20)
    const char* begin = data.data() + start;
    const char* end   = data.data() + pos;

    auto [ptr, ec] = std::from_chars(begin, end, outVal);

    if (ec != std::errc{}) {
        m_lastError = "Error al convertir valor numérico: '"
                      + std::string(begin, end) + "'";
        return false;
    }

    return true;
}

bool PresetManager::expectChar(const std::string& data, size_t& pos,
                               char expected) const
{
    skipWhitespaceAndComments(data, pos);

    if (pos >= data.size()) {
        m_lastError = "Fin de datos inesperado: se esperaba '"
                      + std::string(1, expected) + "'";
        return false;
    }

    if (data[pos] != expected) {
        m_lastError = "Se esperaba '" + std::string(1, expected)
                      + "' pero se encontró '" + std::string(1, data[pos])
                      + "' en la posición " + std::to_string(pos);
        return false;
    }

    ++pos;
    return true;
}

// ============================================================================
//  FUNCIONES DE FORMATO
// ============================================================================

std::string PresetManager::indent(int level)
{
    // 4 espacios por nivel de indentación
    return std::string(static_cast<size_t>(level) * 4, ' ');
}

std::string PresetManager::floatToStr(float value)
{
    // Convertir float a cadena, eliminando ceros redundantes al final
    // pero conservando al menos un decimal (ej. "140.0" en vez de "140")
    std::ostringstream oss;
    oss << value;
    std::string result = oss.str();

    // Asegurar que tenga punto decimal para claridad visual
    if (result.find('.') == std::string::npos) {
        result += ".0";
    }

    return result;
}
