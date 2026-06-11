#pragma once
#include <array>
#include <atomic>

class Sequencer {
private:
    // Matriz de patrones de 6 canales x 16 pasos
    std::array<std::array<std::atomic<bool>, 16>, 6> m_stepGrids;

public:
    Sequencer();
    
    // Configura un paso del secuenciador
    void setStep(int channel, int step, bool active);
    
    // Obtiene el estado de un paso
    bool getStep(int channel, int step) const;
    
    // Limpia la grilla completa
    void clearGrid();

    // Retorna true si el canal especificado está activo en el paso actual
    bool isTriggerActive(int channel, int step) const;
};
