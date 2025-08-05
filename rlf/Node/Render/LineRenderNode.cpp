#include <Node/Render/LineRenderNode.hpp>

namespace rlf::Node {
    void LineRenderNode::renderImpl() {
        DrawLine3D(Vector3{mStartPoint.x, mStartPoint.y, 0.0f}, Vector3{mEndPoint.x, mEndPoint.y, 0.0f}, getTint());
    }

    Vector2 const& LineRenderNode::getStartPoint() const {
        return mStartPoint;
    }
    void LineRenderNode::setStartPoint(Vector2 const& startPoint) {
        mStartPoint = startPoint;
    }

    Vector2 const& LineRenderNode::getEndPoint() const {
        return mEndPoint;
    }
    void LineRenderNode::setEndPoint(Vector2 const& endPoint) {
        mEndPoint = endPoint;
    }
}
