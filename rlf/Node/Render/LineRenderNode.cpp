#include <Node/Render/LineRenderNode.hpp>

namespace rlf
{
    void LineRenderNode::renderImpl()
    {
        DrawLineEx({mStartPoint.x, mStartPoint.y}, {mEndPoint.x, mEndPoint.y}, 1.0f, getTint());
        // DrawLine3D({mStartPoint.x, mStartPoint.y, 0.0f}, {mEndPoint.x, mEndPoint.y, 0.0f}, getTint());
    }

    rlf::Vec2f const& LineRenderNode::getStartPoint() const
    {
        return mStartPoint;
    }
    void LineRenderNode::setStartPoint(rlf::Vec2f const& startPoint)
    {
        mStartPoint = startPoint;
    }

    rlf::Vec2f const& LineRenderNode::getEndPoint() const
    {
        return mEndPoint;
    }
    void LineRenderNode::setEndPoint(rlf::Vec2f const& endPoint)
    {
        mEndPoint = endPoint;
    }
}
