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
        struct Config {
            u32              width  = 1280;
            u32              height = 720;
            std::string_view title  = "Hello rlf";
        };

        static Engine &getInstance();

        Engine()                          = default;
        ~Engine()                         = default;
        Engine(Engine const &)            = delete;
        Engine(Engine &&)                 = delete;
        Engine &operator=(Engine const &) = delete;
        Engine &operator=(Engine &&)      = delete;

        void run(Config const &config = Config(1280, 720, "Hello rlf"));
        void setToQuit();

        void        setAssetsDirectory(std::filesystem::path const &assetsPath);
        std::string getAssetsDirectory() const;
        void        setInitialWorldToLoad(std::string const &filename);
        void        setNextWorldToLoad(std::string const &filename);

        void setSetupFunc(std::function<void()> setupFunc);
        void setInitFunc(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> initFunc);
        void setUpdateFunc(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> updateFunc);
        void setShutdownFunc(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> shutdownFunc);

        std::shared_ptr<Node::BaseNode> getRootNode() const;

        template <class T>
        void addSystem();

        template <class T>
        std::shared_ptr<T> getSystem() const;

    private:
        std::string                                               mInitialWorldToLoad;
        std::string                                               mNextWorldToLoad;
        std::function<void()>                                     mSetupFunc;
        std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> mInitFunc;
        std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> mUpdateFunc;
        std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> mShutdownFunc;
        std::shared_ptr<Node::BaseNode>                           mRootNode;

        std::vector<std::shared_ptr<System::ISystem>> mSystems;
        std::unordered_map<std::string, u64>          mSystemLUT;

        bool mToQuit = false;
    };
}

#include <Engine/EngineImpl.hpp>
