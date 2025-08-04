#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf {
    class CircleColliderNode : public ColliderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(CircleColliderNode)

    protected:
        void initImpl() override;
        void shutdownImpl() override;
        void updateImpl() override;

    private:
    };
}
