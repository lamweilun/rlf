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
    std::stringstream ss;
    ss << v.x;
    ss << ' ' << v.y;
    j = ss.str();
}
void to_json(rlf::Json& j, Vector3 const& v) {
    std::stringstream ss;
    ss << v.x;
    ss << ' ' << v.y;
    ss << ' ' << v.z;
    j = ss.str();
}
void to_json(rlf::Json& j, Vector4 const& v) {
    std::stringstream ss;
    ss << v.x;
    ss << ' ' << v.y;
    ss << ' ' << v.z;
    ss << ' ' << v.w;
    j = ss.str();
}

void from_json(rlf::Json const& j, Vector2& v) {
    std::stringstream ss;
    ss.str(j.get<std::string>());
    ss >> v.x;
    ss >> v.y;
}
void from_json(rlf::Json const& j, Vector3& v) {
    std::stringstream ss;
    ss.str(j.get<std::string>());
    ss >> v.x;
    ss >> v.y;
    ss >> v.z;
}
void from_json(rlf::Json const& j, Vector4& v) {
    std::stringstream ss;
    ss.str(j.get<std::string>());
    ss >> v.x;
    ss >> v.y;
    ss >> v.z;
    ss >> v.w;
}
