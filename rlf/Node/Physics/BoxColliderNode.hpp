#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf::Node {
    class BoxColliderNode : public ColliderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BoxColliderNode)

    protected:
        void setupImpl() override;
        void shutdownImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(ColliderNode)
        RLF_NODE_ACCESS_END

    private:
    };
}
