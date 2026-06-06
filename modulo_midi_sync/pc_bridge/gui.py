import tkinter as tk
import threading
import asyncio
import aalink
import serial
import serial.tools.list_ports
from pythonosc.udp_client import SimpleUDPClient
from pythonosc.dispatcher import Dispatcher
from pythonosc.osc_server import AsyncIOOSCUDPServer
import websockets
import json
import winsound
import time

BG_COLOR = "#1e1e1e"
PANEL_BG = "#2d2d2d"
NEUTRAL_WHITE = "#e0e0e0"
ACCENT_ORANGE = "#ff8c00"
BORDER = "#444444"
BORDER_STRONG = "#666666"
RED = "#ff3333"
CYAN = "#00ffff"
GREEN = "#00ff00"

class SyncApp:
    def __init__(self, master):
        self.master = master
        master.title("Bazz Sync Bridge")
        master.geometry("360x560")
        master.configure(bg=BG_COLOR)

        self.osc_client = SimpleUDPClient("127.0.0.1", 8000)
        self.serial_port = None
        self.phase_offset_ms = 0.0
        self.test_metronome_beats = 0
        self.sync_direction = "link_to_bazz"
        
        self.setup_ui()
        self.connect_serial_loop()
        
        self.link = None
        self.running = True
        self.is_playing = True
        self.ws_clients = set()
        
        # OSC Server para escuchar al Sintetizador (RX)
        self.dispatcher = Dispatcher()
        self.dispatcher.map("/synth/ack", self.handle_synth_ack)
        self.dispatcher.map("/synth/beat", self.handle_synth_beat)

        self.thread = threading.Thread(target=self.start_asyncio_loop, daemon=True)
        self.thread.start()

        self.thread_poll = threading.Thread(target=self.poll_bazz_bpm_loop, daemon=True)
        self.thread_poll.start()

        self.master.after(500, self.update_bpm_display)

    def handle_synth_ack(self, address, *args):
        # Escaneo de señal que llega desde el sintetizador
        if len(args) > 0:
            ack_type = args[0]
            if ack_type == "reset":
                self.trigger_ui_rx(GREEN)
                self.broadcast_ws({"type": "rx", "color": GREEN})
            elif ack_type == "sync":
                self.trigger_ui_rx(CYAN)
                self.broadcast_ws({"type": "rx", "color": "#00ffff"})

    def handle_synth_beat(self, address, *args):
        # Cuando el sintetizador reporta un beat (paso % 4 == 0)
        step = args[0] if len(args) > 0 else 0
        self.broadcast_ws({"type": "beat", "step": step})
        # Actualizar la UI del bridge para dar feedback visual
        pulse_type = 1 if step == 0 else 2
        self.master.after_idle(lambda: self.draw_osc_trace(pulse_type))
        self.master.after(150, lambda: self.draw_osc_trace(0))

    def broadcast_ws(self, msg_dict):
        if not self.ws_clients: return
        msg = json.dumps(msg_dict)
        for client in self.ws_clients:
            asyncio.create_task(client.send(msg))

    async def websocket_handler(self, websocket):
        self.ws_clients.add(websocket)
        try:
            await websocket.wait_closed()
        finally:
            self.ws_clients.remove(websocket)

    def connect_serial_loop(self):
        if self.serial_port is None:
            ports = serial.tools.list_ports.comports()
            for p in ports:
                if "CH340" in p.description or "CP210" in p.description or "Serial" in p.description or "USB" in p.description:
                    try:
                        self.serial_port = serial.Serial(p.device, 115200, timeout=0)
                        self.lbl_serial_status.config(text=f"ESP32 CONECTADO: {p.device}", fg="#00ff00")
                        break
                    except:
                        pass
            if self.serial_port is None:
                self.lbl_serial_status.config(text="Buscando ESP32 COM...", fg=RED)
        
        if self.serial_port is not None:
            try:
                if not self.serial_port.is_open:
                    raise Exception("Port closed")
            except:
                self.serial_port = None
                self.lbl_serial_status.config(text="Conexión perdida. Buscando...", fg=RED)

        self.master.after(2000, self.connect_serial_loop)

    def setup_ui(self):
        main_frame = tk.Frame(self.master, bg=PANEL_BG, bd=1, relief="ridge")
        main_frame.place(relx=0.05, rely=0.05, relwidth=0.9, relheight=0.9)

        self.lbl_title = tk.Label(main_frame, text="BAZZ SYNC BRIDGE", font=("Orbitron", 12, "bold"), bg=PANEL_BG, fg=ACCENT_ORANGE)
        self.lbl_title.pack(pady=(10, 0))

        self.lbl_serial_status = tk.Label(main_frame, text="Iniciando...", font=("Orbitron", 8), bg=PANEL_BG, fg=NEUTRAL_WHITE)
        self.lbl_serial_status.pack(pady=(0, 10))

        tk.Label(main_frame, text="SEÑAL DE SALIDA (SQUARE WAVE)", font=("Orbitron", 8), bg=PANEL_BG, fg=NEUTRAL_WHITE).pack()
        self.osc_canvas = tk.Canvas(main_frame, width=280, height=60, bg="#0a0a0a", highlightthickness=1, highlightbackground=BORDER)
        self.osc_canvas.pack(pady=(0, 10))
        self.draw_osc_trace(0)

        led_frame = tk.Frame(main_frame, bg=PANEL_BG)
        led_frame.pack(pady=5)

        tx_frame = tk.Frame(led_frame, bg=PANEL_BG)
        tx_frame.grid(row=0, column=0, padx=20)
        tk.Label(tx_frame, text="SYNC TX", font=("Orbitron", 8), bg=PANEL_BG, fg=NEUTRAL_WHITE).pack()
        self.canvas_tx = tk.Canvas(tx_frame, width=20, height=20, bg=PANEL_BG, highlightthickness=0)
        self.led_tx = self.canvas_tx.create_oval(2, 2, 18, 18, fill="#220000", outline=BORDER)
        self.canvas_tx.pack(pady=5)

        rx_frame = tk.Frame(led_frame, bg=PANEL_BG)
        rx_frame.grid(row=0, column=1, padx=20)
        tk.Label(rx_frame, text="SYNTH RX", font=("Orbitron", 8), bg=PANEL_BG, fg=NEUTRAL_WHITE).pack()
        self.canvas_rx = tk.Canvas(rx_frame, width=20, height=20, bg=PANEL_BG, highlightthickness=0)
        self.led_rx = self.canvas_rx.create_oval(2, 2, 18, 18, fill="#002200", outline=BORDER)
        self.canvas_rx.pack(pady=5)

        self.lbl_offset = tk.Label(main_frame, text=f"Phase Nudge: {self.phase_offset_ms:.1f} ms", font=("Orbitron", 9), bg=PANEL_BG, fg=NEUTRAL_WHITE)
        self.lbl_offset.pack(pady=(10, 0))
        btn_frame = tk.Frame(main_frame, bg=PANEL_BG)
        btn_frame.pack(pady=5)

        btn_style = {"bg": BG_COLOR, "fg": NEUTRAL_WHITE, "font": ("Orbitron", 10, "bold"), "activebackground": BORDER, "activeforeground": NEUTRAL_WHITE, "relief": "flat", "bd": 1, "highlightbackground": BORDER_STRONG}
        
        tk.Button(btn_frame, text="< -1ms", width=8, command=self.nudge_minus, **btn_style).grid(row=0, column=0, padx=5)
        tk.Button(btn_frame, text="+1ms >", width=8, command=self.nudge_plus, **btn_style).grid(row=0, column=1, padx=5)

        bpm_frame = tk.Frame(main_frame, bg=PANEL_BG)
        bpm_frame.pack(pady=10)
        
        self.bpm_locked = False
        self.bpm_var = tk.StringVar(value="120.00")
        self.entry_bpm = tk.Entry(bpm_frame, textvariable=self.bpm_var, font=("Orbitron", 10), width=6, justify='center', bg=BG_COLOR, fg=NEUTRAL_WHITE, insertbackground=NEUTRAL_WHITE)
        self.entry_bpm.grid(row=0, column=0, padx=5)
        
        self.btn_lock = tk.Button(bpm_frame, text="LOCK", width=6, command=self.toggle_lock, **btn_style)
        self.btn_lock.grid(row=0, column=1, padx=2)
        
        self.btn_play = tk.Button(bpm_frame, text="PLAY", width=6, command=self.toggle_play, **btn_style)
        self.btn_play.grid(row=0, column=2, padx=2)

        tk.Button(bpm_frame, text="SET", command=self.send_bpm, **btn_style).grid(row=0, column=3, padx=5)

        self.btn_direction = tk.Button(main_frame, text="MODO: LINK -> BAZZ", command=self.toggle_sync_direction, **btn_style)
        self.btn_direction.pack(pady=5)

        self.btn_metro = tk.Button(main_frame, text="Test Metrónomo\n(4 Compases)", command=self.activate_metronome, **btn_style)
        self.btn_metro.pack(pady=10)

    def draw_osc_trace(self, pulse_type):
        self.osc_canvas.delete("trace")
        self.osc_canvas.create_line(0, 50, 280, 50, fill="#333", tags="trace")
        
        if pulse_type == 1:
            points = [0, 50, 20, 50, 20, 10, 150, 10, 150, 50, 280, 50]
            self.osc_canvas.create_line(points, fill=GREEN, width=3, tags="trace")
            self.osc_canvas.create_text(85, 25, text="50ms (BEAT 1 - COMPÁS)", fill=GREEN, font=("Orbitron", 7, "bold"), tags="trace")
        elif pulse_type == 2:
            points = [0, 50, 20, 50, 20, 10, 40, 10, 40, 50, 280, 50]
            self.osc_canvas.create_line(points, fill=CYAN, width=2, tags="trace")
            self.osc_canvas.create_text(30, 25, text="10ms", fill=CYAN, font=("Orbitron", 7), tags="trace")

    def toggle_lock(self):
        self.bpm_locked = not self.bpm_locked
        if self.bpm_locked:
            self.entry_bpm.config(fg=RED)
            self.btn_lock.config(text="UNLOCK")
            try:
                self.osc_client.send_message("/master/bpm_lock", 1)
            except: pass
        else:
            self.entry_bpm.config(fg=NEUTRAL_WHITE)
            self.btn_lock.config(text="LOCK")
            try:
                self.osc_client.send_message("/master/bpm_lock", 0)
            except: pass

    def toggle_play(self):
        self.is_playing = not self.is_playing
        if self.is_playing:
            self.btn_play.config(text="PAUSE", fg=GREEN)
        else:
            self.btn_play.config(text="PLAY", fg=NEUTRAL_WHITE)

    def update_bpm_display(self):
        if hasattr(self, 'current_peers'):
            self.lbl_title.config(text=f"ABLETON LINK ({self.current_peers} Peers)")
            if not self.bpm_locked:
                if self.sync_direction == "link_to_bazz":
                    self.bpm_var.set(f"{self.current_tempo:.2f}")
                    try:
                        self.osc_client.send_message("/master/bpm", self.current_tempo)
                    except: pass
        self.master.after(500, self.update_bpm_display)

    def trigger_ui_tx(self, color, is_beat_1):
        # 1. Enviar Websocket asíncrono inmediatamente antes de procesar la UI
        if is_beat_1:
            self.broadcast_ws({"type": "tx", "pulse": 1, "color": color})
        else:
            self.broadcast_ws({"type": "tx", "pulse": 2, "color": color})
            
        asyncio.create_task(self.delayed_ws_clear())

        # 2. Dibujar UI (Tkinter) usando after e after_idle
        self.master.after_idle(lambda: self.canvas_tx.itemconfig(self.led_tx, fill=color, outline=color))
        self.master.after(50, lambda: self.canvas_tx.itemconfig(self.led_tx, fill="#220000", outline=BORDER))
        
        if is_beat_1:
            self.master.after_idle(lambda: self.draw_osc_trace(1))
        else:
            self.master.after_idle(lambda: self.draw_osc_trace(2))
        
        self.master.after(150, lambda: self.draw_osc_trace(0))

    async def delayed_ws_clear(self):
        await asyncio.sleep(0.15)
        self.broadcast_ws({"type": "tx", "pulse": 0})

    def trigger_ui_rx(self, color):
        self.master.after_idle(lambda: self.canvas_rx.itemconfig(self.led_rx, fill=color, outline=color))
        self.master.after(50, lambda: self.canvas_rx.itemconfig(self.led_rx, fill="#002200", outline=BORDER))

    def play_sound(self, filename):
        try:
            winsound.PlaySound(filename, winsound.SND_FILENAME | winsound.SND_ASYNC | winsound.SND_NODEFAULT)
        except:
            pass

    def start_asyncio_loop(self):
        self.loop = asyncio.new_event_loop()
        asyncio.set_event_loop(self.loop)
        self.loop.run_until_complete(self.main_asyncio_loop())

    async def main_asyncio_loop(self):
        # Iniciar Servidor OSC (Puerto 8001)
        self.osc_server = AsyncIOOSCUDPServer(("127.0.0.1", 8001), self.dispatcher, asyncio.get_event_loop())
        self.transport, self.protocol = await self.osc_server.create_serve_endpoint()
        
        # Iniciar Servidor WebSocket (Puerto 8002) para enviar eventos a la Web UI
        async with websockets.serve(self.websocket_handler, "127.0.0.1", 8002):
            # Iniciar loop de Ableton Link
            await self.link_loop()

    async def link_loop(self):
        self.link = aalink.Link(120.0)
        self.link.enabled = True
        
        ticks_per_beat = 24
        sync_id_counter = 1
        last_processed_tick = -1
        
        while self.running:
            beat = self.link.beat
            tempo = self.link.tempo
            
            self.current_tempo = tempo
            self.current_peers = self.link.num_peers
            
            next_tick_beat = ((int(beat * ticks_per_beat)) + 1) / ticks_per_beat
            
            offset_beats = (self.phase_offset_ms / 1000.0) * (tempo / 60.0)
            target_beat = next_tick_beat - offset_beats
            
            await self.link.sync(target_beat)
            
            if not self.is_playing:
                await asyncio.sleep(0.01)
                continue

            tick_index = int(next_tick_beat * ticks_per_beat)
            if tick_index == last_processed_tick:
                await asyncio.sleep(0.002)
                continue
            last_processed_tick = tick_index
            
            if tick_index % 6 == 0:
                # 16 pasos = 4 beats = 96 ticks. Cada paso = 1 semicorchea = 6 ticks.
                step_index = (tick_index // 6) % 16
                
                is_beat_1 = (step_index == 0)
                is_measure_start = (step_index % 4 == 0 and not is_beat_1)
                
                if is_beat_1:
                    cmd_byte = 0xF9
                elif is_measure_start:
                    cmd_byte = 0xF8
                else:
                    cmd_byte = 0xF7
                
                # Enviar a hardware (ESP32) y Windows OSC (solo si LINK -> BAZZ)
                if self.sync_direction == "link_to_bazz":
                    if self.serial_port:
                        try:
                            self.serial_port.write(bytes([cmd_byte]))
                        except:
                            pass
                            
                    try:
                        self.osc_client.send_message("/clock/sync", "")
                        if is_beat_1:
                            sync_id_counter += 1
                            self.osc_client.send_message("/master/sync_reset", sync_id_counter)
                    except:
                        pass
                
                # Update UI visuals for all 16 steps
                if is_beat_1:
                    color = GREEN
                elif is_measure_start:
                    color = RED
                else:
                    color = CYAN
                    
                self.master.after_idle(lambda c=color: self.btn_play.config(bg=c, fg="#000"))
                self.master.after(50, lambda: self.btn_play.config(bg=BG_COLOR, fg=GREEN))
                
                self.trigger_ui_tx(color, is_beat_1)

                if step_index % 4 == 0:
                    if self.test_metronome_beats > 0:
                        if is_beat_1:
                            self.play_sound("high_click.wav")
                        else:
                            self.play_sound("low_click.wav")
                        self.test_metronome_beats -= 1
                        if self.test_metronome_beats <= 0:
                            self.master.after_idle(lambda: self.btn_metro.config(text="Test Metrónomo\n(4 Compases)", bg=BG_COLOR))

    def nudge_plus(self):
        self.phase_offset_ms += 1.0
        self.lbl_offset.config(text=f"Phase Nudge: {self.phase_offset_ms:.1f} ms")
        try:
            self.osc_client.send_message("/master/sync_offset", self.phase_offset_ms)
        except: pass

    def nudge_minus(self):
        self.phase_offset_ms -= 1.0
        self.lbl_offset.config(text=f"Phase Nudge: {self.phase_offset_ms:.1f} ms")
        try:
            self.osc_client.send_message("/master/sync_offset", self.phase_offset_ms)
        except: pass

    def send_bpm(self):
        try:
            bpm = float(self.bpm_var.get())
            if self.link:
                self.link.tempo = bpm
            try:
                self.osc_client.send_message("/master/bpm", bpm)
            except: pass
        except ValueError:
            pass

    def toggle_sync_direction(self):
        if self.sync_direction == "link_to_bazz":
            self.sync_direction = "bazz_to_link"
            self.btn_direction.config(text="MODO: BAZZ -> LINK", fg=ACCENT_ORANGE)
        else:
            self.sync_direction = "link_to_bazz"
            self.btn_direction.config(text="MODO: LINK -> BAZZ", fg=NEUTRAL_WHITE)

    def poll_bazz_bpm_loop(self):
        import urllib.request
        import json
        while self.running:
            if self.sync_direction == "bazz_to_link":
                try:
                    req = urllib.request.Request("http://127.0.0.1:8000/api/status", headers={'User-Agent': 'Mozilla/5.0'})
                    with urllib.request.urlopen(req, timeout=0.4) as response:
                        data = json.loads(response.read().decode())
                        bazz_bpm = float(data.get("bpm", 140.0))
                        if self.link and abs(self.link.tempo - bazz_bpm) > 0.05:
                            self.link.tempo = bazz_bpm
                            self.current_tempo = bazz_bpm
                            self.master.after_idle(lambda v=bazz_bpm: self.bpm_var.set(f"{v:.2f}"))
                except Exception as e:
                    pass
            time.sleep(0.3)

    def activate_metronome(self):
        self.test_metronome_beats = 16 
        self.btn_metro.config(text="Sonando...", bg="#4a2c2c")

    def on_closing(self):
        self.running = False
        if hasattr(self, 'transport'):
            self.transport.close()
        if self.serial_port:
            self.serial_port.close()
        self.master.destroy()

if __name__ == "__main__":
    root = tk.Tk()
    app = SyncApp(root)
    root.protocol("WM_DELETE_WINDOW", app.on_closing)
    root.mainloop()
