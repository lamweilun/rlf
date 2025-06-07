#include <Node/Enemy/EnemyNode.hpp>

namespace rlf {
    EnemyNode::EnemyNode() {
        setScale(Vector3{20, 20, 0});
    }

    void EnemyNode::renderImpl() {
        DrawCircle(0, 0, 1.0f, RED);
    }
}
