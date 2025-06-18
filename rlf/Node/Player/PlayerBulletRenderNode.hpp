#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class PlayerBulletRenderNode : public rlf::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerBulletRenderNode)

        void renderImpl() override;

    private:
    };
}
