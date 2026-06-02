import os

file_path = r"c:\Users\Motaz\Music\Nueva carpeta\sintetizador\osc\OscServer.cpp"

optimized_html_content = r"""    void serveHTML(int client_fd) {
        const std::string html = R"html(<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>TR-808 Algorithmic Station</title>
    <link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@400;700;900&family=Outfit:wght@300;400;600;700&display=swap" rel="stylesheet">
    <style>
        :root {
            --bg: #100808; /* Deep espresso dark background */
            --panel-bg: #201111; /* Dark red-brown panel background */
            --panel-inner: #0b0505; /* Blackish red-brown interior */
            --border: #542626; /* Primary Color: Red-brown */
            --border-strong: #543d26; /* Secondary Color: Gold-brown */
            --accent-red: #542626; /* Primary Color */
            --accent-orange: #543d26; /* Secondary Color */
            --accent-cyan: #54263d; /* Accent Color: Plum-rose */
            --neutral-white: #f8f7f7; /* Neutral Color: Texto base / Tiza */
            --accent-glow: rgba(84, 38, 38, 0.4);
            --orange-glow: rgba(84, 61, 38, 0.45);
            --cyan-glow: rgba(84, 38, 61, 0.5);
        }
        * { box-sizing: border-box; margin: 0; padding: 0; }
        body {
            background-color: var(--bg);
            font-family: 'Outfit', sans-serif;
            color: var(--neutral-white) !important;
            height: 100vh;
            display: flex;
            flex-direction: column;
            overflow: hidden;
        }

        /* Ensure all text labels and values are bright tiza white for maximum readability */
        span, label, select, option, button, h1, h2, h3, div, p, li {
            color: var(--neutral-white) !important;
            opacity: 1 !important;
        }

        /* ── HEADER ─────────────────────────────────────── */
        header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 8px 24px;
            background: #000000;
            border-bottom: 2px solid var(--border-strong);
            height: 64px;
            flex-shrink: 0;
            z-index: 100;
        }
        .header-title-group {
            display: flex;
            align-items: center;
        }
        .header-logo {
            height: 38px;
            max-width: 220px;
            object-fit: contain;
            filter: invert(1); /* Inverts Logo.png from black to white */
        }

        .header-right { display: flex; align-items: center; gap: 12px; }

        /* Unified deck grid */
        .header-center-deck {
            display: flex;
            align-items: center;
            gap: 16px;
        }

        /* ── BPM CENTRAL DISPLAY ───────── */
        .bpm-control-center {
            display: flex;
            align-items: center;
            gap: 10px;
            background: #000000;
            border: 1px solid var(--border-strong);
            padding: 4px 16px;
            border-radius: 6px;
            box-shadow: inset 0 0 10px rgba(84, 61, 38, 0.15);
            height: 38px;
        }
        .bpm-btn {
            background: rgba(255, 255, 255, 0.02);
            border: 1px solid var(--border);
            color: var(--neutral-white) !important;
            width: 32px;
            height: 24px;
            border-radius: 4px;
            display: flex;
            align-items: center;
            justify-content: center;
            cursor: pointer;
            font-family: 'Orbitron', sans-serif;
            font-size: 0.65rem;
            font-weight: 700;
            transition: all 0.2s;
            outline: none;
        }
        .bpm-btn:hover:not(:disabled) {
            background: var(--border);
            color: var(--neutral-white) !important;
            border-color: var(--border);
            box-shadow: 0 0 8px var(--accent-glow);
        }
        .bpm-btn:disabled {
            opacity: 0.25 !important;
            cursor: not-allowed;
        }
        .bpm-display-group {
            display: flex;
            align-items: center;
            gap: 12px;
            min-width: 100px;
            justify-content: center;
        }
        .bpm-text {
            font-family: 'Orbitron', sans-serif;
            font-size: 1.2rem;
            font-weight: 900;
            color: var(--neutral-white) !important;
            text-shadow: 0 0 8px var(--accent-glow);
        }
        .bpm-unit {
            font-size: 0.58rem;
            color: var(--neutral-white) !important;
            font-weight: 400;
        }
        .bpm-header-slider {
            -webkit-appearance: none;
            width: 90px;
            height: 3px;
            background: #111;
            border: 1px solid var(--border);
            outline: none;
            border-radius: 1.5px;
            transition: all 0.2s;
        }
        .bpm-header-slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 8px;
            height: 14px;
            border-radius: 1px;
            background: var(--border);
            cursor: pointer;
            box-shadow: 0 0 6px var(--accent-glow);
        }

        .led {
            width: 8px; height: 8px; border-radius: 50%;
            background-color: #220000;
            box-shadow: inset 0 0 4px rgba(0,0,0,0.5);
            transition: background-color 0.04s, box-shadow 0.04s;
        }
        .led-active {
            background-color: var(--border);
            box-shadow: 0 0 8px var(--border), 0 0 16px var(--accent-glow);
        }

        /* ── SYSTEM STATUS LCD DECK (INTEGRATED) ────────── */
        .system-status-lcd {
            display: flex;
            align-items: center;
            gap: 12px;
            background: #000000;
            border: 1px solid var(--border-strong);
            padding: 4px 12px;
            border-radius: 6px;
            box-shadow: inset 0 0 8px rgba(84, 61, 38, 0.15);
            height: 38px;
        }
        .lcd-metric-box {
            display: flex;
            flex-direction: column;
            gap: 1px;
            min-width: 65px;
        }
        .lcd-row {
            display: flex;
            justify-content: space-between;
            align-items: center;
            font-size: 0.52rem;
            line-height: 1.1;
        }
        .lcd-lbl {
            font-family: 'Orbitron', sans-serif;
            font-weight: 700;
            color: var(--accent-orange) !important;
            font-size: 0.48rem;
            text-transform: uppercase;
        }
        .lcd-val {
            font-family: 'Orbitron', sans-serif;
            font-weight: 700;
            color: var(--neutral-white) !important;
        }
        .lcd-meter-box {
            display: flex;
            flex-direction: column;
            gap: 2px;
            min-width: 75px;
            border-left: 1px solid rgba(84, 61, 38, 0.3);
            border-right: 1px solid rgba(84, 61, 38, 0.3);
            padding: 0 8px;
        }
        .lcd-meter-lbl-row {
            display: flex;
            justify-content: space-between;
            align-items: center;
            font-size: 0.52rem;
            line-height: 1.1;
        }
        .lcd-val-db {
            font-family: 'Orbitron', sans-serif;
            font-weight: 700;
            color: var(--neutral-white) !important;
            font-size: 0.48rem;
        }
        .led-bar-mini {
            height: 4px;
            background: #111;
            border-radius: 2px;
            overflow: hidden;
            display: flex;
            gap: 1.5px;
            width: 100%;
        }
        .led-segment-mini {
            flex: 1;
            background: #200;
            transition: background 0.05s ease;
        }
        .led-segment-mini.active-accent { background: var(--accent-cyan); box-shadow: 0 0 3px var(--cyan-glow); }
        .led-segment-mini.active-sec { background: var(--accent-orange); box-shadow: 0 0 3px var(--orange-glow); }
        .led-segment-mini.active-prim { background: var(--accent-red); box-shadow: 0 0 3px var(--accent-glow); }

        .lcd-led-box {
            display: flex;
            flex-direction: column;
            gap: 2px;
            min-width: 40px;
        }
        .lcd-led-row {
            display: flex;
            align-items: center;
            justify-content: space-between;
            font-size: 0.48rem;
        }
        .ind-dot-mini {
            width: 5px;
            height: 5px;
            border-radius: 50%;
            background: #200;
            transition: background 0.05s;
        }
        .ind-dot-mini.active {
            background: var(--accent-cyan);
            box-shadow: 0 0 5px var(--accent-cyan);
        }

        .actions-bar { display: flex; gap: 6px; }
        .btn {
            background: rgba(255,255,255,0.02); border: 1px solid var(--border-strong);
            color: var(--neutral-white) !important; padding: 5px 10px; border-radius: 4px; cursor: pointer;
            font-family: 'Orbitron', sans-serif; font-weight: 700; font-size: 0.65rem;
            transition: all 0.18s; text-transform: uppercase; letter-spacing: 1px;
        }
        .btn:hover { background: var(--border); color: var(--neutral-white) !important; border-color: var(--border); box-shadow: 0 0 8px var(--accent-glow); }
        .btn-active { background: rgba(84,38,38,0.25); border-color: var(--border); color: var(--neutral-white) !important; }
        .btn-settings { background: rgba(84,38,38,0.12); border-color: var(--border-strong); color: var(--neutral-white) !important; }

        /* ── TWO COLUMN APP CONTAINER ── */
        .app-container {
            flex: 1;
            position: relative;
            width: 100%;
            height: calc(100vh - 64px);
            overflow: hidden;
            background: var(--bg);
        }

        .center-col {
            width: 100%;
            height: 100%;
            display: flex;
            flex-direction: column;
            background: #000000;
            overflow-y: auto;
            padding: 16px 24px;
            gap: 16px;
            transition: padding-right 0.3s ease;
        }

        .right-col {
            position: fixed;
            top: 64px;
            right: -320px;
            width: 320px;
            height: calc(100vh - 64px);
            background: var(--panel-bg);
            border-left: 2px solid var(--border);
            box-shadow: -5px 0 25px rgba(84, 38, 38, 0.2);
            transition: right 0.3s cubic-bezier(0.4, 0, 0.2, 1);
            z-index: 90;
            display: flex;
            flex-direction: column;
            padding: 16px;
            gap: 16px;
            overflow-y: auto;
        }
        .right-col.open {
            right: 0;
        }

        /* ── MASTER MIXER CONSOLE ───────────────────────── */
        .master-mix-console {
            background: var(--panel-bg);
            border: 2px solid var(--border-strong);
            border-radius: 8px;
            padding: 14px;
            display: flex;
            flex-direction: column;
            gap: 10px;
            box-shadow: 0 4px 15px rgba(0,0,0,0.8), inset 0 0 10px rgba(84,61,38,0.1);
            flex-shrink: 0;
        }
        .mixer-header {
            font-family: 'Orbitron', sans-serif;
            font-size: 0.75rem;
            font-weight: 900;
            color: var(--accent-orange) !important;
            letter-spacing: 1.5px;
            text-shadow: 0 0 8px rgba(84, 61, 38, 0.4);
            border-bottom: 1px solid var(--border-strong);
            padding-bottom: 6px;
            text-transform: uppercase;
        }
        .mixer-channels-grid {
            display: grid;
            grid-template-columns: repeat(6, 1fr);
            gap: 8px;
            width: 100%;
        }
        .mixer-channel-strip {
            background: var(--panel-inner);
            border: 1px solid var(--border);
            border-radius: 6px;
            padding: 8px;
            display: flex;
            flex-direction: column;
            gap: 8px;
            box-shadow: inset 0 1px 3px rgba(0,0,0,0.6);
            min-width: 0;
        }
        .chan-title-row {
            display: flex;
            justify-content: space-between;
            align-items: center;
            border-bottom: 1px dashed var(--border);
            padding-bottom: 4px;
            gap: 4px;
        }
        .chan-title {
            font-family: 'Orbitron', sans-serif;
            font-size: 0.65rem;
            font-weight: 900;
            color: var(--neutral-white) !important;
            text-shadow: 0 0 4px var(--accent-glow);
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
        }
        .chan-edit-btn {
            background: transparent;
            border: 1px solid var(--accent-cyan);
            color: var(--neutral-white) !important;
            font-size: 0.52rem;
            font-family: 'Orbitron', sans-serif;
            font-weight: 700;
            padding: 1px 4px;
            border-radius: 3px;
            cursor: pointer;
            transition: all 0.2s;
        }
        .chan-edit-btn:hover {
            background: var(--accent-cyan);
            color: var(--neutral-white) !important;
            box-shadow: 0 0 6px var(--cyan-glow);
        }
        .mixer-widget-box {
            display: flex;
            flex-direction: column;
            gap: 3px;
            background: rgba(255,255,255,0.01);
            border: 1px solid rgba(84, 38, 38, 0.25);
            padding: 5px;
            border-radius: 4px;
        }
        .mixer-lbl-row {
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        .mixer-lbl {
            font-size: 0.5rem;
            font-weight: 900;
            color: var(--neutral-white) !important;
            text-transform: uppercase;
            letter-spacing: 0.5px;
        }
        .mixer-val-txt, .fader-val-txt, .mixer-val-mini {
            font-family: 'Orbitron', sans-serif;
            font-size: 0.5rem;
            font-weight: 700;
            color: var(--neutral-white) !important;
        }
        .mixer-select {
            background: #000;
            border: 1px solid var(--border);
            color: var(--neutral-white) !important;
            font-size: 0.55rem;
            padding: 2px 4px;
            border-radius: 3px;
            outline: none;
            cursor: pointer;
            width: 100%;
        }
        .mixer-select:focus {
            border-color: var(--accent-cyan);
        }
        .mixer-slider-h {
            -webkit-appearance: none;
            width: 100%;
            height: 2px;
            background: #111;
            border: 1px solid var(--border);
            border-radius: 1px;
            outline: none;
        }
        .mixer-slider-h::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 6px;
            height: 10px;
            background: var(--accent-orange);
            border: 1px solid #000;
            border-radius: 1px;
            cursor: pointer;
        }
        .mixer-slider-h::-webkit-slider-thumb:hover {
            background: var(--border);
            box-shadow: 0 0 4px var(--accent-glow);
        }

        /* Fader de Volumen Vertical */
        .fader-widget-vertical {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 4px;
            background: rgba(255,255,255,0.02);
            border: 1px solid var(--border);
            border-radius: 4px;
            padding: 6px;
            height: 140px;
        }
        .fader-lbl-row {
            display: flex;
            justify-content: space-between;
            width: 100%;
            border-bottom: 1px dashed rgba(84,38,38,0.25);
            padding-bottom: 2px;
        }
        .fader-track-container {
            flex: 1;
            display: flex;
            justify-content: center;
            align-items: center;
            width: 100%;
            position: relative;
            padding: 10px 0;
        }
        .fader-slider-v {
            -webkit-appearance: none;
            transform: rotate(-90deg);
            width: 90px;
            height: 4px;
            background: #111;
            border: 1px solid var(--border);
            border-radius: 2px;
            outline: none;
            cursor: pointer;
        }
        .fader-slider-v::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 14px;
            height: 20px;
            background: var(--border);
            border: 2px solid var(--neutral-white);
            border-radius: 2px;
            box-shadow: 0 0 6px var(--accent-glow);
            cursor: pointer;
        }
        .fader-slider-v::-webkit-slider-thumb:hover {
            background: var(--accent-cyan);
            box-shadow: 0 0 8px var(--cyan-glow);
        }

        /* Knobs alineados en fila */
        .mixer-knob-row {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 4px;
            justify-items: center;
        }
        .knob-widget-mini {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 2px;
            width: 100%;
        }
        .mini-knob {
            width: 32px !important;
            height: 32px !important;
        }
        .dial-mini {
            width: 20px !important;
            height: 20px !important;
            top: 6px !important;
            left: 6px !important;
            border-width: 1px !important;
        }
        .pointer-mini {
            width: 1.5px !important;
            height: 6px !important;
            margin-top: 1px !important;
        }
        .clk-btn-group-mini {
            display: grid;
            grid-template-columns: repeat(5, 1fr);
            gap: 2px;
            width: 100%;
        }
        .clk-mini-btn {
            background: #000;
            border: 1px solid var(--border);
            color: var(--neutral-white) !important;
            font-family: 'Orbitron', sans-serif;
            font-size: 0.45rem;
            font-weight: 700;
            padding: 2px 0;
            border-radius: 2px;
            cursor: pointer;
            text-align: center;
            transition: all 0.2s;
        }
        .clk-mini-btn:hover {
            border-color: var(--accent-cyan);
        }
        .clk-mini-btn.active {
            background: var(--accent-cyan);
            border-color: var(--accent-cyan);
            color: var(--neutral-white) !important;
            box-shadow: 0 0 4px var(--cyan-glow);
        }

        .panel-header {
            font-family: 'Orbitron', sans-serif;
            font-size: 0.8rem;
            font-weight: 900;
            color: var(--neutral-white) !important;
            text-shadow: 0 0 6px var(--accent-glow);
            letter-spacing: 2px;
            text-transform: uppercase;
            border-bottom: 1px solid var(--border-strong);
            padding-bottom: 6px;
            margin-bottom: 4px;
        }
        .section {
            background: var(--panel-inner);
            border: 1px solid var(--border);
            border-radius: 6px;
            padding: 12px;
            display: flex;
            flex-direction: column;
            gap: 12px;
            box-shadow: inset 0 1px 3px rgba(0,0,0,0.6);
        }
        .section-title {
            font-size: 0.65rem;
            text-transform: uppercase;
            color: var(--neutral-white) !important;
            letter-spacing: 1.5px;
            font-weight: 700;
            border-bottom: 1px solid var(--border-strong);
            padding-bottom: 4px;
            margin-bottom: 4px;
            text-shadow: 0 0 4px var(--accent-glow);
        }

        /* ── INSTRUMENT TABS (Elektron Style) ───────────── */
        .instrument-tabs {
            display: flex;
            gap: 6px;
            background: var(--panel-bg);
            padding: 6px;
            border-radius: 6px;
            border: 1px solid var(--border-strong);
            flex-shrink: 0;
        }
        .tab-btn {
            flex: 1;
            background: #070709;
            border: 1px solid var(--border);
            color: var(--neutral-white) !important;
            padding: 8px 6px;
            border-radius: 4px;
            cursor: pointer;
            font-family: 'Orbitron', sans-serif;
            font-size: 0.7rem;
            font-weight: 900;
            text-transform: uppercase;
            letter-spacing: 1px;
            text-align: center;
            transition: all 0.2s;
        }
        .tab-btn:hover {
            border-color: var(--border);
            box-shadow: 0 0 4px var(--accent-glow);
        }
        .tab-btn.active {
            background: var(--border);
            color: var(--neutral-white) !important;
            border-color: var(--border);
            box-shadow: 0 0 8px var(--accent-glow);
        }

        /* ── ACTIVE INSTRUMENT PANEL ────────────────────── */
        .active-instrument-panel {
            flex: 1;
            display: flex;
            flex-direction: column;
            gap: 16px;
        }

        .active-synth-section {
            background: var(--panel-bg);
            border: 1px solid var(--border-strong);
            border-radius: 6px;
            padding: 16px;
            display: flex;
            flex-direction: column;
            gap: 16px;
        }

        /* ── ELEKTRON KNOB WIDGETS ──────────────────────── */
        .knobs-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(90px, 1fr));
            gap: 12px;
            justify-items: center;
        }
        .knob-widget {
            display: flex;
            flex-direction: column;
            align-items: center;
            width: 80px;
            gap: 6px;
        }
        .knob-label {
            font-size: 0.58rem;
            text-transform: uppercase;
            color: var(--neutral-white) !important;
            font-weight: 700;
            text-align: center;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
            width: 100%;
        }
        .knob-outer {
            width: 48px;
            height: 48px;
            position: relative;
            cursor: ns-resize;
            touch-action: none;
        }
        .knob-svg { width: 100%; height: 100%; transform: rotate(135deg); }
        .knob-active-ring {
            stroke: var(--border); transition: stroke-dashoffset 0.05s ease;
        }
        .knob-dial {
            width: 32px;
            height: 32px;
            border-radius: 50%;
            background: radial-gradient(circle, #25252b 0%, #0c0c0f 100%);
            border: 1px solid var(--border);
            position: absolute;
            top: 8px;
            left: 8px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.8), inset 0 1px 1px rgba(255,255,255,0.05);
            display: flex;
            justify-content: center;
            align-items: flex-start;
            transition: transform 0.05s ease;
        }
        .knob-pointer {
            width: 2.5px; height: 9px;
            background: var(--border); border-radius: 1px;
            margin-top: 2px; box-shadow: 0 0 4px var(--border);
        }
        .knob-value-display {
            font-family: 'Orbitron', sans-serif;
            font-size: 0.6rem;
            font-weight: 700;
            background: #000000;
            border: 1px solid var(--border);
            color: var(--neutral-white) !important;
            padding: 2px 4px;
            border-radius: 3px;
            min-width: 44px;
            text-align: center;
        }

        .slider-widget { display: flex; flex-direction: column; gap: 4px; background: var(--panel-inner); border: 1px solid var(--border); padding: 10px; border-radius: 4px; }
        .slider-label-row { display: flex; justify-content: space-between; font-size: 0.58rem; text-transform: uppercase; color: var(--neutral-white) !important; font-weight: 700; }
        .slider-label-row span { color: var(--neutral-white) !important; text-overflow: ellipsis; white-space: nowrap; overflow: hidden; }
        .slider-val { font-family: 'Orbitron', sans-serif; color: var(--neutral-white) !important; font-weight: 700; }
        .slider-container { display: flex; align-items: center; height: 14px; }
        
        input[type="range"] {
            -webkit-appearance: none; width: 100%; height: 3px;
            border-radius: 1.5px; background: #000; outline: none;
            border: 1px solid var(--border);
        }
        input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none; appearance: none;
            width: 10px; height: 14px; border-radius: 1px;
            background: #555; border: 1px solid #000; cursor: pointer;
        }
        input[type="range"]::-webkit-slider-thumb:hover { background: var(--border); box-shadow: 0 0 6px var(--accent-glow); }

        .select-widget { display: flex; flex-direction: column; gap: 4px; }
        .select-label { font-size: 0.58rem; text-transform: uppercase; color: var(--neutral-white) !important; font-weight: 700; letter-spacing: 0.5px; text-overflow: ellipsis; white-space: nowrap; overflow: hidden; }
        select {
            background: #000; border: 1px solid var(--border); color: var(--neutral-white) !important;
            padding: 5px 8px; border-radius: 4px;
            font-family: 'Outfit', sans-serif; font-size: 0.7rem;
            outline: none; width: 100%; cursor: pointer;
        }
        select:focus { border-color: var(--border); }

        .right-col-module {
            display: flex;
            flex-direction: column;
            gap: 10px;
            background: var(--panel-inner);
            border: 1px solid var(--border);
            padding: 14px;
            border-radius: 6px;
            box-shadow: inset 0 1px 3px rgba(0,0,0,0.6);
        }
        .right-col-module-title {
            font-family: 'Orbitron', sans-serif;
            font-size: 0.7rem;
            font-weight: 900;
            color: var(--neutral-white) !important;
            border-bottom: 1px solid var(--border-strong);
            padding-bottom: 4px;
            text-shadow: 0 0 4px var(--accent-glow);
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        .ip-list {
            list-style: none; display: flex; flex-direction: column; gap: 5px;
            font-family: 'Orbitron', sans-serif; font-size: 0.65rem; color: var(--neutral-white) !important;
        }
        .emulator-toggle-row { display: flex; justify-content: space-between; align-items: center; }
        .toggle-switch { position: relative; display: inline-block; width: 38px; height: 18px; }
        .toggle-switch input { opacity: 0; width: 0; height: 0; }
        .slider-switch {
            position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0;
            background-color: #222; transition: .3s; border-radius: 18px;
            border: 1px solid var(--border);
        }
        .slider-switch:before {
            position: absolute; content: ""; height: 12px; width: 12px;
            left: 2px; bottom: 2px; background-color: #ffffff; transition: .3s; border-radius: 50%;
        }
        input:checked + .slider-switch { background-color: rgba(84,38,38,0.08); border-color: var(--border); }
        input:checked + .slider-switch:before { background-color: #ffffff; transform: translateX(20px); box-shadow: 0 0 4px var(--border); }

        ::-webkit-scrollbar { width: 4px; height: 4px; }
        ::-webkit-scrollbar-thumb { background: #222; border-radius: 2px; }
        ::-webkit-scrollbar-thumb:hover { background: #333; }
    </style>
</head>
<body>
    <header>
        <div class="header-title-group">
            <img src="/Logo.png" class="header-logo" alt="TR-808 Logo">
        </div>
        
        <!-- HEADER CENTER DECK: BPM + TELEMETRY LCD (NON-INVASIVE) -->
        <div class="header-center-deck">
            <!-- BPM CONTROL Deck -->
            <div class="bpm-control-center">
                <button class="bpm-btn" title="Dividir Tempo (/2)" onclick="onBpmAction('divide')">/2</button>
                <button class="bpm-btn" title="Restar 1 BPM" onclick="onBpmAction('dec')">−</button>
                <div class="bpm-display-group">
                    <div class="led" id="bpm-led"></div>
                    <span class="bpm-text"><span id="bpm-display">140</span> <span class="bpm-unit">BPM</span></span>
                </div>
                <button class="bpm-btn" title="Sumar 1 BPM" onclick="onBpmAction('inc')">+</button>
                <button class="bpm-btn" title="Multiplicar Tempo (x2)" onclick="onBpmAction('multiply')">x2</button>
                <input type="range" class="bpm-header-slider" id="master-bpm-slider"
                       min="60" max="240" step="1" value="140"
                       oninput="onMasterBpmInput(this.value)">
            </div>
            
            <!-- SYSTEM STATUS LCD Deck -->
            <div class="system-status-lcd">
                <!-- CPU & RAM -->
                <div class="lcd-metric-box">
                    <div class="lcd-row"><span class="lcd-lbl">CPU</span><span class="lcd-val" id="hud-cpu">3.5%</span></div>
                    <div class="lcd-row"><span class="lcd-lbl">RAM</span><span class="lcd-val" id="hud-ram">18.2 MB</span></div>
                </div>

                <!-- DB Meter -->
                <div class="lcd-meter-box">
                    <div class="lcd-meter-lbl-row">
                        <span class="lcd-lbl">MST</span>
                        <span class="lcd-val-db" id="hud-db">-6 dB</span>
                    </div>
                    <div class="led-bar-mini" id="hud-master-bar">
                        <div class="led-segment-mini active-accent"></div>
                        <div class="led-segment-mini active-accent"></div>
                        <div class="led-segment-mini active-accent"></div>
                        <div class="led-segment-mini active-accent"></div>
                        <div class="led-segment-mini active-sec"></div>
                        <div class="led-segment-mini"></div>
                    </div>
                </div>

                <!-- OSC & MIDI -->
                <div class="lcd-led-box">
                    <div class="lcd-led-row">
                        <span class="lcd-lbl">OSC</span>
                        <div class="ind-dot-mini active" id="hud-osc"></div>
                    </div>
                    <div class="lcd-led-row">
                        <span class="lcd-lbl">MID</span>
                        <div class="ind-dot-mini" id="hud-midi"></div>
                    </div>
                </div>
            </div>
        </div>

        <div class="header-right">
            <div class="actions-bar">
                <button class="btn btn-settings" id="btn-settings-toggle" onclick="toggleSettingsDrawer()">⚙ Ajustes</button>
            </div>
        </div>
    </header>

    <!-- ── APP CONTAINER ── -->
    <div class="app-container">
        
        <!-- ── COLUMNA CENTRAL (ACTIVE INSTRUMENT TABBED) ── -->
        <div class="center-col">
            
            <!-- MASTER MIXER CONSOLE -->
            <div class="master-mix-console" id="master-mix-console"></div>

            <!-- INSTRUMENT TAB SELECTOR -->
            <div class="instrument-tabs">
                <button class="tab-btn active" id="tab-bombo" onclick="setActiveInstrument('bombo')">BOMBO</button>
                <button class="tab-btn" id="tab-caja" onclick="setActiveInstrument('caja')">CAJA</button>
                <button class="tab-btn" id="tab-platillos" onclick="setActiveInstrument('platillos')">PLATILLOS</button>
                <button class="tab-btn" id="tab-bajo" onclick="setActiveInstrument('bajo')">BAJO</button>
                <button class="tab-btn" id="tab-psycho" onclick="setActiveInstrument('psycho')">PSYCHO</button>
                <button class="tab-btn" id="tab-siringe" onclick="setActiveInstrument('siringe')">SIRINGE</button>
            </div>

            <!-- ACTIVE INSTRUMENT PANEL -->
            <div class="active-instrument-panel" id="active-instrument-panel">
                <!-- Se poblará dinámicamente vía Javascript -->
            </div>

        </div>

        <!-- ── COLUMNA DERECHA (MODULATION / SYSTEM - COLLAPSIBLE SIDE DRAWER) ────── -->
        <div class="right-col">
            
            <div class="panel-header">MODULATION &amp; SYSTEM</div>

            <!-- PRESET MANAGER -->
            <div class="right-col-module">
                <div class="right-col-module-title">Gestión de Presets</div>
                <div style="display:grid; grid-template-columns: 1fr 1fr; gap: 8px;">
                    <button class="btn" id="btn-save" onclick="triggerPreset('save')">Guardar</button>
                    <button class="btn" id="btn-load" onclick="triggerPreset('load')">Cargar</button>
                </div>
            </div>

            <!-- AUTOMATIZACION Y AUTOMATISMO -->
            <div class="right-col-module">
                <div class="right-col-module-title">Grabadora Automática</div>
                <div style="display:grid; grid-template-columns: 1fr 1fr; gap: 8px;">
                    <button class="btn" id="btn-r-rec" onclick="triggerAutomation('record')" style="height:28px;">● REC</button>
                    <button class="btn" id="btn-r-play" onclick="triggerAutomation('play')" style="height:28px;">► PLAY</button>
                </div>
                <button class="btn" id="btn-r-stop" onclick="triggerAutomation('stop')" style="width:100%;height:28px;">■ STOP</button>
            </div>

            <!-- AJUSTES DE SISTEMA -->
            <div class="right-col-module">
                <div class="right-col-module-title">Ajustes de Sistema (Settings)</div>
                
                <!-- RELOJ DE PRUEBA -->
                <div style="display:flex; flex-direction:column; gap:10px; margin-bottom:8px; border-bottom:1px dashed var(--border); padding-bottom:12px;">
                    <div class="emulator-toggle-row">
                        <span style="font-size:0.7rem;color:#ffffff;font-weight:700;">Simulación Reloj</span>
                        <label class="toggle-switch">
                            <input type="checkbox" id="emu-active-toggle" onchange="toggleEmulator(this.checked)">
                            <span class="slider-switch"></span>
                        </label>
                    </div>
                    <div class="slider-widget" style="padding:0; border:none; background:none;">
                        <div class="slider-label-row">
                            <span style="color:#ffffff;">BPM Emu</span>
                            <span class="slider-val" id="emu-bpm-display">120</span>
                        </div>
                        <div class="slider-container">
                            <input type="range" id="emu-bpm-input" min="60" max="240" step="1" value="120"
                                   oninput="setEmulatorBpm(this.value)">
                        </div>
                    </div>
                </div>

                <!-- SALIDA DE AUDIO -->
                <div class="select-widget">
                    <span class="select-label" style="color:#ffffff;font-weight:700;">Dispositivo de Salida</span>
                    <select id="audio-device-select" onchange="setAudioDevice(this.value)">
                        <option value="">Cargando dispositivos...</option>
                    </select>
                </div>
            </div>

            <!-- CONEXION TOUCHOSC (IPs) -->
            <div class="right-col-module">
                <div class="right-col-module-title">Control Remoto OSC</div>
                <ul class="ip-list" id="ip-list"><li>Cargando IPs...</li></ul>
                <div style="font-size:0.58rem;color:#ffffff;line-height:1.3;margin-top:4px">
                    Conecta TouchOSC al puerto <strong>8000</strong> usando cualquiera de estas IPs.
                </div>
            </div>

        </div>

    </div>

    <script>
        let parameters = [];
        let activeKnob = null;
        let startY = 0, startVal = 0;
        let ledInterval = null;
        let currentBpm = 140;
        let externalClockActive = false;
        let activeInstrumentKey = 'bombo';
        let simulatedRam = 18.2;
        let activeInstrumentRendered = false;

        const INSTRUMENTS = [
            { key: 'bombo',     name: 'Bombo',       prefix: '/kick/' },
            { key: 'caja',      name: 'Caja',        prefix: '/snare/' },
            { key: 'platillos', name: 'Platillos',   prefix: '/hat/' },
            { key: 'bajo',      name: 'Bajo WG',     prefix: '/bass/' },
            { key: 'psycho',    name: 'Synth Psyche',prefix: '/syn1/' },
            { key: 'siringe',   name: 'Siringe FDN', prefix: '/syn2/' }
        ];

        /* ── BPM LED ──────────────────────────── */
        function startLedBlinking() {
            if (ledInterval) clearInterval(ledInterval);
            const intervalMs = (60000 / currentBpm) / 2;
            let on = false;
            ledInterval = setInterval(() => {
                const led = document.getElementById('bpm-led');
                if (!led) return;
                on = !on;
                led.classList.toggle('led-active', on);
            }, intervalMs);
        }

        /* ── TOGGLE SETTINGS DRAWER ─────────────────────── */
        function toggleSettingsDrawer() {
            const drawer = document.querySelector('.right-col');
            drawer.classList.toggle('open');
            const btn = document.getElementById('btn-settings-toggle');
            if (btn) btn.classList.toggle('btn-active', drawer.classList.contains('open'));
        }

        /* ── FETCH PARAMS ─────────────────────── */
        async function fetchParams() {
            try {
                const r = await fetch('/api/params');
                if (!r.ok) return;
                parameters = await r.json();

                const bpmParam = parameters.find(p => p.path === '/master/bpm');
                if (bpmParam) {
                    const bv = Math.round(bpmParam.value);
                    document.getElementById('bpm-display').innerText = bv;
                    if (!externalClockActive) {
                        const sl = document.getElementById('master-bpm-slider');
                        if (sl && document.activeElement !== sl) sl.value = bv;
                    }
                    if (Math.abs(currentBpm - bpmParam.value) > 0.5) {
                        currentBpm = bpmParam.value;
                        startLedBlinking();
                    }
                }

                // Sincronizar todos los controles del Mixer Console a las variables OSC globales del diccionario!
                const accentParam = parameters.find(p => p.path === '/master/accent');
                const swingParam = parameters.find(p => p.path === '/master/swing');
                const notaParam = parameters.find(p => p.path === '/master/nota');
                const grooveParam = parameters.find(p => p.path === '/master/groove');

                INSTRUMENTS.forEach(inst => {
                    if (accentParam) {
                        const outer = document.getElementById(`outer-inst-master-accent-${inst.key}`);
                        if (outer && activeKnob !== outer) {
                            outer.setAttribute('data-value', accentParam.value);
                            updateKnobGraphics(outer);
                        }
                        const disp = document.getElementById(`display-inst-master-accent-${inst.key}`);
                        if (disp) disp.innerText = accentParam.value.toFixed(2);
                    }

                    if (swingParam) {
                        const outer = document.getElementById(`outer-inst-master-swing-${inst.key}`);
                        if (outer && activeKnob !== outer) {
                            outer.setAttribute('data-value', swingParam.value);
                            updateKnobGraphics(outer);
                        }
                        const disp = document.getElementById(`display-inst-master-swing-${inst.key}`);
                        if (disp) disp.innerText = swingParam.value.toFixed(2);
                    }

                    if (notaParam) {
                        const sel = document.getElementById(`select-inst-master-nota-${inst.key}`);
                        if (sel && document.activeElement !== sel) {
                            sel.value = Math.round(notaParam.value);
                        }
                    }

                    if (grooveParam) {
                        const sel = document.getElementById(`select-inst-master-groove-${inst.key}`);
                        if (sel && document.activeElement !== sel) {
                            sel.value = Math.round(grooveParam.value);
                        }
                    }

                    const volParam = parameters.find(p => p.path === inst.prefix + 'vol');
                    if (volParam) {
                        const disp = document.getElementById(`display-mixer-vol-${inst.key}`);
                        if (disp) disp.innerText = volParam.value.toFixed(2);
                        const sl = document.getElementById(`slider-mixer-vol-${inst.key}`);
                        if (sl && document.activeElement !== sl) {
                            sl.value = volParam.value;
                        }
                    }

                    const decayKey = inst.key === 'snare' ? 'dec_resorte' : (inst.key === 'bombo' ? 'dec' : (inst.key === 'bajo' ? 'dec' : 'dec'));
                    const decayParam = parameters.find(p => p.path === inst.prefix + decayKey) || parameters.find(p => p.path.endsWith('/dec'));
                    if (decayParam) {
                        const disp = document.getElementById(`display-mixer-decay-${inst.key}`);
                        if (disp) disp.innerText = decayParam.value.toFixed(2);
                        const sl = document.getElementById(`slider-mixer-decay-${inst.key}`);
                        if (sl && document.activeElement !== sl) {
                            sl.value = decayParam.value;
                        }
                    }
                });

                const emuActive = parameters.find(p => p.path === '/emulator/active');
                const emuBpm = parameters.find(p => p.path === '/emulator/bpm');
                if (emuActive) {
                    const t = document.getElementById('emu-active-toggle');
                    if (t && document.activeElement !== t) t.checked = emuActive.value > 0.5;
                }
                if (emuBpm) {
                    const sl = document.getElementById('emu-bpm-input');
                    if (sl && document.activeElement !== sl) {
                        sl.value = Math.round(emuBpm.value);
                        document.getElementById('emu-bpm-display').innerText = Math.round(emuBpm.value);
                    }
                }

                if (!document.getElementById('master-mix-console').innerHTML) {
                    renderMixerConsole();
                }

                // Render active synthesis section with butter smooth dynamic value updates
                if (!activeInstrumentRendered) {
                    renderActiveInstrument();
                } else {
                    updateActiveInstrumentValues();
                }
            } catch(e) { console.error(e); }
        }

        /* ── FETCH STATUS ─────────────────────── */
        async function fetchStatus() {
            try {
                const r = await fetch('/api/status');
                if (!r.ok) return;
                const st = await r.json();

                const ipList = document.getElementById('ip-list');
                if (ipList) {
                    ipList.innerHTML = st.ips.length === 0
                        ? '<li>Localhost (127.0.0.1)</li>'
                        : st.ips.map(ip => `<li>🌐 ${ip}</li>`).join('');
                }

                const sel = document.getElementById('audio-device-select');
                if (sel) {
                    sel.innerHTML = st.devices.map(d =>
                        `<option value="${d.id}" ${d.active ? 'selected' : ''}>${d.name}</option>`
                    ).join('');
                }

                externalClockActive = st.externalClock === true;
                const bpmSlider = document.getElementById('master-bpm-slider');
                if (bpmSlider) bpmSlider.disabled = externalClockActive;
                
                document.querySelectorAll('.bpm-btn').forEach(btn => {
                    btn.disabled = externalClockActive;
                });

                if (externalClockActive && st.bpm > 20) {
                    currentBpm = st.bpm;
                    const bv = Math.round(st.bpm);
                    document.getElementById('bpm-display').innerText = bv;
                    startLedBlinking();
                }

                const ind = document.getElementById('hud-midi');
                if (ind) {
                    ind.classList.add('active');
                    setTimeout(() => ind.classList.remove('active'), 80);
                }

                simulateAudioMeter();
                updateRamMetric();
            } catch(e) { console.error(e); }
        }

        function simulateAudioMeter() {
            const bar = document.getElementById('hud-master-bar');
            if (!bar) return;
            const segments = bar.children;
            const activeCount = Math.floor(Math.random() * 4) + 2;
            for(let i=0; i<segments.length; i++) {
                segments[i].className = 'led-segment-mini';
                if (i < activeCount) {
                    if (i >= 5) {
                        segments[i].classList.add('active-prim');
                    } else if (i >= 4) {
                        segments[i].classList.add('active-sec');
                    } else {
                        segments[i].classList.add('active-accent');
                    }
                }
            }
            const dbVal = -24 + (activeCount * 4);
            document.getElementById('hud-db').innerText = `${dbVal} dB`;
        }

        function updateRamMetric() {
            simulatedRam += (Math.random() - 0.5) * 0.08;
            simulatedRam = Math.max(18.0, Math.min(18.8, simulatedRam));
            const ramEl = document.getElementById('hud-ram');
            if (ramEl) ramEl.innerText = `${simulatedRam.toFixed(1)} MB`;
        }

        function parseStyle(p) {
            const label = p.label || '';
            let style = 'slider', menuItems = [];
            if (label.includes('style:knob')) {
                style = 'knob';
            } else if (label.includes('style:menu')) {
                style = 'menu';
                const m = label.match(/style:menu\s*\{([^}]+)\}/);
                if (m && m[1]) {
                    m[1].split(';').forEach(item => {
                        const parts = item.split(':');
                        if (parts.length === 2) {
                            const text = parts[0].trim().replace(/['"]/g, '');
                            const val = parseFloat(parts[1].trim());
                            if (!isNaN(val)) menuItems.push({ text, value: val });
                        }
                    });
                }
            }
            return { style, menuItems };
        }

        function setActiveInstrument(key) {
            activeInstrumentKey = key;
            INSTRUMENTS.forEach(inst => {
                const btn = document.getElementById(`tab-${inst.key}`);
                if (btn) btn.classList.toggle('active', inst.key === key);
            });
            activeInstrumentRendered = false; // Trigger full DOM re-creation once
            renderActiveInstrument();
        }

        /* ── ZERO LATENCY SELECTOR SYNC ──────────────── */
        function onMasterNotaChange(value) {
            INSTRUMENTS.forEach(inst => {
                const sel = document.getElementById(`select-inst-master-nota-${inst.key}`);
                if (sel) sel.value = value;
            });
            updateParam('/master/nota', value);
        }

        function onMasterGrooveChange(value) {
            INSTRUMENTS.forEach(inst => {
                const sel = document.getElementById(`select-inst-master-groove-${inst.key}`);
                if (sel) sel.value = value;
            });
            updateParam('/master/groove', value);
        }

        function renderMixerConsole() {
            const container = document.getElementById('master-mix-console');
            if (!container || parameters.length === 0) return;
            
            container.innerHTML = `
                <div class="mixer-header">CONSOLA DE MEZCLA MAESTRA (MASTER MIX)</div>
                <div class="mixer-channels-grid">
                    ${INSTRUMENTS.map(inst => {
                        const clkParam = parameters.find(p => p.path === inst.prefix + 'reloj') || { value: 1.0 };
                        const volParam = parameters.find(p => p.path === inst.prefix + 'vol') || { value: 0.8, min: 0, max: 1 };
                        
                        const decayKey = inst.key === 'snare' ? 'dec_resorte' : (inst.key === 'bombo' ? 'dec' : (inst.key === 'bajo' ? 'dec' : 'dec'));
                        const decayParam = parameters.find(p => p.path === inst.prefix + decayKey) || parameters.find(p => p.path.endsWith('/dec')) || { value: 0.2, min: 0.01, max: 2.0 };
                        const decayName = decayParam ? decayParam.path.split('/').pop().toUpperCase() : 'DECAY';

                        return `
                            <div class="mixer-channel-strip" id="chan-${inst.key}">
                                <div class="chan-title-row">
                                    <span class="chan-title">${inst.name.toUpperCase()}</span>
                                    <button class="chan-edit-btn" onclick="setActiveInstrument('${inst.key}')">✎ SÍNTESIS</button>
                                </div>
                                
                                <!-- Reloj Multiplier -->
                                <div class="mixer-widget-box">
                                    <span class="mixer-lbl">Sync Reloj</span>
                                    <div class="clk-btn-group-mini">
                                        ${[0.25, 0.5, 1.0, 2.0, 4.0].map(val => {
                                            const lbl = val === 0.25 ? '÷4' : (val === 0.5 ? '÷2' : (val === 1.0 ? 'x1' : (val === 2.0 ? 'x2' : 'x4')));
                                            const active = Math.abs(clkParam.value - val) < 0.05 ? 'active' : '';
                                            return `<button class="clk-mini-btn ${active}" onclick="updateParam('${clkParam.path || inst.prefix + 'reloj'}', ${val})">${lbl}</button>`;
                                        }).join('')}
                                    </div>
                                </div>

                                <!-- Accent & Swing Knobs (MAPPED GLOBALLY FOR ALL STRIPS) -->
                                <div class="mixer-knob-row">
                                    <div class="knob-widget-mini">
                                        <span class="mixer-lbl">Accent</span>
                                        <div class="knob-outer mini-knob" id="outer-inst-master-accent-${inst.key}"
                                             data-path="/master/accent" data-min="0" data-max="1" data-value="${parameters.find(p => p.path === '/master/accent')?.value || 0.5}">
                                             <svg class="knob-svg" viewBox="0 0 100 100">
                                                 <circle cx="50" cy="50" r="40" stroke="#121217" stroke-width="10" fill="none"/>
                                                 <circle class="knob-active-ring" cx="50" cy="50" r="40"
                                                         stroke-width="10" fill="none" stroke-linecap="round"/>
                                             </svg>
                                             <div class="knob-dial dial-mini"><div class="knob-pointer pointer-mini"></div></div>
                                        </div>
                                        <span class="mixer-val-mini" id="display-inst-master-accent-${inst.key}">0.50</span>
                                    </div>

                                    <div class="knob-widget-mini">
                                        <span class="mixer-lbl">Swing</span>
                                        <div class="knob-outer mini-knob" id="outer-inst-master-swing-${inst.key}"
                                             data-path="/master/swing" data-min="0" data-max="75" data-value="${parameters.find(p => p.path === '/master/swing')?.value || 0}">
                                             <svg class="knob-svg" viewBox="0 0 100 100">
                                                 <circle cx="50" cy="50" r="40" stroke="#121217" stroke-width="10" fill="none"/>
                                                 <circle class="knob-active-ring" cx="50" cy="50" r="40"
                                                         stroke-width="10" fill="none" stroke-linecap="round"/>
                                             </svg>
                                             <div class="knob-dial dial-mini"><div class="knob-pointer pointer-mini"></div></div>
                                        </div>
                                        <span class="mixer-val-mini" id="display-inst-master-swing-${inst.key}">0.00</span>
                                    </div>
                                </div>

                                <!-- Groove & Nota Selectors (MAPPED GLOBALLY FOR ALL STRIPS) -->
                                <div class="mixer-widget-box">
                                    <span class="mixer-lbl">Tonalidad</span>
                                    <select class="mixer-select" id="select-inst-master-nota-${inst.key}" onchange="onMasterNotaChange(this.value)">
                                        <option value="36">C (Do)</option>
                                        <option value="37">C# (Do#)</option>
                                        <option value="38">D (Re)</option>
                                        <option value="39">D# (Re#)</option>
                                        <option value="40">E (Mi)</option>
                                        <option value="41">F (Fa)</option>
                                        <option value="42">F# (Fa#)</option>
                                        <option value="43">G (Sol)</option>
                                        <option value="44">G# (Sol#)</option>
                                        <option value="45">A (La)</option>
                                        <option value="46">A# (La#)</option>
                                        <option value="47">B (Si)</option>
                                    </select>
                                </div>

                                <div class="mixer-widget-box">
                                    <span class="mixer-lbl">Groove</span>
                                    <select class="mixer-select" id="select-inst-master-groove-${inst.key}" onchange="onMasterGrooveChange(this.value)">
                                        <option value="0">1: Ultra Hipnótico</option>
                                        <option value="1">2: Deep Mental</option>
                                        <option value="2">3: Bucle Psíquico</option>
                                        <option value="3">4: Driving Techno</option>
                                        <option value="4">5: Tribal Funk</option>
                                        <option value="5">6: Hardgroove Tradicional</option>
                                        <option value="6">7: Hardgroove Frenético</option>
                                    </select>
                                </div>

                                <!-- Decay Slider (Horizontal) -->
                                <div class="mixer-widget-box">
                                    <div class="mixer-lbl-row">
                                        <span class="mixer-lbl">${decayName.substring(0, 8)}</span>
                                        <span class="mixer-val-txt" id="display-mixer-decay-${inst.key}">${decayParam.value.toFixed(2)}</span>
                                    </div>
                                    <input type="range" class="mixer-slider-h" id="slider-mixer-decay-${inst.key}"
                                           min="${decayParam.min}" max="${decayParam.max}" step="0.01" value="${decayParam.value}"
                                           oninput="updateParam('${decayParam.path}', this.value, 'display-mixer-decay-${inst.key}')">
                                </div>

                                <!-- Vertical Volume Fader -->
                                <div class="fader-widget-vertical">
                                    <div class="fader-lbl-row">
                                        <span class="mixer-lbl">VOLUME</span>
                                        <span class="fader-val-txt" id="display-mixer-vol-${inst.key}">${volParam.value.toFixed(2)}</span>
                                    </div>
                                    <div class="fader-track-container">
                                        <input type="range" class="fader-slider-v" id="slider-mixer-vol-${inst.key}"
                                               min="${volParam.min}" max="${volParam.max}" step="0.01" value="${volParam.value}"
                                               oninput="updateParam('${volParam.path}', this.value, 'display-mixer-vol-${inst.key}')">
                                    </div>
                                </div>
                            </div>
                        `;
                    }).join('')}
                </div>
            `;
            
            // Vincular eventos de drag a todos los knobs del mixer console
            INSTRUMENTS.forEach(inst => {
                ['accent', 'swing'].forEach(k => {
                    const ko = document.getElementById(`outer-inst-master-${k}-${inst.key}`);
                    if (ko) {
                        ko.addEventListener('mousedown', startKnobDrag);
                        ko.addEventListener('touchstart', startKnobDrag, { passive: false });
                        updateKnobGraphics(ko);
                    }
                });
            });
        }

        function renderActiveInstrument() {
            const panel = document.getElementById('active-instrument-panel');
            if (!panel || parameters.length === 0) return;

            const inst = INSTRUMENTS.find(i => i.key === activeInstrumentKey);
            if (!inst) return;

            const allParams = parameters.filter(p => p.path.startsWith(inst.prefix));
            
            const excludedKeys = ['vol', 'volume', 'decay', 'dec', 'dec_cuerpo', 'dec_resorte', 'ataque', 'attack', 'release', 'reloj', 'accent', 'swing', 'nota', 'nota_base', 'groove'];
            const synthParams = allParams.filter(p => {
                const pk = p.path.split('/').pop().toLowerCase();
                return !excludedKeys.includes(pk);
            });

            panel.innerHTML = `
                <!-- VERTICAL SYNTH PANEL (ADVANCED SYNTHESIS ONLY) -->
                <div class="active-synth-section">
                    <div class="panel-header" style="font-size:0.7rem; border:none; margin:0; padding:0; color:var(--neutral-white) !important;">
                        CONTROLES DE SÍNTESIS AVANZADA: ${inst.name.toUpperCase()}
                    </div>
                    <div class="knobs-grid" id="synth-knobs-${inst.key}"></div>
                    <div id="synth-sliders-${inst.key}" style="display:flex; flex-direction:column; gap:10px;"></div>
                    <div id="synth-menus-${inst.key}" style="display:flex; flex-direction:column; gap:10px;"></div>
                </div>
            `;

            const knobGrid = document.getElementById(`synth-knobs-${inst.key}`);
            const sliderContainer = document.getElementById(`synth-sliders-${inst.key}`);
            const menuContainer = document.getElementById(`synth-menus-${inst.key}`);

            synthParams.forEach(p => {
                const parsed = parseStyle(p);
                const paramKey = p.path.split('/').pop();
                const cleanName = paramKey.replace(/_/g, ' ');
                const elemId = `synth-${inst.key}-${paramKey}`;

                if (parsed.style === 'knob') {
                    const w = document.createElement('div');
                    w.id = elemId; w.className = 'knob-widget';
                    w.innerHTML = `
                        <span class="knob-label" title="${cleanName}">${cleanName}</span>
                        <div class="knob-outer" id="outer-${elemId}" data-path="${p.path}" data-min="${p.min}" data-max="${p.max}" data-value="${p.value}">
                            <svg class="knob-svg" viewBox="0 0 100 100"><circle cx="50" cy="50" r="40" stroke="#121217" stroke-width="8" fill="none"/><circle class="knob-active-ring" cx="50" cy="50" r="40" stroke-width="8" fill="none" stroke-linecap="round"/></svg>
                            <div class="knob-dial"><div class="knob-pointer"></div></div>
                        </div>
                        <span class="knob-value-display" id="disp-${elemId}">${p.value.toFixed(2)}</span>
                    `;
                    knobGrid.appendChild(w);
                    const ko = w.querySelector('.knob-outer');
                    ko.addEventListener('mousedown', startKnobDrag);
                    ko.addEventListener('touchstart', startKnobDrag, { passive: false });
                    updateKnobGraphics(ko);
                } else if (parsed.style === 'menu') {
                    const w = document.createElement('div');
                    w.id = elemId; w.className = 'select-widget';
                    const opts = parsed.menuItems.map(o => `<option value="${o.value}">${o.text}</option>`).join('');
                    w.innerHTML = `
                        <span class="select-label">${cleanName}</span>
                        <select id="sel-${elemId}" onchange="updateParam('${p.path}', this.value)">${opts}</select>
                    `;
                    menuContainer.appendChild(w);
                    const sel = document.getElementById(`sel-${elemId}`);
                    if (sel) sel.value = p.value;
                } else {
                    const w = document.createElement('div');
                    w.id = elemId; w.className = 'slider-widget';
                    w.innerHTML = `
                        <div class="slider-label-row"><span>${cleanName}</span><span class="slider-val" id="disp-${elemId}">${p.value.toFixed(2)}</span></div>
                        <div class="slider-container"><input type="range" id="inp-${elemId}" min="${p.min}" max="${p.max}" step="0.001" value="${p.value}" oninput="updateParam('${p.path}', this.value, 'disp-${elemId}')"></div>
                    `;
                    sliderContainer.appendChild(w);
                }
            });

            activeInstrumentRendered = true;
        }

        /* ── DYNAMIC VALUE UPDATE FOR SYNTH PANEL WITHOUT DESTROYING DOM nodes ── */
        function updateActiveInstrumentValues() {
            if (parameters.length === 0) return;
            const inst = INSTRUMENTS.find(i => i.key === activeInstrumentKey);
            if (!inst) return;

            const allParams = parameters.filter(p => p.path.startsWith(inst.prefix));
            const excludedKeys = ['vol', 'volume', 'decay', 'dec', 'dec_cuerpo', 'dec_resorte', 'ataque', 'attack', 'release', 'reloj', 'accent', 'swing', 'nota', 'nota_base', 'groove'];
            const synthParams = allParams.filter(p => {
                const pk = p.path.split('/').pop().toLowerCase();
                return !excludedKeys.includes(pk);
            });

            synthParams.forEach(p => {
                const parsed = parseStyle(p);
                const paramKey = p.path.split('/').pop();
                const elemId = `synth-${inst.key}-${paramKey}`;

                if (parsed.style === 'knob') {
                    const outer = document.getElementById(`outer-${elemId}`);
                    if (outer && activeKnob !== outer) {
                        outer.setAttribute('data-value', p.value);
                        updateKnobGraphics(outer);
                    }
                    const disp = document.getElementById(`disp-${elemId}`);
                    if (disp) disp.innerText = p.value.toFixed(2);
                } else if (parsed.style === 'menu') {
                    const sel = document.getElementById(`sel-${elemId}`);
                    if (sel && document.activeElement !== sel) {
                        sel.value = p.value;
                    }
                } else {
                    const inp = document.getElementById(`inp-${elemId}`);
                    if (inp && document.activeElement !== inp) {
                        inp.value = p.value;
                    }
                    const disp = document.getElementById(`disp-${elemId}`);
                    if (disp) disp.innerText = p.value.toFixed(2);
                }
            });
        }

        function startKnobDrag(e) {
            activeKnob = e.currentTarget;
            startY = e.clientY || (e.touches ? e.touches[0].clientY : 0);
            startVal = parseFloat(activeKnob.getAttribute('data-value'));
            document.addEventListener('mousemove', dragKnob);
            document.addEventListener('touchmove', dragKnob, { passive: false });
            document.addEventListener('mouseup', stopKnobDrag);
            document.addEventListener('touchend', stopKnobDrag);
            e.preventDefault();
        }
        function dragKnob(e) {
            if (!activeKnob) return;
            const cy = e.clientY || (e.touches ? e.touches[0].clientY : 0);
            const deltaY = startY - cy;
            const min = parseFloat(activeKnob.getAttribute('data-min'));
            const max = parseFloat(activeKnob.getAttribute('data-max'));
            let nv = startVal + (deltaY / 200) * (max - min);
            nv = Math.max(min, Math.min(max, nv));
            
            const path = activeKnob.getAttribute('data-path');
            activeKnob.setAttribute('data-value', nv);
            updateKnobGraphics(activeKnob);
            updateParam(path, nv);
            
            // Feedback instantáneo de sincronización global para knobs en Mixer Console
            if (path === '/master/accent' || path === '/master/swing') {
                const k = path === '/master/accent' ? 'accent' : 'swing';
                INSTRUMENTS.forEach(inst => {
                    const otherKnob = document.getElementById(`outer-inst-master-${k}-${inst.key}`);
                    if (otherKnob && otherKnob !== activeKnob) {
                        otherKnob.setAttribute('data-value', nv);
                        updateKnobGraphics(otherKnob);
                    }
                });
            }
            if (e.cancelable) e.preventDefault();
        }
        function stopKnobDrag() {
            activeKnob = null;
            document.removeEventListener('mousemove', dragKnob);
            document.removeEventListener('touchmove', dragKnob);
            document.removeEventListener('mouseup', stopKnobDrag);
            document.removeEventListener('touchend', stopKnobDrag);
        }
        function updateKnobGraphics(knob) {
            const min = parseFloat(knob.getAttribute('data-min'));
            const max = parseFloat(knob.getAttribute('data-max'));
            const val = parseFloat(knob.getAttribute('data-value'));
            const pct = (val - min) / (max - min);
            const circ = 251.2;
            const arc = circ * 0.75;
            const offset = circ - pct * arc;
            const ring = knob.querySelector('.knob-active-ring');
            if (ring) {
                ring.setAttribute('stroke-dasharray', `${circ}`);
                ring.setAttribute('stroke-dashoffset', `${offset}`);
            }
            const dial = knob.querySelector('.knob-dial');
            if (dial) dial.style.transform = `rotate(${pct * 270 - 135}deg)`;
            
            const disp = knob.closest('.knob-widget-mini')?.querySelector('.mixer-val-mini') || knob.closest('.knob-widget')?.querySelector('.knob-value-display');
            if (disp) disp.innerText = val.toFixed(2);
        }

        function onMasterBpmInput(val) {
            if (externalClockActive) return;
            document.getElementById('bpm-display').innerText = Math.round(val);
            currentBpm = parseFloat(val);
            updateParam('/master/bpm', val);
        }
        function onBpmAction(action) {
            if (externalClockActive) return;
            let targetBpm = currentBpm;
            if (action === 'divide') targetBpm = Math.max(60, currentBpm / 2);
            else if (action === 'multiply') targetBpm = Math.min(240, currentBpm * 2);
            else if (action === 'dec') targetBpm = Math.max(60, currentBpm - 1);
            else if (action === 'inc') targetBpm = Math.min(240, currentBpm + 1);
            targetBpm = Math.round(targetBpm);
            currentBpm = targetBpm;
            document.getElementById('bpm-display').innerText = targetBpm;
            const bpmSlider = document.getElementById('master-bpm-slider');
            if (bpmSlider) bpmSlider.value = targetBpm;
            updateParam('/master/bpm', targetBpm);
            startLedBlinking();
        }
        async function updateParam(path, value, displayId = null) {
            if (displayId) {
                const el = document.getElementById(displayId);
                if (el) el.innerText = Number(value).toFixed(2);
            }
            try { await fetch(`/api/set?path=${encodeURIComponent(path)}&value=${value}`); } catch(e) { console.error(e); }
        }
        async function triggerPreset(action) {
            try {
                await fetch(`/api/set?path=${encodeURIComponent('/preset/'+action)}&value=1`);
                alert(`Preset ${action === 'save' ? 'guardado' : 'cargado'} con éxito.`);
                setTimeout(fetchParams, 300);
            } catch(e) { console.error(e); }
        }
        async function triggerAutomation(action) {
            try {
                await fetch(`/api/set?path=${encodeURIComponent('/automation/'+action)}&value=1`);
                ['btn-record','btn-play','btn-stop','btn-r-rec','btn-r-play','btn-r-stop'].forEach(id => {
                    const el = document.getElementById(id);
                    if (el) el.classList.remove('btn-active');
                });
                if (action === 'record') {
                    document.getElementById('btn-r-rec').classList.add('btn-active');
                } else if (action === 'play') {
                    document.getElementById('btn-r-play').classList.add('btn-active');
                }
            } catch(e) { console.error(e); }
        }
        async function setAudioDevice(id) {
            if (!id) return;
            try { await fetch(`/api/audio/set?id=${id}`); } catch(e) { console.error(e); }
        }

        /* ── EMULATOR ──────────────────────────── */
        function toggleEmulator(active) { updateParam('/emulator/active', active ? 1 : 0); }
        function setEmulatorBpm(bpm) {
            document.getElementById('emu-bpm-display').innerText = Math.round(bpm);
            updateParam('/emulator/bpm', bpm);
        }

        /* ── INIT ──────────────────────────────── */
        fetchParams();
        fetchStatus();
        setInterval(fetchParams, 1000);
        setInterval(fetchStatus, 2000);
    </script>
</body>
</html>)html";

        std::string headers = "HTTP/1.1 200 OK\r\n"
                              "Content-Length: " + std::to_string(html.length()) + "\r\n"
                              "Content-Type: text/html; charset=utf-8\r\n"
                              "Access-Control-Allow-Origin: *\r\n"
                              "Connection: close\r\n\r\n";
        send(client_fd, (headers + html).c_str(), headers.length() + html.length(), 0);

    }

    void serveLogo(int client_fd) {
        std::ifstream file("Logo.png", std::ios::binary);
        if (!file.is_open()) {
            std::string body = "404 Not Found";
            std::string headers = "HTTP/1.1 404 Not Found\r\n"
                                  "Content-Length: " + std::to_string(body.length()) + "\r\n"
                                  "Content-Type: text/plain\r\n"
                                  "Connection: close\r\n\r\n";
            send(client_fd, (headers + body).c_str(), headers.length() + body.length(), 0);
            return;
        }

        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        std::string headers = "HTTP/1.1 200 OK\r\n"
                              "Content-Length: " + std::to_string(buffer.size()) + "\r\n"
                              "Content-Type: image/png\r\n"
                              "Access-Control-Allow-Origin: *\r\n"
                              "Connection: close\r\n\r\n";
        
        send(client_fd, headers.c_str(), headers.length(), 0);
        send(client_fd, buffer.data(), buffer.size(), 0);
    }
"""

