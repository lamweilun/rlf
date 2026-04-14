#include <Node/UI/UITextNode.hpp>

namespace rlf
{
    void UITextNode::renderImpl()
    {
        auto const spacing  = mAutoSpacing ? static_cast<float>(mFontSize) * 0.1f : mSpacing;
        auto const textSize = MeasureTextEx(GetFontDefault(), mText.c_str(), static_cast<float>(mFontSize), spacing);
        Font       font     = GetFontDefault();
        if (auto fontRsc = mFont.getFont())
        {
            font = *fontRsc;
        }
        DrawTextEx(font,
                   mText.c_str(),                  // Text
                   textSize * -0.5f,               // Origin
                   static_cast<float>(mFontSize),  // Font Size
                   spacing,                        // Spacing
                   getTint());
    }

    FontResource const& UITextNode::getFontResource() const
    {
        return mFont;
    }
    void UITextNode::setFontResource(FontResource const& font)
    {
        mFont = font;
    }

    void UITextNode::setText(std::string const& text)
    {
        mText = text;
    }
    std::string const& UITextNode::getText() const
    {
        return mText;
    }

    void UITextNode::setFontSize(u32 const fontSize)
    {
        mFontSize = fontSize;
    }
    u32 UITextNode::getFontSize() const
    {
        return mFontSize;
    }
}
