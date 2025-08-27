#pragma once

#include <Node/UI/UINode.hpp>

namespace rlf::Node {
    class UITextNode : public UINode {
    public:
        RLF_TYPE_REGISTER_QUICK(UITextNode)

        void renderImpl() override;

        std::string const& getText() const;
        void               setText(std::string const& text);

        FontResource const& getFontResource() const;
        void                setFontResource(FontResource const&);

        u32  getFontSize() const;
        void setFontSize(u32 const fontSize);

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(UINode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Font", getFontResource, setFontResource)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Text", getText, setText)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Font Size", getFontSize, setFontSize)
        RLF_NODE_ACCESS_MEMBER("Spacing", mSpacing);
        RLF_NODE_ACCESS_MEMBER("Auto Spacing", mAutoSpacing);
        RLF_NODE_ACCESS_END

    private:
        FontResource mFont;
        std::string  mText        = {};
        u32          mFontSize    = 20;
        f32          mSpacing     = 0.0f;
        bool         mAutoSpacing = true;
    };
}
