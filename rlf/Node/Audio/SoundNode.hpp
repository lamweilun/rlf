#pragma once

#include <Node/BaseNode.hpp>

#include <Resource/SoundResource.hpp>

namespace rlf::Node {
    class SoundNode : public rlf::Node::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(SoundNode)

        void play() const;
        void resume() const;
        void pause() const;
        void stop() const;
        bool isPlaying() const;

        void                      setSound(rlf::SoundResource const& soundRsc);
        rlf::SoundResource const& getSound() const;

    protected:
        void initImpl() override;
        void shutdownImpl() override;
        void setActiveImpl(bool const active) override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Sound", getSound, setSound)
        RLF_NODE_ACCESS_MEMBER("Play On Init", mPlayOnInit)
        RLF_NODE_ACCESS_MEMBER("Pause On Inactive", mPauseOnInactive)
        RLF_NODE_ACCESS_END

    private:
        rlf::SoundResource mSound;
        bool               mPlayOnInit      = true;
        bool               mPauseOnInactive = true;
    };
}
