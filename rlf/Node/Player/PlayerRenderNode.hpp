#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class PlayerRenderNode : public rlf::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerRenderNode)

        void renderImpl() override;

    private:
    };
}
