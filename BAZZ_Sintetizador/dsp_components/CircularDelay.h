#pragma once
// ============================================================================
// CircularDelay.h — Buffer circular de retardo para BAZZ Sintetizador
// ============================================================================
//
// Buffer de retardo circular con máscara de potencia de 2, sin asignación
// dinámica de memoria. Reemplaza los patrones repetitivos de Faust como:
//
//   std::array<float, 512> fRec64;
//   fRec64[IOTA0 & 511] = valor;                       // escritura
//   float x = fRec64[(IOTA0 - delay) & 511];           // lectura entera
//   float y = frac * fRec36[(IOTA0 - i1) & 8191]       // lectura interpolada
//           + (1-frac) * fRec36[(IOTA0 - i2) & 8191];
//
// Uso típico:
//   bazz_dsp::CircularDelay<512> delay;   // 512 muestras (potencia de 2)
//   delay.write(input);
//   float out = delay.read(348);          // lectura con retardo fijo
//   float out2 = delay.readInterpolated(347.5f); // retardo fraccional
//   delay.advance();  // avanzar el índice (llamar una vez por muestra)
//
// Para el patrón FDN del Kick (4 delays compartiendo IOTA0):
//   bazz_dsp::CircularDelayGroup<4> fdn;
//   fdn.delay<0>().configure<512>();  // etc.
//   // O simplemente usar 4 CircularDelay separados con advance() manual.
//
// Dependencias: <array>, <cmath>, <cstdint>, <algorithm>
// Sin asignación dinámica de memoria. Seguro para tiempo real.
// ============================================================================

#include <array>
#include <cmath>
#include <cstdint>
#include <algorithm>

namespace bazz_dsp {

// ──────────────────────────────────────────────────────────────────────────────
// Utilidad: verificar que un valor es potencia de 2 en tiempo de compilación
// ──────────────────────────────────────────────────────────────────────────────
namespace detail {
    constexpr bool isPowerOf2(int v) { return v > 0 && (v & (v - 1)) == 0; }
} // namespace detail

// ──────────────────────────────────────────────────────────────────────────────
// CircularDelay<MaxSize> — Buffer circular con máscara de potencia de 2
// ──────────────────────────────────────────────────────────────────────────────
//
// MaxSize DEBE ser potencia de 2 (256, 512, 1024, 2048, 4096, 8192...).
// Esto permite usar operación AND bit a bit en lugar de módulo, que es
// significativamente más rápido en el inner loop de audio.
//
// Patrón Faust equivalente:
//   std::array<float, MaxSize> fRec;
//   int IOTA0 = 0;
//   fRec[IOTA0 & (MaxSize-1)] = x;              // write
//   float y = fRec[(IOTA0 - delay) & (MaxSize-1)]; // read
//   IOTA0 = IOTA0 + 1;                           // advance
//
// La máscara es (MaxSize - 1), ej: 511 para MaxSize=512.
//
// IMPORTANTE: El orden de operaciones por muestra debe ser:
//   1. Leer valores anteriores con read() / readInterpolated()
//   2. Escribir nuevo valor con write()
//   3. Avanzar índice con advance()
//   (O usar writeThenAdvance() para combinar pasos 2 y 3)
//
// Nota sobre el patrón FDN:
// En el FDN del Kick, varios delays comparten el mismo IOTA0.
// Puedes replicar esto usando advance() manualmente en cada delay,
// o usando el método estático advanceSharedIndex() con un IOTA externo.
// ──────────────────────────────────────────────────────────────────────────────
template<int MaxSize>
class CircularDelay {
    static_assert(detail::isPowerOf2(MaxSize),
        "MaxSize debe ser potencia de 2 (256, 512, 1024, 2048, 4096, 8192...)");
    static_assert(MaxSize >= 4,
        "MaxSize minimo es 4 muestras");

public:
    // Constante de máscara expuesta para uso externo (ej: patrón Faust directo)
    static constexpr int kMask = MaxSize - 1;
    static constexpr int kSize = MaxSize;

    CircularDelay() { reset(); }

    // ────────────────────────────────────────────────────────────────────────
    // reset() — Limpia todo el buffer y reinicia el índice de escritura
    // ────────────────────────────────────────────────────────────────────────
    void reset() {
        m_buffer.fill(0.0f);
        m_writeIndex = 0;
    }

    // ────────────────────────────────────────────────────────────────────────
    // write() — Escribe un valor en la posición actual del buffer
    // ────────────────────────────────────────────────────────────────────────
    // Equivalente Faust: fRec64[IOTA0 & 511] = valor;
    // NO avanza el índice — llamar advance() después.
    inline void write(float value) {
        m_buffer[m_writeIndex & kMask] = value;
    }

    // ────────────────────────────────────────────────────────────────────────
    // writeThenAdvance() — Escribe y avanza el índice en un solo paso
    // ────────────────────────────────────────────────────────────────────────
    // Combina write() + advance() para casos simples (un solo delay).
    inline void writeThenAdvance(float value) {
        m_buffer[m_writeIndex & kMask] = value;
        ++m_writeIndex;
    }

    // ────────────────────────────────────────────────────────────────────────
    // read() — Lee un valor con retardo entero en muestras
    // ────────────────────────────────────────────────────────────────────────
    // Parámetros:
    //   delaySamples — Número de muestras de retardo (0 = muestra actual)
    //
    // Equivalente Faust: fRec64[(IOTA0 - delay) & 511]
    //
    // CUIDADO: delaySamples debe ser < MaxSize, no se verifica en release.
    inline float read(int delaySamples) const {
        return m_buffer[(m_writeIndex - delaySamples) & kMask];
    }

