#include <Node/Enemy/EnemyRenderNode.hpp>

namespace rlf {
    void EnemyRenderNode::initImpl() {
        RenderNode::initImpl();
        setTint(RED);
    }

    void EnemyRenderNode::renderImpl() {
        DrawCircleV(Vector2Zeros, 1.0f, getTint());
    }
}
