#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf::Node {
    class UINode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(UINode)

        void setLayer(i32 const layer) override;

    protected:
        void setActiveImpl(bool const selfActive) override;
        void initImpl() override;
        void shutdownImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RenderNode)
        RLF_NODE_ACCESS_END

    private:
    };
}
