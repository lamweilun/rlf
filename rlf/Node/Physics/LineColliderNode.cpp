#include <Node/Physics/LineColliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

namespace rlf::Node {

    Vector2 const& LineColliderNode::getStartPoint() const {
        return mStartPoint;
    }
    void LineColliderNode::setStartPoint(Vector2 const& startPoint) {
        mStartPoint = startPoint;
    }

    Vector2 const& LineColliderNode::getEndPoint() const {
        return mEndPoint;
    }
    void LineColliderNode::setEndPoint(Vector2 const& endPoint) {
        mEndPoint = endPoint;
    }

    void LineColliderNode::setupImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->addColliderNode(std::static_pointer_cast<LineColliderNode>(shared_from_this()));
    }
    void LineColliderNode::shutdownImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->removeColliderNode(std::static_pointer_cast<LineColliderNode>(shared_from_this()));
        ColliderNode::shutdownImpl();
    }

    void LineColliderNode::updateImpl() {
        if (!mCollidedCallback) {
            return;
        }
        mCollidedNodes = rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->checkCollision(std::static_pointer_cast<LineColliderNode>(shared_from_this()));
        ColliderNode::updateImpl();
    }
}
