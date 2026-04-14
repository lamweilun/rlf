#pragma once

#include <Engine/EngineConfig.hpp>

#include <Event/EventManager.hpp>
#include <NodeManager/NodeManager.hpp>
#include <System/SystemManager.hpp>

#include <memory>

namespace rlf
{
    class BaseNode;

    class Engine
    {
    public:
        static void    setInstance(Engine* const instance);
        static Engine& getInstance();

        Engine()                         = default;
        ~Engine()                        = default;
        Engine(Engine const&)            = delete;
        Engine(Engine&&)                 = delete;
        Engine& operator=(Engine const&) = delete;
        Engine& operator=(Engine&&)      = delete;

        void run(rlf::EngineConfig const& config);
        void setToQuit();

        void        setAssetsDirectory(std::filesystem::path const& assetsPath);
        std::string getAssetsDirectory() const;
        void        setInitialWorldToLoad(std::string const& filename);
        void        setNextWorldToLoad(std::string const& filename);

        rlf::EventManager& getEventManager();

        rlf::NodeManager&         getNodeManager();
        std::shared_ptr<BaseNode> getRootNode() const;

        template <class T>
        std::shared_ptr<T> getSystem() const
        {
            return mSystemManager.getSystem<T>();
        }

    private:
        static inline Engine* mInstance = nullptr;

        rlf::EventManager  mEventManager;
        rlf::NodeManager   mNodeManager;
        rlf::SystemManager mSystemManager;

        std::string               mInitialWorldToLoad;
        std::string               mNextWorldToLoad;
        std::shared_ptr<BaseNode> mRootNode;
        bool                      mToQuit = false;
    };
}
