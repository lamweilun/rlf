#include <Resource/SoundResource.hpp>

#include <Engine/Engine.hpp>
#include <System/Resource/ResourceSystem.hpp>

namespace rlf {
    SoundResource::~SoundResource() {
        if (mSound && mSound.use_count() == 1) {
            UnloadSound(*mSound);
            mSound = nullptr;
        }
    }

    void SoundResource::setSound(std::shared_ptr<::Sound> sound) {
        mSound = sound;
    }

    std::shared_ptr<::Sound> SoundResource::getSound() const {
        return mSound;
    }

    void to_json(rlf::Json& j, rlf::SoundResource const& rsc) {
        j = rsc.getFilePath();
    }

    void from_json(rlf::Json const& j, rlf::SoundResource& rsc) {
        std::string filePath = j.get<std::string>();
        rsc                  = rlf::Engine::getInstance().getSystem<rlf::System::ResourceSystem>()->getSoundResource(filePath);
        rsc.setFilePath(filePath);
    }
}
