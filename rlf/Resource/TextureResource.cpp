#include <Resource/TextureResource.hpp>

#include <Engine/Engine.hpp>
#include <System/Resource/ResourceSystem.hpp>

namespace rlf
{
    void TextureResource::setTexture(std::shared_ptr<::Texture> texture)
    {
        mTexture = texture;
    }

    std::shared_ptr<::Texture> TextureResource::getTexture() const
    {
        return mTexture;
    }

    u32 TextureResource::getWidth() const
    {
        if (mTexture && IsTextureValid(*mTexture))
        {
            return static_cast<u32>(mTexture->width);
        }
        return 0;
    }
    u32 TextureResource::getHeight() const
    {
        if (mTexture && IsTextureValid(*mTexture))
        {
            return static_cast<u32>(mTexture->height);
        }
        return 0;
    }

    void to_json(rlf::Json& j, rlf::TextureResource const& rsc)
    {
        j = rsc.getFilePath();
    }

    void from_json(rlf::Json const& j, rlf::TextureResource& rsc)
    {
        std::string filePath = j.get<std::string>();
        rsc                  = rlf::Engine::getInstance().getSystem<rlf::System::ResourceSystem>()->getTextureResource(filePath);
        rsc.setFilePath(filePath);
    }
}
