#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    class PlayerNode : public rlf::RigidbodyNode {
    public:
        PlayerNode();

        void update();
        void render();

    private:
        void movementControls();
        void mouseControls();
    };
}
