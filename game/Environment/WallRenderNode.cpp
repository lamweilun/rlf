#include <game/Environment/WallRenderNode.hpp>

namespace rlf {
    void WallRenderNode::renderImpl() {
        DrawRectangleV({-0.5f, -0.5f}, Vector2Ones, getTint());
    }
}
