#pragma once
// ============================================================================
// Saturator.h — Procesador de Saturación/Distorsión para BAZZ Sintetizador
// ============================================================================
//
// Proporciona algoritmos de distorsión y soft-clipping optimizados para
// procesamiento en tiempo real (sin reserva de memoria dinámica).
// Incluye tanh (tangente hiperbólica) y aproximaciones para evitar llamadas
// costosas a std::tanh en el hilo de audio si es necesario, así como emulación
// de tubo (saturación asimétrica).
//
// ============================================================================

#include <cmath>
#include <algorithm>

namespace bazz_dsp {

enum class SaturationMode {
    TanhSoft,
    TanhHard,
    TubeEmulation
};

class Saturator {
private:
    SaturationMode m_mode = SaturationMode::TanhSoft;

public:
    Saturator() = default;
    ~Saturator() = default;

    void setMode(SaturationMode mode) {
        m_mode = mode;
    }

    SaturationMode getMode() const {
        return m_mode;
    }

    // Tangente hiperbólica estándar de std::math
    static inline float tanhSaturate(float x) {
        return std::tanh(x);
    }

    // Aproximación rápida de tanh (para optimizar CPU en el hilo de audio)
    static inline float fastTanh(float x) {
        if (x < -3.0f) return -1.0f;
        if (x > 3.0f) return 1.0f;
        float x2 = x * x;
        return x * (27.0f + x2) / (27.0f + 9.0f * x2);
    }

    // Procesa una muestra con ganancia (drive) aplicada antes de saturar
    inline float process(float input, float drive) {
        float x = input * drive;
        switch (m_mode) {
            case SaturationMode::TanhSoft:
                return fastTanh(x);

            case SaturationMode::TanhHard: {
                // Soft clipping que transiciona a hard clipping
                float saturated = fastTanh(x);
                return std::clamp(saturated * 1.2f, -1.0f, 1.0f);
            }

            case SaturationMode::TubeEmulation: {
                // Saturación asimétrica para emular armónicos pares de válvulas
                if (x > 0.0f) {
                    return fastTanh(x);
                } else {
                    // Menos ganancia y curva más suave en el semiciclo negativo
                    return 0.5f * fastTanh(x * 2.0f);
                }
            }
        }
        return x;
    }
};

} // namespace bazz_dsp
