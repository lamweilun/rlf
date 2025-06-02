#include <Node/Player/PlayerBulletNode.hpp>

namespace rlf {

    void PlayerBulletNode::updateImpl() {
        if (position.x < 0 || position.x > 1280 || position.y < 0 || position.y > 720) {
            markForDestroy = true;
        }

        RigidbodyNode::updateImpl();
    }

    void PlayerBulletNode::renderImpl() {
        DrawCircle(0, 0, 1.0f, BLUE);
    }
}
