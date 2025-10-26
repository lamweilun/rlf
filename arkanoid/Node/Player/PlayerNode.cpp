#include <Node/Player/PlayerNode.hpp>

#include <Engine/Engine.hpp>

#include <Util/Range.hpp>

namespace ark::Node {

    void PlayerNode::initImpl() {
        mBallNode = getRootNode()->getFirstChildOfName<ark::Node::BallNode>("BallNode").value();
    }

    void PlayerNode::updateImpl() {
        // Movement controls
        Vector2 newVelocity = Vector2Zeros;
        if (IsKeyDown(KEY_A)) {
            newVelocity.x = -1.0f;
        } else if (IsKeyDown(KEY_D)) {
            newVelocity.x = 1.0f;
        }
        setVelocity(Vector2Normalize(newVelocity));

        if (!mHasStarted) {
            mBallNode->setPosition({getPosition().x, 250.0f});
        }

        if (IsKeyReleased(KEY_SPACE)) {
            if (!mHasStarted) {
                mHasStarted = true;
                mBallNode->setSpeed(500.0f);
                auto const angleRange = rlf::Range<f32>(-45, 45);
                mBallNode->setVelocity(Vector2FromAngleDeg(angleRange.getValue()));
            }
        }

        rlf::Node::RigidbodyNode::updateImpl();
    }
}
