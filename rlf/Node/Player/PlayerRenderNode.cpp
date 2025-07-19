#include <Node/Player/PlayerRenderNode.hpp>

namespace rlf {
    void PlayerRenderNode::renderImpl() {
        DrawCircleV(Vector2Zeros, 1.0f, getTint());
    }
}
