#pragma once

namespace rlf {
    template <class T>
    class Singleton {
        Singleton(Singleton const &)            = default;
        Singleton(Singleton &&)                 = default;
        Singleton &operator=(Singleton const &) = default;
        Singleton &operator=(Singleton &&)      = default;

    public:
        Singleton()  = default;
        ~Singleton() = default;

        static T &getInstance() {
            static T instance;
            return instance;
        }
    };
}
