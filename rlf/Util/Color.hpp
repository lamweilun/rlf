#pragma once

#include <iostream>

std::ostream& operator<<(std::ostream& os, Color const& color);
void          to_json(rlf::Json& j, Color const& color);
void          from_json(rlf::Json const& j, Color& color);

bool operator==(Color const& lhs, Color const& rhs);
bool operator!=(Color const& lhs, Color const& rhs);

Color  operator+(Color const& lhs, Color const& rhs);
Color& operator+=(Color& lhs, Color const& rhs);

Color  operator-(Color const& lhs, Color const& rhs);
Color& operator-=(Color& lhs, Color const& rhs);

Color  operator*(Color const& lhs, f32 const v);
Color& operator*=(Color& lhs, f32 const v);

Color  operator/(Color const& lhs, f32 const v);
Color& operator/=(Color& lhs, f32 const v);
