#include <System/Resource/ResourceSystem.hpp>

// Global unloaded list
namespace
{
    static std::vector<std::string> mTexturesToBeUnloaded = {};
    static std::vector<std::string> mMusicsToBeUnloaded   = {};
    static std::vector<std::string> mSoundsToBeUnloaded   = {};
    static std::vector<std::string> mFontsToBeUnloaded    = {};
}

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
                auto deleter = [path = filePath](Texture* t)
                {
                    mTexturesToBeUnloaded.push_back(path);
                    UnloadTexture(*t);
                    delete t;
                };
                texture                   = std::shared_ptr<Texture>(new Texture{}, deleter);
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

    MusicResource ResourceSystem::getMusicResource(std::string const& filePath)
    {
        MusicResource rsc;
        if (filePath.empty())
        {
            return rsc;
        }
        std::shared_ptr<Music> music;

        // If sound cannot be found, create and load it in
        if (!mLoadedMusics.contains(filePath))
        {
            auto newMusic = LoadMusicStream(filePath.c_str());
            if (IsMusicValid(newMusic))
            {
                auto deleter = [path = filePath](Music* s)
                {
                    mMusicsToBeUnloaded.push_back(path);
                    UnloadMusicStream(*s);
                    delete s;
                };
                music                   = std::shared_ptr<Music>(new Music{}, deleter);
                *music                  = newMusic;
                mLoadedMusics[filePath] = music;
            }
        }
        else
        {
            music = mLoadedMusics.at(filePath).lock();
        }
        rsc.setMusicStream(music);
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
                auto deleter = [path = filePath](Sound* s)
                {
                    mSoundsToBeUnloaded.push_back(path);
                    UnloadSound(*s);
                    delete s;
                };
                sound                   = std::shared_ptr<Sound>(new Sound{}, deleter);
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
                auto deleter = [path = filePath](Font* f)
                {
                    mFontsToBeUnloaded.push_back(path);
                    UnloadFont(*f);
                    delete f;
                };

                font                   = std::shared_ptr<Font>(new Font{}, deleter);
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
        // Remove unloaded textures
        for (auto const& filePath : mTexturesToBeUnloaded)
        {
            mLoadedTextures.erase(filePath);
        }
        mTexturesToBeUnloaded.clear();

        // Remove unloaded musics
        for (auto const& filePath : mMusicsToBeUnloaded)
        {
            mLoadedMusics.erase(filePath);
        }
        mMusicsToBeUnloaded.clear();

        // Remove unloaded sounds
        for (auto const& filePath : mSoundsToBeUnloaded)
        {
            mLoadedSounds.erase(filePath);
        }
        mSoundsToBeUnloaded.clear();

        // Remove unloaded fonts
        for (auto const& filePath : mFontsToBeUnloaded)
        {
            mLoadedFonts.erase(filePath);
        }
        mFontsToBeUnloaded.clear();
    }

    void ResourceSystem::shutdown()
    {
        mTexturesToBeUnloaded.clear();
        mMusicsToBeUnloaded.clear();
        mSoundsToBeUnloaded.clear();
        mFontsToBeUnloaded.clear();

        mLoadedTextures.clear();
        mLoadedMusics.clear();
        mLoadedSounds.clear();
        mLoadedFonts.clear();
    }
}
