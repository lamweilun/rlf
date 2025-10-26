#pragma once

#include <Node/UI/UINode.hpp>
#include <Resource/TextureResource.hpp>

#include <functional>

namespace rlf::Node {
    class UIButtonNode : public UINode {
    public:
        RLF_TYPE_REGISTER_QUICK(UIButtonNode)

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

        void setClickedCallback(std::function<void()> callback);

    protected:
        void preUpdateImpl() override;
        void updateImpl() override;
        void renderImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(UINode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Texture", getTexture, setTexture)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Hovered Texture", getHoveredTexture, setHoveredTexture)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Clicked Texture", getClickedTexture, setClickedTexture)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Hovered Tint", getHoveredTint, setHoveredTint)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Clicked Tint", getClickedTint, setClickedTint)
        RLF_NODE_ACCESS_MEMBER("Use Border", mUseBorder)
        RLF_NODE_ACCESS_MEMBER("Border Thickness", mBorderThickness)
        RLF_NODE_ACCESS_END

    private:
        rlf::TextureResource mTexture;
        rlf::TextureResource mHoveredTexture;
        rlf::TextureResource mClickedTexture;
        Color                mHoveredTint = WHITE;
        Color                mClickedTint = WHITE;

        bool mUseBorder       = false;
        f32  mBorderThickness = 0.1f;

        rlf::TextureResource mTextureInUse;
        Color                mTintToUse  = WHITE;
        bool                 mIsHovering = false;
        bool                 mIsDown     = false;

        std::function<void()> mClickedCallback;
    };
}
