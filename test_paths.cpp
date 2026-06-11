#include <iostream>
#include "core/Synthesizer.h"
#include "audio/FaustUI.h"

extern "C" dsp* newmydsp();
extern "C" void deletemydsp(dsp* d);

int main() {
    core::Synthesizer synthCore;
    audio::FaustMapUI ui(&synthCore);
    
    dsp* myDsp = newmydsp();
    myDsp->buildUserInterface(&ui);
    
    auto params = synthCore.getAllParameters();
    for (const auto& pair : params) {
        std::cout << "PATH: " << pair.first << std::endl;
    }
    
    deletemydsp(myDsp);
    return 0;
}
