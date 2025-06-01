#include <Node/NodeBase.hpp>
#include <Node/Physics/RigidbodyNode.hpp>
#include <Node/Player/PlayerNode.hpp>
#include <Node/Player/PlayerBulletNode.hpp>

#include <NodeSystem/NodeDestroyer.hpp>
#include <NodeSystem/NodeRenderer.hpp>
#include <NodeSystem/NodeUpdater.hpp>

#include <print>

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "Hello rlf");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    // SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
    // ToggleBorderlessWindowed();

    rlf::NodeDestroyer destroyer;
    rlf::NodeUpdater   updater;
    rlf::NodeRenderer  renderer;

    rlf::Node rootNode   = rlf::NodeBase();
    auto     &playerNode = std::get<rlf::NodeBase>(rootNode).addChild<rlf::PlayerNode>();
    playerNode.position  = Vector3{640, 360, 0};

    while (!WindowShouldClose()) {
        rootNode.visit(destroyer);
        rootNode.visit(updater);

        BeginDrawing();
        ClearBackground(BLACK);

        rootNode.visit(renderer);

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}
