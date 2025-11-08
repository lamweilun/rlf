#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf::Node
{
    class CircleRenderNode : public RenderNode
    {
    public:
        RLF_TYPE_REGISTER_QUICK(CircleRenderNode)

        void renderImpl() override;

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RenderNode)
        RLF_NODE_ACCESS_END

    private:
    };
}
