#pragma once

#include <iostream>

std::ostream& operator<<(std::ostream& os, Color const& color);
void          to_json(rlf::Json& j, Color const& color);
void          from_json(rlf::Json const& j, Color& color);

bool operator==(Color const& lhs, Color const& rhs);
bool operator!=(Color const& lhs, Color const& rhs);

Vector4 ColorToVector4(Color const& color);
Color   Vector4ToColor(Vector4 const& vec);

Color  operator+(Color const& lhs, Color const& rhs);
Color& operator+=(Color& lhs, Color const& rhs);

Color  operator-(Color const& lhs, Color const& rhs);
Color& operator-=(Color& lhs, Color const& rhs);

Color  operator*(Color const& lhs, f32 const v);
Color& operator*=(Color& lhs, f32 const v);

Color  operator/(Color const& lhs, f32 const v);
Color& operator/=(Color& lhs, f32 const v);

struct Color4F {
    f32 r = 0.0f;
    f32 g = 0.0f;
    f32 b = 0.0f;
    f32 a = 0.0f;

    Color4F()                          = default;
    ~Color4F()                         = default;
    Color4F(Color4F const&)            = default;
    Color4F(Color4F&&)                 = default;
    Color4F& operator=(Color4F const&) = default;
    Color4F& operator=(Color4F&&)      = default;

    friend std::ostream& operator<<(std::ostream& os, Color4F const& color);
    bool                 operator==(Color4F const& rhs) const;
    bool                 operator!=(Color4F const& rhs) const;

    Color4F  operator+(Color4F const& rhs) const;
    Color4F& operator+=(Color4F const& rhs);

    Color4F  operator-(Color4F const& rhs) const;
    Color4F& operator-=(Color4F const& rhs);

    Color4F  operator*(Color4F const& rhs) const;
    Color4F& operator*=(Color4F const& rhs);

    Color4F  operator/(Color4F const& rhs) const;
    Color4F& operator/=(Color4F const& rhs);

    Color4F  operator*(f32 const v) const;
    Color4F& operator*=(f32 const v);

    Color4F  operator/(f32 const v) const;
    Color4F& operator/=(f32 const v);

    static Color4F FromColor(Color const& color);
    Vector4        ToVector4() const;
    Color          ToColor() const;
};

void to_json(rlf::Json& j, Color4F const& color);
void from_json(rlf::Json const& j, Color4F& color);
