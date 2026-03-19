#pragma once

#include <Node/NodeManager.hpp>

#include <System/ISystem.hpp>

#include <functional>
#include <memory>

namespace rlf
{
    namespace Node
    {
        class BaseNode;
    }

    class Engine
    {
    public:
        struct Config
        {
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

        void run(Config const &config);
        void setToQuit();

        void        setAssetsDirectory(std::filesystem::path const &assetsPath);
        std::string getAssetsDirectory() const;
        void        setInitialWorldToLoad(std::string const &filename);
        void        setNextWorldToLoad(std::string const &filename);

        void setSetupFunc(std::function<void(rlf::NodeManager&)> setupFunc);
        void setInitFunc(std::function<void(rlf::Node::BaseNode*)> initFunc);
        void setUpdateFunc(std::function<void(rlf::Node::BaseNode*)> updateFunc);
        void setShutdownFunc(std::function<void(rlf::Node::BaseNode*)> shutdownFunc);

        rlf::Node::BaseNode* getRootNode() const;

        template <class T>
        void addSystem();

        template <class T>
        std::shared_ptr<T> getSystem() const;

    private:
        std::string                                               mInitialWorldToLoad;
        std::string                                               mNextWorldToLoad;
        std::function<void(rlf::NodeManager&)>                    mSetupFunc;
        std::function<void(rlf::Node::BaseNode*)> mInitFunc;
        std::function<void(rlf::Node::BaseNode*)> mUpdateFunc;
        std::function<void(rlf::Node::BaseNode*)> mShutdownFunc;
        Node::BaseNode                                           *mRootNode;

        std::vector<std::shared_ptr<System::ISystem>> mSystems;
        std::unordered_map<std::string, u64>          mSystemLUT;

        bool mToQuit = false;
    };
}

#include <Engine/EngineImpl.hpp>
