#pragma once

#include <cstdint>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class Meta {
public:
    virtual ~Meta() {}
    virtual void declare(const char* key, const char* value) = 0;
};

class UI {
public:
    virtual ~UI() {}
    virtual void openVerticalBox(const char* label) {}
    virtual void openHorizontalBox(const char* label) {}
    virtual void closeBox() {}
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
    
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
    virtual void addToggleButton(const char* label, FAUSTFLOAT* zone) {}
};

class dsp {
public:
    virtual ~dsp() {}
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual void init(int sample_rate) = 0;
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    virtual void buildUserInterface(UI* ui_interface) = 0;
    
    // Métodos para sincronización de paso
    virtual int getCurrentStep() { return -1; }
    virtual uint64_t getLastStep0TimeMs() { return 0; }
    virtual uint64_t getLastBeatTimeMs() { return 0; }
    virtual int getLastBeatStep() { return -1; }
    virtual void setBpm(float bpm) {}
    virtual void resetSequencer() {}
    virtual void alignToBeat() {}
};
