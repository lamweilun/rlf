#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf {
    class EnemyNode : public RigidbodyNode {
    public:
        EnemyNode();

        void renderImpl() override;
    };
}
