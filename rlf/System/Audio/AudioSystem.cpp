#include <System/Audio/AudioSystem.hpp>

namespace rlf
{
    void AudioSystem::init()
    {
        InitAudioDevice();
    }

    void AudioSystem::shutdown()
    {
        CloseAudioDevice();
    }
}
