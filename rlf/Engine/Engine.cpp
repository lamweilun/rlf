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
#include <Node/NodeManager.hpp>

#include <Node/BaseNode.hpp>

#include <Node/Audio/MusicNode.hpp>
#include <Node/Audio/SoundNode.cpp>

#include <Node/Physics/ColliderNode.cpp>
#include <Node/Physics/BoxColliderNode.cpp>
#include <Node/Physics/CircleColliderNode.cpp>
#include <Node/Physics/RigidbodyNode.cpp>

#include <Node/Render/RenderNode.cpp>
#include <Node/Render/CameraNode.hpp>
#include <Node/Render/LineRenderNode.cpp>
#include <Node/Render/CircleRenderNode.cpp>
#include <Node/Render/QuadRenderNode.cpp>
#include <Node/Render/SpriteRenderNode.cpp>
#include <Node/Render/ParticleRenderNode.cpp>
#include <Node/Render/BurstParticleRenderNode.cpp>

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
        MaximizeWindow();
#else
        ToggleBorderlessWindowed();
#endif

        // Register Types here
        mNodeManager.registerNodeType<rlf::Node::BaseNode>();

        mNodeManager.registerNodeType<rlf::Node::MusicNode>();
        mNodeManager.registerNodeType<rlf::Node::SoundNode>();

        mNodeManager.registerNodeType<rlf::Node::ColliderNode>();
        mNodeManager.registerNodeType<rlf::Node::BoxColliderNode>();
        mNodeManager.registerNodeType<rlf::Node::CircleColliderNode>();
        mNodeManager.registerNodeType<rlf::Node::RigidbodyNode>();

        // Render Nodes
        mNodeManager.registerNodeType<rlf::Node::RenderNode>();
        mNodeManager.registerNodeType<rlf::Node::CameraNode>();
        mNodeManager.registerNodeType<rlf::Node::LineRenderNode>();
        mNodeManager.registerNodeType<rlf::Node::CircleRenderNode>();
        mNodeManager.registerNodeType<rlf::Node::QuadRenderNode>();
        mNodeManager.registerNodeType<rlf::Node::SpriteRenderNode>();
        mNodeManager.registerNodeType<rlf::Node::ParticleRenderNode>();
        mNodeManager.registerNodeType<rlf::Node::BurstParticleRenderNode>();

        // UI Nodes
        mNodeManager.registerNodeType<rlf::Node::UINode>();
        mNodeManager.registerNodeType<rlf::Node::UICameraNode>();
        mNodeManager.registerNodeType<rlf::Node::UIButtonNode>();
        mNodeManager.registerNodeType<rlf::Node::UISpriteNode>();
        mNodeManager.registerNodeType<rlf::Node::UITextNode>();
        mNodeManager.registerNodeType<rlf::Node::UISliderNode>();

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
        mRootNode = mNodeManager.create<rlf::Node::BaseNode>().value();
        mRootNode->setName(mRootNode->getTypeNameImpl().data());

        // Attempt to load initial world if there's one set
        if (!mInitialWorldToLoad.empty())
        {
            mRootNode->deserializeFromFile(mInitialWorldToLoad);
        }

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

        mRootNode->shutdown();
        mNodeManager.destroy(mRootNode);

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

    rlf::NodeManager& Engine::getNodeManager()
    {
        return mNodeManager;
    }

    rlf::Node::BaseNode* Engine::getRootNode() const
    {
        return mRootNode;
    }
}
