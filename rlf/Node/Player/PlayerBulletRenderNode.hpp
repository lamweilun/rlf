#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf {
    class PlayerBulletRenderNode : public rlf::RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerBulletRenderNode)

    protected:
        void initImpl() override;
        void renderImpl() override;

    private:
    };
}