    // ────────────────────────────────────────────────────────────────────────
    // readInterpolated() — Lee con retardo fraccional (interpolación lineal)
    // ────────────────────────────────────────────────────────────────────────
    // Parámetros:
    //   delaySamples — Retardo en muestras (puede ser fraccionario)
    //
    // Equivalente Faust (BassVoice waveguide):
    //   fSlow113 * fRec36[(IOTA0 - iSlow112) & 8191]
    // + fSlow111 * fRec36[(IOTA0 - iSlow109) & 8191]
    //
    // Usa interpolación lineal entre las dos muestras adyacentes.
    // Para la guía de ondas del BassVoice, esto es exactamente el patrón
    // de retardo fraccional que permite afinación precisa sub-muestra.
    inline float readInterpolated(float delaySamples) const {
        const int intDelay = static_cast<int>(delaySamples);
        const float frac = delaySamples - static_cast<float>(intDelay);

        const float s0 = m_buffer[(m_writeIndex - intDelay) & kMask];
        const float s1 = m_buffer[(m_writeIndex - intDelay - 1) & kMask];

        // Interpolación lineal: (1-frac)*s0 + frac*s1
        return s0 + frac * (s1 - s0);
    }

    // ────────────────────────────────────────────────────────────────────────
    // readCubic() — Lee con retardo fraccional (interpolación cúbica)
    // ────────────────────────────────────────────────────────────────────────
    // Mayor calidad que lineal, útil para efectos de pitch-shift y chorus.
    // Usa 4 puntos para interpolar con un polinomio de Hermite.
    inline float readCubic(float delaySamples) const {
        const int d = static_cast<int>(delaySamples);
        const float f = delaySamples - static_cast<float>(d);

        const float y0 = m_buffer[(m_writeIndex - d + 1) & kMask];
        const float y1 = m_buffer[(m_writeIndex - d)     & kMask];
        const float y2 = m_buffer[(m_writeIndex - d - 1) & kMask];
        const float y3 = m_buffer[(m_writeIndex - d - 2) & kMask];

        // Hermite interpolación cúbica
        const float c0 = y1;
        const float c1 = 0.5f * (y2 - y0);
        const float c2 = y0 - 2.5f * y1 + 2.0f * y2 - 0.5f * y3;
        const float c3 = 0.5f * (y3 - y0) + 1.5f * (y1 - y2);

        return ((c3 * f + c2) * f + c1) * f + c0;
    }

    // ────────────────────────────────────────────────────────────────────────
    // readTwoTap() — Lee y suma dos taps adyacentes (patrón FDN)
    // ────────────────────────────────────────────────────────────────────────
    // Equivalente Faust (patrón de lectura del Rumble FDN del Kick):
    //   fRec64[(IOTA0 - 348) & 511] + fRec64[(IOTA0 - 349) & 511]
    //
    // Esto se usa en el FDN para suavizar la realimentación entre canales.
    inline float readTwoTap(int delaySamples) const {
        return m_buffer[(m_writeIndex - delaySamples) & kMask]
             + m_buffer[(m_writeIndex - delaySamples - 1) & kMask];
    }

    // ────────────────────────────────────────────────────────────────────────
    // advance() — Avanza el índice de escritura
    // ────────────────────────────────────────────────────────────────────────
    // Equivalente Faust: IOTA0 = IOTA0 + 1;
    // Llamar exactamente UNA vez por muestra, DESPUÉS de write() y read().
    inline void advance() {
        ++m_writeIndex;
    }

    // ────────────────────────────────────────────────────────────────────────
    // Acceso directo al buffer — para patrones Faust más complejos
    // ────────────────────────────────────────────────────────────────────────

    // Acceso al índice actual (equivalente a IOTA0)
    int getWriteIndex() const { return m_writeIndex; }

    // Establecer índice externo (para sincronizar múltiples delays en FDN)
    void setWriteIndex(int idx) { m_writeIndex = idx; }

    // Acceso directo al buffer interno (lectura con índice y máscara)
    // Equivalente: fRec64[index & 511]
    inline float& operator[](int maskedIndex) {
        return m_buffer[maskedIndex & kMask];
    }
    inline float operator[](int maskedIndex) const {
        return m_buffer[maskedIndex & kMask];
    }

    // Referencia al array interno (para llenar con fill(), etc.)
    std::array<float, MaxSize>& buffer() { return m_buffer; }
    const std::array<float, MaxSize>& buffer() const { return m_buffer; }

private:
    std::array<float, MaxSize> m_buffer;
    int m_writeIndex = 0;
};

// ──────────────────────────────────────────────────────────────────────────────
// Aliases de tamaños comunes usados en el proyecto
// ──────────────────────────────────────────────────────────────────────────────
// KickVoice FDN:     fRec64/65 = 512,  fRec66/67 = 1024
// KickVoice DCBlock: fVec31/32 = 256
// SiringeVoice FDN:  fRec18/19/20 = 2048,  fRec21 = 4096
// BassVoice WG:      fRec36 = 8192
using Delay256  = CircularDelay<256>;
using Delay512  = CircularDelay<512>;
using Delay1024 = CircularDelay<1024>;
using Delay2048 = CircularDelay<2048>;
using Delay4096 = CircularDelay<4096>;
using Delay8192 = CircularDelay<8192>;

} // namespace bazz_dsp
