#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf {
    class EnemyRenderNode : public rlf::RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(EnemyRenderNode)

    protected:
        void initImpl() override;
        void renderImpl() override;

    private:
    };
}
