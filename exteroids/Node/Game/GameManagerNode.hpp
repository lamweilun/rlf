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

    private:
        // Game UI
        std::shared_ptr<rlf::Node::BaseNode> mGameUINode;

        // Player
        std::shared_ptr<ext::Node::PlayerNode> mPlayerNode;
    };
}
