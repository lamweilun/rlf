#include <Node/Player/PlayerRenderNode.hpp>

namespace rlf {
    void PlayerRenderNode::renderImpl() {
        DrawCircle(0, 0, 1.0f, WHITE);
    }
}
