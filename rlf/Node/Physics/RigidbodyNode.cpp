#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    void RigidbodyNode::updateImpl() {
        setPosition(getPosition() + velocity * speed * GetFrameTime());
    }
}
