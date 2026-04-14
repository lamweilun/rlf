#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf
{
    class CircleColliderNode : public ColliderNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(CircleColliderNode)

    protected:
        void setupImpl() override;
        void shutdownImpl() override;

    private:
    };
}
