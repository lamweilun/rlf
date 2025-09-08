#include <Util/Color.hpp>

std::ostream& operator<<(std::ostream& os, Color color) {
    os << "[";
    os << static_cast<u16>(color.r) << ", ";
    os << static_cast<u16>(color.g) << ", ";
    os << static_cast<u16>(color.b) << ", ";
    os << static_cast<u16>(color.a);
    os << "]";
    return os;
}

void to_json(rlf::Json& j, Color const& color) {
    j["r"] = color.r;
    j["g"] = color.g;
    j["b"] = color.b;
    j["a"] = color.a;
}
void from_json(rlf::Json const& j, Color& color) {
    color.r = j["r"];
    color.g = j["g"];
    color.b = j["b"];
    color.a = j["a"];
}

bool operator==(Color const& lhs, Color const& rhs) {
    return ColorIsEqual(lhs, rhs);
}
bool operator!=(Color const& lhs, Color const& rhs) {
    return !(lhs == rhs);
}
