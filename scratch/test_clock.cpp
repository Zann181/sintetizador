#include "../BAZZ_Sintetizador/sequencer/Clock.h"
#include <iostream>

int main() {
    Clock clock;
    clock.initialize(48000);
    clock.setBpm(120.0f);
    clock.setSwing(75.0f); // 75% swing

    std::cout << "--- Testing Clock with 75% Swing ---" << std::endl;
    int step = 0;
    int triggerCount = 0;

    // Process 48000 * 2 samples (2 seconds of audio)
    for (int i = 0; i < 96000; ++i) {
        float triggerAmp = clock.processSample(1.0f, 0.5f, step);
        if (triggerAmp > 0.0f) {
            std::cout << "Sample " << i << ": Triggered step " << step << " with amplitude " << triggerAmp << std::endl;
            triggerCount++;
        }
    }
    std::cout << "Total triggers: " << triggerCount << std::endl;
    return 0;
}
