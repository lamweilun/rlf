#include <Node/UI/UIButtonNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node {
    void UIButtonNode::renderImpl() {
#ifdef RLF_EDITOR
        mTextureInUse = mTexture;
        mTintToUse    = getTint();
#endif

        if (auto texture = mTextureInUse.getTexture()) {
            rlPushMatrix();
            rlTranslatef(static_cast<f32>(-texture->width) * 0.5f, static_cast<f32>(-texture->height) * 0.5f, 0.0f);
            DrawTexture(*texture, 0, 0, mTintToUse);
            rlPopMatrix();
        }
    }

    void UIButtonNode::updateImpl() {
        mTextureInUse = mTexture;
        mTintToUse    = getTint();

        // Get Current Active Camera
        Camera2D camera;
        if (auto activeCameraNode = rlf::Engine::getInstance().getSystem<System::RenderSystem>()->getActiveCameraNode()) {
            camera = activeCameraNode->getAsCamera2DUI();
        } else {
            camera.offset   = Vector2{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f};
            camera.target   = Vector2Zeros;
            camera.rotation = 0.0f;
            camera.zoom     = 1.0f;
        }

        // Get Global Button Rec
        auto const globalScale = getGlobalScale();
        auto const globalPos   = getGlobalPosition();
        Rectangle  buttonRec;
        buttonRec.width  = globalScale.x * static_cast<f32>(mTexture.getWidth());
        buttonRec.height = globalScale.y * static_cast<f32>(mTexture.getHeight());
        buttonRec.x      = globalPos.x - (buttonRec.width * 0.5f);
        buttonRec.y      = globalPos.y - (buttonRec.height * 0.5f);

        // Get Global Mouse Pos
        auto mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        // Check if mouse is clicking
        if (CheckCollisionPointRec(mouseWorldPos, buttonRec)) {
            if (!IsMouseButtonDown(0)) {
                mTextureInUse = mHoveredTexture;
                mTintToUse    = mHoveredTint;
            } else {
                mTextureInUse = mClickedTexture;
                mTintToUse    = mClickedTint;
            }
        }

        if (IsMouseButtonPressed(0) && mClickedCallback) {
            mClickedCallback(std::static_pointer_cast<UIButtonNode>(shared_from_this()));
        }
    }

    rlf::TextureResource const& UIButtonNode::getTexture() const {
        return mTexture;
    }
    void UIButtonNode::setTexture(rlf::TextureResource const& textureRsc) {
        mTexture = textureRsc;
    }

    rlf::TextureResource const& UIButtonNode::getHoveredTexture() const {
        return mHoveredTexture;
    }
    void UIButtonNode::setHoveredTexture(rlf::TextureResource const& textureRsc) {
        mHoveredTexture = textureRsc;
    }

    void UIButtonNode::setHoveredTint(Color const& tint) {
        mHoveredTint = tint;
    }
    Color const& UIButtonNode::getHoveredTint() const {
        return mHoveredTint;
    }

    rlf::TextureResource const& UIButtonNode::getClickedTexture() const {
        return mClickedTexture;
    }
    void UIButtonNode::setClickedTexture(rlf::TextureResource const& textureRsc) {
        mClickedTexture = textureRsc;
    }

    void UIButtonNode::setClickedTint(Color const& tint) {
        mClickedTint = tint;
    }
    Color const& UIButtonNode::getClickedTint() const {
        return mClickedTint;
    }

    void UIButtonNode::setClickedCallback(std::function<void(std::shared_ptr<UIButtonNode>)> callback) {
        mClickedCallback = callback;
    }
}
