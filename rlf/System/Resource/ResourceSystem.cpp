#include <System/Resource/ResourceSystem.hpp>

namespace rlf::System
{

    TextureResource ResourceSystem::getTextureResource(std::string const& filePath)
    {
        TextureResource rsc;
        if (filePath.empty())
        {
            return rsc;
        }
        std::shared_ptr<Texture> texture;

        // If texture cannot be found, create and load it in
        if (!mLoadedTextures.contains(filePath))
        {
            auto newTexture = LoadTexture(filePath.c_str());
            if (IsTextureValid(newTexture))
            {
                texture                   = std::shared_ptr<Texture>(new Texture{}, [](Texture* t)
                                                                     { UnloadTexture(*t); delete t; });
                *texture                  = newTexture;
                mLoadedTextures[filePath] = texture;
            }
        }
        else
        {
            texture = mLoadedTextures.at(filePath).lock();
        }
        rsc.setTexture(texture);
        return rsc;
    }

    SoundResource ResourceSystem::getSoundResource(std::string const& filePath)
    {
        SoundResource rsc;
        if (filePath.empty())
        {
            return rsc;
        }
        std::shared_ptr<Sound> sound;

        // If sound cannot be found, create and load it in
        if (!mLoadedSounds.contains(filePath))
        {
            auto newSound = LoadSound(filePath.c_str());
            if (IsSoundValid(newSound))
            {
                sound                   = std::shared_ptr<Sound>(new Sound{}, [](Sound* s)
                                                                 { UnloadSound(*s); delete s; });
                *sound                  = newSound;
                mLoadedSounds[filePath] = sound;
            }
        }
        else
        {
            sound = mLoadedSounds.at(filePath).lock();
        }
        rsc.setSound(sound);
        return rsc;
    }

    MusicResource ResourceSystem::getMusicResource(std::string const& filePath)
    {
        MusicResource rsc;
        if (filePath.empty())
        {
            return rsc;
        }
        std::shared_ptr<Music> music;

        // If sound cannot be found, create and load it in
        if (!mLoadedMusic.contains(filePath))
        {
            auto newMusic = LoadMusicStream(filePath.c_str());
            if (IsMusicValid(newMusic))
            {
                music                  = std::shared_ptr<Music>(new Music{}, [](Music* s)
                                                                { UnloadMusicStream(*s); delete s; });
                *music                 = newMusic;
                mLoadedMusic[filePath] = music;
            }
        }
        else
        {
            music = mLoadedMusic.at(filePath).lock();
        }
        rsc.setMusicStream(music);
        return rsc;
    }

    FontResource ResourceSystem::getFontResource(std::string const& filePath)
    {
        FontResource rsc;
        if (filePath.empty())
        {
            return rsc;
        }
        std::shared_ptr<Font> font;

        // If sound cannot be found, create and load it in
        if (!mLoadedFonts.contains(filePath))
        {
            auto newFont = LoadFont(filePath.c_str());
            if (IsFontValid(newFont))
            {
                font                   = std::shared_ptr<Font>(new Font{}, [](Font* f)
                                                               { UnloadFont(*f); delete f; });
                *font                  = newFont;
                mLoadedFonts[filePath] = font;
            }
        }
        else
        {
            font = mLoadedFonts.at(filePath).lock();
        }
        rsc.setFont(font);
        return rsc;
    }

    void ResourceSystem::update()
    {
        // Garbage Collect
        auto garbageCollectFunc = [](auto& loadedResources)
        {
            auto loadedRscCopy = loadedResources;
            for (auto const& [path, rsc] : loadedRscCopy)
            {
                if (rsc.expired())
                {
                    loadedResources.erase(path);
                }
            }
        };
        garbageCollectFunc(mLoadedTextures);
        garbageCollectFunc(mLoadedSounds);
        garbageCollectFunc(mLoadedFonts);
    }

    void ResourceSystem::shutdown()
    {
        mLoadedTextures.clear();
        mLoadedSounds.clear();
        mLoadedFonts.clear();
    }
}
