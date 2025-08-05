#pragma once

#include <Node/BaseNode.hpp>

#include <functional>
#include <memory>

namespace rlf {
    class Engine {
    public:
        Engine(u32 const width = 1280, u32 const height = 720, char const *title = "");
        ~Engine();
        Engine(Engine const &)            = delete;
        Engine(Engine &&)                 = delete;
        Engine &operator=(Engine const &) = delete;
        Engine &operator=(Engine &&)      = delete;

        void run(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> setupFunc = nullptr);

    private:
    };
}
