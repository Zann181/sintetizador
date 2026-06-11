import("stdfaust.lib");

step_freq = 1.0; // 1 Hz
phase = (+(step_freq / ma.SR) ~ ma.decimal);
raw_trig = phase < phase';

tick(trig, s) = select2(trig, s, (s + 1) % 16);
step = tick(raw_trig) ~ _;

process = step, raw_trig;
