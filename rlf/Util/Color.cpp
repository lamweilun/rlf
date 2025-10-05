#include <Util/Color.hpp>

std::ostream& operator<<(std::ostream& os, Color const& color) {
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

Vector4 ColorToVector4(Color const& color) {
    return Vector4{
        static_cast<f32>(color.r) / 255,
        static_cast<f32>(color.g) / 255,
        static_cast<f32>(color.b) / 255,
        static_cast<f32>(color.a) / 255};
}

Color Vector4ToColor(Vector4 const& vec) {
    return Color{
        static_cast<u8>(std::clamp(vec.x, 0.0f, 1.0f) * 255),
        static_cast<u8>(std::clamp(vec.y, 0.0f, 1.0f) * 255),
        static_cast<u8>(std::clamp(vec.z, 0.0f, 1.0f) * 255),
        static_cast<u8>(std::clamp(vec.w, 0.0f, 1.0f) * 255)};
}

Color operator+(Color const& lhs, Color const& rhs) {
    Color     c;
    u16 const r = lhs.r + rhs.r;
    u16 const g = lhs.g + rhs.g;
    u16 const b = lhs.b + rhs.b;
    u16 const a = lhs.a + rhs.a;
    c.r         = static_cast<u8>(std::clamp(r, u16{0}, u16{255}));
    c.g         = static_cast<u8>(std::clamp(g, u16{0}, u16{255}));
    c.b         = static_cast<u8>(std::clamp(b, u16{0}, u16{255}));
    c.a         = static_cast<u8>(std::clamp(a, u16{0}, u16{255}));
    return c;
}

Color& operator+=(Color& lhs, Color const& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

Color operator-(Color const& lhs, Color const& rhs) {
    Color     c;
    i16 const r = lhs.r - rhs.r;
    i16 const g = lhs.g - rhs.g;
    i16 const b = lhs.b - rhs.b;
    i16 const a = lhs.a - rhs.a;
    c.r         = static_cast<u8>(std::clamp(r, i16{0}, i16{255}));
    c.g         = static_cast<u8>(std::clamp(g, i16{0}, i16{255}));
    c.b         = static_cast<u8>(std::clamp(b, i16{0}, i16{255}));
    c.a         = static_cast<u8>(std::clamp(a, i16{0}, i16{255}));
    return c;
}

Color& operator-=(Color& lhs, Color const& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

Color operator*(Color const& lhs, f32 const v) {
    Color     c;
    f32 const r = lhs.r * v;
    f32 const g = lhs.g * v;
    f32 const b = lhs.b * v;
    f32 const a = lhs.a * v;
    c.r         = static_cast<u8>(std::clamp(r, 0.0f, 255.0f));
    c.g         = static_cast<u8>(std::clamp(g, 0.0f, 255.0f));
    c.b         = static_cast<u8>(std::clamp(b, 0.0f, 255.0f));
    c.a         = static_cast<u8>(std::clamp(a, 0.0f, 255.0f));
    return c;
}
Color& operator*=(Color& lhs, f32 const v) {
    lhs = lhs * v;
    return lhs;
}

Color operator/(Color const& lhs, f32 const v) {
    if (FloatEquals(v, 0.0f)) {
        return lhs;
    }
    Color     c;
    f32 const r = lhs.r / v;
    f32 const g = lhs.g / v;
    f32 const b = lhs.b / v;
    f32 const a = lhs.a / v;
    c.r         = static_cast<u8>(std::clamp(r, 0.0f, 255.0f));
    c.g         = static_cast<u8>(std::clamp(g, 0.0f, 255.0f));
    c.b         = static_cast<u8>(std::clamp(b, 0.0f, 255.0f));
    c.a         = static_cast<u8>(std::clamp(a, 0.0f, 255.0f));
    return c;
}
Color& operator/=(Color& lhs, f32 const v) {
    lhs = lhs / v;
    return lhs;
}

Color4F Color4F::FromColor(Color const& color) {
    Color4F col;
    col.r = color.r / 255.0f;
    col.g = color.g / 255.0f;
    col.b = color.b / 255.0f;
    col.a = color.a / 255.0f;
    return col;
}

std::ostream& operator<<(std::ostream& os, Color4F const& color) {
    os << "[";
    os << color.r << ", ";
    os << color.g << ", ";
    os << color.b << ", ";
    os << color.a;
    os << "]";
    return os;
}

bool Color4F::operator==(Color4F const& rhs) const {
    return FloatEquals(r, rhs.r) &&
           FloatEquals(g, rhs.g) &&
           FloatEquals(b, rhs.b) &&
           FloatEquals(a, rhs.a);
}
bool Color4F::operator!=(Color4F const& rhs) const {
    return !(*this == rhs);
}

Color4F Color4F::operator+(Color4F const& rhs) const {
    Color4F c = *this;
    c += rhs;
    return c;
}
Color4F& Color4F::operator+=(Color4F const& rhs) {
    r = std::clamp(r + rhs.r, 0.0f, 1.0f);
    g = std::clamp(g + rhs.g, 0.0f, 1.0f);
    b = std::clamp(b + rhs.b, 0.0f, 1.0f);
    a = std::clamp(a + rhs.a, 0.0f, 1.0f);
    return *this;
}

Color4F Color4F::operator-(Color4F const& rhs) const {
    Color4F c = *this;
    c -= rhs;
    return c;
}
Color4F& Color4F::operator-=(Color4F const& rhs) {
    r = std::clamp(r - rhs.r, 0.0f, 1.0f);
    g = std::clamp(g - rhs.g, 0.0f, 1.0f);
    b = std::clamp(b - rhs.b, 0.0f, 1.0f);
    a = std::clamp(a - rhs.a, 0.0f, 1.0f);
    return *this;
}

Color4F Color4F::operator*(Color4F const& rhs) const {
    Color4F c = *this;
    c *= rhs;
    return c;
}
Color4F& Color4F::operator*=(Color4F const& rhs) {
    r = std::clamp(r * rhs.r, 0.0f, 1.0f);
    g = std::clamp(g * rhs.g, 0.0f, 1.0f);
    b = std::clamp(b * rhs.b, 0.0f, 1.0f);
    a = std::clamp(a * rhs.a, 0.0f, 1.0f);
    return *this;
}

Color4F Color4F::operator/(Color4F const& rhs) const {
    Color4F c = *this;
    c /= rhs;
    return c;
}
Color4F& Color4F::operator/=(Color4F const& rhs) {
    r = std::clamp(r / rhs.r, 0.0f, 1.0f);
    g = std::clamp(g / rhs.g, 0.0f, 1.0f);
    b = std::clamp(b / rhs.b, 0.0f, 1.0f);
    a = std::clamp(a / rhs.a, 0.0f, 1.0f);
    return *this;
}

Color4F Color4F::operator*(f32 const v) const {
    Color4F c = *this;
    c *= v;
    return c;
}
Color4F& Color4F::operator*=(f32 const v) {
    r = std::clamp(r * v, 0.0f, 1.0f);
    g = std::clamp(g * v, 0.0f, 1.0f);
    b = std::clamp(b * v, 0.0f, 1.0f);
    a = std::clamp(a * v, 0.0f, 1.0f);
    return *this;
}

Color4F Color4F::operator/(f32 const v) const {
    Color4F c = *this;
    c /= v;
    return c;
}
Color4F& Color4F::operator/=(f32 const v) {
    if (FloatEquals(v, 0.0f)) {
        return *this;
    }
    r = std::clamp(r / v, 0.0f, 1.0f);
    g = std::clamp(g / v, 0.0f, 1.0f);
    b = std::clamp(b / v, 0.0f, 1.0f);
    a = std::clamp(a / v, 0.0f, 1.0f);
    return *this;
}

void to_json(rlf::Json& j, Color4F const& color) {
    j["r"] = color.r;
    j["g"] = color.g;
    j["b"] = color.b;
    j["a"] = color.a;
}
void from_json(rlf::Json const& j, Color4F& color) {
    color.r = j["r"];
    color.g = j["g"];
    color.b = j["b"];
    color.a = j["a"];
}

Vector4 Color4F::ToVector4() const {
    Vector4 v;
    v.x = r;
    v.y = g;
    v.z = b;
    v.w = a;
    return v;
}
Color Color4F::ToColor() const {
    Color c;
    c.r = static_cast<u8>(r * 255.0f);
    c.g = static_cast<u8>(g * 255.0f);
    c.b = static_cast<u8>(b * 255.0f);
    c.a = static_cast<u8>(a * 255.0f);
    return c;
}
