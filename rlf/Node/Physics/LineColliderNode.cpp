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
        auto lineCollider = shared_from_this()->as<LineColliderNode>();
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->addColliderNode(lineCollider);
    }
    void LineColliderNode::shutdownImpl() {
        auto lineCollider = shared_from_this()->as<LineColliderNode>();
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->removeColliderNode(lineCollider);
    }
}
