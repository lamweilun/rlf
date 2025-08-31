#pragma once

#include <Node/Render/RenderNode.hpp>

#include <Resource/TextureResource.hpp>

namespace rlf::Node {
    class SpriteRenderNode : public RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(SpriteRenderNode)

        void renderImpl() override;

        rlf::TextureResource const& getTexture() const;
        void                        setTexture(rlf::TextureResource const& textureRsc);

    protected:
        void shutdownImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RenderNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Texture", getTexture, setTexture)
        RLF_NODE_ACCESS_END

    private:
        rlf::TextureResource mTexture;
    };
}
