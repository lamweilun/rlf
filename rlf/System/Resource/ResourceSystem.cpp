#include <System/Resource/ResourceSystem.hpp>

namespace rlf::System {

    TextureResource ResourceSystem::getTextureResource(std::string const& filePath) {
        TextureResource          rsc;
        std::shared_ptr<Texture> texture;

        // If texture cannot be found, create and load it in
        if (!mLoadedTextures.contains(filePath)) {
            texture  = std::make_shared<Texture>();
            *texture = LoadTexture(filePath.c_str());
            if (IsTextureValid(*texture)) {
                mLoadedTextures[filePath] = texture;
            }
        } else {
            texture = mLoadedTextures.at(filePath).lock();
        }
        rsc.setTexture(texture);
        return rsc;
    }

    SoundResource ResourceSystem::getSoundResource(std::string const& filePath) {
        SoundResource          rsc;
        std::shared_ptr<Sound> sound;

        // If sound cannot be found, create and load it in
        if (!mLoadedSounds.contains(filePath)) {
            sound  = std::make_shared<Sound>();
            *sound = LoadSound(filePath.c_str());
            if (IsSoundValid(*sound)) {
                mLoadedSounds[filePath] = sound;
            }
        } else {
            sound = mLoadedSounds.at(filePath).lock();
        }
        rsc.setSound(sound);
        return rsc;
    }

    void ResourceSystem::update() {
        // Garbage Collect
        auto garbageCollectFunc = [](auto& loadedResources) {
            auto loadedRscCopy = loadedResources;
            for (auto const& [path, rsc] : loadedRscCopy) {
                if (rsc.expired()) {
                    loadedResources.erase(path);
                }
            }
        };
        garbageCollectFunc(mLoadedTextures);
        garbageCollectFunc(mLoadedSounds);
    }

    void ResourceSystem::shutdown() {
        mLoadedTextures.clear();
        mLoadedSounds.clear();
    }
}
