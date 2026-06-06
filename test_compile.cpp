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
	
	int iVec5[2];
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
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iVec5[l7] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			iRec5[l8] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec5[0] = 1;
			iRec5[0] = (iVec5[1] + iRec5[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec5[0]));
			iVec5[1] = iVec5[0];
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
	FAUSTFLOAT fHslider0;
	float fVec1[2];
	int iRec3[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fConst13;
	int iVec2[2];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fHslider4;
	int IOTA0;
	int iVec3[32768];
	FAUSTFLOAT fHslider5;
	float fConst14;
	int iVec4[2];
	int iRec4[2];
	float fConst15;
	float fConst16;
	FAUSTFLOAT fHslider6;
	float fConst17;
	float fRec6[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fConst18;
	float fRec7[2];
	float fVec6[2];
	float fVec7[2048];
	float fConst19;
	float fConst20;
	float fRec10[2];
	FAUSTFLOAT fHslider9;
	float fRec8[2];
	float fRec2[3];
	float fConst21;
	float fRec1[3];
	float fVec8[256];
	FAUSTFLOAT fHslider10;
	float fRec11[2];
	FAUSTFLOAT fHslider11;
	FAUSTFLOAT fHslider12;
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
	FAUSTFLOAT fHslider13;
	FAUSTFLOAT fHslider14;
	FAUSTFLOAT fHslider15;
	float fRec16[2];
	FAUSTFLOAT fHslider16;
	FAUSTFLOAT fHslider17;
	float fVec9[2];
	int iRec22[2];
	FAUSTFLOAT fHslider18;
	FAUSTFLOAT fHslider19;
	int iVec10[2];
	FAUSTFLOAT fHslider20;
	FAUSTFLOAT fHslider21;
	int iVec11[32768];
	FAUSTFLOAT fHslider22;
	int iVec12[2];
	int iRec23[2];
	FAUSTFLOAT fHslider23;
	FAUSTFLOAT fHslider24;
	FAUSTFLOAT fHslider25;
	float fRec21[2];
	float fConst34;
	float fConst35;
	float fConst36;
	float fRec24[2];
	float fRec25[2];
	float fRec26[2];
	float fRec27[2];
	FAUSTFLOAT fHslider26;
	float fRec17[2048];
	float fRec18[2048];
	float fRec19[2048];
	float fRec20[4096];
	FAUSTFLOAT fHslider27;
	float fRec15[2];
	FAUSTFLOAT fHslider28;
	float fRec14[2];
	float fRec13[3];
	float fConst37;
	float fRec12[3];
	FAUSTFLOAT fHslider29;
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
	FAUSTFLOAT fHslider30;
	FAUSTFLOAT fHslider31;
	float fVec13[2];
	int iRec32[2];
	FAUSTFLOAT fHslider32;
	FAUSTFLOAT fHslider33;
	int iVec14[2];
	int iVec15[32768];
	FAUSTFLOAT fHslider34;
	int iVec16[2];
	float fRec31[2];
	FAUSTFLOAT fHslider35;
	float fConst51;
	float fRec30[2];
	FAUSTFLOAT fHslider36;
	int iRec34[2];
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	int iRec36[2];
	float fVec17[2];
	float fConst57;
	float fRec35[2];
	FAUSTFLOAT fHslider37;
	FAUSTFLOAT fHslider38;
	FAUSTFLOAT fHslider39;
	float fConst58;
	float fConst59;
	float fRec38[2];
	FAUSTFLOAT fHslider40;
	float fRec37[2];
	FAUSTFLOAT fHslider41;
	float fRec33[8192];
	float fRec29[3];
	float fConst60;
	float fRec28[3];
	FAUSTFLOAT fHslider42;
	FAUSTFLOAT fHslider43;
	float fConst61;
	FAUSTFLOAT fHslider44;
	FAUSTFLOAT fHslider45;
	FAUSTFLOAT fHslider46;
	float fRec40[2];
	float fVec18[2];
	float fConst62;
	float fVec19[128];
	float fRec41[2];
	float fVec20[2];
	float fVec21[128];
	float fRec42[2];
	float fVec22[2];
	float fVec23[128];
	float fRec43[2];
	float fVec24[2];
	float fVec25[256];
	float fRec44[2];
	float fVec26[2];
	float fVec27[256];
	float fRec45[2];
	float fVec28[2];
	float fVec29[512];
	FAUSTFLOAT fHslider47;
	FAUSTFLOAT fHslider48;
	float fVec30[2];
	int iRec46[2];
	FAUSTFLOAT fHslider49;
	FAUSTFLOAT fHslider50;
	int iVec31[2];
	FAUSTFLOAT fHslider51;
	FAUSTFLOAT fHslider52;
	int iVec32[32768];
	FAUSTFLOAT fHslider53;
	int iVec33[2];
	int iRec47[2];
	FAUSTFLOAT fHslider54;
	FAUSTFLOAT fHslider55;
	float fRec39[3];
	FAUSTFLOAT fHslider56;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	FAUSTFLOAT fHslider57;
	FAUSTFLOAT fHslider58;
	FAUSTFLOAT fHslider59;
	float fVec34[2];
	int iRec51[2];
	FAUSTFLOAT fHslider60;
	FAUSTFLOAT fHslider61;
	int iVec35[2];
	int iVec36[32768];
	FAUSTFLOAT fHslider62;
	int iVec37[2];
	int iRec50[2];
	FAUSTFLOAT fHslider63;
	FAUSTFLOAT fHslider64;
	FAUSTFLOAT fHslider65;
	float fRec52[3];
	FAUSTFLOAT fHslider66;
	float fConst68;
	float fConst69;
	FAUSTFLOAT fHslider67;
	FAUSTFLOAT fHslider68;
	FAUSTFLOAT fHslider69;
	float fConst70;
	float fRec53[2];
	float fConst71;
	float fRec54[2];
	FAUSTFLOAT fHslider70;
	FAUSTFLOAT fHslider71;
	float fRec49[3];
	float fRec48[3];
	FAUSTFLOAT fHslider72;
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
	FAUSTFLOAT fHslider73;
	FAUSTFLOAT fHslider74;
	float fConst82;
	FAUSTFLOAT fHslider75;
	float fVec38[2];
	int iRec69[2];
	FAUSTFLOAT fHslider76;
	FAUSTFLOAT fHslider77;
	int iVec39[2];
	FAUSTFLOAT fHslider78;
	FAUSTFLOAT fHslider79;
	int iVec40[32768];
	FAUSTFLOAT fHslider80;
	int iVec41[2];
	int iRec70[2];
	FAUSTFLOAT fHslider81;
	FAUSTFLOAT fHslider82;
	FAUSTFLOAT fHslider83;
	FAUSTFLOAT fHslider84;
	float fRec71[2];
	float fConst83;
	float fRec68[2];
	FAUSTFLOAT fHslider85;
	FAUSTFLOAT fHslider86;
	FAUSTFLOAT fHslider87;
	float fVec42[2];
	float fRec67[2];
	float fRec66[3];
	float fRec65[3];
	float fRec64[3];
	float fRec63[3];
	float fConst84;
	float fConst85;
	float fRec72[2];
	float fRec73[2];
	float fRec74[2];
	float fRec75[2];
	float fRec59[512];
	float fRec60[512];
	float fRec61[1024];
	float fRec62[1024];
	float fVec43[256];
	float fRec57[2];
	float fVec44[256];
	float fRec55[2];
	FAUSTFLOAT fHslider88;
	FAUSTFLOAT fHslider89;
	float fVec45[2];
	float fRec0[2];
	FAUSTFLOAT fHslider90;
	float fRec77[3];
	float fVec46[2];
	float fRec76[2];
	
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
		fHslider0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider2 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider4 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider5 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider6 = static_cast<FAUSTFLOAT>(0.2f);
		fHslider7 = static_cast<FAUSTFLOAT>(12.0f);
		fHslider8 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider9 = static_cast<FAUSTFLOAT>(5.0f);
		fHslider10 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider11 = static_cast<FAUSTFLOAT>(0.7f);
		fHslider12 = static_cast<FAUSTFLOAT>(0.85f);
		fHslider13 = static_cast<FAUSTFLOAT>(0.005f);
		fHslider14 = static_cast<FAUSTFLOAT>(-2e+01f);
		fHslider15 = static_cast<FAUSTFLOAT>(2.0f);
		fHslider16 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider17 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider18 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider19 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider20 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider21 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider22 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider23 = static_cast<FAUSTFLOAT>(0.2f);
		fHslider24 = static_cast<FAUSTFLOAT>(12.0f);
		fHslider25 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider26 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider27 = static_cast<FAUSTFLOAT>(0.1f);
		fHslider28 = static_cast<FAUSTFLOAT>(6.0f);
		fHslider29 = static_cast<FAUSTFLOAT>(0.22f);
		fHslider30 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider31 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider32 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider33 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider34 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider35 = static_cast<FAUSTFLOAT>(0.35f);
		fHslider36 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider37 = static_cast<FAUSTFLOAT>(-12.0f);
		fHslider38 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider39 = static_cast<FAUSTFLOAT>(0.04f);
		fHslider40 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider41 = static_cast<FAUSTFLOAT>(0.65f);
		fHslider42 = static_cast<FAUSTFLOAT>(0.55f);
		fHslider43 = static_cast<FAUSTFLOAT>(6.5e+03f);
		fHslider44 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider45 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider46 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider47 = static_cast<FAUSTFLOAT>(0.35f);
		fHslider48 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider49 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider50 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider51 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider52 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider53 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider54 = static_cast<FAUSTFLOAT>(0.001f);
		fHslider55 = static_cast<FAUSTFLOAT>(0.04f);
		fHslider56 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider57 = static_cast<FAUSTFLOAT>(1.6e+02f);
		fHslider58 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider59 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider60 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider61 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider62 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider63 = static_cast<FAUSTFLOAT>(0.16f);
		fHslider64 = static_cast<FAUSTFLOAT>(1.65e+03f);
		fHslider65 = static_cast<FAUSTFLOAT>(2.5f);
		fHslider66 = static_cast<FAUSTFLOAT>(0.55f);
		fHslider67 = static_cast<FAUSTFLOAT>(0.07f);
		fHslider68 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider69 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider70 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider71 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider72 = static_cast<FAUSTFLOAT>(0.65f);
		fHslider73 = static_cast<FAUSTFLOAT>(7.5e+02f);
		fHslider74 = static_cast<FAUSTFLOAT>(0.4f);
		fHslider75 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider76 = static_cast<FAUSTFLOAT>(1.4e+02f);
		fHslider77 = static_cast<FAUSTFLOAT>(1.0f);
		fHslider78 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider79 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider80 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider81 = static_cast<FAUSTFLOAT>(0.18f);
		fHslider82 = static_cast<FAUSTFLOAT>(1.5e+02f);
		fHslider83 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider84 = static_cast<FAUSTFLOAT>(36.0f);
		fHslider85 = static_cast<FAUSTFLOAT>(2.5e+03f);
		fHslider86 = static_cast<FAUSTFLOAT>(8.0f);
		fHslider87 = static_cast<FAUSTFLOAT>(3.5f);
		fHslider88 = static_cast<FAUSTFLOAT>(0.45f);
		fHslider89 = static_cast<FAUSTFLOAT>(0.85f);
		fHslider90 = static_cast<FAUSTFLOAT>(4.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fVec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec3[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iVec2[l3] = 0;
		}
		IOTA0 = 0;
		for (int l4 = 0; l4 < 32768; l4 = l4 + 1) {
			iVec3[l4] = 0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iVec4[l5] = 0;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iRec4[l6] = 0;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec6[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec7[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fVec6[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2048; l12 = l12 + 1) {
			fVec7[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec10[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec8[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec2[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 3; l16 = l16 + 1) {
			fRec1[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 256; l17 = l17 + 1) {
			fVec8[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec11[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec16[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fVec9[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			iRec22[l21] = 0;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			iVec10[l22] = 0;
		}
		for (int l23 = 0; l23 < 32768; l23 = l23 + 1) {
			iVec11[l23] = 0;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			iVec12[l24] = 0;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			iRec23[l25] = 0;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec21[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec24[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec25[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec26[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec27[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2048; l31 = l31 + 1) {
			fRec17[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2048; l32 = l32 + 1) {
			fRec18[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2048; l33 = l33 + 1) {
			fRec19[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 4096; l34 = l34 + 1) {
			fRec20[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec15[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fRec14[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec13[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec12[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fVec13[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			iRec32[l40] = 0;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			iVec14[l41] = 0;
		}
		for (int l42 = 0; l42 < 32768; l42 = l42 + 1) {
			iVec15[l42] = 0;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			iVec16[l43] = 0;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fRec31[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec30[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			iRec34[l46] = 0;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			iRec36[l47] = 0;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fVec17[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec35[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fRec38[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec37[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 8192; l52 = l52 + 1) {
			fRec33[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 3; l53 = l53 + 1) {
			fRec29[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec28[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec40[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2; l56 = l56 + 1) {
			fVec18[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 128; l57 = l57 + 1) {
			fVec19[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec41[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fVec20[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 128; l60 = l60 + 1) {
			fVec21[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec42[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fVec22[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 128; l63 = l63 + 1) {
			fVec23[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fRec43[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fVec24[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 256; l66 = l66 + 1) {
			fVec25[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 2; l67 = l67 + 1) {
			fRec44[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fVec26[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 256; l69 = l69 + 1) {
			fVec27[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fRec45[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 2; l71 = l71 + 1) {
			fVec28[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 512; l72 = l72 + 1) {
			fVec29[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 2; l73 = l73 + 1) {
			fVec30[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 2; l74 = l74 + 1) {
			iRec46[l74] = 0;
		}
		for (int l75 = 0; l75 < 2; l75 = l75 + 1) {
			iVec31[l75] = 0;
		}
		for (int l76 = 0; l76 < 32768; l76 = l76 + 1) {
			iVec32[l76] = 0;
		}
		for (int l77 = 0; l77 < 2; l77 = l77 + 1) {
			iVec33[l77] = 0;
		}
		for (int l78 = 0; l78 < 2; l78 = l78 + 1) {
			iRec47[l78] = 0;
		}
		for (int l79 = 0; l79 < 3; l79 = l79 + 1) {
			fRec39[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 2; l80 = l80 + 1) {
			fVec34[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 2; l81 = l81 + 1) {
			iRec51[l81] = 0;
		}
		for (int l82 = 0; l82 < 2; l82 = l82 + 1) {
			iVec35[l82] = 0;
		}
		for (int l83 = 0; l83 < 32768; l83 = l83 + 1) {
			iVec36[l83] = 0;
		}
		for (int l84 = 0; l84 < 2; l84 = l84 + 1) {
			iVec37[l84] = 0;
		}
		for (int l85 = 0; l85 < 2; l85 = l85 + 1) {
			iRec50[l85] = 0;
		}
		for (int l86 = 0; l86 < 3; l86 = l86 + 1) {
			fRec52[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 2; l87 = l87 + 1) {
			fRec53[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 2; l88 = l88 + 1) {
			fRec54[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 3; l89 = l89 + 1) {
			fRec49[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 3; l90 = l90 + 1) {
			fRec48[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 2; l91 = l91 + 1) {
			fVec38[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 2; l92 = l92 + 1) {
			iRec69[l92] = 0;
		}
		for (int l93 = 0; l93 < 2; l93 = l93 + 1) {
			iVec39[l93] = 0;
		}
		for (int l94 = 0; l94 < 32768; l94 = l94 + 1) {
			iVec40[l94] = 0;
		}
		for (int l95 = 0; l95 < 2; l95 = l95 + 1) {
			iVec41[l95] = 0;
		}
		for (int l96 = 0; l96 < 2; l96 = l96 + 1) {
			iRec70[l96] = 0;
		}
		for (int l97 = 0; l97 < 2; l97 = l97 + 1) {
			fRec71[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 2; l98 = l98 + 1) {
			fRec68[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 2; l99 = l99 + 1) {
			fVec42[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 2; l100 = l100 + 1) {
			fRec67[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 3; l101 = l101 + 1) {
			fRec66[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 3; l102 = l102 + 1) {
			fRec65[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 3; l103 = l103 + 1) {
			fRec64[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 3; l104 = l104 + 1) {
			fRec63[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 2; l105 = l105 + 1) {
			fRec72[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 2; l106 = l106 + 1) {
			fRec73[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 2; l107 = l107 + 1) {
			fRec74[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 2; l108 = l108 + 1) {
			fRec75[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 512; l109 = l109 + 1) {
			fRec59[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 512; l110 = l110 + 1) {
			fRec60[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 1024; l111 = l111 + 1) {
			fRec61[l111] = 0.0f;
		}
		for (int l112 = 0; l112 < 1024; l112 = l112 + 1) {
			fRec62[l112] = 0.0f;
		}
		for (int l113 = 0; l113 < 256; l113 = l113 + 1) {
			fVec43[l113] = 0.0f;
		}
		for (int l114 = 0; l114 < 2; l114 = l114 + 1) {
			fRec57[l114] = 0.0f;
		}
		for (int l115 = 0; l115 < 256; l115 = l115 + 1) {
			fVec44[l115] = 0.0f;
		}
		for (int l116 = 0; l116 < 2; l116 = l116 + 1) {
			fRec55[l116] = 0.0f;
		}
		for (int l117 = 0; l117 < 2; l117 = l117 + 1) {
			fVec45[l117] = 0.0f;
		}
		for (int l118 = 0; l118 < 2; l118 = l118 + 1) {
			fRec0[l118] = 0.0f;
		}
		for (int l119 = 0; l119 < 3; l119 = l119 + 1) {
			fRec77[l119] = 0.0f;
		}
		for (int l120 = 0; l120 < 2; l120 = l120 + 1) {
			fVec46[l120] = 0.0f;
		}
		for (int l121 = 0; l121 < 2; l121 = l121 + 1) {
			fRec76[l121] = 0.0f;
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
		ui_interface->declare(&fHslider76, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider76, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider75, "osc", "/master/sync_reset");
		ui_interface->addHorizontalSlider("Sync_Reset", &fHslider75, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+07f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider78, "1", "");
		ui_interface->declare(&fHslider78, "osc", "/kick/accent");
		ui_interface->declare(&fHslider78, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider78, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider83, "1", "");
		ui_interface->declare(&fHslider83, "osc", "/kick/tune");
		ui_interface->declare(&fHslider83, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider83, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider81, "1", "");
		ui_interface->declare(&fHslider81, "osc", "/kick/dec");
		ui_interface->declare(&fHslider81, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider81, FAUSTFLOAT(0.18f), FAUSTFLOAT(0.02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider79, "1", "");
		ui_interface->declare(&fHslider79, "osc", "/kick/groove");
		ui_interface->declare(&fHslider79, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider79, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider88, "1", "");
		ui_interface->declare(&fHslider88, "osc", "/kick/mix");
		ui_interface->declare(&fHslider88, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Rumble", &fHslider88, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider84, "1", "");
		ui_interface->declare(&fHslider84, "osc", "/kick/nota");
		ui_interface->declare(&fHslider84, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider84, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider77, "1", "");
		ui_interface->declare(&fHslider77, "osc", "/kick/reloj");
		ui_interface->declare(&fHslider77, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider77, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider80, "1", "");
		ui_interface->declare(&fHslider80, "osc", "/kick/swing");
		ui_interface->declare(&fHslider80, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider80, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider82, "1", "");
		ui_interface->declare(&fHslider82, "osc", "/kick/sweep");
		ui_interface->declare(&fHslider82, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Transitorio", &fHslider82, FAUSTFLOAT(1.5e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(3e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider89, "1", "");
		ui_interface->declare(&fHslider89, "osc", "/kick/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider89, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider85, "2", "");
		ui_interface->declare(&fHslider85, "osc", "/kick/comp_fmax");
		ui_interface->declare(&fHslider85, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Filtro Frec Max", &fHslider85, FAUSTFLOAT(2.5e+03f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(8e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider73, "2", "");
		ui_interface->declare(&fHslider73, "osc", "/kick/comp_fmin");
		ui_interface->declare(&fHslider73, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Filtro Frec Min", &fHslider73, FAUSTFLOAT(7.5e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(2e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider86, "2", "");
		ui_interface->declare(&fHslider86, "osc", "/kick/comp_ratio");
		ui_interface->declare(&fHslider86, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Lim Ratio", &fHslider86, FAUSTFLOAT(8.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider74, "2", "");
		ui_interface->declare(&fHslider74, "osc", "/kick/comp_thresh");
		ui_interface->declare(&fHslider74, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Lim Umbral", &fHslider74, FAUSTFLOAT(0.4f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider87, "2", "");
		ui_interface->declare(&fHslider87, "osc", "/kick/comp_drive");
		ui_interface->declare(&fHslider87, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Saturacion Pegada", &fHslider87, FAUSTFLOAT(3.5f), FAUSTFLOAT(0.5f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("Caja");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider60, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider60, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider59, "osc", "/master/sync_reset");
		ui_interface->addHorizontalSlider("Sync_Reset", &fHslider59, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+07f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider70, "1", "");
		ui_interface->declare(&fHslider70, "osc", "/snare/accent");
		ui_interface->declare(&fHslider70, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider70, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider68, "1", "");
		ui_interface->declare(&fHslider68, "osc", "/snare/tune");
		ui_interface->declare(&fHslider68, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider68, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider67, "1", "");
		ui_interface->declare(&fHslider67, "osc", "/snare/dec_cuerpo");
		ui_interface->declare(&fHslider67, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decay Cuerpo", &fHslider67, FAUSTFLOAT(0.07f), FAUSTFLOAT(0.01f), FAUSTFLOAT(0.4f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider63, "1", "");
		ui_interface->declare(&fHslider63, "osc", "/snare/dec_resorte");
		ui_interface->declare(&fHslider63, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decay Resortes", &fHslider63, FAUSTFLOAT(0.16f), FAUSTFLOAT(0.02f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider57, "1", "");
		ui_interface->declare(&fHslider57, "osc", "/snare/hp");
		ui_interface->declare(&fHslider57, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro Paso Alto", &fHslider57, FAUSTFLOAT(1.6e+02f), FAUSTFLOAT(8e+01f), FAUSTFLOAT(4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider64, "1", "");
		ui_interface->declare(&fHslider64, "osc", "/snare/freq");
		ui_interface->declare(&fHslider64, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Frecuencia Resortes", &fHslider64, FAUSTFLOAT(1.65e+03f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(4e+03f), FAUSTFLOAT(1e+01f));
		ui_interface->declare(&fHslider58, "1", "");
		ui_interface->declare(&fHslider58, "osc", "/snare/groove");
		ui_interface->declare(&fHslider58, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider58, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider66, "1", "");
		ui_interface->declare(&fHslider66, "osc", "/snare/mix");
		ui_interface->declare(&fHslider66, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Resortes", &fHslider66, FAUSTFLOAT(0.55f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider69, "1", "");
		ui_interface->declare(&fHslider69, "osc", "/snare/nota");
		ui_interface->declare(&fHslider69, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider69, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider61, "1", "");
		ui_interface->declare(&fHslider61, "osc", "/snare/reloj");
		ui_interface->declare(&fHslider61, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider61, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider65, "1", "");
		ui_interface->declare(&fHslider65, "osc", "/snare/q");
		ui_interface->declare(&fHslider65, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Resonancia Resortes", &fHslider65, FAUSTFLOAT(2.5f), FAUSTFLOAT(1.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider71, "1", "");
		ui_interface->declare(&fHslider71, "osc", "/snare/drive");
		ui_interface->declare(&fHslider71, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider71, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider62, "1", "");
		ui_interface->declare(&fHslider62, "osc", "/snare/swing");
		ui_interface->declare(&fHslider62, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider62, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider72, "1", "");
		ui_interface->declare(&fHslider72, "osc", "/snare/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider72, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("Platillos");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider49, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider49, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider48, "osc", "/master/sync_reset");
		ui_interface->addHorizontalSlider("Sync_Reset", &fHslider48, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+07f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider51, "1", "");
		ui_interface->declare(&fHslider51, "osc", "/hat/accent");
		ui_interface->declare(&fHslider51, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider51, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider45, "1", "");
		ui_interface->declare(&fHslider45, "osc", "/hat/tune");
		ui_interface->declare(&fHslider45, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Afinacion", &fHslider45, FAUSTFLOAT(0.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider54, "1", "");
		ui_interface->declare(&fHslider54, "osc", "/hat/ataque");
		ui_interface->declare(&fHslider54, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Ataque", &fHslider54, FAUSTFLOAT(0.001f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider55, "1", "");
		ui_interface->declare(&fHslider55, "osc", "/hat/dec");
		ui_interface->declare(&fHslider55, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider55, FAUSTFLOAT(0.04f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider43, "1", "");
		ui_interface->declare(&fHslider43, "osc", "/hat/cutoff");
		ui_interface->declare(&fHslider43, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro Paso Alto", &fHslider43, FAUSTFLOAT(6.5e+03f), FAUSTFLOAT(3e+03f), FAUSTFLOAT(1.2e+04f), FAUSTFLOAT(5e+01f));
		ui_interface->declare(&fHslider52, "1", "");
		ui_interface->declare(&fHslider52, "osc", "/hat/groove");
		ui_interface->declare(&fHslider52, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider52, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider44, "1", "");
		ui_interface->declare(&fHslider44, "osc", "/hat/mix");
		ui_interface->declare(&fHslider44, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Mix Metal Ruido", &fHslider44, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider46, "1", "");
		ui_interface->declare(&fHslider46, "osc", "/hat/nota");
		ui_interface->declare(&fHslider46, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider46, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider50, "1", "");
		ui_interface->declare(&fHslider50, "osc", "/hat/reloj");
		ui_interface->declare(&fHslider50, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider50, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider47, "1", "");
		ui_interface->declare(&fHslider47, "osc", "/hat/drive");
		ui_interface->declare(&fHslider47, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider47, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider53, "1", "");
		ui_interface->declare(&fHslider53, "osc", "/hat/swing");
		ui_interface->declare(&fHslider53, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider53, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider56, "1", "");
		ui_interface->declare(&fHslider56, "osc", "/hat/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider56, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openVerticalBox("Bajo WG");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider33, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider33, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider31, "osc", "/master/sync_reset");
		ui_interface->addHorizontalSlider("Sync_Reset", &fHslider31, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+07f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider36, "1", "");
		ui_interface->declare(&fHslider36, "osc", "/bass/accent");
		ui_interface->declare(&fHslider36, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider36, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider35, "1", "");
		ui_interface->declare(&fHslider35, "osc", "/bass/dec");
		ui_interface->declare(&fHslider35, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider35, FAUSTFLOAT(0.35f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider39, "1", "");
		ui_interface->declare(&fHslider39, "osc", "/bass/detune");
		ui_interface->declare(&fHslider39, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Desafinado", &fHslider39, FAUSTFLOAT(0.04f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider40, "1", "");
		ui_interface->declare(&fHslider40, "osc", "/bass/lfo");
		ui_interface->declare(&fHslider40, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Filtro LFO", &fHslider40, FAUSTFLOAT(0.45f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider30, "1", "");
		ui_interface->declare(&fHslider30, "osc", "/bass/groove");
		ui_interface->declare(&fHslider30, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider30, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider37, "1", "");
		ui_interface->declare(&fHslider37, "osc", "/bass/intervalo");
		ui_interface->addHorizontalSlider("Sintesis/Intervalo", &fHslider37, FAUSTFLOAT(-12.0f), FAUSTFLOAT(-12.0f), FAUSTFLOAT(7.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider38, "1", "");
		ui_interface->declare(&fHslider38, "osc", "/bass/nota");
		ui_interface->declare(&fHslider38, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider38, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider32, "1", "");
		ui_interface->declare(&fHslider32, "osc", "/bass/reloj");
		ui_interface->declare(&fHslider32, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider32, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider41, "1", "");
		ui_interface->declare(&fHslider41, "osc", "/bass/drive");
		ui_interface->declare(&fHslider41, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Saturacion", &fHslider41, FAUSTFLOAT(0.65f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider34, "1", "");
		ui_interface->declare(&fHslider34, "osc", "/bass/swing");
		ui_interface->declare(&fHslider34, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider34, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider42, "1", "");
		ui_interface->declare(&fHslider42, "osc", "/bass/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider42, FAUSTFLOAT(0.55f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "5", "");
		ui_interface->openVerticalBox("Synth Psyche");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider1, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider1, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider0, "osc", "/master/sync_reset");
		ui_interface->addHorizontalSlider("Sync_Reset", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+07f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider3, "1", "");
		ui_interface->declare(&fHslider3, "osc", "/syn1/accent");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider3, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider11, "1", "");
		ui_interface->declare(&fHslider11, "osc", "/syn1/auto_p");
		ui_interface->declare(&fHslider11, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Profundidad", &fHslider11, FAUSTFLOAT(0.7f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider90, "1", "");
		ui_interface->declare(&fHslider90, "osc", "/syn1/auto_r");
		ui_interface->declare(&fHslider90, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Resonancia", &fHslider90, FAUSTFLOAT(4.5f), FAUSTFLOAT(1.0f), FAUSTFLOAT(9.0f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider10, "1", "");
		ui_interface->declare(&fHslider10, "osc", "/syn1/auto_v");
		ui_interface->declare(&fHslider10, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Auto Velocidad", &fHslider10, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.05f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "osc", "/syn1/dec");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider6, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "osc", "/syn1/groove");
		ui_interface->declare(&fHslider4, "style", "menu{'1: Ultra Hipnotico':0; '2: Deep Mental':1; '3: Bucle Psiquico':2; '4: Driving Techno':3; '5: Tribal Funk':4; '6: Hardgroove Tradicional':5; '7: Hardgroove Frenetico':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider8, "1", "");
		ui_interface->declare(&fHslider8, "osc", "/syn1/nota");
		ui_interface->declare(&fHslider8, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider8, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider9, "1", "");
		ui_interface->declare(&fHslider9, "osc", "/syn1/osc1");
		ui_interface->addHorizontalSlider("Sintesis/Osc 1", &fHslider9, FAUSTFLOAT(5.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "osc", "/syn1/osc2");
		ui_interface->addHorizontalSlider("Sintesis/Osc 2", &fHslider7, FAUSTFLOAT(12.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(19.0f), FAUSTFLOAT(19.0f));
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "osc", "/syn1/reloj");
		ui_interface->declare(&fHslider2, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "osc", "/syn1/swing");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider12, "1", "");
		ui_interface->declare(&fHslider12, "osc", "/syn1/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider12, FAUSTFLOAT(0.85f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "6", "");
		ui_interface->openVerticalBox("Siringe FDN");
		ui_interface->openVerticalBox("0_MASTER");
		ui_interface->declare(&fHslider18, "osc", "/master/bpm");
		ui_interface->addHorizontalSlider("BPM_Maestro", &fHslider18, FAUSTFLOAT(1.4e+02f), FAUSTFLOAT(6e+01f), FAUSTFLOAT(2.4e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider17, "osc", "/master/sync_reset");
		ui_interface->addHorizontalSlider("Sync_Reset", &fHslider17, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+07f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider20, "1", "");
		ui_interface->declare(&fHslider20, "osc", "/syn2/accent");
		ui_interface->declare(&fHslider20, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Accent", &fHslider20, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider23, "1", "");
		ui_interface->declare(&fHslider23, "osc", "/syn2/dec");
		ui_interface->declare(&fHslider23, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Decaimiento", &fHslider23, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.01f), FAUSTFLOAT(2.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider26, "1", "");
		ui_interface->declare(&fHslider26, "osc", "/syn2/disp");
		ui_interface->declare(&fHslider26, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Dispersion", &fHslider26, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.9f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider21, "1", "");
		ui_interface->declare(&fHslider21, "osc", "/syn2/groove");
		ui_interface->declare(&fHslider21, "style", "menu{'1':0; '2':1; '3':2; '4':3; '5':4; '6':5; '7':6}");
		ui_interface->addHorizontalSlider("Sintesis/Groove", &fHslider21, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider15, "1", "");
		ui_interface->declare(&fHslider15, "osc", "/syn2/lfo_f");
		ui_interface->declare(&fHslider15, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/LFO Freq", &fHslider15, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider16, "1", "");
		ui_interface->declare(&fHslider16, "osc", "/syn2/lfo_p");
		ui_interface->declare(&fHslider16, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/LFO Profundidad", &fHslider16, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider24, "1", "");
		ui_interface->declare(&fHslider24, "osc", "/syn2/nota");
		ui_interface->declare(&fHslider24, "style", "menu{'Octava':12; 'Quinta Arriba':19; 'Doble Octava':24}");
		ui_interface->addHorizontalSlider("Sintesis/Nota Siringe", &fHslider24, FAUSTFLOAT(12.0f), FAUSTFLOAT(12.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider25, "1", "");
		ui_interface->declare(&fHslider25, "osc", "/syn2/nota");
		ui_interface->declare(&fHslider25, "style", "menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}");
		ui_interface->addHorizontalSlider("Sintesis/Nota", &fHslider25, FAUSTFLOAT(36.0f), FAUSTFLOAT(36.0f), FAUSTFLOAT(47.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider19, "1", "");
		ui_interface->declare(&fHslider19, "osc", "/syn2/reloj");
		ui_interface->declare(&fHslider19, "style", "menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}");
		ui_interface->addHorizontalSlider("Sintesis/Reloj", &fHslider19, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.25f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.25f));
		ui_interface->declare(&fHslider22, "1", "");
		ui_interface->declare(&fHslider22, "osc", "/syn2/swing");
		ui_interface->declare(&fHslider22, "style", "knob");
		ui_interface->addHorizontalSlider("Sintesis/Swing", &fHslider22, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(75.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider29, "1", "");
		ui_interface->declare(&fHslider29, "osc", "/syn2/vol");
		ui_interface->addHorizontalSlider("Sintesis/Volumen", &fHslider29, FAUSTFLOAT(0.22f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider13, "2", "");
		ui_interface->declare(&fHslider13, "osc", "/syn2/comp_a");
		ui_interface->declare(&fHslider13, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Ataque", &fHslider13, FAUSTFLOAT(0.005f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider27, "2", "");
		ui_interface->declare(&fHslider27, "osc", "/syn2/comp_rel");
		ui_interface->declare(&fHslider27, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Liberacion", &fHslider27, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.01f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider28, "2", "");
		ui_interface->declare(&fHslider28, "osc", "/syn2/comp_r");
		ui_interface->declare(&fHslider28, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Ratio", &fHslider28, FAUSTFLOAT(6.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider14, "2", "");
		ui_interface->declare(&fHslider14, "osc", "/syn2/comp_th");
		ui_interface->declare(&fHslider14, "style", "knob");
		ui_interface->addHorizontalSlider("Dinamica/Comp Umbral", &fHslider14, FAUSTFLOAT(-2e+01f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = static_cast<float>(fHslider0);
		float fSlow1 = static_cast<float>(fHslider2) * static_cast<float>(fHslider1);
		float fSlow2 = fConst13 * fSlow1;
		float fSlow3 = 0.4f * static_cast<float>(fHslider3) + 1.0f;
		float fSlow4 = static_cast<float>(fHslider4);
		int iSlow5 = fSlow4 >= 4.0f;
		int iSlow6 = fSlow4 >= 2.0f;
		int iSlow7 = fSlow4 >= 1.0f;
		int iSlow8 = fSlow4 >= 3.0f;
		int iSlow9 = fSlow4 >= 6.0f;
		int iSlow10 = fSlow4 >= 5.0f;
		float fSlow11 = fConst14 * (static_cast<float>(fHslider5) / fSlow1);
		int iSlow12 = static_cast<int>(fSlow11);
		int iSlow13 = std::min<int>(16385, std::max<int>(0, iSlow12 + 1));
		float fSlow14 = std::floor(fSlow11);
		float fSlow15 = fSlow11 - fSlow14;
		int iSlow16 = std::min<int>(16385, std::max<int>(0, iSlow12));
		float fSlow17 = fSlow14 + (1.0f - fSlow11);
		float fSlow18 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider6));
		float fSlow19 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider8) + -69.0f));
		float fSlow20 = 4.4e+02f * fSlow19 * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider7));
		float fSlow21 = 4.4e+02f * fSlow19 * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider9));
		float fSlow22 = fConst18 * static_cast<float>(fHslider10);
		float fSlow23 = static_cast<float>(fHslider11);
		float fSlow24 = static_cast<float>(fHslider12);
		float fSlow25 = fConst5 * fSlow24 * (1.0f - 0.5f * fSlow23);
		float fSlow26 = static_cast<float>(fHslider13);
		float fSlow27 = 0.5f * fSlow26;
		int iSlow28 = std::fabs(fSlow27) < 1.1920929e-07f;
		float fSlow29 = ((iSlow28) ? 0.0f : std::exp(-(fConst18 / ((iSlow28) ? 1.0f : fSlow27))));
		float fSlow30 = 1.0f - fSlow29;
		float fSlow31 = static_cast<float>(fHslider14);
		float fSlow32 = fConst18 * static_cast<float>(fHslider15);
		float fSlow33 = static_cast<float>(fHslider16);
		float fSlow34 = static_cast<float>(fHslider17);
		float fSlow35 = static_cast<float>(fHslider19) * static_cast<float>(fHslider18);
		float fSlow36 = fConst13 * fSlow35;
		float fSlow37 = 0.6f * static_cast<float>(fHslider20) + 1.0f;
		float fSlow38 = static_cast<float>(fHslider21);
		int iSlow39 = fSlow38 >= 4.0f;
		int iSlow40 = fSlow38 >= 2.0f;
		int iSlow41 = fSlow38 >= 1.0f;
		int iSlow42 = fSlow38 >= 3.0f;
		int iSlow43 = fSlow38 >= 6.0f;
		int iSlow44 = fSlow38 >= 5.0f;
		float fSlow45 = fConst14 * (static_cast<float>(fHslider22) / fSlow35);
		int iSlow46 = static_cast<int>(fSlow45);
		int iSlow47 = std::min<int>(16385, std::max<int>(0, iSlow46 + 1));
		float fSlow48 = std::floor(fSlow45);
		float fSlow49 = fSlow45 - fSlow48;
		int iSlow50 = std::min<int>(16385, std::max<int>(0, iSlow46));
		float fSlow51 = fSlow48 + (1.0f - fSlow45);
		float fSlow52 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider23));
		float fSlow53 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider25) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider24));
		float fSlow54 = 0.5f * static_cast<float>(fHslider26);
		float fSlow55 = static_cast<float>(fHslider27);
		int iSlow56 = std::fabs(fSlow55) < 1.1920929e-07f;
		float fSlow57 = ((iSlow56) ? 0.0f : std::exp(-(fConst18 / ((iSlow56) ? 1.0f : fSlow55))));
		int iSlow58 = std::fabs(fSlow26) < 1.1920929e-07f;
		float fSlow59 = ((iSlow58) ? 0.0f : std::exp(-(fConst18 / ((iSlow58) ? 1.0f : fSlow26))));
		float fSlow60 = 1.0f / std::max<float>(1.1920929e-07f, static_cast<float>(fHslider28)) + -1.0f;
		float fSlow61 = fConst26 * static_cast<float>(fHslider29);
		float fSlow62 = static_cast<float>(fHslider30);
		int iSlow63 = fSlow62 >= 4.0f;
		int iSlow64 = fSlow62 >= 2.0f;
		int iSlow65 = fSlow62 >= 1.0f;
		float fSlow66 = static_cast<float>(fHslider31);
		float fSlow67 = static_cast<float>(fHslider33);
		float fSlow68 = fSlow67 * static_cast<float>(fHslider32);
		float fSlow69 = fConst13 * fSlow68;
		int iSlow70 = fSlow62 >= 3.0f;
		int iSlow71 = fSlow62 >= 6.0f;
		int iSlow72 = fSlow62 >= 5.0f;
		float fSlow73 = fConst14 * (static_cast<float>(fHslider34) / fSlow68);
		int iSlow74 = static_cast<int>(fSlow73);
		int iSlow75 = std::min<int>(16385, std::max<int>(0, iSlow74 + 1));
		float fSlow76 = std::floor(fSlow73);
		float fSlow77 = fSlow73 - fSlow76;
		int iSlow78 = std::min<int>(16385, std::max<int>(0, iSlow74));
		float fSlow79 = fSlow76 + (1.0f - fSlow73);
		float fSlow80 = 0.004166667f * (fSlow67 / static_cast<float>(fHslider35));
		float fSlow81 = 0.4f * static_cast<float>(fHslider36) + 1.0f;
		float fSlow82 = static_cast<float>(fHslider39);
		float fSlow83 = fConst58 * ((0.059f * fSlow82 + 1.0f) / (std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider38) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider37))));
		int iSlow84 = static_cast<int>(fSlow83);
		int iSlow85 = std::min<int>(131073, std::max<int>(0, iSlow84 + 1)) + 1;
		float fSlow86 = std::floor(fSlow83);
		float fSlow87 = fSlow83 - fSlow86;
		int iSlow88 = std::min<int>(131073, std::max<int>(0, iSlow84)) + 1;
		float fSlow89 = fSlow86 + (1.0f - fSlow83);
		float fSlow90 = static_cast<float>(fHslider40);
		float fSlow91 = 3.0f * static_cast<float>(fHslider41);
		float fSlow92 = (fSlow91 + 1.0f) * (0.014f * fSlow82 + 0.985f);
		float fSlow93 = fConst42 * static_cast<float>(fHslider42);
		float fSlow94 = std::tan(fConst61 * static_cast<float>(fHslider43));
		float fSlow95 = mydsp_faustpower2_f(fSlow94);
		float fSlow96 = 2.0f * (1.0f - 1.0f / fSlow95);
		float fSlow97 = 1.0f / fSlow94;
		float fSlow98 = (fSlow97 + -1.4142135f) / fSlow94 + 1.0f;
		float fSlow99 = (fSlow97 + 1.4142135f) / fSlow94 + 1.0f;
		float fSlow100 = 1.0f / fSlow99;
		float fSlow101 = static_cast<float>(fHslider44);
		float fSlow102 = 4.656613e-10f * fSlow101;
		float fSlow103 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider46) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider45));
		float fSlow104 = std::max<float>(19306.982f * fSlow103, 23.44895f);
		float fSlow105 = std::max<float>(2e+01f, std::fabs(fSlow104));
		float fSlow106 = fConst18 * fSlow105;
		float fSlow107 = fConst62 / fSlow105;
		float fSlow108 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow104));
		int iSlow109 = static_cast<int>(fSlow108);
		float fSlow110 = std::floor(fSlow108);
		float fSlow111 = fSlow110 + (1.0f - fSlow108);
		float fSlow112 = std::max<float>(15940.032f * fSlow103, 23.44895f);
		float fSlow113 = std::max<float>(2e+01f, std::fabs(fSlow112));
		float fSlow114 = fConst18 * fSlow113;
		float fSlow115 = fConst62 / fSlow113;
		float fSlow116 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow112));
		int iSlow117 = static_cast<int>(fSlow116);
		float fSlow118 = std::floor(fSlow116);
		float fSlow119 = fSlow118 + (1.0f - fSlow116);
		float fSlow120 = std::max<float>(12784.989f * fSlow103, 23.44895f);
		float fSlow121 = std::max<float>(2e+01f, std::fabs(fSlow120));
		float fSlow122 = fConst18 * fSlow121;
		float fSlow123 = fConst62 / fSlow121;
		float fSlow124 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow120));
		int iSlow125 = static_cast<int>(fSlow124);
		float fSlow126 = std::floor(fSlow124);
		float fSlow127 = fSlow126 + (1.0f - fSlow124);
		float fSlow128 = std::max<float>(9794.762f * fSlow103, 23.44895f);
		float fSlow129 = std::max<float>(2e+01f, std::fabs(fSlow128));
		float fSlow130 = fConst18 * fSlow129;
		float fSlow131 = fConst62 / fSlow129;
		float fSlow132 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow128));
		int iSlow133 = static_cast<int>(fSlow132);
		float fSlow134 = std::floor(fSlow132);
		float fSlow135 = fSlow134 + (1.0f - fSlow132);
		float fSlow136 = std::max<float>(7016.4395f * fSlow103, 23.44895f);
		float fSlow137 = std::max<float>(2e+01f, std::fabs(fSlow136));
		float fSlow138 = fConst18 * fSlow137;
		float fSlow139 = fConst62 / fSlow137;
		float fSlow140 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow136));
		int iSlow141 = static_cast<int>(fSlow140);
		float fSlow142 = std::floor(fSlow140);
		float fSlow143 = fSlow142 + (1.0f - fSlow140);
		float fSlow144 = std::max<float>(4709.02f * fSlow103, 23.44895f);
		float fSlow145 = std::max<float>(2e+01f, std::fabs(fSlow144));
		float fSlow146 = fConst18 * fSlow145;
		float fSlow147 = fConst62 / fSlow145;
		float fSlow148 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fSlow144));
		int iSlow149 = static_cast<int>(fSlow148);
		int iSlow150 = iSlow149 + 1;
		float fSlow151 = std::floor(fSlow148);
		float fSlow152 = fSlow148 - fSlow151;
		float fSlow153 = fSlow151 + (1.0f - fSlow148);
		int iSlow154 = iSlow141 + 1;
		float fSlow155 = fSlow140 - fSlow142;
		int iSlow156 = iSlow133 + 1;
		float fSlow157 = fSlow132 - fSlow134;
		int iSlow158 = iSlow125 + 1;
		float fSlow159 = fSlow124 - fSlow126;
		int iSlow160 = iSlow117 + 1;
		float fSlow161 = fSlow116 - fSlow118;
		int iSlow162 = iSlow109 + 1;
		float fSlow163 = fSlow108 - fSlow110;
		float fSlow164 = 1.0f / fSlow105;
		float fSlow165 = 1.0f / fSlow113;
		float fSlow166 = 1.0f / fSlow121;
		float fSlow167 = 1.0f / fSlow129;
		float fSlow168 = 1.0f / fSlow137;
		float fSlow169 = 1.0f / fSlow145;
		float fSlow170 = 0.15f * (1.0f - fSlow101);
		float fSlow171 = 6.5f * static_cast<float>(fHslider47);
		float fSlow172 = static_cast<float>(fHslider48);
		float fSlow173 = static_cast<float>(fHslider50) * static_cast<float>(fHslider49);
		float fSlow174 = fConst13 * fSlow173;
		float fSlow175 = 0.4f * static_cast<float>(fHslider51) + 1.0f;
		float fSlow176 = static_cast<float>(fHslider52);
		int iSlow177 = fSlow176 >= 4.0f;
		int iSlow178 = fSlow176 >= 2.0f;
		int iSlow179 = fSlow176 >= 1.0f;
		int iSlow180 = fSlow176 >= 3.0f;
		int iSlow181 = fSlow176 >= 6.0f;
		int iSlow182 = fSlow176 >= 5.0f;
		float fSlow183 = fConst14 * (static_cast<float>(fHslider53) / fSlow173);
		int iSlow184 = static_cast<int>(fSlow183);
		int iSlow185 = std::min<int>(16385, std::max<int>(0, iSlow184 + 1));
		float fSlow186 = std::floor(fSlow183);
		float fSlow187 = fSlow183 - fSlow186;
		int iSlow188 = std::min<int>(16385, std::max<int>(0, iSlow184));
		float fSlow189 = fSlow186 + (1.0f - fSlow183);
		float fSlow190 = std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider54));
		float fSlow191 = 1.0f / fSlow190;
		float fSlow192 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider55));
		float fSlow193 = 2.0f * (static_cast<float>(fHslider56) / (fSlow95 * fSlow99));
		float fSlow194 = std::tan(fConst61 * static_cast<float>(fHslider57));
		float fSlow195 = mydsp_faustpower2_f(fSlow194);
		float fSlow196 = 2.0f * (1.0f - 1.0f / fSlow195);
		float fSlow197 = 1.0f / fSlow194;
		float fSlow198 = (fSlow197 + -1.4142135f) / fSlow194 + 1.0f;
		float fSlow199 = (fSlow197 + 1.4142135f) / fSlow194 + 1.0f;
		float fSlow200 = 1.0f / fSlow199;
		float fSlow201 = static_cast<float>(fHslider58);
		int iSlow202 = fSlow201 >= 4.0f;
		int iSlow203 = fSlow201 >= 2.0f;
		int iSlow204 = fSlow201 >= 1.0f;
		float fSlow205 = static_cast<float>(fHslider59);
		float fSlow206 = static_cast<float>(fHslider61) * static_cast<float>(fHslider60);
		float fSlow207 = fConst13 * fSlow206;
		int iSlow208 = fSlow201 >= 3.0f;
		int iSlow209 = fSlow201 >= 6.0f;
		int iSlow210 = fSlow201 >= 5.0f;
		float fSlow211 = fConst14 * (static_cast<float>(fHslider62) / fSlow206);
		int iSlow212 = static_cast<int>(fSlow211);
		int iSlow213 = std::min<int>(16385, std::max<int>(0, iSlow212 + 1));
		float fSlow214 = std::floor(fSlow211);
		float fSlow215 = fSlow211 - fSlow214;
		int iSlow216 = std::min<int>(16385, std::max<int>(0, iSlow212));
		float fSlow217 = fSlow214 + (1.0f - fSlow211);
		float fSlow218 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider63));
		float fSlow219 = std::tan(fConst61 * static_cast<float>(fHslider64));
		float fSlow220 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fSlow219));
		float fSlow221 = 1.0f / static_cast<float>(fHslider65);
		float fSlow222 = 1.0f / fSlow219;
		float fSlow223 = (fSlow222 - fSlow221) / fSlow219 + 1.0f;
		float fSlow224 = (fSlow221 + fSlow222) / fSlow219 + 1.0f;
		float fSlow225 = 1.0f / fSlow224;
		float fSlow226 = static_cast<float>(fHslider66);
		float fSlow227 = 2.34f * (fSlow226 / (fSlow219 * fSlow224));
		float fSlow228 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider67));
		float fSlow229 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider69) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider68));
		float fSlow230 = fConst70 * fSlow229;
		float fSlow231 = fConst71 * fSlow229;
		float fSlow232 = 1.0f - fSlow226;
		float fSlow233 = 0.4f * static_cast<float>(fHslider70) + 1.0f;
		float fSlow234 = static_cast<float>(fHslider71);
		float fSlow235 = 1.0f / (fSlow195 * fSlow199);
		float fSlow236 = static_cast<float>(fHslider72);
		float fSlow237 = static_cast<float>(fHslider73);
		float fSlow238 = static_cast<float>(fHslider74);
		float fSlow239 = static_cast<float>(fHslider75);
		float fSlow240 = static_cast<float>(fHslider77) * static_cast<float>(fHslider76);
		float fSlow241 = fConst13 * fSlow240;
		float fSlow242 = 0.4f * static_cast<float>(fHslider78) + 1.0f;
		float fSlow243 = static_cast<float>(fHslider79);
		int iSlow244 = fSlow243 >= 4.0f;
		int iSlow245 = fSlow243 >= 2.0f;
		int iSlow246 = fSlow243 >= 1.0f;
		int iSlow247 = fSlow243 >= 3.0f;
		int iSlow248 = fSlow243 >= 6.0f;
		int iSlow249 = fSlow243 >= 5.0f;
		float fSlow250 = fConst14 * (static_cast<float>(fHslider80) / fSlow240);
		int iSlow251 = static_cast<int>(fSlow250);
		int iSlow252 = std::min<int>(16385, std::max<int>(0, iSlow251 + 1));
		float fSlow253 = std::floor(fSlow250);
		float fSlow254 = fSlow250 - fSlow253;
		int iSlow255 = std::min<int>(16385, std::max<int>(0, iSlow251));
		float fSlow256 = fSlow253 + (1.0f - fSlow250);
		float fSlow257 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider81));
		float fSlow258 = static_cast<float>(fHslider82);
		float fSlow259 = 4.4e+02f * std::pow(2.0f, 0.083333336f * (static_cast<float>(fHslider84) + -69.0f)) * std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider83));
		float fSlow260 = static_cast<float>(fHslider85);
		float fSlow261 = static_cast<float>(fHslider86);
		float fSlow262 = fSlow261 * (fSlow260 - fSlow237);
		float fSlow263 = static_cast<float>(fHslider87);
		float fSlow264 = static_cast<float>(fHslider88);
		float fSlow265 = 1.8f * fSlow264;
		float fSlow266 = fConst60 * (1.0f - fSlow264);
		float fSlow267 = static_cast<float>(fHslider89);
		float fSlow268 = 5e+03f * fSlow23;
		float fSlow269 = 1.0f / static_cast<float>(fHslider90);
		float fSlow270 = 85.0f * fSlow23;
		float fSlow271 = fSlow23 * fSlow24;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fVec1[0] = fSlow0;
			iRec3[0] = (iRec3[1] + 1) * (1 - (fSlow0 != fVec1[1]));
			int iTemp0 = static_cast<int>(fSlow2 * static_cast<float>(iRec3[0])) % 16;
			iVec2[0] = iTemp0;
			int iTemp1 = iTemp0 >= 8;
			int iTemp2 = iTemp0 >= 12;
			int iTemp3 = iTemp0 >= 10;
			int iTemp4 = iTemp0 >= 9;
			int iTemp5 = ((iTemp4) ? 0 : 1);
			int iTemp6 = iTemp0 >= 4;
			int iTemp7 = iTemp0 >= 6;
			int iTemp8 = iTemp0 >= 5;
			int iTemp9 = ((iTemp8) ? 0 : 1);
			int iTemp10 = ((iTemp7) ? 0 : iTemp9);
			int iTemp11 = iTemp0 >= 14;
			int iTemp12 = iTemp0 >= 13;
			int iTemp13 = iTemp0 >= 15;
			int iTemp14 = ((iTemp13) ? 0 : 1);
			int iTemp15 = iTemp0 >= 2;
			int iTemp16 = iTemp0 >= 3;
			int iTemp17 = ((iTemp16) ? 0 : 1);
			int iTemp18 = iTemp0 >= 11;
			int iTemp19 = ((iTemp18) ? 0 : 1);
			int iTemp20 = ((iTemp0 >= 1) ? 0 : 1);
			int iTemp21 = ((iTemp16) ? 1 : 0);
			int iTemp22 = iTemp0 >= 7;
			int iTemp23 = ((iTemp18) ? 1 : 0);
			int iTemp24 = ((iTemp11) ? iTemp14 : 0);
			int iTemp25 = iTemp0 != iVec2[1];
			iVec3[IOTA0 & 32767] = iTemp25;
			int iTemp26 = static_cast<int>((((iTemp0 % 2) == 1) ? fSlow17 * static_cast<float>(iVec3[(IOTA0 - iSlow16) & 32767]) + fSlow15 * static_cast<float>(iVec3[(IOTA0 - iSlow13) & 32767]) : static_cast<float>(iTemp25))) & (((iSlow5) ? ((iSlow9) ? ((iTemp1) ? ((iTemp2) ? 1 : ((iTemp3) ? iTemp23 : 1)) : ((iTemp6) ? ((iTemp7) ? ((iTemp22) ? 1 : 0) : 1) : ((iTemp15) ? iTemp21 : 1))) : ((iSlow10) ? ((iTemp1) ? ((iTemp2) ? ((iTemp11) ? ((iTemp13) ? 1 : 0) : 1) : ((iTemp3) ? iTemp19 : iTemp5)) : ((iTemp6) ? ((iTemp7) ? 1 : iTemp9) : ((iTemp15) ? iTemp17 : iTemp20))) : ((iTemp1) ? ((iTemp2) ? iTemp24 : ((iTemp3) ? iTemp19 : ((iTemp4) ? 1 : 0))) : ((iTemp6) ? iTemp10 : ((iTemp15) ? 1 : 0))))) : ((iSlow6) ? ((iSlow8) ? ((iTemp1) ? ((iTemp2) ? iTemp24 : ((iTemp3) ? iTemp23 : iTemp5)) : ((iTemp6) ? ((iTemp7) ? ((iTemp22) ? 0 : 1) : 0) : ((iTemp15) ? iTemp21 : iTemp20))) : ((iTemp1) ? ((iTemp2) ? ((iTemp11) ? 0 : ((iTemp12) ? 1 : 0)) : ((iTemp3) ? iTemp19 : 0)) : ((iTemp6) ? ((iTemp7) ? 0 : ((iTemp8) ? 1 : 0)) : ((iTemp15) ? iTemp17 : 0)))) : ((iSlow7) ? ((iTemp1) ? ((iTemp2) ? ((iTemp11) ? iTemp14 : ((iTemp12) ? 0 : 1)) : 0) : ((iTemp6) ? iTemp10 : 0)) : ((iTemp1) ? ((iTemp2) ? 0 : ((iTemp3) ? 0 : iTemp5)) : 0)))) > 0);
			iVec4[0] = iTemp26;
			iRec4[0] = (iRec4[1] + (iRec4[1] > 0)) * (iTemp26 <= iVec4[1]) + (iTemp26 > iVec4[1]);
			float fTemp27 = static_cast<float>(iRec4[0]);
			int iTemp28 = 1 - iVec0[1];
			float fTemp29 = ((iTemp28) ? 0.0f : fConst17 + fRec6[1]);
			fRec6[0] = fTemp29 - std::floor(fTemp29);
			float fTemp30 = std::max<float>(fSlow20 + ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec6[0]), 65535))], 23.44895f);
			float fTemp31 = std::max<float>(2e+01f, std::fabs(fTemp30));
			float fTemp32 = ((iTemp28) ? 0.0f : fRec7[1] + fConst18 * fTemp31);
			fRec7[0] = fTemp32 - std::floor(fTemp32);
			float fTemp33 = mydsp_faustpower2_f(2.0f * fRec7[0] + -1.0f);
			fVec6[0] = fTemp33;
			float fTemp34 = static_cast<float>(iVec0[1]);
			float fTemp35 = fTemp34 * (fTemp33 - fVec6[1]) / fTemp31;
			fVec7[IOTA0 & 2047] = fTemp35;
			float fTemp36 = std::max<float>(0.0f, std::min<float>(2047.0f, fConst19 / fTemp30));
			int iTemp37 = static_cast<int>(fTemp36);
			float fTemp38 = std::floor(fTemp36);
			float fTemp39 = ((iTemp28) ? 0.0f : fConst20 + fRec10[1]);
			fRec10[0] = fTemp39 - std::floor(fTemp39);
			float fTemp40 = std::max<float>(1.1920929e-07f, std::fabs(fSlow21 + 2.0f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec10[0]), 65535))]));
			float fTemp41 = fRec8[1] + fConst18 * fTemp40;
			float fTemp42 = fTemp41 + -1.0f;
			int iTemp43 = fTemp42 < 0.0f;
			fRec8[0] = ((iTemp43) ? fTemp41 : fTemp42);
			float fRec9 = ((iTemp43) ? fTemp41 : fTemp41 + fTemp42 * (1.0f - fConst0 / fTemp40));
			fRec2[0] = (0.6f * (2.0f * fRec9 + -1.0f) + fConst14 * (fTemp35 - fVec7[(IOTA0 - iTemp37) & 2047] * (fTemp38 + (1.0f - fTemp36)) - (fTemp36 - fTemp38) * fVec7[(IOTA0 - (iTemp37 + 1)) & 2047])) * std::max<float>(0.0f, std::min<float>(fConst16 * fTemp27, fSlow18 * (fConst15 - fTemp27) + 1.0f)) * (((((iTemp0 == 0) | (iTemp0 == 4)) | (iTemp0 == 8)) | (iTemp0 == 12)) ? fSlow3 : 1.0f) - fConst12 * (fConst10 * fRec2[2] + fConst8 * fRec2[1]);
			fRec1[0] = fConst21 * (fRec2[2] + (fRec2[0] - 2.0f * fRec2[1])) - fConst5 * (fConst4 * fRec1[2] + fConst2 * fRec1[1]);
			float fTemp44 = fRec1[2] + fRec1[0] + 2.0f * fRec1[1];
			fVec8[IOTA0 & 255] = fTemp44;
			float fTemp45 = ((iTemp28) ? 0.0f : fSlow22 + fRec11[1]);
			fRec11[0] = fTemp45 - std::floor(fTemp45);
			float fTemp46 = ((iTemp28) ? 0.0f : fSlow32 + fRec16[1]);
			fRec16[0] = fTemp46 - std::floor(fTemp46);
			fVec9[0] = fSlow34;
			iRec22[0] = (iRec22[1] + 1) * (1 - (fSlow34 != fVec9[1]));
			int iTemp47 = static_cast<int>(fSlow36 * static_cast<float>(iRec22[0])) % 16;
			iVec10[0] = iTemp47;
			int iTemp48 = iTemp47 >= 8;
			int iTemp49 = iTemp47 >= 4;
			int iTemp50 = iTemp47 >= 2;
			int iTemp51 = iTemp47 >= 1;
			int iTemp52 = ((iTemp51) ? 0 : 1);
			int iTemp53 = iTemp47 >= 12;
			int iTemp54 = iTemp47 >= 14;
			int iTemp55 = iTemp47 >= 13;
			int iTemp56 = ((iTemp55) ? 0 : 1);
			int iTemp57 = ((iTemp54) ? 0 : iTemp56);
			int iTemp58 = iTemp47 >= 3;
			int iTemp59 = iTemp47 >= 6;
			int iTemp60 = iTemp47 >= 7;
			int iTemp61 = iTemp47 >= 10;
			int iTemp62 = iTemp47 >= 9;
			int iTemp63 = ((iTemp62) ? 1 : 0);
			int iTemp64 = ((iTemp61) ? 0 : iTemp63);
			int iTemp65 = ((iTemp51) ? 1 : 0);
			int iTemp66 = iTemp47 >= 5;
			int iTemp67 = ((iTemp60) ? 1 : 0);
			int iTemp68 = ((iTemp47 >= 15) ? 0 : 1);
			int iTemp69 = ((iTemp66) ? 1 : 0);
			int iTemp70 = ((iTemp55) ? 1 : 0);
			int iTemp71 = iTemp47 != iVec10[1];
			iVec11[IOTA0 & 32767] = iTemp71;
			int iTemp72 = static_cast<int>((((iTemp47 % 2) == 1) ? fSlow51 * static_cast<float>(iVec11[(IOTA0 - iSlow50) & 32767]) + fSlow49 * static_cast<float>(iVec11[(IOTA0 - iSlow47) & 32767]) : static_cast<float>(iTemp71)));
			int iTemp73 = iTemp72 & (iTemp72 & (((iSlow39) ? ((iSlow43) ? ((iTemp48) ? ((iTemp53) ? ((iTemp54) ? 1 : 0) : 1) : ((iTemp49) ? ((iTemp59) ? 1 : 0) : 1)) : ((iSlow44) ? ((iTemp48) ? ((iTemp53) ? ((iTemp54) ? 1 : iTemp70) : ((iTemp61) ? 1 : iTemp63)) : ((iTemp49) ? ((iTemp59) ? 1 : iTemp69) : ((iTemp50) ? 1 : iTemp65))) : ((iTemp48) ? ((iTemp53) ? ((iTemp54) ? iTemp68 : iTemp70) : ((iTemp61) ? ((iTemp47 >= 11) ? 1 : 0) : ((iTemp62) ? 0 : 1))) : ((iTemp49) ? ((iTemp59) ? iTemp67 : iTemp69) : ((iTemp50) ? ((iTemp58) ? 0 : 1) : iTemp52))))) : ((iSlow40) ? ((iSlow42) ? ((iTemp48) ? ((iTemp53) ? ((iTemp54) ? iTemp68 : iTemp56) : iTemp64) : ((iTemp49) ? ((iTemp59) ? iTemp67 : ((iTemp66) ? 0 : 1)) : ((iTemp50) ? 0 : iTemp65))) : ((iTemp48) ? ((iTemp53) ? iTemp57 : iTemp64) : ((iTemp49) ? ((iTemp59) ? ((iTemp60) ? 0 : 1) : 0) : ((iTemp50) ? ((iTemp58) ? 1 : 0) : 0)))) : ((iSlow41) ? ((iTemp48) ? ((iTemp53) ? iTemp57 : 0) : 0) : ((iTemp48) ? 0 : ((iTemp49) ? 0 : ((iTemp50) ? 0 : iTemp52)))))) > 0));
			iVec12[0] = iTemp73;
			iRec23[0] = (iRec23[1] + (iRec23[1] > 0)) * (iTemp73 <= iVec12[1]) + (iTemp73 > iVec12[1]);
			float fTemp74 = static_cast<float>(iRec23[0]);
			float fTemp75 = std::max<float>(0.0f, std::min<float>(fConst16 * fTemp74, fSlow52 * (fConst15 - fTemp74) + 1.0f)) * (((((iTemp47 == 0) | (iTemp47 == 4)) | (iTemp47 == 8)) | (iTemp47 == 12)) ? fSlow37 : 1.0f);
			float fTemp76 = ((iTemp28) ? 0.0f : fRec21[1] + fConst18 * (fSlow53 + 1.5e+03f * fTemp75));
			fRec21[0] = fTemp76 - std::floor(fTemp76);
			float fTemp77 = fTemp75 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec21[0]), 65535))];
			fRec24[0] = -(fConst36 * (fConst35 * fRec24[1] - (fRec18[(IOTA0 - 1400) & 2047] + fRec18[(IOTA0 - 1401) & 2047])));
			fRec25[0] = -(fConst36 * (fConst35 * fRec25[1] - (fRec17[(IOTA0 - 1118) & 2047] + fRec17[(IOTA0 - 1119) & 2047])));
			float fTemp78 = fRec25[0] + fRec24[0];
			fRec26[0] = -(fConst36 * (fConst35 * fRec26[1] - (fRec19[(IOTA0 - 1724) & 2047] + fRec19[(IOTA0 - 1725) & 2047])));
			fRec27[0] = -(fConst36 * (fConst35 * fRec27[1] - (fRec20[(IOTA0 - 2090) & 4095] + fRec20[(IOTA0 - 2091) & 4095])));
			fRec17[IOTA0 & 2047] = fSlow54 * (fRec27[0] + fRec26[0] + fTemp78) + fTemp77;
			float fTemp79 = fRec25[0] - fRec24[0];
			fRec18[IOTA0 & 2047] = fTemp77 - fSlow54 * (fRec27[0] - (fRec26[0] + fTemp79));
			fRec19[IOTA0 & 2047] = fTemp77 - fSlow54 * (fRec27[0] - (fTemp78 - fRec26[0]));
			fRec20[IOTA0 & 4095] = fTemp77 + fSlow54 * (fRec27[0] - (fRec26[0] - fTemp79));
			float fTemp80 = (fRec17[IOTA0 & 2047] + fRec18[IOTA0 & 2047] + fRec19[IOTA0 & 2047] + fRec20[IOTA0 & 4095]) * (fSlow33 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec16[0]), 65535))] + 1.0f);
			float fTemp81 = std::fabs(0.25f * fTemp80);
			float fTemp82 = ((fTemp81 > fRec15[1]) ? fSlow59 : fSlow57);
			fRec15[0] = fTemp81 * (1.0f - fTemp82) + fRec15[1] * fTemp82;
			fRec14[0] = fSlow60 * std::max<float>(2e+01f * std::log10(std::max<float>(1.1754944e-38f, fRec15[0])) - fSlow31, 0.0f) * fSlow30 + fSlow29 * fRec14[1];
			fRec13[0] = 0.25f * fTemp80 * std::pow(1e+01f, 0.05f * fRec14[0]) - fConst33 * (fConst31 * fRec13[2] + fConst29 * fRec13[1]);
			fRec12[0] = fConst37 * (fRec13[2] + (fRec13[0] - 2.0f * fRec13[1])) - fConst26 * (fConst25 * fRec12[2] + fConst23 * fRec12[1]);
			fVec13[0] = fSlow66;
			iRec32[0] = (iRec32[1] + 1) * (1 - (fSlow66 != fVec13[1]));
			int iTemp83 = static_cast<int>(fSlow69 * static_cast<float>(iRec32[0])) % 16;
			iVec14[0] = iTemp83;
			int iTemp84 = iTemp83 >= 8;
			int iTemp85 = iTemp83 >= 4;
			int iTemp86 = iTemp83 >= 2;
			int iTemp87 = iTemp83 >= 3;
			int iTemp88 = ((iTemp87) ? 0 : 1);
			int iTemp89 = iTemp83 >= 6;
			int iTemp90 = ((iTemp83 >= 7) ? 0 : 1);
			int iTemp91 = iTemp83 >= 12;
			int iTemp92 = iTemp83 >= 10;
			int iTemp93 = ((iTemp83 >= 11) ? 0 : 1);
			int iTemp94 = iTemp83 >= 14;
			int iTemp95 = iTemp83 >= 15;
			int iTemp96 = ((iTemp95) ? 0 : 1);
			int iTemp97 = iTemp83 >= 1;
			int iTemp98 = ((iTemp97) ? 1 : 0);
			int iTemp99 = iTemp83 >= 5;
			int iTemp100 = ((iTemp89) ? iTemp90 : ((iTemp99) ? 1 : 0));
			int iTemp101 = iTemp83 >= 9;
			int iTemp102 = ((iTemp92) ? iTemp93 : ((iTemp101) ? 1 : 0));
			int iTemp103 = iTemp83 >= 13;
			int iTemp104 = ((iTemp103) ? 1 : 0);
			int iTemp105 = ((iTemp97) ? 0 : 1);
			int iTemp106 = ((iTemp89) ? iTemp90 : ((iTemp99) ? 0 : 1));
			int iTemp107 = ((iTemp101) ? 0 : 1);
			int iTemp108 = ((iTemp103) ? 0 : 1);
			int iTemp109 = iTemp83 != iVec14[1];
			iVec15[IOTA0 & 32767] = iTemp109;
			int iTemp110 = static_cast<int>((((iTemp83 % 2) == 1) ? fSlow79 * static_cast<float>(iVec15[(IOTA0 - iSlow78) & 32767]) + fSlow77 * static_cast<float>(iVec15[(IOTA0 - iSlow75) & 32767]) : static_cast<float>(iTemp109))) & (((iSlow63) ? ((iSlow71) ? ((iTemp84) ? ((iTemp91) ? 1 : ((iTemp92) ? iTemp93 : 1)) : ((iTemp85) ? ((iTemp89) ? iTemp90 : 1) : ((iTemp86) ? iTemp88 : 1))) : ((iSlow72) ? ((iTemp84) ? ((iTemp91) ? ((iTemp94) ? 1 : iTemp104) : ((iTemp92) ? 1 : iTemp107)) : ((iTemp85) ? iTemp100 : ((iTemp86) ? 1 : iTemp105))) : ((iTemp84) ? ((iTemp91) ? ((iTemp94) ? ((iTemp95) ? 1 : 0) : iTemp108) : iTemp102) : ((iTemp85) ? iTemp106 : ((iTemp86) ? ((iTemp87) ? 1 : 0) : iTemp98))))) : ((iSlow64) ? ((iSlow70) ? ((iTemp84) ? ((iTemp91) ? ((iTemp94) ? iTemp96 : iTemp108) : ((iTemp92) ? iTemp93 : iTemp107)) : ((iTemp85) ? iTemp106 : ((iTemp86) ? iTemp88 : iTemp105))) : ((iTemp84) ? ((iTemp91) ? ((iTemp94) ? 1 : 0) : ((iTemp92) ? 1 : 0)) : ((iTemp85) ? ((iTemp89) ? 1 : 0) : ((iTemp86) ? 1 : 0)))) : ((iSlow65) ? ((iTemp84) ? ((iTemp91) ? ((iTemp94) ? iTemp96 : iTemp104) : iTemp102) : ((iTemp85) ? iTemp100 : ((iTemp86) ? iTemp88 : iTemp98))) : ((iTemp84) ? ((iTemp91) ? ((iTemp94) ? iTemp96 : 0) : ((iTemp92) ? iTemp93 : 0)) : ((iTemp85) ? ((iTemp89) ? iTemp90 : 0) : ((iTemp86) ? iTemp88 : 0)))))) > 0);
			iVec16[0] = iTemp110;
			fRec31[0] = (fConst18 + fRec31[1]) * (1.0f - static_cast<float>(iTemp110));
			fRec30[0] = fConst51 * std::exp(-(fSlow80 * fRec31[0])) + fConst50 * fRec30[1];
			iRec34[0] = (iRec34[1] + (iRec34[1] > 0)) * (iTemp110 <= iVec16[1]) + (iTemp110 > iVec16[1]);
			float fTemp111 = static_cast<float>(iRec34[0]);
			iRec36[0] = 1103515245 * iRec36[1] + 12345;
			float fTemp112 = static_cast<float>(iRec36[0]);
			fVec17[0] = fTemp112;
			fRec35[0] = fConst57 * (4.656613e-10f * (fTemp112 + fVec17[1]) - fConst56 * fRec35[1]);
			fRec38[0] = fConst59 + fRec38[1] * static_cast<float>(1 - iTemp110);
			float fTemp113 = std::max<float>(0.01f, 0.6f - 0.15f * (fSlow82 - fSlow90 * std::sin(6.2831855f * (fRec38[0] - std::floor(fRec38[0])))));
			fRec37[0] = fRec37[1] * (1.0f - fTemp113) + fTemp113 * (fSlow89 * fRec33[(IOTA0 - iSlow88) & 8191] + fSlow87 * fRec33[(IOTA0 - iSlow85) & 8191]);
			fRec33[IOTA0 & 8191] = fSlow92 * (fRec37[0] / (fSlow91 * std::fabs(fRec37[0]) + 1.0f)) + fRec35[0] * std::max<float>(0.0f, std::min<float>(fConst53 * fTemp111, fConst54 * (fConst52 - fTemp111) + 1.0f)) * (((((iTemp83 == 0) | (iTemp83 == 4)) | (iTemp83 == 8)) | (iTemp83 == 12)) ? fSlow81 : 1.0f);
			fRec29[0] = fRec33[IOTA0 & 8191] * fRec30[0] - fConst49 * (fConst47 * fRec29[2] + fConst45 * fRec29[1]);
			fRec28[0] = fConst60 * (fRec29[2] + (fRec29[0] - 2.0f * fRec29[1])) - fConst42 * (fConst41 * fRec28[2] + fConst39 * fRec28[1]);
			float fTemp114 = ((iTemp28) ? 0.0f : fSlow106 + fRec40[1]);
			fRec40[0] = fTemp114 - std::floor(fTemp114);
			float fTemp115 = mydsp_faustpower2_f(2.0f * fRec40[0] + -1.0f);
			fVec18[0] = fTemp115;
			float fTemp116 = fTemp115 - fVec18[1];
			float fTemp117 = fSlow107 * fTemp34 * fTemp116;
			fVec19[IOTA0 & 127] = fTemp117;
			float fTemp118 = ((iTemp28) ? 0.0f : fSlow114 + fRec41[1]);
			fRec41[0] = fTemp118 - std::floor(fTemp118);
			float fTemp119 = mydsp_faustpower2_f(2.0f * fRec41[0] + -1.0f);
			fVec20[0] = fTemp119;
			float fTemp120 = fTemp119 - fVec20[1];
			float fTemp121 = fSlow115 * fTemp34 * fTemp120;
			fVec21[IOTA0 & 127] = fTemp121;
			float fTemp122 = ((iTemp28) ? 0.0f : fSlow122 + fRec42[1]);
			fRec42[0] = fTemp122 - std::floor(fTemp122);
			float fTemp123 = mydsp_faustpower2_f(2.0f * fRec42[0] + -1.0f);
			fVec22[0] = fTemp123;
			float fTemp124 = fTemp123 - fVec22[1];
			float fTemp125 = fSlow123 * fTemp34 * fTemp124;
			fVec23[IOTA0 & 127] = fTemp125;
			float fTemp126 = ((iTemp28) ? 0.0f : fSlow130 + fRec43[1]);
			fRec43[0] = fTemp126 - std::floor(fTemp126);
			float fTemp127 = mydsp_faustpower2_f(2.0f * fRec43[0] + -1.0f);
			fVec24[0] = fTemp127;
			float fTemp128 = fTemp127 - fVec24[1];
			float fTemp129 = fSlow131 * fTemp34 * fTemp128;
			fVec25[IOTA0 & 255] = fTemp129;
			float fTemp130 = ((iTemp28) ? 0.0f : fSlow138 + fRec44[1]);
			fRec44[0] = fTemp130 - std::floor(fTemp130);
			float fTemp131 = mydsp_faustpower2_f(2.0f * fRec44[0] + -1.0f);
			fVec26[0] = fTemp131;
			float fTemp132 = fTemp131 - fVec26[1];
			float fTemp133 = fSlow139 * fTemp34 * fTemp132;
			fVec27[IOTA0 & 255] = fTemp133;
			float fTemp134 = ((iTemp28) ? 0.0f : fSlow146 + fRec45[1]);
			fRec45[0] = fTemp134 - std::floor(fTemp134);
			float fTemp135 = mydsp_faustpower2_f(2.0f * fRec45[0] + -1.0f);
			fVec28[0] = fTemp135;
			float fTemp136 = fTemp135 - fVec28[1];
			float fTemp137 = fSlow147 * fTemp34 * fTemp136;
			fVec29[IOTA0 & 511] = fTemp137;
			float fTemp138 = fSlow170 * (fConst62 * fTemp34 * (fSlow169 * fTemp136 + fSlow168 * fTemp132 + fSlow167 * fTemp128 + fSlow166 * fTemp124 + fSlow165 * fTemp120 + fSlow164 * fTemp116) - (fSlow163 * fVec19[(IOTA0 - iSlow162) & 127] + fSlow161 * fVec21[(IOTA0 - iSlow160) & 127] + fSlow159 * fVec23[(IOTA0 - iSlow158) & 127] + fSlow157 * fVec25[(IOTA0 - iSlow156) & 255] + fSlow155 * fVec27[(IOTA0 - iSlow154) & 255] + fSlow153 * fVec29[(IOTA0 - iSlow149) & 511] + fSlow152 * fVec29[(IOTA0 - iSlow150) & 511] + fSlow143 * fVec27[(IOTA0 - iSlow141) & 255] + fSlow135 * fVec25[(IOTA0 - iSlow133) & 255] + fSlow127 * fVec23[(IOTA0 - iSlow125) & 127] + fSlow119 * fVec21[(IOTA0 - iSlow117) & 127] + fSlow111 * fVec19[(IOTA0 - iSlow109) & 127])) + fSlow102 * fTemp112;
			fVec30[0] = fSlow172;
			iRec46[0] = (iRec46[1] + 1) * (1 - (fSlow172 != fVec30[1]));
			int iTemp139 = static_cast<int>(fSlow174 * static_cast<float>(iRec46[0])) % 16;
			iVec31[0] = iTemp139;
			int iTemp140 = iTemp139 >= 8;
			int iTemp141 = iTemp139 >= 4;
			int iTemp142 = iTemp139 >= 2;
			int iTemp143 = iTemp139 >= 3;
			int iTemp144 = ((iTemp143) ? 0 : 1);
			int iTemp145 = iTemp139 >= 6;
			int iTemp146 = iTemp139 >= 7;
			int iTemp147 = ((iTemp146) ? 0 : 1);
			int iTemp148 = iTemp139 >= 12;
			int iTemp149 = iTemp139 >= 10;
			int iTemp150 = iTemp139 >= 11;
			int iTemp151 = ((iTemp150) ? 0 : 1);
			int iTemp152 = iTemp139 >= 14;
			int iTemp153 = ((iTemp139 >= 15) ? 0 : 1);
			int iTemp154 = ((iTemp152) ? iTemp153 : 0);
			int iTemp155 = iTemp139 >= 1;
			int iTemp156 = iTemp139 >= 5;
			int iTemp157 = ((iTemp156) ? 1 : 0);
			int iTemp158 = ((iTemp145) ? iTemp147 : iTemp157);
			int iTemp159 = iTemp139 >= 9;
			int iTemp160 = ((iTemp152) ? iTemp153 : ((iTemp139 >= 13) ? 1 : 0));
			int iTemp161 = ((iTemp155) ? 0 : 1);
			int iTemp162 = ((iTemp146) ? 1 : 0);
			int iTemp163 = ((iTemp149) ? ((iTemp150) ? 1 : 0) : 1);
			int iTemp164 = iTemp139 != iVec31[1];
			iVec32[IOTA0 & 32767] = iTemp164;
			int iTemp165 = static_cast<int>((((iTemp139 % 2) == 1) ? fSlow189 * static_cast<float>(iVec32[(IOTA0 - iSlow188) & 32767]) + fSlow187 * static_cast<float>(iVec32[(IOTA0 - iSlow185) & 32767]) : static_cast<float>(iTemp164))) & (((iSlow177) ? ((iSlow181) ? ((iTemp140) ? 1 : ((iTemp141) ? ((iTemp145) ? 1 : ((iTemp156) ? 0 : 1)) : 1)) : ((iSlow182) ? ((iTemp140) ? ((iTemp148) ? 1 : iTemp163) : ((iTemp141) ? ((iTemp145) ? iTemp162 : 1) : ((iTemp142) ? ((iTemp143) ? 1 : 0) : 1))) : ((iTemp140) ? ((iTemp148) ? iTemp160 : iTemp163) : ((iTemp141) ? ((iTemp145) ? iTemp162 : iTemp157) : ((iTemp142) ? 1 : iTemp161))))) : ((iSlow178) ? ((iSlow180) ? 1 : ((iTemp140) ? ((iTemp148) ? iTemp154 : ((iTemp149) ? 1 : ((iTemp159) ? 0 : 1))) : ((iTemp141) ? iTemp158 : ((iTemp142) ? iTemp144 : iTemp161)))) : ((iSlow179) ? ((iTemp140) ? ((iTemp148) ? iTemp160 : ((iTemp149) ? iTemp151 : ((iTemp159) ? 1 : 0))) : ((iTemp141) ? iTemp158 : ((iTemp142) ? iTemp144 : ((iTemp155) ? 1 : 0)))) : ((iTemp140) ? ((iTemp148) ? iTemp154 : ((iTemp149) ? iTemp151 : 0)) : ((iTemp141) ? ((iTemp145) ? iTemp147 : 0) : ((iTemp142) ? iTemp144 : 0)))))) > 0);
			iVec33[0] = iTemp165;
			iRec47[0] = (iRec47[1] + (iRec47[1] > 0)) * (iTemp165 <= iVec33[1]) + (iTemp165 > iVec33[1]);
			float fTemp166 = static_cast<float>(iRec47[0]);
			fRec39[0] = fTemp138 * std::max<float>(0.0f, std::min<float>(fSlow191 * fTemp166, fSlow192 * (fSlow190 - fTemp166) + 1.0f)) * (((((iTemp139 == 0) | (iTemp139 == 4)) | (iTemp139 == 8)) | (iTemp139 == 12)) ? fSlow175 : 1.0f) / (fSlow171 * std::fabs(fTemp138) + 1.0f) - fSlow100 * (fSlow98 * fRec39[2] + fSlow96 * fRec39[1]);
			fVec34[0] = fSlow205;
			iRec51[0] = (iRec51[1] + 1) * (1 - (fSlow205 != fVec34[1]));
			int iTemp167 = static_cast<int>(fSlow207 * static_cast<float>(iRec51[0])) % 16;
			iVec35[0] = iTemp167;
			int iTemp168 = iTemp167 >= 8;
			int iTemp169 = iTemp167 >= 4;
			int iTemp170 = iTemp167 >= 6;
			int iTemp171 = ((iTemp167 >= 5) ? 0 : 1);
			int iTemp172 = ((iTemp170) ? 0 : iTemp171);
			int iTemp173 = ((iTemp169) ? iTemp172 : 0);
			int iTemp174 = iTemp167 >= 12;
			int iTemp175 = iTemp167 >= 14;
			int iTemp176 = ((iTemp167 >= 13) ? 0 : 1);
			int iTemp177 = ((iTemp175) ? 0 : iTemp176);
			int iTemp178 = iTemp167 >= 10;
			int iTemp179 = iTemp167 >= 11;
			int iTemp180 = ((iTemp179) ? 0 : 1);
			int iTemp181 = ((iTemp178) ? iTemp180 : 0);
			int iTemp182 = iTemp167 >= 2;
			int iTemp183 = ((iTemp167 >= 3) ? 0 : 1);
			int iTemp184 = ((iTemp182) ? iTemp183 : 0);
			int iTemp185 = iTemp167 >= 9;
			int iTemp186 = ((iTemp185) ? 1 : 0);
			int iTemp187 = ((iTemp167 >= 7) ? 1 : 0);
			int iTemp188 = ((iTemp170) ? iTemp187 : iTemp171);
			int iTemp189 = iTemp167 >= 15;
			int iTemp190 = ((iTemp175) ? ((iTemp189) ? 0 : 1) : iTemp176);
			int iTemp191 = iTemp167 != iVec35[1];
			iVec36[IOTA0 & 32767] = iTemp191;
			int iTemp192 = static_cast<int>((((iTemp167 % 2) == 1) ? fSlow217 * static_cast<float>(iVec36[(IOTA0 - iSlow216) & 32767]) + fSlow215 * static_cast<float>(iVec36[(IOTA0 - iSlow213) & 32767]) : static_cast<float>(iTemp191))) & (((iSlow202) ? ((iSlow209) ? ((iTemp168) ? ((iTemp174) ? 1 : ((iTemp178) ? iTemp180 : ((iTemp185) ? 0 : 1))) : ((iTemp169) ? ((iTemp170) ? iTemp187 : 1) : ((iTemp182) ? iTemp183 : ((iTemp167 >= 1) ? 0 : 1)))) : ((iSlow210) ? ((iTemp168) ? ((iTemp174) ? iTemp190 : ((iTemp178) ? ((iTemp179) ? 1 : 0) : iTemp186)) : ((iTemp169) ? iTemp188 : ((iTemp182) ? 1 : 0))) : ((iTemp168) ? ((iTemp174) ? ((iTemp175) ? ((iTemp189) ? 1 : 0) : iTemp176) : iTemp181) : ((iTemp169) ? iTemp188 : iTemp184)))) : ((iSlow203) ? ((iSlow208) ? ((iTemp168) ? ((iTemp174) ? iTemp190 : 0) : ((iTemp169) ? iTemp188 : 0)) : ((iTemp168) ? ((iTemp174) ? iTemp177 : ((iTemp178) ? 0 : iTemp186)) : ((iTemp169) ? iTemp172 : iTemp184))) : ((iSlow204) ? ((iTemp168) ? ((iTemp174) ? iTemp177 : iTemp181) : iTemp173) : ((iTemp168) ? ((iTemp174) ? iTemp177 : 0) : iTemp173)))) > 0);
			iVec37[0] = iTemp192;
			iRec50[0] = (iRec50[1] + (iRec50[1] > 0)) * (iTemp192 <= iVec37[1]) + (iTemp192 > iVec37[1]);
			float fTemp193 = static_cast<float>(iRec50[0]);
			fRec52[0] = 4.656613e-10f * fTemp112 - fSlow225 * (fSlow223 * fRec52[2] + fSlow220 * fRec52[1]);
			float fTemp194 = ((iTemp28) ? 0.0f : fSlow230 + fRec53[1]);
			fRec53[0] = fTemp194 - std::floor(fTemp194);
			float fTemp195 = ((iTemp28) ? 0.0f : fSlow231 + fRec54[1]);
			fRec54[0] = fTemp195 - std::floor(fTemp195);
			fRec49[0] = fSlow234 * (((((iTemp167 == 0) | (iTemp167 == 4)) | (iTemp167 == 8)) | (iTemp167 == 12)) ? fSlow233 : 1.0f) * (fSlow232 * (0.65f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec54[0]), 65535))] + 0.35f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec53[0]), 65535))]) * std::max<float>(0.0f, std::min<float>(fConst69 * fTemp193, fSlow228 * (fConst68 - fTemp193) + 1.0f)) + fSlow227 * (fRec52[0] - fRec52[2]) * std::max<float>(0.0f, std::min<float>(fConst53 * fTemp193, fSlow218 * (fConst52 - fTemp193) + 1.0f))) - fSlow200 * (fSlow198 * fRec49[2] + fSlow196 * fRec49[1]);
			fRec48[0] = fSlow235 * (fRec49[2] + (fRec49[0] - 2.0f * fRec49[1])) - fConst67 * (fConst66 * fRec48[2] + fConst64 * fRec48[1]);
			fVec38[0] = fSlow239;
			iRec69[0] = (iRec69[1] + 1) * (1 - (fSlow239 != fVec38[1]));
			int iTemp196 = static_cast<int>(fSlow241 * static_cast<float>(iRec69[0])) % 16;
			iVec39[0] = iTemp196;
			int iTemp197 = iTemp196 >= 8;
			int iTemp198 = iTemp196 >= 4;
			int iTemp199 = iTemp196 >= 2;
			int iTemp200 = ((iTemp196 >= 1) ? 0 : 1);
			int iTemp201 = ((iTemp199) ? 0 : iTemp200);
			int iTemp202 = iTemp196 >= 6;
			int iTemp203 = ((iTemp196 >= 5) ? 0 : 1);
			int iTemp204 = ((iTemp198) ? ((iTemp202) ? 0 : iTemp203) : iTemp201);
			int iTemp205 = iTemp196 >= 12;
			int iTemp206 = iTemp196 >= 10;
			int iTemp207 = ((iTemp196 >= 9) ? 0 : 1);
			int iTemp208 = ((iTemp206) ? 0 : iTemp207);
			int iTemp209 = iTemp196 >= 14;
			int iTemp210 = ((iTemp196 >= 13) ? 0 : 1);
			int iTemp211 = ((iTemp209) ? 0 : iTemp210);
			int iTemp212 = iTemp196 >= 15;
			int iTemp213 = ((iTemp205) ? ((iTemp209) ? ((iTemp212) ? 0 : 1) : iTemp210) : iTemp208);
			int iTemp214 = iTemp196 >= 7;
			int iTemp215 = ((iTemp202) ? ((iTemp214) ? 1 : 0) : iTemp203);
			int iTemp216 = ((iTemp198) ? iTemp215 : iTemp201);
			int iTemp217 = ((iTemp214) ? 0 : 1);
			int iTemp218 = iTemp196 >= 3;
			int iTemp219 = iTemp196 != iVec39[1];
			iVec40[IOTA0 & 32767] = iTemp219;
			int iTemp220 = static_cast<int>((((iTemp196 % 2) == 1) ? fSlow256 * static_cast<float>(iVec40[(IOTA0 - iSlow255) & 32767]) + fSlow254 * static_cast<float>(iVec40[(IOTA0 - iSlow252) & 32767]) : static_cast<float>(iTemp219))) & (((iSlow244) ? ((iSlow248) ? ((iTemp197) ? ((iTemp205) ? ((iTemp209) ? 0 : 1) : ((iTemp206) ? ((iTemp196 >= 11) ? 0 : 1) : iTemp207)) : ((iTemp198) ? iTemp215 : ((iTemp199) ? ((iTemp218) ? 0 : 1) : iTemp200))) : ((iSlow249) ? ((iTemp197) ? iTemp213 : iTemp216) : ((iTemp197) ? ((iTemp205) ? ((iTemp209) ? ((iTemp212) ? 1 : 0) : iTemp210) : iTemp208) : ((iTemp198) ? ((iTemp202) ? iTemp217 : 0) : ((iTemp199) ? ((iTemp218) ? 1 : 0) : iTemp200))))) : ((iSlow245) ? ((iSlow247) ? ((iTemp197) ? iTemp213 : ((iTemp198) ? ((iTemp202) ? iTemp217 : iTemp203) : iTemp201)) : ((iTemp197) ? ((iTemp205) ? iTemp211 : 0) : iTemp216)) : ((iSlow246) ? ((iTemp197) ? iTemp213 : iTemp204) : ((iTemp197) ? ((iTemp205) ? iTemp211 : iTemp208) : iTemp204)))) > 0);
			iVec41[0] = iTemp220;
			iRec70[0] = (iRec70[1] + (iRec70[1] > 0)) * (iTemp220 <= iVec41[1]) + (iTemp220 > iVec41[1]);
			float fTemp221 = static_cast<float>(iRec70[0]);
			float fTemp222 = fConst53 * fTemp221;
			float fTemp223 = fConst52 - fTemp221;
			float fTemp224 = ((iTemp28) ? 0.0f : fRec71[1] + fConst18 * (fSlow259 + fSlow258 * std::pow(std::max<float>(0.0f, std::min<float>(fTemp222, fConst16 * fTemp223 + 1.0f)), 1.5f)));
			fRec71[0] = fTemp224 - std::floor(fTemp224);
			float fTemp225 = ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec71[0]), 65535))] * std::max<float>(0.0f, std::min<float>(fTemp222, fSlow257 * fTemp223 + 1.0f)) * (((((iTemp196 == 0) | (iTemp196 == 4)) | (iTemp196 == 8)) | (iTemp196 == 12)) ? fSlow242 : 1.0f);
			fRec68[0] = fConst83 * std::fabs(fTemp225) + fConst82 * fRec68[1];
			float fTemp226 = std::max<float>(0.0f, fRec68[0] - fSlow238);
			float fTemp227 = 1.0f / std::tan(fConst61 * std::max<float>(fSlow237, fSlow260 - fSlow262 * fTemp226));
			float fTemp228 = tanhf(fSlow263 * (fTemp225 / (fSlow261 * fTemp226 + 1.0f)));
			fVec42[0] = fTemp228;
			fRec67[0] = -((fRec67[1] * (1.0f - fTemp227) - (fTemp228 + fVec42[1])) / (fTemp227 + 1.0f));
			fRec66[0] = fRec67[0] - fConst81 * (fConst80 * fRec66[2] + fConst78 * fRec66[1]);
			fRec65[0] = fConst81 * (fRec66[2] + fRec66[0] + 2.0f * fRec66[1]) - fConst49 * (fConst47 * fRec65[2] + fConst45 * fRec65[1]);
			float fTemp229 = fRec65[2] + (fRec65[0] - 2.0f * fRec65[1]);
			fRec64[0] = fConst60 * fTemp229 - fConst12 * (fConst10 * fRec64[2] + fConst8 * fRec64[1]);
			fRec63[0] = fConst21 * (fRec64[2] + (fRec64[0] - 2.0f * fRec64[1])) - fConst76 * (fConst75 * fRec63[2] + fConst73 * fRec63[1]);
			float fTemp230 = fConst76 * (fRec63[2] + fRec63[0] + 2.0f * fRec63[1]);
			fRec72[0] = -(fConst85 * (fConst84 * fRec72[1] - (fRec62[(IOTA0 - 702) & 1023] + fRec62[(IOTA0 - 703) & 1023])));
			float fTemp231 = tanhf(fRec72[0]);
			fRec73[0] = -(fConst85 * (fConst84 * fRec73[1] - (fRec61[(IOTA0 - 594) & 1023] + fRec61[(IOTA0 - 595) & 1023])));
			float fTemp232 = tanhf(fRec73[0]);
			fRec74[0] = -(fConst85 * (fConst84 * fRec74[1] - (fRec60[(IOTA0 - 462) & 511] + fRec60[(IOTA0 - 463) & 511])));
			float fTemp233 = tanhf(fRec74[0]);
			fRec75[0] = -(fConst85 * (fConst84 * fRec75[1] - (fRec59[(IOTA0 - 348) & 511] + fRec59[(IOTA0 - 349) & 511])));
			float fTemp234 = tanhf(fRec75[0]);
			float fTemp235 = fTemp234 + fTemp233;
			fRec59[IOTA0 & 511] = 0.75f * (0.5f * (fTemp235 + fTemp232 + fTemp231) + fTemp230);
			fRec60[IOTA0 & 511] = 0.75f * (fTemp230 + 0.5f * (fTemp234 + fTemp232 - (fTemp233 + fTemp231)));
			fRec61[IOTA0 & 1023] = 0.75f * (fTemp230 + 0.5f * (fTemp235 - (fTemp232 + fTemp231)));
			fRec62[IOTA0 & 1023] = 0.75f * (fTemp230 + 0.5f * (fTemp234 + fTemp231 - (fTemp233 + fTemp232)));
			float fTemp236 = fRec59[IOTA0 & 511] + fRec60[IOTA0 & 511] + fRec61[IOTA0 & 1023] + fRec62[IOTA0 & 1023] - 0.5f * fRec57[1];
			fVec43[IOTA0 & 255] = fTemp236;
			fRec57[0] = fVec43[(IOTA0 - 130) & 255];
			float fRec58 = 0.5f * fTemp236;
			float fTemp237 = fRec58 + fRec57[1] - 0.5f * fRec55[1];
			fVec44[IOTA0 & 255] = fTemp237;
			fRec55[0] = fVec44[(IOTA0 - 190) & 255];
			float fRec56 = 0.5f * fTemp237;
			float fTemp238 = fSlow267 * (fSlow266 * fTemp229 + fSlow265 * (fRec56 + fRec55[1])) + fSlow236 * tanhf(fConst67 * (fRec48[2] + fRec48[0] + 2.0f * fRec48[1])) + fSlow193 * (fRec39[2] + (fRec39[0] - 2.0f * fRec39[1])) + fSlow93 * (fRec28[2] + fRec28[0] + 2.0f * fRec28[1]) + fSlow61 * (fRec12[2] + fRec12[0] + 2.0f * fRec12[1]);
			float fTemp239 = tanhf(1.5f * (fTemp238 + fSlow25 * std::sqrt(1.0f - fRec11[0]) * fTemp44));
			fVec45[0] = fTemp239;
			fRec0[0] = 0.995f * fRec0[1] + fTemp239 - fVec45[1];
			output0[i0] = static_cast<FAUSTFLOAT>(fRec0[0]);
			float fTemp240 = std::sin(3.1415927f * fRec11[0]);
			float fTemp241 = std::tan(fConst61 * (fSlow268 * fTemp240 + 4e+02f));
			float fTemp242 = 1.0f / fTemp241;
			float fTemp243 = (fSlow269 + fTemp242) / fTemp241 + 1.0f;
			float fTemp244 = fSlow270 * fTemp240;
			float fTemp245 = fTemp244 + 1e+02f;
			int iTemp246 = static_cast<int>(fTemp245);
			float fTemp247 = std::floor(fTemp245);
			fRec77[0] = fConst5 * (fVec8[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp246))) & 255] * (fTemp247 + (-99.0f - fTemp244)) + (fTemp244 + (1e+02f - fTemp247)) * fVec8[(IOTA0 - std::min<int>(4097, std::max<int>(0, iTemp246 + 1))) & 255]) - (fRec77[2] * ((fTemp242 - fSlow269) / fTemp241 + 1.0f) + 2.0f * fRec77[1] * (1.0f - 1.0f / mydsp_faustpower2_f(fTemp241))) / fTemp243;
			float fTemp248 = tanhf(1.5f * (fTemp238 + fSlow271 * (std::sqrt(fRec11[0]) * (fRec77[0] - fRec77[2]) / (fTemp241 * fTemp243))));
			fVec46[0] = fTemp248;
			fRec76[0] = 0.995f * fRec76[1] + fTemp248 - fVec46[1];
			output1[i0] = static_cast<FAUSTFLOAT>(fRec76[0]);
			iVec0[1] = iVec0[0];
			fVec1[1] = fVec1[0];
			iRec3[1] = iRec3[0];
			iVec2[1] = iVec2[0];
			IOTA0 = IOTA0 + 1;
			iVec4[1] = iVec4[0];
			iRec4[1] = iRec4[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fVec6[1] = fVec6[0];
			fRec10[1] = fRec10[0];
			fRec8[1] = fRec8[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec11[1] = fRec11[0];
			fRec16[1] = fRec16[0];
			fVec9[1] = fVec9[0];
			iRec22[1] = iRec22[0];
			iVec10[1] = iVec10[0];
			iVec12[1] = iVec12[0];
			iRec23[1] = iRec23[0];
			fRec21[1] = fRec21[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fVec13[1] = fVec13[0];
			iRec32[1] = iRec32[0];
			iVec14[1] = iVec14[0];
			iVec16[1] = iVec16[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			iRec34[1] = iRec34[0];
			iRec36[1] = iRec36[0];
			fVec17[1] = fVec17[0];
			fRec35[1] = fRec35[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec40[1] = fRec40[0];
			fVec18[1] = fVec18[0];
			fRec41[1] = fRec41[0];
			fVec20[1] = fVec20[0];
			fRec42[1] = fRec42[0];
			fVec22[1] = fVec22[0];
			fRec43[1] = fRec43[0];
			fVec24[1] = fVec24[0];
			fRec44[1] = fRec44[0];
			fVec26[1] = fVec26[0];
			fRec45[1] = fRec45[0];
			fVec28[1] = fVec28[0];
			fVec30[1] = fVec30[0];
			iRec46[1] = iRec46[0];
			iVec31[1] = iVec31[0];
			iVec33[1] = iVec33[0];
			iRec47[1] = iRec47[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fVec34[1] = fVec34[0];
			iRec51[1] = iRec51[0];
			iVec35[1] = iVec35[0];
			iVec37[1] = iVec37[0];
			iRec50[1] = iRec50[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec53[1] = fRec53[0];
			fRec54[1] = fRec54[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fVec38[1] = fVec38[0];
			iRec69[1] = iRec69[0];
			iVec39[1] = iVec39[0];
			iVec41[1] = iVec41[0];
			iRec70[1] = iRec70[0];
			fRec71[1] = fRec71[0];
			fRec68[1] = fRec68[0];
			fVec42[1] = fVec42[0];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec72[1] = fRec72[0];
			fRec73[1] = fRec73[0];
			fRec74[1] = fRec74[0];
			fRec75[1] = fRec75[0];
			fRec57[1] = fRec57[0];
			fRec55[1] = fRec55[0];
			fVec45[1] = fVec45[0];
			fRec0[1] = fRec0[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fVec46[1] = fVec46[0];
			fRec76[1] = fRec76[0];
		}
	}

};

#endif
