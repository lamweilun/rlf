#pragma once

#include <numbers>

std::ostream& operator<<(std::ostream& os, Vector2 const& v);
std::ostream& operator<<(std::ostream& os, Vector3 const& v);
std::ostream& operator<<(std::ostream& os, Vector4 const& v);

void to_json(rlf::Json& j, Vector2 const& v);
void to_json(rlf::Json& j, Vector3 const& v);
void to_json(rlf::Json& j, Vector4 const& v);

void from_json(rlf::Json const& j, Vector2& v);
void from_json(rlf::Json const& j, Vector3& v);
void from_json(rlf::Json const& j, Vector4& v);

Vector2 operator-(Vector2 const&);

namespace rlf {
    static inline constexpr auto pi   = std::numbers::pi_v<f32>;
    static inline constexpr auto pi_d = std::numbers::pi_v<f64>;
}
