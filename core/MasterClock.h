#pragma once

#include <atomic>
#include <mutex>
#include <chrono>

namespace core {

class MasterClock {
public:
    MasterClock() : m_bpm(140.0f), m_externalBpm(0.0f), m_lastExternalPulseMs(0.0) {}

    // Llama a esto cuando se reciba un pulso de reloj externo (ej. cada cuarto de nota o beat)
    void syncPulse(double timestamp_ms) {
        if (m_lastPulseTime > 0) {
            double delta_ms = timestamp_ms - m_lastPulseTime;
            if (delta_ms > 10.0 && delta_ms < 3000.0) {
                // 1 pulso = 1 cuarto de nota (beat): BPM = 60000 / delta_ms
                float new_bpm = static_cast<float>(60000.0 / delta_ms);
                // Suavizado exponencial (LPF)
                float prev = m_bpm.load(std::memory_order_acquire);
                float smoothed = prev * 0.7f + new_bpm * 0.3f;
                m_bpm.store(smoothed, std::memory_order_release);
                m_externalBpm.store(smoothed, std::memory_order_release);
            }
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

private:
    std::atomic<float>  m_bpm;
    std::atomic<float>  m_externalBpm;
    std::atomic<double> m_lastExternalPulseMs;
    double              m_lastPulseTime{0.0};
};

} // namespace core
