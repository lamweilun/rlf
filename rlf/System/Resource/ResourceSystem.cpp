#include <System/Resource/ResourceSystem.hpp>

namespace rlf::System {

    TextureResource ResourceSystem::getTextureResource(std::string const& filePath) {
        TextureResource          rsc;
        std::shared_ptr<Texture> texture;

        if (!mLoadedTextures.contains(filePath)) {
            texture                   = std::make_shared<Texture>();
            *texture                  = LoadTexture(filePath.c_str());
            mLoadedTextures[filePath] = texture;
        } else {
            texture = mLoadedTextures.at(filePath);
        }
        rsc.setTexture(texture);
        return rsc;
    }

    void ResourceSystem::update() {
        // RELOOK INTO GARBAGE COLLECT

        // std::vector<std::string> unloadedTexturePaths;
        // for (auto const& [path, texture] : mLoadedTextures) {
        //     if (texture.use_count() == 1) {
        //         UnloadTexture(*texture);
        //         unloadedTexturePaths.push_back(path);
        //     }
        // }
        // for (auto const& path : unloadedTexturePaths) {
        //     mLoadedTextures.erase(path);
        // }
    }

    void ResourceSystem::shutdown() {
        for (auto const& [path, texture] : mLoadedTextures) {
            UnloadTexture(*texture);
        }
        mLoadedTextures.clear();
    }
}
