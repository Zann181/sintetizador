declare filename "untitled.dsp";
declare name "untitled";
declare name "TR_808_Algorithmic_Techno_Station";
declare description "Estación de Ritmo Techno Avanzada con Estructura Modular Completa y Control Dinámico Total";
declare license "MIT";

import("stdfaust.lib");
la = library("linearalgebra.lib");

// =============================================================================
// PROCESADOR DINÁMICO OPTIMIZADO (COMPRESIÓN + FILTRO DINÁMICO PARA EL BOMBO)
// =============================================================================
light_dyn_sat(thresh, ratio, f_max, f_min, drive, x) = 
    (x * gain * drive) : ma.tanh : fi.lowpass(1, dyn_freq)
with {
    env = abs(x) : si.smooth(ba.tau2pole(0.01)); 
    overshoot = max(0.0, env - thresh);
    gain = 1.0 / (1.0 + overshoot * ratio);
    dyn_freq = max(f_min, f_max - (overshoot * ratio * (f_max - f_min)));
};

// =============================================================================
// 1. RELOJ MAESTRO CENTRALIZADO CON MOTOR DE SWING / BALANCEO ANALÓGICO
// =============================================================================
master_bpm   = hslider("v:0_MASTER/BPM_Maestro [osc:/master/bpm]", 140, 60, 240, 1);
accent_level = hslider("v:0_MASTER/Accent_Global [style:knob][osc:/master/accent]", 0.5, 0, 1, 0.01);
master_swing = hslider("v:0_MASTER/Swing_Groove [style:knob][osc:/master/swing]", 0, 0, 75, 1); 

nota_base = hslider("v:0_MASTER/Nota_Fundamental [style:menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}][osc:/master/nota]", 36, 36, 47, 1);

F0 = ba.midikey2hz(nota_base);
semitono2ratio(s) = pow(2.0, s / 12.0);

master_clock_engine = environment {
    // Frecuencia de pasos en Hz: (bpm / 60.0) * 4.0 * mult = (bpm / 15.0) * mult
    step_freq(bpm, mult) = (bpm / 15.0) * mult;
    
    // Phasor: rampa acumulativa de 0 a 1 que se resetea automáticamente en 1
    phase(bpm, mult) = (+(step_freq(bpm, mult) / ma.SR) ~ ma.decimal);
    
    // Disparo limpio solo cuando el phasor da la vuelta (phase < phase')
    get_raw_trig(bpm, mult) = phase(bpm, mult) < phase(bpm, mult)';
    
    // Contador de paso (0-15) incrementado estrictamente en los flancos de disparo
    tick(trig, s) = select2(trig, s, (s + 1) % 16);
    get_step(bpm, mult) = tick(get_raw_trig(bpm, mult)) ~ _;
    
    // Disparador con soporte de swing delay
    get_trig(bpm, mult, swing) = select2(is_even_step, raw_trig, delayed_trig)
    with {
        step = get_step(bpm, mult);
        raw_trig = get_raw_trig(bpm, mult);
        is_even_step = (step % 2 == 1); 
        samples_per_step = ma.SR / step_freq(bpm, mult);
        d_amt = (swing / 100.0) * 0.5 * samples_per_step;
        delayed_trig = de.fdelay(16384, d_amt, raw_trig);
    };
};

groove_menu = hslider("Evolucion_Groove [style:menu{
    '1: Ultra Hipnotico':0; 
    '2: Deep Mental':1; 
    '3: Bucle Psiquico':2; 
    '4: Driving Techno':3; 
    '5: Tribal Funk':4; 
    '6: Hardgroove Tradicional':5; 
    '7: Hardgroove Frenetico':6
}][osc:/master/groove]", 0, 0, 6, 1);

is_downbeat(s) = (s == 0) | (s == 4) | (s == 8) | (s == 12);
calc_accent(s) = select2(is_downbeat(s), 1.0, 1.0 + accent_level * 0.4);

master_accent(s) = is_downbeat(s);
m_syn2(s) = pat_syn2(s);

