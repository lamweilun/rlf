#include <Player/PlayerNode.hpp>
#include <Player/PlayerRenderNode.hpp>

#include <Node/Physics/LineColliderNode.hpp>

namespace rlf::Node {
    void PlayerNode::updateImpl() {
        auto velocity = Vector2Zeros;
        if (IsKeyDown(KEY_W)) {
            velocity.y = -1;
        } else if (IsKeyDown(KEY_S)) {
            velocity.y = 1;
        }
        velocity = Vector2Normalize(velocity);
        setVelocity(velocity);

        RigidbodyNode::updateImpl();
    }
}
