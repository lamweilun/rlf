#include <Node/UI/UISliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node
{
    void UISliderNode::renderImpl()
    {
#ifdef RLF_EDITOR
        mButtonTextureInUse = mButtonTexture;
        mTintToUse          = getTint();
#endif

        if (auto backGroundTexture = mBackgroundTexture.getTexture())
        {
            DrawTexture(*backGroundTexture, -backGroundTexture->width / 2, -backGroundTexture->height / 2, mBackgroundTint);
        }

        if (auto buttonTexture = mButtonTextureInUse.getTexture())
        {
            if (auto backGroundTexture = mBackgroundTexture.getTexture())
            {
                auto const ratio       = mCurrentValue / (mValueRange.getMax() - mValueRange.getMin());
                auto const valueOffset = (static_cast<f32>(backGroundTexture->width) * ratio);
                auto const buttonX     = static_cast<f32>((-buttonTexture->width / 2)) - static_cast<f32>((backGroundTexture->width / 2)) + valueOffset;
                DrawTexture(*buttonTexture, static_cast<i32>(buttonX), -buttonTexture->height / 2, mTintToUse);
            }
        }
    }

    void UISliderNode::updateImpl()
    {
        mButtonTextureInUse = mButtonTexture;
        mTintToUse          = getTint();

        // Get Global Background Rec
        Rectangle backgroundRec = {};
        {
            auto const globalScale = getGlobalScale();
            auto const globalPos   = getGlobalPosition();
            backgroundRec.width    = globalScale.x;
            backgroundRec.height   = globalScale.y;
            if (mBackgroundTexture.getTexture())
            {
                backgroundRec.width *= static_cast<f32>(mBackgroundTexture.getWidth());
                backgroundRec.height *= static_cast<f32>(mBackgroundTexture.getHeight());
            }
            backgroundRec.x = globalPos.x - (backgroundRec.width * 0.5f);
            backgroundRec.y = globalPos.y - (backgroundRec.height * 0.5f);
        }

        // Get Global Button Rec
        Rectangle buttonRec = {};
        {
            auto const globalScale = getGlobalScale();
            auto const globalPos   = getGlobalPosition();
            buttonRec.width        = globalScale.x;
            buttonRec.height       = globalScale.y;
            if (auto buttonTexture = mButtonTexture.getTexture())
            {
                buttonRec.width *= static_cast<f32>(buttonTexture->width);
                buttonRec.height *= static_cast<f32>(buttonTexture->height);
            }
            buttonRec.x = globalPos.x;
            buttonRec.y = globalPos.y - (buttonRec.height * 0.5f);

            auto const ratio = mCurrentValue / (mValueRange.getMax() - mValueRange.getMin());
            if (auto backGroundTexture = mBackgroundTexture.getTexture())
            {
                auto const valueOffset = (static_cast<f32>(backGroundTexture->width) * ratio);
                if (auto buttonTexture = mButtonTexture.getTexture())
                {
                    auto const buttonX = static_cast<f32>((-buttonTexture->width / 2)) - static_cast<f32>((backGroundTexture->width / 2)) + valueOffset;
                    buttonRec.x += buttonX;
                }
            }
        }

        // Get Global Mouse Pos
        auto mouseWorldPos = rlf::Engine::getInstance().getSystem<System::RenderSystem>()->getUIMousePosition();

        // Check if mouse is clicking
        auto mIsHoveringButton = CheckCollisionPointRec({mouseWorldPos.x, mouseWorldPos.y}, buttonRec);
        auto mIsDown           = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        if (mIsHoveringButton)
        {
            if (!mIsDown)
            {
                mButtonTextureInUse = mHoveredButtonTexture;
                mTintToUse          = mHoveredButtonTint;
            }
            else
            {
                mButtonTextureInUse = mClickedButtonTexture;
                mTintToUse          = mClickedButtonTint;

                auto const ratio = (mouseWorldPos.x - backgroundRec.x) / backgroundRec.width;
                setCurrentValue((mValueRange.getMax() - mValueRange.getMin()) * ratio);
                if (mCallback)
                {
                    mCallback(getCurrentValue());
                }
            }
        }
        else
        {
            bool const isHoveringBackground = CheckCollisionPointRec({mouseWorldPos.x, mouseWorldPos.y}, backgroundRec);
            if (isHoveringBackground && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                auto const ratio = (mouseWorldPos.x - backgroundRec.x) / backgroundRec.width;
                setCurrentValue((mValueRange.getMax() - mValueRange.getMin()) * ratio);
                if (mCallback)
                {
                    mCallback(getCurrentValue());
                }
            }
        }
    }

    rlf::Range<f32> const& UISliderNode::getValueRange() const
    {
        return mValueRange;
    }
    void UISliderNode::setValueRange(rlf::Range<f32> const& valueRange)
    {
        mValueRange   = valueRange;
        mCurrentValue = std::clamp(mCurrentValue, mValueRange.getMin(), mValueRange.getMax());
    }

    f32 UISliderNode::getCurrentValue() const
    {
        return mCurrentValue;
    }
    void UISliderNode::setCurrentValue(f32 const currVal)
    {
        mCurrentValue = currVal;
        mCurrentValue = std::clamp(mCurrentValue, mValueRange.getMin(), mValueRange.getMax());
    }

    void UISliderNode::setCallback(std::function<void(f32)> callback)
    {
        mCallback = callback;
    }
}