// =============================================================================
// 2. BANCOS DE DATOS RÍTMICOS DE ALTA COMPATIBILIDAD (7 ESTILOS x 16 PASOS)
// =============================================================================
pat_kick(s) = ba.selectn(16, s, 
    checkbox("v:PAD/KICK/00 [osc:/kick/step0]"), checkbox("v:PAD/KICK/01 [osc:/kick/step1]"),
    checkbox("v:PAD/KICK/02 [osc:/kick/step2]"), checkbox("v:PAD/KICK/03 [osc:/kick/step3]"),
    checkbox("v:PAD/KICK/04 [osc:/kick/step4]"), checkbox("v:PAD/KICK/05 [osc:/kick/step5]"),
    checkbox("v:PAD/KICK/06 [osc:/kick/step6]"), checkbox("v:PAD/KICK/07 [osc:/kick/step7]"),
    checkbox("v:PAD/KICK/08 [osc:/kick/step8]"), checkbox("v:PAD/KICK/09 [osc:/kick/step9]"),
    checkbox("v:PAD/KICK/10 [osc:/kick/step10]"), checkbox("v:PAD/KICK/11 [osc:/kick/step11]"),
    checkbox("v:PAD/KICK/12 [osc:/kick/step12]"), checkbox("v:PAD/KICK/13 [osc:/kick/step13]"),
    checkbox("v:PAD/KICK/14 [osc:/kick/step14]"), checkbox("v:PAD/KICK/15 [osc:/kick/step15]")
);

pat_snare(s) = ba.selectn(16, s, 
    checkbox("v:PAD/SNARE/00 [osc:/snare/step0]"), checkbox("v:PAD/SNARE/01 [osc:/snare/step1]"),
    checkbox("v:PAD/SNARE/02 [osc:/snare/step2]"), checkbox("v:PAD/SNARE/03 [osc:/snare/step3]"),
    checkbox("v:PAD/SNARE/04 [osc:/snare/step4]"), checkbox("v:PAD/SNARE/05 [osc:/snare/step5]"),
    checkbox("v:PAD/SNARE/06 [osc:/snare/step6]"), checkbox("v:PAD/SNARE/07 [osc:/snare/step7]"),
    checkbox("v:PAD/SNARE/08 [osc:/snare/step8]"), checkbox("v:PAD/SNARE/09 [osc:/snare/step9]"),
    checkbox("v:PAD/SNARE/10 [osc:/snare/step10]"), checkbox("v:PAD/SNARE/11 [osc:/snare/step11]"),
    checkbox("v:PAD/SNARE/12 [osc:/snare/step12]"), checkbox("v:PAD/SNARE/13 [osc:/snare/step13]"),
    checkbox("v:PAD/SNARE/14 [osc:/snare/step14]"), checkbox("v:PAD/SNARE/15 [osc:/snare/step15]")
);

pat_hat(s) = ba.selectn(16, s, 
    checkbox("v:PAD/HAT/00 [osc:/hat/step0]"), checkbox("v:PAD/HAT/01 [osc:/hat/step1]"),
    checkbox("v:PAD/HAT/02 [osc:/hat/step2]"), checkbox("v:PAD/HAT/03 [osc:/hat/step3]"),
    checkbox("v:PAD/HAT/04 [osc:/hat/step4]"), checkbox("v:PAD/HAT/05 [osc:/hat/step5]"),
    checkbox("v:PAD/HAT/06 [osc:/hat/step6]"), checkbox("v:PAD/HAT/07 [osc:/hat/step7]"),
    checkbox("v:PAD/HAT/08 [osc:/hat/step8]"), checkbox("v:PAD/HAT/09 [osc:/hat/step9]"),
    checkbox("v:PAD/HAT/10 [osc:/hat/step10]"), checkbox("v:PAD/HAT/11 [osc:/hat/step11]"),
    checkbox("v:PAD/HAT/12 [osc:/hat/step12]"), checkbox("v:PAD/HAT/13 [osc:/hat/step13]"),
    checkbox("v:PAD/HAT/14 [osc:/hat/step14]"), checkbox("v:PAD/HAT/15 [osc:/hat/step15]")
);

pat_bass(s) = ba.selectn(16, s, 
    checkbox("v:PAD/BASS/00 [osc:/bass/step0]"), checkbox("v:PAD/BASS/01 [osc:/bass/step1]"),
    checkbox("v:PAD/BASS/02 [osc:/bass/step2]"), checkbox("v:PAD/BASS/03 [osc:/bass/step3]"),
    checkbox("v:PAD/BASS/04 [osc:/bass/step4]"), checkbox("v:PAD/BASS/05 [osc:/bass/step5]"),
    checkbox("v:PAD/BASS/06 [osc:/bass/step6]"), checkbox("v:PAD/BASS/07 [osc:/bass/step7]"),
    checkbox("v:PAD/BASS/08 [osc:/bass/step8]"), checkbox("v:PAD/BASS/09 [osc:/bass/step9]"),
    checkbox("v:PAD/BASS/10 [osc:/bass/step10]"), checkbox("v:PAD/BASS/11 [osc:/bass/step11]"),
    checkbox("v:PAD/BASS/12 [osc:/bass/step12]"), checkbox("v:PAD/BASS/13 [osc:/bass/step13]"),
    checkbox("v:PAD/BASS/14 [osc:/bass/step14]"), checkbox("v:PAD/BASS/15 [osc:/bass/step15]")
);

