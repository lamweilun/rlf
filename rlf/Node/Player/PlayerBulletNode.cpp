#include <Node/Player/PlayerBulletNode.hpp>
#include <Node/Player/PlayerBulletRenderNode.hpp>

#include <Node/Enemy/EnemyNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/SphereColliderNode.hpp>

namespace rlf {

    void PlayerBulletNode::initImpl() {
        setScale(Vector3{5, 5, 0});
        speed = 1000.0f;

        addChild<PlayerBulletRenderNode>();

        auto bulletColliderNode = addChild<rlf::SphereColliderNode>();
        bulletColliderNode->setCollidedCallback([this](std::shared_ptr<rlf::ColliderNode> cn) {
            if (auto cnParent = cn->getParent().lock()) {
                if (std::dynamic_pointer_cast<rlf::EnemyNode>(cnParent)) {
                    setToDestroy(true);
                }
            }
        });
    }

    void PlayerBulletNode::updateImpl() {
        auto const& position = getPosition();
        if (position.x < 0 || position.x > 1280 || position.y < 0 || position.y > 720) {
            setToDestroy(true);
        }

        RigidbodyNode::updateImpl();
    }
}
