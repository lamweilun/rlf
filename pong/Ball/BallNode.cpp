#include <Ball/BallNode.hpp>
#include <Ball/BallRenderNode.hpp>
#include <Node/Physics/SphereColliderNode.hpp>

#include <Node/Render/ParticleRenderNode.hpp>

namespace rlf {
    void BallNode::initImpl() {
        setScale({10.0f, 10.0f, 1.0f});
        setSpeed(500.0f);

        auto renderNode = addChild<rlf::BallRenderNode>();
        renderNode->setTint(RED);

        auto colliderNode = addChild<rlf::SphereColliderNode>();
        colliderNode->setCollidedCallback([this](std::shared_ptr<rlf::ColliderNode> node) {
            if (node->hasTag("Player") || node->hasTag("Wall")) {
                auto velocity = Vector3Reflect(getVelocity(), Vector3Normalize(node->getGlobalRight()));
                setVelocity(Vector3Normalize(velocity));

                auto pn = this->getRootNode()->addChild<ParticleRenderNode>();
                pn->setMaxCount(100);
                pn->setSpawnRate(0.25f);
                pn->setPosition(getGlobalPosition());
            }
        });

        Vector3 velocity = Vector3Zeros;
        velocity.x       = -1.0f;
        velocity.y       = static_cast<f32>(GetRandomValue(-100, 100)) / 100.0f - 0.5f;
        setVelocity(Vector3Normalize(velocity));
    }
}
