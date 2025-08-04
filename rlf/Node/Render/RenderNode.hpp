#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class RenderNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(RenderNode)

        virtual void renderImpl();

        void         setTint(Color const& tint);
        Color const& getTint() const;

        void setLayer(i32 const layer);
        i32  getLayer() const;

    protected:
        void setActiveImpl(bool const selfActive) override;
        void initImpl() override;
        void shutdownImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("tint", getTint, setTint)
        RLF_NODE_ACCESS_MEMBER_GET_SET("layer", getLayer, setLayer)
        RLF_NODE_ACCESS_END

    private:
        Color mTint  = WHITE;
        i32   mLayer = 0;
    };
}