pat_syn1(s) = ba.selectn(16, s, 
    checkbox("v:PAD/SYN1/00 [osc:/syn1/step0]"), checkbox("v:PAD/SYN1/01 [osc:/syn1/step1]"),
    checkbox("v:PAD/SYN1/02 [osc:/syn1/step2]"), checkbox("v:PAD/SYN1/03 [osc:/syn1/step3]"),
    checkbox("v:PAD/SYN1/04 [osc:/syn1/step4]"), checkbox("v:PAD/SYN1/05 [osc:/syn1/step5]"),
    checkbox("v:PAD/SYN1/06 [osc:/syn1/step6]"), checkbox("v:PAD/SYN1/07 [osc:/syn1/step7]"),
    checkbox("v:PAD/SYN1/08 [osc:/syn1/step8]"), checkbox("v:PAD/SYN1/09 [osc:/syn1/step9]"),
    checkbox("v:PAD/SYN1/10 [osc:/syn1/step10]"), checkbox("v:PAD/SYN1/11 [osc:/syn1/step11]"),
    checkbox("v:PAD/SYN1/12 [osc:/syn1/step12]"), checkbox("v:PAD/SYN1/13 [osc:/syn1/step13]"),
    checkbox("v:PAD/SYN1/14 [osc:/syn1/step14]"), checkbox("v:PAD/SYN1/15 [osc:/syn1/step15]")
);

pat_syn2(s) = ba.selectn(16, s, 
    checkbox("v:PAD/SYN2/00 [osc:/syn2/step0]"), checkbox("v:PAD/SYN2/01 [osc:/syn2/step1]"),
    checkbox("v:PAD/SYN2/02 [osc:/syn2/step2]"), checkbox("v:PAD/SYN2/03 [osc:/syn2/step3]"),
    checkbox("v:PAD/SYN2/04 [osc:/syn2/step4]"), checkbox("v:PAD/SYN2/05 [osc:/syn2/step5]"),
    checkbox("v:PAD/SYN2/06 [osc:/syn2/step6]"), checkbox("v:PAD/SYN2/07 [osc:/syn2/step7]"),
    checkbox("v:PAD/SYN2/08 [osc:/syn2/step8]"), checkbox("v:PAD/SYN2/09 [osc:/syn2/step9]"),
    checkbox("v:PAD/SYN2/10 [osc:/syn2/step10]"), checkbox("v:PAD/SYN2/11 [osc:/syn2/step11]"),
    checkbox("v:PAD/SYN2/12 [osc:/syn2/step12]"), checkbox("v:PAD/SYN2/13 [osc:/syn2/step13]"),
    checkbox("v:PAD/SYN2/14 [osc:/syn2/step14]"), checkbox("v:PAD/SYN2/15 [osc:/syn2/step15]")
);

// =============================================================================
// 3. MOTORES DE SÍNTESIS Y RACK MODULAR DE INSTRUMENTOS VERIFICADOS
// =============================================================================

