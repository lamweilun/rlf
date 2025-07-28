#include <Engine/Engine.hpp>

#include <System/Audio/AudioSystem.hpp>
#include <System/Physics/PhysicsSystem.hpp>
#include <System/Render/RenderSystem.hpp>
#include <System/Type/TypeSystem.hpp>

namespace rlf {
    Engine::Engine(u32 const width, u32 const height, char const* title) {
        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
        InitWindow(static_cast<int>(width), static_cast<int>(height), title);
        // SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

        rlf::System::TypeSystem::getInstance();
        auto& audioSystem = rlf::System::AudioSystem::getInstance();
        rlf::System::RenderSystem::getInstance();
        rlf::System::PhysicsSystem::getInstance();

        audioSystem.init();
    }

    Engine::~Engine() {
        rlf::System::AudioSystem::getInstance().shutdown();

        CloseWindow();
    }

    void Engine::run(std::function<void(std::shared_ptr<rlf::BaseNode>)> setupFunc) {
        auto rootNode = std::make_shared<rlf::BaseNode>();
        rootNode->init();

        if (setupFunc) {
            setupFunc(rootNode);
        }

        auto& rendererSystem = rlf::System::RenderSystem::getInstance();

        while (!WindowShouldClose()) {
            rootNode->update();

            BeginDrawing();
            ClearBackground(BLACK);

            rendererSystem.render();

#ifdef RLF_DEBUG
            DrawFPS(10, 10);
#endif
            EndDrawing();
        }

        rootNode->shutdown();
    }
}
