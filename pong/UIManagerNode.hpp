#pragma once

#include <Node/BaseNode.hpp>

namespace rlf::Node {
    class UIManagerNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(UIManagerNode)

        void initImpl() override;

    private:
    };
}
