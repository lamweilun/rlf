#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf::Node {
    class PlayerNode : public RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerNode)

    protected:
        void updateImpl() override;

    private:
    };
}
