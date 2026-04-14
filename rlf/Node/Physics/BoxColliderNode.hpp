#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf
{
    class BoxColliderNode : public ColliderNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(BoxColliderNode)

    protected:
        void setupImpl() override;
        void shutdownImpl() override;

    private:
    };
}
