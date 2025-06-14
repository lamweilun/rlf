#pragma once

namespace rlf {
    template <class T>
    class Singleton {
    public:
        Singleton()                             = default;
        ~Singleton()                            = default;
        Singleton(Singleton const &)            = delete;
        Singleton(Singleton &&)                 = delete;
        Singleton &operator=(Singleton const &) = delete;
        Singleton &operator=(Singleton &&)      = delete;

        static T &getInstance() {
            static T instance;
            return instance;
        }
    };
}
