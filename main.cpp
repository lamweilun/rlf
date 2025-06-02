#include <Node/Node.hpp>

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "Hello rlf");
    // SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    auto rootNode = std::make_shared<rlf::BaseNode>();
    rootNode->addChild<rlf::PlayerNode>();
    auto enemy1      = rootNode->addChild<rlf::EnemyNode>();
    enemy1->position = Vector3{640, 360, 0};

    while (!WindowShouldClose()) {
        rootNode->update();

        BeginDrawing();
        ClearBackground(BLACK);

        rootNode->render();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}
