#pragma once

namespace rlf {

    template <class T>
    class MemberTraits;

    template <class T, class M>
    class MemberTraits<M T::*> {
    public:
        using MemberType = M;
        using Type       = T;
    };
}
