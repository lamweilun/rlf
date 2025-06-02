#pragma once

namespace rlf {
    template <class T>
    class Singleton {
        Singleton()                             = default;
        Singleton(Singleton const &)            = default;
        Singleton(Singleton &&)                 = default;
        Singleton &operator=(Singleton const &) = default;
        Singleton &operator=(Singleton &&)      = default;

    public:
        ~Singleton() = default;

        static Singleton &getInstance() {
            static Singleton instance;
            return instance;
        }
    };
}
