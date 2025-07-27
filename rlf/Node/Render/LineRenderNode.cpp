#include <Node/Render/LineRenderNode.hpp>

namespace rlf {
    void LineRenderNode::renderImpl() {
        DrawLine3D(mStartPoint, mEndPoint, getTint());
    }

    Vector3 const& LineRenderNode::getStartPoint() const {
        return mStartPoint;
    }
    void LineRenderNode::setStartPoint(Vector3 const& startPoint) {
        mStartPoint = startPoint;
    }

    Vector3 const& LineRenderNode::getEndPoint() const {
        return mEndPoint;
    }
    void LineRenderNode::setEndPoint(Vector3 const& endPoint) {
        mEndPoint = endPoint;
    }
}
