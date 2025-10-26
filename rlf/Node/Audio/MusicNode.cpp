#include <Node/Audio/MusicNode.hpp>

namespace rlf::Node {

    void MusicNode::play() const {
        if (!getActive()) {
            return;
        }

        if (auto musicStream = mMusicRsc.getMusicStream()) {
            PlayMusicStream(*musicStream);
        }
    }

    void MusicNode::resume() const {
        if (!getActive()) {
            return;
        }
        if (auto musicStream = mMusicRsc.getMusicStream()) {
            ResumeMusicStream(*musicStream);
        }
    }
    void MusicNode::pause() const {
        if (!getActive()) {
            return;
        }
        if (auto musicStream = mMusicRsc.getMusicStream()) {
            PauseMusicStream(*musicStream);
        }
    }

    void MusicNode::stop() const {
        if (!getActive()) {
            return;
        }
        if (auto musicStream = mMusicRsc.getMusicStream()) {
            StopMusicStream(*musicStream);
        }
    }

    bool MusicNode::isPlaying() const {
        if (auto musicStream = mMusicRsc.getMusicStream()) {
            return IsMusicStreamPlaying(*musicStream);
        }
        return false;
    }

    void MusicNode::initImpl() {
        if (mPlayOnInit) {
            play();
        }
    }
    void MusicNode::uninitImpl() {
        stop();
    }
    void MusicNode::setActiveImpl(bool const active) {
        active ? resume() : pause();
    }

    void MusicNode::setMusic(rlf::MusicResource const& musicRsc) {
        mMusicRsc = musicRsc;
    }
    rlf::MusicResource const& MusicNode::getMusic() const {
        return mMusicRsc;
    }
}
