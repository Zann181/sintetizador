#include "Sequencer.h"

Sequencer::Sequencer() {
    clearGrid();
}

void Sequencer::setStep(int channel, int step, bool active) {
    if (channel >= 0 && channel < 6 && step >= 0 && step < 16) {
        m_stepGrids[channel][step].store(active, std::memory_order_relaxed);
    }
}

bool Sequencer::getStep(int channel, int step) const {
    if (channel >= 0 && channel < 6 && step >= 0 && step < 16) {
        return m_stepGrids[channel][step].load(std::memory_order_relaxed);
    }
    return false;
}

void Sequencer::clearGrid() {
    for (int c = 0; c < 6; ++c) {
        for (int s = 0; s < 16; ++s) {
            m_stepGrids[c][s].store(false, std::memory_order_relaxed);
        }
    }
}

bool Sequencer::isTriggerActive(int channel, int step) const {
    if (channel >= 0 && channel < 6 && step >= 0 && step < 16) {
        return m_stepGrids[channel][step].load(std::memory_order_relaxed);
    }
    return false;
}
