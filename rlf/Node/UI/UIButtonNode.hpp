#pragma once

#include <Node/UI/UINode.hpp>
#include <Resource/TextureResource.hpp>

#include <functional>

namespace rlf::Node {
    class UIButtonNode : public UINode {
    public:
        RLF_TYPE_REGISTER_QUICK(UIButtonNode)

        void updateImpl() override;
        void renderImpl() override;

        rlf::TextureResource const& getTexture() const;
        void                        setTexture(rlf::TextureResource const& textureRsc);

        rlf::TextureResource const& getHoveredTexture() const;
        void                        setHoveredTexture(rlf::TextureResource const& textureRsc);

        Color const& getHoveredTint() const;
        void         setHoveredTint(Color const& tint);

        rlf::TextureResource const& getClickedTexture() const;
        void                        setClickedTexture(rlf::TextureResource const& textureRsc);

        Color const& getClickedTint() const;
        void         setClickedTint(Color const& tint);

        void setClickedCallback(std::function<void(std::shared_ptr<UIButtonNode>)> callback);

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(UINode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Texture", getTexture, setTexture)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Hovered Texture", getHoveredTexture, setHoveredTexture)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Hovered Tint", getHoveredTint, setHoveredTint)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Clicked Texture", getClickedTexture, setClickedTexture)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Clicked Tint", getClickedTint, setClickedTint)
        RLF_NODE_ACCESS_END

    private:
        rlf::TextureResource mTexture;
        rlf::TextureResource mHoveredTexture;
        rlf::TextureResource mClickedTexture;
        Color                mHoveredTint = WHITE;
        Color                mClickedTint = WHITE;

        rlf::TextureResource mTextureInUse;
        Color                mTintToUse = WHITE;

        std::function<void(std::shared_ptr<UIButtonNode>)> mClickedCallback;
    };
}
