#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf::Node {
    class BallRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BallRenderNode)

        void renderImpl() override;

    private:
    };
}
