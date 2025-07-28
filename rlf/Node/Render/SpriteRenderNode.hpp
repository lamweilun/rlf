#pragma once

#include <Node/Render/RenderNode.hpp>

namespace rlf {
    class SpriteRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(SpriteRenderNode)

        void renderImpl() override;
        void shutdownImpl() override;

        void setTextureFromMemory(std::vector<u8> const& data, std::string_view filetype);

    private:
        Texture mTexture = {};
    };
}
