#include <Engine/Engine.hpp>

// System Types here
#include <System/Physics/PhysicsSystem.hpp>
#include <System/Audio/AudioSystem.hpp>
#include <System/Render/RenderSystem.hpp>
#include <System/Resource/ResourceSystem.hpp>

#ifdef RLF_EDITOR
#include <System/Editor/EditorSystem.hpp>
#endif

// All Node Types here
#include <Node/BaseNode.hpp>

#include <Node/Audio/MusicNode.hpp>
#include <Node/Audio/SoundNode.hpp>

#include <Node/Physics/ColliderNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>
#include <Node/Physics/RigidbodyNode.hpp>

#include <Node/Render/RenderNode.hpp>
#include <Node/Render/CameraNode.hpp>
#include <Node/Render/LineRenderNode.hpp>
#include <Node/Render/CircleRenderNode.hpp>
#include <Node/Render/QuadRenderNode.hpp>
#include <Node/Render/SpriteRenderNode.hpp>
#include <Node/Render/ParticleRenderNode.hpp>
#include <Node/Render/BurstParticleRenderNode.hpp>

#include <Node/UI/UINode.hpp>
#include <Node/UI/UICameraNode.hpp>
#include <Node/UI/UIButtonNode.hpp>
#include <Node/UI/UISpriteNode.hpp>
#include <Node/UI/UITextNode.hpp>
#include <Node/UI/UISliderNode.hpp>

namespace rlf
{
    void Engine::setInstance(Engine* const instance)
    {
        assert(instance != nullptr);
        mInstance = instance;
    }

    Engine& Engine::getInstance()
    {
        return *mInstance;
    }

    void Engine::run(rlf::EngineConfig const& config)
    {
        unsigned int const windowFlag = FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE;
        SetConfigFlags(windowFlag);
        InitWindow(static_cast<int>(config.width), static_cast<int>(config.height), config.title.data());
        SetTargetFPS(GetMonitorRefreshRate(0));
        SetExitKey(KEY_NULL);

#ifdef RLF_EDITOR
        // MaximizeWindow();
#else
        ToggleBorderlessWindowed();
#endif

        // Register Types here
        mNodeManager.registerNodeType<rlf::BaseNode>();

        mNodeManager.registerNodeType<rlf::MusicNode>();
        mNodeManager.registerNodeType<rlf::SoundNode>();

        mNodeManager.registerNodeType<rlf::ColliderNode>();
        mNodeManager.registerNodeType<rlf::BoxColliderNode>();
        mNodeManager.registerNodeType<rlf::CircleColliderNode>();
        mNodeManager.registerNodeType<rlf::RigidbodyNode>();

        // Render Nodes
        mNodeManager.registerNodeType<rlf::RenderNode>();
        mNodeManager.registerNodeType<rlf::CameraNode>();
        mNodeManager.registerNodeType<rlf::LineRenderNode>();
        mNodeManager.registerNodeType<rlf::CircleRenderNode>();
        mNodeManager.registerNodeType<rlf::QuadRenderNode>();
        mNodeManager.registerNodeType<rlf::SpriteRenderNode>();
        mNodeManager.registerNodeType<rlf::ParticleRenderNode>();
        mNodeManager.registerNodeType<rlf::BurstParticleRenderNode>();

        // UI Nodes
        mNodeManager.registerNodeType<rlf::UINode>();
        mNodeManager.registerNodeType<rlf::UICameraNode>();
        mNodeManager.registerNodeType<rlf::UIButtonNode>();
        mNodeManager.registerNodeType<rlf::UISpriteNode>();
        mNodeManager.registerNodeType<rlf::UITextNode>();
        mNodeManager.registerNodeType<rlf::UISliderNode>();

        // Register Systems
        mSystemManager.registerSystem<rlf::PhysicsSystem>();
        mSystemManager.registerSystem<rlf::AudioSystem>();
        mSystemManager.registerSystem<rlf::RenderSystem>();
        mSystemManager.registerSystem<rlf::ResourceSystem>();

#ifdef RLF_EDITOR
        mSystemManager.registerSystem<rlf::EditorSystem>();
#endif

        // Run custom setup func, for registering of app node types
        if (config.setup_func)
        {
            config.setup_func(mNodeManager, mSystemManager);
        }

        // Initialize all systems
        for (auto& system : mSystemManager.getSystems())
        {
            system->init();
        }

        // Create root node
        mRootNode = mNodeManager.create<rlf::BaseNode>().value();
        mRootNode->setName(mRootNode->getTypeNameImpl().data());

        // Attempt to load initial world if there's one set
        if (!mInitialWorldToLoad.empty())
        {
            mRootNode->deserializeFromFile(mInitialWorldToLoad);
        }
        mRootNode->setup();
        mRootNode->init();

        while (!(WindowShouldClose() || mToQuit))
        {
#ifndef RLF_EDITOR
            // Alt + Enter to toggle Borderless Fullscreen
            if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
            {
                ToggleBorderlessWindowed();
            }
#endif

            // Checks if there's a next world to load before doing any updates
            if (!mNextWorldToLoad.empty())
            {
                mRootNode->deserializeFromFile(mNextWorldToLoad);
                mNextWorldToLoad.clear();
            }

            mRootNode->preUpdate();
            mRootNode->update();
            mRootNode->postUpdate();

            for (auto& system : mSystemManager.getSystems())
            {
                system->update();
            }

            BeginDrawing();
            ClearBackground(BLACK);

            for (auto& system : mSystemManager.getSystems())
            {
                system->render();
            }

            // #if defined(RLF_DEBUG) && !defined(RLF_EDITOR)
            // Draw FPS counter
            DrawFPS(10, 10);
            // #endif

            EndDrawing();
        }

        if (config.shutdown_func)
        {
            config.shutdown_func();
        }

        // Set all children to destroy then run through
        for (auto& child : mRootNode->getChildren())
        {
            child->setToDestroy(true);
        }
        mRootNode->preUpdate();
        mRootNode->update();
        mRootNode->postUpdate();
        mRootNode->uninit();
        mRootNode->shutdown();
        mRootNode.reset();

        auto systems = mSystemManager.getSystems();
        std::ranges::reverse(systems);
        for (auto const& system : systems)
        {
            system->shutdown();
        }

        CloseWindow();
    }

    void Engine::setToQuit()
    {
        mToQuit = true;
    }

    void Engine::setAssetsDirectory(std::filesystem::path const& assetsPath)
    {
        std::filesystem::current_path(assetsPath);
    }

    std::string Engine::getAssetsDirectory() const
    {
        return std::filesystem::current_path().string();
    }

    void Engine::setInitialWorldToLoad(std::string const& filename)
    {
        mInitialWorldToLoad = filename;
    }
    void Engine::setNextWorldToLoad(std::string const& filename)
    {
        mNextWorldToLoad = filename;
    }

    rlf::EventManager& Engine::getEventManager()
    {
        return mEventManager;
    }

    rlf::NodeManager& Engine::getNodeManager()
    {
        return mNodeManager;
    }

    std::shared_ptr<BaseNode> Engine::getRootNode() const
    {
        return mRootNode;
    }
}
