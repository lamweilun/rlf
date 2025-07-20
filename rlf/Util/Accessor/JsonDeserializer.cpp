#include <Util/Accessor/JsonDeserializer.hpp>

namespace rlf {
    rlf::Json const& JsonDeserializer::getJson() const {
        return mJson;
    }
    void JsonDeserializer::setJson(rlf::Json const& j) {
        mJson = j;
    }
}
