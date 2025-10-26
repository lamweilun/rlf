#pragma once

#include <Node/Physics/CircleColliderNode.hpp>

#include <Node/Physics/RigidbodyNode.hpp>
#include <Node/UI/UITextNode.hpp>

namespace ark::Node {
    class BallNode : public rlf::Node::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BallNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RigidbodyNode)
        RLF_NODE_ACCESS_END

    private:
        std::shared_ptr<rlf::Node::CircleColliderNode> collider;
        std::shared_ptr<rlf::Node::UITextNode>         mScoreText;
        int                                            score = 0;
    };
}
