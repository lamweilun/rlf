#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    void RigidbodyNode::updateImpl() {
        auto newPosition = getPosition() + velocity * speed * GetFrameTime();
        setPosition(newPosition);
    }
}
