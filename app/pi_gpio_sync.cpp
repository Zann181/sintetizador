#include <gpiod.h>
#include <lo/lo.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <string>
#include <vector>

// Signal handler to allow clean exit on Ctrl+C or systemctl stop
volatile sig_atomic_t keep_running = 1;

void handle_signal(int sig) {
    keep_running = 0;
}

int main(int argc, char* argv[]) {
    int pin = 17;
    int chip_num = -1; // -1 means auto-detect

    // Parse arguments: ./pi_gpio_sync [pin] [chip_number]
    if (argc > 1) {
        try {
            pin = std::stoi(argv[1]);
        } catch (...) {
            std::cerr << "[GPIO SYNC] Invalid pin argument. Using 17." << std::endl;
        }
    }
    if (argc > 2) {
        try {
            chip_num = std::stoi(argv[2]);
        } catch (...) {
            std::cerr << "[GPIO SYNC] Invalid chip argument." << std::endl;
        }
    }

    struct gpiod_chip *chip = nullptr;

    if (chip_num >= 0) {
        std::string chip_path = "/dev/gpiochip" + std::to_string(chip_num);
        chip = gpiod_chip_open(chip_path.c_str());
        if (!chip) {
            std::cerr << "[GPIO SYNC] Error: Could not open specified chip " << chip_path << std::endl;
            return 1;
        }
    } else {
        // Auto-detect GPIO chip: RPi 5 uses gpiochip4 (RP1), RPi 3/4 uses gpiochip0.
        // We test multiple candidates to ensure portability across different Pi boards and OS versions.
        std::vector<int> candidates = {4, 0, 1, 2, 3, 5};
        for (int c : candidates) {
            std::string chip_path = "/dev/gpiochip" + std::to_string(c);
            chip = gpiod_chip_open(chip_path.c_str());
            if (chip) {
                struct gpiod_chip_info *info = gpiod_chip_get_info(chip);
                if (info) {
                    unsigned int num_lines = gpiod_chip_info_get_num_lines(info);
                    gpiod_chip_info_free(info);
                    if (static_cast<unsigned int>(pin) < num_lines) {
                        std::cout << "[GPIO SYNC] Auto-detected GPIO chip: " << chip_path 
                                  << " (Lines: " << num_lines << ")" << std::endl;
                        break;
                    }
                }
                gpiod_chip_close(chip);
                chip = nullptr;
            }
        }
    }

    if (!chip) {
        std::cerr << "[GPIO SYNC] Error: Could not open a valid gpiochip containing pin " << pin << std::endl;
        std::cerr << "Make sure you run this on a Raspberry Pi and have installed libgpiod (apt install gpiod libgpiod-dev)." << std::endl;
        return 1;
    }

    // 1. Create a line configuration object
    struct gpiod_line_config *line_cfg = gpiod_line_config_new();
    if (!line_cfg) {
        std::cerr << "[GPIO SYNC] Error: Failed to allocate line config." << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    // 2. Create and configure a line settings object for input + rising edge
    struct gpiod_line_settings *settings = gpiod_line_settings_new();
    if (!settings) {
        std::cerr << "[GPIO SYNC] Error: Failed to allocate line settings." << std::endl;
        gpiod_line_config_free(line_cfg);
        gpiod_chip_close(chip);
        return 1;
    }
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_INPUT);
    gpiod_line_settings_set_edge_detection(settings, GPIOD_LINE_EDGE_RISING);

    // 3. Add the settings to the line configuration for specific offset
    unsigned int offset = static_cast<unsigned int>(pin);
    if (gpiod_line_config_add_line_settings(line_cfg, &offset, 1, settings) < 0) {
        std::cerr << "[GPIO SYNC] Error: Failed to add line settings." << std::endl;
        gpiod_line_settings_free(settings);
        gpiod_line_config_free(line_cfg);
        gpiod_chip_close(chip);
        return 1;
    }

    // 4. Configure the request config
    struct gpiod_request_config *req_cfg = gpiod_request_config_new();
    if (!req_cfg) {
        std::cerr << "[GPIO SYNC] Error: Failed to allocate request config." << std::endl;
        gpiod_line_settings_free(settings);
        gpiod_line_config_free(line_cfg);
        gpiod_chip_close(chip);
        return 1;
    }
    gpiod_request_config_set_consumer(req_cfg, "pi_gpio_sync");

    // 5. Request the line (offsets are specified directly via line_cfg)
    struct gpiod_line_request *request = gpiod_chip_request_lines(chip, req_cfg, line_cfg);

    // Config structs can be freed immediately after request is made
    gpiod_line_settings_free(settings);
    gpiod_line_config_free(line_cfg);
    gpiod_request_config_free(req_cfg);

    if (!request) {
        std::cerr << "[GPIO SYNC] Error: Failed to request GPIO line " << pin << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    // 6. Prepare event buffer
    struct gpiod_edge_event_buffer *event_buffer = gpiod_edge_event_buffer_new(16);
    if (!event_buffer) {
        std::cerr << "[GPIO SYNC] Error: Failed to allocate edge event buffer." << std::endl;
        gpiod_line_request_release(request);
        gpiod_chip_close(chip);
        return 1;
    }

    // Initialize OSC client to send to local FaustSynthServer port 8000
    lo_address target = lo_address_new("127.0.0.1", "8000");
    if (!target) {
        std::cerr << "[GPIO SYNC] Error: Could not create OSC target address" << std::endl;
        gpiod_edge_event_buffer_free(event_buffer);
        gpiod_line_request_release(request);
        gpiod_chip_close(chip);
        return 1;
    }

    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    std::cout << "[GPIO SYNC] Native C++ daemon started (libgpiod v2 API)." << std::endl;
    std::cout << "Listening on GPIO Pin: " << pin << " -> sending OSC /clock/sync to 127.0.0.1:8000" << std::endl;

    double last_pulse_ms = 0.0;
    const double debounce_ms = 40.0; // Debounce window to prevent double trigger on noisy signals

    while (keep_running) {
        // Wait for an event (blocks for up to 1 second)
        int res = gpiod_line_request_wait_edge_events(request, 1000000000LL);
        if (res < 0) {
            std::cerr << "[GPIO SYNC] Error waiting for event" << std::endl;
            break;
        } else if (res > 0) {
            int num_events = gpiod_line_request_read_edge_events(request, event_buffer, 16);
            if (num_events < 0) {
                std::cerr << "[GPIO SYNC] Error reading events" << std::endl;
                continue;
            }
            
            for (int i = 0; i < num_events; i++) {
                struct gpiod_edge_event *event = gpiod_edge_event_buffer_get_event(event_buffer, i);
                if (event && gpiod_edge_event_get_event_type(event) == GPIOD_EDGE_EVENT_RISING_EDGE) {
                    auto now = std::chrono::steady_clock::now();
                    double now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
                    
                    // Software debounce logic
                    if (now_ms - last_pulse_ms >= debounce_ms) {
                        lo_send(target, "/clock/sync", "");
                        std::cout << "[GPIO SYNC] Pulse received on GPIO " << pin 
                                  << " -> Sent OSC /clock/sync @ " << now_ms << " ms" << std::endl;
                        last_pulse_ms = now_ms;
                    }
                }
            }
        }
    }

    std::cout << "[GPIO SYNC] Stopping daemon and releasing resources..." << std::endl;
    lo_address_free(target);
    gpiod_edge_event_buffer_free(event_buffer);
    gpiod_line_request_release(request);
    gpiod_chip_close(chip);
    return 0;
}
