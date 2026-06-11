#pragma once
#include <cmath>
#include <algorithm>

class AudioMixer {
private:
    // Estados del DC blocker para canal izquierdo
    float m_dcBlockerX_L = 0.0f;
    float m_dcBlockerY_L = 0.0f;

    // Estados del DC blocker para canal derecho
    float m_dcBlockerX_R = 0.0f;
    float m_dcBlockerY_R = 0.0f;

public:
    void reset() {
        m_dcBlockerX_L = 0.0f;
        m_dcBlockerY_L = 0.0f;
        m_dcBlockerX_R = 0.0f;
        m_dcBlockerY_R = 0.0f;
    }

    // Aplica ganancia maestra, saturación tanh y filtro DC Blocker
    void processMaster(float* bufferL, float* bufferR, int numSamples) {
        for (int i = 0; i < numSamples; ++i) {
            // 1. Ganancia maestra (* 1.5)
            float xL = bufferL[i] * 1.5f;
            float xR = bufferR[i] * 1.5f;

            // 2. Saturación analógica (tanhf)
            float satL = std::tanh(xL);
            float satR = std::tanh(xR);

            // 3. DC Blocker: y(n) = 0.995 * y(n-1) + x(n) - x(n-1)
            float yL = 0.995f * m_dcBlockerY_L + satL - m_dcBlockerX_L;
            m_dcBlockerX_L = satL;
            m_dcBlockerY_L = yL;

            float yR = 0.995f * m_dcBlockerY_R + satR - m_dcBlockerX_R;
            m_dcBlockerX_R = satR;
            m_dcBlockerY_R = yR;

            // Guardar salida final
            bufferL[i] = yL;
            bufferR[i] = yR;
        }
    }
};
