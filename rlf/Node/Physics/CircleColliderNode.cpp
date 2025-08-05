#include <Node/Physics/CircleColliderNode.hpp>

#include <System/Physics/PhysicsSystem.hpp>

#ifdef RLF_DEBUG
#include <Node/Render/CircleRenderNode.hpp>
#endif

namespace rlf::Node {
    void CircleColliderNode::initImpl() {
        rlf::System::PhysicsSystem::getInstance().addColliderNode(std::static_pointer_cast<CircleColliderNode>(shared_from_this()));

#ifdef RLF_DEBUG
        auto childNode = addChild<CircleRenderNode>();
        childNode->setTint(GREEN);
        childNode->setLayer(1);
#endif
    }
    void CircleColliderNode::shutdownImpl() {
        rlf::System::PhysicsSystem::getInstance().removeColliderNode(std::static_pointer_cast<CircleColliderNode>(shared_from_this()));
        ColliderNode::shutdownImpl();
    }

    void CircleColliderNode::updateImpl() {
        if (!mCollidedCallback) {
            return;
        }
        mCollidedNodes = rlf::System::PhysicsSystem::getInstance().checkCollision(std::static_pointer_cast<CircleColliderNode>(shared_from_this()));
        ColliderNode::updateImpl();
    }
}
