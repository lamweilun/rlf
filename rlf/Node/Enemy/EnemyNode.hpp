#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    class EnemyNode : public RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(EnemyNode)

        void initImpl() override;
    };
}
