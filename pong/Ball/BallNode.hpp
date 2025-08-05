#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf::Node {
    class BallNode : public RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BallNode)

        void initImpl() override;

    private:
    };
}
