#pragma once

#include <Node/NodeManager.hpp>
#include <System/SystemManager.hpp>

#include <functional>

namespace rlf
{
    struct EngineConfig
    {
        u32              width  = 1280;
        u32              height = 720;
        std::string_view title  = "Hello rlf";

        std::function<void(rlf::NodeManager&, rlf::SystemManager&)> setup_func;
        std::function<void()>                                       shutdown_func;
    };
}
