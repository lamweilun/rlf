#include <Node/Render/SpriteRenderNode.hpp>

namespace rlf::Node {
    void SpriteRenderNode::renderImpl() {
        DrawTexture(mTexture, 0, 0, getTint());
    }

    void SpriteRenderNode::shutdownImpl() {
        if (IsTextureValid(mTexture)) {
            UnloadTexture(mTexture);
        }
        mTexture = {};
        RenderNode::shutdownImpl();
    }

    void SpriteRenderNode::setTextureFromMemory(std::vector<u8> const& data, std::string_view filetype) {
        // Attempts to load texture
        Image image = LoadImageFromMemory(filetype.data(), data.data(), static_cast<int>(data.size()));
        if (!IsImageValid(image)) {
            return;
        }
        auto newTexture = LoadTextureFromImage(image);
        UnloadImage(image);
        if (!IsTextureValid(newTexture)) {
            return;
        }

        // Unload old texture if there's any and set new texture
        if (IsTextureValid(mTexture)) {
            UnloadTexture(mTexture);
        }
        mTexture = newTexture;
    }
}
