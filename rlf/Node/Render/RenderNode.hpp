#pragma once

#include <Node/BaseNode.hpp>

namespace rlf
{
    class RenderNode : public BaseNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(RenderNode)

        virtual void renderImpl();

        i32          getLayer() const;
        virtual void setLayer(i32 const layer);

        Color const& getTint() const;
        void         setTint(Color const& tint);

        bool getBloom() const;
        void setBloom(bool const bloom);

    protected:
        void setActiveImpl(bool const selfActive) override;
        void setupImpl() override;
        void shutdownImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("layer", getLayer, setLayer)
        RLF_NODE_ACCESS_MEMBER_GET_SET("tint", getTint, setTint)
        RLF_NODE_ACCESS_MEMBER_GET_SET("bloom", getBloom, setBloom)
        RLF_NODE_ACCESS_END

    private:
        Color mTint  = WHITE;
        bool  mBloom = false;

    protected:
        i32 mLayer = 0;
    };
}