// --- MÓDULO 1: BOMBO ---
kick_mod = vgroup("[1] Bombo", kick_out * vol)
with {
    clk_mult   = hslider("[1] Sintesis/Reloj [style:menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}][osc:/kick/reloj]", 1, 0.25, 4, 0.25);
    vol        = hslider("[1] Sintesis/Volumen [osc:/kick/vol]", 0.85, 0, 1, 0.01);
    kick_dec   = hslider("[1] Sintesis/Decaimiento [style:knob][osc:/kick/dec]", 0.18, 0.02, 1.0, 0.01); 
    kick_sweep = hslider("[1] Sintesis/Transitorio [style:knob][osc:/kick/sweep]", 150.0, 0.0, 300.0, 1.0);
    tune_k     = hslider("[1] Sintesis/Afinacion [style:knob][osc:/kick/tune]", 0, -12, 12, 1);
    spring_mix = hslider("[1] Sintesis/Mix Rumble [style:knob][osc:/kick/mix]", 0.45, 0.0, 1.0, 0.01);

    comp_thresh = hslider("[2] Dinamica/Lim Umbral [style:knob][osc:/kick/comp_thresh]", 0.40, 0.01, 1.0, 0.01);
    comp_ratio  = hslider("[2] Dinamica/Lim Ratio [style:knob][osc:/kick/comp_ratio]", 8.0, 1.0, 20.0, 0.1); 
    comp_drive  = hslider("[2] Dinamica/Saturacion Pegada [style:knob][osc:/kick/comp_drive]", 3.5, 0.5, 8.0, 0.1);
    comp_fmax   = hslider("[2] Dinamica/Filtro Frec Max [style:knob][osc:/kick/comp_fmax]", 2500.0, 1000.0, 8000.0, 10.0);
    comp_fmin   = hslider("[2] Dinamica/Filtro Frec Min [style:knob][osc:/kick/comp_fmin]", 750.0, 100.0, 2000.0, 10.0);

    accent     = hslider("[1] Sintesis/Accent [style:knob][osc:/kick/accent]", 0.5, 0, 1, 0.01);
    swing      = hslider("[1] Sintesis/Swing [style:knob][osc:/kick/swing]", 0, 0, 75, 1);
    nota       = hslider("[1] Sintesis/Nota [style:menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}][osc:/kick/nota]", 36, 36, 47, 1);

    local_step = master_clock_engine.get_step(master_bpm, clk_mult);
    local_trig = master_clock_engine.get_trig(master_bpm, clk_mult, swing);
    
    gate = local_trig & (pat_kick(local_step) > 0);
    calc_local_accent(s) = select2(is_downbeat(s), 1.0, 1.0 + accent * 0.4);
    v_trig = calc_local_accent(local_step);

    f0_local = ba.midikey2hz(nota);
    env_k = en.ar(0.001, kick_dec, gate) * v_trig;
    env_k_pitch = en.ar(0.001, 0.05, gate); 
    f_kick = f0_local * semitono2ratio(tune_k); 
    kick_raw = os.oscsin(f_kick + kick_sweep * pow(env_k_pitch, 1.5)) * env_k;
    
    kick_paralelo = kick_raw : light_dyn_sat(comp_thresh, comp_ratio, comp_fmax, comp_fmin, comp_drive);

    spring_tank(dry_signal) = dry_signal <: _, (fi.highpass(2, 60) : fi.lowpass(2, 1200) : fdn_spring : fi.allpass_comb(1024, 131, 0.5) : fi.allpass_comb(1024, 191, 0.5)) : dry_mix
    with {
        spring_matrix(v1,v2,v3,v4) = ((v1+v2+v3+v4)*0.5, (v1-v2+v3-v4)*0.5, (v1+v2-v3-v4)*0.5, (v1-v2-v3+v4)*0.5);
        matrix_fb(fb1,fb2,fb3,fb4,in_sig) = ((fb1+in_sig)*0.75, (fb2+in_sig)*0.75, (fb3+in_sig)*0.75, (fb4+in_sig)*0.75);
        fdn_spring = matrix_fb ~ ( (de.delay(1024, 347), de.delay(1024, 461), de.delay(1024, 593), de.delay(1024, 701)) : (fi.lowpass(1, 2000), fi.lowpass(1, 2000), fi.lowpass(1, 2000), fi.lowpass(1, 2000)) : (ma.tanh, ma.tanh, ma.tanh, ma.tanh) : spring_matrix ) :> _;
        dry_mix(dry, wet) = (dry * (1.0 - spring_mix)) + (wet * spring_mix * 1.8);
    };
    kick_out = kick_paralelo : fi.lowpass(2, 2500) : fi.highpass(2, 20) : spring_tank;
};

