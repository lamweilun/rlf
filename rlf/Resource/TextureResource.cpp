#include <Resource/TextureResource.hpp>

#include <Engine/Engine.hpp>
#include <System/Resource/ResourceSystem.hpp>

namespace rlf {
    void TextureResource::setTexture(std::shared_ptr<::Texture> texture) {
        mTexture = texture;
    }

    std::shared_ptr<::Texture> TextureResource::getTexture() const {
        return mTexture;
    }

    void to_json(rlf::Json& j, rlf::TextureResource const& rsc) {
        j = rsc.getFilePath();
    }

    void from_json(rlf::Json const& j, rlf::TextureResource& rsc) {
        std::string filePath = j.get<std::string>();
        rsc                  = rlf::Engine::getInstance().getSystem<rlf::System::ResourceSystem>()->getTextureResource(filePath);
        rsc.setFilePath(filePath);
    }
}
