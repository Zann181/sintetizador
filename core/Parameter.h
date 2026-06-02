#pragma once

#include <string>
#include <atomic>
#include <functional>
#include <vector>

namespace core {

class Parameter {
public:
    Parameter(const std::string& path, float min_val, float max_val, float init_val, const std::string& label = "")
        : m_path(path), m_min(min_val), m_max(max_val), m_value(init_val), m_label(label) {}

    // Lock-free read and write for the audio thread and OSC thread
    float getValue() const {
        return m_value.load(std::memory_order_acquire);
    }

    void setValue(float val) {
        // Clamp value
        if (val < m_min) val = m_min;
        if (val > m_max) val = m_max;
        
        m_value.store(val, std::memory_order_release);
    }

    // Path like "/kick/vol"
    const std::string& getPath() const {
        return m_path;
    }

    const std::string& getLabel() const {
        return m_label;
    }

    float getMin() const { return m_min; }
    float getMax() const { return m_max; }

private:
    std::string m_path;
    float m_min;
    float m_max;
    std::atomic<float> m_value;
    std::string m_label;
};

} // namespace core
