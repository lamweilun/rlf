#include <Node/Render/SpriteRenderNode.hpp>

namespace rlf::Node {
    void SpriteRenderNode::renderImpl() {
        if (auto texture = mTexture.getTexture().lock()) {
            rlPushMatrix();
            rlTranslatef(static_cast<f32>(-texture->width) * 0.5f, static_cast<f32>(-texture->height) * 0.5f, 0.0f);
            DrawTexture(*texture, 0, 0, getTint());
            rlPopMatrix();
        }
    }

    void SpriteRenderNode::setTexture(rlf::TextureResource const& textureRsc) {
        mTexture = textureRsc;
    }
    rlf::TextureResource const& SpriteRenderNode::getTexture() const {
        return mTexture;
    }
}
