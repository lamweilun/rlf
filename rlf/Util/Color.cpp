#include <Util/Color.hpp>

std::ostream& operator<<(std::ostream& os, Color color) {
    os << '[';
    os << color.r << ", ";
    os << color.g << ", ";
    os << color.b << ", ";
    os << color.a;
    os << ']';
    return os;
}

void to_json(rlf::Json& j, Color const& color) {
    j['r'] = color.r;
    j['g'] = color.g;
    j['b'] = color.b;
    j['a'] = color.a;
}
void from_json(rlf::Json const& j, Color& color) {
    color.r = j['r'];
    color.g = j['g'];
    color.b = j['b'];
    color.a = j['a'];
}
