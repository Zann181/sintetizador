// ===========================================================================
// BAZZ C++ SYNC BRIDGE  –  Ableton Link + Dear ImGui Edition
// ===========================================================================
// Synchronizes to Ableton Link, sends MIDI clock bytes to the ESP32 via
// serial COM, and sends /clock/sync + /master/sync_reset to the synthesizer
// via OSC UDP.  Measures both scheduling jitter and OSC round-trip latency.
// Features a graphical GUI using Dear ImGui and GLFW.
// ===========================================================================

#include <ableton/Link.hpp>
#include <lo/lo.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include <cmath>
#include <csignal>
#include <algorithm>
#include <vector>
#include <mutex>
#include "App.h"

// ImGui & GLFW
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// ── Platform-specific includes ──────────────────────────────────────────────
#ifdef _WIN32
#   define NOMINMAX
#   include <windows.h>
#   include <mmsystem.h>
#   pragma comment(lib, "winmm")
    typedef HANDLE SerialHandle;
#   define INVALID_SERIAL_HANDLE INVALID_HANDLE_VALUE
#else
#   include <fcntl.h>
#   include <termios.h>
#   include <unistd.h>
    typedef int SerialHandle;
#   define INVALID_SERIAL_HANDLE -1
#endif

// ── Global control ──────────────────────────────────────────────────────────
std::atomic<bool>     keep_running{true};
std::atomic<uint64_t> last_ping_time_us{0};
std::atomic<double>   last_rtt_ms{0.0};
std::atomic<double>   last_jitter_ms{0.0};
std::atomic<int>      peers_count{0};
std::atomic<int>      current_step{0};
std::atomic<double>   current_tempo{120.0};
std::atomic<bool>     is_playing{false};
std::atomic<double>   phase_offset_ms{0.0};

// To flash LEDs and Trace
std::atomic<uint64_t> last_tx_time_us{0};
std::atomic<uint64_t> last_rx_time_us{0};
std::atomic<uint64_t> last_trace_time_us{0};
std::atomic<int>      last_tx_pulse_type{0}; // 1 = Beat 1, 2 = Other beats
std::atomic<int>      last_rx_pulse_type{0}; // 1 = Beat 1, 2 = Other beats
std::atomic<bool>     tempo_changed_by_gui{false};
std::atomic<bool>     play_changed_by_gui{false};
std::atomic<bool>     is_master{true}; // True = LEAD (Master), False = FOLLOW (Slave)

// ── WebSocket Server ────────────────────────────────────────────────────────
struct WsData {};
uWS::Loop* ws_loop = nullptr;
uWS::App*  ws_app  = nullptr;

void broadcast_ws(const std::string& msg) {
    if (ws_loop && ws_app) {
        ws_loop->defer([msg]() {
            if (ws_app) {
                ws_app->publish("bazz_sync", msg, uWS::OpCode::TEXT, false);
            }
        });
    }
}

void ws_server_thread_func() {
    uWS::App app;
    ws_app = &app;
    
    app.ws<WsData>("/*", {
        .open = [](auto *ws) {
            ws->subscribe("bazz_sync");
        }
    }).listen(8002, [](auto *listen_socket) {
        if (listen_socket) {
            std::cout << "WS Server listening on port 8002" << std::endl;
        } else {
            std::cerr << "Failed to listen on WS port 8002" << std::endl;
        }
    });
    
    ws_loop = uWS::Loop::get();
    app.run();
}

void signal_handler(int /*signum*/) {
    keep_running = false;
}

// ── Cross-platform Serial API ────────────────────────────────────────────────
SerialHandle openSerialPort(const std::string& portName) {
#ifdef _WIN32
    std::string fullPortName = "\\\\.\\" + portName;
    HANDLE hSerial = CreateFileA(fullPortName.c_str(),
                                 GENERIC_READ | GENERIC_WRITE,
                                 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) return INVALID_HANDLE_VALUE;

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    if (!GetCommState(hSerial, &dcb)) { CloseHandle(hSerial); return INVALID_HANDLE_VALUE; }
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    if (!SetCommState(hSerial, &dcb)) { CloseHandle(hSerial); return INVALID_HANDLE_VALUE; }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);
    return hSerial;
