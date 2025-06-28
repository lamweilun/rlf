#include <Node/Player/PlayerNode.hpp>

#include <Node/Player/PlayerRenderNode.hpp>
#include <Node/Player/PlayerBulletNode.hpp>

namespace rlf {

    void PlayerNode::initImpl() {
        setScale(Vector3{10, 10, 0});
        mSpeed = 200.0f;

        getOrAddFirstChildOfType<PlayerRenderNode>();
    }

    void PlayerNode::updateImpl() {
        attackControls();
        movementControls();
        RigidbodyNode::updateImpl();
    }

    void PlayerNode::attackControls() {
        // Spawn a player bullet at the position of the player
        bool const isFiring = IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE);
        if (isFiring) {
            auto bulletNode = getRootNode()->addChild<PlayerBulletNode>();
            bulletNode->setPosition(getPosition());
            bulletNode->mVelocity = Vector3Normalize(Vector3{static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()), 0} - bulletNode->getPosition());
        }
    }

    void PlayerNode::movementControls() {
        mVelocity = Vector3Zeros;

        if (IsKeyDown(KEY_W)) {
            mVelocity.y = -1.0f;
        } else if (IsKeyDown(KEY_S)) {
            mVelocity.y = 1.0f;
        }

        if (IsKeyDown(KEY_A)) {
            mVelocity.x = -1.0f;
        } else if (IsKeyDown(KEY_D)) {
            mVelocity.x = 1.0f;
        }

        mVelocity = Vector3Normalize(mVelocity);
    }
}
