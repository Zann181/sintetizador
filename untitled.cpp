/* ------------------------------------------------------------
license: "MIT"
name: "untitled", "TR_808_Algorithmic_Techno_Station"
Code generated with Faust 2.85.5 (https://faust.grame.fr)
Compilation options: -lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
#include <chrono>
#include <atomic>
#include "core/FaustDefs.h"
#include "audio/FaustUI.h"

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

class mydspSIG0 {
	
  private:
	
	int iVec3[2];
	int iRec6[2];
	int fSampleRate;
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		fSampleRate = sample_rate;
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iVec3[l6] = 0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec6[l7] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec3[0] = 1;
			iRec6[0] = (iVec3[1] + iRec6[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec6[0]));
			iVec3[1] = iVec3[0];
			iRec6[1] = iRec6[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float mydsp_faustpower2_f(float value) {
	return value * value;
}
static float ftbl0mydspSIG0[65536];

class mydsp : public dsp {
	
 public:
	std::atomic<uint64_t> m_lastStep0TimeMs{0};
	std::atomic<uint64_t> m_lastBeatTimeMs{0};
	std::atomic<int> m_lastBeatStep{-1};
	std::atomic<bool> m_pendingReset{false};
	
 private:
	
	int iVec0[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fConst13;
	float fRec4[2];
	int IOTA0;
	int iVec1[32768];
	int iRec3[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fCheckbox4;
	FAUSTFLOAT fCheckbox5;
	FAUSTFLOAT fCheckbox6;
	FAUSTFLOAT fCheckbox7;
	FAUSTFLOAT fCheckbox8;
	FAUSTFLOAT fCheckbox9;
	FAUSTFLOAT fCheckbox10;
	FAUSTFLOAT fCheckbox11;
	FAUSTFLOAT fCheckbox12;
	FAUSTFLOAT fCheckbox13;
	FAUSTFLOAT fCheckbox14;
	FAUSTFLOAT fCheckbox15;
	FAUSTFLOAT fHslider3;
	float fConst14;
	int iVec2[2];
	int iRec5[2];
	float fConst15;
	float fConst16;
	FAUSTFLOAT fHslider4;
	float fConst17;
	float fRec7[2];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fConst18;
	float fRec8[2];
	float fVec4[2];
	float fVec5[2048];
	float fConst19;
	float fConst20;
	float fRec11[2];
	FAUSTFLOAT fHslider7;
	float fRec9[2];
	float fRec2[3];
	float fConst21;
	float fRec1[3];
	float fVec6[256];
	FAUSTFLOAT fHslider8;
	float fRec12[2];
	FAUSTFLOAT fHslider9;
	FAUSTFLOAT fHslider10;
	float fConst22;
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	float fRec17[2];
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHslider15;
	FAUSTFLOAT fHslider16;
	float fRec24[2];
	int iVec7[32768];
	int iRec23[2];
	FAUSTFLOAT fHslider17;
	FAUSTFLOAT fCheckbox16;
	FAUSTFLOAT fCheckbox17;
	FAUSTFLOAT fCheckbox18;
	FAUSTFLOAT fCheckbox19;
	FAUSTFLOAT fCheckbox20;
	FAUSTFLOAT fCheckbox21;
	FAUSTFLOAT fCheckbox22;
	FAUSTFLOAT fCheckbox23;
	FAUSTFLOAT fCheckbox24;
	FAUSTFLOAT fCheckbox25;
	FAUSTFLOAT fCheckbox26;
	FAUSTFLOAT fCheckbox27;
	FAUSTFLOAT fCheckbox28;
	FAUSTFLOAT fCheckbox29;
	FAUSTFLOAT fCheckbox30;
	FAUSTFLOAT fCheckbox31;
	FAUSTFLOAT fHslider18;
	int iVec8[2];
	int iRec25[2];
	FAUSTFLOAT fHslider19;
	FAUSTFLOAT fHslider20;
	FAUSTFLOAT fHslider21;
	float fRec22[2];
	float fConst34;
	float fConst35;
	float fConst36;
	float fRec26[2];
	float fRec27[2];
	float fRec28[2];
	float fRec29[2];
	FAUSTFLOAT fHslider22;
	float fRec18[2048];
	float fRec19[2048];
	float fRec20[2048];
	float fRec21[4096];
	FAUSTFLOAT fHslider23;
	float fRec16[2];
	FAUSTFLOAT fHslider24;
	float fRec15[2];
	float fRec14[3];
	float fConst37;
	float fRec13[3];
	FAUSTFLOAT fHslider25;
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	FAUSTFLOAT fHslider26;
	FAUSTFLOAT fHslider27;
	float fRec35[2];
	int iVec9[32768];
	int iRec34[2];
	FAUSTFLOAT fCheckbox32;
	FAUSTFLOAT fCheckbox33;
	FAUSTFLOAT fCheckbox34;
	FAUSTFLOAT fCheckbox35;
	FAUSTFLOAT fCheckbox36;
	FAUSTFLOAT fCheckbox37;
	FAUSTFLOAT fCheckbox38;
	FAUSTFLOAT fCheckbox39;
	FAUSTFLOAT fCheckbox40;
	FAUSTFLOAT fCheckbox41;
	FAUSTFLOAT fCheckbox42;
	FAUSTFLOAT fCheckbox43;
	FAUSTFLOAT fCheckbox44;
	FAUSTFLOAT fCheckbox45;
	FAUSTFLOAT fCheckbox46;
	FAUSTFLOAT fCheckbox47;
	FAUSTFLOAT fHslider28;
	int iVec10[2];
	float fRec33[2];
	FAUSTFLOAT fHslider29;
	float fConst51;
	float fRec32[2];
	FAUSTFLOAT fHslider30;
	int iRec37[2];
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	int iRec39[2];
	float fVec11[2];
	float fConst57;
	float fRec38[2];
	FAUSTFLOAT fHslider31;
	FAUSTFLOAT fHslider32;
	FAUSTFLOAT fHslider33;
	float fConst58;
	float fConst59;
	float fRec41[2];
	FAUSTFLOAT fHslider34;
	float fRec40[2];
	FAUSTFLOAT fHslider35;
	float fRec36[8192];
	float fRec31[3];
	float fConst60;
	float fRec30[3];
	FAUSTFLOAT fHslider36;
	FAUSTFLOAT fHslider37;
	float fConst61;
	FAUSTFLOAT fHslider38;
	FAUSTFLOAT fHslider39;
	FAUSTFLOAT fHslider40;
	float fRec43[2];
	float fVec12[2];
	float fConst62;
	float fVec13[128];
	float fRec44[2];
	float fVec14[2];
	float fVec15[128];
	float fRec45[2];
	float fVec16[2];
	float fVec17[128];
	float fRec46[2];
	float fVec18[2];
	float fVec19[256];
	float fRec47[2];
	float fVec20[2];
	float fVec21[256];
	float fRec48[2];
	float fVec22[2];
	float fVec23[512];
	FAUSTFLOAT fHslider41;
	FAUSTFLOAT fHslider42;
	FAUSTFLOAT fHslider43;
	float fRec50[2];
	int iVec24[32768];
	int iRec49[2];
	FAUSTFLOAT fHslider44;
	FAUSTFLOAT fCheckbox48;
	FAUSTFLOAT fCheckbox49;
	FAUSTFLOAT fCheckbox50;
	FAUSTFLOAT fCheckbox51;
	FAUSTFLOAT fCheckbox52;
	FAUSTFLOAT fCheckbox53;
	FAUSTFLOAT fCheckbox54;
	FAUSTFLOAT fCheckbox55;
	FAUSTFLOAT fCheckbox56;
	FAUSTFLOAT fCheckbox57;
	FAUSTFLOAT fCheckbox58;
	FAUSTFLOAT fCheckbox59;
	FAUSTFLOAT fCheckbox60;
	FAUSTFLOAT fCheckbox61;
	FAUSTFLOAT fCheckbox62;
	FAUSTFLOAT fCheckbox63;
	FAUSTFLOAT fHslider45;
	int iVec25[2];
	int iRec51[2];
	FAUSTFLOAT fHslider46;
	FAUSTFLOAT fHslider47;
	float fRec42[3];
	FAUSTFLOAT fHslider48;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	FAUSTFLOAT fHslider49;
	FAUSTFLOAT fHslider50;
	FAUSTFLOAT fHslider51;
	float fRec56[2];
	int iVec26[32768];
	int iRec55[2];
	FAUSTFLOAT fCheckbox64;
	FAUSTFLOAT fCheckbox65;
	FAUSTFLOAT fCheckbox66;
	FAUSTFLOAT fCheckbox67;
	FAUSTFLOAT fCheckbox68;
	FAUSTFLOAT fCheckbox69;
	FAUSTFLOAT fCheckbox70;
	FAUSTFLOAT fCheckbox71;
	FAUSTFLOAT fCheckbox72;
	FAUSTFLOAT fCheckbox73;
	FAUSTFLOAT fCheckbox74;
	FAUSTFLOAT fCheckbox75;
	FAUSTFLOAT fCheckbox76;
	FAUSTFLOAT fCheckbox77;
	FAUSTFLOAT fCheckbox78;
	FAUSTFLOAT fCheckbox79;
	FAUSTFLOAT fHslider52;
	int iVec27[2];
	int iRec54[2];
	FAUSTFLOAT fHslider53;
	FAUSTFLOAT fHslider54;
	FAUSTFLOAT fHslider55;
	float fRec57[3];
	FAUSTFLOAT fHslider56;
	float fConst68;
	float fConst69;
	FAUSTFLOAT fHslider57;
	FAUSTFLOAT fHslider58;
	FAUSTFLOAT fHslider59;
	float fConst70;
	float fRec58[2];
	float fConst71;
	float fRec59[2];
	FAUSTFLOAT fHslider60;
	FAUSTFLOAT fHslider61;
	float fRec53[3];
	float fRec52[3];
	FAUSTFLOAT fHslider62;
	float fConst72;
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fConst80;
	float fConst81;
	FAUSTFLOAT fHslider63;
	FAUSTFLOAT fHslider64;
	float fConst82;
	FAUSTFLOAT fHslider65;
	FAUSTFLOAT fHslider66;
	float fRec75[2];
	int iVec28[32768];
	int iRec74[2];
	FAUSTFLOAT fHslider67;
	FAUSTFLOAT fCheckbox80;
	FAUSTFLOAT fCheckbox81;
	FAUSTFLOAT fCheckbox82;
	FAUSTFLOAT fCheckbox83;
	FAUSTFLOAT fCheckbox84;
	FAUSTFLOAT fCheckbox85;
	FAUSTFLOAT fCheckbox86;
	FAUSTFLOAT fCheckbox87;
	FAUSTFLOAT fCheckbox88;
	FAUSTFLOAT fCheckbox89;
	FAUSTFLOAT fCheckbox90;
	FAUSTFLOAT fCheckbox91;
	FAUSTFLOAT fCheckbox92;
	FAUSTFLOAT fCheckbox93;
	FAUSTFLOAT fCheckbox94;
	FAUSTFLOAT fCheckbox95;
	FAUSTFLOAT fHslider68;
	int iVec29[2];
	int iRec76[2];
	FAUSTFLOAT fHslider69;
	FAUSTFLOAT fHslider70;
	FAUSTFLOAT fHslider71;
	FAUSTFLOAT fHslider72;
	float fRec77[2];
	float fConst83;
	float fRec73[2];
	FAUSTFLOAT fHslider73;
	FAUSTFLOAT fHslider74;
	FAUSTFLOAT fHslider75;
	float fVec30[2];
	float fRec72[2];
	float fRec71[3];
	float fRec70[3];
	float fRec69[3];
	float fRec68[3];
	float fConst84;
	float fConst85;
	float fRec78[2];
	float fRec79[2];
	float fRec80[2];
	float fRec81[2];
	float fRec64[512];
	float fRec65[512];
	float fRec66[1024];
	float fRec67[1024];
	float fVec31[256];
	float fRec62[2];
	float fVec32[256];
	float fRec60[2];
	FAUSTFLOAT fHslider76;
	FAUSTFLOAT fHslider77;
	float fVec33[2];
	float fRec0[2];
	FAUSTFLOAT fHslider78;
	float fRec83[3];
	float fVec34[2];
	float fRec82[2];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = delete;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = delete;
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/amp_follower_ar:author", "Jonatan Liljedahl, revised by Romain Michon");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/selectbus:author", "David Braun");
		m->declare("basics.lib/selectbus:license", "MIT");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -fpga-mem-th 4 -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("compressors.lib/compression_gain_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compression_gain_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compression_gain_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_lad_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_lad_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_lad_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "1.6.0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("description", "Estación de Ritmo Techno Avanzada con Estructura Modular Completa y Control Dinámico Total");
		m->declare("envelopes.lib/ar:author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("filename", "untitled.dsp");
		m->declare("filters.lib/allpass_comb:author", "Julius O. Smith III");
		m->declare("filters.lib/allpass_comb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/allpass_comb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/dcblocker:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblocker:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblocker:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonbp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonbp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonbp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("license", "MIT");
		m->declare("linearalgebra.lib/matMul:author", "David Braun");
		m->declare("linearalgebra.lib/matMul:copyright", "MIT License");
		m->declare("linearalgebra.lib/name", "Faust Linear Algebra Library");
		m->declare("linearalgebra.lib/transpose2:author", "David Braun");
		m->declare("linearalgebra.lib/transpose2:copyright", "MIT License");
		m->declare("linearalgebra.lib/version", "0.1.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "untitled");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "1.5.0");
		m->declare("oscillators.lib/lf_sawpos:author", "Bart Brouns, revised by Stéphane Letz");
		m->declare("oscillators.lib/lf_sawpos:licence", "STK-4.3");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/saw2ptr:author", "Julius O. Smith III");
		m->declare("oscillators.lib/saw2ptr:license", "STK-4.3");
		m->declare("oscillators.lib/sawN:author", "Julius O. Smith III");
		m->declare("oscillators.lib/sawN:license", "STK-4.3");
		m->declare("oscillators.lib/version", "1.7.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Routing Library");
		m->declare("signals.lib/onePoleSwitching:author", "Jonatan Liljedahl, revised by Dario Sanfilippo");
		m->declare("signals.lib/onePoleSwitching:licence", "STK-4.3");
		m->declare("signals.lib/version", "1.6.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = std::tan(6283.1855f / fConst0);
		fConst2 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst1));
		fConst3 = 1.0f / fConst1;
		fConst4 = (fConst3 + -1.4142135f) / fConst1 + 1.0f;
		fConst5 = 1.0f / ((fConst3 + 1.4142135f) / fConst1 + 1.0f);
		fConst6 = std::tan(188.49556f / fConst0);
		fConst7 = mydsp_faustpower2_f(fConst6);
		fConst8 = 2.0f * (1.0f - 1.0f / fConst7);
		fConst9 = 1.0f / fConst6;
		fConst10 = (fConst9 + -1.4142135f) / fConst6 + 1.0f;
		fConst11 = (fConst9 + 1.4142135f) / fConst6 + 1.0f;
		fConst12 = 1.0f / fConst11;
		fConst13 = 0.06666667f / fConst0;
		fConst14 = 0.075f * fConst0;
		fConst15 = std::max<float>(1.0f, 0.05f * fConst0);
		fConst16 = 1.0f / fConst15;
		fConst17 = 0.3f / fConst0;
		fConst18 = 1.0f / fConst0;
		fConst19 = 0.5f * fConst0;
		fConst20 = 0.08f / fConst0;
		fConst21 = 1.0f / (fConst7 * fConst11);
		fConst22 = std::tan(20420.352f / fConst0);
		fConst23 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst22));
		fConst24 = 1.0f / fConst22;
		fConst25 = (fConst24 + -1.4142135f) / fConst22 + 1.0f;
		fConst26 = 1.0f / ((fConst24 + 1.4142135f) / fConst22 + 1.0f);
		fConst27 = std::tan(471.2389f / fConst0);
		fConst28 = mydsp_faustpower2_f(fConst27);
		fConst29 = 2.0f * (1.0f - 1.0f / fConst28);
		fConst30 = 1.0f / fConst27;
		fConst31 = (fConst30 + -1.4142135f) / fConst27 + 1.0f;
		fConst32 = (fConst30 + 1.4142135f) / fConst27 + 1.0f;
		fConst33 = 1.0f / fConst32;
		fConst34 = 1.0f / std::tan(10995.574f / fConst0);
		fConst35 = 1.0f - fConst34;
		fConst36 = 1.0f / (fConst34 + 1.0f);
		fConst37 = 1.0f / (fConst28 * fConst32);
		fConst38 = std::tan(2513.2742f / fConst0);
		fConst39 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst38));
		fConst40 = 1.0f / fConst38;
		fConst41 = (fConst40 + -1.4142135f) / fConst38 + 1.0f;
		fConst42 = 1.0f / ((fConst40 + 1.4142135f) / fConst38 + 1.0f);
		fConst43 = std::tan(62.831852f / fConst0);
		fConst44 = mydsp_faustpower2_f(fConst43);
		fConst45 = 2.0f * (1.0f - 1.0f / fConst44);
		fConst46 = 1.0f / fConst43;
		fConst47 = (fConst46 + -1.4142135f) / fConst43 + 1.0f;
		fConst48 = (fConst46 + 1.4142135f) / fConst43 + 1.0f;
		fConst49 = 1.0f / fConst48;
		fConst50 = std::exp(-(2e+02f / fConst0));
		fConst51 = 1.0f - fConst50;
		fConst52 = std::max<float>(1.0f, 0.001f * fConst0);
		fConst53 = 1.0f / fConst52;
		fConst54 = 1.0f / std::max<float>(1.0f, 0.18f * fConst0);
		fConst55 = 1.0f / std::tan(4712.389f / fConst0);
		fConst56 = 1.0f - fConst55;
		fConst57 = 1.0f / (fConst55 + 1.0f);
		fConst58 = 0.0022727272f * fConst0;
		fConst59 = 3.0f / fConst0;
		fConst60 = 1.0f / (fConst44 * fConst48);
		fConst61 = 3.1415927f / fConst0;
		fConst62 = 0.25f * fConst0;
		fConst63 = std::tan(28274.334f / fConst0);
		fConst64 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst63));
		fConst65 = 1.0f / fConst63;
		fConst66 = (fConst65 + -1.4142135f) / fConst63 + 1.0f;
		fConst67 = 1.0f / ((fConst65 + 1.4142135f) / fConst63 + 1.0f);
		fConst68 = std::max<float>(1.0f, 0.0005f * fConst0);
		fConst69 = 1.0f / fConst68;
		fConst70 = 2233.421f / fConst0;
		fConst71 = 1210.8909f / fConst0;
		fConst72 = std::tan(3769.9111f / fConst0);
		fConst73 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst72));
		fConst74 = 1.0f / fConst72;
		fConst75 = (fConst74 + -1.4142135f) / fConst72 + 1.0f;
		fConst76 = 1.0f / ((fConst74 + 1.4142135f) / fConst72 + 1.0f);
		fConst77 = std::tan(7853.9814f / fConst0);
		fConst78 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst77));
		fConst79 = 1.0f / fConst77;
		fConst80 = (fConst79 + -1.4142135f) / fConst77 + 1.0f;
		fConst81 = 1.0f / ((fConst79 + 1.4142135f) / fConst77 + 1.0f);
		fConst82 = std::exp(-(1e+02f / fConst0));
		fConst83 = 1.0f - fConst82;
		fConst84 = 1.0f - fConst3;
		fConst85 = 1.0f / (fConst3 + 1.0f);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider1 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.5f);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox3 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox4 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox5 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox6 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox7 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox8 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox9 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox10 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox11 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox12 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox13 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox14 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox15 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider4 = static_cast<FAUSTFLOAT>(0.2f);
		fHslider5 = static_cast<FAUSTFLOAT>(12.0f);
		fHslider6 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider7 = static_cast<FAUSTFLOAT>(5.0f);
		fHslider8 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider9 = static_cast<FAUSTFLOAT>(0.7f);
		fHslider10 = static_cast<FAUSTFLOAT>(0.85f);
		fHslider11 = static_cast<FAUSTFLOAT>(0.005f);
		fHslider12 = static_cast<FAUSTFLOAT>(-2e+01f);
		fHslider13 = static_cast<FAUSTFLOAT>(2.0f);
		fHslider14 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider15 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider16 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider17 = static_cast<FAUSTFLOAT>(0.5f);
		fCheckbox16 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox17 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox18 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox19 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox20 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox21 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox22 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox23 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox24 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox25 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox26 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox27 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox28 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox29 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox30 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox31 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider18 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider19 = static_cast<FAUSTFLOAT>(0.2f);
		fHslider20 = static_cast<FAUSTFLOAT>(12.0f);
		fHslider21 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider22 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider23 = static_cast<FAUSTFLOAT>(0.1f);
		fHslider24 = static_cast<FAUSTFLOAT>(6.0f);
		fHslider25 = static_cast<FAUSTFLOAT>(0.22f);
		fHslider26 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider27 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fCheckbox32 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox33 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox34 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox35 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox36 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox37 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox38 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox39 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox40 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox41 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox42 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox43 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox44 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox45 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox46 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox47 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider28 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider29 = static_cast<FAUSTFLOAT>(0.35f);
		fHslider30 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider31 = static_cast<FAUSTFLOAT>(-12.0f);
		fHslider32 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider33 = static_cast<FAUSTFLOAT>(0.04f);
		fHslider34 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider35 = static_cast<FAUSTFLOAT>(0.65f);
		fHslider36 = static_cast<FAUSTFLOAT>(0.55f);
		fHslider37 = static_cast<FAUSTFLOAT>(6.5e+03f);
		fHslider38 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider39 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider40 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider41 = static_cast<FAUSTFLOAT>(0.35f);
		fHslider42 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider43 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider44 = static_cast<FAUSTFLOAT>(0.5f);
		fCheckbox48 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox49 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox50 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox51 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox52 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox53 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox54 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox55 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox56 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox57 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox58 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox59 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox60 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox61 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox62 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox63 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider45 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider46 = static_cast<FAUSTFLOAT>(0.001f);
		fHslider47 = static_cast<FAUSTFLOAT>(0.04f);
		fHslider48 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider49 = static_cast<FAUSTFLOAT>(1.6e+02f);
		fHslider50 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider51 = static_cast<FAUSTFLOAT>(1.0f);
		fCheckbox64 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox65 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox66 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox67 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox68 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox69 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox70 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox71 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox72 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox73 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox74 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox75 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox76 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox77 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox78 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox79 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider52 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider53 = static_cast<FAUSTFLOAT>(0.16f);
		fHslider54 = static_cast<FAUSTFLOAT>(1.65e+03f);
		fHslider55 = static_cast<FAUSTFLOAT>(2.5f);
		fHslider56 = static_cast<FAUSTFLOAT>(0.55f);
		fHslider57 = static_cast<FAUSTFLOAT>(0.07f);
		fHslider58 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider59 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider60 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider61 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider62 = static_cast<FAUSTFLOAT>(0.65f);
		fHslider63 = static_cast<FAUSTFLOAT>(7.5e+02f);
		fHslider64 = static_cast<FAUSTFLOAT>(0.4f);
		fHslider65 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider66 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider67 = static_cast<FAUSTFLOAT>(0.5f);
		fCheckbox80 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox81 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox82 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox83 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox84 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox85 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox86 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox87 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox88 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox89 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox90 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox91 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox92 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox93 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox94 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox95 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider68 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider69 = static_cast<FAUSTFLOAT>(0.18f);
		fHslider70 = static_cast<FAUSTFLOAT>(1.5e+02f);
		fHslider71 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider72 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider73 = static_cast<FAUSTFLOAT>(2.5e+03f);
		fHslider74 = static_cast<FAUSTFLOAT>(8.0f);
		fHslider75 = static_cast<FAUSTFLOAT>(3.5f);
		fHslider76 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider77 = static_cast<FAUSTFLOAT>(0.85f);
		fHslider78 = static_cast<FAUSTFLOAT>(4.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		IOTA0 = 0;
		for (int l2 = 0; l2 < 32768; l2 = l2 + 1) {
			iVec1[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iRec3[l3] = 0;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iVec2[l4] = 0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iRec5[l5] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec8[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fVec4[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2048; l11 = l11 + 1) {
			fVec5[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec11[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec9[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec2[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec1[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 256; l16 = l16 + 1) {
			fVec6[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec12[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec17[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec24[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 32768; l20 = l20 + 1) {
			iVec7[l20] = 0;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			iRec23[l21] = 0;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			iVec8[l22] = 0;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			iRec25[l23] = 0;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec22[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec26[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec27[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec28[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec29[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2048; l29 = l29 + 1) {
			fRec18[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2048; l30 = l30 + 1) {
			fRec19[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2048; l31 = l31 + 1) {
			fRec20[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 4096; l32 = l32 + 1) {
			fRec21[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec16[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec15[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec14[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec13[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec35[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 32768; l38 = l38 + 1) {
			iVec9[l38] = 0;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			iRec34[l39] = 0;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			iVec10[l40] = 0;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec33[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec32[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			iRec37[l43] = 0;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			iRec39[l44] = 0;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fVec11[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec38[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec41[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fRec40[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 8192; l49 = l49 + 1) {
			fRec36[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec31[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec30[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fRec43[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fVec12[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 128; l54 = l54 + 1) {
			fVec13[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec44[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2; l56 = l56 + 1) {
			fVec14[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 128; l57 = l57 + 1) {
			fVec15[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec45[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fVec16[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 128; l60 = l60 + 1) {
			fVec17[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec46[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fVec18[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 256; l63 = l63 + 1) {
			fVec19[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fRec47[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fVec20[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 256; l66 = l66 + 1) {
			fVec21[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 2; l67 = l67 + 1) {
			fRec48[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fVec22[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 512; l69 = l69 + 1) {
			fVec23[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fRec50[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 32768; l71 = l71 + 1) {
			iVec24[l71] = 0;
		}
		for (int l72 = 0; l72 < 2; l72 = l72 + 1) {
			iRec49[l72] = 0;
		}
		for (int l73 = 0; l73 < 2; l73 = l73 + 1) {
			iVec25[l73] = 0;
		}
		for (int l74 = 0; l74 < 2; l74 = l74 + 1) {
			iRec51[l74] = 0;
		}
		for (int l75 = 0; l75 < 3; l75 = l75 + 1) {
			fRec42[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 2; l76 = l76 + 1) {
			fRec56[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 32768; l77 = l77 + 1) {
			iVec26[l77] = 0;
		}
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			iRec55[l78] = 0;
		}
		for (int l79 = 0; l79 < 2; l79 = l79 + 1) {
			iVec27[l79] = 0;
		}
		for (int l80 = 0; l80 < 2; l80 = l80 + 1) {
			iRec54[l80] = 0;
		}
		for (int l81 = 0; l81 < 3; l81 = l81 + 1) {
			fRec57[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			fRec58[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 2; l83 = l83 + 1) {
			fRec59[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 3; l84 = l84 + 1) {
			fRec53[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 3; l85 = l85 + 1) {
			fRec52[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 2; l86 = l86 + 1) {
			fRec75[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 32768; l87 = l87 + 1) {
			iVec28[l87] = 0;
		}
		for (int l88 = 0; l88 < 2; l88 = l88 + 1) {
			iRec74[l88] = 0;
		}
		for (int l89 = 0; l89 < 2; l89 = l89 + 1) {
			iVec29[l89] = 0;
		}
		for (int l90 = 0; l90 < 2; l90 = l90 + 1) {
			iRec76[l90] = 0;
		}
		for (int l91 = 0; l91 < 2; l91 = l91 + 1) {
			fRec77[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 2; l92 = l92 + 1) {
			fRec73[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 2; l93 = l93 + 1) {
			fVec30[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fRec72[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 3; l95 = l95 + 1) {
			fRec71[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 3; l96 = l96 + 1) {
			fRec70[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 3; l97 = l97 + 1) {
			fRec69[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 3; l98 = l98 + 1) {
			fRec68[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 2; l99 = l99 + 1) {
			fRec78[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 2; l100 = l100 + 1) {
			fRec79[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 2; l101 = l101 + 1) {
			fRec80[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 2; l102 = l102 + 1) {
			fRec81[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 512; l103 = l103 + 1) {
			fRec64[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 512; l104 = l104 + 1) {
			fRec65[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 1024; l105 = l105 + 1) {
			fRec66[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 1024; l106 = l106 + 1) {
			fRec67[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 256; l107 = l107 + 1) {
			fVec31[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 2; l108 = l108 + 1) {
			fRec62[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 256; l109 = l109 + 1) {
			fVec32[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fRec60[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 2; l111 = l111 + 1) {
			fVec33[l111] = 0.0f;
		}
		for (int l112 = 0; l112 < 2; l112 = l112 + 1) {
			fRec0[l112] = 0.0f;
		}
		for (int l113 = 0; l113 < 3; l113 = l113 + 1) {
			fRec83[l113] = 0.0f;
		}
		for (int l114 = 0; l114 < 2; l114 = l114 + 1) {
			fVec34[l114] = 0.0f;
		}
		for (int l115 = 0; l115 < 2; l115 = l115 + 1) {
			fRec82[l115] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return nullptr;
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("TR_808_ALGORITHMIC_STATION");
		ui_interface->openHorizontalBox("INSTRUMENTOS");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Bombo");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider65, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider65, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PAD");
		ui_interface->declare(&fCheckbox80, "osc", "/kick/step0");
		ui_interface->addCheckButton("KICK/00", &fCheckbox80);
		ui_interface->declare(&fCheckbox81, "osc", "/kick/step1");
		ui_interface->addCheckButton("KICK/01", &fCheckbox81);
		ui_interface->declare(&fCheckbox82, "osc", "/kick/step2");
		ui_interface->addCheckButton("KICK/02", &fCheckbox82);
		ui_interface->declare(&fCheckbox83, "osc", "/kick/step3");
		ui_interface->addCheckButton("KICK/03", &fCheckbox83);
		ui_interface->declare(&fCheckbox84, "osc", "/kick/step4");
		ui_interface->addCheckButton("KICK/04", &fCheckbox84);
		ui_interface->declare(&fCheckbox85, "osc", "/kick/step5");
		ui_interface->addCheckButton("KICK/05", &fCheckbox85);
		ui_interface->declare(&fCheckbox86, "osc", "/kick/step6");
		ui_interface->addCheckButton("KICK/06", &fCheckbox86);
		ui_interface->declare(&fCheckbox87, "osc", "/kick/step7");
		ui_interface->addCheckButton("KICK/07", &fCheckbox87);
		ui_interface->declare(&fCheckbox88, "osc", "/kick/step8");
		ui_interface->addCheckButton("KICK/08", &fCheckbox88);
		ui_interface->declare(&fCheckbox89, "osc", "/kick/step9");
		ui_interface->addCheckButton("KICK/09", &fCheckbox89);
		ui_interface->declare(&fCheckbox90, "osc", "/kick/step10");
		ui_interface->addCheckButton("KICK/10", &fCheckbox90);
		ui_interface->declare(&fCheckbox91, "osc", "/kick/step11");
		ui_interface->addCheckButton("KICK/11", &fCheckbox91);
		ui_interface->declare(&fCheckbox92, "osc", "/kick/step12");
		ui_interface->addCheckButton("KICK/12", &fCheckbox92);
		ui_interface->declare(&fCheckbox93, "osc", "/kick/step13");
		ui_interface->addCheckButton("KICK/13", &fCheckbox93);
		ui_interface->declare(&fCheckbox94, "osc", "/kick/step14");
		ui_interface->addCheckButton("KICK/14", &fCheckbox94);
		ui_interface->declare(&fCheckbox95, "osc", "/kick/step15");
		ui_interface->addCheckButton("KICK/15", &fCheckbox95);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider67, "1", "");
		ui_interface->declare(&fHslider67, "osc", "/kick/accent");
		ui_interface->declare(&fHslider67, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider67, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider71, "1", "");
		ui_interface->declare(&fHslider71, "osc", "/kick/tune");
		ui_interface->declare(&fHslider71, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider71, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider69, "1", "");
		ui_interface->declare(&fHslider69, "osc", "/kick/dec");
		ui_interface->declare(&fHslider69, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider69, FAUSTFLOAT(0.18f), FAUSTFLOAT(0.02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider76, "1", "");
		ui_interface->declare(&fHslider76, "osc", "/kick/mix");
		ui_interface->declare(&fHslider76, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Rumble", &fHslider76, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider72, "1", "");
		ui_interface->declare(&fHslider72, "osc", "/kick/nota");
		ui_interface->declare(&fHslider72, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider72, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider66, "1", "");
		ui_interface->declare(&fHslider66, "osc", "/kick/reloj");
		ui_interface->declare(&fHslider66, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider66, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider68, "1", "");
		ui_interface->declare(&fHslider68, "osc", "/kick/swing");
		ui_interface->declare(&fHslider68, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider68, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider70, "1", "");
		ui_interface->declare(&fHslider70, "osc", "/kick/sweep");
		ui_interface->declare(&fHslider70, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Transitorio", &fHslider70, FAUSTFLOAT(1.5e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(3e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider77, "1", "");
		ui_interface->declare(&fHslider77, "osc", "/kick/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider77, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider73, "2", "");
		ui_interface->declare(&fHslider73, "osc", "/kick/comp_fmax");
		ui_interface->declare(&fHslider73, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Filtro Frec Max", &fHslider73, FAUSTFLOAT(2.5e+03f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(8e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider63, "2", "");
		ui_interface->declare(&fHslider63, "osc", "/kick/comp_fmin");
		ui_interface->declare(&fHslider63, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Filtro Frec Min", &fHslider63, FAUSTFLOAT(7.5e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider74, "2", "");
		ui_interface->declare(&fHslider74, "osc", "/kick/comp_ratio");
		ui_interface->declare(&fHslider74, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Lim Ratio", &fHslider74, FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider64, "2", "");
		ui_interface->declare(&fHslider64, "osc", "/kick/comp_thresh");
		ui_interface->declare(&fHslider64, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Lim Umbral", &fHslider64, FAUSTFLOAT(0.4f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider75, "2", "");
		ui_interface->declare(&fHslider75, "osc", "/kick/comp_drive");
		ui_interface->declare(&fHslider75, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Saturacion Pegada", &fHslider75, FAUSTFLOAT(3.5f), FAUSTFLOAT(0.5f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("Caja");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider50, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider50, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PAD");
		ui_interface->declare(&fCheckbox64, "osc", "/snare/step0");
		ui_interface->addCheckButton("SNARE/00", &fCheckbox64);
		ui_interface->declare(&fCheckbox65, "osc", "/snare/step1");
		ui_interface->addCheckButton("SNARE/01", &fCheckbox65);
		ui_interface->declare(&fCheckbox66, "osc", "/snare/step2");
		ui_interface->addCheckButton("SNARE/02", &fCheckbox66);
		ui_interface->declare(&fCheckbox67, "osc", "/snare/step3");
		ui_interface->addCheckButton("SNARE/03", &fCheckbox67);
		ui_interface->declare(&fCheckbox68, "osc", "/snare/step4");
		ui_interface->addCheckButton("SNARE/04", &fCheckbox68);
		ui_interface->declare(&fCheckbox69, "osc", "/snare/step5");
		ui_interface->addCheckButton("SNARE/05", &fCheckbox69);
		ui_interface->declare(&fCheckbox70, "osc", "/snare/step6");
		ui_interface->addCheckButton("SNARE/06", &fCheckbox70);
		ui_interface->declare(&fCheckbox71, "osc", "/snare/step7");
		ui_interface->addCheckButton("SNARE/07", &fCheckbox71);
		ui_interface->declare(&fCheckbox72, "osc", "/snare/step8");
		ui_interface->addCheckButton("SNARE/08", &fCheckbox72);
		ui_interface->declare(&fCheckbox73, "osc", "/snare/step9");
		ui_interface->addCheckButton("SNARE/09", &fCheckbox73);
		ui_interface->declare(&fCheckbox74, "osc", "/snare/step10");
		ui_interface->addCheckButton("SNARE/10", &fCheckbox74);
		ui_interface->declare(&fCheckbox75, "osc", "/snare/step11");
		ui_interface->addCheckButton("SNARE/11", &fCheckbox75);
		ui_interface->declare(&fCheckbox76, "osc", "/snare/step12");
		ui_interface->addCheckButton("SNARE/12", &fCheckbox76);
		ui_interface->declare(&fCheckbox77, "osc", "/snare/step13");
		ui_interface->addCheckButton("SNARE/13", &fCheckbox77);
		ui_interface->declare(&fCheckbox78, "osc", "/snare/step14");
		ui_interface->addCheckButton("SNARE/14", &fCheckbox78);
		ui_interface->declare(&fCheckbox79, "osc", "/snare/step15");
		ui_interface->addCheckButton("SNARE/15", &fCheckbox79);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider60, "1", "");
		ui_interface->declare(&fHslider60, "osc", "/snare/accent");
		ui_interface->declare(&fHslider60, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider60, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider58, "1", "");
		ui_interface->declare(&fHslider58, "osc", "/snare/tune");
		ui_interface->declare(&fHslider58, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider58, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider57, "1", "");
		ui_interface->declare(&fHslider57, "osc", "/snare/dec_cuerpo");
		ui_interface->declare(&fHslider57, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decay Cuerpo", &fHslider57, FAUSTFLOAT(0.07f), FAUSTFLOAT(0.01f), FAUSTFLOAT(0.4f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider53, "1", "");
		ui_interface->declare(&fHslider53, "osc", "/snare/dec_resorte");
		ui_interface->declare(&fHslider53, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decay Resortes", &fHslider53, FAUSTFLOAT(0.16f), FAUSTFLOAT(0.02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider49, "1", "");
		ui_interface->declare(&fHslider49, "osc", "/snare/hp");
		ui_interface->declare(&fHslider49, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro Paso Alto", &fHslider49, FAUSTFLOAT(1.6e+02f), FAUSTFLOAT(8e+01f), FAUSTFLOAT(4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider54, "1", "");
		ui_interface->declare(&fHslider54, "osc", "/snare/freq");
		ui_interface->declare(&fHslider54, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Frecuencia Resortes", &fHslider54, FAUSTFLOAT(1.65e+03f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider56, "1", "");
		ui_interface->declare(&fHslider56, "osc", "/snare/mix");
		ui_interface->declare(&fHslider56, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Resortes", &fHslider56, FAUSTFLOAT(0.55f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider59, "1", "");
		ui_interface->declare(&fHslider59, "osc", "/snare/nota");
		ui_interface->declare(&fHslider59, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider59, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider51, "1", "");
		ui_interface->declare(&fHslider51, "osc", "/snare/reloj");
		ui_interface->declare(&fHslider51, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider51, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider55, "1", "");
		ui_interface->declare(&fHslider55, "osc", "/snare/q");
		ui_interface->declare(&fHslider55, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Resonancia Resortes", &fHslider55, FAUSTFLOAT(2.5f), FAUSTFLOAT(1.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider61, "1", "");
		ui_interface->declare(&fHslider61, "osc", "/snare/drive");
		ui_interface->declare(&fHslider61, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider61, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider52, "1", "");
		ui_interface->declare(&fHslider52, "osc", "/snare/swing");
		ui_interface->declare(&fHslider52, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider52, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider62, "1", "");
		ui_interface->declare(&fHslider62, "osc", "/snare/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider62, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("Platillos");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider42, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider42, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PAD");
		ui_interface->declare(&fCheckbox48, "osc", "/hat/step0");
		ui_interface->addCheckButton("HAT/00", &fCheckbox48);
		ui_interface->declare(&fCheckbox49, "osc", "/hat/step1");
		ui_interface->addCheckButton("HAT/01", &fCheckbox49);
		ui_interface->declare(&fCheckbox50, "osc", "/hat/step2");
		ui_interface->addCheckButton("HAT/02", &fCheckbox50);
		ui_interface->declare(&fCheckbox51, "osc", "/hat/step3");
		ui_interface->addCheckButton("HAT/03", &fCheckbox51);
		ui_interface->declare(&fCheckbox52, "osc", "/hat/step4");
		ui_interface->addCheckButton("HAT/04", &fCheckbox52);
		ui_interface->declare(&fCheckbox53, "osc", "/hat/step5");
		ui_interface->addCheckButton("HAT/05", &fCheckbox53);
		ui_interface->declare(&fCheckbox54, "osc", "/hat/step6");
		ui_interface->addCheckButton("HAT/06", &fCheckbox54);
		ui_interface->declare(&fCheckbox55, "osc", "/hat/step7");
		ui_interface->addCheckButton("HAT/07", &fCheckbox55);
		ui_interface->declare(&fCheckbox56, "osc", "/hat/step8");
		ui_interface->addCheckButton("HAT/08", &fCheckbox56);
		ui_interface->declare(&fCheckbox57, "osc", "/hat/step9");
		ui_interface->addCheckButton("HAT/09", &fCheckbox57);
		ui_interface->declare(&fCheckbox58, "osc", "/hat/step10");
		ui_interface->addCheckButton("HAT/10", &fCheckbox58);
		ui_interface->declare(&fCheckbox59, "osc", "/hat/step11");
		ui_interface->addCheckButton("HAT/11", &fCheckbox59);
		ui_interface->declare(&fCheckbox60, "osc", "/hat/step12");
		ui_interface->addCheckButton("HAT/12", &fCheckbox60);
		ui_interface->declare(&fCheckbox61, "osc", "/hat/step13");
		ui_interface->addCheckButton("HAT/13", &fCheckbox61);
		ui_interface->declare(&fCheckbox62, "osc", "/hat/step14");
		ui_interface->addCheckButton("HAT/14", &fCheckbox62);
		ui_interface->declare(&fCheckbox63, "osc", "/hat/step15");
		ui_interface->addCheckButton("HAT/15", &fCheckbox63);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider44, "1", "");
		ui_interface->declare(&fHslider44, "osc", "/hat/accent");
		ui_interface->declare(&fHslider44, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider44, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider39, "1", "");
		ui_interface->declare(&fHslider39, "osc", "/hat/tune");
		ui_interface->declare(&fHslider39, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider39, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider46, "1", "");
		ui_interface->declare(&fHslider46, "osc", "/hat/ataque");
		ui_interface->declare(&fHslider46, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Ataque", &fHslider46, FAUSTFLOAT(0.001f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider47, "1", "");
		ui_interface->declare(&fHslider47, "osc", "/hat/dec");
		ui_interface->declare(&fHslider47, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider47, FAUSTFLOAT(0.04f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider37, "1", "");
		ui_interface->declare(&fHslider37, "osc", "/hat/cutoff");
		ui_interface->declare(&fHslider37, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro Paso Alto", &fHslider37, FAUSTFLOAT(6.5e+03f), FAUSTFLOAT(3e+03f), FAUSTFLOAT(1.2e+04f), FAUSTFLOAT(5e+01f));
		ui_interface->declare(&fHslider38, "1", "");
		ui_interface->declare(&fHslider38, "osc", "/hat/mix");
		ui_interface->declare(&fHslider38, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Metal Ruido", &fHslider38, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider40, "1", "");
		ui_interface->declare(&fHslider40, "osc", "/hat/nota");
		ui_interface->declare(&fHslider40, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider40, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider43, "1", "");
		ui_interface->declare(&fHslider43, "osc", "/hat/reloj");
		ui_interface->declare(&fHslider43, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider43, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider41, "1", "");
		ui_interface->declare(&fHslider41, "osc", "/hat/drive");
		ui_interface->declare(&fHslider41, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider41, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider45, "1", "");
		ui_interface->declare(&fHslider45, "osc", "/hat/swing");
		ui_interface->declare(&fHslider45, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider45, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider48, "1", "");
		ui_interface->declare(&fHslider48, "osc", "/hat/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider48, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openVerticalBox("Bajo WG");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider27, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider27, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PAD");
		ui_interface->declare(&fCheckbox32, "osc", "/bass/step0");
		ui_interface->addCheckButton("BASS/00", &fCheckbox32);
		ui_interface->declare(&fCheckbox33, "osc", "/bass/step1");
		ui_interface->addCheckButton("BASS/01", &fCheckbox33);
		ui_interface->declare(&fCheckbox34, "osc", "/bass/step2");
		ui_interface->addCheckButton("BASS/02", &fCheckbox34);
		ui_interface->declare(&fCheckbox35, "osc", "/bass/step3");
		ui_interface->addCheckButton("BASS/03", &fCheckbox35);
		ui_interface->declare(&fCheckbox36, "osc", "/bass/step4");
		ui_interface->addCheckButton("BASS/04", &fCheckbox36);
		ui_interface->declare(&fCheckbox37, "osc", "/bass/step5");
		ui_interface->addCheckButton("BASS/05", &fCheckbox37);
		ui_interface->declare(&fCheckbox38, "osc", "/bass/step6");
		ui_interface->addCheckButton("BASS/06", &fCheckbox38);
		ui_interface->declare(&fCheckbox39, "osc", "/bass/step7");
		ui_interface->addCheckButton("BASS/07", &fCheckbox39);
		ui_interface->declare(&fCheckbox40, "osc", "/bass/step8");
		ui_interface->addCheckButton("BASS/08", &fCheckbox40);
		ui_interface->declare(&fCheckbox41, "osc", "/bass/step9");
		ui_interface->addCheckButton("BASS/09", &fCheckbox41);
		ui_interface->declare(&fCheckbox42, "osc", "/bass/step10");
		ui_interface->addCheckButton("BASS/10", &fCheckbox42);
		ui_interface->declare(&fCheckbox43, "osc", "/bass/step11");
		ui_interface->addCheckButton("BASS/11", &fCheckbox43);
		ui_interface->declare(&fCheckbox44, "osc", "/bass/step12");
		ui_interface->addCheckButton("BASS/12", &fCheckbox44);
		ui_interface->declare(&fCheckbox45, "osc", "/bass/step13");
		ui_interface->addCheckButton("BASS/13", &fCheckbox45);
		ui_interface->declare(&fCheckbox46, "osc", "/bass/step14");
		ui_interface->addCheckButton("BASS/14", &fCheckbox46);
		ui_interface->declare(&fCheckbox47, "osc", "/bass/step15");
		ui_interface->addCheckButton("BASS/15", &fCheckbox47);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider30, "1", "");
		ui_interface->declare(&fHslider30, "osc", "/bass/accent");
		ui_interface->declare(&fHslider30, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider30, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider29, "1", "");
		ui_interface->declare(&fHslider29, "osc", "/bass/dec");
		ui_interface->declare(&fHslider29, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider29, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider33, "1", "");
		ui_interface->declare(&fHslider33, "osc", "/bass/detune");
		ui_interface->declare(&fHslider33, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Desafinado", &fHslider33, FAUSTFLOAT(0.04f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider34, "1", "");
		ui_interface->declare(&fHslider34, "osc", "/bass/lfo");
		ui_interface->declare(&fHslider34, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro LFO", &fHslider34, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider31, "1", "");
		ui_interface->declare(&fHslider31, "osc", "/bass/intervalo");
		ui_interface->addHorizontalSlider("Sintesis/Intervalo", &fHslider31, FAUSTFLOAT(-12.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(7.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider32, "1", "");
		ui_interface->declare(&fHslider32, "osc", "/bass/nota");
		ui_interface->declare(&fHslider32, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider32, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider26, "1", "");
		ui_interface->declare(&fHslider26, "osc", "/bass/reloj");
		ui_interface->declare(&fHslider26, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider26, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider35, "1", "");
		ui_interface->declare(&fHslider35, "osc", "/bass/drive");
		ui_interface->declare(&fHslider35, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider35, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider28, "1", "");
		ui_interface->declare(&fHslider28, "osc", "/bass/swing");
		ui_interface->declare(&fHslider28, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider28, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider36, "1", "");
		ui_interface->declare(&fHslider36, "osc", "/bass/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider36, FAUSTFLOAT(0.55f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "5", "");
		ui_interface->openVerticalBox("Synth Psyche");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider0, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider0, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PAD");
		ui_interface->declare(&fCheckbox0, "osc", "/syn1/step0");
		ui_interface->addCheckButton("SYN1/00", &fCheckbox0);
		ui_interface->declare(&fCheckbox1, "osc", "/syn1/step1");
		ui_interface->addCheckButton("SYN1/01", &fCheckbox1);
		ui_interface->declare(&fCheckbox2, "osc", "/syn1/step2");
		ui_interface->addCheckButton("SYN1/02", &fCheckbox2);
		ui_interface->declare(&fCheckbox3, "osc", "/syn1/step3");
		ui_interface->addCheckButton("SYN1/03", &fCheckbox3);
		ui_interface->declare(&fCheckbox4, "osc", "/syn1/step4");
		ui_interface->addCheckButton("SYN1/04", &fCheckbox4);
		ui_interface->declare(&fCheckbox5, "osc", "/syn1/step5");
		ui_interface->addCheckButton("SYN1/05", &fCheckbox5);
		ui_interface->declare(&fCheckbox6, "osc", "/syn1/step6");
		ui_interface->addCheckButton("SYN1/06", &fCheckbox6);
		ui_interface->declare(&fCheckbox7, "osc", "/syn1/step7");
		ui_interface->addCheckButton("SYN1/07", &fCheckbox7);
		ui_interface->declare(&fCheckbox8, "osc", "/syn1/step8");
		ui_interface->addCheckButton("SYN1/08", &fCheckbox8);
		ui_interface->declare(&fCheckbox9, "osc", "/syn1/step9");
		ui_interface->addCheckButton("SYN1/09", &fCheckbox9);
		ui_interface->declare(&fCheckbox10, "osc", "/syn1/step10");
		ui_interface->addCheckButton("SYN1/10", &fCheckbox10);
		ui_interface->declare(&fCheckbox11, "osc", "/syn1/step11");
		ui_interface->addCheckButton("SYN1/11", &fCheckbox11);
		ui_interface->declare(&fCheckbox12, "osc", "/syn1/step12");
		ui_interface->addCheckButton("SYN1/12", &fCheckbox12);
		ui_interface->declare(&fCheckbox13, "osc", "/syn1/step13");
		ui_interface->addCheckButton("SYN1/13", &fCheckbox13);
		ui_interface->declare(&fCheckbox14, "osc", "/syn1/step14");
		ui_interface->addCheckButton("SYN1/14", &fCheckbox14);
		ui_interface->declare(&fCheckbox15, "osc", "/syn1/step15");
		ui_interface->addCheckButton("SYN1/15", &fCheckbox15);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "osc", "/syn1/accent");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider2, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider9, "1", "");
		ui_interface->declare(&fHslider9, "osc", "/syn1/auto_p");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Profundidad", &fHslider9, FAUSTFLOAT(0.7f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider78, "1", "");
		ui_interface->declare(&fHslider78, "osc", "/syn1/auto_r");
		ui_interface->declare(&fHslider78, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Resonancia", &fHslider78, FAUSTFLOAT(4.5f), FAUSTFLOAT(1.0f), FAUSTFLOAT(9.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider8, "1", "");
		ui_interface->declare(&fHslider8, "osc", "/syn1/auto_v");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Velocidad", &fHslider8, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.05f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "osc", "/syn1/dec");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider4, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "osc", "/syn1/nota");
		ui_interface->declare(&fHslider6, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider6, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "osc", "/syn1/osc1");
		ui_interface->addHorizontalSlider("Sintesis/Osc 1", &fHslider7, FAUSTFLOAT(5.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "osc", "/syn1/osc2");
		ui_interface->addHorizontalSlider("Sintesis/Osc 2", &fHslider5, FAUSTFLOAT(12.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(19.0f), FAUSTFLOAT(19.0f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "osc", "/syn1/reloj");
		ui_interface->declare(&fHslider1, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "osc", "/syn1/swing");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider10, "1", "");
		ui_interface->declare(&fHslider10, "osc", "/syn1/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider10, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "6", "");
		ui_interface->openVerticalBox("Siringe FDN");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider15, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider15, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("PAD");
		ui_interface->declare(&fCheckbox16, "osc", "/syn2/step0");
		ui_interface->addCheckButton("SYN2/00", &fCheckbox16);
		ui_interface->declare(&fCheckbox17, "osc", "/syn2/step1");
		ui_interface->addCheckButton("SYN2/01", &fCheckbox17);
		ui_interface->declare(&fCheckbox18, "osc", "/syn2/step2");
		ui_interface->addCheckButton("SYN2/02", &fCheckbox18);
		ui_interface->declare(&fCheckbox19, "osc", "/syn2/step3");
		ui_interface->addCheckButton("SYN2/03", &fCheckbox19);
		ui_interface->declare(&fCheckbox20, "osc", "/syn2/step4");
		ui_interface->addCheckButton("SYN2/04", &fCheckbox20);
		ui_interface->declare(&fCheckbox21, "osc", "/syn2/step5");
		ui_interface->addCheckButton("SYN2/05", &fCheckbox21);
		ui_interface->declare(&fCheckbox22, "osc", "/syn2/step6");
		ui_interface->addCheckButton("SYN2/06", &fCheckbox22);
		ui_interface->declare(&fCheckbox23, "osc", "/syn2/step7");
		ui_interface->addCheckButton("SYN2/07", &fCheckbox23);
		ui_interface->declare(&fCheckbox24, "osc", "/syn2/step8");
		ui_interface->addCheckButton("SYN2/08", &fCheckbox24);
		ui_interface->declare(&fCheckbox25, "osc", "/syn2/step9");
		ui_interface->addCheckButton("SYN2/09", &fCheckbox25);
		ui_interface->declare(&fCheckbox26, "osc", "/syn2/step10");
		ui_interface->addCheckButton("SYN2/10", &fCheckbox26);
		ui_interface->declare(&fCheckbox27, "osc", "/syn2/step11");
		ui_interface->addCheckButton("SYN2/11", &fCheckbox27);
		ui_interface->declare(&fCheckbox28, "osc", "/syn2/step12");
		ui_interface->addCheckButton("SYN2/12", &fCheckbox28);
		ui_interface->declare(&fCheckbox29, "osc", "/syn2/step13");
		ui_interface->addCheckButton("SYN2/13", &fCheckbox29);
		ui_interface->declare(&fCheckbox30, "osc", "/syn2/step14");
		ui_interface->addCheckButton("SYN2/14", &fCheckbox30);
		ui_interface->declare(&fCheckbox31, "osc", "/syn2/step15");
		ui_interface->addCheckButton("SYN2/15", &fCheckbox31);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider17, "1", "");
		ui_interface->declare(&fHslider17, "osc", "/syn2/accent");
		ui_interface->declare(&fHslider17, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider17, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider19, "1", "");
		ui_interface->declare(&fHslider19, "osc", "/syn2/dec");
		ui_interface->declare(&fHslider19, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider19, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider22, "1", "");
		ui_interface->declare(&fHslider22, "osc", "/syn2/disp");
		ui_interface->declare(&fHslider22, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Dispersion", &fHslider22, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.9f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider13, "1", "");
		ui_interface->declare(&fHslider13, "osc", "/syn2/lfo_f");
		ui_interface->declare(&fHslider13, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/LFO Freq", &fHslider13, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider14, "1", "");
		ui_interface->declare(&fHslider14, "osc", "/syn2/lfo_p");
		ui_interface->declare(&fHslider14, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/LFO Profundidad", &fHslider14, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider20, "1", "");
		ui_interface->declare(&fHslider20, "osc", "/syn2/nota");
		ui_interface->declare(&fHslider20, "style", "menu{'Octava':12; 'Quinta Arriba':19; 'Doble Octava':24}");
		ui_interface->addHorizontalSlider("Sintesis/Nota Siringe", &fHslider20, FAUSTFLOAT(12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider21, "1", "");
		ui_interface->declare(&fHslider21, "osc", "/syn2/nota");
		ui_interface->declare(&fHslider21, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider21, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider16, "1", "");
		ui_interface->declare(&fHslider16, "osc", "/syn2/reloj");
		ui_interface->declare(&fHslider16, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider16, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider18, "1", "");
		ui_interface->declare(&fHslider18, "osc", "/syn2/swing");
		ui_interface->declare(&fHslider18, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider18, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider25, "1", "");
		ui_interface->declare(&fHslider25, "osc", "/syn2/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider25, FAUSTFLOAT(0.22f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider11, "2", "");
		ui_interface->declare(&fHslider11, "osc", "/syn2/comp_a");
		ui_interface->declare(&fHslider11, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Ataque", &fHslider11, FAUSTFLOAT(0.005f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider23, "2", "");
		ui_interface->declare(&fHslider23, "osc", "/syn2/comp_rel");
		ui_interface->declare(&fHslider23, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Liberacion", &fHslider23, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider24, "2", "");
		ui_interface->declare(&fHslider24, "osc", "/syn2/comp_r");
		ui_interface->declare(&fHslider24, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Ratio", &fHslider24, FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider12, "2", "");
		ui_interface->declare(&fHslider12, "osc", "/syn2/comp_th");
		ui_interface->declare(&fHslider12, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Umbral", &fHslider12, FAUSTFLOAT(-2e+01f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		if (m_pendingReset.exchange(false, std::memory_order_acq_rel)) {
			// Reset all step counters to 0
			iRec3[0] = 0; iRec3[1] = 0;
			iRec23[0] = 0; iRec23[1] = 0;
			iRec34[0] = 0; iRec34[1] = 0;
			iRec49[0] = 0; iRec49[1] = 0;
			iRec55[0] = 0; iRec55[1] = 0;
			iRec74[0] = 0; iRec74[1] = 0;

			// Reset all phase accumulators to 0.0f
			fRec4[0] = 0.0f; fRec4[1] = 0.0f;
			fRec24[0] = 0.0f; fRec24[1] = 0.0f;
			fRec35[0] = 0.0f; fRec35[1] = 0.0f;
			fRec50[0] = 0.0f; fRec50[1] = 0.0f;
			fRec56[0] = 0.0f; fRec56[1] = 0.0f;
			fRec75[0] = 0.0f; fRec75[1] = 0.0f;
		}
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = static_cast<float>(fHslider1) * static_cast<float>(fHslider0);
		float fSlow1 = fConst13 * fSlow0;
		float fSlow2 = 0.4f * static_cast<float>(fHslider2) + 1.0f;
		float fSlow3 = static_cast<float>(fCheckbox0);
		float fSlow4 = static_cast<float>(fCheckbox1);
		float fSlow5 = static_cast<float>(fCheckbox2);
		float fSlow6 = static_cast<float>(fCheckbox3);
		float fSlow7 = static_cast<float>(fCheckbox4);
		float fSlow8 = static_cast<float>(fCheckbox5);
		float fSlow9 = static_cast<float>(fCheckbox6);
		float fSlow10 = static_cast<float>(fCheckbox7);
		float fSlow11 = static_cast<float>(fCheckbox8);
		float fSlow12 = static_cast<float>(fCheckbox9);
		float fSlow13 = static_cast<float>(fCheckbox10);
		float fSlow14 = static_cast<float>(fCheckbox11);
		float fSlow15 = static_cast<float>(fCheckbox12);
		float fSlow16 = static_cast<float>(fCheckbox13);
		float fSlow17 = static_cast<float>(fCheckbox14);
		float fSlow18 = static_cast<float>(fCheckbox15);
		float fSlow19 = fConst14 * (static_cast<float>(fHslider3) / fSlow0);
		int iSlow20 = static_cast<int>(fSlow19);
		int iSlow21 = std::min<int>(16385, std::max<int>(0, iSlow20 + 1));
		float fSlow22 = std::floor(fSlow19);
		float fSlow23 = fSlow19 - fSlow22;
		int iSlow24 = std::min<int>(16385, std::max<int>(0, iSlow20));
		float fSlow25 = fSlow22 + (1.0f - fSlow19);
		float fSlow26 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider4));
		float fSlow27 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider6) + -69.0f));
		float fSlow28 = 4.4e+02f * fSlow27 * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider5));
		float fSlow29 = 4.4e+02f * fSlow27 * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider7));
		float fSlow30 = fConst18 * static_cast<float>(fHslider8);
		float fSlow31 = static_cast<float>(fHslider9);
		float fSlow32 = static_cast<float>(fHslider10);
		float fSlow33 = fConst5 * fSlow32 * (1.0f - 0.5f * fSlow31);
		float fSlow34 = static_cast<float>(fHslider11);
		float fSlow35 = 0.5f * fSlow34;
		int iSlow36 = std::fabs(fSlow35) < 1.1920929e-07f;
		float fSlow37 = ((iSlow36) ? 0.0f : std::exp(-(fConst18 / ((iSlow36) ? 1.0f : fSlow35))));
		float fSlow38 = 1.0f - fSlow37;
		float fSlow39 = static_cast<float>(fHslider12);
		float fSlow40 = fConst18 * static_cast<float>(fHslider13);
		float fSlow41 = static_cast<float>(fHslider14);
		float fSlow42 = static_cast<float>(fHslider16) * static_cast<float>(fHslider15);
		float fSlow43 = fConst13 * fSlow42;
		float fSlow44 = 0.6f * static_cast<float>(fHslider17) + 1.0f;
		float fSlow45 = static_cast<float>(fCheckbox16);
		float fSlow46 = static_cast<float>(fCheckbox17);
		float fSlow47 = static_cast<float>(fCheckbox18);
		float fSlow48 = static_cast<float>(fCheckbox19);
		float fSlow49 = static_cast<float>(fCheckbox20);
		float fSlow50 = static_cast<float>(fCheckbox21);
		float fSlow51 = static_cast<float>(fCheckbox22);
		float fSlow52 = static_cast<float>(fCheckbox23);
		float fSlow53 = static_cast<float>(fCheckbox24);
		float fSlow54 = static_cast<float>(fCheckbox25);
		float fSlow55 = static_cast<float>(fCheckbox26);
		float fSlow56 = static_cast<float>(fCheckbox27);
		float fSlow57 = static_cast<float>(fCheckbox28);
		float fSlow58 = static_cast<float>(fCheckbox29);
		float fSlow59 = static_cast<float>(fCheckbox30);
		float fSlow60 = static_cast<float>(fCheckbox31);
		float fSlow61 = fConst14 * (static_cast<float>(fHslider18) / fSlow42);
		int iSlow62 = static_cast<int>(fSlow61);
		int iSlow63 = std::min<int>(16385, std::max<int>(0, iSlow62 + 1));
		float fSlow64 = std::floor(fSlow61);
		float fSlow65 = fSlow61 - fSlow64;
		int iSlow66 = std::min<int>(16385, std::max<int>(0, iSlow62));
		float fSlow67 = fSlow64 + (1.0f - fSlow61);
		float fSlow68 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider19));
		float fSlow69 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider21) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider20));
		float fSlow70 = 0.5f * static_cast<float>(fHslider22);
		float fSlow71 = static_cast<float>(fHslider23);
		int iSlow72 = std::fabs(fSlow71) < 1.1920929e-07f;
		float fSlow73 = ((iSlow72) ? 0.0f : std::exp(-(fConst18 / ((iSlow72) ? 1.0f : fSlow71))));
		int iSlow74 = std::fabs(fSlow34) < 1.1920929e-07f;
		float fSlow75 = ((iSlow74) ? 0.0f : std::exp(-(fConst18 / ((iSlow74) ? 1.0f : fSlow34))));
		float fSlow76 = 1.0f / std::max<float>(1.1920929e-07f, static_cast<float>(fHslider24)) + -1.0f;
		float fSlow77 = fConst26 * static_cast<float>(fHslider25);
		float fSlow78 = static_cast<float>(fHslider27);
		float fSlow79 = fSlow78 * static_cast<float>(fHslider26);
		float fSlow80 = fConst13 * fSlow79;
		float fSlow81 = static_cast<float>(fCheckbox32);
		float fSlow82 = static_cast<float>(fCheckbox33);
		float fSlow83 = static_cast<float>(fCheckbox34);
		float fSlow84 = static_cast<float>(fCheckbox35);
		float fSlow85 = static_cast<float>(fCheckbox36);
		float fSlow86 = static_cast<float>(fCheckbox37);
		float fSlow87 = static_cast<float>(fCheckbox38);
		float fSlow88 = static_cast<float>(fCheckbox39);
		float fSlow89 = static_cast<float>(fCheckbox40);
		float fSlow90 = static_cast<float>(fCheckbox41);
		float fSlow91 = static_cast<float>(fCheckbox42);
		float fSlow92 = static_cast<float>(fCheckbox43);
		float fSlow93 = static_cast<float>(fCheckbox44);
		float fSlow94 = static_cast<float>(fCheckbox45);
		float fSlow95 = static_cast<float>(fCheckbox46);
		float fSlow96 = static_cast<float>(fCheckbox47);
		float fSlow97 = fConst14 * (static_cast<float>(fHslider28) / fSlow79);
		int iSlow98 = static_cast<int>(fSlow97);
		int iSlow99 = std::min<int>(16385, std::max<int>(0, iSlow98 + 1));
		float fSlow100 = std::floor(fSlow97);
		float fSlow101 = fSlow97 - fSlow100;
		int iSlow102 = std::min<int>(16385, std::max<int>(0, iSlow98));
		float fSlow103 = fSlow100 + (1.0f - fSlow97);
		float fSlow104 = 0.004166667f * (fSlow78 / static_cast<float>(fHslider29));
		float fSlow105 = 0.4f * static_cast<float>(fHslider30) + 1.0f;
		float fSlow106 = static_cast<float>(fHslider33);
		float fSlow107 = fConst58 * ((0.059f * fSlow106 + 1.0f) / (std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider32) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider31))));
		int iSlow108 = static_cast<int>(fSlow107);
		int iSlow109 = std::min<int>(131073, std::max<int>(0, iSlow108 + 1)) + 1;
		float fSlow110 = std::floor(fSlow107);
		float fSlow111 = fSlow107 - fSlow110;
		int iSlow112 = std::min<int>(131073, std::max<int>(0, iSlow108)) + 1;
		float fSlow113 = fSlow110 + (1.0f - fSlow107);
		float fSlow114 = static_cast<float>(fHslider34);
		float fSlow115 = 3.0f * static_cast<float>(fHslider35);
		float fSlow116 = (fSlow115 + 1.0f) * (0.014f * fSlow106 + 0.985f);
		float fSlow117 = fConst42 * static_cast<float>(fHslider36);
		float fSlow118 = std::tan(fConst61 * static_cast<float>(fHslider37));
		float fSlow119 = mydsp_faustpower2_f(fSlow118);
		float fSlow120 = 2.0f * (1.0f - 1.0f / fSlow119);
		float fSlow121 = 1.0f / fSlow118;
		float fSlow122 = (fSlow121 + -1.4142135f) / fSlow118 + 1.0f;
		float fSlow123 = (fSlow121 + 1.4142135f) / fSlow118 + 1.0f;
		float fSlow124 = 1.0f / fSlow123;
		float fSlow125 = static_cast<float>(fHslider38);
		float fSlow126 = 4.656613e-10f * fSlow125;
		float fSlow127 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider40) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider39));
		float fSlow128 = std::max<float>(19306.982f * fSlow127, 23.44895f);
		float fSlow129 = std::max<float>(2e+01f, std::fabs(fSlow128));
		float fSlow130 = fConst18 * fSlow129;
		float fSlow131 = fConst62 / fSlow129;
		float fSlow132 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow128));
		int iSlow133 = static_cast<int>(fSlow132);
		float fSlow134 = std::floor(fSlow132);
		float fSlow135 = fSlow134 + (1.0f - fSlow132);
		float fSlow136 = std::max<float>(15940.032f * fSlow127, 23.44895f);
		float fSlow137 = std::max<float>(2e+01f, std::fabs(fSlow136));
		float fSlow138 = fConst18 * fSlow137;
		float fSlow139 = fConst62 / fSlow137;
		float fSlow140 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow136));
		int iSlow141 = static_cast<int>(fSlow140);
		float fSlow142 = std::floor(fSlow140);
		float fSlow143 = fSlow142 + (1.0f - fSlow140);
		float fSlow144 = std::max<float>(12784.989f * fSlow127, 23.44895f);
		float fSlow145 = std::max<float>(2e+01f, std::fabs(fSlow144));
		float fSlow146 = fConst18 * fSlow145;
		float fSlow147 = fConst62 / fSlow145;
		float fSlow148 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow144));
		int iSlow149 = static_cast<int>(fSlow148);
		float fSlow150 = std::floor(fSlow148);
		float fSlow151 = fSlow150 + (1.0f - fSlow148);
		float fSlow152 = std::max<float>(9794.762f * fSlow127, 23.44895f);
		float fSlow153 = std::max<float>(2e+01f, std::fabs(fSlow152));
		float fSlow154 = fConst18 * fSlow153;
		float fSlow155 = fConst62 / fSlow153;
		float fSlow156 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow152));
		int iSlow157 = static_cast<int>(fSlow156);
		float fSlow158 = std::floor(fSlow156);
		float fSlow159 = fSlow158 + (1.0f - fSlow156);
		float fSlow160 = std::max<float>(7016.4395f * fSlow127, 23.44895f);
		float fSlow161 = std::max<float>(2e+01f, std::fabs(fSlow160));
		float fSlow162 = fConst18 * fSlow161;
		float fSlow163 = fConst62 / fSlow161;
		float fSlow164 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow160));
		int iSlow165 = static_cast<int>(fSlow164);
		float fSlow166 = std::floor(fSlow164);
		float fSlow167 = fSlow166 + (1.0f - fSlow164);
		float fSlow168 = std::max<float>(4709.02f * fSlow127, 23.44895f);
		float fSlow169 = std::max<float>(2e+01f, std::fabs(fSlow168));
		float fSlow170 = fConst18 * fSlow169;
		float fSlow171 = fConst62 / fSlow169;
		float fSlow172 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow168));
		int iSlow173 = static_cast<int>(fSlow172);
		int iSlow174 = iSlow173 + 1;
		float fSlow175 = std::floor(fSlow172);
		float fSlow176 = fSlow172 - fSlow175;
		float fSlow177 = fSlow175 + (1.0f - fSlow172);
		int iSlow178 = iSlow165 + 1;
		float fSlow179 = fSlow164 - fSlow166;
		int iSlow180 = iSlow157 + 1;
		float fSlow181 = fSlow156 - fSlow158;
		int iSlow182 = iSlow149 + 1;
		float fSlow183 = fSlow148 - fSlow150;
		int iSlow184 = iSlow141 + 1;
		float fSlow185 = fSlow140 - fSlow142;
		int iSlow186 = iSlow133 + 1;
		float fSlow187 = fSlow132 - fSlow134;
		float fSlow188 = 1.0f / fSlow129;
		float fSlow189 = 1.0f / fSlow137;
		float fSlow190 = 1.0f / fSlow145;
		float fSlow191 = 1.0f / fSlow153;
		float fSlow192 = 1.0f / fSlow161;
		float fSlow193 = 1.0f / fSlow169;
		float fSlow194 = 0.15f * (1.0f - fSlow125);
		float fSlow195 = 6.5f * static_cast<float>(fHslider41);
		float fSlow196 = static_cast<float>(fHslider43) * static_cast<float>(fHslider42);
		float fSlow197 = fConst13 * fSlow196;
		float fSlow198 = 0.4f * static_cast<float>(fHslider44) + 1.0f;
		float fSlow199 = static_cast<float>(fCheckbox48);
		float fSlow200 = static_cast<float>(fCheckbox49);
		float fSlow201 = static_cast<float>(fCheckbox50);
		float fSlow202 = static_cast<float>(fCheckbox51);
		float fSlow203 = static_cast<float>(fCheckbox52);
		float fSlow204 = static_cast<float>(fCheckbox53);
		float fSlow205 = static_cast<float>(fCheckbox54);
		float fSlow206 = static_cast<float>(fCheckbox55);
		float fSlow207 = static_cast<float>(fCheckbox56);
		float fSlow208 = static_cast<float>(fCheckbox57);
		float fSlow209 = static_cast<float>(fCheckbox58);
		float fSlow210 = static_cast<float>(fCheckbox59);
		float fSlow211 = static_cast<float>(fCheckbox60);
		float fSlow212 = static_cast<float>(fCheckbox61);
		float fSlow213 = static_cast<float>(fCheckbox62);
		float fSlow214 = static_cast<float>(fCheckbox63);
		float fSlow215 = fConst14 * (static_cast<float>(fHslider45) / fSlow196);
		int iSlow216 = static_cast<int>(fSlow215);
		int iSlow217 = std::min<int>(16385, std::max<int>(0, iSlow216 + 1));
		float fSlow218 = std::floor(fSlow215);
		float fSlow219 = fSlow215 - fSlow218;
		int iSlow220 = std::min<int>(16385, std::max<int>(0, iSlow216));
		float fSlow221 = fSlow218 + (1.0f - fSlow215);
		float fSlow222 = std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider46));
		float fSlow223 = 1.0f / fSlow222;
		float fSlow224 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider47));
		float fSlow225 = 2.0f * (static_cast<float>(fHslider48) / (fSlow119 * fSlow123));
		float fSlow226 = std::tan(fConst61 * static_cast<float>(fHslider49));
		float fSlow227 = mydsp_faustpower2_f(fSlow226);
		float fSlow228 = 2.0f * (1.0f - 1.0f / fSlow227);
		float fSlow229 = 1.0f / fSlow226;
		float fSlow230 = (fSlow229 + -1.4142135f) / fSlow226 + 1.0f;
		float fSlow231 = (fSlow229 + 1.4142135f) / fSlow226 + 1.0f;
		float fSlow232 = 1.0f / fSlow231;
		float fSlow233 = static_cast<float>(fHslider51) * static_cast<float>(fHslider50);
		float fSlow234 = fConst13 * fSlow233;
		float fSlow235 = static_cast<float>(fCheckbox64);
		float fSlow236 = static_cast<float>(fCheckbox65);
		float fSlow237 = static_cast<float>(fCheckbox66);
		float fSlow238 = static_cast<float>(fCheckbox67);
		float fSlow239 = static_cast<float>(fCheckbox68);
		float fSlow240 = static_cast<float>(fCheckbox69);
		float fSlow241 = static_cast<float>(fCheckbox70);
		float fSlow242 = static_cast<float>(fCheckbox71);
		float fSlow243 = static_cast<float>(fCheckbox72);
		float fSlow244 = static_cast<float>(fCheckbox73);
		float fSlow245 = static_cast<float>(fCheckbox74);
		float fSlow246 = static_cast<float>(fCheckbox75);
		float fSlow247 = static_cast<float>(fCheckbox76);
		float fSlow248 = static_cast<float>(fCheckbox77);
		float fSlow249 = static_cast<float>(fCheckbox78);
		float fSlow250 = static_cast<float>(fCheckbox79);
		float fSlow251 = fConst14 * (static_cast<float>(fHslider52) / fSlow233);
		int iSlow252 = static_cast<int>(fSlow251);
		int iSlow253 = std::min<int>(16385, std::max<int>(0, iSlow252 + 1));
		float fSlow254 = std::floor(fSlow251);
		float fSlow255 = fSlow251 - fSlow254;
		int iSlow256 = std::min<int>(16385, std::max<int>(0, iSlow252));
		float fSlow257 = fSlow254 + (1.0f - fSlow251);
		float fSlow258 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider53));
		float fSlow259 = std::tan(fConst61 * static_cast<float>(fHslider54));
		float fSlow260 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fSlow259));
		float fSlow261 = 1.0f / static_cast<float>(fHslider55);
		float fSlow262 = 1.0f / fSlow259;
		float fSlow263 = (fSlow262 - fSlow261) / fSlow259 + 1.0f;
		float fSlow264 = (fSlow261 + fSlow262) / fSlow259 + 1.0f;
		float fSlow265 = 1.0f / fSlow264;
		float fSlow266 = static_cast<float>(fHslider56);
		float fSlow267 = 2.34f * (fSlow266 / (fSlow259 * fSlow264));
		float fSlow268 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider57));
		float fSlow269 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider59) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider58));
		float fSlow270 = fConst70 * fSlow269;
		float fSlow271 = fConst71 * fSlow269;
		float fSlow272 = 1.0f - fSlow266;
		float fSlow273 = 0.4f * static_cast<float>(fHslider60) + 1.0f;
		float fSlow274 = static_cast<float>(fHslider61);
		float fSlow275 = 1.0f / (fSlow227 * fSlow231);
		float fSlow276 = static_cast<float>(fHslider62);
		float fSlow277 = static_cast<float>(fHslider63);
		float fSlow278 = static_cast<float>(fHslider64);
		float fSlow279 = static_cast<float>(fHslider66) * static_cast<float>(fHslider65);
		float fSlow280 = fConst13 * fSlow279;
		float fSlow281 = 0.4f * static_cast<float>(fHslider67) + 1.0f;
		float fSlow282 = static_cast<float>(fCheckbox80);
		float fSlow283 = static_cast<float>(fCheckbox81);
		float fSlow284 = static_cast<float>(fCheckbox82);
		float fSlow285 = static_cast<float>(fCheckbox83);
		float fSlow286 = static_cast<float>(fCheckbox84);
		float fSlow287 = static_cast<float>(fCheckbox85);
		float fSlow288 = static_cast<float>(fCheckbox86);
		float fSlow289 = static_cast<float>(fCheckbox87);
		float fSlow290 = static_cast<float>(fCheckbox88);
		float fSlow291 = static_cast<float>(fCheckbox89);
		float fSlow292 = static_cast<float>(fCheckbox90);
		float fSlow293 = static_cast<float>(fCheckbox91);
		float fSlow294 = static_cast<float>(fCheckbox92);
		float fSlow295 = static_cast<float>(fCheckbox93);
		float fSlow296 = static_cast<float>(fCheckbox94);
		float fSlow297 = static_cast<float>(fCheckbox95);
		float fSlow298 = fConst14 * (static_cast<float>(fHslider68) / fSlow279);
		int iSlow299 = static_cast<int>(fSlow298);
		int iSlow300 = std::min<int>(16385, std::max<int>(0, iSlow299 + 1));
		float fSlow301 = std::floor(fSlow298);
		float fSlow302 = fSlow298 - fSlow301;
		int iSlow303 = std::min<int>(16385, std::max<int>(0, iSlow299));
		float fSlow304 = fSlow301 + (1.0f - fSlow298);
		float fSlow305 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider69));
		float fSlow306 = static_cast<float>(fHslider70);
		float fSlow307 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider72) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider71));
		float fSlow308 = static_cast<float>(fHslider73);
		float fSlow309 = static_cast<float>(fHslider74);
		float fSlow310 = fSlow309 * (fSlow308 - fSlow277);
		float fSlow311 = static_cast<float>(fHslider75);
		float fSlow312 = static_cast<float>(fHslider76);
		float fSlow313 = 1.8f * fSlow312;
		float fSlow314 = fConst60 * (1.0f - fSlow312);
		float fSlow315 = static_cast<float>(fHslider77);
		float fSlow316 = 5e+03f * fSlow31;
		float fSlow317 = 1.0f / static_cast<float>(fHslider78);
		float fSlow318 = 85.0f * fSlow31;
		float fSlow319 = fSlow31 * fSlow32;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fRec4[0] = fSlow1 + (fRec4[1] - std::floor(fRec4[1]));
			int iTemp0 = fRec4[0] < fRec4[1];
			iVec1[IOTA0 & 32767] = iTemp0;
			iRec3[0] = ((iTemp0) ? (iRec3[1] + 1) % 16 : iRec3[1]);
			if (iTemp0) {
				uint64_t now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
					std::chrono::system_clock::now().time_since_epoch()).count();
				m_lastBeatTimeMs.store(now_ms);
				m_lastBeatStep.store(iRec3[0]);
				if (iRec3[0] == 0) {
					m_lastStep0TimeMs.store(now_ms);
				}
			}
			int iTemp1 = static_cast<int>((((iRec3[0] % 2) == 1) ? fSlow25 * static_cast<float>(iVec1[(IOTA0 - iSlow24) & 32767]) + fSlow23 * static_cast<float>(iVec1[(IOTA0 - iSlow21) & 32767]) : static_cast<float>(iTemp0))) & (((iRec3[0] >= 8) ? ((iRec3[0] >= 12) ? ((iRec3[0] >= 14) ? ((iRec3[0] >= 15) ? fSlow18 : fSlow17) : ((iRec3[0] >= 13) ? fSlow16 : fSlow15)) : ((iRec3[0] >= 10) ? ((iRec3[0] >= 11) ? fSlow14 : fSlow13) : ((iRec3[0] >= 9) ? fSlow12 : fSlow11))) : ((iRec3[0] >= 4) ? ((iRec3[0] >= 6) ? ((iRec3[0] >= 7) ? fSlow10 : fSlow9) : ((iRec3[0] >= 5) ? fSlow8 : fSlow7)) : ((iRec3[0] >= 2) ? ((iRec3[0] >= 3) ? fSlow6 : fSlow5) : ((iRec3[0] >= 1) ? fSlow4 : fSlow3)))) > 0.0f);
			iVec2[0] = iTemp1;
			iRec5[0] = (iRec5[1] + (iRec5[1] > 0)) * (iTemp1 <= iVec2[1]) + (iTemp1 > iVec2[1]);
			float fTemp2 = static_cast<float>(iRec5[0]);
			int iTemp3 = 1 - iVec0[1];
			float fTemp4 = ((iTemp3) ? 0.0f : fConst17 + fRec7[1]);
			fRec7[0] = fTemp4 - std::floor(fTemp4);
			float fTemp5 = std::max<float>(fSlow28 + ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec7[0]), 65535))], 23.44895f);
			float fTemp6 = std::max<float>(2e+01f, std::fabs(fTemp5));
			float fTemp7 = ((iTemp3) ? 0.0f : fRec8[1] + fConst18 * fTemp6);
			fRec8[0] = fTemp7 - std::floor(fTemp7);
			float fTemp8 = mydsp_faustpower2_f(2.0f * fRec8[0] + -1.0f);
			fVec4[0] = fTemp8;
			float fTemp9 = static_cast<float>(iVec0[1]);
			float fTemp10 = fTemp9 * (fTemp8 - fVec4[1]) / fTemp6;
			fVec5[IOTA0 & 2047] = fTemp10;
			float fTemp11 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fTemp5));
			int iTemp12 = static_cast<int>(fTemp11);
			float fTemp13 = std::floor(fTemp11);
			float fTemp14 = ((iTemp3) ? 0.0f : fConst20 + fRec11[1]);
			fRec11[0] = fTemp14 - std::floor(fTemp14);
			float fTemp15 = std::max<float>(1.1920929e-07f, std::fabs(fSlow29 + 2.0f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec11[0]), 65535))]));
			float fTemp16 = fRec9[1] + fConst18 * fTemp15;
			float fTemp17 = fTemp16 + -1.0f;
			int iTemp18 = fTemp17 < 0.0f;
			fRec9[0] = ((iTemp18) ? fTemp16 : fTemp17);
			float fRec10 = ((iTemp18) ? fTemp16 : fTemp16 + fTemp17 * (1.0f - fConst0 / fTemp15));
			fRec2[0] = (0.6f * (2.0f * fRec10 + -1.0f) + fConst14 * (fTemp10 - fVec5[(IOTA0 - iTemp12) & 2047] * (fTemp13 + (1.0f - fTemp11)) - (fTemp11 - fTemp13) * fVec5[(IOTA0 - (iTemp12 + 1)) & 2047])) * std::max<float>(0.0f, std::min<float>(fConst16 * fTemp2, fSlow26 * (fConst15 - fTemp2) + 1.0f)) * (((((iRec3[0] == 0) | (iRec3[0] == 4)) | (iRec3[0] == 8)) | (iRec3[0] == 12)) ? fSlow2 : 1.0f) - fConst12 * (fConst10 * fRec2[2] + fConst8 * fRec2[1]);
			fRec1[0] = fConst21 * (fRec2[2] + (fRec2[0] - 2.0f * fRec2[1])) - fConst5 * (fConst4 * fRec1[2] + fConst2 * fRec1[1]);
			float fTemp19 = fRec1[2] + fRec1[0] + 2.0f * fRec1[1];
			fVec6[IOTA0 & 255] = fTemp19;
			float fTemp20 = ((iTemp3) ? 0.0f : fSlow30 + fRec12[1]);
			fRec12[0] = fTemp20 - std::floor(fTemp20);
			float fTemp21 = ((iTemp3) ? 0.0f : fSlow40 + fRec17[1]);
			fRec17[0] = fTemp21 - std::floor(fTemp21);
			fRec24[0] = fSlow43 + (fRec24[1] - std::floor(fRec24[1]));
			int iTemp22 = fRec24[0] < fRec24[1];
			iVec7[IOTA0 & 32767] = iTemp22;
			iRec23[0] = ((iTemp22) ? (iRec23[1] + 1) % 16 : iRec23[1]);
			int iTemp23 = static_cast<int>((((iRec23[0] % 2) == 1) ? fSlow67 * static_cast<float>(iVec7[(IOTA0 - iSlow66) & 32767]) + fSlow65 * static_cast<float>(iVec7[(IOTA0 - iSlow63) & 32767]) : static_cast<float>(iTemp22)));
			int iTemp24 = iTemp23 & (iTemp23 & (((iRec23[0] >= 8) ? ((iRec23[0] >= 12) ? ((iRec23[0] >= 14) ? ((iRec23[0] >= 15) ? fSlow60 : fSlow59) : ((iRec23[0] >= 13) ? fSlow58 : fSlow57)) : ((iRec23[0] >= 10) ? ((iRec23[0] >= 11) ? fSlow56 : fSlow55) : ((iRec23[0] >= 9) ? fSlow54 : fSlow53))) : ((iRec23[0] >= 4) ? ((iRec23[0] >= 6) ? ((iRec23[0] >= 7) ? fSlow52 : fSlow51) : ((iRec23[0] >= 5) ? fSlow50 : fSlow49)) : ((iRec23[0] >= 2) ? ((iRec23[0] >= 3) ? fSlow48 : fSlow47) : ((iRec23[0] >= 1) ? fSlow46 : fSlow45)))) > 0.0f));
			iVec8[0] = iTemp24;
			iRec25[0] = (iRec25[1] + (iRec25[1] > 0)) * (iTemp24 <= iVec8[1]) + (iTemp24 > iVec8[1]);
			float fTemp25 = static_cast<float>(iRec25[0]);
			float fTemp26 = std::max<float>(0.0f, std::min<float>(fConst16 * fTemp25, fSlow68 * (fConst15 - fTemp25) + 1.0f)) * (((((iRec23[0] == 0) | (iRec23[0] == 4)) | (iRec23[0] == 8)) | (iRec23[0] == 12)) ? fSlow44 : 1.0f);
			float fTemp27 = ((iTemp3) ? 0.0f : fRec22[1] + fConst18 * (fSlow69 + 1.5e+03f * fTemp26));
			fRec22[0] = fTemp27 - std::floor(fTemp27);
			float fTemp28 = fTemp26 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec22[0]), 65535))];
			fRec26[0] = -(fConst36 * (fConst35 * fRec26[1] - (fRec19[(IOTA0 - 1400) & 2047] + fRec19[(IOTA0 - 1401) & 2047])));
			fRec27[0] = -(fConst36 * (fConst35 * fRec27[1] - (fRec18[(IOTA0 - 1118) & 2047] + fRec18[(IOTA0 - 1119) & 2047])));
			float fTemp29 = fRec27[0] + fRec26[0];
			fRec28[0] = -(fConst36 * (fConst35 * fRec28[1] - (fRec20[(IOTA0 - 1724) & 2047] + fRec20[(IOTA0 - 1725) & 2047])));
			fRec29[0] = -(fConst36 * (fConst35 * fRec29[1] - (fRec21[(IOTA0 - 2090) & 4095] + fRec21[(IOTA0 - 2091) & 4095])));
			fRec18[IOTA0 & 2047] = fSlow70 * (fRec29[0] + fRec28[0] + fTemp29) + fTemp28;
			float fTemp30 = fRec27[0] - fRec26[0];
			fRec19[IOTA0 & 2047] = fTemp28 - fSlow70 * (fRec29[0] - (fRec28[0] + fTemp30));
			fRec20[IOTA0 & 2047] = fTemp28 - fSlow70 * (fRec29[0] - (fTemp29 - fRec28[0]));
			fRec21[IOTA0 & 4095] = fTemp28 + fSlow70 * (fRec29[0] - (fRec28[0] - fTemp30));
			float fTemp31 = (fRec18[IOTA0 & 2047] + fRec19[IOTA0 & 2047] + fRec20[IOTA0 & 2047] + fRec21[IOTA0 & 4095]) * (fSlow41 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec17[0]), 65535))] + 1.0f);
			float fTemp32 = std::fabs(0.25f * fTemp31);
			float fTemp33 = ((fTemp32 > fRec16[1]) ? fSlow75 : fSlow73);
			fRec16[0] = fTemp32 * (1.0f - fTemp33) + fRec16[1] * fTemp33;
			fRec15[0] = fSlow76 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec16[0])) - fSlow39, 0.0f) * fSlow38 + fSlow37 * fRec15[1];
			fRec14[0] = 0.25f * fTemp31 * std::pow(1e+01f, 0.05f * fRec15[0]) - fConst33 * (fConst31 * fRec14[2] + fConst29 * fRec14[1]);
			fRec13[0] = fConst37 * (fRec14[2] + (fRec14[0] - 2.0f * fRec14[1])) - fConst26 * (fConst25 * fRec13[2] + fConst23 * fRec13[1]);
			fRec35[0] = fSlow80 + (fRec35[1] - std::floor(fRec35[1]));
			int iTemp34 = fRec35[0] < fRec35[1];
			iVec9[IOTA0 & 32767] = iTemp34;
			iRec34[0] = ((iTemp34) ? (iRec34[1] + 1) % 16 : iRec34[1]);
			int iTemp35 = static_cast<int>((((iRec34[0] % 2) == 1) ? fSlow103 * static_cast<float>(iVec9[(IOTA0 - iSlow102) & 32767]) + fSlow101 * static_cast<float>(iVec9[(IOTA0 - iSlow99) & 32767]) : static_cast<float>(iTemp34))) & (((iRec34[0] >= 8) ? ((iRec34[0] >= 12) ? ((iRec34[0] >= 14) ? ((iRec34[0] >= 15) ? fSlow96 : fSlow95) : ((iRec34[0] >= 13) ? fSlow94 : fSlow93)) : ((iRec34[0] >= 10) ? ((iRec34[0] >= 11) ? fSlow92 : fSlow91) : ((iRec34[0] >= 9) ? fSlow90 : fSlow89))) : ((iRec34[0] >= 4) ? ((iRec34[0] >= 6) ? ((iRec34[0] >= 7) ? fSlow88 : fSlow87) : ((iRec34[0] >= 5) ? fSlow86 : fSlow85)) : ((iRec34[0] >= 2) ? ((iRec34[0] >= 3) ? fSlow84 : fSlow83) : ((iRec34[0] >= 1) ? fSlow82 : fSlow81)))) > 0.0f);
			iVec10[0] = iTemp35;
			fRec33[0] = (fConst18 + fRec33[1]) * (1.0f - static_cast<float>(iTemp35));
			fRec32[0] = fConst51 * std::exp(-(fSlow104 * fRec33[0])) + fConst50 * fRec32[1];
			iRec37[0] = (iRec37[1] + (iRec37[1] > 0)) * (iTemp35 <= iVec10[1]) + (iTemp35 > iVec10[1]);
			float fTemp36 = static_cast<float>(iRec37[0]);
			iRec39[0] = 1103515245 * iRec39[1] + 12345;
			float fTemp37 = static_cast<float>(iRec39[0]);
			fVec11[0] = fTemp37;
			fRec38[0] = fConst57 * (4.656613e-10f * (fTemp37 + fVec11[1]) - fConst56 * fRec38[1]);
			fRec41[0] = fConst59 + fRec41[1] * static_cast<float>(1 - iTemp35);
			float fTemp38 = std::max<float>(0.01f, 0.6f - 0.15f * (fSlow106 - fSlow114 * std::sin(6.2831855f * (fRec41[0] - std::floor(fRec41[0])))));
			fRec40[0] = fRec40[1] * (1.0f - fTemp38) + fTemp38 * (fSlow113 * fRec36[(IOTA0 - iSlow112) & 8191] + fSlow111 * fRec36[(IOTA0 - iSlow109) & 8191]);
			fRec36[IOTA0 & 8191] = fSlow116 * (fRec40[0] / (fSlow115 * std::fabs(fRec40[0]) + 1.0f)) + fRec38[0] * std::max<float>(0.0f, std::min<float>(fConst53 * fTemp36, fConst54 * (fConst52 - fTemp36) + 1.0f)) * (((((iRec34[0] == 0) | (iRec34[0] == 4)) | (iRec34[0] == 8)) | (iRec34[0] == 12)) ? fSlow105 : 1.0f);
			fRec31[0] = fRec36[IOTA0 & 8191] * fRec32[0] - fConst49 * (fConst47 * fRec31[2] + fConst45 * fRec31[1]);
			fRec30[0] = fConst60 * (fRec31[2] + (fRec31[0] - 2.0f * fRec31[1])) - fConst42 * (fConst41 * fRec30[2] + fConst39 * fRec30[1]);
			float fTemp39 = ((iTemp3) ? 0.0f : fSlow130 + fRec43[1]);
			fRec43[0] = fTemp39 - std::floor(fTemp39);
			float fTemp40 = mydsp_faustpower2_f(2.0f * fRec43[0] + -1.0f);
			fVec12[0] = fTemp40;
			float fTemp41 = fTemp40 - fVec12[1];
			float fTemp42 = fSlow131 * fTemp9 * fTemp41;
			fVec13[IOTA0 & 127] = fTemp42;
			float fTemp43 = ((iTemp3) ? 0.0f : fSlow138 + fRec44[1]);
			fRec44[0] = fTemp43 - std::floor(fTemp43);
			float fTemp44 = mydsp_faustpower2_f(2.0f * fRec44[0] + -1.0f);
			fVec14[0] = fTemp44;
			float fTemp45 = fTemp44 - fVec14[1];
			float fTemp46 = fSlow139 * fTemp9 * fTemp45;
			fVec15[IOTA0 & 127] = fTemp46;
			float fTemp47 = ((iTemp3) ? 0.0f : fSlow146 + fRec45[1]);
			fRec45[0] = fTemp47 - std::floor(fTemp47);
			float fTemp48 = mydsp_faustpower2_f(2.0f * fRec45[0] + -1.0f);
			fVec16[0] = fTemp48;
			float fTemp49 = fTemp48 - fVec16[1];
			float fTemp50 = fSlow147 * fTemp9 * fTemp49;
			fVec17[IOTA0 & 127] = fTemp50;
			float fTemp51 = ((iTemp3) ? 0.0f : fSlow154 + fRec46[1]);
			fRec46[0] = fTemp51 - std::floor(fTemp51);
			float fTemp52 = mydsp_faustpower2_f(2.0f * fRec46[0] + -1.0f);
			fVec18[0] = fTemp52;
			float fTemp53 = fTemp52 - fVec18[1];
			float fTemp54 = fSlow155 * fTemp9 * fTemp53;
			fVec19[IOTA0 & 255] = fTemp54;
			float fTemp55 = ((iTemp3) ? 0.0f : fSlow162 + fRec47[1]);
			fRec47[0] = fTemp55 - std::floor(fTemp55);
			float fTemp56 = mydsp_faustpower2_f(2.0f * fRec47[0] + -1.0f);
			fVec20[0] = fTemp56;
			float fTemp57 = fTemp56 - fVec20[1];
			float fTemp58 = fSlow163 * fTemp9 * fTemp57;
			fVec21[IOTA0 & 255] = fTemp58;
			float fTemp59 = ((iTemp3) ? 0.0f : fSlow170 + fRec48[1]);
			fRec48[0] = fTemp59 - std::floor(fTemp59);
			float fTemp60 = mydsp_faustpower2_f(2.0f * fRec48[0] + -1.0f);
			fVec22[0] = fTemp60;
			float fTemp61 = fTemp60 - fVec22[1];
			float fTemp62 = fSlow171 * fTemp9 * fTemp61;
			fVec23[IOTA0 & 511] = fTemp62;
			float fTemp63 = fSlow194 * (fConst62 * fTemp9 * (fSlow193 * fTemp61 + fSlow192 * fTemp57 + fSlow191 * fTemp53 + fSlow190 * fTemp49 + fSlow189 * fTemp45 + fSlow188 * fTemp41) - (fSlow187 * fVec13[(IOTA0 - iSlow186) & 127] + fSlow185 * fVec15[(IOTA0 - iSlow184) & 127] + fSlow183 * fVec17[(IOTA0 - iSlow182) & 127] + fSlow181 * fVec19[(IOTA0 - iSlow180) & 255] + fSlow179 * fVec21[(IOTA0 - iSlow178) & 255] + fSlow177 * fVec23[(IOTA0 - iSlow173) & 511] + fSlow176 * fVec23[(IOTA0 - iSlow174) & 511] + fSlow167 * fVec21[(IOTA0 - iSlow165) & 255] + fSlow159 * fVec19[(IOTA0 - iSlow157) & 255] + fSlow151 * fVec17[(IOTA0 - iSlow149) & 127] + fSlow143 * fVec15[(IOTA0 - iSlow141) & 127] + fSlow135 * fVec13[(IOTA0 - iSlow133) & 127])) + fSlow126 * fTemp37;
			fRec50[0] = fSlow197 + (fRec50[1] - std::floor(fRec50[1]));
			int iTemp64 = fRec50[0] < fRec50[1];
			iVec24[IOTA0 & 32767] = iTemp64;
			iRec49[0] = ((iTemp64) ? (iRec49[1] + 1) % 16 : iRec49[1]);
			int iTemp65 = static_cast<int>((((iRec49[0] % 2) == 1) ? fSlow221 * static_cast<float>(iVec24[(IOTA0 - iSlow220) & 32767]) + fSlow219 * static_cast<float>(iVec24[(IOTA0 - iSlow217) & 32767]) : static_cast<float>(iTemp64))) & (((iRec49[0] >= 8) ? ((iRec49[0] >= 12) ? ((iRec49[0] >= 14) ? ((iRec49[0] >= 15) ? fSlow214 : fSlow213) : ((iRec49[0] >= 13) ? fSlow212 : fSlow211)) : ((iRec49[0] >= 10) ? ((iRec49[0] >= 11) ? fSlow210 : fSlow209) : ((iRec49[0] >= 9) ? fSlow208 : fSlow207))) : ((iRec49[0] >= 4) ? ((iRec49[0] >= 6) ? ((iRec49[0] >= 7) ? fSlow206 : fSlow205) : ((iRec49[0] >= 5) ? fSlow204 : fSlow203)) : ((iRec49[0] >= 2) ? ((iRec49[0] >= 3) ? fSlow202 : fSlow201) : ((iRec49[0] >= 1) ? fSlow200 : fSlow199)))) > 0.0f);
			iVec25[0] = iTemp65;
			iRec51[0] = (iRec51[1] + (iRec51[1] > 0)) * (iTemp65 <= iVec25[1]) + (iTemp65 > iVec25[1]);
			float fTemp66 = static_cast<float>(iRec51[0]);
			fRec42[0] = fTemp63 * std::max<float>(0.0f, std::min<float>(fSlow223 * fTemp66, fSlow224 * (fSlow222 - fTemp66) + 1.0f)) * (((((iRec49[0] == 0) | (iRec49[0] == 4)) | (iRec49[0] == 8)) | (iRec49[0] == 12)) ? fSlow198 : 1.0f) / (fSlow195 * std::fabs(fTemp63) + 1.0f) - fSlow124 * (fSlow122 * fRec42[2] + fSlow120 * fRec42[1]);
			fRec56[0] = fSlow234 + (fRec56[1] - std::floor(fRec56[1]));
			int iTemp67 = fRec56[0] < fRec56[1];
			iVec26[IOTA0 & 32767] = iTemp67;
			iRec55[0] = ((iTemp67) ? (iRec55[1] + 1) % 16 : iRec55[1]);
			int iTemp68 = static_cast<int>((((iRec55[0] % 2) == 1) ? fSlow257 * static_cast<float>(iVec26[(IOTA0 - iSlow256) & 32767]) + fSlow255 * static_cast<float>(iVec26[(IOTA0 - iSlow253) & 32767]) : static_cast<float>(iTemp67))) & (((iRec55[0] >= 8) ? ((iRec55[0] >= 12) ? ((iRec55[0] >= 14) ? ((iRec55[0] >= 15) ? fSlow250 : fSlow249) : ((iRec55[0] >= 13) ? fSlow248 : fSlow247)) : ((iRec55[0] >= 10) ? ((iRec55[0] >= 11) ? fSlow246 : fSlow245) : ((iRec55[0] >= 9) ? fSlow244 : fSlow243))) : ((iRec55[0] >= 4) ? ((iRec55[0] >= 6) ? ((iRec55[0] >= 7) ? fSlow242 : fSlow241) : ((iRec55[0] >= 5) ? fSlow240 : fSlow239)) : ((iRec55[0] >= 2) ? ((iRec55[0] >= 3) ? fSlow238 : fSlow237) : ((iRec55[0] >= 1) ? fSlow236 : fSlow235)))) > 0.0f);
			iVec27[0] = iTemp68;
			iRec54[0] = (iRec54[1] + (iRec54[1] > 0)) * (iTemp68 <= iVec27[1]) + (iTemp68 > iVec27[1]);
			float fTemp69 = static_cast<float>(iRec54[0]);
			fRec57[0] = 4.656613e-10f * fTemp37 - fSlow265 * (fSlow263 * fRec57[2] + fSlow260 * fRec57[1]);
			float fTemp70 = ((iTemp3) ? 0.0f : fSlow270 + fRec58[1]);
			fRec58[0] = fTemp70 - std::floor(fTemp70);
			float fTemp71 = ((iTemp3) ? 0.0f : fSlow271 + fRec59[1]);
			fRec59[0] = fTemp71 - std::floor(fTemp71);
			fRec53[0] = fSlow274 * (((((iRec55[0] == 0) | (iRec55[0] == 4)) | (iRec55[0] == 8)) | (iRec55[0] == 12)) ? fSlow273 : 1.0f) * (fSlow272 * (0.65f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec59[0]), 65535))] + 0.35f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec58[0]), 65535))]) * std::max<float>(0.0f, std::min<float>(fConst69 * fTemp69, fSlow268 * (fConst68 - fTemp69) + 1.0f)) + fSlow267 * (fRec57[0] - fRec57[2]) * std::max<float>(0.0f, std::min<float>(fConst53 * fTemp69, fSlow258 * (fConst52 - fTemp69) + 1.0f))) - fSlow232 * (fSlow230 * fRec53[2] + fSlow228 * fRec53[1]);
			fRec52[0] = fSlow275 * (fRec53[2] + (fRec53[0] - 2.0f * fRec53[1])) - fConst67 * (fConst66 * fRec52[2] + fConst64 * fRec52[1]);
			fRec75[0] = fSlow280 + (fRec75[1] - std::floor(fRec75[1]));
			int iTemp72 = fRec75[0] < fRec75[1];
			iVec28[IOTA0 & 32767] = iTemp72;
			iRec74[0] = ((iTemp72) ? (iRec74[1] + 1) % 16 : iRec74[1]);
			int iTemp73 = static_cast<int>((((iRec74[0] % 2) == 1) ? fSlow304 * static_cast<float>(iVec28[(IOTA0 - iSlow303) & 32767]) + fSlow302 * static_cast<float>(iVec28[(IOTA0 - iSlow300) & 32767]) : static_cast<float>(iTemp72))) & (((iRec74[0] >= 8) ? ((iRec74[0] >= 12) ? ((iRec74[0] >= 14) ? ((iRec74[0] >= 15) ? fSlow297 : fSlow296) : ((iRec74[0] >= 13) ? fSlow295 : fSlow294)) : ((iRec74[0] >= 10) ? ((iRec74[0] >= 11) ? fSlow293 : fSlow292) : ((iRec74[0] >= 9) ? fSlow291 : fSlow290))) : ((iRec74[0] >= 4) ? ((iRec74[0] >= 6) ? ((iRec74[0] >= 7) ? fSlow289 : fSlow288) : ((iRec74[0] >= 5) ? fSlow287 : fSlow286)) : ((iRec74[0] >= 2) ? ((iRec74[0] >= 3) ? fSlow285 : fSlow284) : ((iRec74[0] >= 1) ? fSlow283 : fSlow282)))) > 0.0f);
			iVec29[0] = iTemp73;
			iRec76[0] = (iRec76[1] + (iRec76[1] > 0)) * (iTemp73 <= iVec29[1]) + (iTemp73 > iVec29[1]);
			float fTemp74 = static_cast<float>(iRec76[0]);
			float fTemp75 = fConst53 * fTemp74;
			float fTemp76 = fConst52 - fTemp74;
			float fTemp77 = ((iTemp3) ? 0.0f : fRec77[1] + fConst18 * (fSlow307 + fSlow306 * std::pow(std::max<float>(0.0f, std::min<float>(fTemp75, fConst16 * fTemp76 + 1.0f)), 1.5f)));
			fRec77[0] = fTemp77 - std::floor(fTemp77);
			float fTemp78 = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec77[0]), 65535))] * std::max<float>(0.0f, std::min<float>(fTemp75, fSlow305 * fTemp76 + 1.0f)) * (((((iRec74[0] == 0) | (iRec74[0] == 4)) | (iRec74[0] == 8)) | (iRec74[0] == 12)) ? fSlow281 : 1.0f);
			fRec73[0] = fConst83 * std::fabs(fTemp78) + fConst82 * fRec73[1];
			float fTemp79 = std::max<float>(0.0f, fRec73[0] - fSlow278);
			float fTemp80 = 1.0f / std::tan(fConst61 * std::max<float>(fSlow277, fSlow308 - fSlow310 * fTemp79));
			float fTemp81 = tanhf(fSlow311 * (fTemp78 / (fSlow309 * fTemp79 + 1.0f)));
			fVec30[0] = fTemp81;
			fRec72[0] = -((fRec72[1] * (1.0f - fTemp80) - (fTemp81 + fVec30[1])) / (fTemp80 + 1.0f));
			fRec71[0] = fRec72[0] - fConst81 * (fConst80 * fRec71[2] + fConst78 * fRec71[1]);
			fRec70[0] = fConst81 * (fRec71[2] + fRec71[0] + 2.0f * fRec71[1]) - fConst49 * (fConst47 * fRec70[2] + fConst45 * fRec70[1]);
			float fTemp82 = fRec70[2] + (fRec70[0] - 2.0f * fRec70[1]);
			fRec69[0] = fConst60 * fTemp82 - fConst12 * (fConst10 * fRec69[2] + fConst8 * fRec69[1]);
			fRec68[0] = fConst21 * (fRec69[2] + (fRec69[0] - 2.0f * fRec69[1])) - fConst76 * (fConst75 * fRec68[2] + fConst73 * fRec68[1]);
			float fTemp83 = fConst76 * (fRec68[2] + fRec68[0] + 2.0f * fRec68[1]);
			fRec78[0] = -(fConst85 * (fConst84 * fRec78[1] - (fRec67[(IOTA0 - 702) & 1023] + fRec67[(IOTA0 - 703) & 1023])));
			float fTemp84 = tanhf(fRec78[0]);
			fRec79[0] = -(fConst85 * (fConst84 * fRec79[1] - (fRec66[(IOTA0 - 594) & 1023] + fRec66[(IOTA0 - 595) & 1023])));
			float fTemp85 = tanhf(fRec79[0]);
			fRec80[0] = -(fConst85 * (fConst84 * fRec80[1] - (fRec65[(IOTA0 - 462) & 511] + fRec65[(IOTA0 - 463) & 511])));
			float fTemp86 = tanhf(fRec80[0]);
			fRec81[0] = -(fConst85 * (fConst84 * fRec81[1] - (fRec64[(IOTA0 - 348) & 511] + fRec64[(IOTA0 - 349) & 511])));
			float fTemp87 = tanhf(fRec81[0]);
			float fTemp88 = fTemp87 + fTemp86;
			fRec64[IOTA0 & 511] = 0.75f * (0.5f * (fTemp88 + fTemp85 + fTemp84) + fTemp83);
			fRec65[IOTA0 & 511] = 0.75f * (fTemp83 + 0.5f * (fTemp87 + fTemp85 - (fTemp86 + fTemp84)));
			fRec66[IOTA0 & 1023] = 0.75f * (fTemp83 + 0.5f * (fTemp88 - (fTemp85 + fTemp84)));
			fRec67[IOTA0 & 1023] = 0.75f * (fTemp83 + 0.5f * (fTemp87 + fTemp84 - (fTemp86 + fTemp85)));
			float fTemp89 = fRec64[IOTA0 & 511] + fRec65[IOTA0 & 511] + fRec66[IOTA0 & 1023] + fRec67[IOTA0 & 1023] - 0.5f * fRec62[1];
			fVec31[IOTA0 & 255] = fTemp89;
			fRec62[0] = fVec31[(IOTA0 - 130) & 255];
			float fRec63 = 0.5f * fTemp89;
			float fTemp90 = fRec63 + fRec62[1] - 0.5f * fRec60[1];
			fVec32[IOTA0 & 255] = fTemp90;
			fRec60[0] = fVec32[(IOTA0 - 190) & 255];
			float fRec61 = 0.5f * fTemp90;
			float fTemp91 = fSlow315 * (fSlow314 * fTemp82 + fSlow313 * (fRec61 + fRec60[1])) + fSlow276 * tanhf(fConst67 * (fRec52[2] + fRec52[0] + 2.0f * fRec52[1])) + fSlow225 * (fRec42[2] + (fRec42[0] - 2.0f * fRec42[1])) + fSlow117 * (fRec30[2] + fRec30[0] + 2.0f * fRec30[1]) + fSlow77 * (fRec13[2] + fRec13[0] + 2.0f * fRec13[1]);
			float fTemp92 = tanhf(1.5f * (fTemp91 + fSlow33 * std::sqrt(1.0f - fRec12[0]) * fTemp19));
			fVec33[0] = fTemp92;
			fRec0[0] = 0.995f * fRec0[1] + fTemp92 - fVec33[1];
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0]);
			float fTemp93 = std::sin(3.1415927f * fRec12[0]);
			float fTemp94 = std::tan(fConst61 * (fSlow316 * fTemp93 + 4e+02f));
			float fTemp95 = 1.0f / fTemp94;
			float fTemp96 = (fSlow317 + fTemp95) / fTemp94 + 1.0f;
			float fTemp97 = fSlow318 * fTemp93;
			float fTemp98 = fTemp97 + 1e+02f;
			int iTemp99 = static_cast<int>(fTemp98);
			float fTemp100 = std::floor(fTemp98);
			fRec83[0] = fConst5 * (fVec6[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp99))) & 255] * (fTemp100 + (-99.0f - fTemp97)) + (fTemp97 + (1e+02f - fTemp100)) * fVec6[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp99 + 1))) & 255]) - (fRec83[2] * ((fTemp95 - fSlow317) / fTemp94 + 1.0f) + 2.0f * fRec83[1] * (1.0f - 1.0f / mydsp_faustpower2_f(fTemp94))) / fTemp96;
			float fTemp101 = tanhf(1.5f * (fTemp91 + fSlow319 * (std::sqrt(fRec12[0]) * (fRec83[0] - fRec83[2]) / (fTemp94 * fTemp96))));
			fVec34[0] = fTemp101;
			fRec82[0] = 0.995f * fRec82[1] + fTemp101 - fVec34[1];
			output1[i0] = static_cast<FAUSTFLOAT>(fRec82[0]);
			iVec0[1] = iVec0[0];
			fRec4[1] = fRec4[0];
			IOTA0 = IOTA0 + 1;
			iRec3[1] = iRec3[0];
			iVec2[1] = iVec2[0];
			iRec5[1] = iRec5[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fVec4[1] = fVec4[0];
			fRec11[1] = fRec11[0];
			fRec9[1] = fRec9[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec12[1] = fRec12[0];
			fRec17[1] = fRec17[0];
			fRec24[1] = fRec24[0];
			iRec23[1] = iRec23[0];
			iVec8[1] = iVec8[0];
			iRec25[1] = iRec25[0];
			fRec22[1] = fRec22[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			fRec29[1] = fRec29[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec35[1] = fRec35[0];
			iRec34[1] = iRec34[0];
			iVec10[1] = iVec10[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			iRec37[1] = iRec37[0];
			iRec39[1] = iRec39[0];
			fVec11[1] = fVec11[0];
			fRec38[1] = fRec38[0];
			fRec41[1] = fRec41[0];
			fRec40[1] = fRec40[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec43[1] = fRec43[0];
			fVec12[1] = fVec12[0];
			fRec44[1] = fRec44[0];
			fVec14[1] = fVec14[0];
			fRec45[1] = fRec45[0];
			fVec16[1] = fVec16[0];
			fRec46[1] = fRec46[0];
			fVec18[1] = fVec18[0];
			fRec47[1] = fRec47[0];
			fVec20[1] = fVec20[0];
			fRec48[1] = fRec48[0];
			fVec22[1] = fVec22[0];
			fRec50[1] = fRec50[0];
			iRec49[1] = iRec49[0];
			iVec25[1] = iVec25[0];
			iRec51[1] = iRec51[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec56[1] = fRec56[0];
			iRec55[1] = iRec55[0];
			iVec27[1] = iVec27[0];
			iRec54[1] = iRec54[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec58[1] = fRec58[0];
			fRec59[1] = fRec59[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec75[1] = fRec75[0];
			iRec74[1] = iRec74[0];
			iVec29[1] = iVec29[0];
			iRec76[1] = iRec76[0];
			fRec77[1] = fRec77[0];
			fRec73[1] = fRec73[0];
			fVec30[1] = fVec30[0];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec78[1] = fRec78[0];
			fRec79[1] = fRec79[0];
			fRec80[1] = fRec80[0];
			fRec81[1] = fRec81[0];
			fRec62[1] = fRec62[0];
			fRec60[1] = fRec60[0];
			fVec33[1] = fVec33[0];
			fRec0[1] = fRec0[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fVec34[1] = fVec34[0];
			fRec82[1] = fRec82[0];
		}
	}

	int getCurrentStep() override { return iRec3[0]; }
	uint64_t getLastStep0TimeMs() override { return m_lastStep0TimeMs.load(); }
	uint64_t getLastBeatTimeMs() override { return m_lastBeatTimeMs.load(); }
	int getLastBeatStep() override { return m_lastBeatStep.load(); }
	void resetSequencer() override {
		m_pendingReset.store(true, std::memory_order_release);
	}

};


extern "C" dsp* newmydsp() {
    return new mydsp();
}

extern "C" void deletemydsp(dsp* d) {
    delete d;
}

#endif
