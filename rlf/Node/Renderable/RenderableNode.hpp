#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class RenderableNode : public BaseNode {
    public:
        virtual void renderImpl();

        void initImpl() override;
        void shutdownImpl() override;
    };
}
