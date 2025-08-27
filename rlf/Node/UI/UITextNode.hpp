#pragma once

#include <Node/UI/UINode.hpp>

namespace rlf::Node {
    class UITextNode : public UINode {
    public:
        RLF_TYPE_REGISTER_QUICK(UITextNode)

        void renderImpl() override;

        void               setText(std::string const& text);
        std::string const& getText() const;

        void setFontSize(u32 const fontSize);
        u32  getFontSize() const;

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(UINode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Text", getText, setText)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Font Size", getFontSize, setFontSize)
        RLF_NODE_ACCESS_MEMBER("Spacing", mSpacing);
        RLF_NODE_ACCESS_MEMBER("Auto Spacing", mAutoSpacing);
        RLF_NODE_ACCESS_END

    private:
        std::string mText        = {};
        u32         mFontSize    = 20;
        f32         mSpacing     = 0.0f;
        bool        mAutoSpacing = true;
    };
}