// --- MÓDULO 2: CAJA ---
snare_mod = vgroup("[2] Caja", snare_out * vol)
with {
    clk_mult  = hslider("[1] Sintesis/Reloj [style:menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}][osc:/snare/reloj]", 1, 0.25, 4, 0.25);
    vol       = hslider("[1] Sintesis/Volumen [osc:/snare/vol]", 0.65, 0, 1, 0.01);
    dec_body  = hslider("[1] Sintesis/Decay Cuerpo [style:knob][osc:/snare/dec_cuerpo]", 0.07, 0.01, 0.4, 0.01); 
    dec_snare = hslider("[1] Sintesis/Decay Resortes [style:knob][osc:/snare/dec_resorte]", 0.16, 0.02, 1.0, 0.01); 
    tune_sn   = hslider("[1] Sintesis/Afinacion [style:knob][osc:/snare/tune]", 0, -12, 12, 1); 
    snare_mix = hslider("[1] Sintesis/Mix Resortes [style:knob][osc:/snare/mix]", 0.55, 0.0, 1.0, 0.01);

    sn_freq   = hslider("[1] Sintesis/Frecuencia Resortes [style:knob][osc:/snare/freq]", 1650.0, 1000.0, 4000.0, 10.0);
    sn_q      = hslider("[1] Sintesis/Resonancia Resortes [style:knob][osc:/snare/q]", 2.5, 1.0, 5.0, 0.1);
    sn_hp     = hslider("[1] Sintesis/Filtro Paso Alto [style:knob][osc:/snare/hp]", 160.0, 80.0, 400.0, 1.0);
    sn_drive  = hslider("[1] Sintesis/Saturacion [style:knob][osc:/snare/drive]", 1.0, 1.0, 5.0, 0.1);

    accent     = hslider("[1] Sintesis/Accent [style:knob][osc:/snare/accent]", 0.5, 0, 1, 0.01);
    swing      = hslider("[1] Sintesis/Swing [style:knob][osc:/snare/swing]", 0, 0, 75, 1);
    nota       = hslider("[1] Sintesis/Nota [style:menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}][osc:/snare/nota]", 36, 36, 47, 1);

    local_step = master_clock_engine.get_step(master_bpm, clk_mult);
    local_trig = master_clock_engine.get_trig(master_bpm, clk_mult, swing);
    
    gate = local_trig & (pat_snare(local_step) > 0);
    calc_local_accent(s) = select2(is_downbeat(s), 1.0, 1.0 + accent * 0.4);
    v_trig = calc_local_accent(local_step);

    f_base = ba.midikey2hz(nota);
    scale_ratio = f_base / ba.midikey2hz(36);
    f_body1 = 180.0 * scale_ratio * semitono2ratio(tune_sn);
    f_body2 = 332.0 * scale_ratio * semitono2ratio(tune_sn);
    env_body = en.ar(0.0005, dec_body, gate) * v_trig;
    cuerpo_tonal = (os.oscsin(f_body1) * 0.65 + os.oscsin(f_body2) * 0.35) * env_body;

    env_snare = en.ar(0.001, dec_snare, gate) * v_trig;
    ruido_filtrado = no.noise : fi.resonbp(sn_freq, sn_q, 1.3) * env_snare;

    snare_raw = ((cuerpo_tonal * (1.0 - snare_mix)) + (ruido_filtrado * snare_mix * 1.8)) * sn_drive;
    snare_out = snare_raw : fi.highpass(2, sn_hp) : fi.lowpass(2, 9000) : ma.tanh;
};

// --- MÓDULO 3: PLATILLOS ---
hat_mod = vgroup("[3] Platillos", hat_out * vol)
with {
    clk_mult = hslider("[1] Sintesis/Reloj [style:menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}][osc:/hat/reloj]", 1, 0.25, 4, 0.25);
    vol      = hslider("[1] Sintesis/Volumen [osc:/hat/vol]", 0.45, 0, 1, 0.01);
    h_a      = hslider("[1] Sintesis/Ataque [style:knob][osc:/hat/ataque]", 0.001, 0.001, 0.1, 0.001);
    h_d      = hslider("[1] Sintesis/Decaimiento [style:knob][osc:/hat/dec]", 0.04, 0.01, 1.0, 0.01); 
    tune_h   = hslider("[1] Sintesis/Afinacion [style:knob][osc:/hat/tune]", 0, -12, 12, 1); 
    drive    = hslider("[1] Sintesis/Saturacion [style:knob][osc:/hat/drive]", 0.35, 0.0, 1.0, 0.001);

    h_mix    = hslider("[1] Sintesis/Mix Metal Ruido [style:knob][osc:/hat/mix]", 0.5, 0.0, 1.0, 0.01);
    h_cutoff = hslider("[1] Sintesis/Filtro Paso Alto [style:knob][osc:/hat/cutoff]", 6500.0, 3000.0, 12000.0, 50.0);

    accent     = hslider("[1] Sintesis/Accent [style:knob][osc:/hat/accent]", 0.5, 0, 1, 0.01);
    swing      = hslider("[1] Sintesis/Swing [style:knob][osc:/hat/swing]", 0, 0, 75, 1);
    nota       = hslider("[1] Sintesis/Nota [style:menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}][osc:/hat/nota]", 36, 36, 47, 1);

    local_step = master_clock_engine.get_step(master_bpm, clk_mult);
    local_trig = master_clock_engine.get_trig(master_bpm, clk_mult, swing);
    
    gate = local_trig & (pat_hat(local_step) > 0);
    calc_local_accent(s) = select2(is_downbeat(s), 1.0, 1.0 + accent * 0.4);
    v_trig = calc_local_accent(local_step);

    f_base = ba.midikey2hz(nota);
    scale_ratio = f_base / ba.midikey2hz(36);
    env_slap_hat = en.ar(h_a, h_d, gate) * v_trig;
    f_m = 350.0 * scale_ratio * semitono2ratio(tune_h);

    cluster_metalico = (os.square(f_m * 2.0) + os.square(f_m * 2.98) + os.square(f_m * 4.16) + os.square(f_m * 5.43) + os.square(f_m * 6.77) + os.square(f_m * 8.2)) * 0.15;
    ruido_blanco = no.noise * 0.5;
    saturador_hat(d, x) = x / (1.0 + d * abs(x)); 
    fuente_hat_saturada = ((cluster_metalico * (1.0 - h_mix)) + (ruido_blanco * h_mix * 2.0)) : saturador_hat(drive * 6.5);
    hat_raw = fuente_hat_saturada * env_slap_hat;
    hat_out = hat_raw : fi.highpass(2, h_cutoff) * 2.0; 
};

