#include <Node/Enemy/EnemyRenderNode.hpp>

namespace rlf {
    void EnemyRenderNode::renderImpl() {
        DrawCubeV(Vector3Zeros, Vector3Ones * 2.0f, RED);
    }
}
