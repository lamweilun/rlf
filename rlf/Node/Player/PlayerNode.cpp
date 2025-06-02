#include <Node/Player/PlayerNode.hpp>

#include <Node/Player/PlayerBulletNode.hpp>

namespace rlf {

    PlayerNode::PlayerNode() {
        speed = 200.0f;
        scale = Vector3{10, 10, 0};
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
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            auto bulletNode      = getRootNode()->addChild<PlayerBulletNode>();
            bulletNode->position = position;
            bulletNode->scale    = Vector3{5, 5, 0};
            bulletNode->velocity = Vector3{GetMousePosition().x, GetMousePosition().y, 0.0f} - bulletNode->position;
            bulletNode->velocity = Vector3Normalize(bulletNode->velocity);
            bulletNode->speed    = 1000.0f;
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
