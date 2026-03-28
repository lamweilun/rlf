#pragma once

#include <System/ISystem.hpp>

namespace rlf
{
    class AudioSystem : public ISystem
    {
    public:
        void init() override;
        void shutdown() override;

    private:
    };
}