with open(file_path, "r", encoding="utf-8") as f:
    content = f.read()

# 1. Update the HTTP Server request routing in handleRequest to direct /Logo.png /logo.png
old_route = '        if (path == "/" || path == "/index.html") {\n            serveHTML(client_fd);\n        }'
new_route = '        if (path == "/" || path == "/index.html") {\n            serveHTML(client_fd);\n        }\n        else if (path == "/Logo.png" || path == "/logo.png") {\n            serveLogo(client_fd);\n        }'

if old_route in content:
    content = content.replace(old_route, new_route, 1)
    print("Added C++ routing for /Logo.png successfully!")
else:
    # If already replaced in a previous attempt, let's keep it safe
    print("Routing for /Logo.png already exists or route not found.")

# 2. Locate serveHTML block and replace it
start_tag = "    void serveHTML(int client_fd) {"
end_tag = "    void serveParams(int client_fd) {"

start_idx = content.find(start_tag)
end_idx = content.find(end_tag)

if start_idx == -1 or end_idx == -1:
    print("Error: Could not find serveHTML or serveParams in OscServer.cpp!")
    exit(1)

content = content[:start_idx] + optimized_html_content + "\n    " + content[end_idx:]

with open(file_path, "w", encoding="utf-8") as f:
    f.write(content)

print("OscServer.cpp full optimized update completed successfully!")
