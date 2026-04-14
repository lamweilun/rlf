#pragma once

#include <Node/Render/RenderNode.hpp>

#include <Resource/TextureResource.hpp>

namespace rlf
{
    class SpriteRenderNode : public RenderNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(SpriteRenderNode)

        void renderImpl() override;

        rlf::TextureResource const& getTexture() const;
        void                        setTexture(rlf::TextureResource const& textureRsc);

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RenderNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Texture", getTexture, setTexture)
        RLF_NODE_ACCESS_MEMBER("X Frames", mXFrames)
        RLF_NODE_ACCESS_MEMBER("Y Frames", mYFrames)
        RLF_NODE_ACCESS_MEMBER("Frame Index", mFrameIndex)
        RLF_NODE_ACCESS_END

    private:
        rlf::TextureResource mTexture;
        u32                  mXFrames    = 1;
        u32                  mYFrames    = 1;
        u32                  mFrameIndex = 0;
    };
}
