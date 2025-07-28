#include <Node/Physics/SphereColliderNode.hpp>

#include <System/Physics/PhysicsSystem.hpp>

#ifdef RLF_DEBUG
#include <Node/Render/SphereRenderNode.hpp>
#endif

namespace rlf {
    void SphereColliderNode::initImpl() {
        rlf::System::PhysicsSystem::getInstance().addColliderNode(std::static_pointer_cast<SphereColliderNode>(shared_from_this()));

#ifdef RLF_DEBUG
        auto childNode = addChild<SphereRenderNode>();
        childNode->setTint(GREEN);
        childNode->setLayer(1);
#endif
    }
    void SphereColliderNode::shutdownImpl() {
        rlf::System::PhysicsSystem::getInstance().removeColliderNode(std::static_pointer_cast<SphereColliderNode>(shared_from_this()));
        ColliderNode::shutdownImpl();
    }

    void SphereColliderNode::updateImpl() {
        if (!mCollidedCallback) {
            return;
        }
        mCollidedNodes = rlf::System::PhysicsSystem::getInstance().checkCollision(std::static_pointer_cast<SphereColliderNode>(shared_from_this()));
        ColliderNode::updateImpl();
    }
}
