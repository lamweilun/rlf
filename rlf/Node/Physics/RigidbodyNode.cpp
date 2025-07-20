#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    void RigidbodyNode::updateImpl() {
        auto newPosition = getPosition() + mVelocity * mSpeed * GetFrameTime();
        setPosition(newPosition);
    }
}