// --- MÓDULO 4: BAJO WAVEGUIDE ---
bass_mod = vgroup("[4] Bajo WG", bass_out * vol)
with {
    clk_mult  = hslider("[1] Sintesis/Reloj [style:menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}][osc:/bass/reloj]", 1, 0.25, 4, 0.25);
    intervalo = hslider("[1] Sintesis/Intervalo [osc:/bass/intervalo]", -12, -12, 7, 1);
    vol       = hslider("[1] Sintesis/Volumen [osc:/bass/vol]", 0.55, 0, 1, 0.01);
    dec_bass  = hslider("[1] Sintesis/Decaimiento [style:knob][osc:/bass/dec]", 0.35, 0.01, 1.0, 0.01); 
    cam_lenta = hslider("[1] Sintesis/Desafinado [style:knob][osc:/bass/detune]", 0.04, 0.0, 1.0, 0.01);
    peso_flt  = hslider("[1] Sintesis/Filtro LFO [style:knob][osc:/bass/lfo]", 0.45, 0.0, 1.0, 0.01);
    drive_ui  = hslider("[1] Sintesis/Saturacion [style:knob][osc:/bass/drive]", 0.65, 0.0, 1.0, 0.001);

    accent     = hslider("[1] Sintesis/Accent [style:knob][osc:/bass/accent]", 0.5, 0, 1, 0.01);
    swing      = hslider("[1] Sintesis/Swing [style:knob][osc:/bass/swing]", 0, 0, 75, 1);
    nota       = hslider("[1] Sintesis/Nota [style:menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}][osc:/bass/nota]", 36, 36, 47, 1);

    local_step = master_clock_engine.get_step(master_bpm, clk_mult);
    local_trig = master_clock_engine.get_trig(master_bpm, clk_mult, swing);
    
    gate = local_trig & (pat_bass(local_step) > 0);
    calc_local_accent(s) = select2(is_downbeat(s), 1.0, 1.0 + accent * 0.4);
    v_trig = calc_local_accent(local_step);

    tau_bass = (4.0 * (60.0 / master_bpm)) * dec_bass;
    timer_bass = (+(1.0/ma.SR) * (1.0 - gate)) ~ _;
    env_exp_bass = exp(-timer_bass / tau_bass) : si.smooth(ba.tau2pole(0.005));

    env_slap_bass = en.ar(0.001, 0.18, gate) * v_trig;
    x_n_bass = (no.noise : fi.lowpass(1, 1500)) * env_slap_bass;
    f0_local = ba.midikey2hz(nota);
    f_base_bass = f0_local * semitono2ratio(intervalo);
    L_dinamico_bass = (ma.SR / f_base_bass) * (1.0 + (cam_lenta * 0.059));

    fase_sinc_bass = (+(3.0/ma.SR) ~ *(1 - gate)) : ma.decimal;
    c_val_bass  = max(0.01, (0.6 - (cam_lenta * 0.15)) + sin(fase_sinc_bass * 2 * ma.PI) * peso_flt * 0.15);
    g_val_bass = 0.985 + (cam_lenta * 0.014);

    filtro_material_bass(c) = *(c) : + ~ *(1 - c);
    saturador_bass(d, x) = x * (1.0 + d) / (1.0 + d * abs(x));

    bass_waveguide = x_n_bass : + ~ (de.fdelay(131072, L_dinamico_bass) : filtro_material_bass(c_val_bass) : saturador_bass(drive_ui * 3.0) : *(g_val_bass));
    bass_out = (bass_waveguide * env_exp_bass) : fi.highpass(2, 20) : fi.lowpass(2, 800); 
};

