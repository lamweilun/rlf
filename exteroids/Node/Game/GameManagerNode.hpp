#pragma once

#include <Node/BaseNode.hpp>
#include <Node/UI/UIButtonNode.hpp>

namespace ext::Node {
    class GameManagerNode : public rlf::Node::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(GameManagerNode)

    protected:
        void initImpl() override;

    private:
        void startGameButtonCallback();

        // Main Menu UI
        std::shared_ptr<BaseNode>
                                                 mMainMenuUINode;
        std::shared_ptr<rlf::Node::UIButtonNode> mStartButtonNode;
        std::shared_ptr<rlf::Node::UIButtonNode> mQuitButtonNode;

        // Game UI
        std::shared_ptr<rlf::Node::BaseNode> mGameUINode;
    };
}
