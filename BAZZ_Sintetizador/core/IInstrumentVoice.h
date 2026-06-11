#pragma once
#include <string>
#include <cstdint>
#include "InstrumentDescriptor.h"

// ============================================================================
// IInstrumentVoice.h — v2
// Interfaz abstracta común para todos los generadores de audio (voces) del
// sintetizador BAZZ. Versión 2 con soporte de introspección, serialización
// de estado y despacho de parámetros por ID numérico (sin strings en RT).
// ============================================================================

class IInstrumentVoice {
public:
    virtual ~IInstrumentVoice() = default;

    // ---- Ciclo de vida ----

    // Configura la frecuencia de muestreo del DSP interno.
    // Debe llamarse antes de cualquier procesamiento.
    virtual void initialize(double sampleRate) = 0;

    // Limpia buffers de delay y resetea todos los estados internos de filtros.
    virtual void clearState() = 0;

    // ---- Procesamiento de audio ----

    // Dispara un golpe del instrumento con velocidad dinámica (0.0f a 1.0f).
    virtual void trigger(float velocity) = 0;

    // Renderiza un bloque de audio. Suma en los buffers estéreo de salida.
    // Si triggerBuffer != nullptr, contiene amplitudes de trigger muestra-por-muestra
    // generadas por el Clock del secuenciador.
    virtual void processBlock(float* outputBufferL, float* outputBufferR,
                              int numSamples,
                              const float* triggerBuffer = nullptr) = 0;

    // ---- Parámetros (v1 — compatibilidad, NO usar en hilo de audio nuevo) ----

    // Actualiza un parámetro de síntesis usando el path OSC como string.
    // DEPRECADO en la v2: preferir setParameterById() que evita allocaciones.
    virtual void setParameter(const std::string& name, float value) = 0;

    // ---- Parámetros (v2 — sin strings, apto para audio thread) ----

    // Actualiza un parámetro usando su ID hash (bazz::paramHash("/kick/vol")).
    // Implementación por defecto delega a setParameter() para compatibilidad
    // con voces que aún no migraron.
    virtual void setParameterById(uint32_t paramId, float value) {
        // Fallback: buscar el path en el descriptor y llamar setParameter()
        const auto& desc = getDescriptor();
        const bazz::ParamInfo* p = desc.findParamById(paramId);
        if (p) setParameter(p->oscPath, value);
    }

    // ---- Introspección (v2) ----

    // Retorna el descriptor del instrumento con sus metadatos y parámetros.
    virtual const bazz::InstrumentDescriptor& getDescriptor() const = 0;

    // ---- Serialización de estado (v2) ----

    // Escribe los valores actuales de todos los parámetros en el buffer.
    // El orden sigue el array params[] del InstrumentDescriptor.
    // Retorna la cantidad de parámetros escritos.
    virtual int getState(float* buffer, int maxParams) const {
        (void)buffer; (void)maxParams;
        return 0; // Implementación por defecto: sin estado
    }

    // Restaura los valores de todos los parámetros desde el buffer.
    // El orden debe coincidir con getState().
    virtual void setState(const float* buffer, int numParams) {
        (void)buffer; (void)numParams;
    }
};
