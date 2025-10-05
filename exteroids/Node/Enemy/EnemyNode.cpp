#include <Node/Enemy/EnemyNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

namespace ext::Node {
    void EnemyNode::initImpl() {
        auto enemyCollider = getFirstChildOfType<rlf::Node::CircleColliderNode>().value();
        enemyCollider->setCollidedCallback([this](std::shared_ptr<rlf::Node::ColliderNode> collided) {
            if (collided->hasTag("PlayerBullet")) {
                setHP(getHP() - 1);
            }
        });
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
