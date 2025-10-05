#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace ext::Node {
    class EnemyNode : public rlf::Node::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(EnemyNode)

        u32  getHP() const;
        void setHP(u32 const hp);

    protected:
        void initImpl() override;
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RigidbodyNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Enemy HP", getHP, setHP)
        RLF_NODE_ACCESS_END

    private:
        u32 mHP = 1;
    };
}
