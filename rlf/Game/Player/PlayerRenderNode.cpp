#include <Game/Player/PlayerRenderNode.hpp>

namespace rlf {
    void PlayerRenderNode::renderImpl() {
        DrawRectangleV({-0.5f, -0.5f}, Vector2Ones, getTint());
    }
}
