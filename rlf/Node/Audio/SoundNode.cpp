#include <Node/Audio/SoundNode.hpp>

namespace rlf {
    void SoundNode::play() const {
        if (!getActive()) {
            return;
        }
        PlaySound(mSound);
    }

    void SoundNode::resume() const {
        if (!getActive()) {
            return;
        }
        ResumeSound(mSound);
    }

    void SoundNode::pause() const {
        if (!getActive()) {
            return;
        }
        PauseSound(mSound);
    }

    void SoundNode::stop() const {
        if (!getActive()) {
            return;
        }
        StopSound(mSound);
    }

    bool SoundNode::isPlaying() const {
        return IsSoundPlaying(mSound);
    }

    void SoundNode::setSoundFromMemory(std::vector<u8> const &data, std::string_view filetype) {
        // Attempt to load new music
        auto newWave = LoadWaveFromMemory(filetype.data(), data.data(), static_cast<int>(data.size()));
        if (!IsWaveValid(newWave)) {
            return;
        }
        auto newSound = LoadSoundFromWave(newWave);
        UnloadWave(newWave);
        if (!IsSoundValid(newSound)) {
            return;
        }

        // Set new music
        if (IsSoundValid(mSound)) {
            UnloadSound(mSound);
        }
        mSound = newSound;
    }

    void SoundNode::setActiveImpl(bool const active) {
        if (!active) {
            if (mPauseWhenInactive) {
                pause();
            } else {
                stop();
            }
        } else {
            if (mPauseWhenInactive) {
                resume();
            } else {
                play();
            }
        }
    }

    void SoundNode::shutdownImpl() {
        if (IsSoundValid(mSound)) {
            UnloadSound(mSound);
        }
        mSound = {};
    }
}