#else
    int fd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) return -1;
    struct termios opts;
    tcgetattr(fd, &opts);
    cfsetispeed(&opts, B115200);
    cfsetospeed(&opts, B115200);
    opts.c_cflag |= (CLOCAL | CREAD);
    opts.c_cflag &= ~PARENB;
    opts.c_cflag &= ~CSTOPB;
    opts.c_cflag &= ~CSIZE;
    opts.c_cflag |=  CS8;
    opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    opts.c_iflag &= ~(IXON | IXOFF | IXANY);
    opts.c_oflag &= ~OPOST;
    tcsetattr(fd, TCSANOW, &opts);
    return fd;
#endif
}

void closeSerialPort(SerialHandle h) {
    if (h == INVALID_SERIAL_HANDLE) return;
#ifdef _WIN32
    CloseHandle(h);
#else
    close(h);
#endif
}

bool writeSerialByte(SerialHandle h, uint8_t byte) {
    if (h == INVALID_SERIAL_HANDLE) return false;
#ifdef _WIN32
    DWORD written = 0;
    return WriteFile(h, &byte, 1, &written, NULL) && written == 1;
#else
    return write(h, &byte, 1) == 1;
#endif
}

void clearSerialInputBuffer(SerialHandle h) {
    if (h == INVALID_SERIAL_HANDLE) return;
#ifdef _WIN32
    PurgeComm(h, PURGE_RXCLEAR | PURGE_RXABORT);
#else
    tcflush(h, TCIFLUSH);
#endif
}

