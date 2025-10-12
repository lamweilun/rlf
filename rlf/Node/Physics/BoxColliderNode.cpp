#include <Node/Physics/BoxColliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

namespace rlf::Node {
    void BoxColliderNode::setupImpl() {
        auto boxCollider = shared_from_this()->as<BoxColliderNode>();
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->addColliderNode(boxCollider);
    }
    void BoxColliderNode::shutdownImpl() {
        auto boxCollider = shared_from_this()->as<BoxColliderNode>();
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->removeColliderNode(boxCollider);
    }
    void BoxColliderNode::updateImpl() {
        auto boxCollider = shared_from_this()->as<BoxColliderNode>();
        mCollisionInfos  = rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->getCollisionInfos(boxCollider);
        ColliderNode::updateImpl();
    }
}