// --- MÓDULO 5: SYNTH 1 PSICODÉLICO ---
synth1_mod = vgroup("[5] Synth Psyche", synth1_out_stereo : par(i, 2, *(vol)))
with {
    clk_mult       = hslider("[1] Sintesis/Reloj [style:menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}][osc:/syn1/reloj]", 1, 0.25, 4, 0.25);
    intervalo_osc1 = hslider("[1] Sintesis/Osc 1 [osc:/syn1/osc1]", 5, 0, 12, 1);
    intervalo_osc2 = hslider("[1] Sintesis/Osc 2 [osc:/syn1/osc2]", 12, 0, 19, 19);
    vol            = hslider("[1] Sintesis/Volumen [osc:/syn1/vol]", 0.85, 0, 1, 0.01);
    s_d            = hslider("[1] Sintesis/Decaimiento [style:knob][osc:/syn1/dec]", 0.2, 0.01, 2.0, 0.01); 
    auto_vel       = hslider("[1] Sintesis/Auto Velocidad [style:knob][osc:/syn1/auto_v]", 0.5, 0.05, 5.0, 0.01);
    auto_prof      = hslider("[1] Sintesis/Auto Profundidad [style:knob][osc:/syn1/auto_p]", 0.7, 0.0, 1.0, 0.01);
    auto_res       = hslider("[1] Sintesis/Auto Resonancia [style:knob][osc:/syn1/auto_r]", 4.5, 1.0, 9.0, 0.1);

    accent     = hslider("[1] Sintesis/Accent [style:knob][osc:/syn1/accent]", 0.5, 0, 1, 0.01);
    swing      = hslider("[1] Sintesis/Swing [style:knob][osc:/syn1/swing]", 0, 0, 75, 1);
    nota       = hslider("[1] Sintesis/Nota [style:menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}][osc:/syn1/nota]", 36, 36, 47, 1);

    local_step = master_clock_engine.get_step(master_bpm, clk_mult);
    local_trig = master_clock_engine.get_trig(master_bpm, clk_mult, swing);
    
    gate = local_trig & (pat_syn1(local_step) > 0);
    calc_local_accent(s) = select2(is_downbeat(s), 1.0, 1.0 + accent * 0.4);
    v_trig = calc_local_accent(local_step);

    f0_local = ba.midikey2hz(nota);
    synth_freq1 = f0_local * semitono2ratio(intervalo_osc1);
    synth_freq2 = f0_local * semitono2ratio(intervalo_osc2); 
    synth_source = os.sawtooth(synth_freq1 + 2.0 * os.oscsin(0.08)) * 0.6 + os.square(synth_freq2 + os.oscsin(0.3)) * 0.3;

    synth1_env = en.ar(0.05, s_d, gate) * v_trig;
    psyche_osc_raw = synth_source * synth1_env : fi.highpass(2, 60) : fi.lowpass(2, 2000);

    fase_auto = os.lf_sawpos(auto_vel); 
    doppler_delay = 100.0 + (sin(fase_auto * ma.PI) * 85.0 * auto_prof);
    frecuencia_viento = 400.0 + (sin(fase_auto * ma.PI) * 5000.0 * auto_prof);

    panner_L = sqrt(1.0 - fase_auto);
    panner_R = sqrt(fase_auto);

    mezcla_autobahn(in_sig) = 
        in_sig <: 
        _ * (1.0 - (auto_prof * 0.5)), 
        (de.fdelay(4096, doppler_delay) : fi.resonbp(frecuencia_viento, auto_res, 1.0)) * auto_prof 
        :> _ * panner_L, _ * panner_R;
        
    synth1_out_stereo = psyche_osc_raw : mezcla_autobahn;
};

