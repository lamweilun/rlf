#include <Node/Physics/BoxColliderNode.hpp>

#include <System/PhysicsSystem.hpp>

namespace rlf {
    void BoxColliderNode::initImpl() {
        rlf::PhysicsSystem::getInstance().addColliderNode(std::static_pointer_cast<BoxColliderNode>(shared_from_this()));
    }
    void BoxColliderNode::shutdownImpl() {
        rlf::PhysicsSystem::getInstance().removeColliderNode(std::static_pointer_cast<BoxColliderNode>(shared_from_this()));
    }

    void BoxColliderNode::updateImpl() {
        mCollidedNodes = rlf::PhysicsSystem::getInstance().checkCollision(std::static_pointer_cast<BoxColliderNode>(shared_from_this()));
        ColliderNode::updateImpl();
    }

    BoundingBox BoxColliderNode::getBoundingBox() const {
        BoundingBox bb;
        auto const  globalPos   = getGlobalPosition();
        auto const  globalScale = getGlobalScale();

        bb.min = globalPos - globalScale;
        bb.max = globalPos + globalScale;

        return bb;
    }
}
