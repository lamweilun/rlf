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
    std::stringstream ss;
    ss << v2.x;
    ss << ' ' << v2.y;
    j = ss.str();
}
void to_json(rlf::Json& j, Vector3 const& v3) {
    std::stringstream ss;
    ss << v3.x;
    ss << ' ' << v3.y;
    ss << ' ' << v3.z;
    j = ss.str();
}
void to_json(rlf::Json& j, Vector4 const& v4) {
    std::stringstream ss;
    ss << v4.x;
    ss << ' ' << v4.y;
    ss << ' ' << v4.z;
    ss << ' ' << v4.w;
    j = ss.str();
}

void from_json(rlf::Json const& j, Vector2& v2) {
    std::stringstream ss;
    ss.str(j.get<std::string>());
    ss >> v2.x;
    ss >> v2.y;
}
void from_json(rlf::Json const& j, Vector3& v3) {
    std::stringstream ss;
    ss.str(j.get<std::string>());
    ss >> v3.x;
    ss >> v3.y;
    ss >> v3.z;
}
void from_json(rlf::Json const& j, Vector4& v4) {
    std::stringstream ss;
    ss.str(j.get<std::string>());
    ss >> v4.x;
    ss >> v4.y;
    ss >> v4.z;
    ss >> v4.w;
}
