#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class ColliderNode : public BaseNode {
    public:
        void initImpl() override;
        void shutdownImpl() override;
    };
}
