#pragma once

#include <Node/BaseNode.hpp>
#include <Node/UI/UIButtonNode.hpp>

#include <Node/Player/PlayerNode.hpp>

namespace ext::Node {
    class GameManagerNode : public rlf::Node::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(GameManagerNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_END

    private:
        // Game UI
        std::shared_ptr<rlf::Node::BaseNode>   mGameUINode;
        std::shared_ptr<rlf::Node::UITextNode> mGameOverText;

        // Player
        std::shared_ptr<ark::Node::PlayerNode> mPlayerNode;

        std::shared_ptr<ark::Node::BallNode> mBallNode;
    };
}
