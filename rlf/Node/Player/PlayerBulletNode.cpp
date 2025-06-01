#include <Node/Player/PlayerBulletNode.hpp>

namespace rlf {

    void PlayerBulletNode::update() {
        if (position.x < 0.0f || position.x > 1280 || position.y < 0.0f || position.y > 720) {
            markForDestroy = true;
        }

        RigidbodyNode::update();
    }

    void PlayerBulletNode::render() {
        DrawCircleV(Vector2Zeros, 5.0f, BLUE);
    }
}
