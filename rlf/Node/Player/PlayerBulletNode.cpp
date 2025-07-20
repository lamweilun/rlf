#include <Node/Player/PlayerBulletNode.hpp>
#include <Node/Player/PlayerBulletRenderNode.hpp>

#include <Node/Enemy/EnemyNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/SphereColliderNode.hpp>

namespace rlf {

    void PlayerBulletNode::initImpl() {
        setScale(Vector3{5, 5, 0});
        mSpeed = 1000.0f;

        getOrAddFirstChildOfType<PlayerBulletRenderNode>();

        auto bulletColliderNode = getOrAddFirstChildOfType<rlf::BoxColliderNode>();
        bulletColliderNode->addTag("PlayerBullet");
        bulletColliderNode->setCollidedCallback([this](std::shared_ptr<rlf::ColliderNode> cn) {
            if (cn->hasTag("Enemy")) {
                setToDestroy(true);

                auto newScale = cn->getParent().lock()->getScale();
                newScale.x -= Vector3Ones.x * 0.01f;
                newScale.y -= Vector3Ones.y * 0.01f;
                cn->getParent().lock()->setScale(newScale);
            }
        });
    }

    void PlayerBulletNode::updateImpl() {
        auto const& position = getPosition();
        if (position.x < 0 || position.x > 1280 || position.y < 0 || position.y > 720) {
            setToDestroy(true);
        }

        float angle = std::atan2f(mVelocity.y, mVelocity.x);
        setRotationEulerRad(Vector3{0, 0, angle});

        RigidbodyNode::updateImpl();
    }
}
