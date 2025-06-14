#include <Node/Player/PlayerNode.hpp>

#include <Node/Player/PlayerRenderNode.hpp>
#include <Node/Player/PlayerBulletNode.hpp>

namespace rlf {

    void PlayerNode::initImpl() {
        setScale(Vector3{10, 10, 0});
        speed = 200.0f;

        addChild<PlayerRenderNode>();
    }

    void PlayerNode::updateImpl() {
        mouseControls();
        movementControls();
        RigidbodyNode::updateImpl();
    }

    void PlayerNode::mouseControls() {
        // Spawn a player bullet at the position of the player
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            auto bulletNode = getRootNode()->addChild<PlayerBulletNode>();
            bulletNode->setPosition(getPosition());
            bulletNode->velocity = Vector3{GetMousePosition().x, GetMousePosition().y, 0.0f} - bulletNode->getPosition();
            bulletNode->velocity = Vector3Normalize(bulletNode->velocity);

            float angle = std::atan2f(bulletNode->velocity.y, bulletNode->velocity.x);
            bulletNode->setRotationEulerRad(Vector3{0, 0, angle});
        }
    }

    void PlayerNode::movementControls() {
        velocity = Vector3Zeros;

        if (IsKeyDown(KEY_W)) {
            velocity.y = -1.0f;
        } else if (IsKeyDown(KEY_S)) {
            velocity.y = 1.0f;
        }

        if (IsKeyDown(KEY_A)) {
            velocity.x = -1.0f;
        } else if (IsKeyDown(KEY_D)) {
            velocity.x = 1.0f;
        }

        velocity = Vector3Normalize(velocity);
    }
}
