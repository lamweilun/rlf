#include <Player/PlayerNode.hpp>
#include <Player/PlayerRenderNode.hpp>

#include <Node/Physics/LineColliderNode.hpp>

namespace rlf {
    void PlayerNode::initImpl() {
        setSpeed(300.0f);

        Vector3 const scale = {10.0f, 100.0f, 1.0f};

        addChild<rlf::PlayerRenderNode>()->setScale(scale);

        auto colliderNode = addChild<rlf::LineColliderNode>();
        colliderNode->setScale(scale);
        colliderNode->addTag("Player");
        colliderNode->setStartPoint({0.5f, -0.5f, 0.0f});
        colliderNode->setEndPoint({0.5f, 0.5f, 0.0f});
    }

    void PlayerNode::updateImpl() {
        auto velocity = Vector3Zeros;
        if (IsKeyDown(KEY_W)) {
            velocity.y = -1;
        } else if (IsKeyDown(KEY_S)) {
            velocity.y = 1;
        }
        velocity = Vector3Normalize(velocity);
        setVelocity(velocity);

        RigidbodyNode::updateImpl();
    }
}
