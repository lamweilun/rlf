#include <Node/Player/PlayerBulletNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

#include <Node/Enemy/EnemyNode.hpp>

namespace ext::Node {

    void PlayerBulletNode::initImpl() {
        if (auto childCollider = getFirstChildOfType<rlf::Node::CircleColliderNode>()) {
            auto bulletCollider = childCollider.value();
            bulletCollider->setCollidedCallback([this](std::vector<rlf::CollideInfo> const& infos) {
                for (auto const& info : infos) {
                    if (info.other->hasTag("Enemy")) {
                        // Collision resolver
                        setPosition(getPosition() + info.collidedNormal * info.collidedDepth);

                        // Test reflection
                        auto const& tangent     = info.collidedNormal;
                        auto        newVelocity = Vector2Reflect(Vector2Normalize(getVelocity()), tangent);
                        setVelocity(newVelocity);
                        // setToDestroy(true);
                    }
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
