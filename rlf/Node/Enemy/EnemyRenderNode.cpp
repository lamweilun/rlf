#include <Node/Enemy/EnemyRenderNode.hpp>

namespace rlf {
    void EnemyRenderNode::renderImpl() {
        DrawSphere(Vector3Zeros, 1.0f, RED);
    }
}
