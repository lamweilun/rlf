#include <Node/UI/UIButtonNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node
{
    void UIButtonNode::renderImpl()
    {
#ifdef RLF_EDITOR
        mTextureInUse = mTexture;
        mTintToUse    = getTint();
#endif

        if (auto texture = mTextureInUse.getTexture())
        {
            rlPushMatrix();
            rlTranslatef(static_cast<f32>(-texture->width) * 0.5f, static_cast<f32>(-texture->height) * 0.5f, 0.0f);
            DrawTexture(*texture, 0, 0, mTintToUse);
            rlPopMatrix();
        }

        if (mUseBorder)
        {
            Rectangle rec = {};
            rec.x         = -0.5f;
            rec.y         = -0.5f;
            rec.width     = 1.0f;
            rec.height    = 1.0f;
            DrawRectangleLinesEx(rec, mBorderThickness, mTintToUse);
        }
    }

    void UIButtonNode::preUpdateImpl()
    {
        // Trigger callback based on last frame behaviour
        if (mIsHovering && mIsDown)
        {
            if (mClickedCallback && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                mClickedCallback();
            }
        }
    }

    void UIButtonNode::updateImpl()
    {
        mTextureInUse = mTexture;
        mTintToUse    = getTint();
        mIsHovering   = false;
        mIsDown       = false;

        // Get Global Button Rec
        auto const globalScale = getGlobalScale();
        auto const globalPos   = getGlobalPosition();
        Rectangle  buttonRec;
        buttonRec.width  = globalScale.x;
        buttonRec.height = globalScale.y;
        if (mTexture.getTexture())
        {
            buttonRec.width *= static_cast<f32>(mTexture.getWidth());
            buttonRec.height *= static_cast<f32>(mTexture.getHeight());
        }
        buttonRec.x = globalPos.x - (buttonRec.width * 0.5f);
        buttonRec.y = globalPos.y - (buttonRec.height * 0.5f);

        // Get Global Mouse Pos
        auto mouseWorldPos = rlf::Engine::getInstance().getSystem<RenderSystem>()->getUIMousePosition();

        // Check if mouse is clicking
        mIsHovering = CheckCollisionPointRec({mouseWorldPos.x, mouseWorldPos.y}, buttonRec);
        mIsDown     = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        if (mIsHovering)
        {
            if (!mIsDown)
            {
                mTextureInUse = mHoveredTexture;
                mTintToUse    = mHoveredTint;
            }
            else
            {
                mTextureInUse = mClickedTexture;
                mTintToUse    = mClickedTint;
            }
        }
    }

    rlf::TextureResource const& UIButtonNode::getTexture() const
    {
        return mTexture;
    }
    void UIButtonNode::setTexture(rlf::TextureResource const& textureRsc)
    {
        mTexture = textureRsc;
    }

    rlf::TextureResource const& UIButtonNode::getHoveredTexture() const
    {
        return mHoveredTexture;
    }
    void UIButtonNode::setHoveredTexture(rlf::TextureResource const& textureRsc)
    {
        mHoveredTexture = textureRsc;
    }

    rlf::TextureResource const& UIButtonNode::getClickedTexture() const
    {
        return mClickedTexture;
    }
    void UIButtonNode::setClickedTexture(rlf::TextureResource const& textureRsc)
    {
        mClickedTexture = textureRsc;
    }

    Color const& UIButtonNode::getHoveredTint() const
    {
        return mHoveredTint;
    }
    void UIButtonNode::setHoveredTint(Color const& tint)
    {
        mHoveredTint = tint;
    }

    Color const& UIButtonNode::getClickedTint() const
    {
        return mClickedTint;
    }
    void UIButtonNode::setClickedTint(Color const& tint)
    {
        mClickedTint = tint;
    }

    void UIButtonNode::setClickedCallback(std::function<void()> callback)
    {
        mClickedCallback = callback;
    }
}
