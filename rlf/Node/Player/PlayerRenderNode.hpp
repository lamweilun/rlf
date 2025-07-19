#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf {
    class PlayerRenderNode : public rlf::RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerRenderNode)

    protected:
        void renderImpl() override;

    private:
    };
}
