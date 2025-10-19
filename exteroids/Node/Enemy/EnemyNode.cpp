#include <Node/Enemy/EnemyNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

namespace ext::Node {
    void EnemyNode::initImpl() {
        if (auto const enemyCollider = getFirstChildOfType<rlf::Node::BoxColliderNode>()) {
            enemyCollider.value()->setCollidedCallback([this](rlf::CollideInfo const& info) {
                if (info.other && info.other->hasTag("PlayerBullet")) {
                }
            });
        }
    }
    void EnemyNode::updateImpl() {
        rlf::Node::RigidbodyNode::updateImpl();
    }

    u32 EnemyNode::getHP() const {
        return mHP;
    }
    void EnemyNode::setHP(u32 const hp) {
        mHP = hp;
        if (mHP == 0) {
            setToDestroy(true);
        }
    }
}
