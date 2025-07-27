#include <Node/Physics/LineColliderNode.hpp>

#include <System/PhysicsSystem.hpp>

namespace rlf {

    Vector3 const& LineColliderNode::getStartPoint() const {
        return mStartPoint;
    }
    void LineColliderNode::setStartPoint(Vector3 const& startPoint) {
        mStartPoint = startPoint;
#ifdef RLF_DEBUG
        if (!mRenderNode) {
            mRenderNode = getOrAddFirstChildOfType<LineRenderNode>();
        }
        mRenderNode->setStartPoint(startPoint);
#endif
    }

    Vector3 const& LineColliderNode::getEndPoint() const {
        return mEndPoint;
    }
    void LineColliderNode::setEndPoint(Vector3 const& endPoint) {
        mEndPoint = endPoint;
#ifdef RLF_DEBUG
        if (!mRenderNode) {
            mRenderNode = getOrAddFirstChildOfType<LineRenderNode>();
        }
        mRenderNode->setEndPoint(endPoint);
#endif
    }

    void LineColliderNode::initImpl() {
        rlf::PhysicsSystem::getInstance().addColliderNode(std::static_pointer_cast<LineColliderNode>(shared_from_this()));

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
        rlf::PhysicsSystem::getInstance().removeColliderNode(std::static_pointer_cast<LineColliderNode>(shared_from_this()));
    }

    void LineColliderNode::updateImpl() {
        if (!mCollidedCallback) {
            return;
        }
        mCollidedNodes = rlf::PhysicsSystem::getInstance().checkCollision(std::static_pointer_cast<LineColliderNode>(shared_from_this()));
        ColliderNode::updateImpl();
    }
}
