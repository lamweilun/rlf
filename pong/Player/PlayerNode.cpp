#include <Player/PlayerNode.hpp>

#include <Node/Physics/LineColliderNode.hpp>

namespace rlf::Node {
    void PlayerNode::updateImpl() {
        auto velocity = Vector2Zeros;

        int upKey   = mIsPlayerOne ? KEY_W : KEY_UP;
        int downKey = mIsPlayerOne ? KEY_S : KEY_DOWN;

        if (IsKeyDown(upKey)) {
            velocity.y = -1;
        } else if (IsKeyDown(downKey)) {
            velocity.y = 1;
        }

        velocity = Vector2Normalize(velocity);
        setVelocity(velocity);

        RigidbodyNode::updateImpl();
    }
}