// ── OSC ACK & BEAT callbacks ─────────────────────────────────────────────────
int ack_handler(const char* path, const char* types, lo_arg** argv,
                int argc, lo_message msg, void* user_data) {
    auto     now    = std::chrono::steady_clock::now();
    uint64_t now_us = std::chrono::duration_cast<std::chrono::microseconds>(
                          now.time_since_epoch()).count();
                          
    last_rx_time_us.store(now_us); // Flash RX led
    
    if (argc > 0 && argv[0]) {
        std::string ack_type = &argv[0]->s;
        if (ack_type == "reset") {
            last_rx_pulse_type.store(1); // Beat 1
            last_trace_time_us.store(now_us);
            broadcast_ws(R"({"type": "rx", "color": "#00ff00"})");
        } else if (ack_type == "sync") {
            last_rx_pulse_type.store(2); // Other beats
            last_trace_time_us.store(now_us);
            broadcast_ws(R"({"type": "rx", "color": "#00ffff"})");
        }
    }
    
    uint64_t ping   = last_ping_time_us.exchange(0);
    if (ping > 0) {
        double rtt_ms = (now_us - ping) / 1000.0;
        last_rtt_ms.store(rtt_ms);
    }
    return 0;
}

int beat_handler(const char* path, const char* types, lo_arg** argv,
                 int argc, lo_message msg, void* user_data) {
    auto     now    = std::chrono::steady_clock::now();
    uint64_t now_us = std::chrono::duration_cast<std::chrono::microseconds>(
                          now.time_since_epoch()).count();
                          
    if (argc > 0) {
        int step = argv[0]->i;
        int beat_idx = (step / 4) % 4;
        last_rx_pulse_type.store(beat_idx == 0 ? 1 : 2);
        last_trace_time_us.store(now_us);
        last_rx_time_us.store(now_us); // Flash RX led
        
        broadcast_ws("{\"type\": \"beat\", \"step\": " + std::to_string(step) + "}");
    }
    return 0;
}

// ── Link thread ──────────────────────────────────────────────────────────────
void link_loop_thread(const std::string& portName, lo_address synthAddr) {
#ifdef _WIN32
    timeBeginPeriod(1);
#endif

    SerialHandle hSerial = INVALID_SERIAL_HANDLE;
    if (!portName.empty()) {
        hSerial = openSerialPort(portName);
    }

    ableton::Link link(current_tempo.load());
    link.enable(true);
    link.enableStartStopSync(true); // Permitir que Traktor pause o inicie la app
    
    // Send initial tempo and lock status to synth at startup
    lo_send(synthAddr, "/master/bpm", "f", (float)current_tempo.load());
    lo_send(synthAddr, "/master/bpm_lock", "i", 1); // Locked by default
    
    link.setNumPeersCallback([](std::size_t n) {
        peers_count = static_cast<int>(n);
    });

    const double quantum = 4.0;
    int  last_tick_16th = -1;
    int  sync_id   = 1;

    while (keep_running) {
        auto   state          = link.captureAppSessionState();
        auto   now_link       = link.clock().micros();
        bool   state_changed  = false;

        // 1. Sync from GUI -> Link
        if (tempo_changed_by_gui.exchange(false)) {
            state.setTempo(current_tempo.load(), now_link);
            state_changed = true;
        }
        if (play_changed_by_gui.exchange(false)) {
            state.setIsPlaying(is_playing.load(), now_link);
            state_changed = true;
        }
        if (state_changed) {
            link.commitAppSessionState(state);
            state = link.captureAppSessionState();
        }

        // 2. Sync logic depending on Master/Follow mode
        double tempo = state.tempo();
        
        if (is_master.load()) {
            // LEAD MODE: If Link differs from our GUI, force Link back to our GUI state
            bool force_commit = false;
            if (std::abs(tempo - current_tempo.load()) > 0.01) {
                state.setTempo(current_tempo.load(), now_link);
                force_commit = true;
            }
            if (state.isPlaying() != is_playing.load()) {
                state.setIsPlaying(is_playing.load(), now_link);
                force_commit = true;
            }
            if (force_commit) {
                link.commitAppSessionState(state);
                state = link.captureAppSessionState();
            }
        } else {
            // FOLLOW MODE: Accept changes from Link (e.g. Traktor)
            if (std::abs(tempo - current_tempo.load()) > 0.01) {
                current_tempo.store(tempo);
                lo_send(synthAddr, "/master/bpm", "f", (float)tempo);
            }
            if (state.isPlaying() != is_playing.load()) {
                is_playing.store(state.isPlaying());
            }
        }
        double current_beat   = state.beatAtTime(now_link, quantum);

        double current_16th   = current_beat * 4.0;
        double next_16th      = std::floor(current_16th) + 1.0;
        double next_beat_time_calc = next_16th / 4.0;
        
        // Apply phase offset
        double offset_beats   = (phase_offset_ms.load() / 1000.0) * (tempo / 60.0);
        auto   next_beat_time = state.timeAtBeat(next_beat_time_calc + offset_beats, quantum);

        // Sleep/Spin
        while (keep_running) {
            auto    now_us  = link.clock().micros();
            int64_t remain  = std::chrono::duration_cast<std::chrono::microseconds>(
                                  next_beat_time - now_us).count();

            if (remain <= 0) {
                int64_t jitter_us = -remain;
                last_jitter_ms = jitter_us / 1000.0;

                auto   trig_state = link.captureAppSessionState();
                double trig_beat  = trig_state.beatAtTime(now_us, quantum);
                int    tick_16th  = static_cast<int>(std::floor(trig_beat * 4.0));

                if (tick_16th != last_tick_16th) {
                    last_tick_16th = tick_16th;
                    
                    bool is_beat_start = (tick_16th % 4 == 0);
                    int  step_index    = (tick_16th / 4) % 4;
                    bool is_beat_1     = (step_index == 0);
                    
                    if (is_beat_start) {
                        current_step = step_index;
                    }
                    
                    if (is_playing.load()) {
                        if (is_beat_start && hSerial != INVALID_SERIAL_HANDLE) {
                            uint8_t cmd = is_beat_1 ? 0xF9 : 0xF8;
                            clearSerialInputBuffer(hSerial);
                            writeSerialByte(hSerial, cmd);
                        }
    
                        if (is_beat_start) {
                            uint64_t ping_us = static_cast<uint64_t>(
                                std::chrono::duration_cast<std::chrono::microseconds>(
                                    std::chrono::steady_clock::now().time_since_epoch()).count());
                            last_ping_time_us.store(ping_us);
                            
                            last_tx_time_us.store(ping_us);
                            last_tx_pulse_type.store(is_beat_1 ? 1 : 2);
                            
                            std::string color = is_beat_1 ? "#00ff00" : "#ff3333";
                            broadcast_ws("{\"type\": \"tx\", \"pulse\": " + std::to_string(is_beat_1 ? 1 : 2) + ", \"color\": \"" + color + "\"}");
                            
                            // Clear WS trace after 150ms using a detached thread or defer
                            std::thread([]() {
                                std::this_thread::sleep_for(std::chrono::milliseconds(150));
                                broadcast_ws("{\"type\": \"tx\", \"pulse\": 0}");
                            }).detach();
                            
                            // Send OSC sync once per beat so MasterClock calculates BPM correctly
                            lo_send(synthAddr, "/clock/sync", "");
                            if (is_beat_1) {
                                // Realign synthesizer phase at the start of every measure to prevent phase drift
                                lo_send(synthAddr, "/master/sync_reset", "");
                            }
                        }
                    }
                }
                break;
            }

            int64_t spin_threshold = 2000;
#ifdef _WIN32
            spin_threshold = 20000;
#endif

            if (remain > spin_threshold) {
                int64_t sleep_us = remain - spin_threshold;
                std::this_thread::sleep_for(std::chrono::microseconds(sleep_us));
            } else {
                std::this_thread::yield();
            }
        }
    }

    closeSerialPort(hSerial);
#ifdef _WIN32
    timeEndPeriod(1);
#endif
}

// ── Main ────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
    std::string portName   = "";
    double      initialBpm = 120.0;

    if (argc > 1) portName = argv[1];
    if (argc > 2) {
        try { initialBpm = std::stod(argv[2]); }
        catch (...) { }
    }
    current_tempo.store(initialBpm);

    lo_address synthAddr = lo_address_new("127.0.0.1", "8000");
    if (!synthAddr) return 1;

    lo_server_thread ackServer = lo_server_thread_new("8001", nullptr);
    if (ackServer) {
        lo_server_thread_add_method(ackServer, "/synth/ack", "s", ack_handler, nullptr);
        lo_server_thread_add_method(ackServer, "/synth/beat", "i", beat_handler, nullptr);
        lo_server_thread_start(ackServer);
    }
    
    // Tell the synth where to send ACKs and BEATs
    lo_send(synthAddr, "/bridge/connect", "i", 8001);

    std::signal(SIGINT,  signal_handler);
    std::signal(SIGTERM, signal_handler);

    // Setup GLFW
    if (!glfwInit()) return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(380, 560, "BAZZ Sync Bridge", NULL, NULL);
    if (window == NULL) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Custom colors
    ImVec4 bg_color = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    ImGui::GetStyle().WindowRounding = 5.0f;
    ImGui::GetStyle().FrameRounding = 3.0f;

    bool bpm_locked = true;
    char bpm_input[16];
    double display_bpm = initialBpm;
    snprintf(bpm_input, 16, "%.2f", initialBpm);

    // Launch background thread for Link AFTER GLFW init
    std::thread link_thread(link_loop_thread, portName, synthAddr);
    
    // Launch WS Server
    std::thread ws_thread(ws_server_thread_func);

    // Render loop
    while (!glfwWindowShouldClose(window) && keep_running) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)width, (float)height));
        
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
        ImGui::Begin("Main Window", NULL, window_flags);

        // Title
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.55f, 0.0f, 1.0f)); // ACCENT_ORANGE
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("BAZZ SYNC BRIDGE");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::PopStyleColor();

        ImGui::Spacing();
        
        // Serial status
        if (!portName.empty()) {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "ESP32 CONECTADO: %s", portName.c_str());
        } else {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "ESP32: No port specified");
        }

        ImGui::Separator();
        
        // Status row
        ImGui::Text("Peers: %d | RTT: %.1fms | Jitter: %.2fms", peers_count.load(), last_rtt_ms.load(), last_jitter_ms.load());
        ImGui::Spacing();

        // Wave trace emulation based on RX from Synth (like the Python GUI)
        ImGui::Text("SEÑAL DE SALIDA (RX SYNTH)");
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetCursorScreenPos();
        draw_list->AddRectFilled(p, ImVec2(p.x + 300, p.y + 60), IM_COL32(10, 10, 10, 255));
        draw_list->AddRect(p, ImVec2(p.x + 300, p.y + 60), IM_COL32(68, 68, 68, 255));
        
        uint64_t now_us = static_cast<uint64_t>(
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count());
                
        uint64_t trace_age = now_us - last_trace_time_us.load();
        int rx_pulse_type = last_rx_pulse_type.load();
        
        if (trace_age < 150000) { // Trace visible for 150ms
            if (rx_pulse_type == 1) { // BEAT 1 (Green)
                std::vector<ImVec2> pts = {
                    ImVec2(p.x + 0, p.y + 50), ImVec2(p.x + 20, p.y + 50),
                    ImVec2(p.x + 20, p.y + 10), ImVec2(p.x + 150, p.y + 10),
                    ImVec2(p.x + 150, p.y + 50), ImVec2(p.x + 300, p.y + 50)
                };
                draw_list->AddPolyline(pts.data(), pts.size(), IM_COL32(0, 255, 0, 255), 0, 3.0f);
                draw_list->AddText(ImVec2(p.x + 85, p.y + 25), IM_COL32(0, 255, 0, 255), "BEAT 1");
            } else { // BEAT 2,3,4 (Cyan)
                std::vector<ImVec2> pts = {
                    ImVec2(p.x + 0, p.y + 50), ImVec2(p.x + 20, p.y + 50),
                    ImVec2(p.x + 20, p.y + 10), ImVec2(p.x + 40, p.y + 10),
                    ImVec2(p.x + 40, p.y + 50), ImVec2(p.x + 300, p.y + 50)
                };
                draw_list->AddPolyline(pts.data(), pts.size(), IM_COL32(0, 255, 255, 255), 0, 2.0f);
            }
        } else {
            // Flat line
            draw_list->AddLine(ImVec2(p.x + 0, p.y + 50), ImVec2(p.x + 300, p.y + 50), IM_COL32(51, 51, 51, 255), 2.0f);
        }
        ImGui::Dummy(ImVec2(300, 65));
        
        ImGui::Spacing();
        
        // LEDs
        ImGui::Columns(2, 0, false);
        ImVec2 led_p = ImGui::GetCursorScreenPos();
        draw_list->AddText(ImVec2(led_p.x + 20, led_p.y), IM_COL32(224, 224, 224, 255), "SYNC TX");
        uint64_t tx_age = now_us - last_tx_time_us.load();
        ImColor tx_color = (tx_age < 50000) ? ((last_tx_pulse_type.load() == 1) ? ImColor(0, 255, 0) : ImColor(0, 255, 255)) : ImColor(34, 0, 0);
        draw_list->AddCircleFilled(ImVec2(led_p.x + 45, led_p.y + 30), 15.0f, tx_color);
        ImGui::NextColumn();

        led_p = ImGui::GetCursorScreenPos();
        draw_list->AddText(ImVec2(led_p.x + 20, led_p.y), IM_COL32(224, 224, 224, 255), "SYNTH RX");
        uint64_t rx_age = now_us - last_rx_time_us.load();
        ImColor rx_color = (rx_age < 50000) ? ((last_rx_pulse_type.load() == 1) ? ImColor(0, 255, 0) : ImColor(0, 255, 255)) : ImColor(0, 34, 0);
        draw_list->AddCircleFilled(ImVec2(led_p.x + 45, led_p.y + 30), 15.0f, rx_color);
        ImGui::Columns(1);
        ImGui::Dummy(ImVec2(0, 50));
        
        ImGui::Separator();
        
        // Step Sequencer
        ImGui::Text("Secuenciador (Beats):");
        int s = current_step.load();
        for(int i = 0; i < 4; i++) {
            ImGui::SameLine();
            if (i == s && is_playing.load()) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.8f, 0.0f, 1.0f));
                ImGui::Button(" [O] ", ImVec2(40, 30));
                ImGui::PopStyleColor();
            } else {
                ImGui::Button(" [ ] ", ImVec2(40, 30));
            }
        }
        
        ImGui::Separator();
        
        // Phase Nudge
        ImGui::Text("Phase Nudge: %.1f ms", phase_offset_ms.load());
        if (ImGui::Button("< -1ms", ImVec2(80, 30))) {
            phase_offset_ms.store(phase_offset_ms.load() - 1.0);
            lo_send(synthAddr, "/master/sync_offset", "f", (float)phase_offset_ms.load());
        }
        ImGui::SameLine();
        if (ImGui::Button("+1ms >", ImVec2(80, 30))) {
            phase_offset_ms.store(phase_offset_ms.load() + 1.0);
            lo_send(synthAddr, "/master/sync_offset", "f", (float)phase_offset_ms.load());
        }
        
        ImGui::Separator();
        
        // BPM Controls
        // Auto-update textbox if tempo changed via Traktor
        if (std::abs(current_tempo.load() - display_bpm) > 0.01) {
            display_bpm = current_tempo.load();
            snprintf(bpm_input, 16, "%.2f", display_bpm);
        }
        
        ImGui::PushItemWidth(80);
        ImGui::InputText("##bpm", bpm_input, 16);
        ImGui::PopItemWidth();
        ImGui::SameLine();
        if (ImGui::Button("SET", ImVec2(50, 25))) {
            try {
                double new_bpm = std::stod(bpm_input);
                current_tempo.store(new_bpm);
                display_bpm = new_bpm;
                tempo_changed_by_gui.store(true);
                lo_send(synthAddr, "/master/bpm", "f", (float)new_bpm);
            } catch (...) {}
        }
        ImGui::SameLine();
        if (ImGui::Button(bpm_locked ? "UNLOCK" : "LOCK", ImVec2(60, 25))) {
            bpm_locked = !bpm_locked;
            lo_send(synthAddr, "/master/bpm_lock", "i", bpm_locked ? 1 : 0);
        }
        ImGui::SameLine();
        bool master = is_master.load();
        ImGui::PushStyleColor(ImGuiCol_Button, master ? ImVec4(0.8f, 0.4f, 0.0f, 1.0f) : ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
        if (ImGui::Button(master ? "LEAD" : "FOLLOW", ImVec2(60, 25))) {
            is_master.store(!master);
            if (!master) { // Switched to LEAD
                tempo_changed_by_gui.store(true);
                play_changed_by_gui.store(true);
            }
        }
        ImGui::PopStyleColor();
        
        ImGui::SameLine();
        bool playing = is_playing.load();
        if (playing) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.6f, 0.0f, 1.0f));
            if (ImGui::Button("PAUSE", ImVec2(60, 25))) {
                is_playing.store(false);
                play_changed_by_gui.store(true);
            }
            ImGui::PopStyleColor();
        } else {
            if (ImGui::Button("PLAY", ImVec2(60, 25))) {
                is_playing.store(true);
                play_changed_by_gui.store(true);
            }
        }
        
        ImGui::End();

        // Rendering
        ImGui::Render();
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    keep_running = false;
    link_thread.join();
    
    // Stop uWS loop if running
    if (ws_loop) {
        ws_loop->defer([]() {
            if (ws_app) ws_app->close();
        });
    }
    ws_thread.join();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    if (ackServer) {
        lo_server_thread_stop(ackServer);
        lo_server_thread_free(ackServer);
    }
    lo_address_free(synthAddr);
    
    return 0;
}
