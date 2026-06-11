#include "../BAZZ_Sintetizador/core/mydsp.h"
#include <iostream>
#include <vector>

int main() {
    mydsp dsp;
    dsp.init(48000);

    // Turn on step 0 and step 1 for all instruments in the checkboxes
    // Kick: fCheckbox[80...95]
    // Snare: fCheckbox[64...79]
    // Hat: fCheckbox[48...63]
    // Bass: fCheckbox[32...47]
    // Syn1: fCheckbox[0...15]
    // Syn2: fCheckbox[16...31]
    
    // Let's set step 0 (button 1) and step 1 (button 2) to active
    dsp.fCheckbox[80 + 0] = 1.0f; dsp.fCheckbox[80 + 1] = 1.0f; // Kick
    dsp.fCheckbox[64 + 0] = 1.0f; dsp.fCheckbox[64 + 1] = 1.0f; // Snare
    dsp.fCheckbox[48 + 0] = 1.0f; dsp.fCheckbox[48 + 1] = 1.0f; // Hat
    dsp.fCheckbox[32 + 0] = 1.0f; dsp.fCheckbox[32 + 1] = 1.0f; // Bass
    dsp.fCheckbox[0 + 0]  = 1.0f; dsp.fCheckbox[0 + 1]  = 1.0f; // Syn1
    dsp.fCheckbox[16 + 0] = 1.0f; dsp.fCheckbox[16 + 1] = 1.0f; // Syn2

    // Set swing for Hat to 75, Bass to 0.75, Kick/Snare to 0
    dsp.fHslider[45] = 75.0f;  // Hat swing
    dsp.fHslider[28] = 0.75f;  // Bass swing
    dsp.fHslider[68] = 0.0f;   // Kick swing
    dsp.fHslider[52] = 0.0f;   // Snare swing
    dsp.fHslider[3]  = 56.0f;   // Syn1 swing
    dsp.fHslider[18] = 56.0f;   // Syn2 swing

    // Process a block of audio (say 15000 samples, which is 2.5 steps at 120 BPM)
    int count = 15000;
    std::vector<float> outL(count, 0.0f);
    std::vector<float> outR(count, 0.0f);
    float* outputs[2] = { outL.data(), outR.data() };

    std::cout << "Starting compute loop..." << std::endl;
    dsp.compute(count, nullptr, outputs);
    std::cout << "Compute finished successfully!" << std::endl;

    return 0;
}
