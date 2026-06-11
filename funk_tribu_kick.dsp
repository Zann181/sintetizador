// ════════════════════════════════════════════════════════════════
//  FUNK TRIBU KICK  —  neo-trance / fast techno
//  Sub masivo + resonancia + limiter lookahead
//  Todos los parámetros con OSC [osc:/kick/... min max]
// ════════════════════════════════════════════════════════════════

import("stdfaust.lib");

sy = library("synths.lib");
co = library("compressors.lib");
fi = library("filters.lib");
os = library("oscillators.lib");
en = library("envelopes.lib");

// ── INTERFAZ UI con grupos y metadatos OSC ───────────────────────
// La sintaxis [osc:/ruta min max] expone cada parámetro como
// endpoint OSC. faust2jack, faust2pd, faust-osc-controller, etc.
// respetan estos metadatos automáticamente.

kick_group(x)   = hgroup("[0] KICK FUNK TRIBU", x);
core_group(x)   = kick_group(vgroup("[0] Core", x));
sub_group(x)    = kick_group(vgroup("[1] Sub Boost", x));
res_group(x)    = kick_group(vgroup("[2] Resonancia", x));
lim_group(x)    = kick_group(vgroup("[3] Limiter", x));

// ── GATE ─────────────────────────────────────────────────────────
// checkbox = estado estable ON/OFF (no button momentáneo)
// [osc:/kick/gate 0 1] → recibe 0.0 o 1.0 por OSC
gate = core_group(
    checkbox("[0] gate [osc:/kick/gate 0 1][style:toggle]")
);

// ── CORE PARAMETERS ──────────────────────────────────────────────
pitch = core_group(
    hslider("[1] pitch [unit:Hz][osc:/kick/pitch 30 100][style:knob]",
        52, 30, 100, 0.1)
);
click = core_group(
    hslider("[2] click [osc:/kick/click 0.005 1][style:knob]",
        0.68, 0.005, 1, 0.001)
);
decay = core_group(
    hslider("[3] decay [unit:s][osc:/kick/decay 0.1 1.5][style:knob]",
        0.50, 0.1, 1.5, 0.01)
);
drive = core_group(
    hslider("[4] drive [osc:/kick/drive 1 10][style:knob]",
        7.5, 1, 10, 0.1)
);

// ── SUB BOOST PARAMETERS ─────────────────────────────────────────
sub_freq = sub_group(
    hslider("[0] freq [unit:Hz][osc:/kick/sub/freq 20 90][style:knob]",
        48, 20, 90, 0.5)
);
sub_gain = sub_group(
    hslider("[1] gain [osc:/kick/sub/gain 0 1][style:knob]",
        0.55, 0, 1, 0.01)
);
sub_decay = sub_group(
    hslider("[2] decay [unit:s][osc:/kick/sub/decay 0.05 1.2][style:knob]",
        0.60, 0.05, 1.2, 0.01)
);

// ── RESONANCIA PARAMETERS ────────────────────────────────────────
res_freq = res_group(
    hslider("[0] freq [unit:Hz][osc:/kick/res/freq 30 120][style:knob]",
        55, 30, 120, 0.5)
);
res_q = res_group(
    hslider("[1] Q [osc:/kick/res/q 1 20][style:knob]",
        12.0, 1, 20, 0.1)
);
res_mix = res_group(
    hslider("[2] mix [osc:/kick/res/mix 0 1][style:knob]",
        0.40, 0, 1, 0.01)
);

// ── LIMITER PARAMETERS ───────────────────────────────────────────
// LD es compile-time constant en limiter_lad — usamos valor fijo
// Los demás parámetros sí son modulables por OSC
lim_ceil = lim_group(
    hslider("[0] ceiling [osc:/kick/lim/ceiling 0.5 1][style:knob]",
        0.97, 0.5, 1, 0.01)
);
lim_att = lim_group(
    hslider("[1] attack [unit:s][osc:/kick/lim/attack 0.001 0.02][style:knob]",
        0.002, 0.001, 0.02, 0.001)
);
lim_rel = lim_group(
    hslider("[2] release [unit:s][osc:/kick/lim/release 0.05 0.5][style:knob]",
        0.15, 0.05, 0.5, 0.01)
);

// ════════════════════════════════════════════════════════════════
//  SIGNAL CHAIN
// ════════════════════════════════════════════════════════════════

// 1. Kick principal — sine sweep con saturador interno
kick_raw = sy.kick(pitch, click, 0.005, decay, drive, gate);

// 2. Sub boost — sine pura con envelope AR independiente
//    Frecuencia debajo del kick → masa infrasónica real
sub_env   = en.ar(0.001, sub_decay, gate);
sub_layer = os.oscsin(sub_freq) * sub_env * sub_gain;

// 3. Resonancia — resonlp con Q alto sobre el cuerpo del kick
//    Q=12 crea el "rebote" de sub característico del techno masivo
resonance  = fi.resonlp(res_freq, res_q, 1.0);
kick_res   = kick_raw : resonance * res_mix;

// 4. Suma de capas
kick_full = kick_raw + kick_res + sub_layer;

// 5. Limiter lookahead estéreo
//    LD=0.010 compile-time, ceiling/att/rel son controlables
limiter = co.limiter_lad_stereo(0.010, lim_ceil, lim_att, 0.050, lim_rel);

process = kick_full <: _,_ : limiter;

// ════════════════════════════════════════════════════════════════
//  MAPA OSC — todos los endpoints
// ════════════════════════════════════════════════════════════════
//
//  GATE & TRIGGER
//  /kick/gate          0 | 1       disparo (toggle estable)
//
//  KICK CORE
//  /kick/pitch         30–100 Hz   frecuencia base del sweep
//  /kick/click         0.005–1     velocidad del pitch envelope
//  /kick/decay         0.1–1.5 s   cola del kick
//  /kick/drive         1–10        saturación (más = más grit)
//
//  SUB BOOST
//  /kick/sub/freq      20–90 Hz    frecuencia de la sine sub
//  /kick/sub/gain      0–1         nivel de la capa sub
//  /kick/sub/decay     0.05–1.2 s  caída de la capa sub
//
//  RESONANCIA
//  /kick/res/freq      30–120 Hz   frecuencia de resonancia
//  /kick/res/q         1–20        Q del filtro (más = más timbre)
//  /kick/res/mix       0–1         nivel de la capa resonante
//
//  LIMITER
//  /kick/lim/ceiling   0.5–1       techo de amplitud (lineal)
//  /kick/lim/attack    0.001–0.02s ataque del limiter
//  /kick/lim/release   0.05–0.5 s  release del limiter
//
//  USO CON faust2jack:
//  faust2jack -osc funk_tribu_kick.dsp
//  → escucha en UDP 5510, envía en 5511
//
//  USO CON faust2pd / oscsend (Pure Data):
//  [oscsend localhost 5510 /kick/gate i 1]
//  [oscsend localhost 5510 /kick/pitch f 52]
//
//  USO CON TouchOSC / Lemur / Max:
//  Apuntar al IP:5510 con los paths de arriba
// ════════════════════════════════════════════════════════════════
