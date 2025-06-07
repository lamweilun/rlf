#include <Node/Player/PlayerNode.hpp>

#include <Node/Player/PlayerBulletNode.hpp>

namespace rlf {

    PlayerNode::PlayerNode() {
        speed = 200.0f;
        setScale(Vector3{10, 10, 0});
    }

    void PlayerNode::updateImpl() {
        mouseControls();
        movementControls();
        RigidbodyNode::updateImpl();
    }

    void PlayerNode::renderImpl() {
        DrawCircle(0, 0, 1.0f, WHITE);
    }

    void PlayerNode::mouseControls() {
        // Spawn a player bullet at the position of the player
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            auto bulletNode = getRootNode()->addChild<PlayerBulletNode>();
            bulletNode->setPosition(getPosition());
            bulletNode->velocity = Vector3{GetMousePosition().x, GetMousePosition().y, 0.0f} - bulletNode->getPosition();
            bulletNode->velocity = Vector3Normalize(bulletNode->velocity);
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
