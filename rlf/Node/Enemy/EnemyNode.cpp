#include <Node/Enemy/EnemyNode.hpp>
#include <Node/Enemy/EnemyRenderNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>

namespace rlf {
    void EnemyNode::initImpl() {
        setScale(Vector3{20, 20, 0});
        addChild<EnemyRenderNode>();
        addChild<BoxColliderNode>();
    }
}
