#pragma once

#include <System/ISystem.hpp>

#include <functional>
#include <memory>

namespace rlf {
    namespace Node {
        class BaseNode;
    }

    class Engine {
    public:
        static Engine &getInstance();

        Engine(u32 const width = 1280, u32 const height = 720, char const *title = "");
        ~Engine();
        Engine(Engine const &)            = delete;
        Engine(Engine &&)                 = delete;
        Engine &operator=(Engine const &) = delete;
        Engine &operator=(Engine &&)      = delete;

        void run(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> setupFunc = nullptr);

        std::shared_ptr<Node::BaseNode> getRootNode() const;

        template <class T>
        void addSystem();

        template <class T>
        std::shared_ptr<T> getSystem() const;

    private:
        std::shared_ptr<Node::BaseNode> mRootNode;

        std::vector<std::shared_ptr<System::ISystem>> mSystems;
        std::unordered_map<std::string, u64>          mSystemLUT;
    };
}

#include <Engine/EngineImpl.hpp>
