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
	float fConst34;
	FAUSTFLOAT fHslider12;
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	int iVec8[2];
	int iVec9[32768];
	FAUSTFLOAT fHslider15;
	int iVec10[2];
	float fRec15[2];
	FAUSTFLOAT fHslider16;
	float fConst35;
	float fRec14[2];
	FAUSTFLOAT fHslider17;
	int iRec17[2];
	float fConst36;
	float fConst37;
	float fConst38;
	float fConst39;
	float fConst40;
	int iRec19[2];
	float fVec11[2];
	float fConst41;
	float fRec18[2];
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fHslider19;
	FAUSTFLOAT fHslider20;
	float fConst42;
	float fConst43;
	float fRec21[2];
	FAUSTFLOAT fHslider21;
	float fRec20[2];
	FAUSTFLOAT fHslider22;
	float fRec16[8192];
	float fRec13[3];
	float fConst44;
	float fRec12[3];
	FAUSTFLOAT fHslider23;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	FAUSTFLOAT fHslider24;
	FAUSTFLOAT fHslider25;
	FAUSTFLOAT fHslider26;
	int iVec12[2];
	int iVec13[32768];
	FAUSTFLOAT fHslider27;
	int iVec14[2];
	int iRec24[2];
	FAUSTFLOAT fHslider28;
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fRec25[3];
	FAUSTFLOAT fHslider29;
	float fConst63;
	float fConst64;
	float fConst65;
	FAUSTFLOAT fHslider30;
	FAUSTFLOAT fHslider31;
	float fConst66;
	float fRec26[2];
	float fConst67;
	float fRec27[2];
	FAUSTFLOAT fHslider32;
	float fRec23[3];
	float fConst68;
	float fRec22[3];
	FAUSTFLOAT fHslider33;
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	FAUSTFLOAT fHslider34;
	FAUSTFLOAT fHslider35;
	float fConst79;
	FAUSTFLOAT fHslider36;
	FAUSTFLOAT fHslider37;
	int iVec15[2];
	FAUSTFLOAT fHslider38;
	FAUSTFLOAT fHslider39;
	int iVec16[32768];
	FAUSTFLOAT fHslider40;
	int iVec17[2];
	int iRec42[2];
	FAUSTFLOAT fHslider41;
	FAUSTFLOAT fHslider42;
	FAUSTFLOAT fHslider43;
	FAUSTFLOAT fHslider44;
	float fRec43[2];
	float fConst80;
	float fRec41[2];
	FAUSTFLOAT fHslider45;
	FAUSTFLOAT fHslider46;
	float fConst81;
	FAUSTFLOAT fHslider47;
	float fVec18[2];
	float fRec40[2];
	float fRec39[3];
	float fRec38[3];
	float fRec37[3];
	float fRec36[3];
	float fConst82;
	float fConst83;
	float fRec44[2];
	float fRec45[2];
	float fRec46[2];
	float fRec47[2];
	float fRec32[512];
	float fRec33[512];
	float fRec34[1024];
	float fRec35[1024];
	float fVec19[256];
	float fRec30[2];
	float fVec20[256];
	float fRec28[2];
	FAUSTFLOAT fHslider48;
	FAUSTFLOAT fHslider49;
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	FAUSTFLOAT fHslider50;
	float fRec49[2];
	float fVec21[2];
	float fConst90;
	float fVec22[128];
	float fRec50[2];
	float fVec23[2];
	float fVec24[128];
	float fRec51[2];
	float fVec25[2];
	float fVec26[128];
	float fRec52[2];
	float fVec27[2];
	float fVec28[256];
	float fRec53[2];
	float fVec29[2];
	float fVec30[256];
	float fRec54[2];
	float fVec31[2];
	float fVec32[512];
	FAUSTFLOAT fHslider51;
	FAUSTFLOAT fHslider52;
	FAUSTFLOAT fHslider53;
	int iVec33[2];
	FAUSTFLOAT fHslider54;
	FAUSTFLOAT fHslider55;
	int iVec34[32768];
	FAUSTFLOAT fHslider56;
	int iVec35[2];
	int iRec55[2];
	FAUSTFLOAT fHslider57;
	FAUSTFLOAT fHslider58;
	float fRec48[3];
	FAUSTFLOAT fHslider59;
	float fConst91;
	float fConst92;
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	FAUSTFLOAT fHslider60;
	FAUSTFLOAT fHslider61;
	FAUSTFLOAT fHslider62;
	float fRec60[2];
	FAUSTFLOAT fHslider63;
	FAUSTFLOAT fHslider64;
	FAUSTFLOAT fHslider65;
	float fRec67[2];
	int iVec36[2];
	int iRec66[2];
	FAUSTFLOAT fHslider66;
	FAUSTFLOAT fHslider67;
	int iVec37[2];
	int iRec68[2];
	FAUSTFLOAT fHslider68;
	FAUSTFLOAT fHslider69;
	FAUSTFLOAT fHslider70;
	float fRec65[2];
	float fConst99;
	float fConst100;
	float fConst101;
	float fRec69[2];
	float fRec70[2];
	float fRec71[2];
	float fRec72[2];
	FAUSTFLOAT fHslider71;
	float fRec61[2048];
	float fRec62[2048];
	float fRec63[2048];
	float fRec64[4096];
	FAUSTFLOAT fHslider72;
	float fRec59[2];
	FAUSTFLOAT fHslider73;
	float fRec58[2];
	float fRec57[3];
	float fConst102;
	float fRec56[3];
	FAUSTFLOAT fHslider74;
	float fVec38[2];
	float fRec0[2];
	FAUSTFLOAT fHslider75;
	float fRec74[3];
	float fVec39[2];
	float fRec73[2];
	
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
		fConst22 = std::tan(2513.2742f / fConst0);
		fConst23 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst22));
		fConst24 = 1.0f / fConst22;
		fConst25 = (fConst24 + -1.4142135f) / fConst22 + 1.0f;
		fConst26 = 1.0f / ((fConst24 + 1.4142135f) / fConst22 + 1.0f);
		fConst27 = std::tan(62.831852f / fConst0);
		fConst28 = mydsp_faustpower2_f(fConst27);
		fConst29 = 2.0f * (1.0f - 1.0f / fConst28);
		fConst30 = 1.0f / fConst27;
		fConst31 = (fConst30 + -1.4142135f) / fConst27 + 1.0f;
		fConst32 = (fConst30 + 1.4142135f) / fConst27 + 1.0f;
		fConst33 = 1.0f / fConst32;
		fConst34 = std::exp(-(2e+02f / fConst0));
		fConst35 = 1.0f - fConst34;
		fConst36 = std::max<float>(1.0f, 0.001f * fConst0);
		fConst37 = 1.0f / fConst36;
		fConst38 = 1.0f / std::max<float>(1.0f, 0.18f * fConst0);
		fConst39 = 1.0f / std::tan(4712.389f / fConst0);
		fConst40 = 1.0f - fConst39;
		fConst41 = 1.0f / (fConst39 + 1.0f);
		fConst42 = 0.0022727272f * fConst0;
		fConst43 = 3.0f / fConst0;
		fConst44 = 1.0f / (fConst28 * fConst32);
		fConst45 = std::tan(28274.334f / fConst0);
		fConst46 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst45));
		fConst47 = 1.0f / fConst45;
		fConst48 = (fConst47 + -1.4142135f) / fConst45 + 1.0f;
		fConst49 = 1.0f / ((fConst47 + 1.4142135f) / fConst45 + 1.0f);
		fConst50 = std::tan(502.65482f / fConst0);
		fConst51 = mydsp_faustpower2_f(fConst50);
		fConst52 = 2.0f * (1.0f - 1.0f / fConst51);
		fConst53 = 1.0f / fConst50;
		fConst54 = (fConst53 + -1.4142135f) / fConst50 + 1.0f;
		fConst55 = (fConst53 + 1.4142135f) / fConst50 + 1.0f;
		fConst56 = 1.0f / fConst55;
		fConst57 = std::tan(5183.628f / fConst0);
		fConst58 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst57));
		fConst59 = 1.0f / fConst57;
		fConst60 = (fConst59 + -0.4f) / fConst57 + 1.0f;
		fConst61 = (fConst59 + 0.4f) / fConst57 + 1.0f;
		fConst62 = 1.0f / fConst61;
		fConst63 = 2.34f / (fConst57 * fConst61);
		fConst64 = std::max<float>(1.0f, 0.0005f * fConst0);
		fConst65 = 1.0f / fConst64;
		fConst66 = 332.0f / fConst0;
		fConst67 = 1.8e+02f / fConst0;
		fConst68 = 1.0f / (fConst51 * fConst55);
		fConst69 = std::tan(3769.9111f / fConst0);
		fConst70 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst69));
		fConst71 = 1.0f / fConst69;
		fConst72 = (fConst71 + -1.4142135f) / fConst69 + 1.0f;
		fConst73 = 1.0f / ((fConst71 + 1.4142135f) / fConst69 + 1.0f);
		fConst74 = std::tan(7853.9814f / fConst0);
		fConst75 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst74));
		fConst76 = 1.0f / fConst74;
		fConst77 = (fConst76 + -1.4142135f) / fConst74 + 1.0f;
		fConst78 = 1.0f / ((fConst76 + 1.4142135f) / fConst74 + 1.0f);
		fConst79 = std::exp(-(1e+02f / fConst0));
		fConst80 = 1.0f - fConst79;
		fConst81 = 3.1415927f / fConst0;
		fConst82 = 1.0f - fConst3;
		fConst83 = 1.0f / (fConst3 + 1.0f);
		fConst84 = std::tan(20420.352f / fConst0);
		fConst85 = mydsp_faustpower2_f(fConst84);
		fConst86 = 2.0f * (1.0f - 1.0f / fConst85);
		fConst87 = 1.0f / fConst84;
		fConst88 = (fConst87 + -1.4142135f) / fConst84 + 1.0f;
		fConst89 = 1.0f / ((fConst87 + 1.4142135f) / fConst84 + 1.0f);
		fConst90 = 0.25f * fConst0;
		fConst91 = 2.0f / fConst85;
		fConst92 = std::tan(471.2389f / fConst0);
		fConst93 = mydsp_faustpower2_f(fConst92);
		fConst94 = 2.0f * (1.0f - 1.0f / fConst93);
		fConst95 = 1.0f / fConst92;
		fConst96 = (fConst95 + -1.4142135f) / fConst92 + 1.0f;
		fConst97 = (fConst95 + 1.4142135f) / fConst92 + 1.0f;
		fConst98 = 1.0f / fConst97;
		fConst99 = 1.0f / std::tan(10995.574f / fConst0);
		fConst100 = 1.0f - fConst99;
		fConst101 = 1.0f / (fConst99 + 1.0f);
		fConst102 = 1.0f / (fConst93 * fConst97);
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
		fHslider12 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider13 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider14 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider15 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider16 = static_cast<FAUSTFLOAT>(0.35f);
		fHslider17 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider18 = static_cast<FAUSTFLOAT>(-12.0f);
		fHslider19 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider20 = static_cast<FAUSTFLOAT>(0.04f);
		fHslider21 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider22 = static_cast<FAUSTFLOAT>(0.65f);
		fHslider23 = static_cast<FAUSTFLOAT>(0.55f);
		fHslider24 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider25 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider26 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider27 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider28 = static_cast<FAUSTFLOAT>(0.16f);
		fHslider29 = static_cast<FAUSTFLOAT>(0.55f);
		fHslider30 = static_cast<FAUSTFLOAT>(0.07f);
		fHslider31 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider32 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider33 = static_cast<FAUSTFLOAT>(0.65f);
		fHslider34 = static_cast<FAUSTFLOAT>(7.5e+02f);
		fHslider35 = static_cast<FAUSTFLOAT>(0.4f);
		fHslider36 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider37 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider38 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider39 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider40 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider41 = static_cast<FAUSTFLOAT>(0.18f);
		fHslider42 = static_cast<FAUSTFLOAT>(1.5e+02f);
		fHslider43 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider44 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider45 = static_cast<FAUSTFLOAT>(2.5e+03f);
		fHslider46 = static_cast<FAUSTFLOAT>(8.0f);
		fHslider47 = static_cast<FAUSTFLOAT>(3.5f);
		fHslider48 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider49 = static_cast<FAUSTFLOAT>(0.85f);
		fHslider50 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider51 = static_cast<FAUSTFLOAT>(0.35f);
		fHslider52 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider53 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider54 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider55 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider56 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider57 = static_cast<FAUSTFLOAT>(0.001f);
		fHslider58 = static_cast<FAUSTFLOAT>(0.04f);
		fHslider59 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider60 = static_cast<FAUSTFLOAT>(0.005f);
		fHslider61 = static_cast<FAUSTFLOAT>(-2e+01f);
		fHslider62 = static_cast<FAUSTFLOAT>(2.0f);
		fHslider63 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider64 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider65 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider66 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider67 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider68 = static_cast<FAUSTFLOAT>(0.2f);
		fHslider69 = static_cast<FAUSTFLOAT>(12.0f);
		fHslider70 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider71 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider72 = static_cast<FAUSTFLOAT>(0.1f);
		fHslider73 = static_cast<FAUSTFLOAT>(6.0f);
		fHslider74 = static_cast<FAUSTFLOAT>(0.22f);
		fHslider75 = static_cast<FAUSTFLOAT>(4.5f);
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
			iVec8[l18] = 0;
		}
		for (int l19 = 0; l19 < 32768; l19 = l19 + 1) {
			iVec9[l19] = 0;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			iVec10[l20] = 0;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec15[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec14[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			iRec17[l23] = 0;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			iRec19[l24] = 0;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fVec11[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec18[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec21[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec20[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 8192; l29 = l29 + 1) {
			fRec16[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 3; l30 = l30 + 1) {
			fRec13[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 3; l31 = l31 + 1) {
			fRec12[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			iVec12[l32] = 0;
		}
		for (int l33 = 0; l33 < 32768; l33 = l33 + 1) {
			iVec13[l33] = 0;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			iVec14[l34] = 0;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			iRec24[l35] = 0;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec25[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec26[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fRec27[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec23[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 3; l40 = l40 + 1) {
			fRec22[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			iVec15[l41] = 0;
		}
		for (int l42 = 0; l42 < 32768; l42 = l42 + 1) {
			iVec16[l42] = 0;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			iVec17[l43] = 0;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			iRec42[l44] = 0;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec43[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec41[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fVec18[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fRec40[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 3; l49 = l49 + 1) {
			fRec39[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 3; l50 = l50 + 1) {
			fRec38[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 3; l51 = l51 + 1) {
			fRec37[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 3; l52 = l52 + 1) {
			fRec36[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fRec44[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec45[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec46[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2; l56 = l56 + 1) {
			fRec47[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 512; l57 = l57 + 1) {
			fRec32[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 512; l58 = l58 + 1) {
			fRec33[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 1024; l59 = l59 + 1) {
			fRec34[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 1024; l60 = l60 + 1) {
			fRec35[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 256; l61 = l61 + 1) {
			fVec19[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec30[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 256; l63 = l63 + 1) {
			fVec20[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fRec28[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fRec49[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 2; l66 = l66 + 1) {
			fVec21[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 128; l67 = l67 + 1) {
			fVec22[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fRec50[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 2; l69 = l69 + 1) {
			fVec23[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 128; l70 = l70 + 1) {
			fVec24[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 2; l71 = l71 + 1) {
			fRec51[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 2; l72 = l72 + 1) {
			fVec25[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 128; l73 = l73 + 1) {
			fVec26[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 2; l74 = l74 + 1) {
			fRec52[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			fVec27[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 256; l76 = l76 + 1) {
			fVec28[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 2; l77 = l77 + 1) {
			fRec53[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			fVec29[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 256; l79 = l79 + 1) {
			fVec30[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 2; l80 = l80 + 1) {
			fRec54[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 2; l81 = l81 + 1) {
			fVec31[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 512; l82 = l82 + 1) {
			fVec32[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 2; l83 = l83 + 1) {
			iVec33[l83] = 0;
		}
		for (int l84 = 0; l84 < 32768; l84 = l84 + 1) {
			iVec34[l84] = 0;
		}
		for (int l85 = 0; l85 < 2; l85 = l85 + 1) {
			iVec35[l85] = 0;
		}
		for (int l86 = 0; l86 < 2; l86 = l86 + 1) {
			iRec55[l86] = 0;
		}
		for (int l87 = 0; l87 < 3; l87 = l87 + 1) {
			fRec48[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 2; l88 = l88 + 1) {
			fRec60[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 2; l89 = l89 + 1) {
			fRec67[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 2; l90 = l90 + 1) {
			iVec36[l90] = 0;
		}
		for (int l91 = 0; l91 < 2; l91 = l91 + 1) {
			iRec66[l91] = 0;
		}
		for (int l92 = 0; l92 < 2; l92 = l92 + 1) {
			iVec37[l92] = 0;
		}
		for (int l93 = 0; l93 < 2; l93 = l93 + 1) {
			iRec68[l93] = 0;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fRec65[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 2; l95 = l95 + 1) {
			fRec69[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 2; l96 = l96 + 1) {
			fRec70[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 2; l97 = l97 + 1) {
			fRec71[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 2; l98 = l98 + 1) {
			fRec72[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 2048; l99 = l99 + 1) {
			fRec61[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 2048; l100 = l100 + 1) {
			fRec62[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 2048; l101 = l101 + 1) {
			fRec63[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 4096; l102 = l102 + 1) {
			fRec64[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 2; l103 = l103 + 1) {
			fRec59[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 2; l104 = l104 + 1) {
			fRec58[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 3; l105 = l105 + 1) {
			fRec57[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 3; l106 = l106 + 1) {
			fRec56[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 2; l107 = l107 + 1) {
			fVec38[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 2; l108 = l108 + 1) {
			fRec0[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 3; l109 = l109 + 1) {
			fRec74[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 2; l110 = l110 + 1) {
			fVec39[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 2; l111 = l111 + 1) {
			fRec73[l111] = 0.0f;
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
		ui_interface->declare(&fHslider38, "osc", "/master/accent");
		ui_interface->declare(&fHslider38, "style", "knob");
		ui_interface->addHorizontalSlider("Accent_Global", &fHslider38, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider36, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider36, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider44, "osc", "/master/nota");
		ui_interface->declare(&fHslider44, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Nota_Fundamental", &fHslider44, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider40, "osc", "/master/swing");
		ui_interface->declare(&fHslider40, "style", "knob");
		ui_interface->addHorizontalSlider("Swing_Groove", &fHslider40, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider39, "osc", "/master/groove");
		ui_interface->declare(&fHslider39, "style", "menu{     '1: Ultra Hipnotico':0;      '2: Deep Mental':1;      '3: Bucle Psiquico':2;      '4: Driving Techno':3;      '5: Tribal Funk':4;      '6: Hardgroove Tradicional':5;      '7: Hardgroove Frenetico':6 }");
		ui_interface->addHorizontalSlider("Evolucion_Groove", &fHslider39, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider43, "1", "");
		ui_interface->declare(&fHslider43, "osc", "/kick/tune");
		ui_interface->declare(&fHslider43, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider43, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider41, "1", "");
		ui_interface->declare(&fHslider41, "osc", "/kick/dec");
		ui_interface->declare(&fHslider41, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider41, FAUSTFLOAT(0.18f), FAUSTFLOAT(0.02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider48, "1", "");
		ui_interface->declare(&fHslider48, "osc", "/kick/mix");
		ui_interface->declare(&fHslider48, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Rumble", &fHslider48, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider37, "1", "");
		ui_interface->declare(&fHslider37, "osc", "/kick/reloj");
		ui_interface->declare(&fHslider37, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider37, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider42, "1", "");
		ui_interface->declare(&fHslider42, "osc", "/kick/sweep");
		ui_interface->declare(&fHslider42, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Transitorio", &fHslider42, FAUSTFLOAT(1.5e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(3e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider49, "1", "");
		ui_interface->declare(&fHslider49, "osc", "/kick/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider49, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider45, "2", "");
		ui_interface->declare(&fHslider45, "osc", "/kick/comp_fmax");
		ui_interface->declare(&fHslider45, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Filtro Frec Max", &fHslider45, FAUSTFLOAT(2.5e+03f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(8e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider34, "2", "");
		ui_interface->declare(&fHslider34, "osc", "/kick/comp_fmin");
		ui_interface->declare(&fHslider34, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Filtro Frec Min", &fHslider34, FAUSTFLOAT(7.5e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider46, "2", "");
		ui_interface->declare(&fHslider46, "osc", "/kick/comp_ratio");
		ui_interface->declare(&fHslider46, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Lim Ratio", &fHslider46, FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider35, "2", "");
		ui_interface->declare(&fHslider35, "osc", "/kick/comp_thresh");
		ui_interface->declare(&fHslider35, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Lim Umbral", &fHslider35, FAUSTFLOAT(0.4f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider47, "2", "");
		ui_interface->declare(&fHslider47, "osc", "/kick/comp_drive");
		ui_interface->declare(&fHslider47, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Saturacion Pegada", &fHslider47, FAUSTFLOAT(3.5f), FAUSTFLOAT(0.5f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("Caja");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider32, "osc", "/master/accent");
		ui_interface->declare(&fHslider32, "style", "knob");
		ui_interface->addHorizontalSlider("Accent_Global", &fHslider32, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider25, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider25, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider27, "osc", "/master/swing");
		ui_interface->declare(&fHslider27, "style", "knob");
		ui_interface->addHorizontalSlider("Swing_Groove", &fHslider27, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider24, "osc", "/master/groove");
		ui_interface->declare(&fHslider24, "style", "menu{     '1: Ultra Hipnotico':0;      '2: Deep Mental':1;      '3: Bucle Psiquico':2;      '4: Driving Techno':3;      '5: Tribal Funk':4;      '6: Hardgroove Tradicional':5;      '7: Hardgroove Frenetico':6 }");
		ui_interface->addHorizontalSlider("Evolucion_Groove", &fHslider24, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider31, "1", "");
		ui_interface->declare(&fHslider31, "osc", "/snare/tune");
		ui_interface->declare(&fHslider31, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider31, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider30, "1", "");
		ui_interface->declare(&fHslider30, "osc", "/snare/dec_cuerpo");
		ui_interface->declare(&fHslider30, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decay Cuerpo", &fHslider30, FAUSTFLOAT(0.07f), FAUSTFLOAT(0.01f), FAUSTFLOAT(0.4f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider28, "1", "");
		ui_interface->declare(&fHslider28, "osc", "/snare/dec_resorte");
		ui_interface->declare(&fHslider28, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decay Resortes", &fHslider28, FAUSTFLOAT(0.16f), FAUSTFLOAT(0.02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider29, "1", "");
		ui_interface->declare(&fHslider29, "osc", "/snare/mix");
		ui_interface->declare(&fHslider29, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Resortes", &fHslider29, FAUSTFLOAT(0.55f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider26, "1", "");
		ui_interface->declare(&fHslider26, "osc", "/snare/reloj");
		ui_interface->declare(&fHslider26, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider26, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider33, "1", "");
		ui_interface->declare(&fHslider33, "osc", "/snare/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider33, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("Platillos");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider54, "osc", "/master/accent");
		ui_interface->declare(&fHslider54, "style", "knob");
		ui_interface->addHorizontalSlider("Accent_Global", &fHslider54, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider52, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider52, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider56, "osc", "/master/swing");
		ui_interface->declare(&fHslider56, "style", "knob");
		ui_interface->addHorizontalSlider("Swing_Groove", &fHslider56, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider55, "osc", "/master/groove");
		ui_interface->declare(&fHslider55, "style", "menu{     '1: Ultra Hipnotico':0;      '2: Deep Mental':1;      '3: Bucle Psiquico':2;      '4: Driving Techno':3;      '5: Tribal Funk':4;      '6: Hardgroove Tradicional':5;      '7: Hardgroove Frenetico':6 }");
		ui_interface->addHorizontalSlider("Evolucion_Groove", &fHslider55, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider50, "1", "");
		ui_interface->declare(&fHslider50, "osc", "/hat/tune");
		ui_interface->declare(&fHslider50, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider50, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider57, "1", "");
		ui_interface->declare(&fHslider57, "osc", "/hat/ataque");
		ui_interface->declare(&fHslider57, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Ataque", &fHslider57, FAUSTFLOAT(0.001f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider58, "1", "");
		ui_interface->declare(&fHslider58, "osc", "/hat/dec");
		ui_interface->declare(&fHslider58, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider58, FAUSTFLOAT(0.04f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider53, "1", "");
		ui_interface->declare(&fHslider53, "osc", "/hat/reloj");
		ui_interface->declare(&fHslider53, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider53, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider51, "1", "");
		ui_interface->declare(&fHslider51, "osc", "/hat/drive");
		ui_interface->declare(&fHslider51, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider51, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider59, "1", "");
		ui_interface->declare(&fHslider59, "osc", "/hat/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider59, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openVerticalBox("Bajo WG");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider17, "osc", "/master/accent");
		ui_interface->declare(&fHslider17, "style", "knob");
		ui_interface->addHorizontalSlider("Accent_Global", &fHslider17, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider14, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider14, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider19, "osc", "/master/nota");
		ui_interface->declare(&fHslider19, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Nota_Fundamental", &fHslider19, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider15, "osc", "/master/swing");
		ui_interface->declare(&fHslider15, "style", "knob");
		ui_interface->addHorizontalSlider("Swing_Groove", &fHslider15, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider12, "osc", "/master/groove");
		ui_interface->declare(&fHslider12, "style", "menu{     '1: Ultra Hipnotico':0;      '2: Deep Mental':1;      '3: Bucle Psiquico':2;      '4: Driving Techno':3;      '5: Tribal Funk':4;      '6: Hardgroove Tradicional':5;      '7: Hardgroove Frenetico':6 }");
		ui_interface->addHorizontalSlider("Evolucion_Groove", &fHslider12, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider16, "1", "");
		ui_interface->declare(&fHslider16, "osc", "/bass/dec");
		ui_interface->declare(&fHslider16, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider16, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider20, "1", "");
		ui_interface->declare(&fHslider20, "osc", "/bass/detune");
		ui_interface->declare(&fHslider20, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Desafinado", &fHslider20, FAUSTFLOAT(0.04f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider21, "1", "");
		ui_interface->declare(&fHslider21, "osc", "/bass/lfo");
		ui_interface->declare(&fHslider21, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro LFO", &fHslider21, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider18, "1", "");
		ui_interface->declare(&fHslider18, "osc", "/bass/intervalo");
		ui_interface->addHorizontalSlider("Sintesis/Intervalo", &fHslider18, FAUSTFLOAT(-12.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(7.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider13, "1", "");
		ui_interface->declare(&fHslider13, "osc", "/bass/reloj");
		ui_interface->declare(&fHslider13, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider13, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider22, "1", "");
		ui_interface->declare(&fHslider22, "osc", "/bass/drive");
		ui_interface->declare(&fHslider22, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider22, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider23, "1", "");
		ui_interface->declare(&fHslider23, "osc", "/bass/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider23, FAUSTFLOAT(0.55f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "5", "");
		ui_interface->openVerticalBox("Synth Psyche");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider2, "osc", "/master/accent");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Accent_Global", &fHslider2, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider0, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider7, "osc", "/master/nota");
		ui_interface->declare(&fHslider7, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Nota_Fundamental", &fHslider7, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider4, "osc", "/master/swing");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Swing_Groove", &fHslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider3, "osc", "/master/groove");
		ui_interface->declare(&fHslider3, "style", "menu{     '1: Ultra Hipnotico':0;      '2: Deep Mental':1;      '3: Bucle Psiquico':2;      '4: Driving Techno':3;      '5: Tribal Funk':4;      '6: Hardgroove Tradicional':5;      '7: Hardgroove Frenetico':6 }");
		ui_interface->addHorizontalSlider("Evolucion_Groove", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider10, "1", "");
		ui_interface->declare(&fHslider10, "osc", "/syn1/auto_p");
		ui_interface->declare(&fHslider10, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Profundidad", &fHslider10, FAUSTFLOAT(0.7f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider75, "1", "");
		ui_interface->declare(&fHslider75, "osc", "/syn1/auto_r");
		ui_interface->declare(&fHslider75, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Resonancia", &fHslider75, FAUSTFLOAT(4.5f), FAUSTFLOAT(1.0f), FAUSTFLOAT(9.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider9, "1", "");
		ui_interface->declare(&fHslider9, "osc", "/syn1/auto_v");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Velocidad", &fHslider9, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.05f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "osc", "/syn1/dec");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider5, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
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
		ui_interface->declare(&fHslider11, "1", "");
		ui_interface->declare(&fHslider11, "osc", "/syn1/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider11, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "6", "");
		ui_interface->openVerticalBox("Siringe FDN");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider66, "osc", "/master/accent");
		ui_interface->declare(&fHslider66, "style", "knob");
		ui_interface->addHorizontalSlider("Accent_Global", &fHslider66, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider64, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider64, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider70, "osc", "/master/nota");
		ui_interface->declare(&fHslider70, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Nota_Fundamental", &fHslider70, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider68, "1", "");
		ui_interface->declare(&fHslider68, "osc", "/syn2/dec");
		ui_interface->declare(&fHslider68, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider68, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider71, "1", "");
		ui_interface->declare(&fHslider71, "osc", "/syn2/disp");
		ui_interface->declare(&fHslider71, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Dispersion", &fHslider71, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.9f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider62, "1", "");
		ui_interface->declare(&fHslider62, "osc", "/syn2/lfo_f");
		ui_interface->declare(&fHslider62, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/LFO Freq", &fHslider62, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider63, "1", "");
		ui_interface->declare(&fHslider63, "osc", "/syn2/lfo_p");
		ui_interface->declare(&fHslider63, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/LFO Profundidad", &fHslider63, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider69, "1", "");
		ui_interface->declare(&fHslider69, "osc", "/syn2/nota");
		ui_interface->declare(&fHslider69, "style", "menu{'Octava':12; 'Quinta Arriba':19; 'Doble Octava':24}");
		ui_interface->addHorizontalSlider("Sintesis/Nota Siringe", &fHslider69, FAUSTFLOAT(12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider67, "1", "");
		ui_interface->declare(&fHslider67, "osc", "/syn2/pat");
		ui_interface->declare(&fHslider67, "style", "menu{'1':0; '2':1; '3':2; '4':3; '5':4; '6':5; '7':6}");
		ui_interface->addHorizontalSlider("Sintesis/Patron", &fHslider67, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider65, "1", "");
		ui_interface->declare(&fHslider65, "osc", "/syn2/reloj");
		ui_interface->declare(&fHslider65, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider65, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider74, "1", "");
		ui_interface->declare(&fHslider74, "osc", "/syn2/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider74, FAUSTFLOAT(0.22f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider60, "2", "");
		ui_interface->declare(&fHslider60, "osc", "/syn2/comp_a");
		ui_interface->declare(&fHslider60, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Ataque", &fHslider60, FAUSTFLOAT(0.005f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider72, "2", "");
		ui_interface->declare(&fHslider72, "osc", "/syn2/comp_rel");
		ui_interface->declare(&fHslider72, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Liberacion", &fHslider72, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider73, "2", "");
		ui_interface->declare(&fHslider73, "osc", "/syn2/comp_r");
		ui_interface->declare(&fHslider73, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Ratio", &fHslider73, FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider61, "2", "");
		ui_interface->declare(&fHslider61, "osc", "/syn2/comp_th");
		ui_interface->declare(&fHslider61, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Umbral", &fHslider61, FAUSTFLOAT(-2e+01f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f));
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
		int iSlow26 = fSlow25 >= 4.0f;
		int iSlow27 = fSlow25 >= 2.0f;
		int iSlow28 = fSlow25 >= 1.0f;
		float fSlow29 = static_cast<float>(fHslider14);
		float fSlow30 = fSlow29 * static_cast<float>(fHslider13);
		float fSlow31 = fConst13 * fSlow30;
		int iSlow32 = fSlow25 >= 3.0f;
		int iSlow33 = fSlow25 >= 6.0f;
		int iSlow34 = fSlow25 >= 5.0f;
		float fSlow35 = fConst14 * (static_cast<float>(fHslider15) / fSlow30);
		int iSlow36 = static_cast<int>(fSlow35);
		int iSlow37 = std::min<int>(16385, std::max<int>(0, iSlow36 + 1));
		float fSlow38 = std::floor(fSlow35);
		float fSlow39 = fSlow35 - fSlow38;
		int iSlow40 = std::min<int>(16385, std::max<int>(0, iSlow36));
		float fSlow41 = fSlow38 + (1.0f - fSlow35);
		float fSlow42 = 0.004166667f * (fSlow29 / static_cast<float>(fHslider16));
		float fSlow43 = 0.4f * static_cast<float>(fHslider17) + 1.0f;
		float fSlow44 = static_cast<float>(fHslider20);
		float fSlow45 = fConst42 * ((0.059f * fSlow44 + 1.0f) / (std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider19) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider18))));
		int iSlow46 = static_cast<int>(fSlow45);
		int iSlow47 = std::min<int>(131073, std::max<int>(0, iSlow46 + 1)) + 1;
		float fSlow48 = std::floor(fSlow45);
		float fSlow49 = fSlow45 - fSlow48;
		int iSlow50 = std::min<int>(131073, std::max<int>(0, iSlow46)) + 1;
		float fSlow51 = fSlow48 + (1.0f - fSlow45);
		float fSlow52 = static_cast<float>(fHslider21);
		float fSlow53 = 3.0f * static_cast<float>(fHslider22);
		float fSlow54 = (fSlow53 + 1.0f) * (0.014f * fSlow44 + 0.985f);
		float fSlow55 = fConst26 * static_cast<float>(fHslider23);
		float fSlow56 = static_cast<float>(fHslider24);
		int iSlow57 = fSlow56 >= 4.0f;
		int iSlow58 = fSlow56 >= 2.0f;
		int iSlow59 = fSlow56 >= 1.0f;
		float fSlow60 = static_cast<float>(fHslider26) * static_cast<float>(fHslider25);
		float fSlow61 = fConst13 * fSlow60;
		int iSlow62 = fSlow56 >= 3.0f;
		int iSlow63 = fSlow56 >= 6.0f;
		int iSlow64 = fSlow56 >= 5.0f;
		float fSlow65 = fConst14 * (static_cast<float>(fHslider27) / fSlow60);
		int iSlow66 = static_cast<int>(fSlow65);
		int iSlow67 = std::min<int>(16385, std::max<int>(0, iSlow66 + 1));
		float fSlow68 = std::floor(fSlow65);
		float fSlow69 = fSlow65 - fSlow68;
		int iSlow70 = std::min<int>(16385, std::max<int>(0, iSlow66));
		float fSlow71 = fSlow68 + (1.0f - fSlow65);
		float fSlow72 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider28));
		float fSlow73 = static_cast<float>(fHslider29);
		float fSlow74 = fConst63 * fSlow73;
		float fSlow75 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider30));
		float fSlow76 = std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider31));
		float fSlow77 = fConst66 * fSlow76;
		float fSlow78 = fConst67 * fSlow76;
		float fSlow79 = 1.0f - fSlow73;
		float fSlow80 = 0.4f * static_cast<float>(fHslider32) + 1.0f;
		float fSlow81 = static_cast<float>(fHslider33);
		float fSlow82 = static_cast<float>(fHslider34);
		float fSlow83 = static_cast<float>(fHslider35);
		float fSlow84 = static_cast<float>(fHslider37) * static_cast<float>(fHslider36);
		float fSlow85 = fConst13 * fSlow84;
		float fSlow86 = 0.4f * static_cast<float>(fHslider38) + 1.0f;
		float fSlow87 = static_cast<float>(fHslider39);
		int iSlow88 = fSlow87 >= 4.0f;
		int iSlow89 = fSlow87 >= 2.0f;
		int iSlow90 = fSlow87 >= 1.0f;
		int iSlow91 = fSlow87 >= 3.0f;
		int iSlow92 = fSlow87 >= 6.0f;
		int iSlow93 = fSlow87 >= 5.0f;
		float fSlow94 = fConst14 * (static_cast<float>(fHslider40) / fSlow84);
		int iSlow95 = static_cast<int>(fSlow94);
		int iSlow96 = std::min<int>(16385, std::max<int>(0, iSlow95 + 1));
		float fSlow97 = std::floor(fSlow94);
		float fSlow98 = fSlow94 - fSlow97;
		int iSlow99 = std::min<int>(16385, std::max<int>(0, iSlow95));
		float fSlow100 = fSlow97 + (1.0f - fSlow94);
		float fSlow101 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider41));
		float fSlow102 = static_cast<float>(fHslider42);
		float fSlow103 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider44) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider43));
		float fSlow104 = static_cast<float>(fHslider45);
		float fSlow105 = static_cast<float>(fHslider46);
		float fSlow106 = fSlow105 * (fSlow104 - fSlow82);
		float fSlow107 = static_cast<float>(fHslider47);
		float fSlow108 = static_cast<float>(fHslider48);
		float fSlow109 = 1.8f * fSlow108;
		float fSlow110 = fConst44 * (1.0f - fSlow108);
		float fSlow111 = static_cast<float>(fHslider49);
		float fSlow112 = std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider50));
		float fSlow113 = std::max<float>(2.87e+03f * fSlow112, 23.44895f);
		float fSlow114 = std::max<float>(2e+01f, std::fabs(fSlow113));
		float fSlow115 = fConst18 * fSlow114;
		float fSlow116 = fConst90 / fSlow114;
		float fSlow117 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow113));
		int iSlow118 = static_cast<int>(fSlow117);
		float fSlow119 = std::floor(fSlow117);
		float fSlow120 = fSlow119 + (1.0f - fSlow117);
		float fSlow121 = std::max<float>(2369.5f * fSlow112, 23.44895f);
		float fSlow122 = std::max<float>(2e+01f, std::fabs(fSlow121));
		float fSlow123 = fConst18 * fSlow122;
		float fSlow124 = fConst90 / fSlow122;
		float fSlow125 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow121));
		int iSlow126 = static_cast<int>(fSlow125);
		float fSlow127 = std::floor(fSlow125);
		float fSlow128 = fSlow127 + (1.0f - fSlow125);
		float fSlow129 = std::max<float>(1900.5f * fSlow112, 23.44895f);
		float fSlow130 = std::max<float>(2e+01f, std::fabs(fSlow129));
		float fSlow131 = fConst18 * fSlow130;
		float fSlow132 = fConst90 / fSlow130;
		float fSlow133 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow129));
		int iSlow134 = static_cast<int>(fSlow133);
		float fSlow135 = std::floor(fSlow133);
		float fSlow136 = fSlow135 + (1.0f - fSlow133);
		float fSlow137 = std::max<float>(1456.0f * fSlow112, 23.44895f);
		float fSlow138 = std::max<float>(2e+01f, std::fabs(fSlow137));
		float fSlow139 = fConst18 * fSlow138;
		float fSlow140 = fConst90 / fSlow138;
		float fSlow141 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow137));
		int iSlow142 = static_cast<int>(fSlow141);
		float fSlow143 = std::floor(fSlow141);
		float fSlow144 = fSlow143 + (1.0f - fSlow141);
		float fSlow145 = std::max<float>(1043.0f * fSlow112, 23.44895f);
		float fSlow146 = std::max<float>(2e+01f, std::fabs(fSlow145));
		float fSlow147 = fConst18 * fSlow146;
		float fSlow148 = fConst90 / fSlow146;
		float fSlow149 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow145));
		int iSlow150 = static_cast<int>(fSlow149);
		float fSlow151 = std::floor(fSlow149);
		float fSlow152 = fSlow151 + (1.0f - fSlow149);
		float fSlow153 = std::max<float>(7e+02f * fSlow112, 23.44895f);
		float fSlow154 = std::max<float>(2e+01f, std::fabs(fSlow153));
		float fSlow155 = fConst18 * fSlow154;
		float fSlow156 = fConst90 / fSlow154;
		float fSlow157 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow153));
		int iSlow158 = static_cast<int>(fSlow157);
		int iSlow159 = iSlow158 + 1;
		float fSlow160 = std::floor(fSlow157);
		float fSlow161 = fSlow157 - fSlow160;
		float fSlow162 = fSlow160 + (1.0f - fSlow157);
		int iSlow163 = iSlow150 + 1;
		float fSlow164 = fSlow149 - fSlow151;
		int iSlow165 = iSlow142 + 1;
		float fSlow166 = fSlow141 - fSlow143;
		int iSlow167 = iSlow134 + 1;
		float fSlow168 = fSlow133 - fSlow135;
		int iSlow169 = iSlow126 + 1;
		float fSlow170 = fSlow125 - fSlow127;
		int iSlow171 = iSlow118 + 1;
		float fSlow172 = fSlow117 - fSlow119;
		float fSlow173 = 1.0f / fSlow114;
		float fSlow174 = 1.0f / fSlow122;
		float fSlow175 = 1.0f / fSlow130;
		float fSlow176 = 1.0f / fSlow138;
		float fSlow177 = 1.0f / fSlow146;
		float fSlow178 = 1.0f / fSlow154;
		float fSlow179 = 6.5f * static_cast<float>(fHslider51);
		float fSlow180 = static_cast<float>(fHslider53) * static_cast<float>(fHslider52);
		float fSlow181 = fConst13 * fSlow180;
		float fSlow182 = 0.4f * static_cast<float>(fHslider54) + 1.0f;
		float fSlow183 = static_cast<float>(fHslider55);
		int iSlow184 = fSlow183 >= 4.0f;
		int iSlow185 = fSlow183 >= 2.0f;
		int iSlow186 = fSlow183 >= 1.0f;
		int iSlow187 = fSlow183 >= 3.0f;
		int iSlow188 = fSlow183 >= 6.0f;
		int iSlow189 = fSlow183 >= 5.0f;
		float fSlow190 = fConst14 * (static_cast<float>(fHslider56) / fSlow180);
		int iSlow191 = static_cast<int>(fSlow190);
		int iSlow192 = std::min<int>(16385, std::max<int>(0, iSlow191 + 1));
		float fSlow193 = std::floor(fSlow190);
		float fSlow194 = fSlow190 - fSlow193;
		int iSlow195 = std::min<int>(16385, std::max<int>(0, iSlow191));
		float fSlow196 = fSlow193 + (1.0f - fSlow190);
		float fSlow197 = std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider57));
		float fSlow198 = 1.0f / fSlow197;
		float fSlow199 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider58));
		float fSlow200 = fConst91 * static_cast<float>(fHslider59);
		float fSlow201 = static_cast<float>(fHslider60);
		float fSlow202 = 0.5f * fSlow201;
		int iSlow203 = std::fabs(fSlow202) < 1.1920929e-07f;
		float fSlow204 = ((iSlow203) ? 0.0f : std::exp(-(fConst18 / ((iSlow203) ? 1.0f : fSlow202))));
		float fSlow205 = 1.0f - fSlow204;
		float fSlow206 = static_cast<float>(fHslider61);
		float fSlow207 = fConst18 * static_cast<float>(fHslider62);
		float fSlow208 = static_cast<float>(fHslider63);
		float fSlow209 = fConst13 * static_cast<float>(fHslider65) * static_cast<float>(fHslider64);
		float fSlow210 = 0.6f * static_cast<float>(fHslider66) + 1.0f;
		float fSlow211 = static_cast<float>(fHslider67);
		int iSlow212 = fSlow211 >= 4.0f;
		int iSlow213 = fSlow211 >= 2.0f;
		int iSlow214 = fSlow211 >= 1.0f;
		int iSlow215 = fSlow211 >= 3.0f;
		int iSlow216 = fSlow211 >= 6.0f;
		int iSlow217 = fSlow211 >= 5.0f;
		float fSlow218 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider68));
		float fSlow219 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider70) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider69));
		float fSlow220 = 0.5f * static_cast<float>(fHslider71);
		float fSlow221 = static_cast<float>(fHslider72);
		int iSlow222 = std::fabs(fSlow221) < 1.1920929e-07f;
		float fSlow223 = ((iSlow222) ? 0.0f : std::exp(-(fConst18 / ((iSlow222) ? 1.0f : fSlow221))));
		int iSlow224 = std::fabs(fSlow201) < 1.1920929e-07f;
		float fSlow225 = ((iSlow224) ? 0.0f : std::exp(-(fConst18 / ((iSlow224) ? 1.0f : fSlow201))));
		float fSlow226 = 1.0f / std::max<float>(1.1920929e-07f, static_cast<float>(fHslider73)) + -1.0f;
		float fSlow227 = static_cast<float>(fHslider74);
		float fSlow228 = 5e+03f * fSlow22;
		float fSlow229 = 1.0f / static_cast<float>(fHslider75);
		float fSlow230 = 85.0f * fSlow22;
		float fSlow231 = fSlow22 * fSlow23;
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
			int iTemp47 = static_cast<int>(fSlow31 * fTemp0) % 16;
			iVec8[0] = iTemp47;
			int iTemp48 = iTemp47 >= 8;
			int iTemp49 = iTemp47 >= 4;
			int iTemp50 = iTemp47 >= 2;
			int iTemp51 = iTemp47 >= 3;
			int iTemp52 = ((iTemp51) ? 0 : 1);
			int iTemp53 = iTemp47 >= 6;
			int iTemp54 = ((iTemp47 >= 7) ? 0 : 1);
			int iTemp55 = iTemp47 >= 12;
			int iTemp56 = iTemp47 >= 10;
			int iTemp57 = ((iTemp47 >= 11) ? 0 : 1);
			int iTemp58 = iTemp47 >= 14;
			int iTemp59 = iTemp47 >= 15;
			int iTemp60 = ((iTemp59) ? 0 : 1);
			int iTemp61 = iTemp47 >= 1;
			int iTemp62 = ((iTemp61) ? 1 : 0);
			int iTemp63 = iTemp47 >= 5;
			int iTemp64 = ((iTemp53) ? iTemp54 : ((iTemp63) ? 1 : 0));
			int iTemp65 = iTemp47 >= 9;
			int iTemp66 = ((iTemp56) ? iTemp57 : ((iTemp65) ? 1 : 0));
			int iTemp67 = iTemp47 >= 13;
			int iTemp68 = ((iTemp67) ? 1 : 0);
			int iTemp69 = ((iTemp61) ? 0 : 1);
			int iTemp70 = ((iTemp53) ? iTemp54 : ((iTemp63) ? 0 : 1));
			int iTemp71 = ((iTemp65) ? 0 : 1);
			int iTemp72 = ((iTemp67) ? 0 : 1);
			int iTemp73 = iTemp47 != iVec8[1];
			iVec9[IOTA0 & 32767] = iTemp73;
			int iTemp74 = static_cast<int>((((iTemp47 % 2) == 1) ? fSlow41 * static_cast<float>(iVec9[(IOTA0 - iSlow40) & 32767]) + fSlow39 * static_cast<float>(iVec9[(IOTA0 - iSlow37) & 32767]) : static_cast<float>(iTemp73))) & (((iSlow26) ? ((iSlow33) ? ((iTemp48) ? ((iTemp55) ? 1 : ((iTemp56) ? iTemp57 : 1)) : ((iTemp49) ? ((iTemp53) ? iTemp54 : 1) : ((iTemp50) ? iTemp52 : 1))) : ((iSlow34) ? ((iTemp48) ? ((iTemp55) ? ((iTemp58) ? 1 : iTemp68) : ((iTemp56) ? 1 : iTemp71)) : ((iTemp49) ? iTemp64 : ((iTemp50) ? 1 : iTemp69))) : ((iTemp48) ? ((iTemp55) ? ((iTemp58) ? ((iTemp59) ? 1 : 0) : iTemp72) : iTemp66) : ((iTemp49) ? iTemp70 : ((iTemp50) ? ((iTemp51) ? 1 : 0) : iTemp62))))) : ((iSlow27) ? ((iSlow32) ? ((iTemp48) ? ((iTemp55) ? ((iTemp58) ? iTemp60 : iTemp72) : ((iTemp56) ? iTemp57 : iTemp71)) : ((iTemp49) ? iTemp70 : ((iTemp50) ? iTemp52 : iTemp69))) : ((iTemp48) ? ((iTemp55) ? ((iTemp58) ? 1 : 0) : ((iTemp56) ? 1 : 0)) : ((iTemp49) ? ((iTemp53) ? 1 : 0) : ((iTemp50) ? 1 : 0)))) : ((iSlow28) ? ((iTemp48) ? ((iTemp55) ? ((iTemp58) ? iTemp60 : iTemp68) : iTemp66) : ((iTemp49) ? iTemp64 : ((iTemp50) ? iTemp52 : iTemp62))) : ((iTemp48) ? ((iTemp55) ? ((iTemp58) ? iTemp60 : 0) : ((iTemp56) ? iTemp57 : 0)) : ((iTemp49) ? ((iTemp53) ? iTemp54 : 0) : ((iTemp50) ? iTemp52 : 0)))))) > 0);
			iVec10[0] = iTemp74;
			fRec15[0] = (fConst18 + fRec15[1]) * (1.0f - static_cast<float>(iTemp74));
			fRec14[0] = fConst35 * std::exp(-(fSlow42 * fRec15[0])) + fConst34 * fRec14[1];
			iRec17[0] = (iRec17[1] + (iRec17[1] > 0)) * (iTemp74 <= iVec10[1]) + (iTemp74 > iVec10[1]);
			float fTemp75 = static_cast<float>(iRec17[0]);
			iRec19[0] = 1103515245 * iRec19[1] + 12345;
			float fTemp76 = static_cast<float>(iRec19[0]);
			fVec11[0] = fTemp76;
			fRec18[0] = fConst41 * (4.656613e-10f * (fTemp76 + fVec11[1]) - fConst40 * fRec18[1]);
			fRec21[0] = fConst43 + fRec21[1] * static_cast<float>(1 - iTemp74);
			float fTemp77 = std::max<float>(0.01f, 0.6f - 0.15f * (fSlow44 - fSlow52 * std::sin(6.2831855f * (fRec21[0] - std::floor(fRec21[0])))));
			fRec20[0] = fRec20[1] * (1.0f - fTemp77) + fTemp77 * (fSlow51 * fRec16[(IOTA0 - iSlow50) & 8191] + fSlow49 * fRec16[(IOTA0 - iSlow47) & 8191]);
			fRec16[IOTA0 & 8191] = fSlow54 * (fRec20[0] / (fSlow53 * std::fabs(fRec20[0]) + 1.0f)) + fRec18[0] * std::max<float>(0.0f, std::min<float>(fConst37 * fTemp75, fConst38 * (fConst36 - fTemp75) + 1.0f)) * (((((iTemp47 == 0) | (iTemp47 == 4)) | (iTemp47 == 8)) | (iTemp47 == 12)) ? fSlow43 : 1.0f);
			fRec13[0] = fRec16[IOTA0 & 8191] * fRec14[0] - fConst33 * (fConst31 * fRec13[2] + fConst29 * fRec13[1]);
			fRec12[0] = fConst44 * (fRec13[2] + (fRec13[0] - 2.0f * fRec13[1])) - fConst26 * (fConst25 * fRec12[2] + fConst23 * fRec12[1]);
			int iTemp78 = static_cast<int>(fSlow61 * fTemp0) % 16;
			iVec12[0] = iTemp78;
			int iTemp79 = iTemp78 >= 8;
			int iTemp80 = iTemp78 >= 4;
			int iTemp81 = iTemp78 >= 6;
			int iTemp82 = ((iTemp78 >= 5) ? 0 : 1);
			int iTemp83 = ((iTemp81) ? 0 : iTemp82);
			int iTemp84 = ((iTemp80) ? iTemp83 : 0);
			int iTemp85 = iTemp78 >= 12;
			int iTemp86 = iTemp78 >= 14;
			int iTemp87 = ((iTemp78 >= 13) ? 0 : 1);
			int iTemp88 = ((iTemp86) ? 0 : iTemp87);
			int iTemp89 = iTemp78 >= 10;
			int iTemp90 = iTemp78 >= 11;
			int iTemp91 = ((iTemp90) ? 0 : 1);
			int iTemp92 = ((iTemp89) ? iTemp91 : 0);
			int iTemp93 = iTemp78 >= 2;
			int iTemp94 = ((iTemp78 >= 3) ? 0 : 1);
			int iTemp95 = ((iTemp93) ? iTemp94 : 0);
			int iTemp96 = iTemp78 >= 9;
			int iTemp97 = ((iTemp96) ? 1 : 0);
			int iTemp98 = ((iTemp78 >= 7) ? 1 : 0);
			int iTemp99 = ((iTemp81) ? iTemp98 : iTemp82);
			int iTemp100 = iTemp78 >= 15;
			int iTemp101 = ((iTemp86) ? ((iTemp100) ? 0 : 1) : iTemp87);
			int iTemp102 = iTemp78 != iVec12[1];
			iVec13[IOTA0 & 32767] = iTemp102;
			int iTemp103 = static_cast<int>((((iTemp78 % 2) == 1) ? fSlow71 * static_cast<float>(iVec13[(IOTA0 - iSlow70) & 32767]) + fSlow69 * static_cast<float>(iVec13[(IOTA0 - iSlow67) & 32767]) : static_cast<float>(iTemp102))) & (((iSlow57) ? ((iSlow63) ? ((iTemp79) ? ((iTemp85) ? 1 : ((iTemp89) ? iTemp91 : ((iTemp96) ? 0 : 1))) : ((iTemp80) ? ((iTemp81) ? iTemp98 : 1) : ((iTemp93) ? iTemp94 : ((iTemp78 >= 1) ? 0 : 1)))) : ((iSlow64) ? ((iTemp79) ? ((iTemp85) ? iTemp101 : ((iTemp89) ? ((iTemp90) ? 1 : 0) : iTemp97)) : ((iTemp80) ? iTemp99 : ((iTemp93) ? 1 : 0))) : ((iTemp79) ? ((iTemp85) ? ((iTemp86) ? ((iTemp100) ? 1 : 0) : iTemp87) : iTemp92) : ((iTemp80) ? iTemp99 : iTemp95)))) : ((iSlow58) ? ((iSlow62) ? ((iTemp79) ? ((iTemp85) ? iTemp101 : 0) : ((iTemp80) ? iTemp99 : 0)) : ((iTemp79) ? ((iTemp85) ? iTemp88 : ((iTemp89) ? 0 : iTemp97)) : ((iTemp80) ? iTemp83 : iTemp95))) : ((iSlow59) ? ((iTemp79) ? ((iTemp85) ? iTemp88 : iTemp92) : iTemp84) : ((iTemp79) ? ((iTemp85) ? iTemp88 : 0) : iTemp84)))) > 0);
			iVec14[0] = iTemp103;
			iRec24[0] = (iRec24[1] + (iRec24[1] > 0)) * (iTemp103 <= iVec14[1]) + (iTemp103 > iVec14[1]);
			float fTemp104 = static_cast<float>(iRec24[0]);
			fRec25[0] = 4.656613e-10f * fTemp76 - fConst62 * (fConst60 * fRec25[2] + fConst58 * fRec25[1]);
			float fTemp105 = ((iTemp29) ? 0.0f : fSlow77 + fRec26[1]);
			fRec26[0] = fTemp105 - std::floor(fTemp105);
			float fTemp106 = ((iTemp29) ? 0.0f : fSlow78 + fRec27[1]);
			fRec27[0] = fTemp106 - std::floor(fTemp106);
			fRec23[0] = (((((iTemp78 == 0) | (iTemp78 == 4)) | (iTemp78 == 8)) | (iTemp78 == 12)) ? fSlow80 : 1.0f) * (fSlow79 * (0.65f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec27[0]), 65535))] + 0.35f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec26[0]), 65535))]) * std::max<float>(0.0f, std::min<float>(fConst65 * fTemp104, fSlow75 * (fConst64 - fTemp104) + 1.0f)) + fSlow74 * (fRec25[0] - fRec25[2]) * std::max<float>(0.0f, std::min<float>(fConst37 * fTemp104, fSlow72 * (fConst36 - fTemp104) + 1.0f))) - fConst56 * (fConst54 * fRec23[2] + fConst52 * fRec23[1]);
			fRec22[0] = fConst68 * (fRec23[2] + (fRec23[0] - 2.0f * fRec23[1])) - fConst49 * (fConst48 * fRec22[2] + fConst46 * fRec22[1]);
			int iTemp107 = static_cast<int>(fSlow85 * fTemp0) % 16;
			iVec15[0] = iTemp107;
			int iTemp108 = iTemp107 >= 8;
			int iTemp109 = iTemp107 >= 4;
			int iTemp110 = iTemp107 >= 2;
			int iTemp111 = ((iTemp107 >= 1) ? 0 : 1);
			int iTemp112 = ((iTemp110) ? 0 : iTemp111);
			int iTemp113 = iTemp107 >= 6;
			int iTemp114 = ((iTemp107 >= 5) ? 0 : 1);
			int iTemp115 = ((iTemp109) ? ((iTemp113) ? 0 : iTemp114) : iTemp112);
			int iTemp116 = iTemp107 >= 12;
			int iTemp117 = iTemp107 >= 10;
			int iTemp118 = ((iTemp107 >= 9) ? 0 : 1);
			int iTemp119 = ((iTemp117) ? 0 : iTemp118);
			int iTemp120 = iTemp107 >= 14;
			int iTemp121 = ((iTemp107 >= 13) ? 0 : 1);
			int iTemp122 = ((iTemp120) ? 0 : iTemp121);
			int iTemp123 = iTemp107 >= 15;
			int iTemp124 = ((iTemp116) ? ((iTemp120) ? ((iTemp123) ? 0 : 1) : iTemp121) : iTemp119);
			int iTemp125 = iTemp107 >= 7;
			int iTemp126 = ((iTemp113) ? ((iTemp125) ? 1 : 0) : iTemp114);
			int iTemp127 = ((iTemp109) ? iTemp126 : iTemp112);
			int iTemp128 = ((iTemp125) ? 0 : 1);
			int iTemp129 = iTemp107 >= 3;
			int iTemp130 = iTemp107 != iVec15[1];
			iVec16[IOTA0 & 32767] = iTemp130;
			int iTemp131 = static_cast<int>((((iTemp107 % 2) == 1) ? fSlow100 * static_cast<float>(iVec16[(IOTA0 - iSlow99) & 32767]) + fSlow98 * static_cast<float>(iVec16[(IOTA0 - iSlow96) & 32767]) : static_cast<float>(iTemp130))) & (((iSlow88) ? ((iSlow92) ? ((iTemp108) ? ((iTemp116) ? ((iTemp120) ? 0 : 1) : ((iTemp117) ? ((iTemp107 >= 11) ? 0 : 1) : iTemp118)) : ((iTemp109) ? iTemp126 : ((iTemp110) ? ((iTemp129) ? 0 : 1) : iTemp111))) : ((iSlow93) ? ((iTemp108) ? iTemp124 : iTemp127) : ((iTemp108) ? ((iTemp116) ? ((iTemp120) ? ((iTemp123) ? 1 : 0) : iTemp121) : iTemp119) : ((iTemp109) ? ((iTemp113) ? iTemp128 : 0) : ((iTemp110) ? ((iTemp129) ? 1 : 0) : iTemp111))))) : ((iSlow89) ? ((iSlow91) ? ((iTemp108) ? iTemp124 : ((iTemp109) ? ((iTemp113) ? iTemp128 : iTemp114) : iTemp112)) : ((iTemp108) ? ((iTemp116) ? iTemp122 : 0) : iTemp127)) : ((iSlow90) ? ((iTemp108) ? iTemp124 : iTemp115) : ((iTemp108) ? ((iTemp116) ? iTemp122 : iTemp119) : iTemp115)))) > 0);
			iVec17[0] = iTemp131;
			iRec42[0] = (iRec42[1] + (iRec42[1] > 0)) * (iTemp131 <= iVec17[1]) + (iTemp131 > iVec17[1]);
			float fTemp132 = static_cast<float>(iRec42[0]);
			float fTemp133 = fConst37 * fTemp132;
			float fTemp134 = fConst36 - fTemp132;
			float fTemp135 = ((iTemp29) ? 0.0f : fRec43[1] + fConst18 * (fSlow103 + fSlow102 * std::pow(std::max<float>(0.0f, std::min<float>(fTemp133, fConst16 * fTemp134 + 1.0f)), 1.5f)));
			fRec43[0] = fTemp135 - std::floor(fTemp135);
			float fTemp136 = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec43[0]), 65535))] * std::max<float>(0.0f, std::min<float>(fTemp133, fSlow101 * fTemp134 + 1.0f)) * (((((iTemp107 == 0) | (iTemp107 == 4)) | (iTemp107 == 8)) | (iTemp107 == 12)) ? fSlow86 : 1.0f);
			fRec41[0] = fConst80 * std::fabs(fTemp136) + fConst79 * fRec41[1];
			float fTemp137 = std::max<float>(0.0f, fRec41[0] - fSlow83);
			float fTemp138 = 1.0f / std::tan(fConst81 * std::max<float>(fSlow82, fSlow104 - fSlow106 * fTemp137));
			float fTemp139 = tanhf(fSlow107 * (fTemp136 / (fSlow105 * fTemp137 + 1.0f)));
			fVec18[0] = fTemp139;
			fRec40[0] = -((fRec40[1] * (1.0f - fTemp138) - (fTemp139 + fVec18[1])) / (fTemp138 + 1.0f));
			fRec39[0] = fRec40[0] - fConst78 * (fConst77 * fRec39[2] + fConst75 * fRec39[1]);
			fRec38[0] = fConst78 * (fRec39[2] + fRec39[0] + 2.0f * fRec39[1]) - fConst33 * (fConst31 * fRec38[2] + fConst29 * fRec38[1]);
			float fTemp140 = fRec38[2] + (fRec38[0] - 2.0f * fRec38[1]);
			fRec37[0] = fConst44 * fTemp140 - fConst12 * (fConst10 * fRec37[2] + fConst8 * fRec37[1]);
			fRec36[0] = fConst21 * (fRec37[2] + (fRec37[0] - 2.0f * fRec37[1])) - fConst73 * (fConst72 * fRec36[2] + fConst70 * fRec36[1]);
			float fTemp141 = fConst73 * (fRec36[2] + fRec36[0] + 2.0f * fRec36[1]);
			fRec44[0] = -(fConst83 * (fConst82 * fRec44[1] - (fRec35[(IOTA0 - 702) & 1023] + fRec35[(IOTA0 - 703) & 1023])));
			float fTemp142 = tanhf(fRec44[0]);
			fRec45[0] = -(fConst83 * (fConst82 * fRec45[1] - (fRec34[(IOTA0 - 594) & 1023] + fRec34[(IOTA0 - 595) & 1023])));
			float fTemp143 = tanhf(fRec45[0]);
			fRec46[0] = -(fConst83 * (fConst82 * fRec46[1] - (fRec33[(IOTA0 - 462) & 511] + fRec33[(IOTA0 - 463) & 511])));
			float fTemp144 = tanhf(fRec46[0]);
			fRec47[0] = -(fConst83 * (fConst82 * fRec47[1] - (fRec32[(IOTA0 - 348) & 511] + fRec32[(IOTA0 - 349) & 511])));
			float fTemp145 = tanhf(fRec47[0]);
			float fTemp146 = fTemp145 + fTemp144;
			fRec32[IOTA0 & 511] = 0.75f * (0.5f * (fTemp146 + fTemp143 + fTemp142) + fTemp141);
			fRec33[IOTA0 & 511] = 0.75f * (fTemp141 + 0.5f * (fTemp145 + fTemp143 - (fTemp144 + fTemp142)));
			fRec34[IOTA0 & 1023] = 0.75f * (fTemp141 + 0.5f * (fTemp146 - (fTemp143 + fTemp142)));
			fRec35[IOTA0 & 1023] = 0.75f * (fTemp141 + 0.5f * (fTemp145 + fTemp142 - (fTemp144 + fTemp143)));
			float fTemp147 = fRec32[IOTA0 & 511] + fRec33[IOTA0 & 511] + fRec34[IOTA0 & 1023] + fRec35[IOTA0 & 1023] - 0.5f * fRec30[1];
			fVec19[IOTA0 & 255] = fTemp147;
			fRec30[0] = fVec19[(IOTA0 - 130) & 255];
			float fRec31 = 0.5f * fTemp147;
			float fTemp148 = fRec31 + fRec30[1] - 0.5f * fRec28[1];
			fVec20[IOTA0 & 255] = fTemp148;
			fRec28[0] = fVec20[(IOTA0 - 190) & 255];
			float fRec29 = 0.5f * fTemp148;
			float fTemp149 = ((iTemp29) ? 0.0f : fSlow115 + fRec49[1]);
			fRec49[0] = fTemp149 - std::floor(fTemp149);
			float fTemp150 = mydsp_faustpower2_f(2.0f * fRec49[0] + -1.0f);
			fVec21[0] = fTemp150;
			float fTemp151 = fTemp150 - fVec21[1];
			float fTemp152 = fSlow116 * fTemp35 * fTemp151;
			fVec22[IOTA0 & 127] = fTemp152;
			float fTemp153 = ((iTemp29) ? 0.0f : fSlow123 + fRec50[1]);
			fRec50[0] = fTemp153 - std::floor(fTemp153);
			float fTemp154 = mydsp_faustpower2_f(2.0f * fRec50[0] + -1.0f);
			fVec23[0] = fTemp154;
			float fTemp155 = fTemp154 - fVec23[1];
			float fTemp156 = fSlow124 * fTemp35 * fTemp155;
			fVec24[IOTA0 & 127] = fTemp156;
			float fTemp157 = ((iTemp29) ? 0.0f : fSlow131 + fRec51[1]);
			fRec51[0] = fTemp157 - std::floor(fTemp157);
			float fTemp158 = mydsp_faustpower2_f(2.0f * fRec51[0] + -1.0f);
			fVec25[0] = fTemp158;
			float fTemp159 = fTemp158 - fVec25[1];
			float fTemp160 = fSlow132 * fTemp35 * fTemp159;
			fVec26[IOTA0 & 127] = fTemp160;
			float fTemp161 = ((iTemp29) ? 0.0f : fSlow139 + fRec52[1]);
			fRec52[0] = fTemp161 - std::floor(fTemp161);
			float fTemp162 = mydsp_faustpower2_f(2.0f * fRec52[0] + -1.0f);
			fVec27[0] = fTemp162;
			float fTemp163 = fTemp162 - fVec27[1];
			float fTemp164 = fSlow140 * fTemp35 * fTemp163;
			fVec28[IOTA0 & 255] = fTemp164;
			float fTemp165 = ((iTemp29) ? 0.0f : fSlow147 + fRec53[1]);
			fRec53[0] = fTemp165 - std::floor(fTemp165);
			float fTemp166 = mydsp_faustpower2_f(2.0f * fRec53[0] + -1.0f);
			fVec29[0] = fTemp166;
			float fTemp167 = fTemp166 - fVec29[1];
			float fTemp168 = fSlow148 * fTemp35 * fTemp167;
			fVec30[IOTA0 & 255] = fTemp168;
			float fTemp169 = ((iTemp29) ? 0.0f : fSlow155 + fRec54[1]);
			fRec54[0] = fTemp169 - std::floor(fTemp169);
			float fTemp170 = mydsp_faustpower2_f(2.0f * fRec54[0] + -1.0f);
			fVec31[0] = fTemp170;
			float fTemp171 = fTemp170 - fVec31[1];
			float fTemp172 = fSlow156 * fTemp35 * fTemp171;
			fVec32[IOTA0 & 511] = fTemp172;
			float fTemp173 = 0.15f * (fConst90 * fTemp35 * (fSlow178 * fTemp171 + fSlow177 * fTemp167 + fSlow176 * fTemp163 + fSlow175 * fTemp159 + fSlow174 * fTemp155 + fSlow173 * fTemp151) - (fSlow172 * fVec22[(IOTA0 - iSlow171) & 127] + fSlow170 * fVec24[(IOTA0 - iSlow169) & 127] + fSlow168 * fVec26[(IOTA0 - iSlow167) & 127] + fSlow166 * fVec28[(IOTA0 - iSlow165) & 255] + fSlow164 * fVec30[(IOTA0 - iSlow163) & 255] + fSlow162 * fVec32[(IOTA0 - iSlow158) & 511] + fSlow161 * fVec32[(IOTA0 - iSlow159) & 511] + fSlow152 * fVec30[(IOTA0 - iSlow150) & 255] + fSlow144 * fVec28[(IOTA0 - iSlow142) & 255] + fSlow136 * fVec26[(IOTA0 - iSlow134) & 127] + fSlow128 * fVec24[(IOTA0 - iSlow126) & 127] + fSlow120 * fVec22[(IOTA0 - iSlow118) & 127])) + 2.3283064e-10f * fTemp76;
			int iTemp174 = static_cast<int>(fSlow181 * fTemp0) % 16;
			iVec33[0] = iTemp174;
			int iTemp175 = iTemp174 >= 8;
			int iTemp176 = iTemp174 >= 4;
			int iTemp177 = iTemp174 >= 2;
			int iTemp178 = iTemp174 >= 3;
			int iTemp179 = ((iTemp178) ? 0 : 1);
			int iTemp180 = iTemp174 >= 6;
			int iTemp181 = iTemp174 >= 7;
			int iTemp182 = ((iTemp181) ? 0 : 1);
			int iTemp183 = iTemp174 >= 12;
			int iTemp184 = iTemp174 >= 10;
			int iTemp185 = iTemp174 >= 11;
			int iTemp186 = ((iTemp185) ? 0 : 1);
			int iTemp187 = iTemp174 >= 14;
			int iTemp188 = ((iTemp174 >= 15) ? 0 : 1);
			int iTemp189 = ((iTemp187) ? iTemp188 : 0);
			int iTemp190 = iTemp174 >= 1;
			int iTemp191 = iTemp174 >= 5;
			int iTemp192 = ((iTemp191) ? 1 : 0);
			int iTemp193 = ((iTemp180) ? iTemp182 : iTemp192);
			int iTemp194 = iTemp174 >= 9;
			int iTemp195 = ((iTemp187) ? iTemp188 : ((iTemp174 >= 13) ? 1 : 0));
			int iTemp196 = ((iTemp190) ? 0 : 1);
			int iTemp197 = ((iTemp181) ? 1 : 0);
			int iTemp198 = ((iTemp184) ? ((iTemp185) ? 1 : 0) : 1);
			int iTemp199 = iTemp174 != iVec33[1];
			iVec34[IOTA0 & 32767] = iTemp199;
			int iTemp200 = static_cast<int>((((iTemp174 % 2) == 1) ? fSlow196 * static_cast<float>(iVec34[(IOTA0 - iSlow195) & 32767]) + fSlow194 * static_cast<float>(iVec34[(IOTA0 - iSlow192) & 32767]) : static_cast<float>(iTemp199))) & (((iSlow184) ? ((iSlow188) ? ((iTemp175) ? 1 : ((iTemp176) ? ((iTemp180) ? 1 : ((iTemp191) ? 0 : 1)) : 1)) : ((iSlow189) ? ((iTemp175) ? ((iTemp183) ? 1 : iTemp198) : ((iTemp176) ? ((iTemp180) ? iTemp197 : 1) : ((iTemp177) ? ((iTemp178) ? 1 : 0) : 1))) : ((iTemp175) ? ((iTemp183) ? iTemp195 : iTemp198) : ((iTemp176) ? ((iTemp180) ? iTemp197 : iTemp192) : ((iTemp177) ? 1 : iTemp196))))) : ((iSlow185) ? ((iSlow187) ? 1 : ((iTemp175) ? ((iTemp183) ? iTemp189 : ((iTemp184) ? 1 : ((iTemp194) ? 0 : 1))) : ((iTemp176) ? iTemp193 : ((iTemp177) ? iTemp179 : iTemp196)))) : ((iSlow186) ? ((iTemp175) ? ((iTemp183) ? iTemp195 : ((iTemp184) ? iTemp186 : ((iTemp194) ? 1 : 0))) : ((iTemp176) ? iTemp193 : ((iTemp177) ? iTemp179 : ((iTemp190) ? 1 : 0)))) : ((iTemp175) ? ((iTemp183) ? iTemp189 : ((iTemp184) ? iTemp186 : 0)) : ((iTemp176) ? ((iTemp180) ? iTemp182 : 0) : ((iTemp177) ? iTemp179 : 0)))))) > 0);
			iVec35[0] = iTemp200;
			iRec55[0] = (iRec55[1] + (iRec55[1] > 0)) * (iTemp200 <= iVec35[1]) + (iTemp200 > iVec35[1]);
			float fTemp201 = static_cast<float>(iRec55[0]);
			fRec48[0] = fTemp173 * std::max<float>(0.0f, std::min<float>(fSlow198 * fTemp201, fSlow199 * (fSlow197 - fTemp201) + 1.0f)) * (((((iTemp174 == 0) | (iTemp174 == 4)) | (iTemp174 == 8)) | (iTemp174 == 12)) ? fSlow182 : 1.0f) / (fSlow179 * std::fabs(fTemp173) + 1.0f) - fConst89 * (fConst88 * fRec48[2] + fConst86 * fRec48[1]);
			float fTemp202 = ((iTemp29) ? 0.0f : fSlow207 + fRec60[1]);
			fRec60[0] = fTemp202 - std::floor(fTemp202);
			float fTemp203 = ((iTemp29) ? 0.0f : fSlow209 + fRec67[1]);
			fRec67[0] = fTemp203 - std::floor(fTemp203);
			int iTemp204 = (fRec67[0] - fRec67[1]) < 0.0f;
			iVec36[0] = iTemp204;
			int iTemp205 = (static_cast<float>(iTemp204) > 0.0f) & (static_cast<float>(iVec36[1]) <= 0.0f);
			iRec66[0] = (iTemp205 + iRec66[1]) % 16;
			int iTemp206 = iRec66[0] >= 8;
			int iTemp207 = iRec66[0] >= 4;
			int iTemp208 = iRec66[0] >= 2;
			int iTemp209 = iRec66[0] >= 1;
			int iTemp210 = ((iTemp209) ? 0 : 1);
			int iTemp211 = iRec66[0] >= 12;
			int iTemp212 = iRec66[0] >= 14;
			int iTemp213 = iRec66[0] >= 13;
			int iTemp214 = ((iTemp213) ? 0 : 1);
			int iTemp215 = ((iTemp212) ? 0 : iTemp214);
			int iTemp216 = iRec66[0] >= 3;
			int iTemp217 = iRec66[0] >= 6;
			int iTemp218 = iRec66[0] >= 7;
			int iTemp219 = iRec66[0] >= 10;
			int iTemp220 = iRec66[0] >= 9;
			int iTemp221 = ((iTemp220) ? 1 : 0);
			int iTemp222 = ((iTemp219) ? 0 : iTemp221);
			int iTemp223 = ((iTemp209) ? 1 : 0);
			int iTemp224 = iRec66[0] >= 5;
			int iTemp225 = ((iTemp218) ? 1 : 0);
			int iTemp226 = ((iRec66[0] >= 15) ? 0 : 1);
			int iTemp227 = ((iTemp224) ? 1 : 0);
			int iTemp228 = ((iTemp213) ? 1 : 0);
			int iTemp229 = iTemp205 & (iTemp205 & (((iSlow212) ? ((iSlow216) ? ((iTemp206) ? ((iTemp211) ? ((iTemp212) ? 1 : 0) : 1) : ((iTemp207) ? ((iTemp217) ? 1 : 0) : 1)) : ((iSlow217) ? ((iTemp206) ? ((iTemp211) ? ((iTemp212) ? 1 : iTemp228) : ((iTemp219) ? 1 : iTemp221)) : ((iTemp207) ? ((iTemp217) ? 1 : iTemp227) : ((iTemp208) ? 1 : iTemp223))) : ((iTemp206) ? ((iTemp211) ? ((iTemp212) ? iTemp226 : iTemp228) : ((iTemp219) ? ((iRec66[0] >= 11) ? 1 : 0) : ((iTemp220) ? 0 : 1))) : ((iTemp207) ? ((iTemp217) ? iTemp225 : iTemp227) : ((iTemp208) ? ((iTemp216) ? 0 : 1) : iTemp210))))) : ((iSlow213) ? ((iSlow215) ? ((iTemp206) ? ((iTemp211) ? ((iTemp212) ? iTemp226 : iTemp214) : iTemp222) : ((iTemp207) ? ((iTemp217) ? iTemp225 : ((iTemp224) ? 0 : 1)) : ((iTemp208) ? 0 : iTemp223))) : ((iTemp206) ? ((iTemp211) ? iTemp215 : iTemp222) : ((iTemp207) ? ((iTemp217) ? ((iTemp218) ? 0 : 1) : 0) : ((iTemp208) ? ((iTemp216) ? 1 : 0) : 0)))) : ((iSlow214) ? ((iTemp206) ? ((iTemp211) ? iTemp215 : 0) : 0) : ((iTemp206) ? 0 : ((iTemp207) ? 0 : ((iTemp208) ? 0 : iTemp210)))))) > 0));
			iVec37[0] = iTemp229;
			iRec68[0] = (iRec68[1] + (iRec68[1] > 0)) * (iTemp229 <= iVec37[1]) + (iTemp229 > iVec37[1]);
			float fTemp230 = static_cast<float>(iRec68[0]);
			float fTemp231 = std::max<float>(0.0f, std::min<float>(fConst16 * fTemp230, fSlow218 * (fConst15 - fTemp230) + 1.0f)) * (((((iRec66[0] == 0) | (iRec66[0] == 4)) | (iRec66[0] == 8)) | (iRec66[0] == 12)) ? fSlow210 : 1.0f);
			float fTemp232 = ((iTemp29) ? 0.0f : fRec65[1] + fConst18 * (fSlow219 + 1.5e+03f * fTemp231));
			fRec65[0] = fTemp232 - std::floor(fTemp232);
			float fTemp233 = fTemp231 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec65[0]), 65535))];
			fRec69[0] = -(fConst101 * (fConst100 * fRec69[1] - (fRec62[(IOTA0 - 1400) & 2047] + fRec62[(IOTA0 - 1401) & 2047])));
			fRec70[0] = -(fConst101 * (fConst100 * fRec70[1] - (fRec61[(IOTA0 - 1118) & 2047] + fRec61[(IOTA0 - 1119) & 2047])));
			float fTemp234 = fRec70[0] + fRec69[0];
			fRec71[0] = -(fConst101 * (fConst100 * fRec71[1] - (fRec63[(IOTA0 - 1724) & 2047] + fRec63[(IOTA0 - 1725) & 2047])));
			fRec72[0] = -(fConst101 * (fConst100 * fRec72[1] - (fRec64[(IOTA0 - 2090) & 4095] + fRec64[(IOTA0 - 2091) & 4095])));
			fRec61[IOTA0 & 2047] = fSlow220 * (fRec72[0] + fRec71[0] + fTemp234) + fTemp233;
			float fTemp235 = fRec70[0] - fRec69[0];
			fRec62[IOTA0 & 2047] = fTemp233 - fSlow220 * (fRec72[0] - (fRec71[0] + fTemp235));
			fRec63[IOTA0 & 2047] = fTemp233 - fSlow220 * (fRec72[0] - (fTemp234 - fRec71[0]));
			fRec64[IOTA0 & 4095] = fTemp233 + fSlow220 * (fRec72[0] - (fRec71[0] - fTemp235));
			float fTemp236 = (fRec61[IOTA0 & 2047] + fRec62[IOTA0 & 2047] + fRec63[IOTA0 & 2047] + fRec64[IOTA0 & 4095]) * (fSlow208 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec60[0]), 65535))] + 1.0f);
			float fTemp237 = std::fabs(0.25f * fTemp236);
			float fTemp238 = ((fTemp237 > fRec59[1]) ? fSlow225 : fSlow223);
			fRec59[0] = fTemp237 * (1.0f - fTemp238) + fRec59[1] * fTemp238;
			fRec58[0] = fSlow226 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec59[0])) - fSlow206, 0.0f) * fSlow205 + fSlow204 * fRec58[1];
			fRec57[0] = 0.25f * fTemp236 * std::pow(1e+01f, 0.05f * fRec58[0]) - fConst98 * (fConst96 * fRec57[2] + fConst94 * fRec57[1]);
			fRec56[0] = fConst102 * (fRec57[2] + (fRec57[0] - 2.0f * fRec57[1])) - fConst89 * (fConst88 * fRec56[2] + fConst86 * fRec56[1]);
			float fTemp239 = fConst89 * (fSlow227 * (fRec56[2] + fRec56[0] + 2.0f * fRec56[1]) + fSlow200 * (fRec48[2] + (fRec48[0] - 2.0f * fRec48[1]))) + fSlow111 * (fSlow110 * fTemp140 + fSlow109 * (fRec29 + fRec28[1])) + fSlow81 * tanhf(fConst49 * (fRec22[2] + fRec22[0] + 2.0f * fRec22[1])) + fSlow55 * (fRec12[2] + fRec12[0] + 2.0f * fRec12[1]);
			float fTemp240 = tanhf(1.5f * (fTemp239 + fSlow24 * std::sqrt(1.0f - fRec11[0]) * fTemp45));
			fVec38[0] = fTemp240;
			fRec0[0] = 0.995f * fRec0[1] + fTemp240 - fVec38[1];
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0]);
			float fTemp241 = std::sin(3.1415927f * fRec11[0]);
			float fTemp242 = std::tan(fConst81 * (fSlow228 * fTemp241 + 4e+02f));
			float fTemp243 = 1.0f / fTemp242;
			float fTemp244 = (fSlow229 + fTemp243) / fTemp242 + 1.0f;
			float fTemp245 = fSlow230 * fTemp241;
			float fTemp246 = fTemp245 + 1e+02f;
			int iTemp247 = static_cast<int>(fTemp246);
			float fTemp248 = std::floor(fTemp246);
			fRec74[0] = fConst5 * (fVec7[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp247))) & 255] * (fTemp248 + (-99.0f - fTemp245)) + (fTemp245 + (1e+02f - fTemp248)) * fVec7[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp247 + 1))) & 255]) - (fRec74[2] * ((fTemp243 - fSlow229) / fTemp242 + 1.0f) + 2.0f * fRec74[1] * (1.0f - 1.0f / mydsp_faustpower2_f(fTemp242))) / fTemp244;
			float fTemp249 = tanhf(1.5f * (fTemp239 + fSlow231 * (std::sqrt(fRec11[0]) * (fRec74[0] - fRec74[2]) / (fTemp242 * fTemp244))));
			fVec39[0] = fTemp249;
			fRec73[0] = 0.995f * fRec73[1] + fTemp249 - fVec39[1];
			output1[i0] = static_cast<FAUSTFLOAT>(fRec73[0]);
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
			iVec8[1] = iVec8[0];
			iVec10[1] = iVec10[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			iRec17[1] = iRec17[0];
			iRec19[1] = iRec19[0];
			fVec11[1] = fVec11[0];
			fRec18[1] = fRec18[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			iVec12[1] = iVec12[0];
			iVec14[1] = iVec14[0];
			iRec24[1] = iRec24[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			iVec15[1] = iVec15[0];
			iVec17[1] = iVec17[0];
			iRec42[1] = iRec42[0];
			fRec43[1] = fRec43[0];
			fRec41[1] = fRec41[0];
			fVec18[1] = fVec18[0];
			fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec46[1] = fRec46[0];
			fRec47[1] = fRec47[0];
			fRec30[1] = fRec30[0];
			fRec28[1] = fRec28[0];
			fRec49[1] = fRec49[0];
			fVec21[1] = fVec21[0];
			fRec50[1] = fRec50[0];
			fVec23[1] = fVec23[0];
			fRec51[1] = fRec51[0];
			fVec25[1] = fVec25[0];
			fRec52[1] = fRec52[0];
			fVec27[1] = fVec27[0];
			fRec53[1] = fRec53[0];
			fVec29[1] = fVec29[0];
			fRec54[1] = fRec54[0];
			fVec31[1] = fVec31[0];
			iVec33[1] = iVec33[0];
			iVec35[1] = iVec35[0];
			iRec55[1] = iRec55[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec60[1] = fRec60[0];
			fRec67[1] = fRec67[0];
			iVec36[1] = iVec36[0];
			iRec66[1] = iRec66[0];
			iVec37[1] = iVec37[0];
			iRec68[1] = iRec68[0];
			fRec65[1] = fRec65[0];
			fRec69[1] = fRec69[0];
			fRec70[1] = fRec70[0];
			fRec71[1] = fRec71[0];
			fRec72[1] = fRec72[0];
			fRec59[1] = fRec59[0];
			fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fVec38[1] = fVec38[0];
			fRec0[1] = fRec0[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fVec39[1] = fVec39[0];
			fRec73[1] = fRec73[0];
		}
	}

};

#endif
