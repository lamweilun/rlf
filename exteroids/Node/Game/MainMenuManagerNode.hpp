#pragma once

#include <Node/BaseNode.hpp>
#include <Node/UI/UIButtonNode.hpp>

namespace ext
{
    class MainMenuManagerNode : public rlf::BaseNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(MainMenuManagerNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

    private:
        std::shared_ptr<rlf::UIButtonNode> mStartButton;
        std::shared_ptr<rlf::UIButtonNode> mExitButton;
    };
}
