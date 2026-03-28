#include <Resource/SoundResource.hpp>

#include <Engine/Engine.hpp>
#include <System/Resource/ResourceSystem.hpp>

namespace rlf
{
    void MusicResource::setMusicStream(std::shared_ptr<::Music> musicStream)
    {
        mMusicStream = musicStream;
    }

    std::shared_ptr<::Music> MusicResource::getMusicStream() const
    {
        return mMusicStream;
    }

    void to_json(rlf::Json& j, rlf::MusicResource const& rsc)
    {
        j = rsc.getFilePath();
    }

    void from_json(rlf::Json const& j, rlf::MusicResource& rsc)
    {
        std::string filePath = j.get<std::string>();
        rsc                  = rlf::Engine::getInstance().getSystem<rlf::ResourceSystem>()->getMusicResource(filePath);
        rsc.setFilePath(filePath);
    }
}
