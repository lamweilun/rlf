#pragma once

#include <Node/UI/UINode.hpp>
#include <Resource/TextureResource.hpp>

#include <Util/Range.hpp>

#include <functional>

namespace rlf::Node {
    class UISliderNode : public UINode {
    public:
        RLF_TYPE_REGISTER_QUICK(UISliderNode)

        rlf::Range<f32> const& getValueRange() const;
        void                   setValueRange(rlf::Range<f32> const& valueRange);

        f32  getCurrentValue() const;
        void setCurrentValue(f32 const currVal);

        void setCallback(std::function<void(f32)> callback);

    protected:
        void updateImpl() override;
        void renderImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(UINode)
        RLF_NODE_ACCESS_MEMBER("Background Texture", mBackgroundTexture)
        RLF_NODE_ACCESS_MEMBER("Button Texture", mButtonTexture)
        RLF_NODE_ACCESS_MEMBER("Hovered Button Texture", mHoveredButtonTexture)
        RLF_NODE_ACCESS_MEMBER("Clicked Button Texture", mClickedButtonTexture)
        RLF_NODE_ACCESS_MEMBER("Background Tint", mBackgroundTint)
        RLF_NODE_ACCESS_MEMBER("Hovered Button Tint", mHoveredButtonTint)
        RLF_NODE_ACCESS_MEMBER("Clicked Button Tint", mClickedButtonTint)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Value Range", getValueRange, setValueRange)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Current Value", getCurrentValue, setCurrentValue)
        RLF_NODE_ACCESS_END

    private:
        rlf::TextureResource mBackgroundTexture;
        rlf::TextureResource mButtonTexture;
        rlf::TextureResource mHoveredButtonTexture;
        rlf::TextureResource mClickedButtonTexture;

        Color mBackgroundTint    = WHITE;
        Color mHoveredButtonTint = WHITE;
        Color mClickedButtonTint = WHITE;

        rlf::Range<f32> mValueRange   = {0.0f, 1.0f};
        f32             mCurrentValue = 0.0f;

        // Runtime stuffs
        rlf::TextureResource     mButtonTextureInUse;
        Color                    mTintToUse;
        std::function<void(f32)> mCallback = nullptr;
    };
}
