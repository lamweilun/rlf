#include <Util/Math.hpp>

std::ostream& operator<<(std::ostream& os, Vector2 const& v) {
    os << "[";
    os << v.x << ", ";
    os << v.y;
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, Vector3 const& v) {
    os << "[";
    os << v.x << ", ";
    os << v.y << ", ";
    os << v.z;
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, Vector4 const& v) {
    os << "[";
    os << v.x << ", ";
    os << v.y << ", ";
    os << v.z << ", ";
    os << v.w;
    os << "]";
    return os;
}

void to_json(rlf::Json& j, Vector2 const& v) {
    j['x'] = v.x;
    j['y'] = v.y;
}
void to_json(rlf::Json& j, Vector3 const& v) {
    j['x'] = v.x;
    j['y'] = v.y;
    j['z'] = v.z;
}
void to_json(rlf::Json& j, Vector4 const& v) {
    j['x'] = v.x;
    j['y'] = v.y;
    j['z'] = v.z;
    j['w'] = v.w;
}

void from_json(rlf::Json const& j, Vector2& v) {
    v.x = j['x'];
    v.y = j['y'];
}
void from_json(rlf::Json const& j, Vector3& v) {
    v.x = j['x'];
    v.y = j['y'];
    v.z = j['z'];
}
void from_json(rlf::Json const& j, Vector4& v) {
    v.x = j['x'];
    v.y = j['y'];
    v.z = j['z'];
    v.w = j['w'];
}
