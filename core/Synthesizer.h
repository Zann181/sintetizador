#pragma once

#include "Parameter.h"
#include "MasterClock.h"
#include <map>
#include <memory>
#include <string>

namespace core {

class Synthesizer {
public:
    Synthesizer() {
        m_clock = std::make_unique<MasterClock>();
    }

    void addParameter(std::shared_ptr<Parameter> param) {
        m_parameters[param->getPath()] = param;
    }

    std::shared_ptr<Parameter> getParameter(const std::string& path) {
        std::string resolvedPath = path;
        if (path == "/kick/dec") resolvedPath = "/kick/decay";
        else if (path == "/kick/sweep") resolvedPath = "/kick/click";
        else if (path == "/kick/comp_drive") resolvedPath = "/kick/drive";
        else if (path == "/kick/mix") resolvedPath = "/kick/res/mix";
        else if (path == "/kick/tune") resolvedPath = "/kick/pitch";
        else if (path == "/kick/comp_thresh") resolvedPath = "/kick/lim/ceiling";

        auto it = m_parameters.find(resolvedPath);
        if (it != m_parameters.end()) {
            return it->second;
        }
        return nullptr;
    }

    MasterClock* getClock() const {
        return m_clock.get();
    }

    const std::map<std::string, std::shared_ptr<Parameter>>& getAllParameters() const {
        return m_parameters;
    }

private:
    std::unique_ptr<MasterClock> m_clock;
    std::map<std::string, std::shared_ptr<Parameter>> m_parameters;
};

} // namespace core
