#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf::Node {
    class PlayerRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerRenderNode)

        void renderImpl() override;

    private:
    };
}
