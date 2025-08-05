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

    private:
        Vector2 mStartPoint;
        Vector2 mEndPoint;
    };
}
