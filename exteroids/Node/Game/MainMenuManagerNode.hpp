#pragma once

#include <Node/BaseNode.hpp>
#include <Node/UI/UIButtonNode.hpp>

namespace ext::Node {
    class MainMenuManagerNode : public rlf::Node::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(MainMenuManagerNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

    private:
        rlf::Node::UIButtonNode* mStartButton = nullptr;
        rlf::Node::UIButtonNode* mExitButton = nullptr;
    };
}
