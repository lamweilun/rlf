#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf {
    class LineRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(LineRenderNode)

        void renderImpl() override;

        Vector3 const& getStartPoint() const;
        void           setStartPoint(Vector3 const& startPoint);

        Vector3 const& getEndPoint() const;
        void           setEndPoint(Vector3 const& endPoint);

    private:
        Vector3 mStartPoint;
        Vector3 mEndPoint;
    };
}
