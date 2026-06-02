#pragma once

#include "../core/Synthesizer.h"
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>

namespace state {

struct AutomationEvent {
    long long timestamp_ms;
    std::shared_ptr<core::Parameter> param;
    float value;
};

class AutomationRecorder {
public:
    AutomationRecorder(core::Synthesizer* synth) : m_synth(synth), m_state(STOPPED) {}

    ~AutomationRecorder() {
        stop();
        if (m_playbackThread.joinable()) {
            m_playbackThread.join();
        }
    }

    void recordEvent(const std::string& path, float value) {
        if (m_state.load() != RECORDING) return;
        
        auto param = m_synth->getParameter(path);
        if (param) {
            auto now = std::chrono::steady_clock::now();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_recordStartTime).count();
            
            AutomationEvent ev;
            ev.timestamp_ms = ms;
            ev.param = param;
            ev.value = value;
            
            std::lock_guard<std::mutex> lock(m_eventsMutex);
            m_events.push_back(ev);
            param->setValue(value);
        }
    }

    void startRecording() {
        stop();
        {
            std::lock_guard<std::mutex> lock(m_eventsMutex);
            m_events.clear();
        }
        m_recordStartTime = std::chrono::steady_clock::now();
        m_state.store(RECORDING);
    }

    void startPlayback() {
        stop();
        if (m_playbackThread.joinable()) {
            m_playbackThread.join();
        }
        m_state.store(PLAYING);
        m_playbackThread = std::thread(&AutomationRecorder::playbackLoop, this);
    }

    void stop() {
        m_state.store(STOPPED);
    }

private:
    void playbackLoop() {
        auto playStartTime = std::chrono::steady_clock::now();
        size_t index = 0;
        
        while (m_state.load() == PLAYING) {
            long long current_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - playStartTime).count();
            
            bool eventProcessed = false;
            {
                std::lock_guard<std::mutex> lock(m_eventsMutex);
                if (index < m_events.size()) {
                    if (current_ms >= m_events[index].timestamp_ms) {
                        m_events[index].param->setValue(m_events[index].value);
                        index++;
                        eventProcessed = true;
                    }
                } else {
                    // Loop or stop
                    index = 0;
                    playStartTime = std::chrono::steady_clock::now();
                    continue; // Loop infinito por defecto
                }
            }
            
            if (!eventProcessed) {
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
        }
    }

    enum State { STOPPED, RECORDING, PLAYING };
    
    core::Synthesizer* m_synth;
    std::atomic<State> m_state;
    std::vector<AutomationEvent> m_events;
    std::mutex m_eventsMutex;
    std::chrono::steady_clock::time_point m_recordStartTime;
    std::thread m_playbackThread;
};

} // namespace state
