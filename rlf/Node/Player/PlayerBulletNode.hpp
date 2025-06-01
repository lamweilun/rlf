#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    class PlayerBulletNode : public rlf::RigidbodyNode {
    public:
        void update();
        void render();
    };
}
