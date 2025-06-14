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
