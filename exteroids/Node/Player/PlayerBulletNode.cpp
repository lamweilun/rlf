#include <Node/Player/PlayerBulletNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

namespace ext::Node {

    void PlayerBulletNode::initImpl() {
        if (auto const bulletCollider = getFirstChildOfType<rlf::Node::CircleColliderNode>()) {
            bulletCollider.value()->setCollidedCallback([this](rlf::CollideInfo const& info) {
                if (info.other && info.other->hasTag("Enemy")) {
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
