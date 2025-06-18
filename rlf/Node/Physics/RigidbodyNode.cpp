#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    void RigidbodyNode::updateImpl() {
        auto newPosition = getPosition() + velocity * speed * GetFrameTime();
        setPosition(newPosition);
    }

    rlf::Json RigidbodyNode::serializeImpl() const {
        rlf::Json j   = BaseNode::serializeImpl();
        j["velocity"] = velocity;
        j["speed"]    = speed;
        return j;
    }
}
