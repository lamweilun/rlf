#include <Node/Player/PlayerBulletRenderNode.hpp>

namespace rlf {
    void PlayerBulletRenderNode::initImpl() {
        RenderNode::initImpl();
        setTint(BLUE);
    }

    void PlayerBulletRenderNode::renderImpl() {
        DrawCircleV(Vector2Zeros, 1.0f, getTint());
    }
}
