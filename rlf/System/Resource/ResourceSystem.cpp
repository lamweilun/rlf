#include <System/Resource/ResourceSystem.hpp>

namespace rlf::System {

    TextureResource ResourceSystem::getTextureResource(std::string const& filePath) {
        TextureResource          rsc;
        std::shared_ptr<Texture> texture;

        // If texture cannot be found, create and load it in
        if (!mLoadedTextures.contains(filePath)) {
            texture                   = std::make_shared<Texture>();
            *texture                  = LoadTexture(filePath.c_str());
            mLoadedTextures[filePath] = texture;
        } else {
            texture = mLoadedTextures.at(filePath).lock();
        }
        rsc.setTexture(texture);
        return rsc;
    }

    void ResourceSystem::update() {
        // Garbage Collect
        auto loadedTextures = mLoadedTextures;
        for (auto const& [path, texture] : loadedTextures) {
            if (texture.expired()) {
                mLoadedTextures.erase(path);
            }
        }
    }

    void ResourceSystem::shutdown() {
        mLoadedTextures.clear();
    }
}
