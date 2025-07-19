#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    class PlayerNode : public rlf::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

    private:
        void movementControls();
        void attackControls();
    };
}
