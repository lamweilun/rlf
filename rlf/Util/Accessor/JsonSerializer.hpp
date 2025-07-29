#pragma once

namespace rlf::acc {
    class JsonSerializer {
    public:
        rlf::Json const& getJson() const;
        void             setJson(rlf::Json const& j);

        template <class T>
        void operator()(std::string_view name, T const& t) {
            mJson[name] = t;
        }

        // Non-const getter
        template <class T, class M>
        void operator()(std::string_view name,
                        M (T::*getter)(),
                        [[maybe_unused]] void (T::*setter)(M),
                        T const& instance) {
            mJson[name] = (instance.*getter)();
        }

        // Const getter
        template <class T, class M>
        void operator()(std::string_view name,
                        M (T::*getter)() const,
                        [[maybe_unused]] void (T::*setter)(M),
                        T const& instance) {
            mJson[name] = (instance.*getter)();
        }

    private:
        rlf::Json mJson;
    };
}
