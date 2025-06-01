#include <Node/Node.hpp>

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

    rlf::NodeDestroyer destroyer;
    rlf::NodeUpdater   updater;
    rlf::NodeRenderer  renderer;

    auto &playerNode    = rlf::NodeBase::getRootNodeBase().addChild<rlf::PlayerNode>();
    playerNode.position = Vector3{640, 360, 0};

    while (!WindowShouldClose()) {
        std::visit(destroyer, rlf::NodeBase::getRootNode());
        std::visit(updater, rlf::NodeBase::getRootNode());

        auto rootNodeCopy = rlf::NodeBase::getRootNode();
        BeginDrawing();
        ClearBackground(BLACK);

        std::visit(renderer, rootNodeCopy);

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}
