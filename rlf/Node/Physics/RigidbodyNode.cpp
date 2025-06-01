#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    void RigidbodyNode::update() {
        position += velocity * speed * GetFrameTime();
    }
}
