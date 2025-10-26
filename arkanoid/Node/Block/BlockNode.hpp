#pragma once

#include <Node/Physics/RigidbodyNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>

namespace ark::Node {
    class BlockNode : public rlf::Node::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BlockNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RigidbodyNode)
        RLF_NODE_ACCESS_END

    private:
        std::shared_ptr<rlf::Node::BoxColliderNode> collider;
    };
}
