#include <Node/UI/UISpriteNode.hpp>

namespace rlf
{

    void UISpriteNode::renderImpl()
    {
        if (auto texture = mTexture.getTexture())
        {
            auto const frameWidth  = static_cast<f32>(texture->width) / static_cast<f32>(mXFrames);
            auto const frameHeight = static_cast<f32>(texture->height) / static_cast<f32>(mYFrames);
            Rectangle  srcRec      = {frameWidth * static_cast<f32>(mFrameIndex % mXFrames), frameHeight * static_cast<f32>(mFrameIndex / mYFrames),
                                      frameWidth, frameHeight};
            Rectangle  dstRec      = {-frameWidth * 0.5f, -frameHeight * 0.5f, frameWidth, frameHeight};
            DrawTexturePro(*texture, srcRec, dstRec, Vector2Zeros, 0.0f, getTint());
        }
    }

    rlf::TextureResource const& UISpriteNode::getTexture() const
    {
        return mTexture;
    }
    void UISpriteNode::setTexture(rlf::TextureResource const& textureRsc)
    {
        mTexture = textureRsc;
    }
}
