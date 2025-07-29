#include <System/Audio/AudioSystem.hpp>

namespace rlf::system {
    void AudioSystem::init() {
        InitAudioDevice();
    }

    void AudioSystem::shutdown() {
        CloseAudioDevice();
    }
}
