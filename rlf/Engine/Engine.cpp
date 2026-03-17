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
    Engine& Engine::getInstance()
    {
        static Engine engine;
        return engine;
    }

    void Engine::run(Config const& config)
    {
#ifdef RLF_EDITOR
        unsigned int windowFlag = FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE;
#else
        unsigned int windowFlag = FLAG_MSAA_4X_HINT;
#endif
        SetConfigFlags(windowFlag);
        InitWindow(static_cast<int>(config.width), static_cast<int>(config.height), config.title.data());
        SetWindowMonitor(0);
        // SetTargetFPS(GetMonitorRefreshRate(0));
        SetExitKey(KEY_NULL);

#ifdef RLF_EDITOR
        MaximizeWindow();
#else
        // ToggleBorderlessWindowed();
#endif

        addSystem<rlf::System::PhysicsSystem>();
        addSystem<rlf::System::AudioSystem>();
        addSystem<rlf::System::RenderSystem>();
        addSystem<rlf::System::ResourceSystem>();

#ifdef RLF_EDITOR
        addSystem<rlf::System::EditorSystem>();
#endif

        // Register Types here
        rlf::NodeManager::getInstance().registerType<rlf::Node::BaseNode>();

        rlf::NodeManager::getInstance().registerType<rlf::Node::MusicNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::SoundNode>();

        rlf::NodeManager::getInstance().registerType<rlf::Node::ColliderNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::BoxColliderNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::CircleColliderNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::RigidbodyNode>();

        // Render Nodes
        rlf::NodeManager::getInstance().registerType<rlf::Node::RenderNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::CameraNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::LineRenderNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::CircleRenderNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::QuadRenderNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::SpriteRenderNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::ParticleRenderNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::BurstParticleRenderNode>();

        // UI Nodes
        rlf::NodeManager::getInstance().registerType<rlf::Node::UINode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::UICameraNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::UIButtonNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::UISpriteNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::UITextNode>();
        rlf::NodeManager::getInstance().registerType<rlf::Node::UISliderNode>();

        // Run custom setup func, for registering of app node types
        if (mSetupFunc)
        {
            mSetupFunc();
        }

        // Initialize all systems
        for (auto& system : mSystems)
        {
            system->init();
        }

        // Create root node
        mRootNode = std::make_shared<rlf::Node::BaseNode>();
        mRootNode->setName(mRootNode->getTypeNameImpl().data());

        // Attempt to load initial world if there's one set
        if (!mInitialWorldToLoad.empty())
        {
            mRootNode->deserializeFromFile(mInitialWorldToLoad);
        }

        // Run init
        if (mInitFunc)
        {
            mInitFunc(mRootNode);
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

            if (mUpdateFunc)
            {
                mUpdateFunc(mRootNode);
            }

            mRootNode->preUpdate();
            mRootNode->update();
            mRootNode->postUpdate();

            for (auto& system : mSystems)
            {
                system->update();
            }

            BeginDrawing();
            ClearBackground(BLACK);

            for (auto& system : mSystems)
            {
                system->render();
            }

            // #if defined(RLF_DEBUG) && !defined(RLF_EDITOR)
            // Draw FPS counter
            DrawFPS(10, 10);
            // #endif

            EndDrawing();
        }

        if (mShutdownFunc)
        {
            mShutdownFunc(mRootNode);
        }

        mRootNode->shutdown();
        mRootNode.reset();

        std::ranges::reverse(mSystems);
        for (auto const& system : mSystems)
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

    void Engine::setSetupFunc(std::function<void()> setupFunc)
    {
        mSetupFunc = setupFunc;
    }

    void Engine::setInitFunc(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> initFunc)
    {
        mInitFunc = initFunc;
    }

    void Engine::setUpdateFunc(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> updateFunc)
    {
        mUpdateFunc = updateFunc;
    }

    void Engine::setShutdownFunc(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> shutdownFunc)
    {
        mShutdownFunc = shutdownFunc;
    }

    std::shared_ptr<Node::BaseNode> Engine::getRootNode() const
    {
        return mRootNode;
    }
}
