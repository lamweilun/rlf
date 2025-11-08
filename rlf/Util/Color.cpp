#include <Util/Color.hpp>

std::ostream& operator<<(std::ostream& os, Color const& color)
{
    os << "[";
    os << static_cast<u16>(color.r) << ", ";
    os << static_cast<u16>(color.g) << ", ";
    os << static_cast<u16>(color.b) << ", ";
    os << static_cast<u16>(color.a);
    os << "]";
    return os;
}

void to_json(rlf::Json& j, Color const& color)
{
    j["r"] = color.r;
    j["g"] = color.g;
    j["b"] = color.b;
    j["a"] = color.a;
}
void from_json(rlf::Json const& j, Color& color)
{
    color.r = j["r"];
    color.g = j["g"];
    color.b = j["b"];
    color.a = j["a"];
}

bool operator==(Color const& lhs, Color const& rhs)
{
    return ColorIsEqual(lhs, rhs);
}
bool operator!=(Color const& lhs, Color const& rhs)
{
    return !(lhs == rhs);
}

Color operator+(Color const& lhs, Color const& rhs)
{
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

Color& operator+=(Color& lhs, Color const& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

Color operator-(Color const& lhs, Color const& rhs)
{
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

Color& operator-=(Color& lhs, Color const& rhs)
{
    lhs = lhs - rhs;
    return lhs;
}

Color operator*(Color const& lhs, f32 const v)
{
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
Color& operator*=(Color& lhs, f32 const v)
{
    lhs = lhs * v;
    return lhs;
}

Color operator/(Color const& lhs, f32 const v)
{
    if (FloatEquals(v, 0.0f))
    {
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
Color& operator/=(Color& lhs, f32 const v)
{
    lhs = lhs / v;
    return lhs;
}
