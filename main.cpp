#include <Node/NodeInclude.hpp>

#include <NodeSystem/NodeDestroyer.hpp>
#include <NodeSystem/NodeRenderer.hpp>
#include <NodeSystem/NodeUpdater.hpp>

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "Hello rlf");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    rlf::NodeDestroyer destroyer;
    rlf::NodeUpdater   updater;
    rlf::NodeRenderer  renderer;

    auto& rootNode      = rlf::NodeBase::getRootNode();
    auto& playerNode    = rlf::NodeBase::getRootNodeBase().addChild<rlf::PlayerNode>();
    playerNode.position = Vector3{0, 360, 0};

    while (!WindowShouldClose()) {
        std::visit(destroyer, rootNode);
        std::visit(updater, rootNode);

        auto rootNodeCopy = rootNode;
        BeginDrawing();
        ClearBackground(BLACK);

        std::visit(renderer, rootNodeCopy);

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}
