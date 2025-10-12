#include <Node/Enemy/EnemyNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

namespace ext::Node {
    void EnemyNode::initImpl() {
        auto enemyCollider = getFirstChildOfType<rlf::Node::CircleColliderNode>().value();
        enemyCollider->setCollidedCallback([this](std::vector<rlf::CollideInfo> const& infos) {
            for (auto const& info : infos) {
                if (info.other->hasTag("PlayerBullet")) {
                    setToDestroy(true);
                }
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
