#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace ext::Node {
    class PlayerBulletNode : public rlf::Node::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerBulletNode)

    protected:
        void updateImpl() override;

    private:
    };
}
