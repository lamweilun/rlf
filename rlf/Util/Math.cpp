#include <Util/Math.hpp>

std::ostream& operator<<(std::ostream& os, Vector2 const& v2) {
    os << "[";
    os << v2.x << ", ";
    os << v2.y;
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, Vector3 const& v3) {
    os << "[";
    os << v3.x << ", ";
    os << v3.y << ", ";
    os << v3.z;
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, Vector4 const& v4) {
    os << "[";
    os << v4.x << ", ";
    os << v4.y << ", ";
    os << v4.z << ", ";
    os << v4.w;
    os << "]";
    return os;
}

void to_json(rlf::Json& j, Vector2 const& v2) {
    j["x"] = v2.x;
    j["y"] = v2.y;
}
void to_json(rlf::Json& j, Vector3 const& v3) {
    j["x"] = v3.x;
    j["y"] = v3.y;
    j["z"] = v3.z;
}
void to_json(rlf::Json& j, Vector4 const& v4) {
    j["y"] = v4.y;
    j["x"] = v4.x;
    j["z"] = v4.z;
    j["w"] = v4.w;
}

void from_json(rlf::Json const& j, Vector2& v2) {
    v2.x = j["x"];
    v2.y = j["y"];
}
void from_json(rlf::Json const& j, Vector3& v3) {
    v3.x = j["x"];
    v3.y = j["y"];
    v3.z = j["z"];
}
void from_json(rlf::Json const& j, Vector4& v4) {
    v4.x = j["x"];
    v4.y = j["y"];
    v4.z = j["z"];
    v4.w = j["w"];
}
