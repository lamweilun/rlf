#include <Node/Audio/SoundNode.hpp>

namespace rlf::Node {
    void SoundNode::play() const {
        if (!getActive()) {
            return;
        }
        if (auto sound = mSound.getSound()) {
            PlaySound(*sound);
        }
    }

    void SoundNode::resume() const {
        if (!getActive()) {
            return;
        }
        if (auto sound = mSound.getSound()) {
            ResumeSound(*sound);
        }
    }

    void SoundNode::pause() const {
        if (!getActive()) {
            return;
        }
        if (auto sound = mSound.getSound()) {
            PauseSound(*sound);
        }
    }

    void SoundNode::stop() const {
        if (!getActive()) {
            return;
        }
        if (auto sound = mSound.getSound()) {
            StopSound(*sound);
        }
    }

    bool SoundNode::isPlaying() const {
        if (auto sound = mSound.getSound()) {
            return IsSoundPlaying(*sound);
        }
        return false;
    }

    void SoundNode::setSound(rlf::SoundResource const& soundRsc) {
        mSound = soundRsc;
    }
    rlf::SoundResource const& SoundNode::getSound() const {
        return mSound;
    }

    void SoundNode::initImpl() {
        if (mPlayOnInit) {
            play();
        }
    }

    void SoundNode::uninitImpl() {
        stop();
    }

    void SoundNode::setActiveImpl(bool const active) {
        if (!active) {
            if (mPauseOnInactive) {
                pause();
            } else {
                stop();
            }
        } else {
            if (mPauseOnInactive) {
                resume();
            } else {
                play();
            }
        }
    }
}
