#include <Node/Render/SpriteRenderNode.hpp>

namespace rlf
{
    void SpriteRenderNode::renderImpl()
    {
        if (auto texture = mTexture.getTexture())
        {
            auto const frameWidth  = static_cast<f32>(texture->width) / static_cast<f32>(mXFrames);
            auto const frameHeight = static_cast<f32>(texture->height) / static_cast<f32>(mYFrames);

            auto const x = frameWidth * static_cast<f32>(mFrameIndex % mXFrames);
            auto const y = frameHeight * (static_cast<f32>(mFrameIndex) / static_cast<f32>(mYFrames));

            Rectangle srcRec = {x, y, frameWidth, frameHeight};
            Rectangle dstRec = {-frameWidth * 0.5f, -frameHeight * 0.5f, frameWidth, frameHeight};
            DrawTexturePro(*texture, srcRec, dstRec, Vector2Zeros, 0.0f, getTint());
        }
    }

    rlf::TextureResource const& SpriteRenderNode::getTexture() const
    {
        return mTexture;
    }
    void SpriteRenderNode::setTexture(rlf::TextureResource const& textureRsc)
    {
        mTexture = textureRsc;
    }
}
