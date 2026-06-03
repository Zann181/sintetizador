#pragma once

#include <string>
#include <memory>
#include <thread>

#include <lo/lo.h>

namespace core { class Synthesizer; }
namespace state { 
    class PresetManager; 
    class AutomationRecorder; 
}
namespace audio { class RtAudioBackend; }

namespace osc {

class HttpServer;

class OscServer {
public:
    OscServer(core::Synthesizer* synth, state::PresetManager* presetMgr, state::AutomationRecorder* recorder, audio::RtAudioBackend* audioBackend = nullptr);
    ~OscServer();

    bool start(const std::string& port);
    void stop();

private:
    static int genericHandler(const char *path, const char *types, lo_arg **argv,
                              int argc, lo_message msg, void *user_data);

    lo_server_thread m_thread;
    core::Synthesizer* m_synth;
    state::PresetManager* m_presetMgr;
    state::AutomationRecorder* m_recorder;
    audio::RtAudioBackend* m_audioBackend;
    std::unique_ptr<HttpServer> m_htmlServer;
    std::thread m_wsThread;
};

} // namespace osc
