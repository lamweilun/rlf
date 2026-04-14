#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf
{
    class LineRenderNode : public RenderNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(LineRenderNode)

        void renderImpl() override;

        rlf::Vec2f const& getStartPoint() const;
        void              setStartPoint(rlf::Vec2f const& startPoint);

        rlf::Vec2f const& getEndPoint() const;
        void              setEndPoint(rlf::Vec2f const& endPoint);

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RenderNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Start Point", getStartPoint, setStartPoint)
        RLF_NODE_ACCESS_MEMBER_GET_SET("End Point", getEndPoint, setEndPoint)
        RLF_NODE_ACCESS_END

    private:
        rlf::Vec2f mStartPoint;
        rlf::Vec2f mEndPoint;
    };
}
