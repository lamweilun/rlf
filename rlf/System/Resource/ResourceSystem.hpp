#pragma once

#include <Resource/TextureResource.hpp>
#include <Resource/MusicResource.hpp>
#include <Resource/SoundResource.hpp>
#include <Resource/FontResource.hpp>

#include <System/ISystem.hpp>

namespace rlf::System
{
    class ResourceSystem : public ISystem
    {
    public:
        void update() override;
        void shutdown() override;

        TextureResource getTextureResource(std::string const& filePath);
        MusicResource   getMusicResource(std::string const& filePath);
        SoundResource   getSoundResource(std::string const& filePath);
        FontResource    getFontResource(std::string const& filePath);

    private:
        std::unordered_map<std::string, std::weak_ptr<Texture>> mLoadedTextures;
        std::unordered_map<std::string, std::weak_ptr<Music>>   mLoadedMusics;
        std::unordered_map<std::string, std::weak_ptr<Sound>>   mLoadedSounds;
        std::unordered_map<std::string, std::weak_ptr<Font>>    mLoadedFonts;
    };
}
