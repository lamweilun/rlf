#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf {
    class SphereRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(SphereRenderNode)

        void renderImpl() override;

    private:
    };
}
