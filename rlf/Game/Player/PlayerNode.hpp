#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    class PlayerNode : public RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerNode)

        void initImpl() override;

    protected:
        void updateImpl() override;

    private:
    };
}
