#include <Node/Node.hpp>

#include <System/PhysicsSystem.hpp>
#include <System/RendererSystem.hpp>

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "Hello rlf");
    // SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    rlf::PhysicsSystem::getInstance();
    auto& rendererSystem = rlf::RendererSystem::getInstance();

    auto rootNode = std::make_shared<rlf::BaseNode>();

    auto playerNode = rootNode->addChild<rlf::PlayerNode>();
    playerNode->setPosition(Vector3{300, 360, 0});

    // auto enemy1 = rootNode->addChild<rlf::EnemyNode>();
    // enemy1->setPosition(Vector3{640, 360, 0});

    rootNode->init();

    while (!WindowShouldClose()) {
        rootNode->update();

        BeginDrawing();
        ClearBackground(BLACK);

        rendererSystem.render();

        DrawFPS(10, 10);
        EndDrawing();
    }

    rootNode->shutdown();

    CloseWindow();
}
