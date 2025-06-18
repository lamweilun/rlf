#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class EnemyRenderNode : public rlf::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(EnemyRenderNode)

        void renderImpl() override;

    private:
    };
}
