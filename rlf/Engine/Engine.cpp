#include <Engine/Engine.hpp>

#include <System/Physics/PhysicsSystem.hpp>
#include <System/Audio/AudioSystem.hpp>
#include <System/Render/RenderSystem.hpp>

// All Node Types here
#include <Node/Audio/SoundNode.cpp>

#include <Node/Physics/ColliderNode.cpp>
#include <Node/Physics/LineColliderNode.cpp>
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

#include <Node/BaseNode.cpp>

#ifdef RLF_EDITOR
#include <System/Editor/EditorSystem.hpp>
#endif

namespace rlf {
    Engine& Engine::getInstance() {
        static Engine engine;
        return engine;
    }

    Engine::Engine(u32 const width, u32 const height, char const* title) {
        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
        InitWindow(static_cast<int>(width), static_cast<int>(height), title);
        SetWindowMonitor(0);
        SetTargetFPS(GetMonitorRefreshRate(0));

        addSystem<rlf::System::PhysicsSystem>();
        addSystem<rlf::System::AudioSystem>();
        addSystem<rlf::System::RenderSystem>();

#ifdef RLF_EDITOR
        addSystem<rlf::System::EditorSystem>();
#endif
    }

    Engine::~Engine() {
        std::reverse(std::begin(mSystems), std::end(mSystems));
        for (auto& system : mSystems) {
            system->shutdown();
        }
        CloseWindow();
    }

    void Engine::run() {
        // Register Types here
        rlf::TypeManager::getInstance().registerType<rlf::Node::BaseNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::SoundNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::ColliderNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::LineColliderNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::CircleColliderNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::RigidbodyNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::RenderNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::CameraNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::LineRenderNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::CircleRenderNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::QuadRenderNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::SpriteRenderNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::ParticleRenderNode>();
        rlf::TypeManager::getInstance().registerType<rlf::Node::BurstParticleRenderNode>();
        if (mSetupFunc) {
            mSetupFunc();
        }

        // Initialize all systems
        for (auto& system : mSystems) {
            system->init();
        }

        // Create root node
        mRootNode = std::make_shared<rlf::Node::BaseNode>();
        mRootNode->setName(mRootNode->getTypeNameImpl().data());

        // Attempt to load initial world if there's one set
        if (!mInitialWorldToLoad.empty()) {
            mRootNode->deserializeFromFile(mInitialWorldToLoad);
        }

        // Run init
        if (mInitFunc) {
            mInitFunc(mRootNode);
        }
        mRootNode->init();

        while (!WindowShouldClose()) {
            if (mUpdateFunc) {
                mUpdateFunc(mRootNode);
            }

            mRootNode->update();

            for (auto& system : mSystems) {
                system->update();
            }

            BeginDrawing();
            ClearBackground(BLACK);

            for (auto& system : mSystems) {
                system->render();
            }

            DrawFPS(10, 10);
            EndDrawing();
        }

        if (mShutdownFunc) {
            mShutdownFunc(mRootNode);
        }

        mRootNode->shutdown();
        mRootNode.reset();
    }

    void Engine::setInitialWorldToLoad(std::string const& filename) {
        mInitialWorldToLoad = filename;
    }

    void Engine::setAssetsDirectory(std::filesystem::path const& assetsPath) {
        std::filesystem::current_path(assetsPath);
    }

    void Engine::setSetupFunc(std::function<void()> setupFunc) {
        mSetupFunc = setupFunc;
    }

    void Engine::setInitFunc(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> initFunc) {
        mInitFunc = initFunc;
    }

    void Engine::setUpdateFunc(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> updateFunc) {
        mUpdateFunc = updateFunc;
    }

    void Engine::setShutdownFunc(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> shutdownFunc) {
        mShutdownFunc = shutdownFunc;
    }

    std::shared_ptr<Node::BaseNode> Engine::getRootNode() const {
        return mRootNode;
    }
}
