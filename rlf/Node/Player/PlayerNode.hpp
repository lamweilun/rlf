#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    class PlayerNode : public rlf::RigidbodyNode {
    public:
        void initImpl() override;
        void updateImpl() override;

    private:
        void movementControls();
        void mouseControls();
    };
}
