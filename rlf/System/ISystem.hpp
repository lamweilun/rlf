#pragma once

namespace rlf
{
    class ISystem
    {
    public:
        ISystem()                           = default;
        virtual ~ISystem()                  = default;
        ISystem(ISystem const &)            = delete;
        ISystem(ISystem &&)                 = delete;
        ISystem &operator=(ISystem const &) = delete;
        ISystem &operator=(ISystem &&)      = delete;

        virtual void init();
        virtual void update();
        virtual void render();
        virtual void shutdown();

    private:
    };
}
