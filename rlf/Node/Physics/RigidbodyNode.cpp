#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    void RigidbodyNode::updateImpl() {
        position += velocity * speed * GetFrameTime();
    }
}
