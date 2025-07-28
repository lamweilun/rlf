#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class SoundNode : public rlf::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(SoundNode)

        void play() const;
        void resume() const;
        void pause() const;
        void stop() const;
        bool isPlaying() const;

        void setSoundFromMemory(std::vector<u8> const& data, std::string_view filetype);

    protected:
        void setActiveImpl(bool const active) override;
        void shutdownImpl() override;

    private:
        Sound mSound             = {};
        bool  mPauseWhenInactive = false;
    };
}
