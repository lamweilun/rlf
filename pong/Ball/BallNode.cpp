#include <Ball/BallNode.hpp>
#include <Ball/BallRenderNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

#include <Node/Render/BurstParticleRenderNode.hpp>

namespace rlf::Node {
    void BallNode::initImpl() {
        auto colliderNode = addOrGetFirstChildOfType<rlf::Node::CircleColliderNode>();
        colliderNode->setCollidedCallback([this](std::shared_ptr<rlf::Node::ColliderNode> node) {
            if (node->hasTag("Player") || node->hasTag("Wall")) {
                auto oldVelocity = getVelocity();
                auto velocity    = Vector2Reflect(oldVelocity, Vector2Normalize(node->getGlobalRight()));
                setVelocity(Vector2Normalize(velocity));

                auto pn = this->getRootNode()->addChild<BurstParticleRenderNode>();
                pn->setToDestroyAfterBurst(true);
                pn->setBurstCount(1);
                pn->setMaxCount(10);
                pn->setSpawnRate(0.01f);
                pn->setLifeTimeRange({0.25f, 0.75f});
                pn->setStartSpeedRange({100, 700});
                pn->setEndSpeedRange({0, 0});
                pn->setStartScaleRange({3, 10});
                pn->setEndScaleRange({0, 0});

                auto const direction = Vector2Negate(oldVelocity);
                auto       minDir    = Vector2Rotate(direction, -30.0f * DEG2RAD);
                auto       maxDir    = Vector2Rotate(direction, 30.0f * DEG2RAD);

                pn->setDirectionRange({minDir, maxDir});
                pn->setPosition(getGlobalPosition());
            }
        });

        Vector2 velocity = Vector2Zeros;
        velocity.x       = -1.0f;
        velocity.y       = mVelocityRange.getValue() / 100.0f - 0.5f;
        setVelocity(Vector2Normalize(velocity));
    }
}
