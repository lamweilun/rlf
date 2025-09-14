#include <Node/Player/PlayerBulletNode.hpp>

namespace ext::Node {

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
