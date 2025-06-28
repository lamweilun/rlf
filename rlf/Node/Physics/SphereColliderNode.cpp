#include <Node/Physics/SphereColliderNode.hpp>

#include <System/PhysicsSystem.hpp>

namespace rlf {
    void SphereColliderNode::initImpl() {
        rlf::PhysicsSystem::getInstance().addColliderNode(std::static_pointer_cast<SphereColliderNode>(shared_from_this()));
    }
    void SphereColliderNode::shutdownImpl() {
        rlf::PhysicsSystem::getInstance().removeColliderNode(std::static_pointer_cast<SphereColliderNode>(shared_from_this()));
    }

    void SphereColliderNode::updateImpl() {
        mCollidedNodes = rlf::PhysicsSystem::getInstance().checkCollision(std::static_pointer_cast<SphereColliderNode>(shared_from_this()));
        ColliderNode::updateImpl();
    }

#ifdef RLF_DEBUG
    void SphereColliderNode::renderImpl() {
        DrawSphereWires(Vector3Zeros, 1.0f, 8, 8, GREEN);
    }
#endif
}
