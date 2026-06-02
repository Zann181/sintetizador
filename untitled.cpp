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
	
	int iVec4[2];
	int iRec5[2];
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
			iVec4[l6] = 0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec5[l7] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec4[0] = 1;
			iRec5[0] = (iVec4[1] + iRec5[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec5[0]));
			iVec4[1] = iVec4[0];
			iRec5[1] = iRec5[0];
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
	int iRec3[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fConst13;
	int iVec1[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	int IOTA0;
	int iVec2[32768];
	FAUSTFLOAT fHslider4;
	float fConst14;
	int iVec3[2];
	int iRec4[2];
	float fConst15;
	float fConst16;
	FAUSTFLOAT fHslider5;
	float fConst17;
	float fRec6[2];
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	float fConst18;
	float fRec7[2];
	float fVec5[2];
	float fVec6[2048];
	float fConst19;
	float fConst20;
	float fRec10[2];
	FAUSTFLOAT fHslider8;
	float fRec8[2];
	float fRec2[3];
	float fConst21;
	float fRec1[3];
	float fVec7[256];
	FAUSTFLOAT fHslider9;
	float fRec11[2];
	FAUSTFLOAT fHslider10;
	FAUSTFLOAT fHslider11;
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
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	float fRec16[2];
	FAUSTFLOAT fHslider15;
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fHslider17;
	int iVec8[2];
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fHslider19;
	int iVec9[32768];
	FAUSTFLOAT fHslider20;
	int iVec10[2];
	int iRec22[2];
	FAUSTFLOAT fHslider21;
	FAUSTFLOAT fHslider22;
	FAUSTFLOAT fHslider23;
	float fRec21[2];
	float fConst34;
	float fConst35;
	float fConst36;
	float fRec23[2];
	float fRec24[2];
	float fRec25[2];
	float fRec26[2];
	FAUSTFLOAT fHslider24;
	float fRec17[2048];
	float fRec18[2048];
	float fRec19[2048];
	float fRec20[4096];
	FAUSTFLOAT fHslider25;
	float fRec15[2];
	FAUSTFLOAT fHslider26;
	float fRec14[2];
	float fRec13[3];
	float fConst37;
	float fRec12[3];
	FAUSTFLOAT fHslider27;
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
	FAUSTFLOAT fHslider28;
	FAUSTFLOAT fHslider29;
	FAUSTFLOAT fHslider30;
	int iVec11[2];
	int iVec12[32768];
	FAUSTFLOAT fHslider31;
	int iVec13[2];
	float fRec30[2];
	FAUSTFLOAT fHslider32;
	float fConst51;
	float fRec29[2];
	FAUSTFLOAT fHslider33;
	int iRec32[2];
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	int iRec34[2];
	float fVec14[2];
	float fConst57;
	float fRec33[2];
	FAUSTFLOAT fHslider34;
	FAUSTFLOAT fHslider35;
	FAUSTFLOAT fHslider36;
	float fConst58;
	float fConst59;
	float fRec36[2];
	FAUSTFLOAT fHslider37;
	float fRec35[2];
	FAUSTFLOAT fHslider38;
	float fRec31[8192];
	float fRec28[3];
	float fConst60;
	float fRec27[3];
	FAUSTFLOAT fHslider39;
	FAUSTFLOAT fHslider40;
	float fConst61;
	FAUSTFLOAT fHslider41;
	FAUSTFLOAT fHslider42;
	FAUSTFLOAT fHslider43;
	float fRec38[2];
	float fVec15[2];
	float fConst62;
	float fVec16[128];
	float fRec39[2];
	float fVec17[2];
	float fVec18[128];
	float fRec40[2];
	float fVec19[2];
	float fVec20[128];
	float fRec41[2];
	float fVec21[2];
	float fVec22[256];
	float fRec42[2];
	float fVec23[2];
	float fVec24[256];
	float fRec43[2];
	float fVec25[2];
	float fVec26[512];
	FAUSTFLOAT fHslider44;
	FAUSTFLOAT fHslider45;
	FAUSTFLOAT fHslider46;
	int iVec27[2];
	FAUSTFLOAT fHslider47;
	FAUSTFLOAT fHslider48;
	int iVec28[32768];
	FAUSTFLOAT fHslider49;
	int iVec29[2];
	int iRec44[2];
	FAUSTFLOAT fHslider50;
	FAUSTFLOAT fHslider51;
	float fRec37[3];
	FAUSTFLOAT fHslider52;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	FAUSTFLOAT fHslider53;
	FAUSTFLOAT fHslider54;
	FAUSTFLOAT fHslider55;
	FAUSTFLOAT fHslider56;
	int iVec30[2];
	int iVec31[32768];
	FAUSTFLOAT fHslider57;
	int iVec32[2];
	int iRec47[2];
	FAUSTFLOAT fHslider58;
	FAUSTFLOAT fHslider59;
	FAUSTFLOAT fHslider60;
	float fRec48[3];
	FAUSTFLOAT fHslider61;
	float fConst68;
	float fConst69;
	FAUSTFLOAT fHslider62;
	FAUSTFLOAT fHslider63;
	FAUSTFLOAT fHslider64;
	float fConst70;
	float fRec49[2];
	float fConst71;
	float fRec50[2];
	FAUSTFLOAT fHslider65;
	FAUSTFLOAT fHslider66;
	float fRec46[3];
	float fRec45[3];
	FAUSTFLOAT fHslider67;
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
	FAUSTFLOAT fHslider68;
	FAUSTFLOAT fHslider69;
	float fConst82;
	FAUSTFLOAT fHslider70;
	FAUSTFLOAT fHslider71;
	int iVec33[2];
	FAUSTFLOAT fHslider72;
	FAUSTFLOAT fHslider73;
	int iVec34[32768];
	FAUSTFLOAT fHslider74;
	int iVec35[2];
	int iRec65[2];
	FAUSTFLOAT fHslider75;
	FAUSTFLOAT fHslider76;
	FAUSTFLOAT fHslider77;
	FAUSTFLOAT fHslider78;
	float fRec66[2];
	float fConst83;
	float fRec64[2];
	FAUSTFLOAT fHslider79;
	FAUSTFLOAT fHslider80;
	FAUSTFLOAT fHslider81;
	float fVec36[2];
	float fRec63[2];
	float fRec62[3];
	float fRec61[3];
	float fRec60[3];
	float fRec59[3];
	float fConst84;
	float fConst85;
	float fRec67[2];
	float fRec68[2];
	float fRec69[2];
	float fRec70[2];
	float fRec55[512];
	float fRec56[512];
	float fRec57[1024];
	float fRec58[1024];
	float fVec37[256];
	float fRec53[2];
	float fVec38[256];
	float fRec51[2];
	FAUSTFLOAT fHslider82;
	FAUSTFLOAT fHslider83;
	float fVec39[2];
	float fRec0[2];
	FAUSTFLOAT fHslider84;
	float fRec72[3];
	float fVec40[2];
	float fRec71[2];
	
 public:
	mydsp() {
	}
	
	mydsp(const mydsp&) = default;
	
	virtual ~mydsp() = default;
	
	mydsp& operator=(const mydsp&) = default;
	
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
		fHslider3 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider4 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider5 = static_cast<FAUSTFLOAT>(0.2f);
		fHslider6 = static_cast<FAUSTFLOAT>(12.0f);
		fHslider7 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider8 = static_cast<FAUSTFLOAT>(5.0f);
		fHslider9 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider10 = static_cast<FAUSTFLOAT>(0.7f);
		fHslider11 = static_cast<FAUSTFLOAT>(0.85f);
		fHslider12 = static_cast<FAUSTFLOAT>(0.005f);
		fHslider13 = static_cast<FAUSTFLOAT>(-2e+01f);
		fHslider14 = static_cast<FAUSTFLOAT>(2.0f);
		fHslider15 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider16 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider17 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider18 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider19 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider20 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider21 = static_cast<FAUSTFLOAT>(0.2f);
		fHslider22 = static_cast<FAUSTFLOAT>(12.0f);
		fHslider23 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider24 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider25 = static_cast<FAUSTFLOAT>(0.1f);
		fHslider26 = static_cast<FAUSTFLOAT>(6.0f);
		fHslider27 = static_cast<FAUSTFLOAT>(0.22f);
		fHslider28 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider29 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider30 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider31 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider32 = static_cast<FAUSTFLOAT>(0.35f);
		fHslider33 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider34 = static_cast<FAUSTFLOAT>(-12.0f);
		fHslider35 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider36 = static_cast<FAUSTFLOAT>(0.04f);
		fHslider37 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider38 = static_cast<FAUSTFLOAT>(0.65f);
		fHslider39 = static_cast<FAUSTFLOAT>(0.55f);
		fHslider40 = static_cast<FAUSTFLOAT>(6.5e+03f);
		fHslider41 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider42 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider43 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider44 = static_cast<FAUSTFLOAT>(0.35f);
		fHslider45 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider46 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider47 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider48 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider49 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider50 = static_cast<FAUSTFLOAT>(0.001f);
		fHslider51 = static_cast<FAUSTFLOAT>(0.04f);
		fHslider52 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider53 = static_cast<FAUSTFLOAT>(1.6e+02f);
		fHslider54 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider55 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider56 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider57 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider58 = static_cast<FAUSTFLOAT>(0.16f);
		fHslider59 = static_cast<FAUSTFLOAT>(1.65e+03f);
		fHslider60 = static_cast<FAUSTFLOAT>(2.5f);
		fHslider61 = static_cast<FAUSTFLOAT>(0.55f);
		fHslider62 = static_cast<FAUSTFLOAT>(0.07f);
		fHslider63 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider64 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider65 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider66 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider67 = static_cast<FAUSTFLOAT>(0.65f);
		fHslider68 = static_cast<FAUSTFLOAT>(7.5e+02f);
		fHslider69 = static_cast<FAUSTFLOAT>(0.4f);
		fHslider70 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider71 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider72 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider73 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider74 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider75 = static_cast<FAUSTFLOAT>(0.18f);
		fHslider76 = static_cast<FAUSTFLOAT>(1.5e+02f);
		fHslider77 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider78 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider79 = static_cast<FAUSTFLOAT>(2.5e+03f);
		fHslider80 = static_cast<FAUSTFLOAT>(8.0f);
		fHslider81 = static_cast<FAUSTFLOAT>(3.5f);
		fHslider82 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider83 = static_cast<FAUSTFLOAT>(0.85f);
		fHslider84 = static_cast<FAUSTFLOAT>(4.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec3[l1] = 0;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iVec1[l2] = 0;
		}
		IOTA0 = 0;
		for (int l3 = 0; l3 < 32768; l3 = l3 + 1) {
			iVec2[l3] = 0;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iVec3[l4] = 0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iRec4[l5] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec6[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec7[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fVec5[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2048; l11 = l11 + 1) {
			fVec6[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec10[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec8[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec2[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec1[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 256; l16 = l16 + 1) {
			fVec7[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec11[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec16[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			iVec8[l19] = 0;
		}
		for (int l20 = 0; l20 < 32768; l20 = l20 + 1) {
			iVec9[l20] = 0;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			iVec10[l21] = 0;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			iRec22[l22] = 0;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec21[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec23[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec24[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec25[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec26[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2048; l28 = l28 + 1) {
			fRec17[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2048; l29 = l29 + 1) {
			fRec18[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2048; l30 = l30 + 1) {
			fRec19[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 4096; l31 = l31 + 1) {
			fRec20[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec15[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec14[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 3; l34 = l34 + 1) {
			fRec13[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 3; l35 = l35 + 1) {
			fRec12[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			iVec11[l36] = 0;
		}
		for (int l37 = 0; l37 < 32768; l37 = l37 + 1) {
			iVec12[l37] = 0;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			iVec13[l38] = 0;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec30[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec29[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			iRec32[l41] = 0;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			iRec34[l42] = 0;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fVec14[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fRec33[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec36[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec35[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 8192; l47 = l47 + 1) {
			fRec31[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec28[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec27[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fRec38[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fVec15[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 128; l52 = l52 + 1) {
			fVec16[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fRec39[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fVec17[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 128; l55 = l55 + 1) {
			fVec18[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2; l56 = l56 + 1) {
			fRec40[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2; l57 = l57 + 1) {
			fVec19[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 128; l58 = l58 + 1) {
			fVec20[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec41[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 2; l60 = l60 + 1) {
			fVec21[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 256; l61 = l61 + 1) {
			fVec22[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec42[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fVec23[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 256; l64 = l64 + 1) {
			fVec24[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fRec43[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 2; l66 = l66 + 1) {
			fVec25[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 512; l67 = l67 + 1) {
			fVec26[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			iVec27[l68] = 0;
		}
		for (int l69 = 0; l69 < 32768; l69 = l69 + 1) {
			iVec28[l69] = 0;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			iVec29[l70] = 0;
		}
		for (int l71 = 0; l71 < 2; l71 = l71 + 1) {
			iRec44[l71] = 0;
		}
		for (int l72 = 0; l72 < 3; l72 = l72 + 1) {
			fRec37[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 2; l73 = l73 + 1) {
			iVec30[l73] = 0;
		}
		for (int l74 = 0; l74 < 32768; l74 = l74 + 1) {
			iVec31[l74] = 0;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			iVec32[l75] = 0;
		}
		for (int l76 = 0; l76 < 2; l76 = l76 + 1) {
			iRec47[l76] = 0;
		}
		for (int l77 = 0; l77 < 3; l77 = l77 + 1) {
			fRec48[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			fRec49[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 2; l79 = l79 + 1) {
			fRec50[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 3; l80 = l80 + 1) {
			fRec46[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 3; l81 = l81 + 1) {
			fRec45[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			iVec33[l82] = 0;
		}
		for (int l83 = 0; l83 < 32768; l83 = l83 + 1) {
			iVec34[l83] = 0;
		}
		for (int l84 = 0; l84 < 2; l84 = l84 + 1) {
			iVec35[l84] = 0;
		}
		for (int l85 = 0; l85 < 2; l85 = l85 + 1) {
			iRec65[l85] = 0;
		}
		for (int l86 = 0; l86 < 2; l86 = l86 + 1) {
			fRec66[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 2; l87 = l87 + 1) {
			fRec64[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 2; l88 = l88 + 1) {
			fVec36[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 2; l89 = l89 + 1) {
			fRec63[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 3; l90 = l90 + 1) {
			fRec62[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 3; l91 = l91 + 1) {
			fRec61[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 3; l92 = l92 + 1) {
			fRec60[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 3; l93 = l93 + 1) {
			fRec59[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fRec67[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 2; l95 = l95 + 1) {
			fRec68[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 2; l96 = l96 + 1) {
			fRec69[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 2; l97 = l97 + 1) {
			fRec70[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 512; l98 = l98 + 1) {
			fRec55[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 512; l99 = l99 + 1) {
			fRec56[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 1024; l100 = l100 + 1) {
			fRec57[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 1024; l101 = l101 + 1) {
			fRec58[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 256; l102 = l102 + 1) {
			fVec37[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 2; l103 = l103 + 1) {
			fRec53[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 256; l104 = l104 + 1) {
			fVec38[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 2; l105 = l105 + 1) {
			fRec51[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 2; l106 = l106 + 1) {
			fVec39[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 2; l107 = l107 + 1) {
			fRec0[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 3; l108 = l108 + 1) {
			fRec72[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 2; l109 = l109 + 1) {
			fVec40[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fRec71[l110] = 0.0f;
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
		return new mydsp(*this);
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
		ui_interface->declare(&fHslider70, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider70, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider72, "1", "");
		ui_interface->declare(&fHslider72, "osc", "/kick/accent");
		ui_interface->declare(&fHslider72, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider72, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider77, "1", "");
		ui_interface->declare(&fHslider77, "osc", "/kick/tune");
		ui_interface->declare(&fHslider77, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider77, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider75, "1", "");
		ui_interface->declare(&fHslider75, "osc", "/kick/dec");
		ui_interface->declare(&fHslider75, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider75, FAUSTFLOAT(0.18f), FAUSTFLOAT(0.02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider73, "1", "");
		ui_interface->declare(&fHslider73, "osc", "/kick/groove");
		ui_interface->declare(&fHslider73, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider73, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider82, "1", "");
		ui_interface->declare(&fHslider82, "osc", "/kick/mix");
		ui_interface->declare(&fHslider82, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Rumble", &fHslider82, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider78, "1", "");
		ui_interface->declare(&fHslider78, "osc", "/kick/nota");
		ui_interface->declare(&fHslider78, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider78, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider71, "1", "");
		ui_interface->declare(&fHslider71, "osc", "/kick/reloj");
		ui_interface->declare(&fHslider71, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider71, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider74, "1", "");
		ui_interface->declare(&fHslider74, "osc", "/kick/swing");
		ui_interface->declare(&fHslider74, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider74, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider76, "1", "");
		ui_interface->declare(&fHslider76, "osc", "/kick/sweep");
		ui_interface->declare(&fHslider76, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Transitorio", &fHslider76, FAUSTFLOAT(1.5e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(3e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider83, "1", "");
		ui_interface->declare(&fHslider83, "osc", "/kick/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider83, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider79, "2", "");
		ui_interface->declare(&fHslider79, "osc", "/kick/comp_fmax");
		ui_interface->declare(&fHslider79, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Filtro Frec Max", &fHslider79, FAUSTFLOAT(2.5e+03f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(8e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider68, "2", "");
		ui_interface->declare(&fHslider68, "osc", "/kick/comp_fmin");
		ui_interface->declare(&fHslider68, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Filtro Frec Min", &fHslider68, FAUSTFLOAT(7.5e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider80, "2", "");
		ui_interface->declare(&fHslider80, "osc", "/kick/comp_ratio");
		ui_interface->declare(&fHslider80, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Lim Ratio", &fHslider80, FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider69, "2", "");
		ui_interface->declare(&fHslider69, "osc", "/kick/comp_thresh");
		ui_interface->declare(&fHslider69, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Lim Umbral", &fHslider69, FAUSTFLOAT(0.4f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider81, "2", "");
		ui_interface->declare(&fHslider81, "osc", "/kick/comp_drive");
		ui_interface->declare(&fHslider81, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Saturacion Pegada", &fHslider81, FAUSTFLOAT(3.5f), FAUSTFLOAT(0.5f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("Caja");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider55, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider55, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider65, "1", "");
		ui_interface->declare(&fHslider65, "osc", "/snare/accent");
		ui_interface->declare(&fHslider65, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider65, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider63, "1", "");
		ui_interface->declare(&fHslider63, "osc", "/snare/tune");
		ui_interface->declare(&fHslider63, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider63, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider62, "1", "");
		ui_interface->declare(&fHslider62, "osc", "/snare/dec_cuerpo");
		ui_interface->declare(&fHslider62, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decay Cuerpo", &fHslider62, FAUSTFLOAT(0.07f), FAUSTFLOAT(0.01f), FAUSTFLOAT(0.4f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider58, "1", "");
		ui_interface->declare(&fHslider58, "osc", "/snare/dec_resorte");
		ui_interface->declare(&fHslider58, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decay Resortes", &fHslider58, FAUSTFLOAT(0.16f), FAUSTFLOAT(0.02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider53, "1", "");
		ui_interface->declare(&fHslider53, "osc", "/snare/hp");
		ui_interface->declare(&fHslider53, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro Paso Alto", &fHslider53, FAUSTFLOAT(1.6e+02f), FAUSTFLOAT(8e+01f), FAUSTFLOAT(4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider59, "1", "");
		ui_interface->declare(&fHslider59, "osc", "/snare/freq");
		ui_interface->declare(&fHslider59, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Frecuencia Resortes", &fHslider59, FAUSTFLOAT(1.65e+03f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider54, "1", "");
		ui_interface->declare(&fHslider54, "osc", "/snare/groove");
		ui_interface->declare(&fHslider54, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider54, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider61, "1", "");
		ui_interface->declare(&fHslider61, "osc", "/snare/mix");
		ui_interface->declare(&fHslider61, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Resortes", &fHslider61, FAUSTFLOAT(0.55f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider64, "1", "");
		ui_interface->declare(&fHslider64, "osc", "/snare/nota");
		ui_interface->declare(&fHslider64, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider64, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider56, "1", "");
		ui_interface->declare(&fHslider56, "osc", "/snare/reloj");
		ui_interface->declare(&fHslider56, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider56, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider60, "1", "");
		ui_interface->declare(&fHslider60, "osc", "/snare/q");
		ui_interface->declare(&fHslider60, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Resonancia Resortes", &fHslider60, FAUSTFLOAT(2.5f), FAUSTFLOAT(1.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider66, "1", "");
		ui_interface->declare(&fHslider66, "osc", "/snare/drive");
		ui_interface->declare(&fHslider66, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider66, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider57, "1", "");
		ui_interface->declare(&fHslider57, "osc", "/snare/swing");
		ui_interface->declare(&fHslider57, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider57, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider67, "1", "");
		ui_interface->declare(&fHslider67, "osc", "/snare/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider67, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("Platillos");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider45, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider45, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider47, "1", "");
		ui_interface->declare(&fHslider47, "osc", "/hat/accent");
		ui_interface->declare(&fHslider47, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider47, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider42, "1", "");
		ui_interface->declare(&fHslider42, "osc", "/hat/tune");
		ui_interface->declare(&fHslider42, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider42, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider50, "1", "");
		ui_interface->declare(&fHslider50, "osc", "/hat/ataque");
		ui_interface->declare(&fHslider50, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Ataque", &fHslider50, FAUSTFLOAT(0.001f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider51, "1", "");
		ui_interface->declare(&fHslider51, "osc", "/hat/dec");
		ui_interface->declare(&fHslider51, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider51, FAUSTFLOAT(0.04f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider40, "1", "");
		ui_interface->declare(&fHslider40, "osc", "/hat/cutoff");
		ui_interface->declare(&fHslider40, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro Paso Alto", &fHslider40, FAUSTFLOAT(6.5e+03f), FAUSTFLOAT(3e+03f), FAUSTFLOAT(1.2e+04f), FAUSTFLOAT(5e+01f));
		ui_interface->declare(&fHslider48, "1", "");
		ui_interface->declare(&fHslider48, "osc", "/hat/groove");
		ui_interface->declare(&fHslider48, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider48, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider41, "1", "");
		ui_interface->declare(&fHslider41, "osc", "/hat/mix");
		ui_interface->declare(&fHslider41, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Metal Ruido", &fHslider41, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider43, "1", "");
		ui_interface->declare(&fHslider43, "osc", "/hat/nota");
		ui_interface->declare(&fHslider43, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider43, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider46, "1", "");
		ui_interface->declare(&fHslider46, "osc", "/hat/reloj");
		ui_interface->declare(&fHslider46, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider46, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider44, "1", "");
		ui_interface->declare(&fHslider44, "osc", "/hat/drive");
		ui_interface->declare(&fHslider44, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider44, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider49, "1", "");
		ui_interface->declare(&fHslider49, "osc", "/hat/swing");
		ui_interface->declare(&fHslider49, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider49, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider52, "1", "");
		ui_interface->declare(&fHslider52, "osc", "/hat/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider52, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openVerticalBox("Bajo WG");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider30, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider30, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider33, "1", "");
		ui_interface->declare(&fHslider33, "osc", "/bass/accent");
		ui_interface->declare(&fHslider33, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider33, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider32, "1", "");
		ui_interface->declare(&fHslider32, "osc", "/bass/dec");
		ui_interface->declare(&fHslider32, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider32, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider36, "1", "");
		ui_interface->declare(&fHslider36, "osc", "/bass/detune");
		ui_interface->declare(&fHslider36, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Desafinado", &fHslider36, FAUSTFLOAT(0.04f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider37, "1", "");
		ui_interface->declare(&fHslider37, "osc", "/bass/lfo");
		ui_interface->declare(&fHslider37, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro LFO", &fHslider37, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider28, "1", "");
		ui_interface->declare(&fHslider28, "osc", "/bass/groove");
		ui_interface->declare(&fHslider28, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider28, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider34, "1", "");
		ui_interface->declare(&fHslider34, "osc", "/bass/intervalo");
		ui_interface->addHorizontalSlider("Sintesis/Intervalo", &fHslider34, FAUSTFLOAT(-12.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(7.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider35, "1", "");
		ui_interface->declare(&fHslider35, "osc", "/bass/nota");
		ui_interface->declare(&fHslider35, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider35, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider29, "1", "");
		ui_interface->declare(&fHslider29, "osc", "/bass/reloj");
		ui_interface->declare(&fHslider29, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider29, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider38, "1", "");
		ui_interface->declare(&fHslider38, "osc", "/bass/drive");
		ui_interface->declare(&fHslider38, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider38, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider31, "1", "");
		ui_interface->declare(&fHslider31, "osc", "/bass/swing");
		ui_interface->declare(&fHslider31, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider31, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider39, "1", "");
		ui_interface->declare(&fHslider39, "osc", "/bass/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider39, FAUSTFLOAT(0.55f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "5", "");
		ui_interface->openVerticalBox("Synth Psyche");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider0, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider0, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "osc", "/syn1/accent");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider2, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider10, "1", "");
		ui_interface->declare(&fHslider10, "osc", "/syn1/auto_p");
		ui_interface->declare(&fHslider10, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Profundidad", &fHslider10, FAUSTFLOAT(0.7f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider84, "1", "");
		ui_interface->declare(&fHslider84, "osc", "/syn1/auto_r");
		ui_interface->declare(&fHslider84, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Resonancia", &fHslider84, FAUSTFLOAT(4.5f), FAUSTFLOAT(1.0f), FAUSTFLOAT(9.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider9, "1", "");
		ui_interface->declare(&fHslider9, "osc", "/syn1/auto_v");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Velocidad", &fHslider9, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.05f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "osc", "/syn1/dec");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider5, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "osc", "/syn1/groove");
		ui_interface->declare(&fHslider3, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "osc", "/syn1/nota");
		ui_interface->declare(&fHslider7, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider7, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider8, "1", "");
		ui_interface->declare(&fHslider8, "osc", "/syn1/osc1");
		ui_interface->addHorizontalSlider("Sintesis/Osc 1", &fHslider8, FAUSTFLOAT(5.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "osc", "/syn1/osc2");
		ui_interface->addHorizontalSlider("Sintesis/Osc 2", &fHslider6, FAUSTFLOAT(12.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(19.0f), FAUSTFLOAT(19.0f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "osc", "/syn1/reloj");
		ui_interface->declare(&fHslider1, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "osc", "/syn1/swing");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider11, "1", "");
		ui_interface->declare(&fHslider11, "osc", "/syn1/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider11, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "6", "");
		ui_interface->openVerticalBox("Siringe FDN");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider16, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider16, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider18, "1", "");
		ui_interface->declare(&fHslider18, "osc", "/syn2/accent");
		ui_interface->declare(&fHslider18, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider18, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider21, "1", "");
		ui_interface->declare(&fHslider21, "osc", "/syn2/dec");
		ui_interface->declare(&fHslider21, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider21, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider24, "1", "");
		ui_interface->declare(&fHslider24, "osc", "/syn2/disp");
		ui_interface->declare(&fHslider24, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Dispersion", &fHslider24, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.9f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider19, "1", "");
		ui_interface->declare(&fHslider19, "osc", "/syn2/groove");
		ui_interface->declare(&fHslider19, "style", "menu{'1':0; '2':1; '3':2; '4':3; '5':4; '6':5; '7':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider19, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider14, "1", "");
		ui_interface->declare(&fHslider14, "osc", "/syn2/lfo_f");
		ui_interface->declare(&fHslider14, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/LFO Freq", &fHslider14, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider15, "1", "");
		ui_interface->declare(&fHslider15, "osc", "/syn2/lfo_p");
		ui_interface->declare(&fHslider15, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/LFO Profundidad", &fHslider15, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider22, "1", "");
		ui_interface->declare(&fHslider22, "osc", "/syn2/nota");
		ui_interface->declare(&fHslider22, "style", "menu{'Octava':12; 'Quinta Arriba':19; 'Doble Octava':24}");
		ui_interface->addHorizontalSlider("Sintesis/Nota Siringe", &fHslider22, FAUSTFLOAT(12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider23, "1", "");
		ui_interface->declare(&fHslider23, "osc", "/syn2/nota");
		ui_interface->declare(&fHslider23, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider23, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider17, "1", "");
		ui_interface->declare(&fHslider17, "osc", "/syn2/reloj");
		ui_interface->declare(&fHslider17, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider17, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider20, "1", "");
		ui_interface->declare(&fHslider20, "osc", "/syn2/swing");
		ui_interface->declare(&fHslider20, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider20, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider27, "1", "");
		ui_interface->declare(&fHslider27, "osc", "/syn2/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider27, FAUSTFLOAT(0.22f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider12, "2", "");
		ui_interface->declare(&fHslider12, "osc", "/syn2/comp_a");
		ui_interface->declare(&fHslider12, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Ataque", &fHslider12, FAUSTFLOAT(0.005f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider25, "2", "");
		ui_interface->declare(&fHslider25, "osc", "/syn2/comp_rel");
		ui_interface->declare(&fHslider25, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Liberacion", &fHslider25, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider26, "2", "");
		ui_interface->declare(&fHslider26, "osc", "/syn2/comp_r");
		ui_interface->declare(&fHslider26, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Ratio", &fHslider26, FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider13, "2", "");
		ui_interface->declare(&fHslider13, "osc", "/syn2/comp_th");
		ui_interface->declare(&fHslider13, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Umbral", &fHslider13, FAUSTFLOAT(-2e+01f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = static_cast<float>(fHslider1) * static_cast<float>(fHslider0);
		float fSlow1 = fConst13 * fSlow0;
		float fSlow2 = 0.4f * static_cast<float>(fHslider2) + 1.0f;
		float fSlow3 = static_cast<float>(fHslider3);
		int iSlow4 = fSlow3 >= 4.0f;
		int iSlow5 = fSlow3 >= 2.0f;
		int iSlow6 = fSlow3 >= 1.0f;
		int iSlow7 = fSlow3 >= 3.0f;
		int iSlow8 = fSlow3 >= 6.0f;
		int iSlow9 = fSlow3 >= 5.0f;
		float fSlow10 = fConst14 * (static_cast<float>(fHslider4) / fSlow0);
		int iSlow11 = static_cast<int>(fSlow10);
		int iSlow12 = std::min<int>(16385, std::max<int>(0, iSlow11 + 1));
		float fSlow13 = std::floor(fSlow10);
		float fSlow14 = fSlow10 - fSlow13;
		int iSlow15 = std::min<int>(16385, std::max<int>(0, iSlow11));
		float fSlow16 = fSlow13 + (1.0f - fSlow10);
		float fSlow17 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider5));
		float fSlow18 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider7) + -69.0f));
		float fSlow19 = 4.4e+02f * fSlow18 * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider6));
		float fSlow20 = 4.4e+02f * fSlow18 * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider8));
		float fSlow21 = fConst18 * static_cast<float>(fHslider9);
		float fSlow22 = static_cast<float>(fHslider10);
		float fSlow23 = static_cast<float>(fHslider11);
		float fSlow24 = fConst5 * fSlow23 * (1.0f - 0.5f * fSlow22);
		float fSlow25 = static_cast<float>(fHslider12);
		float fSlow26 = 0.5f * fSlow25;
		int iSlow27 = std::fabs(fSlow26) < 1.1920929e-07f;
		float fSlow28 = ((iSlow27) ? 0.0f : std::exp(-(fConst18 / ((iSlow27) ? 1.0f : fSlow26))));
		float fSlow29 = 1.0f - fSlow28;
		float fSlow30 = static_cast<float>(fHslider13);
		float fSlow31 = fConst18 * static_cast<float>(fHslider14);
		float fSlow32 = static_cast<float>(fHslider15);
		float fSlow33 = static_cast<float>(fHslider17) * static_cast<float>(fHslider16);
		float fSlow34 = fConst13 * fSlow33;
		float fSlow35 = 0.6f * static_cast<float>(fHslider18) + 1.0f;
		float fSlow36 = static_cast<float>(fHslider19);
		int iSlow37 = fSlow36 >= 4.0f;
		int iSlow38 = fSlow36 >= 2.0f;
		int iSlow39 = fSlow36 >= 1.0f;
		int iSlow40 = fSlow36 >= 3.0f;
		int iSlow41 = fSlow36 >= 6.0f;
		int iSlow42 = fSlow36 >= 5.0f;
		float fSlow43 = fConst14 * (static_cast<float>(fHslider20) / fSlow33);
		int iSlow44 = static_cast<int>(fSlow43);
		int iSlow45 = std::min<int>(16385, std::max<int>(0, iSlow44 + 1));
		float fSlow46 = std::floor(fSlow43);
		float fSlow47 = fSlow43 - fSlow46;
		int iSlow48 = std::min<int>(16385, std::max<int>(0, iSlow44));
		float fSlow49 = fSlow46 + (1.0f - fSlow43);
		float fSlow50 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider21));
		float fSlow51 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider23) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider22));
		float fSlow52 = 0.5f * static_cast<float>(fHslider24);
		float fSlow53 = static_cast<float>(fHslider25);
		int iSlow54 = std::fabs(fSlow53) < 1.1920929e-07f;
		float fSlow55 = ((iSlow54) ? 0.0f : std::exp(-(fConst18 / ((iSlow54) ? 1.0f : fSlow53))));
		int iSlow56 = std::fabs(fSlow25) < 1.1920929e-07f;
		float fSlow57 = ((iSlow56) ? 0.0f : std::exp(-(fConst18 / ((iSlow56) ? 1.0f : fSlow25))));
		float fSlow58 = 1.0f / std::max<float>(1.1920929e-07f, static_cast<float>(fHslider26)) + -1.0f;
		float fSlow59 = fConst26 * static_cast<float>(fHslider27);
		float fSlow60 = static_cast<float>(fHslider28);
		int iSlow61 = fSlow60 >= 4.0f;
		int iSlow62 = fSlow60 >= 2.0f;
		int iSlow63 = fSlow60 >= 1.0f;
		float fSlow64 = static_cast<float>(fHslider30);
		float fSlow65 = fSlow64 * static_cast<float>(fHslider29);
		float fSlow66 = fConst13 * fSlow65;
		int iSlow67 = fSlow60 >= 3.0f;
		int iSlow68 = fSlow60 >= 6.0f;
		int iSlow69 = fSlow60 >= 5.0f;
		float fSlow70 = fConst14 * (static_cast<float>(fHslider31) / fSlow65);
		int iSlow71 = static_cast<int>(fSlow70);
		int iSlow72 = std::min<int>(16385, std::max<int>(0, iSlow71 + 1));
		float fSlow73 = std::floor(fSlow70);
		float fSlow74 = fSlow70 - fSlow73;
		int iSlow75 = std::min<int>(16385, std::max<int>(0, iSlow71));
		float fSlow76 = fSlow73 + (1.0f - fSlow70);
		float fSlow77 = 0.004166667f * (fSlow64 / static_cast<float>(fHslider32));
		float fSlow78 = 0.4f * static_cast<float>(fHslider33) + 1.0f;
		float fSlow79 = static_cast<float>(fHslider36);
		float fSlow80 = fConst58 * ((0.059f * fSlow79 + 1.0f) / (std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider35) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider34))));
		int iSlow81 = static_cast<int>(fSlow80);
		int iSlow82 = std::min<int>(131073, std::max<int>(0, iSlow81 + 1)) + 1;
		float fSlow83 = std::floor(fSlow80);
		float fSlow84 = fSlow80 - fSlow83;
		int iSlow85 = std::min<int>(131073, std::max<int>(0, iSlow81)) + 1;
		float fSlow86 = fSlow83 + (1.0f - fSlow80);
		float fSlow87 = static_cast<float>(fHslider37);
		float fSlow88 = 3.0f * static_cast<float>(fHslider38);
		float fSlow89 = (fSlow88 + 1.0f) * (0.014f * fSlow79 + 0.985f);
		float fSlow90 = fConst42 * static_cast<float>(fHslider39);
		float fSlow91 = std::tan(fConst61 * static_cast<float>(fHslider40));
		float fSlow92 = mydsp_faustpower2_f(fSlow91);
		float fSlow93 = 2.0f * (1.0f - 1.0f / fSlow92);
		float fSlow94 = 1.0f / fSlow91;
		float fSlow95 = (fSlow94 + -1.4142135f) / fSlow91 + 1.0f;
		float fSlow96 = (fSlow94 + 1.4142135f) / fSlow91 + 1.0f;
		float fSlow97 = 1.0f / fSlow96;
		float fSlow98 = static_cast<float>(fHslider41);
		float fSlow99 = 4.656613e-10f * fSlow98;
		float fSlow100 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider43) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider42));
		float fSlow101 = std::max<float>(19306.982f * fSlow100, 23.44895f);
		float fSlow102 = std::max<float>(2e+01f, std::fabs(fSlow101));
		float fSlow103 = fConst18 * fSlow102;
		float fSlow104 = fConst62 / fSlow102;
		float fSlow105 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow101));
		int iSlow106 = static_cast<int>(fSlow105);
		float fSlow107 = std::floor(fSlow105);
		float fSlow108 = fSlow107 + (1.0f - fSlow105);
		float fSlow109 = std::max<float>(15940.032f * fSlow100, 23.44895f);
		float fSlow110 = std::max<float>(2e+01f, std::fabs(fSlow109));
		float fSlow111 = fConst18 * fSlow110;
		float fSlow112 = fConst62 / fSlow110;
		float fSlow113 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow109));
		int iSlow114 = static_cast<int>(fSlow113);
		float fSlow115 = std::floor(fSlow113);
		float fSlow116 = fSlow115 + (1.0f - fSlow113);
		float fSlow117 = std::max<float>(12784.989f * fSlow100, 23.44895f);
		float fSlow118 = std::max<float>(2e+01f, std::fabs(fSlow117));
		float fSlow119 = fConst18 * fSlow118;
		float fSlow120 = fConst62 / fSlow118;
		float fSlow121 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow117));
		int iSlow122 = static_cast<int>(fSlow121);
		float fSlow123 = std::floor(fSlow121);
		float fSlow124 = fSlow123 + (1.0f - fSlow121);
		float fSlow125 = std::max<float>(9794.762f * fSlow100, 23.44895f);
		float fSlow126 = std::max<float>(2e+01f, std::fabs(fSlow125));
		float fSlow127 = fConst18 * fSlow126;
		float fSlow128 = fConst62 / fSlow126;
		float fSlow129 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow125));
		int iSlow130 = static_cast<int>(fSlow129);
		float fSlow131 = std::floor(fSlow129);
		float fSlow132 = fSlow131 + (1.0f - fSlow129);
		float fSlow133 = std::max<float>(7016.4395f * fSlow100, 23.44895f);
		float fSlow134 = std::max<float>(2e+01f, std::fabs(fSlow133));
		float fSlow135 = fConst18 * fSlow134;
		float fSlow136 = fConst62 / fSlow134;
		float fSlow137 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow133));
		int iSlow138 = static_cast<int>(fSlow137);
		float fSlow139 = std::floor(fSlow137);
		float fSlow140 = fSlow139 + (1.0f - fSlow137);
		float fSlow141 = std::max<float>(4709.02f * fSlow100, 23.44895f);
		float fSlow142 = std::max<float>(2e+01f, std::fabs(fSlow141));
		float fSlow143 = fConst18 * fSlow142;
		float fSlow144 = fConst62 / fSlow142;
		float fSlow145 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow141));
		int iSlow146 = static_cast<int>(fSlow145);
		int iSlow147 = iSlow146 + 1;
		float fSlow148 = std::floor(fSlow145);
		float fSlow149 = fSlow145 - fSlow148;
		float fSlow150 = fSlow148 + (1.0f - fSlow145);
		int iSlow151 = iSlow138 + 1;
		float fSlow152 = fSlow137 - fSlow139;
		int iSlow153 = iSlow130 + 1;
		float fSlow154 = fSlow129 - fSlow131;
		int iSlow155 = iSlow122 + 1;
		float fSlow156 = fSlow121 - fSlow123;
		int iSlow157 = iSlow114 + 1;
		float fSlow158 = fSlow113 - fSlow115;
		int iSlow159 = iSlow106 + 1;
		float fSlow160 = fSlow105 - fSlow107;
		float fSlow161 = 1.0f / fSlow102;
		float fSlow162 = 1.0f / fSlow110;
		float fSlow163 = 1.0f / fSlow118;
		float fSlow164 = 1.0f / fSlow126;
		float fSlow165 = 1.0f / fSlow134;
		float fSlow166 = 1.0f / fSlow142;
		float fSlow167 = 0.15f * (1.0f - fSlow98);
		float fSlow168 = 6.5f * static_cast<float>(fHslider44);
		float fSlow169 = static_cast<float>(fHslider46) * static_cast<float>(fHslider45);
		float fSlow170 = fConst13 * fSlow169;
		float fSlow171 = 0.4f * static_cast<float>(fHslider47) + 1.0f;
		float fSlow172 = static_cast<float>(fHslider48);
		int iSlow173 = fSlow172 >= 4.0f;
		int iSlow174 = fSlow172 >= 2.0f;
		int iSlow175 = fSlow172 >= 1.0f;
		int iSlow176 = fSlow172 >= 3.0f;
		int iSlow177 = fSlow172 >= 6.0f;
		int iSlow178 = fSlow172 >= 5.0f;
		float fSlow179 = fConst14 * (static_cast<float>(fHslider49) / fSlow169);
		int iSlow180 = static_cast<int>(fSlow179);
		int iSlow181 = std::min<int>(16385, std::max<int>(0, iSlow180 + 1));
		float fSlow182 = std::floor(fSlow179);
		float fSlow183 = fSlow179 - fSlow182;
		int iSlow184 = std::min<int>(16385, std::max<int>(0, iSlow180));
		float fSlow185 = fSlow182 + (1.0f - fSlow179);
		float fSlow186 = std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider50));
		float fSlow187 = 1.0f / fSlow186;
		float fSlow188 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider51));
		float fSlow189 = 2.0f * (static_cast<float>(fHslider52) / (fSlow92 * fSlow96));
		float fSlow190 = std::tan(fConst61 * static_cast<float>(fHslider53));
		float fSlow191 = mydsp_faustpower2_f(fSlow190);
		float fSlow192 = 2.0f * (1.0f - 1.0f / fSlow191);
		float fSlow193 = 1.0f / fSlow190;
		float fSlow194 = (fSlow193 + -1.4142135f) / fSlow190 + 1.0f;
		float fSlow195 = (fSlow193 + 1.4142135f) / fSlow190 + 1.0f;
		float fSlow196 = 1.0f / fSlow195;
		float fSlow197 = static_cast<float>(fHslider54);
		int iSlow198 = fSlow197 >= 4.0f;
		int iSlow199 = fSlow197 >= 2.0f;
		int iSlow200 = fSlow197 >= 1.0f;
		float fSlow201 = static_cast<float>(fHslider56) * static_cast<float>(fHslider55);
		float fSlow202 = fConst13 * fSlow201;
		int iSlow203 = fSlow197 >= 3.0f;
		int iSlow204 = fSlow197 >= 6.0f;
		int iSlow205 = fSlow197 >= 5.0f;
		float fSlow206 = fConst14 * (static_cast<float>(fHslider57) / fSlow201);
		int iSlow207 = static_cast<int>(fSlow206);
		int iSlow208 = std::min<int>(16385, std::max<int>(0, iSlow207 + 1));
		float fSlow209 = std::floor(fSlow206);
		float fSlow210 = fSlow206 - fSlow209;
		int iSlow211 = std::min<int>(16385, std::max<int>(0, iSlow207));
		float fSlow212 = fSlow209 + (1.0f - fSlow206);
		float fSlow213 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider58));
		float fSlow214 = std::tan(fConst61 * static_cast<float>(fHslider59));
		float fSlow215 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fSlow214));
		float fSlow216 = 1.0f / static_cast<float>(fHslider60);
		float fSlow217 = 1.0f / fSlow214;
		float fSlow218 = (fSlow217 - fSlow216) / fSlow214 + 1.0f;
		float fSlow219 = (fSlow216 + fSlow217) / fSlow214 + 1.0f;
		float fSlow220 = 1.0f / fSlow219;
		float fSlow221 = static_cast<float>(fHslider61);
		float fSlow222 = 2.34f * (fSlow221 / (fSlow214 * fSlow219));
		float fSlow223 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider62));
		float fSlow224 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider64) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider63));
		float fSlow225 = fConst70 * fSlow224;
		float fSlow226 = fConst71 * fSlow224;
		float fSlow227 = 1.0f - fSlow221;
		float fSlow228 = 0.4f * static_cast<float>(fHslider65) + 1.0f;
		float fSlow229 = static_cast<float>(fHslider66);
		float fSlow230 = 1.0f / (fSlow191 * fSlow195);
		float fSlow231 = static_cast<float>(fHslider67);
		float fSlow232 = static_cast<float>(fHslider68);
		float fSlow233 = static_cast<float>(fHslider69);
		float fSlow234 = static_cast<float>(fHslider71) * static_cast<float>(fHslider70);
		float fSlow235 = fConst13 * fSlow234;
		float fSlow236 = 0.4f * static_cast<float>(fHslider72) + 1.0f;
		float fSlow237 = static_cast<float>(fHslider73);
		int iSlow238 = fSlow237 >= 4.0f;
		int iSlow239 = fSlow237 >= 2.0f;
		int iSlow240 = fSlow237 >= 1.0f;
		int iSlow241 = fSlow237 >= 3.0f;
		int iSlow242 = fSlow237 >= 6.0f;
		int iSlow243 = fSlow237 >= 5.0f;
		float fSlow244 = fConst14 * (static_cast<float>(fHslider74) / fSlow234);
		int iSlow245 = static_cast<int>(fSlow244);
		int iSlow246 = std::min<int>(16385, std::max<int>(0, iSlow245 + 1));
		float fSlow247 = std::floor(fSlow244);
		float fSlow248 = fSlow244 - fSlow247;
		int iSlow249 = std::min<int>(16385, std::max<int>(0, iSlow245));
		float fSlow250 = fSlow247 + (1.0f - fSlow244);
		float fSlow251 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider75));
		float fSlow252 = static_cast<float>(fHslider76);
		float fSlow253 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider78) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider77));
		float fSlow254 = static_cast<float>(fHslider79);
		float fSlow255 = static_cast<float>(fHslider80);
		float fSlow256 = fSlow255 * (fSlow254 - fSlow232);
		float fSlow257 = static_cast<float>(fHslider81);
		float fSlow258 = static_cast<float>(fHslider82);
		float fSlow259 = 1.8f * fSlow258;
		float fSlow260 = fConst60 * (1.0f - fSlow258);
		float fSlow261 = static_cast<float>(fHslider83);
		float fSlow262 = 5e+03f * fSlow22;
		float fSlow263 = 1.0f / static_cast<float>(fHslider84);
		float fSlow264 = 85.0f * fSlow22;
		float fSlow265 = fSlow22 * fSlow23;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			iRec3[0] = iRec3[1] + 1;
			float fTemp0 = static_cast<float>(iRec3[0]);
			int iTemp1 = static_cast<int>(fSlow1 * fTemp0) % 16;
			iVec1[0] = iTemp1;
			int iTemp2 = iTemp1 >= 8;
			int iTemp3 = iTemp1 >= 12;
			int iTemp4 = iTemp1 >= 10;
			int iTemp5 = iTemp1 >= 9;
			int iTemp6 = ((iTemp5) ? 0 : 1);
			int iTemp7 = iTemp1 >= 4;
			int iTemp8 = iTemp1 >= 6;
			int iTemp9 = iTemp1 >= 5;
			int iTemp10 = ((iTemp9) ? 0 : 1);
			int iTemp11 = ((iTemp8) ? 0 : iTemp10);
			int iTemp12 = iTemp1 >= 14;
			int iTemp13 = iTemp1 >= 13;
			int iTemp14 = iTemp1 >= 15;
			int iTemp15 = ((iTemp14) ? 0 : 1);
			int iTemp16 = iTemp1 >= 2;
			int iTemp17 = iTemp1 >= 3;
			int iTemp18 = ((iTemp17) ? 0 : 1);
			int iTemp19 = iTemp1 >= 11;
			int iTemp20 = ((iTemp19) ? 0 : 1);
			int iTemp21 = ((iTemp1 >= 1) ? 0 : 1);
			int iTemp22 = ((iTemp17) ? 1 : 0);
			int iTemp23 = iTemp1 >= 7;
			int iTemp24 = ((iTemp19) ? 1 : 0);
			int iTemp25 = ((iTemp12) ? iTemp15 : 0);
			int iTemp26 = iTemp1 != iVec1[1];
			iVec2[IOTA0 & 32767] = iTemp26;
			int iTemp27 = static_cast<int>((((iTemp1 % 2) == 1) ? fSlow16 * static_cast<float>(iVec2[(IOTA0 - iSlow15) & 32767]) + fSlow14 * static_cast<float>(iVec2[(IOTA0 - iSlow12) & 32767]) : static_cast<float>(iTemp26))) & (((iSlow4) ? ((iSlow8) ? ((iTemp2) ? ((iTemp3) ? 1 : ((iTemp4) ? iTemp24 : 1)) : ((iTemp7) ? ((iTemp8) ? ((iTemp23) ? 1 : 0) : 1) : ((iTemp16) ? iTemp22 : 1))) : ((iSlow9) ? ((iTemp2) ? ((iTemp3) ? ((iTemp12) ? ((iTemp14) ? 1 : 0) : 1) : ((iTemp4) ? iTemp20 : iTemp6)) : ((iTemp7) ? ((iTemp8) ? 1 : iTemp10) : ((iTemp16) ? iTemp18 : iTemp21))) : ((iTemp2) ? ((iTemp3) ? iTemp25 : ((iTemp4) ? iTemp20 : ((iTemp5) ? 1 : 0))) : ((iTemp7) ? iTemp11 : ((iTemp16) ? 1 : 0))))) : ((iSlow5) ? ((iSlow7) ? ((iTemp2) ? ((iTemp3) ? iTemp25 : ((iTemp4) ? iTemp24 : iTemp6)) : ((iTemp7) ? ((iTemp8) ? ((iTemp23) ? 0 : 1) : 0) : ((iTemp16) ? iTemp22 : iTemp21))) : ((iTemp2) ? ((iTemp3) ? ((iTemp12) ? 0 : ((iTemp13) ? 1 : 0)) : ((iTemp4) ? iTemp20 : 0)) : ((iTemp7) ? ((iTemp8) ? 0 : ((iTemp9) ? 1 : 0)) : ((iTemp16) ? iTemp18 : 0)))) : ((iSlow6) ? ((iTemp2) ? ((iTemp3) ? ((iTemp12) ? iTemp15 : ((iTemp13) ? 0 : 1)) : 0) : ((iTemp7) ? iTemp11 : 0)) : ((iTemp2) ? ((iTemp3) ? 0 : ((iTemp4) ? 0 : iTemp6)) : 0)))) > 0);
			iVec3[0] = iTemp27;
			iRec4[0] = (iRec4[1] + (iRec4[1] > 0)) * (iTemp27 <= iVec3[1]) + (iTemp27 > iVec3[1]);
			float fTemp28 = static_cast<float>(iRec4[0]);
			int iTemp29 = 1 - iVec0[1];
			float fTemp30 = ((iTemp29) ? 0.0f : fConst17 + fRec6[1]);
			fRec6[0] = fTemp30 - std::floor(fTemp30);
			float fTemp31 = std::max<float>(fSlow19 + ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec6[0]), 65535))], 23.44895f);
			float fTemp32 = std::max<float>(2e+01f, std::fabs(fTemp31));
			float fTemp33 = ((iTemp29) ? 0.0f : fRec7[1] + fConst18 * fTemp32);
			fRec7[0] = fTemp33 - std::floor(fTemp33);
			float fTemp34 = mydsp_faustpower2_f(2.0f * fRec7[0] + -1.0f);
			fVec5[0] = fTemp34;
			float fTemp35 = static_cast<float>(iVec0[1]);
			float fTemp36 = fTemp35 * (fTemp34 - fVec5[1]) / fTemp32;
			fVec6[IOTA0 & 2047] = fTemp36;
			float fTemp37 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fTemp31));
			int iTemp38 = static_cast<int>(fTemp37);
			float fTemp39 = std::floor(fTemp37);
			float fTemp40 = ((iTemp29) ? 0.0f : fConst20 + fRec10[1]);
			fRec10[0] = fTemp40 - std::floor(fTemp40);
			float fTemp41 = std::max<float>(1.1920929e-07f, std::fabs(fSlow20 + 2.0f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec10[0]), 65535))]));
			float fTemp42 = fRec8[1] + fConst18 * fTemp41;
			float fTemp43 = fTemp42 + -1.0f;
			int iTemp44 = fTemp43 < 0.0f;
			fRec8[0] = ((iTemp44) ? fTemp42 : fTemp43);
			float fRec9 = ((iTemp44) ? fTemp42 : fTemp42 + fTemp43 * (1.0f - fConst0 / fTemp41));
			fRec2[0] = (0.6f * (2.0f * fRec9 + -1.0f) + fConst14 * (fTemp36 - fVec6[(IOTA0 - iTemp38) & 2047] * (fTemp39 + (1.0f - fTemp37)) - (fTemp37 - fTemp39) * fVec6[(IOTA0 - (iTemp38 + 1)) & 2047])) * std::max<float>(0.0f, std::min<float>(fConst16 * fTemp28, fSlow17 * (fConst15 - fTemp28) + 1.0f)) * (((((iTemp1 == 0) | (iTemp1 == 4)) | (iTemp1 == 8)) | (iTemp1 == 12)) ? fSlow2 : 1.0f) - fConst12 * (fConst10 * fRec2[2] + fConst8 * fRec2[1]);
			fRec1[0] = fConst21 * (fRec2[2] + (fRec2[0] - 2.0f * fRec2[1])) - fConst5 * (fConst4 * fRec1[2] + fConst2 * fRec1[1]);
			float fTemp45 = fRec1[2] + fRec1[0] + 2.0f * fRec1[1];
			fVec7[IOTA0 & 255] = fTemp45;
			float fTemp46 = ((iTemp29) ? 0.0f : fSlow21 + fRec11[1]);
			fRec11[0] = fTemp46 - std::floor(fTemp46);
			float fTemp47 = ((iTemp29) ? 0.0f : fSlow31 + fRec16[1]);
			fRec16[0] = fTemp47 - std::floor(fTemp47);
			int iTemp48 = static_cast<int>(fSlow34 * fTemp0) % 16;
			iVec8[0] = iTemp48;
			int iTemp49 = iTemp48 >= 8;
			int iTemp50 = iTemp48 >= 4;
			int iTemp51 = iTemp48 >= 2;
			int iTemp52 = iTemp48 >= 1;
			int iTemp53 = ((iTemp52) ? 0 : 1);
			int iTemp54 = iTemp48 >= 12;
			int iTemp55 = iTemp48 >= 14;
			int iTemp56 = iTemp48 >= 13;
			int iTemp57 = ((iTemp56) ? 0 : 1);
			int iTemp58 = ((iTemp55) ? 0 : iTemp57);
			int iTemp59 = iTemp48 >= 3;
			int iTemp60 = iTemp48 >= 6;
			int iTemp61 = iTemp48 >= 7;
			int iTemp62 = iTemp48 >= 10;
			int iTemp63 = iTemp48 >= 9;
			int iTemp64 = ((iTemp63) ? 1 : 0);
			int iTemp65 = ((iTemp62) ? 0 : iTemp64);
			int iTemp66 = ((iTemp52) ? 1 : 0);
			int iTemp67 = iTemp48 >= 5;
			int iTemp68 = ((iTemp61) ? 1 : 0);
			int iTemp69 = ((iTemp48 >= 15) ? 0 : 1);
			int iTemp70 = ((iTemp67) ? 1 : 0);
			int iTemp71 = ((iTemp56) ? 1 : 0);
			int iTemp72 = iTemp48 != iVec8[1];
			iVec9[IOTA0 & 32767] = iTemp72;
			int iTemp73 = static_cast<int>((((iTemp48 % 2) == 1) ? fSlow49 * static_cast<float>(iVec9[(IOTA0 - iSlow48) & 32767]) + fSlow47 * static_cast<float>(iVec9[(IOTA0 - iSlow45) & 32767]) : static_cast<float>(iTemp72)));
			int iTemp74 = iTemp73 & (iTemp73 & (((iSlow37) ? ((iSlow41) ? ((iTemp49) ? ((iTemp54) ? ((iTemp55) ? 1 : 0) : 1) : ((iTemp50) ? ((iTemp60) ? 1 : 0) : 1)) : ((iSlow42) ? ((iTemp49) ? ((iTemp54) ? ((iTemp55) ? 1 : iTemp71) : ((iTemp62) ? 1 : iTemp64)) : ((iTemp50) ? ((iTemp60) ? 1 : iTemp70) : ((iTemp51) ? 1 : iTemp66))) : ((iTemp49) ? ((iTemp54) ? ((iTemp55) ? iTemp69 : iTemp71) : ((iTemp62) ? ((iTemp48 >= 11) ? 1 : 0) : ((iTemp63) ? 0 : 1))) : ((iTemp50) ? ((iTemp60) ? iTemp68 : iTemp70) : ((iTemp51) ? ((iTemp59) ? 0 : 1) : iTemp53))))) : ((iSlow38) ? ((iSlow40) ? ((iTemp49) ? ((iTemp54) ? ((iTemp55) ? iTemp69 : iTemp57) : iTemp65) : ((iTemp50) ? ((iTemp60) ? iTemp68 : ((iTemp67) ? 0 : 1)) : ((iTemp51) ? 0 : iTemp66))) : ((iTemp49) ? ((iTemp54) ? iTemp58 : iTemp65) : ((iTemp50) ? ((iTemp60) ? ((iTemp61) ? 0 : 1) : 0) : ((iTemp51) ? ((iTemp59) ? 1 : 0) : 0)))) : ((iSlow39) ? ((iTemp49) ? ((iTemp54) ? iTemp58 : 0) : 0) : ((iTemp49) ? 0 : ((iTemp50) ? 0 : ((iTemp51) ? 0 : iTemp53)))))) > 0));
			iVec10[0] = iTemp74;
			iRec22[0] = (iRec22[1] + (iRec22[1] > 0)) * (iTemp74 <= iVec10[1]) + (iTemp74 > iVec10[1]);
			float fTemp75 = static_cast<float>(iRec22[0]);
			float fTemp76 = std::max<float>(0.0f, std::min<float>(fConst16 * fTemp75, fSlow50 * (fConst15 - fTemp75) + 1.0f)) * (((((iTemp48 == 0) | (iTemp48 == 4)) | (iTemp48 == 8)) | (iTemp48 == 12)) ? fSlow35 : 1.0f);
			float fTemp77 = ((iTemp29) ? 0.0f : fRec21[1] + fConst18 * (fSlow51 + 1.5e+03f * fTemp76));
			fRec21[0] = fTemp77 - std::floor(fTemp77);
			float fTemp78 = fTemp76 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec21[0]), 65535))];
			fRec23[0] = -(fConst36 * (fConst35 * fRec23[1] - (fRec18[(IOTA0 - 1400) & 2047] + fRec18[(IOTA0 - 1401) & 2047])));
			fRec24[0] = -(fConst36 * (fConst35 * fRec24[1] - (fRec17[(IOTA0 - 1118) & 2047] + fRec17[(IOTA0 - 1119) & 2047])));
			float fTemp79 = fRec24[0] + fRec23[0];
			fRec25[0] = -(fConst36 * (fConst35 * fRec25[1] - (fRec19[(IOTA0 - 1724) & 2047] + fRec19[(IOTA0 - 1725) & 2047])));
			fRec26[0] = -(fConst36 * (fConst35 * fRec26[1] - (fRec20[(IOTA0 - 2090) & 4095] + fRec20[(IOTA0 - 2091) & 4095])));
			fRec17[IOTA0 & 2047] = fSlow52 * (fRec26[0] + fRec25[0] + fTemp79) + fTemp78;
			float fTemp80 = fRec24[0] - fRec23[0];
			fRec18[IOTA0 & 2047] = fTemp78 - fSlow52 * (fRec26[0] - (fRec25[0] + fTemp80));
			fRec19[IOTA0 & 2047] = fTemp78 - fSlow52 * (fRec26[0] - (fTemp79 - fRec25[0]));
			fRec20[IOTA0 & 4095] = fTemp78 + fSlow52 * (fRec26[0] - (fRec25[0] - fTemp80));
			float fTemp81 = (fRec17[IOTA0 & 2047] + fRec18[IOTA0 & 2047] + fRec19[IOTA0 & 2047] + fRec20[IOTA0 & 4095]) * (fSlow32 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec16[0]), 65535))] + 1.0f);
			float fTemp82 = std::fabs(0.25f * fTemp81);
			float fTemp83 = ((fTemp82 > fRec15[1]) ? fSlow57 : fSlow55);
			fRec15[0] = fTemp82 * (1.0f - fTemp83) + fRec15[1] * fTemp83;
			fRec14[0] = fSlow58 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec15[0])) - fSlow30, 0.0f) * fSlow29 + fSlow28 * fRec14[1];
			fRec13[0] = 0.25f * fTemp81 * std::pow(1e+01f, 0.05f * fRec14[0]) - fConst33 * (fConst31 * fRec13[2] + fConst29 * fRec13[1]);
			fRec12[0] = fConst37 * (fRec13[2] + (fRec13[0] - 2.0f * fRec13[1])) - fConst26 * (fConst25 * fRec12[2] + fConst23 * fRec12[1]);
			int iTemp84 = static_cast<int>(fSlow66 * fTemp0) % 16;
			iVec11[0] = iTemp84;
			int iTemp85 = iTemp84 >= 8;
			int iTemp86 = iTemp84 >= 4;
			int iTemp87 = iTemp84 >= 2;
			int iTemp88 = iTemp84 >= 3;
			int iTemp89 = ((iTemp88) ? 0 : 1);
			int iTemp90 = iTemp84 >= 6;
			int iTemp91 = ((iTemp84 >= 7) ? 0 : 1);
			int iTemp92 = iTemp84 >= 12;
			int iTemp93 = iTemp84 >= 10;
			int iTemp94 = ((iTemp84 >= 11) ? 0 : 1);
			int iTemp95 = iTemp84 >= 14;
			int iTemp96 = iTemp84 >= 15;
			int iTemp97 = ((iTemp96) ? 0 : 1);
			int iTemp98 = iTemp84 >= 1;
			int iTemp99 = ((iTemp98) ? 1 : 0);
			int iTemp100 = iTemp84 >= 5;
			int iTemp101 = ((iTemp90) ? iTemp91 : ((iTemp100) ? 1 : 0));
			int iTemp102 = iTemp84 >= 9;
			int iTemp103 = ((iTemp93) ? iTemp94 : ((iTemp102) ? 1 : 0));
			int iTemp104 = iTemp84 >= 13;
			int iTemp105 = ((iTemp104) ? 1 : 0);
			int iTemp106 = ((iTemp98) ? 0 : 1);
			int iTemp107 = ((iTemp90) ? iTemp91 : ((iTemp100) ? 0 : 1));
			int iTemp108 = ((iTemp102) ? 0 : 1);
			int iTemp109 = ((iTemp104) ? 0 : 1);
			int iTemp110 = iTemp84 != iVec11[1];
			iVec12[IOTA0 & 32767] = iTemp110;
			int iTemp111 = static_cast<int>((((iTemp84 % 2) == 1) ? fSlow76 * static_cast<float>(iVec12[(IOTA0 - iSlow75) & 32767]) + fSlow74 * static_cast<float>(iVec12[(IOTA0 - iSlow72) & 32767]) : static_cast<float>(iTemp110))) & (((iSlow61) ? ((iSlow68) ? ((iTemp85) ? ((iTemp92) ? 1 : ((iTemp93) ? iTemp94 : 1)) : ((iTemp86) ? ((iTemp90) ? iTemp91 : 1) : ((iTemp87) ? iTemp89 : 1))) : ((iSlow69) ? ((iTemp85) ? ((iTemp92) ? ((iTemp95) ? 1 : iTemp105) : ((iTemp93) ? 1 : iTemp108)) : ((iTemp86) ? iTemp101 : ((iTemp87) ? 1 : iTemp106))) : ((iTemp85) ? ((iTemp92) ? ((iTemp95) ? ((iTemp96) ? 1 : 0) : iTemp109) : iTemp103) : ((iTemp86) ? iTemp107 : ((iTemp87) ? ((iTemp88) ? 1 : 0) : iTemp99))))) : ((iSlow62) ? ((iSlow67) ? ((iTemp85) ? ((iTemp92) ? ((iTemp95) ? iTemp97 : iTemp109) : ((iTemp93) ? iTemp94 : iTemp108)) : ((iTemp86) ? iTemp107 : ((iTemp87) ? iTemp89 : iTemp106))) : ((iTemp85) ? ((iTemp92) ? ((iTemp95) ? 1 : 0) : ((iTemp93) ? 1 : 0)) : ((iTemp86) ? ((iTemp90) ? 1 : 0) : ((iTemp87) ? 1 : 0)))) : ((iSlow63) ? ((iTemp85) ? ((iTemp92) ? ((iTemp95) ? iTemp97 : iTemp105) : iTemp103) : ((iTemp86) ? iTemp101 : ((iTemp87) ? iTemp89 : iTemp99))) : ((iTemp85) ? ((iTemp92) ? ((iTemp95) ? iTemp97 : 0) : ((iTemp93) ? iTemp94 : 0)) : ((iTemp86) ? ((iTemp90) ? iTemp91 : 0) : ((iTemp87) ? iTemp89 : 0)))))) > 0);
			iVec13[0] = iTemp111;
			fRec30[0] = (fConst18 + fRec30[1]) * (1.0f - static_cast<float>(iTemp111));
			fRec29[0] = fConst51 * std::exp(-(fSlow77 * fRec30[0])) + fConst50 * fRec29[1];
			iRec32[0] = (iRec32[1] + (iRec32[1] > 0)) * (iTemp111 <= iVec13[1]) + (iTemp111 > iVec13[1]);
			float fTemp112 = static_cast<float>(iRec32[0]);
			iRec34[0] = 1103515245 * iRec34[1] + 12345;
			float fTemp113 = static_cast<float>(iRec34[0]);
			fVec14[0] = fTemp113;
			fRec33[0] = fConst57 * (4.656613e-10f * (fTemp113 + fVec14[1]) - fConst56 * fRec33[1]);
			fRec36[0] = fConst59 + fRec36[1] * static_cast<float>(1 - iTemp111);
			float fTemp114 = std::max<float>(0.01f, 0.6f - 0.15f * (fSlow79 - fSlow87 * std::sin(6.2831855f * (fRec36[0] - std::floor(fRec36[0])))));
			fRec35[0] = fRec35[1] * (1.0f - fTemp114) + fTemp114 * (fSlow86 * fRec31[(IOTA0 - iSlow85) & 8191] + fSlow84 * fRec31[(IOTA0 - iSlow82) & 8191]);
			fRec31[IOTA0 & 8191] = fSlow89 * (fRec35[0] / (fSlow88 * std::fabs(fRec35[0]) + 1.0f)) + fRec33[0] * std::max<float>(0.0f, std::min<float>(fConst53 * fTemp112, fConst54 * (fConst52 - fTemp112) + 1.0f)) * (((((iTemp84 == 0) | (iTemp84 == 4)) | (iTemp84 == 8)) | (iTemp84 == 12)) ? fSlow78 : 1.0f);
			fRec28[0] = fRec31[IOTA0 & 8191] * fRec29[0] - fConst49 * (fConst47 * fRec28[2] + fConst45 * fRec28[1]);
			fRec27[0] = fConst60 * (fRec28[2] + (fRec28[0] - 2.0f * fRec28[1])) - fConst42 * (fConst41 * fRec27[2] + fConst39 * fRec27[1]);
			float fTemp115 = ((iTemp29) ? 0.0f : fSlow103 + fRec38[1]);
			fRec38[0] = fTemp115 - std::floor(fTemp115);
			float fTemp116 = mydsp_faustpower2_f(2.0f * fRec38[0] + -1.0f);
			fVec15[0] = fTemp116;
			float fTemp117 = fTemp116 - fVec15[1];
			float fTemp118 = fSlow104 * fTemp35 * fTemp117;
			fVec16[IOTA0 & 127] = fTemp118;
			float fTemp119 = ((iTemp29) ? 0.0f : fSlow111 + fRec39[1]);
			fRec39[0] = fTemp119 - std::floor(fTemp119);
			float fTemp120 = mydsp_faustpower2_f(2.0f * fRec39[0] + -1.0f);
			fVec17[0] = fTemp120;
			float fTemp121 = fTemp120 - fVec17[1];
			float fTemp122 = fSlow112 * fTemp35 * fTemp121;
			fVec18[IOTA0 & 127] = fTemp122;
			float fTemp123 = ((iTemp29) ? 0.0f : fSlow119 + fRec40[1]);
			fRec40[0] = fTemp123 - std::floor(fTemp123);
			float fTemp124 = mydsp_faustpower2_f(2.0f * fRec40[0] + -1.0f);
			fVec19[0] = fTemp124;
			float fTemp125 = fTemp124 - fVec19[1];
			float fTemp126 = fSlow120 * fTemp35 * fTemp125;
			fVec20[IOTA0 & 127] = fTemp126;
			float fTemp127 = ((iTemp29) ? 0.0f : fSlow127 + fRec41[1]);
			fRec41[0] = fTemp127 - std::floor(fTemp127);
			float fTemp128 = mydsp_faustpower2_f(2.0f * fRec41[0] + -1.0f);
			fVec21[0] = fTemp128;
			float fTemp129 = fTemp128 - fVec21[1];
			float fTemp130 = fSlow128 * fTemp35 * fTemp129;
			fVec22[IOTA0 & 255] = fTemp130;
			float fTemp131 = ((iTemp29) ? 0.0f : fSlow135 + fRec42[1]);
			fRec42[0] = fTemp131 - std::floor(fTemp131);
			float fTemp132 = mydsp_faustpower2_f(2.0f * fRec42[0] + -1.0f);
			fVec23[0] = fTemp132;
			float fTemp133 = fTemp132 - fVec23[1];
			float fTemp134 = fSlow136 * fTemp35 * fTemp133;
			fVec24[IOTA0 & 255] = fTemp134;
			float fTemp135 = ((iTemp29) ? 0.0f : fSlow143 + fRec43[1]);
			fRec43[0] = fTemp135 - std::floor(fTemp135);
			float fTemp136 = mydsp_faustpower2_f(2.0f * fRec43[0] + -1.0f);
			fVec25[0] = fTemp136;
			float fTemp137 = fTemp136 - fVec25[1];
			float fTemp138 = fSlow144 * fTemp35 * fTemp137;
			fVec26[IOTA0 & 511] = fTemp138;
			float fTemp139 = fSlow167 * (fConst62 * fTemp35 * (fSlow166 * fTemp137 + fSlow165 * fTemp133 + fSlow164 * fTemp129 + fSlow163 * fTemp125 + fSlow162 * fTemp121 + fSlow161 * fTemp117) - (fSlow160 * fVec16[(IOTA0 - iSlow159) & 127] + fSlow158 * fVec18[(IOTA0 - iSlow157) & 127] + fSlow156 * fVec20[(IOTA0 - iSlow155) & 127] + fSlow154 * fVec22[(IOTA0 - iSlow153) & 255] + fSlow152 * fVec24[(IOTA0 - iSlow151) & 255] + fSlow150 * fVec26[(IOTA0 - iSlow146) & 511] + fSlow149 * fVec26[(IOTA0 - iSlow147) & 511] + fSlow140 * fVec24[(IOTA0 - iSlow138) & 255] + fSlow132 * fVec22[(IOTA0 - iSlow130) & 255] + fSlow124 * fVec20[(IOTA0 - iSlow122) & 127] + fSlow116 * fVec18[(IOTA0 - iSlow114) & 127] + fSlow108 * fVec16[(IOTA0 - iSlow106) & 127])) + fSlow99 * fTemp113;
			int iTemp140 = static_cast<int>(fSlow170 * fTemp0) % 16;
			iVec27[0] = iTemp140;
			int iTemp141 = iTemp140 >= 8;
			int iTemp142 = iTemp140 >= 4;
			int iTemp143 = iTemp140 >= 2;
			int iTemp144 = iTemp140 >= 3;
			int iTemp145 = ((iTemp144) ? 0 : 1);
			int iTemp146 = iTemp140 >= 6;
			int iTemp147 = iTemp140 >= 7;
			int iTemp148 = ((iTemp147) ? 0 : 1);
			int iTemp149 = iTemp140 >= 12;
			int iTemp150 = iTemp140 >= 10;
			int iTemp151 = iTemp140 >= 11;
			int iTemp152 = ((iTemp151) ? 0 : 1);
			int iTemp153 = iTemp140 >= 14;
			int iTemp154 = ((iTemp140 >= 15) ? 0 : 1);
			int iTemp155 = ((iTemp153) ? iTemp154 : 0);
			int iTemp156 = iTemp140 >= 1;
			int iTemp157 = iTemp140 >= 5;
			int iTemp158 = ((iTemp157) ? 1 : 0);
			int iTemp159 = ((iTemp146) ? iTemp148 : iTemp158);
			int iTemp160 = iTemp140 >= 9;
			int iTemp161 = ((iTemp153) ? iTemp154 : ((iTemp140 >= 13) ? 1 : 0));
			int iTemp162 = ((iTemp156) ? 0 : 1);
			int iTemp163 = ((iTemp147) ? 1 : 0);
			int iTemp164 = ((iTemp150) ? ((iTemp151) ? 1 : 0) : 1);
			int iTemp165 = iTemp140 != iVec27[1];
			iVec28[IOTA0 & 32767] = iTemp165;
			int iTemp166 = static_cast<int>((((iTemp140 % 2) == 1) ? fSlow185 * static_cast<float>(iVec28[(IOTA0 - iSlow184) & 32767]) + fSlow183 * static_cast<float>(iVec28[(IOTA0 - iSlow181) & 32767]) : static_cast<float>(iTemp165))) & (((iSlow173) ? ((iSlow177) ? ((iTemp141) ? 1 : ((iTemp142) ? ((iTemp146) ? 1 : ((iTemp157) ? 0 : 1)) : 1)) : ((iSlow178) ? ((iTemp141) ? ((iTemp149) ? 1 : iTemp164) : ((iTemp142) ? ((iTemp146) ? iTemp163 : 1) : ((iTemp143) ? ((iTemp144) ? 1 : 0) : 1))) : ((iTemp141) ? ((iTemp149) ? iTemp161 : iTemp164) : ((iTemp142) ? ((iTemp146) ? iTemp163 : iTemp158) : ((iTemp143) ? 1 : iTemp162))))) : ((iSlow174) ? ((iSlow176) ? 1 : ((iTemp141) ? ((iTemp149) ? iTemp155 : ((iTemp150) ? 1 : ((iTemp160) ? 0 : 1))) : ((iTemp142) ? iTemp159 : ((iTemp143) ? iTemp145 : iTemp162)))) : ((iSlow175) ? ((iTemp141) ? ((iTemp149) ? iTemp161 : ((iTemp150) ? iTemp152 : ((iTemp160) ? 1 : 0))) : ((iTemp142) ? iTemp159 : ((iTemp143) ? iTemp145 : ((iTemp156) ? 1 : 0)))) : ((iTemp141) ? ((iTemp149) ? iTemp155 : ((iTemp150) ? iTemp152 : 0)) : ((iTemp142) ? ((iTemp146) ? iTemp148 : 0) : ((iTemp143) ? iTemp145 : 0)))))) > 0);
			iVec29[0] = iTemp166;
			iRec44[0] = (iRec44[1] + (iRec44[1] > 0)) * (iTemp166 <= iVec29[1]) + (iTemp166 > iVec29[1]);
			float fTemp167 = static_cast<float>(iRec44[0]);
			fRec37[0] = fTemp139 * std::max<float>(0.0f, std::min<float>(fSlow187 * fTemp167, fSlow188 * (fSlow186 - fTemp167) + 1.0f)) * (((((iTemp140 == 0) | (iTemp140 == 4)) | (iTemp140 == 8)) | (iTemp140 == 12)) ? fSlow171 : 1.0f) / (fSlow168 * std::fabs(fTemp139) + 1.0f) - fSlow97 * (fSlow95 * fRec37[2] + fSlow93 * fRec37[1]);
			int iTemp168 = static_cast<int>(fSlow202 * fTemp0) % 16;
			iVec30[0] = iTemp168;
			int iTemp169 = iTemp168 >= 8;
			int iTemp170 = iTemp168 >= 4;
			int iTemp171 = iTemp168 >= 6;
			int iTemp172 = ((iTemp168 >= 5) ? 0 : 1);
			int iTemp173 = ((iTemp171) ? 0 : iTemp172);
			int iTemp174 = ((iTemp170) ? iTemp173 : 0);
			int iTemp175 = iTemp168 >= 12;
			int iTemp176 = iTemp168 >= 14;
			int iTemp177 = ((iTemp168 >= 13) ? 0 : 1);
			int iTemp178 = ((iTemp176) ? 0 : iTemp177);
			int iTemp179 = iTemp168 >= 10;
			int iTemp180 = iTemp168 >= 11;
			int iTemp181 = ((iTemp180) ? 0 : 1);
			int iTemp182 = ((iTemp179) ? iTemp181 : 0);
			int iTemp183 = iTemp168 >= 2;
			int iTemp184 = ((iTemp168 >= 3) ? 0 : 1);
			int iTemp185 = ((iTemp183) ? iTemp184 : 0);
			int iTemp186 = iTemp168 >= 9;
			int iTemp187 = ((iTemp186) ? 1 : 0);
			int iTemp188 = ((iTemp168 >= 7) ? 1 : 0);
			int iTemp189 = ((iTemp171) ? iTemp188 : iTemp172);
			int iTemp190 = iTemp168 >= 15;
			int iTemp191 = ((iTemp176) ? ((iTemp190) ? 0 : 1) : iTemp177);
			int iTemp192 = iTemp168 != iVec30[1];
			iVec31[IOTA0 & 32767] = iTemp192;
			int iTemp193 = static_cast<int>((((iTemp168 % 2) == 1) ? fSlow212 * static_cast<float>(iVec31[(IOTA0 - iSlow211) & 32767]) + fSlow210 * static_cast<float>(iVec31[(IOTA0 - iSlow208) & 32767]) : static_cast<float>(iTemp192))) & (((iSlow198) ? ((iSlow204) ? ((iTemp169) ? ((iTemp175) ? 1 : ((iTemp179) ? iTemp181 : ((iTemp186) ? 0 : 1))) : ((iTemp170) ? ((iTemp171) ? iTemp188 : 1) : ((iTemp183) ? iTemp184 : ((iTemp168 >= 1) ? 0 : 1)))) : ((iSlow205) ? ((iTemp169) ? ((iTemp175) ? iTemp191 : ((iTemp179) ? ((iTemp180) ? 1 : 0) : iTemp187)) : ((iTemp170) ? iTemp189 : ((iTemp183) ? 1 : 0))) : ((iTemp169) ? ((iTemp175) ? ((iTemp176) ? ((iTemp190) ? 1 : 0) : iTemp177) : iTemp182) : ((iTemp170) ? iTemp189 : iTemp185)))) : ((iSlow199) ? ((iSlow203) ? ((iTemp169) ? ((iTemp175) ? iTemp191 : 0) : ((iTemp170) ? iTemp189 : 0)) : ((iTemp169) ? ((iTemp175) ? iTemp178 : ((iTemp179) ? 0 : iTemp187)) : ((iTemp170) ? iTemp173 : iTemp185))) : ((iSlow200) ? ((iTemp169) ? ((iTemp175) ? iTemp178 : iTemp182) : iTemp174) : ((iTemp169) ? ((iTemp175) ? iTemp178 : 0) : iTemp174)))) > 0);
			iVec32[0] = iTemp193;
			iRec47[0] = (iRec47[1] + (iRec47[1] > 0)) * (iTemp193 <= iVec32[1]) + (iTemp193 > iVec32[1]);
			float fTemp194 = static_cast<float>(iRec47[0]);
			fRec48[0] = 4.656613e-10f * fTemp113 - fSlow220 * (fSlow218 * fRec48[2] + fSlow215 * fRec48[1]);
			float fTemp195 = ((iTemp29) ? 0.0f : fSlow225 + fRec49[1]);
			fRec49[0] = fTemp195 - std::floor(fTemp195);
			float fTemp196 = ((iTemp29) ? 0.0f : fSlow226 + fRec50[1]);
			fRec50[0] = fTemp196 - std::floor(fTemp196);
			fRec46[0] = fSlow229 * (((((iTemp168 == 0) | (iTemp168 == 4)) | (iTemp168 == 8)) | (iTemp168 == 12)) ? fSlow228 : 1.0f) * (fSlow227 * (0.65f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec50[0]), 65535))] + 0.35f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec49[0]), 65535))]) * std::max<float>(0.0f, std::min<float>(fConst69 * fTemp194, fSlow223 * (fConst68 - fTemp194) + 1.0f)) + fSlow222 * (fRec48[0] - fRec48[2]) * std::max<float>(0.0f, std::min<float>(fConst53 * fTemp194, fSlow213 * (fConst52 - fTemp194) + 1.0f))) - fSlow196 * (fSlow194 * fRec46[2] + fSlow192 * fRec46[1]);
			fRec45[0] = fSlow230 * (fRec46[2] + (fRec46[0] - 2.0f * fRec46[1])) - fConst67 * (fConst66 * fRec45[2] + fConst64 * fRec45[1]);
			int iTemp197 = static_cast<int>(fSlow235 * fTemp0) % 16;
			iVec33[0] = iTemp197;
			int iTemp198 = iTemp197 >= 8;
			int iTemp199 = iTemp197 >= 4;
			int iTemp200 = iTemp197 >= 2;
			int iTemp201 = ((iTemp197 >= 1) ? 0 : 1);
			int iTemp202 = ((iTemp200) ? 0 : iTemp201);
			int iTemp203 = iTemp197 >= 6;
			int iTemp204 = ((iTemp197 >= 5) ? 0 : 1);
			int iTemp205 = ((iTemp199) ? ((iTemp203) ? 0 : iTemp204) : iTemp202);
			int iTemp206 = iTemp197 >= 12;
			int iTemp207 = iTemp197 >= 10;
			int iTemp208 = ((iTemp197 >= 9) ? 0 : 1);
			int iTemp209 = ((iTemp207) ? 0 : iTemp208);
			int iTemp210 = iTemp197 >= 14;
			int iTemp211 = ((iTemp197 >= 13) ? 0 : 1);
			int iTemp212 = ((iTemp210) ? 0 : iTemp211);
			int iTemp213 = iTemp197 >= 15;
			int iTemp214 = ((iTemp206) ? ((iTemp210) ? ((iTemp213) ? 0 : 1) : iTemp211) : iTemp209);
			int iTemp215 = iTemp197 >= 7;
			int iTemp216 = ((iTemp203) ? ((iTemp215) ? 1 : 0) : iTemp204);
			int iTemp217 = ((iTemp199) ? iTemp216 : iTemp202);
			int iTemp218 = ((iTemp215) ? 0 : 1);
			int iTemp219 = iTemp197 >= 3;
			int iTemp220 = iTemp197 != iVec33[1];
			iVec34[IOTA0 & 32767] = iTemp220;
			int iTemp221 = static_cast<int>((((iTemp197 % 2) == 1) ? fSlow250 * static_cast<float>(iVec34[(IOTA0 - iSlow249) & 32767]) + fSlow248 * static_cast<float>(iVec34[(IOTA0 - iSlow246) & 32767]) : static_cast<float>(iTemp220))) & (((iSlow238) ? ((iSlow242) ? ((iTemp198) ? ((iTemp206) ? ((iTemp210) ? 0 : 1) : ((iTemp207) ? ((iTemp197 >= 11) ? 0 : 1) : iTemp208)) : ((iTemp199) ? iTemp216 : ((iTemp200) ? ((iTemp219) ? 0 : 1) : iTemp201))) : ((iSlow243) ? ((iTemp198) ? iTemp214 : iTemp217) : ((iTemp198) ? ((iTemp206) ? ((iTemp210) ? ((iTemp213) ? 1 : 0) : iTemp211) : iTemp209) : ((iTemp199) ? ((iTemp203) ? iTemp218 : 0) : ((iTemp200) ? ((iTemp219) ? 1 : 0) : iTemp201))))) : ((iSlow239) ? ((iSlow241) ? ((iTemp198) ? iTemp214 : ((iTemp199) ? ((iTemp203) ? iTemp218 : iTemp204) : iTemp202)) : ((iTemp198) ? ((iTemp206) ? iTemp212 : 0) : iTemp217)) : ((iSlow240) ? ((iTemp198) ? iTemp214 : iTemp205) : ((iTemp198) ? ((iTemp206) ? iTemp212 : iTemp209) : iTemp205)))) > 0);
			iVec35[0] = iTemp221;
			iRec65[0] = (iRec65[1] + (iRec65[1] > 0)) * (iTemp221 <= iVec35[1]) + (iTemp221 > iVec35[1]);
			float fTemp222 = static_cast<float>(iRec65[0]);
			float fTemp223 = fConst53 * fTemp222;
			float fTemp224 = fConst52 - fTemp222;
			float fTemp225 = ((iTemp29) ? 0.0f : fRec66[1] + fConst18 * (fSlow253 + fSlow252 * std::pow(std::max<float>(0.0f, std::min<float>(fTemp223, fConst16 * fTemp224 + 1.0f)), 1.5f)));
			fRec66[0] = fTemp225 - std::floor(fTemp225);
			float fTemp226 = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec66[0]), 65535))] * std::max<float>(0.0f, std::min<float>(fTemp223, fSlow251 * fTemp224 + 1.0f)) * (((((iTemp197 == 0) | (iTemp197 == 4)) | (iTemp197 == 8)) | (iTemp197 == 12)) ? fSlow236 : 1.0f);
			fRec64[0] = fConst83 * std::fabs(fTemp226) + fConst82 * fRec64[1];
			float fTemp227 = std::max<float>(0.0f, fRec64[0] - fSlow233);
			float fTemp228 = 1.0f / std::tan(fConst61 * std::max<float>(fSlow232, fSlow254 - fSlow256 * fTemp227));
			float fTemp229 = tanhf(fSlow257 * (fTemp226 / (fSlow255 * fTemp227 + 1.0f)));
			fVec36[0] = fTemp229;
			fRec63[0] = -((fRec63[1] * (1.0f - fTemp228) - (fTemp229 + fVec36[1])) / (fTemp228 + 1.0f));
			fRec62[0] = fRec63[0] - fConst81 * (fConst80 * fRec62[2] + fConst78 * fRec62[1]);
			fRec61[0] = fConst81 * (fRec62[2] + fRec62[0] + 2.0f * fRec62[1]) - fConst49 * (fConst47 * fRec61[2] + fConst45 * fRec61[1]);
			float fTemp230 = fRec61[2] + (fRec61[0] - 2.0f * fRec61[1]);
			fRec60[0] = fConst60 * fTemp230 - fConst12 * (fConst10 * fRec60[2] + fConst8 * fRec60[1]);
			fRec59[0] = fConst21 * (fRec60[2] + (fRec60[0] - 2.0f * fRec60[1])) - fConst76 * (fConst75 * fRec59[2] + fConst73 * fRec59[1]);
			float fTemp231 = fConst76 * (fRec59[2] + fRec59[0] + 2.0f * fRec59[1]);
			fRec67[0] = -(fConst85 * (fConst84 * fRec67[1] - (fRec58[(IOTA0 - 702) & 1023] + fRec58[(IOTA0 - 703) & 1023])));
			float fTemp232 = tanhf(fRec67[0]);
			fRec68[0] = -(fConst85 * (fConst84 * fRec68[1] - (fRec57[(IOTA0 - 594) & 1023] + fRec57[(IOTA0 - 595) & 1023])));
			float fTemp233 = tanhf(fRec68[0]);
			fRec69[0] = -(fConst85 * (fConst84 * fRec69[1] - (fRec56[(IOTA0 - 462) & 511] + fRec56[(IOTA0 - 463) & 511])));
			float fTemp234 = tanhf(fRec69[0]);
			fRec70[0] = -(fConst85 * (fConst84 * fRec70[1] - (fRec55[(IOTA0 - 348) & 511] + fRec55[(IOTA0 - 349) & 511])));
			float fTemp235 = tanhf(fRec70[0]);
			float fTemp236 = fTemp235 + fTemp234;
			fRec55[IOTA0 & 511] = 0.75f * (0.5f * (fTemp236 + fTemp233 + fTemp232) + fTemp231);
			fRec56[IOTA0 & 511] = 0.75f * (fTemp231 + 0.5f * (fTemp235 + fTemp233 - (fTemp234 + fTemp232)));
			fRec57[IOTA0 & 1023] = 0.75f * (fTemp231 + 0.5f * (fTemp236 - (fTemp233 + fTemp232)));
			fRec58[IOTA0 & 1023] = 0.75f * (fTemp231 + 0.5f * (fTemp235 + fTemp232 - (fTemp234 + fTemp233)));
			float fTemp237 = fRec55[IOTA0 & 511] + fRec56[IOTA0 & 511] + fRec57[IOTA0 & 1023] + fRec58[IOTA0 & 1023] - 0.5f * fRec53[1];
			fVec37[IOTA0 & 255] = fTemp237;
			fRec53[0] = fVec37[(IOTA0 - 130) & 255];
			float fRec54 = 0.5f * fTemp237;
			float fTemp238 = fRec54 + fRec53[1] - 0.5f * fRec51[1];
			fVec38[IOTA0 & 255] = fTemp238;
			fRec51[0] = fVec38[(IOTA0 - 190) & 255];
			float fRec52 = 0.5f * fTemp238;
			float fTemp239 = fSlow261 * (fSlow260 * fTemp230 + fSlow259 * (fRec52 + fRec51[1])) + fSlow231 * tanhf(fConst67 * (fRec45[2] + fRec45[0] + 2.0f * fRec45[1])) + fSlow189 * (fRec37[2] + (fRec37[0] - 2.0f * fRec37[1])) + fSlow90 * (fRec27[2] + fRec27[0] + 2.0f * fRec27[1]) + fSlow59 * (fRec12[2] + fRec12[0] + 2.0f * fRec12[1]);
			float fTemp240 = tanhf(1.5f * (fTemp239 + fSlow24 * std::sqrt(1.0f - fRec11[0]) * fTemp45));
			fVec39[0] = fTemp240;
			fRec0[0] = 0.995f * fRec0[1] + fTemp240 - fVec39[1];
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0]);
			float fTemp241 = std::sin(3.1415927f * fRec11[0]);
			float fTemp242 = std::tan(fConst61 * (fSlow262 * fTemp241 + 4e+02f));
			float fTemp243 = 1.0f / fTemp242;
			float fTemp244 = (fSlow263 + fTemp243) / fTemp242 + 1.0f;
			float fTemp245 = fSlow264 * fTemp241;
			float fTemp246 = fTemp245 + 1e+02f;
			int iTemp247 = static_cast<int>(fTemp246);
			float fTemp248 = std::floor(fTemp246);
			fRec72[0] = fConst5 * (fVec7[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp247))) & 255] * (fTemp248 + (-99.0f - fTemp245)) + (fTemp245 + (1e+02f - fTemp248)) * fVec7[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp247 + 1))) & 255]) - (fRec72[2] * ((fTemp243 - fSlow263) / fTemp242 + 1.0f) + 2.0f * fRec72[1] * (1.0f - 1.0f / mydsp_faustpower2_f(fTemp242))) / fTemp244;
			float fTemp249 = tanhf(1.5f * (fTemp239 + fSlow265 * (std::sqrt(fRec11[0]) * (fRec72[0] - fRec72[2]) / (fTemp242 * fTemp244))));
			fVec40[0] = fTemp249;
			fRec71[0] = 0.995f * fRec71[1] + fTemp249 - fVec40[1];
			output1[i0] = static_cast<FAUSTFLOAT>(fRec71[0]);
			iVec0[1] = iVec0[0];
			iRec3[1] = iRec3[0];
			iVec1[1] = iVec1[0];
			IOTA0 = IOTA0 + 1;
			iVec3[1] = iVec3[0];
			iRec4[1] = iRec4[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fVec5[1] = fVec5[0];
			fRec10[1] = fRec10[0];
			fRec8[1] = fRec8[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec11[1] = fRec11[0];
			fRec16[1] = fRec16[0];
			iVec8[1] = iVec8[0];
			iVec10[1] = iVec10[0];
			iRec22[1] = iRec22[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			iVec11[1] = iVec11[0];
			iVec13[1] = iVec13[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			iRec32[1] = iRec32[0];
			iRec34[1] = iRec34[0];
			fVec14[1] = fVec14[0];
			fRec33[1] = fRec33[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec38[1] = fRec38[0];
			fVec15[1] = fVec15[0];
			fRec39[1] = fRec39[0];
			fVec17[1] = fVec17[0];
			fRec40[1] = fRec40[0];
			fVec19[1] = fVec19[0];
			fRec41[1] = fRec41[0];
			fVec21[1] = fVec21[0];
			fRec42[1] = fRec42[0];
			fVec23[1] = fVec23[0];
			fRec43[1] = fRec43[0];
			fVec25[1] = fVec25[0];
			iVec27[1] = iVec27[0];
			iVec29[1] = iVec29[0];
			iRec44[1] = iRec44[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			iVec30[1] = iVec30[0];
			iVec32[1] = iVec32[0];
			iRec47[1] = iRec47[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			iVec33[1] = iVec33[0];
			iVec35[1] = iVec35[0];
			iRec65[1] = iRec65[0];
			fRec66[1] = fRec66[0];
			fRec64[1] = fRec64[0];
			fVec36[1] = fVec36[0];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec67[1] = fRec67[0];
			fRec68[1] = fRec68[0];
			fRec69[1] = fRec69[0];
			fRec70[1] = fRec70[0];
			fRec53[1] = fRec53[0];
			fRec51[1] = fRec51[0];
			fVec39[1] = fVec39[0];
			fRec0[1] = fRec0[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fVec40[1] = fVec40[0];
			fRec71[1] = fRec71[0];
		}
	}

};

extern "C" dsp* newmydsp() {
    return new mydsp();
}

extern "C" void deletemydsp(dsp* d) {
    delete d;
}

#endif
