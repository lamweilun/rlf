#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf::Node {
    class WallRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(WallRenderNode)

        void renderImpl() override;

    private:
    };
}
