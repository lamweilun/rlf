#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf::Node {
    class CircleColliderNode : public ColliderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(CircleColliderNode)

    protected:
        void setupImpl() override;
        void shutdownImpl() override;
        void updateImpl() override;

    private:
    };
}
