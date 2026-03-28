#pragma once

#include <Engine/EngineConfig.hpp>
#include <Node/NodeManager.hpp>
#include <System/SystemManager.hpp>

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
        static void    setInstance(Engine *const instance);
        static Engine &getInstance();

        Engine()                          = default;
        ~Engine()                         = default;
        Engine(Engine const &)            = delete;
        Engine(Engine &&)                 = delete;
        Engine &operator=(Engine const &) = delete;
        Engine &operator=(Engine &&)      = delete;

        void run(rlf::EngineConfig const &config);
        void setToQuit();

        void        setAssetsDirectory(std::filesystem::path const &assetsPath);
        std::string getAssetsDirectory() const;
        void        setInitialWorldToLoad(std::string const &filename);
        void        setNextWorldToLoad(std::string const &filename);

        rlf::NodeManager    &getNodeManager();
        rlf::Node::BaseNode *getRootNode() const;

        template <class T>
        std::shared_ptr<T> getSystem() const
        {
            return mSystemManager.getSystem<T>();
        }

    private:
        static inline Engine *mInstance = nullptr;

        rlf::NodeManager   mNodeManager;
        rlf::SystemManager mSystemManager;

        std::string     mInitialWorldToLoad;
        std::string     mNextWorldToLoad;
        Node::BaseNode *mRootNode;
        bool            mToQuit = false;
    };
}
