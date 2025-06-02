#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    class PlayerNode : public rlf::RigidbodyNode {
    public:
        PlayerNode();

        void updateImpl() override;
        void renderImpl() override;

    private:
        void movementControls();
        void mouseControls();
    };
}
