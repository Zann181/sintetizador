#pragma once

#include <atomic>
#include <mutex>
#include <chrono>
#include <cmath>
#include <cstdint>

namespace core {

class MasterClock {
public:
    MasterClock() : m_bpm(140.0f), m_externalBpm(0.0f), m_lastExternalPulseMs(0.0), m_lastStep0TimeMs(0), m_hIdx(0), m_hCount(0) {
        for(int i=0; i<16; i++) m_history[i] = 500.0;
    }

    // Llama a esto cuando se reciba un pulso de reloj externo (ej. cada cuarto de nota o beat)
    void syncPulse(double timestamp_ms) {
        if (m_lastPulseTime > 0) {
            double delta_ms = timestamp_ms - m_lastPulseTime;
            // Protección contra rebotes y ruidos
            // Para semicorcheas (1/16): 30 ms = ~500 BPM, 1000 ms = 15 BPM
            if (delta_ms > 30.0 && delta_ms < 1000.0) {
                // Ignore severe outliers (jitter spikes > 30%)
                double expected = 60000.0 / (m_bpm.load(std::memory_order_acquire) * 4.0);
                if (delta_ms > expected * 1.3 || delta_ms < expected * 0.7) {
                    // Reset history on sudden large tempo change
                    for(int i=0; i<16; i++) m_history[i] = delta_ms;
                    m_hCount = 16;
                }

                m_history[m_hIdx] = delta_ms;
                m_hIdx = (m_hIdx + 1) % 16;
                if (m_hCount < 16) m_hCount++;

                double sum = 0;
                for(int i = 0; i < m_hCount; i++) sum += m_history[i];
                double avg_delta = sum / m_hCount;
                
                float new_bpm = static_cast<float>(60000.0 / (avg_delta * 4.0));
                
                float prev = m_bpm.load(std::memory_order_acquire);
                float smoothed = prev * 0.8f + new_bpm * 0.2f;

                // Estabilizador para la UI: Redondear a 2 decimales
                smoothed = roundf(smoothed * 100.0f) / 100.0f;

                m_bpm.store(smoothed, std::memory_order_release);
                m_externalBpm.store(smoothed, std::memory_order_release);
            }
        } else {
            // Inicializar array
            double start_delta = 60000.0 / m_bpm.load();
            for(int i=0; i<16; i++) m_history[i] = start_delta;
            m_hCount = 16;
        }
        m_lastPulseTime = timestamp_ms;
        m_lastExternalPulseMs.store(timestamp_ms, std::memory_order_release);
    }

    // Set directo de BPM (por OSC o interfaz web — solo cuando NO hay reloj externo activo)
    void setBpm(float bpm) {
        if (bpm > 20.0f && bpm < 999.0f) {
            m_bpm.store(bpm, std::memory_order_release);
        }
    }

    float getBpm() const {
        return m_bpm.load(std::memory_order_acquire);
    }

    // Devuelve true si se recibió un pulso de reloj externo en los últimos 2000 ms
    bool isExternalClockActive() const {
        double last = m_lastExternalPulseMs.load(std::memory_order_acquire);
        if (last <= 0.0) return false;
        auto now = std::chrono::steady_clock::now();
        double now_ms = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count());
        return (now_ms - last) < 2000.0;
    }

    float getExternalBpm() const {
        return m_externalBpm.load(std::memory_order_acquire);
    }

    void setLastStep0TimeMs(double time_ms) {
        m_lastStep0TimeMs.store(static_cast<uint64_t>(time_ms), std::memory_order_release);
    }

    double getLastStep0TimeMs() const {
        return static_cast<double>(m_lastStep0TimeMs.load(std::memory_order_acquire));
    }

private:
    std::atomic<float>    m_bpm;
    std::atomic<float>    m_externalBpm;
    std::atomic<double>   m_lastExternalPulseMs;
    std::atomic<uint64_t> m_lastStep0TimeMs;
    double                m_lastPulseTime{0.0};

    // Historial para Moving Average (PLL)
    double m_history[16];
    int m_hIdx;
    int m_hCount;
};

} // namespace core
