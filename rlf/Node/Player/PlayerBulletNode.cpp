#include <Node/Player/PlayerBulletNode.hpp>

namespace rlf {

    void PlayerBulletNode::initImpl() {
        setScale(Vector3{5, 5, 0});
        speed = 1000.0f;
    }

    void PlayerBulletNode::updateImpl() {
        auto const& position = getPosition();
        if (position.x < 0 || position.x > 1280 || position.y < 0 || position.y > 720) {
            setToDestroy(true);
        }

        RigidbodyNode::updateImpl();
    }

    void PlayerBulletNode::renderImpl() {
        DrawCircle(0, 0, 1.0f, BLUE);
    }
}
