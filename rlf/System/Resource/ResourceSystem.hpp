#pragma once

#include <Resource/TextureResource.hpp>

#include <System/ISystem.hpp>

namespace rlf::System {
    class ResourceSystem : public ISystem {
    public:
        void update() override;
        void shutdown() override;

        TextureResource getTextureResource(std::string const& filePath);

    private:
        std::unordered_map<std::string, std::weak_ptr<Texture>> mLoadedTextures;
    };
}
