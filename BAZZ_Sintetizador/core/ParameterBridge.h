#pragma once
#include <atomic>
#include <string>
#include <array>
#include <cstring>
#include <vector>
#include <memory>
#include "IInstrumentVoice.h"
#include "InstrumentDescriptor.h"

struct ParamUpdate {
    char name[64];
    float value;
};

class ParameterBridge {
private:
    static constexpr size_t QUEUE_SIZE = 2048;
    std::array<ParamUpdate, QUEUE_SIZE> m_queue;
    std::atomic<size_t> m_writeIndex{0};
    std::atomic<size_t> m_readIndex{0};

public:
    // Llamado por el hilo GUI o servidor OSC
    bool pushParameter(const std::string& name, float value) {
        size_t currentWrite = m_writeIndex.load(std::memory_order_relaxed);
        size_t nextWrite = (currentWrite + 1) % QUEUE_SIZE;
        
        // Verificar si la cola está llena
        if (nextWrite == m_readIndex.load(std::memory_order_acquire)) {
            return false;
        }
        
        ParamUpdate& update = m_queue[currentWrite];
        std::strncpy(update.name, name.c_str(), 63);
        update.name[63] = '\0';
        update.value = value;
        
        m_writeIndex.store(nextWrite, std::memory_order_release);
        return true;
    }

    // Llamado al inicio del bloque de procesamiento de audio en el hilo de alta prioridad
    void dispatchUpdates(const std::vector<std::shared_ptr<IInstrumentVoice>>& voices) {
        size_t currentRead = m_readIndex.load(std::memory_order_relaxed);
        size_t writeIdx = m_writeIndex.load(std::memory_order_acquire);
        
        while (currentRead != writeIdx) {
            const ParamUpdate& update = m_queue[currentRead];
            
            uint32_t paramId = bazz::paramHash(update.name);
            
            // Distribuir el parámetro a cada una de las voces usando su ID hash
            for (const auto& voice : voices) {
                voice->setParameterById(paramId, update.value);
            }
            
            currentRead = (currentRead + 1) % QUEUE_SIZE;
        }
        
        m_readIndex.store(currentRead, std::memory_order_release);
    }
};
