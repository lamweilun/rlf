#include <Node/Physics/SphereColliderNode.hpp>

#include <System/PhysicsSystem.hpp>

#ifdef RLF_DEBUG
#include <Node/Render/SphereRenderNode.hpp>
#endif

namespace rlf {
    void SphereColliderNode::initImpl() {
        rlf::PhysicsSystem::getInstance().addColliderNode(std::static_pointer_cast<SphereColliderNode>(shared_from_this()));

#ifdef RLF_DEBUG
        auto childNode = addChild<SphereRenderNode>();
        childNode->setTint(GREEN);
        childNode->setLayer(1);
#endif
    }
    void SphereColliderNode::shutdownImpl() {
        rlf::PhysicsSystem::getInstance().removeColliderNode(std::static_pointer_cast<SphereColliderNode>(shared_from_this()));
    }

    void SphereColliderNode::updateImpl() {
        if (!mCollidedCallback) {
            return;
        }
        mCollidedNodes = rlf::PhysicsSystem::getInstance().checkCollision(std::static_pointer_cast<SphereColliderNode>(shared_from_this()));
        ColliderNode::updateImpl();
    }
}
