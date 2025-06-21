#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    void RigidbodyNode::updateImpl() {
        auto newPosition = getPosition() + mVelocity * mSpeed * GetFrameTime();
        setPosition(newPosition);
    }

    rlf::Json RigidbodyNode::serializeImpl() const {
        rlf::Json j   = BaseNode::serializeImpl();
        j["velocity"] = mVelocity;
        j["speed"]    = mSpeed;
        return j;
    }
    void RigidbodyNode::deserializeImpl(rlf::Json const& j) {
        BaseNode::deserializeImpl(j);
        mVelocity = j["velocity"];
        mSpeed    = j["speed"];
    }
}
