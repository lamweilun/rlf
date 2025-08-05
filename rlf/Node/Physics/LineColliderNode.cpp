#include <Node/Physics/LineColliderNode.hpp>

#include <System/Physics/PhysicsSystem.hpp>

namespace rlf::Node {

    Vector2 const& LineColliderNode::getStartPoint() const {
        return mStartPoint;
    }
    void LineColliderNode::setStartPoint(Vector2 const& startPoint) {
        mStartPoint = startPoint;
#ifdef RLF_DEBUG
        if (!mRenderNode) {
            mRenderNode = getOrAddFirstChildOfType<LineRenderNode>();
        }
        mRenderNode->setStartPoint(startPoint);
#endif
    }

    Vector2 const& LineColliderNode::getEndPoint() const {
        return mEndPoint;
    }
    void LineColliderNode::setEndPoint(Vector2 const& endPoint) {
        mEndPoint = endPoint;
#ifdef RLF_DEBUG
        if (!mRenderNode) {
            mRenderNode = getOrAddFirstChildOfType<LineRenderNode>();
        }
        mRenderNode->setEndPoint(endPoint);
#endif
    }

    void LineColliderNode::initImpl() {
        rlf::System::PhysicsSystem::getInstance().addColliderNode(std::static_pointer_cast<LineColliderNode>(shared_from_this()));

#ifdef RLF_DEBUG
        if (!mRenderNode) {
            mRenderNode = getOrAddFirstChildOfType<LineRenderNode>();
        }
        mRenderNode->setStartPoint(getStartPoint());
        mRenderNode->setEndPoint(getEndPoint());
        mRenderNode->setLayer(1);
        mRenderNode->setTint(GREEN);
#endif
    }
    void LineColliderNode::shutdownImpl() {
        rlf::System::PhysicsSystem::getInstance().removeColliderNode(std::static_pointer_cast<LineColliderNode>(shared_from_this()));
        ColliderNode::shutdownImpl();
    }

    void LineColliderNode::updateImpl() {
        if (!mCollidedCallback) {
            return;
        }
        mCollidedNodes = rlf::System::PhysicsSystem::getInstance().checkCollision(std::static_pointer_cast<LineColliderNode>(shared_from_this()));
        ColliderNode::updateImpl();
    }
}
