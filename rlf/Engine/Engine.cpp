#include <Engine/Engine.hpp>

#include <System/Physics/PhysicsSystem.hpp>
#include <System/Audio/AudioSystem.hpp>
#include <System/Render/RenderSystem.hpp>

#ifdef RLF_EDITOR
#include <System/Editor/EditorSystem.hpp>
#endif

namespace rlf {
    Engine& Engine::getInstance() {
        static Engine engine;
        return engine;
    }

    Engine::Engine(u32 const width, u32 const height, char const* title) {
        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
        InitWindow(static_cast<int>(width), static_cast<int>(height), title);
        SetWindowMonitor(0);
        SetTargetFPS(GetMonitorRefreshRate(0));

        addSystem<rlf::System::PhysicsSystem>();
        addSystem<rlf::System::AudioSystem>();
        addSystem<rlf::System::RenderSystem>();

#ifdef RLF_EDITOR
        addSystem<rlf::System::EditorSystem>();
#endif

        for (auto& system : mSystems) {
            system->init();
        }

        mRootNode = std::make_shared<rlf::Node::BaseNode>();
    }

    Engine::~Engine() {
        mRootNode->shutdown();
        mRootNode.reset();

        std::reverse(std::begin(mSystems), std::end(mSystems));
        for (auto& system : mSystems) {
            system->shutdown();
        }
        CloseWindow();
    }

    void Engine::run(std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> setupFunc) {
        mRootNode->init();

        if (setupFunc) {
            setupFunc(mRootNode);
        }

        while (!WindowShouldClose()) {
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
    }

    std::shared_ptr<Node::BaseNode> Engine::getRootNode() const {
        return mRootNode;
    }
}
