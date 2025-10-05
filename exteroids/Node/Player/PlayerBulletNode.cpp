#include <Node/Player/PlayerBulletNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

#include <Node/Enemy/EnemyNode.hpp>

namespace ext::Node {

    void PlayerBulletNode::initImpl() {
        if (auto childCollider = getFirstChildOfType<rlf::Node::CircleColliderNode>()) {
            auto bulletCollider = childCollider.value();
            bulletCollider->setCollidedCallback([this](std::shared_ptr<rlf::Node::ColliderNode> collided) {
                if (collided->hasTag("Enemy")) {
                    setToDestroy(true);
                    // auto enemy = collided->getParent().lock()->as<EnemyNode>();
                    // enemy->setHP(enemy->getHP() - 1);
                }
            });
        }
    }

    void PlayerBulletNode::updateImpl() {
        auto const pos              = getGlobalPosition();
        auto const halfScreenWidth  = static_cast<f32>(GetScreenWidth()) * 0.5f;
        auto const halfScreenHeight = static_cast<f32>(GetScreenHeight()) * 0.5f;
        if (pos.x <= -halfScreenWidth || pos.x >= halfScreenWidth) {
            setToDestroy(true);
        }
        if (pos.y <= -halfScreenHeight || pos.y >= halfScreenHeight) {
            setToDestroy(true);
        }

        rlf::Node::RigidbodyNode::updateImpl();
    }
}
