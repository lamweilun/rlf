#include <Node/UI/UITextNode.hpp>

namespace rlf::Node {
    void UITextNode::renderImpl() {
        auto const spacing  = mAutoSpacing ? static_cast<float>(mFontSize) * 0.1f : mSpacing;
        auto const textSize = MeasureTextEx(GetFontDefault(), mText.c_str(), static_cast<float>(mFontSize), spacing);
        DrawTextEx(GetFontDefault(),
                   mText.c_str(),                  // Text
                   textSize * -0.5f,               // Origin
                   static_cast<float>(mFontSize),  // Font Size
                   spacing,                        // Spacing
                   getTint());
    }

    void UITextNode::setText(std::string const& text) {
        mText = text;
    }
    std::string const& UITextNode::getText() const {
        return mText;
    }

    void UITextNode::setFontSize(u32 const fontSize) {
        mFontSize = fontSize;
    }
    u32 UITextNode::getFontSize() const {
        return mFontSize;
    }
}
