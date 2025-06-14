#include <Node/Player/PlayerBulletRenderNode.hpp>

namespace rlf {
    void PlayerBulletRenderNode::renderImpl() {
        DrawCircle(0, 0, 1.0f, BLUE);
    }
}
