#pragma once

#include <Resource/IResource.hpp>

namespace rlf {
    class SoundResource : public IResource {
    public:
        void                     setSound(std::shared_ptr<::Sound> sound);
        std::shared_ptr<::Sound> getSound() const;

    private:
        std::shared_ptr<::Sound> mSound;

        friend void to_json(rlf::Json& j, rlf::SoundResource const& rsc);
        friend void from_json(rlf::Json const& j, rlf::SoundResource& rsc);
    };
}
