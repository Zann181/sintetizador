#include "../BAZZ_Sintetizador/core/mydsp.h"
#include "../BAZZ_Sintetizador/voices/KickVoice.h"
#include "../BAZZ_Sintetizador/voices/SnareVoice.h"
#include "../BAZZ_Sintetizador/voices/HiHatVoice.h"
#include "../BAZZ_Sintetizador/voices/BassVoice.h"
#include "../BAZZ_Sintetizador/voices/PsycheVoice.h"
#include "../BAZZ_Sintetizador/voices/SiringeVoice.h"
#include "FaustUI.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

void testVoice(const std::string& name, std::shared_ptr<IInstrumentVoice> voice, const std::vector<std::pair<std::string, float>>& params) {
    voice->initialize(48000);
    voice->clearState();
    
    for (const auto& p : params) {
        voice->setParameter(p.first, p.second);
    }

    // Procesar 1 segundo de audio (48000 muestras)
    int bufferSize = 256;
    int totalSamples = 48000;
    std::vector<float> outBufferL(bufferSize, 0.0f);
    std::vector<float> outBufferR(bufferSize, 0.0f);

    long long nonZeroCount = 0;
    float maxVal = 0.0f;
    bool hasNaN = false;
    int firstNaNIndex = -1;

    // Disparar en la primera muestra
    voice->trigger(1.0f);

    for (int s = 0; s < totalSamples; s += bufferSize) {
        // Limpiar buffers
        std::fill(outBufferL.begin(), outBufferL.end(), 0.0f);
        std::fill(outBufferR.begin(), outBufferR.end(), 0.0f);

        voice->processBlock(outBufferL.data(), outBufferR.data(), bufferSize);

        for (int i = 0; i < bufferSize; ++i) {
            float valL = outBufferL[i];
            float valR = outBufferR[i];
            
            if (std::isnan(valL) || std::isnan(valR)) {
                if (!hasNaN) {
                    hasNaN = true;
                    firstNaNIndex = s + i;
                }
            } else {
                float absL = std::abs(valL);
                float absR = std::abs(valR);
                if (absL > 0.00001f || absR > 0.00001f) {
                    nonZeroCount++;
                }
                if (absL > maxVal) maxVal = absL;
                if (absR > maxVal) maxVal = absR;
            }
        }
    }

    std::cout << "Voice [" << name << "]:" << std::endl;
    std::cout << "  - Non-zero samples: " << nonZeroCount << std::endl;
    std::cout << "  - Max amplitude:    " << maxVal << std::endl;
    if (hasNaN) {
        std::cout << "  - STATUS:           HAS NAN (First at sample " << firstNaNIndex << ")" << std::endl;
    } else {
        std::cout << "  - STATUS:           OK" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Standalone Modular Voice Tester ===" << std::endl;

    // Parámetros para cada voz
    std::vector<std::pair<std::string, float>> kickParams = {
        {"/kick/vol", 0.85f}, {"/kick/accent", 0.5f}, {"/kick/tune", 0.0f},
        {"/kick/dec", 0.18f}, {"/kick/mix", 0.45f}, {"/kick/nota", 36.0f},
        {"/kick/reloj", 1.0f}, {"/kick/swing", 0.0f}, {"/kick/sweep", 150.0f},
        {"/kick/comp_fmax", 2500.0f}, {"/kick/comp_fmin", 750.0f},
        {"/kick/comp_ratio", 8.0f}, {"/kick/comp_thresh", 0.4f}, {"/kick/comp_drive", 3.5f}
    };

    std::vector<std::pair<std::string, float>> snareParams = {
        {"/snare/vol", 0.65f}, {"/snare/accent", 0.5f}, {"/snare/tune", 0.0f},
        {"/snare/dec_cuerpo", 0.07f}, {"/snare/dec_resorte", 0.16f}, {"/snare/hp", 160.0f},
        {"/snare/freq", 1650.0f}, {"/snare/mix", 0.55f}, {"/snare/nota", 36.0f},
        {"/snare/reloj", 1.0f}, {"/snare/q", 2.5f}, {"/snare/drive", 1.0f}, {"/snare/swing", 0.0f}
    };

    std::vector<std::pair<std::string, float>> hatParams = {
        {"/hat/vol", 0.45f}, {"/hat/accent", 0.5f}, {"/hat/tune", 0.0f},
        {"/hat/ataque", 0.001f}, {"/hat/dec", 0.04f}, {"/hat/cutoff", 6500.0f},
        {"/hat/mix", 0.5f}, {"/hat/nota", 36.0f}, {"/hat/reloj", 1.0f},
        {"/hat/drive", 0.35f}, {"/hat/swing", 0.0f}
    };

    std::vector<std::pair<std::string, float>> bassParams = {
        {"/bass/vol", 0.55f}, {"/bass/accent", 0.5f}, {"/bass/dec", 0.35f},
        {"/bass/detune", 0.04f}, {"/bass/lfo", 0.45f}, {"/bass/intervalo", -12.0f},
        {"/bass/nota", 36.0f}, {"/bass/reloj", 1.0f}, {"/bass/drive", 0.65f},
        {"/bass/swing", 0.0f}, {"/master/bpm", 140.0f}
    };

    std::vector<std::pair<std::string, float>> psycheParams = {
        {"/syn1/vol", 0.85f}, {"/syn1/accent", 0.5f}, {"/syn1/dec", 0.2f},
        {"/syn1/auto_v", 0.5f}, {"/syn1/auto_p", 0.7f}, {"/syn1/auto_r", 4.5f},
        {"/syn1/nota", 36.0f}, {"/syn1/reloj", 1.0f}, {"/syn1/osc1", 5.0f},
        {"/syn1/osc2", 12.0f}, {"/syn1/swing", 0.0f}
    };

    std::vector<std::pair<std::string, float>> siringeParams = {
        {"/syn2/vol", 0.22f}, {"/syn2/accent", 0.5f}, {"/syn2/dec", 0.2f},
        {"/syn2/disp", 0.5f}, {"/syn2/lfo_f", 2.0f}, {"/syn2/lfo_p", 0.5f},
        {"/syn2/nota", 12.0f}, {"/syn2/reloj", 1.0f}, {"/syn2/swing", 0.0f},
        {"/syn2/comp_a", 0.005f}, {"/syn2/comp_rel", 0.1f}, {"/syn2/comp_r", 6.0f},
        {"/syn2/comp_th", -20.0f}
    };

    testVoice("Kick", std::make_shared<KickVoice>(), kickParams);
    testVoice("Snare", std::make_shared<SnareVoice>(), snareParams);
    testVoice("HiHat", std::make_shared<HiHatVoice>(), hatParams);
    testVoice("Bass", std::make_shared<BassVoice>(), bassParams);
    testVoice("Psyche", std::make_shared<PsycheVoice>(), psycheParams);
    testVoice("Siringe", std::make_shared<SiringeVoice>(), siringeParams);

    return 0;
}
