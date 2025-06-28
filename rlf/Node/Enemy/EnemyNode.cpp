#include <Node/Enemy/EnemyNode.hpp>
#include <Node/Enemy/EnemyRenderNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/SphereColliderNode.hpp>

namespace rlf {
    void EnemyNode::initImpl() {
        setScale(Vector3{20, 20, 0});
        getOrAddFirstChildOfType<EnemyRenderNode>();
        auto enemyCollider = getOrAddFirstChildOfType<SphereColliderNode>();
        enemyCollider->addTag("Enemy");
    }
}
