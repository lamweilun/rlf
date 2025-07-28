#pragma once

#include <Util/Singleton.hpp>

namespace rlf::System {
    class AudioSystem : public Singleton<AudioSystem> {
    public:
        void init();
        void shutdown();

    private:
    };
}
