#pragma once

#include <Util/Traits/FunctionTraits.hpp>
#include <Util/Json.hpp>

#include <any>
#include <string>
#include <type_traits>

namespace rlf {
    class NamedValue {
    public:
        virtual ~NamedValue() = default;
        explicit NamedValue(std::string_view name);

        std::string const& getName() const;

        virtual rlf::Json toJson(std::any const& instance) const         = 0;
        virtual void      fromJson(rlf::Json const&, std::any& instance) = 0;

    private:
        std::string mName;
    };

    template <class T, class M>
    class NamedValueDirect : public NamedValue {
    public:
        explicit NamedValueDirect(std::string_view name, M T::* mp)
            : NamedValue(name), memberPtr(mp) {
        }

        virtual rlf::Json toJson(std::any const& instance) const override {
            using type    = std::decay_t<T>;
            type const& t = std::any_cast<type>(instance);
            rlf::Json   j = t.*memberPtr;
            return j;
        }

        void fromJson(rlf::Json const& j, std::any& instance) override {
            using type   = std::decay_t<T>;
            type t       = std::any_cast<type>(instance);
            t.*memberPtr = j;
            instance     = t;
        }

    private:
        M T::* memberPtr;
    };

    template <class Getter, class Setter>
    class NamedValueGetSet : public NamedValue {
    public:
        explicit NamedValueGetSet(std::string_view name, Getter g, Setter s)
            : NamedValue(name), getter{g}, setter{s} {
        }

        rlf::Json toJson(std::any const& instance) const override {
            using type    = std::decay_t<typename rlf::FunctionTraits<Getter>::Type>;
            type const& t = std::any_cast<type>(instance);
            rlf::Json   j = (t.*getter)();
            return j;
        }

        void fromJson(rlf::Json const& j, std::any& instance) override {
            using type    = std::decay_t<typename rlf::FunctionTraits<Setter>::Type>;
            type t        = std::any_cast<type>(instance);
            using argType = std::decay_t<typename rlf::FunctionTraits<Setter>::template ArgType<0>>;
            argType s     = j;
            (t.*setter)(s);
            instance = t;
        }

    private:
        Getter getter;
        Setter setter;
    };

    template <class Derived, class Base>
    class NamedValueBase : public NamedValue {
    public:
        explicit NamedValueBase(std::string_view name)
            : NamedValue(name) {
        }

        rlf::Json toJson(std::any const& instance) const override {
            using DerivedType    = std::decay_t<Derived>;
            using BaseType       = std::decay_t<Base>;
            DerivedType const& t = std::any_cast<DerivedType>(instance);
            BaseType           b = static_cast<BaseType const&>(t);
            rlf::Json          j = b;
            return j;
        }

        void fromJson(rlf::Json const& j, std::any& instance) override {
            using DerivedType         = std::decay_t<Derived>;
            using BaseType            = std::decay_t<Base>;
            DerivedType t             = std::any_cast<DerivedType>(instance);
            BaseType    b             = j;
            static_cast<BaseType&>(t) = b;
            instance                  = t;
        }
    };
}
