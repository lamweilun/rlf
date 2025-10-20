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
    j["x"] = v.x;
    j["y"] = v.y;
}
void to_json(rlf::Json& j, Vector3 const& v) {
    j["x"] = v.x;
    j["y"] = v.y;
    j["z"] = v.z;
}
void to_json(rlf::Json& j, Vector4 const& v) {
    j["x"] = v.x;
    j["y"] = v.y;
    j["z"] = v.z;
    j["w"] = v.w;
}

void from_json(rlf::Json const& j, Vector2& v) {
    rlf::JsonGetSafe(j, "x", v.x);
    rlf::JsonGetSafe(j, "y", v.y);
}
void from_json(rlf::Json const& j, Vector3& v) {
    rlf::JsonGetSafe(j, "x", v.x);
    rlf::JsonGetSafe(j, "y", v.y);
    rlf::JsonGetSafe(j, "z", v.z);
}
void from_json(rlf::Json const& j, Vector4& v) {
    rlf::JsonGetSafe(j, "x", v.x);
    rlf::JsonGetSafe(j, "y", v.y);
    rlf::JsonGetSafe(j, "z", v.z);
    rlf::JsonGetSafe(j, "w", v.w);
}

Vector2 operator-(Vector2 const& v) {
    return Vector2(-v.x, -v.y);
}

Vector2 Vector2FromAngleRad(f32 const angleRad) {
    return Vector2Normalize(Vector2(std::cosf(angleRad), std::sinf(angleRad)));
}

Vector2 Vector2FromAngleDeg(f32 const angleDeg) {
    return Vector2FromAngleRad(angleDeg * DEG2RAD);
}

f32 AngleRadFromVector2(Vector2 const& v) {
    return Vector2Angle(Vector2{1.0f, 0.0f}, Vector2Normalize(v));
}
f32 AngleDegFromVector2(Vector2 const& v) {
    return AngleRadFromVector2(v) * RAD2DEG;
}
