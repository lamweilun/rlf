#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf::Node {
    class LineRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(LineRenderNode)

        void renderImpl() override;

        Vector2 const& getStartPoint() const;
        void           setStartPoint(Vector2 const& startPoint);

        Vector2 const& getEndPoint() const;
        void           setEndPoint(Vector2 const& endPoint);

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RenderNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Start Point", getStartPoint, setStartPoint)
        RLF_NODE_ACCESS_MEMBER_GET_SET("End Point", getEndPoint, setEndPoint)
        RLF_NODE_ACCESS_END

    private:
        Vector2 mStartPoint;
        Vector2 mEndPoint;
    };
}
