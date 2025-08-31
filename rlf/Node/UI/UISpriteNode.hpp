#pragma once

#include <Node/UI/UINode.hpp>
#include <Resource/TextureResource.hpp>

namespace rlf::Node {
    class UISpriteNode : public UINode {
    public:
        RLF_TYPE_REGISTER_QUICK(UISpriteNode)

        void renderImpl() override;

        rlf::TextureResource const& getTexture() const;
        void                        setTexture(rlf::TextureResource const& textureRsc);

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(UINode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Texture", getTexture, setTexture)
        RLF_NODE_ACCESS_END

    private:
        rlf::TextureResource mTexture;
    };
}
