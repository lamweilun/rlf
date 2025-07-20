#pragma once

namespace rlf {
    class JsonDeserializer {
    public:
        rlf::Json const& getJson() const;
        void             setJson(rlf::Json const& j);

        template <class T>
        void operator()(std::string_view name, T& t) {
            if (mJson.contains(name)) {
                t = mJson[name];
            }
        }

        // Non-const getter
        template <class T, class M>
        void operator()(std::string_view name,
                        [[maybe_unused]] M (T::*getter)(),
                        void (T::*setter)(M),
                        T& instance) {
            if (mJson.contains(name)) {
                (instance.*setter)(mJson[name].get<std::decay_t<M>>());
            }
        }

        // Const getter
        template <class T, class M>
        void operator()(std::string_view name,
                        [[maybe_unused]] M (T::*getter)() const,
                        void (T::*setter)(M),
                        T& instance) {
            if (mJson.contains(name)) {
                (instance.*setter)(mJson[name].get<std::decay_t<M>>());
            }
        }

    private:
        rlf::Json mJson;
    };
}
