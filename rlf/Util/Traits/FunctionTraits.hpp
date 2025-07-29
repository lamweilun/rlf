#pragma once

#include <tuple>

namespace rlf::traits {

    template <class T>
    class FunctionTraits;

    template <class R, class... Args>
    class FunctionTraits<R(Args...)> {
    public:
        using RetType  = R;
        using ArgTypes = std::tuple<Args...>;

        template <size_t I>
        using ArgType = std::tuple_element_t<I, ArgTypes>;
    };

    template <class R, class T, class... Args>
    class FunctionTraits<R (T::*)(Args...)> {
    public:
        using RetType  = R;
        using Type     = T;
        using ArgTypes = std::tuple<Args...>;

        template <size_t I>
        using ArgType = std::tuple_element_t<I, ArgTypes>;
    };

    template <class R, class T, class... Args>
    class FunctionTraits<R (T::*)(Args...) const> {
    public:
        using RetType  = R;
        using Type     = T;
        using ArgTypes = std::tuple<Args...>;

        template <size_t I>
        using ArgType = std::tuple_element_t<I, ArgTypes>;
    };
}
