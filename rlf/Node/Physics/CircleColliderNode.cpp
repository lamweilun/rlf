#include <Node/Physics/CircleColliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

namespace rlf::Node {
    void CircleColliderNode::setupImpl() {
        auto circleCollider = shared_from_this()->as<CircleColliderNode>();
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->addColliderNode(circleCollider);
    }
    void CircleColliderNode::shutdownImpl() {
        auto circleCollider = shared_from_this()->as<CircleColliderNode>();
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->removeColliderNode(circleCollider);
    }

    void CircleColliderNode::updateImpl() {
        auto circleCollider = shared_from_this()->as<CircleColliderNode>();
        auto infos          = rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->getCollisionInfos(circleCollider);
        // mCollidedNodes      = rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->checkCollision(circleCollider);
        mCollisionInfos = infos;
        ColliderNode::updateImpl();
    }
}
