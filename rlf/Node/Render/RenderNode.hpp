#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class RenderNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(RenderNode)

        virtual void renderImpl();

        void         setTint(Color const& tint);
        Color const& getTint() const;

        void setLayer(int const layer);
        int  getLayer() const;

    protected:
        void setActiveImpl(bool const selfActive) override;
        void initImpl() override;
        void shutdownImpl() override;

    private:
        Color mTint  = WHITE;
        int   mLayer = 0;
    };
}
