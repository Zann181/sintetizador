/* ------------------------------------------------------------
name: "untitled"
Code generated with Faust 2.81.10 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
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
	
	int iVec2[2];
	int iRec1[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			iVec2[l3] = 0;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iRec1[l4] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec2[0] = 1;
			iRec1[0] = (iVec2[1] + iRec1[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec1[0]));
			iVec2[1] = iVec2[0];
			iRec1[1] = iRec1[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];
static float mydsp_faustpower2_f(float value) {
	return value * value;
}

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fCheckbox0;
	float fVec0[2];
	int iVec1[2];
	int iRec0[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fConst3;
	float fRec2[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fConst4;
	FAUSTFLOAT fHslider4;
	float fRec5[2];
	float fConst5;
	float fConst6;
	FAUSTFLOAT fHslider5;
	int iRec6[2];
	float fConst7;
	FAUSTFLOAT fHslider6;
	float fRec4[2];
	FAUSTFLOAT fHslider7;
	FAUSTFLOAT fHslider8;
	float fRec3[3];
	FAUSTFLOAT fHslider9;
	int IOTA0;
	float fVec3[2048];
	int iConst8;
	FAUSTFLOAT fHslider10;
	float fConst9;
	int iRec9[2];
	float fRec10[2];
	float fRec8[2];
	FAUSTFLOAT fHslider11;
	float fRec7[2];
	FAUSTFLOAT fHslider12;
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/peakholder:author", "Dario Sanfilippo");
		m->declare("basics.lib/peakholder:copyright", "Copyright (C) 2022 Dario Sanfilippo <sanfilippo.dario@gmail.com>");
		m->declare("basics.lib/peakholder:license", "MIT-style STK-4.3 license");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("compressors.lib/limiter_lad_N:author", "Dario Sanfilippo");
		m->declare("compressors.lib/limiter_lad_N:copyright", "Copyright (C) 2020 Dario Sanfilippo       <sanfilippo.dario@gmail.com>");
		m->declare("compressors.lib/limiter_lad_N:license", "GPLv3 license");
		m->declare("compressors.lib/limiter_lad_stereo:author", "Dario Sanfilippo");
		m->declare("compressors.lib/limiter_lad_stereo:copyright", "Copyright (C) 2020 Dario Sanfilippo       <sanfilippo.dario@gmail.com>");
		m->declare("compressors.lib/limiter_lad_stereo:license", "GPLv3 license");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "1.6.0");
		m->declare("envelopes.lib/adsr:author", "Yann Orlarey and Andrey Bundin");
		m->declare("envelopes.lib/ar:author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "1.3.0");
		m->declare("filename", "untitled.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/resonlp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonlp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonlp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("name", "untitled");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "1.2.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
		m->declare("synths.lib/name", "Faust Synthesizer Library");
		m->declare("synths.lib/version", "1.1.0");
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
		fConst1 = std::max<float>(1.0f, 0.001f * fConst0);
		fConst2 = 1.0f / fConst1;
		fConst3 = 1.0f / fConst0;
		fConst4 = 3.1415927f / fConst0;
		fConst5 = std::max<float>(1.0f, 0.005f * fConst0);
		fConst6 = 1.0f / fConst5;
		fConst7 = 1.0f / std::max<float>(1.0f, 0.1f * fConst0);
		iConst8 = static_cast<int>(0.01f * fConst0);
		fConst9 = 0.05f * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(0.6f);
		fHslider1 = static_cast<FAUSTFLOAT>(48.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(0.55f);
		fHslider3 = static_cast<FAUSTFLOAT>(55.0f);
		fHslider4 = static_cast<FAUSTFLOAT>(12.0f);
		fHslider5 = static_cast<FAUSTFLOAT>(0.68f);
		fHslider6 = static_cast<FAUSTFLOAT>(52.0f);
		fHslider7 = static_cast<FAUSTFLOAT>(0.5f);
		fHslider8 = static_cast<FAUSTFLOAT>(7.5f);
		fHslider9 = static_cast<FAUSTFLOAT>(0.4f);
		fHslider10 = static_cast<FAUSTFLOAT>(0.002f);
		fHslider11 = static_cast<FAUSTFLOAT>(0.15f);
		fHslider12 = static_cast<FAUSTFLOAT>(0.97f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iVec1[l1] = 0;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec0[l2] = 0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec5[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec6[l7] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec4[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec3[l9] = 0.0f;
		}
		IOTA0 = 0;
		for (int l10 = 0; l10 < 2048; l10 = l10 + 1) {
			fVec3[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			iRec9[l11] = 0;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec10[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec8[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec7[l14] = 0.0f;
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
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("KICK FUNK TRIBU");
		ui_interface->declare(0, "0", "");
		ui_interface->openVerticalBox("Core");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "osc", "/kick/gate 0 1");
		ui_interface->declare(&fCheckbox0, "style", "toggle");
		ui_interface->addCheckButton("gate", &fCheckbox0);
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "osc", "/kick/pitch 30 100");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->declare(&fHslider6, "unit", "Hz");
		ui_interface->addHorizontalSlider("pitch", &fHslider6, FAUSTFLOAT(52.0f), FAUSTFLOAT(3e+01f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "osc", "/kick/click 0.005 1");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("click", &fHslider5, FAUSTFLOAT(0.68f), FAUSTFLOAT(0.005f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider7, "3", "");
		ui_interface->declare(&fHslider7, "osc", "/kick/decay 0.1 1.5");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->declare(&fHslider7, "unit", "s");
		ui_interface->addHorizontalSlider("decay", &fHslider7, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1.5f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider8, "4", "");
		ui_interface->declare(&fHslider8, "osc", "/kick/drive 1 10");
		ui_interface->declare(&fHslider8, "style", "knob");
		ui_interface->addHorizontalSlider("drive", &fHslider8, FAUSTFLOAT(7.5f), FAUSTFLOAT(1.0f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("Sub Boost");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "osc", "/kick/sub/freq 20 90");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fHslider1, FAUSTFLOAT(48.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(9e+01f), FAUSTFLOAT(0.5f));
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "osc", "/kick/sub/gain 0 1");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fHslider2, FAUSTFLOAT(0.55f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->declare(&fHslider0, "osc", "/kick/sub/decay 0.05 1.2");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "unit", "s");
		ui_interface->addHorizontalSlider("decay", &fHslider0, FAUSTFLOAT(0.6f), FAUSTFLOAT(0.05f), FAUSTFLOAT(1.2f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("Resonancia");
		ui_interface->declare(&fHslider3, "0", "");
		ui_interface->declare(&fHslider3, "osc", "/kick/res/freq 30 120");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->declare(&fHslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fHslider3, FAUSTFLOAT(55.0f), FAUSTFLOAT(3e+01f), FAUSTFLOAT(1.2e+02f), FAUSTFLOAT(0.5f));
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "osc", "/kick/res/q 1 20");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Q", &fHslider4, FAUSTFLOAT(12.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider9, "2", "");
		ui_interface->declare(&fHslider9, "osc", "/kick/res/mix 0 1");
		ui_interface->declare(&fHslider9, "style", "knob");
		ui_interface->addHorizontalSlider("mix", &fHslider9, FAUSTFLOAT(0.4f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("Limiter");
		ui_interface->declare(&fHslider12, "0", "");
		ui_interface->declare(&fHslider12, "osc", "/kick/lim/ceiling 0.5 1");
		ui_interface->declare(&fHslider12, "style", "knob");
		ui_interface->addHorizontalSlider("ceiling", &fHslider12, FAUSTFLOAT(0.97f), FAUSTFLOAT(0.5f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider10, "1", "");
		ui_interface->declare(&fHslider10, "osc", "/kick/lim/attack 0.001 0.02");
		ui_interface->declare(&fHslider10, "style", "knob");
		ui_interface->declare(&fHslider10, "unit", "s");
		ui_interface->addHorizontalSlider("attack", &fHslider10, FAUSTFLOAT(0.002f), FAUSTFLOAT(0.001f), FAUSTFLOAT(0.02f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider11, "2", "");
		ui_interface->declare(&fHslider11, "osc", "/kick/lim/release 0.05 0.5");
		ui_interface->declare(&fHslider11, "style", "knob");
		ui_interface->declare(&fHslider11, "unit", "s");
		ui_interface->addHorizontalSlider("release", &fHslider11, FAUSTFLOAT(0.15f), FAUSTFLOAT(0.05f), FAUSTFLOAT(0.5f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = static_cast<float>(fCheckbox0);
		float fSlow1 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider0));
		float fSlow2 = fConst3 * static_cast<float>(fHslider1);
		float fSlow3 = static_cast<float>(fHslider2);
		float fSlow4 = std::tan(fConst4 * static_cast<float>(fHslider3));
		float fSlow5 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fSlow4));
		float fSlow6 = 1.0f / static_cast<float>(fHslider4);
		float fSlow7 = 1.0f / fSlow4;
		float fSlow8 = (fSlow7 - fSlow6) / fSlow4 + 1.0f;
		float fSlow9 = (fSlow6 + fSlow7) / fSlow4 + 1.0f;
		float fSlow10 = 1.0f / fSlow9;
		float fSlow11 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider5));
		int iSlow12 = fSlow0 == 0.0f;
		float fSlow13 = fConst3 * static_cast<float>(fHslider6);
		float fSlow14 = 1.0f / std::max<float>(1.0f, fConst0 * static_cast<float>(fHslider7));
		float fSlow15 = static_cast<float>(fHslider8);
		float fSlow16 = static_cast<float>(fHslider9) / fSlow9;
		float fSlow17 = static_cast<float>(fHslider10);
		int iSlow18 = std::fabs(fSlow17) < 1.1920929e-07f;
		float fSlow19 = ((iSlow18) ? 0.0f : std::exp(-(fConst3 / ((iSlow18) ? 1.0f : fSlow17))));
		float fSlow20 = 1.0f - fSlow19;
		float fSlow21 = static_cast<float>(fHslider11);
		int iSlow22 = std::fabs(fSlow21) < 1.1920929e-07f;
		float fSlow23 = ((iSlow22) ? 0.0f : std::exp(-(fConst3 / ((iSlow22) ? 1.0f : fSlow21))));
		float fSlow24 = 1.0f - fSlow23;
		float fSlow25 = static_cast<float>(fHslider12);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fVec0[0] = fSlow0;
			iVec1[0] = 1;
			iRec0[0] = (iRec0[1] + (iRec0[1] > 0)) * (fSlow0 <= fVec0[1]) + (fSlow0 > fVec0[1]);
			float fTemp0 = static_cast<float>(iRec0[0]);
			int iTemp1 = 1 - iVec1[1];
			float fTemp2 = ((iTemp1) ? 0.0f : fSlow2 + fRec2[1]);
			fRec2[0] = fTemp2 - std::floor(fTemp2);
			fRec5[0] = fSlow0 + fRec5[1] * static_cast<float>(fVec0[1] >= fSlow0);
			float fTemp3 = fConst6 * fRec5[0];
			float fTemp4 = fConst5 - fRec5[0];
			iRec6[0] = iSlow12 * (iRec6[1] + 1);
			float fTemp5 = 1.0f - fConst7 * static_cast<float>(iRec6[0]);
			float fTemp6 = ((iTemp1) ? 0.0f : fRec4[1] + fSlow13 * (4.0f * std::max<float>(0.0f, fTemp5 * std::min<float>(fTemp3, std::max<float>(fSlow11 * fTemp4 + 1.0f, 0.0f))) + 1.0f));
			fRec4[0] = fTemp6 - std::floor(fTemp6);
			float fTemp7 = tanhf(fSlow15 * std::max<float>(0.0f, std::min<float>(fTemp3, std::max<float>(fSlow14 * fTemp4 + 1.0f, 0.0f)) * fTemp5) * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec4[0]), 65535))]);
			fRec3[0] = fTemp7 - fSlow10 * (fSlow8 * fRec3[2] + fSlow5 * fRec3[1]);
			float fTemp8 = fTemp7 + fSlow16 * (fRec3[2] + fRec3[0] + 2.0f * fRec3[1]) + fSlow3 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec2[0]), 65535))] * std::max<float>(0.0f, std::min<float>(fConst2 * fTemp0, fSlow1 * (fConst1 - fTemp0) + 1.0f));
			fVec3[IOTA0 & 2047] = fTemp8;
			float fTemp9 = std::fabs(fTemp8);
			float fTemp10 = std::fabs(std::max<float>(fTemp9, fTemp9));
			int iTemp11 = (fTemp10 >= fRec10[1]) | (static_cast<float>(iRec9[1]) >= fConst9);
			iRec9[0] = ((iTemp11) ? 0 : iRec9[1] + 1);
			fRec10[0] = ((iTemp11) ? fTemp10 : fRec10[1]);
			fRec8[0] = fRec10[0] * fSlow20 + fSlow19 * fRec8[1];
			float fTemp12 = std::fabs(fRec8[0]);
			fRec7[0] = std::max<float>(fTemp12, fRec7[1] * fSlow23 + fTemp12 * fSlow24);
			float fTemp13 = std::min<float>(1.0f, fSlow25 / std::max<float>(fRec7[0], 1.1920929e-07f)) * fVec3[(IOTA0 - iConst8) & 2047];
			output0[i0] = static_cast<FAUSTFLOAT>(fTemp13);
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp13);
			fVec0[1] = fVec0[0];
			iVec1[1] = iVec1[0];
			iRec0[1] = iRec0[0];
			fRec2[1] = fRec2[0];
			fRec5[1] = fRec5[0];
			iRec6[1] = iRec6[0];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			IOTA0 = IOTA0 + 1;
			iRec9[1] = iRec9[0];
			fRec10[1] = fRec10[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
		}
	}

};

#endif