// --- MÓDULO 6: SIRINGE FDN ---
synth2_mod = vgroup("[6] Siringe FDN", synth2_out * vol)
with {
    clk_mult = hslider("[1] Sintesis/Reloj [style:menu{'÷4':0.25; '÷2':0.5; 'x1':1; 'x2':2; 'x4':4}][osc:/syn2/reloj]", 1, 0.25, 4, 0.25);
    intervalo_siringe = hslider("[1] Sintesis/Nota Siringe [style:menu{'Octava':12; 'Quinta Arriba':19; 'Doble Octava':24}][osc:/syn2/nota]", 12, 12, 24, 1);
    vol    = hslider("[1] Sintesis/Volumen [osc:/syn2/vol]", 0.22, 0, 1, 0.01);
    sir_dec = hslider("[1] Sintesis/Decaimiento [style:knob][osc:/syn2/dec]", 0.2, 0.01, 2.0, 0.01); 
    disp   = hslider("[1] Sintesis/Dispersion [style:knob][osc:/syn2/disp]", 0.5, 0.1, 0.9, 0.01);
    f_lfo  = hslider("[1] Sintesis/LFO Freq [style:knob][osc:/syn2/lfo_f]", 2, 0.1, 20, 0.1);
    p_lfo  = hslider("[1] Sintesis/LFO Profundidad [style:knob][osc:/syn2/lfo_p]", 0.5, 0, 1, 0.01);

    comp_ratio  = hslider("[2] Dinamica/Comp Ratio [style:knob][osc:/syn2/comp_r]", 6.0, 1.0, 20.0, 0.1);    
    comp_thresh = hslider("[2] Dinamica/Comp Umbral [style:knob][osc:/syn2/comp_th]", -20.0, -60.0, 0.0, 0.1); 
    comp_att    = hslider("[2] Dinamica/Comp Ataque [style:knob][osc:/syn2/comp_a]", 0.005, 0.001, 0.1, 0.001); 
    comp_rel    = hslider("[2] Dinamica/Comp Liberacion [style:knob][osc:/syn2/comp_rel]", 0.1, 0.01, 1.0, 0.01); 

    accent     = hslider("[1] Sintesis/Accent [style:knob][osc:/syn2/accent]", 0.5, 0, 1, 0.01);
    swing      = hslider("[1] Sintesis/Swing [style:knob][osc:/syn2/swing]", 0, 0, 75, 1);
    nota       = hslider("[1] Sintesis/Nota [style:menu{'C (Do)':36; 'C# (Do#)':37; 'D (Re)':38; 'D# (Re#)':39; 'E (Mi)':40; 'F (Fa)':41; 'F# (Fa#)':42; 'G (Sol)':43; 'G# (Sol#)':44; 'A (La)':45; 'A# (La#)':46; 'B (Si)':47}][osc:/syn2/nota]", 36, 36, 47, 1);

    local_step = master_clock_engine.get_step(master_bpm, clk_mult);
    local_trig = master_clock_engine.get_trig(master_bpm, clk_mult, swing);
    
    acc_active = master_accent(local_step);
    v_trig = select2(acc_active, 1.0, 1.0 + accent * 0.6);
    gate = local_trig & (m_syn2(local_step) > 0);

    f0_local = ba.midikey2hz(nota);
    freq_base = f0_local * semitono2ratio(intervalo_siringe);
    env_sir = en.ar(0.05, sir_dec, local_trig & gate) * v_trig; 
    
    frecuencia_inst = freq_base + (env_sir * 1500.0);
    siringe = os.osc(frecuencia_inst) * env_sir;

    H4_s2 = ( disp,  disp,  disp,  disp,
              disp, -disp,  disp, -disp,
              disp,  disp, -disp, -disp,
              disp, -disp, -disp,  disp );

    bosque_dispersion(v1, v2, v3, v4) = H4_s2, v1, v2, v3, v4 : la.matMul(4, 4, 4, 1) : par(i, 4, *(0.5));
    absorcion = fi.lowpass(1, 3500);
    matriz_suma(fb1, fb2, fb3, fb4, in1, in2, in3, in4) = (fb1 + in1), (fb2 + in2), (fb3 + in3), (fb4 + in4);

    fdn_core = matriz_suma ~ (
        (de.delay(4096, 1117), de.delay(4096, 1399), de.delay(4096, 1723), de.delay(4096, 2089)) 
        : (absorcion, absorcion, absorcion, absorcion) 
        : bosque_dispersion
    );

    fdn_mono = siringe <: fdn_core :> /(4.0);
    modulacion = 1 + (os.osc(f_lfo) * p_lfo);

    raw_bosque_signal = fdn_mono * modulacion;
    bosque_comprimido = raw_bosque_signal : co.compressor_mono(comp_ratio, comp_thresh, comp_att, comp_rel); 
    
    synth2_out = bosque_comprimido : fi.highpass(2, 150) : fi.lowpass(2, 6500); 
};

// =============================================================================
// 4. DISTRIBUCIÓN ESTÉREO Y FILTRADO FINAL DE SEGURIDAD
// =============================================================================
instrument_rack = hgroup("INSTRUMENTOS", kick_mod, snare_mod, hat_mod, bass_mod, synth1_mod, synth2_mod);

ruteo_estereo(k, sn, h, b, s1_L, s1_R, s2) = (mono_mix + s1_L), (mono_mix + s1_R)
with { mono_mix = k + sn + h + b + s2; };

mezcla_estereo = instrument_rack : ruteo_estereo;

process = vgroup("TR_808_ALGORITHMIC_STATION", mezcla_estereo : par(i, 2, *(1.5) : ma.tanh : fi.dcblocker));