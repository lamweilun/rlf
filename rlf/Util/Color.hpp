#pragma once

#include <iostream>

std::ostream& operator<<(std::ostream& os, Color color);
void          to_json(rlf::Json& j, Color const& v);
void          from_json(rlf::Json const& j, Color& v);

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
