#include <Util/Accessor/JsonSerializer.hpp>

namespace rlf {
    rlf::Json const& JsonSerializer::getJson() const {
        return mJson;
    }
    void JsonSerializer::setJson(rlf::Json const& j) {
        mJson = j;
    }
}
