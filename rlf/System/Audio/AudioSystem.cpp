#include <System/Audio/AudioSystem.hpp>

namespace rlf::System {
    void AudioSystem::init() {
        InitAudioDevice();
    }

    void AudioSystem::shutdown() {
        CloseAudioDevice();
    }
}
