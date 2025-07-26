#include <Node/Render/SpriteRenderNode.hpp>

namespace rlf {
    void SpriteRenderNode::renderImpl() {
        DrawTexture(mTexture, 0, 0, getTint());
    }

    void SpriteRenderNode::shutdownImpl() {
        UnloadTexture(mTexture);
        RenderNode::shutdownImpl();
    }

    void SpriteRenderNode::setTextureFromMemory(std::vector<u8> const& data) {
        Image image = LoadImageFromMemory(".png", data.data(), static_cast<int>(data.size()));
        mTexture    = LoadTextureFromImage(image);
        UnloadImage(image);
    }
}
