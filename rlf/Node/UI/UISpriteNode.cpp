#include <Node/UI/UISpriteNode.hpp>

namespace rlf::Node {

    void UISpriteNode::renderImpl() {
        if (auto texture = mTexture.getTexture()) {
            rlPushMatrix();
            rlTranslatef(static_cast<f32>(-texture->width) * 0.5f, static_cast<f32>(-texture->height) * 0.5f, 0.0f);
            DrawTexture(*texture, 0, 0, getTint());
            rlPopMatrix();
        }
    }

    rlf::TextureResource const& UISpriteNode::getTexture() const {
        return mTexture;
    }
    void UISpriteNode::setTexture(rlf::TextureResource const& textureRsc) {
        mTexture = textureRsc;
    }
}
