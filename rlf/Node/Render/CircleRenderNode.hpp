#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf {
    class CircleRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(CircleRenderNode)

        void renderImpl() override;

    private:
    };
}
