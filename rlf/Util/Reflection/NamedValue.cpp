#include <Util/Reflection/NamedValue.hpp>

namespace rlf {
    NamedValue::NamedValue(std::string_view name)
        : mName{name} {
    }

    std::string const& NamedValue::getName() const {
        return mName;
    }
}
