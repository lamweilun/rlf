#pragma once

#include <Node/BaseNode.hpp>

#include <Resource/MusicResource.hpp>

namespace rlf::Node {
    class MusicNode : public rlf::Node::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(MusicNode)

        void play() const;
        void resume() const;
        void pause() const;
        void stop() const;
        bool isPlaying() const;

        void                      setMusic(rlf::MusicResource const& musicRsc);
        rlf::MusicResource const& getMusic() const;

    protected:
        void initImpl() override;
        void uninitImpl() override;
        void setActiveImpl(bool const active) override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Music Path", getMusic, setMusic)
        RLF_NODE_ACCESS_MEMBER("Play On Init", mPlayOnInit)
        RLF_NODE_ACCESS_END

    private:
        rlf::MusicResource mMusicRsc;
        bool               mPlayOnInit = true;
    };
}
