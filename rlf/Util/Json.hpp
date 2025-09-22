#pragma once

#include <nlohmann/json.hpp>

namespace rlf {
    using Json = nlohmann::ordered_json;

    template <class T>
    void JsonGetSafe(rlf::Json const& j, std::string_view name, T& t) {
        if (j.contains(name) && !j[name].is_null()) {
            t = j[name];
        }
    }
}
