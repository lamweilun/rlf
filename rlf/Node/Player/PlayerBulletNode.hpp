#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    class PlayerBulletNode : public rlf::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerBulletNode)

        void initImpl() override;
        void updateImpl() override;
    };
}
