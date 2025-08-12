#include <Node/Physics/CircleColliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

#ifdef RLF_DEBUG
#include <Node/Render/CircleRenderNode.hpp>
#endif

namespace rlf::Node {
    void CircleColliderNode::initImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->addColliderNode(std::static_pointer_cast<CircleColliderNode>(shared_from_this()));

#ifdef RLF_DEBUG
        auto childNode = addChild<CircleRenderNode>();
        childNode->setTint(GREEN);
        childNode->setLayer(1);
#endif
    }
    void CircleColliderNode::shutdownImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->removeColliderNode(std::static_pointer_cast<CircleColliderNode>(shared_from_this()));
        ColliderNode::shutdownImpl();
    }

    void CircleColliderNode::updateImpl() {
        if (!mCollidedCallback) {
            return;
        }
        mCollidedNodes = rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->checkCollision(std::static_pointer_cast<CircleColliderNode>(shared_from_this()));
        ColliderNode::updateImpl();
    }
}
