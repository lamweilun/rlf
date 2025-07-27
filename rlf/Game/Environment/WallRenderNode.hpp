#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf {
    class WallRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(WallRenderNode)

        void renderImpl() override;

    private:
    };
}
