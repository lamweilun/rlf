#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf::Node {

    void RigidbodyNode::setVelocity(Vector2 const& velocity) {
        mVelocity = velocity;
    }
    Vector2 const& RigidbodyNode::getVelocity() const {
        return mVelocity;
    }

    void RigidbodyNode::setVelocityFromAngleRad(f32 const angleRad) {
        mVelocity = Vector2FromAngleRad(angleRad);
    }
    void RigidbodyNode::setVelocityFromAngleDeg(f32 const angleDeg) {
        setVelocityFromAngleRad(angleDeg * DEG2RAD);
    }

    void RigidbodyNode::setSpeed(f32 const speed) {
        mSpeed = speed;
    }
    f32 RigidbodyNode::getSpeed() const {
        return mSpeed;
    }

    void RigidbodyNode::updateImpl() {
        auto newPosition = getPosition() + mVelocity * mSpeed * GetFrameTime();
        setPosition(newPosition);
    }
}
