#pragma once

#include <Resource/IResource.hpp>

namespace rlf {
    class MusicResource : public IResource {
    public:
        void                     setMusicStream(std::shared_ptr<::Music> music);
        std::shared_ptr<::Music> getMusicStream() const;

    private:
        std::shared_ptr<::Music> mMusicStream;

        friend void to_json(rlf::Json& j, rlf::MusicResource const& rsc);
        friend void from_json(rlf::Json const& j, rlf::MusicResource& rsc);
    };
}
