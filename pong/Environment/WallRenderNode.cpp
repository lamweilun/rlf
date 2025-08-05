#include <Environment/WallRenderNode.hpp>

namespace rlf::Node {
    void WallRenderNode::renderImpl() {
        DrawRectangleV({-0.5f, -0.5f}, Vector2Ones, getTint());
    }
}
