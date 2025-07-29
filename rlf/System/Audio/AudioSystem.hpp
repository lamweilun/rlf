#pragma once

#include <Util/Singleton.hpp>

namespace rlf::system {
    class AudioSystem : public Singleton<AudioSystem> {
    public:
        void init();
        void shutdown();

    private:
    };
}
