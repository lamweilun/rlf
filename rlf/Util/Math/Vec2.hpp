#pragma once

#include <Util/Math/Angle.hpp>

#include <algorithm>
#include <array>
#include <limits>
#include <cmath>
#include <type_traits>
#include <ostream>

namespace rlf
{
    template <class T>
    struct Vec2
    {
        union
        {
            std::array<T, 2> data = {};
            struct
            {
                T r, g;
            };
            struct
            {
                T x, y;
            };
            struct
            {
                T u, v;
            };
        };

        Vec2(T X = {}, T Y = {}) : x{X}, y{Y}
        {
        }
        ~Vec2()                      = default;
        Vec2(Vec2 const&)            = default;
        Vec2(Vec2&&)                 = default;
        Vec2& operator=(Vec2 const&) = default;
        Vec2& operator=(Vec2&&)      = default;

        static inline constexpr Vec2 Zero() { return Vec2(0, 0); }
        static inline constexpr Vec2 One() { return Vec2(1, 1); }
        static inline constexpr Vec2 Up() { return Vec2(0, 1); }
        static inline constexpr Vec2 Down() { return Vec2(0, -1); }
        static inline constexpr Vec2 Left() { return Vec2(-1, 0); }
        static inline constexpr Vec2 Right() { return Vec2(1, 0); }

        static inline constexpr Vec2 FromAngle(T const angleRad) { return {std::cos(angleRad), std::sin(angleRad)}; }

        inline constexpr auto& operator[](std::size_t const index)
        {
            return data[index];
        }

        inline constexpr auto const& operator[](std::size_t const Index) const
        {
            return data.at(Index);
        }

        constexpr bool operator==(Vec2 const& rhs) const
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                return std::abs(data[0] - rhs.data[0]) <= std::numeric_limits<T>::epsilon() &&
                       std::abs(data[1] - rhs.data[1]) <= std::numeric_limits<T>::epsilon();
            }
            else
            {
                return data == rhs.data;
            }
        }
        constexpr bool operator!=(Vec2 const& rhs) const
        {
            return !((*this) == rhs);
        }

        constexpr Vec2 operator-() const
        {
            return Vec2(-x, -y);
        }

        // Addition operators
        Vec2 operator+(Vec2 const& rhs) const
        {
            Vec2 v = *this;
            v += rhs;
            return v;
        }
        Vec2& operator+=(Vec2 const& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        // Subtraction operators
        Vec2 operator-(Vec2 const& rhs) const
        {
            Vec2 v = *this;
            v -= rhs;
            return v;
        }
        Vec2& operator-=(Vec2 const& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        // Multiply operators
        Vec2 operator*(Vec2 const& rhs) const
        {
            Vec2 v = *this;
            v *= rhs;
            return v;
        }
        Vec2& operator*=(Vec2 const& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            return *this;
        }
        Vec2 operator*(T const t) const
        {
            Vec2 v = *this;
            v *= t;
            return v;
        }
        Vec2& operator*=(T const t)
        {
            x *= t;
            y *= t;
            return *this;
        }

        // Division operators
        Vec2 operator/(Vec2 const& rhs) const
        {
            Vec2 v = *this;
            v /= rhs;
            return v;
        }
        Vec2& operator/=(Vec2 const& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            return *this;
        }
        Vec2 operator/(T const t) const
        {
            Vec2 v = *this;
            v /= t;
            return v;
        }
        Vec2& operator/=(T const t)
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                if (std::abs(t) <= std::numeric_limits<T>::epsilon())
                {
                    return *this;
                }
            }
            else
            {
                if (t == 0)
                {
                    return *this;
                }
            }
            x /= t;
            y /= t;
            return *this;
        }

        constexpr Vec2& Rotate(T const angleRad)
        {
            T const cosRes = std::cos(angleRad);
            T const sinRes = std::sin(angleRad);
            x              = x * cosRes - y * sinRes;
            y              = x * sinRes + y * cosRes;
            return *this;
        }

        constexpr Vec2 RotateBy(T const angleRad) const
        {
            Vec2 v = *this;
            v.Rotate(angleRad);
            return v;
        }

        constexpr T LengthSq() const
        {
            return (x * x) + (y * y);
        }

        constexpr T Length() const
        {
            return std::sqrt(LengthSq());
        }

        Vec2 Degrees() const
        {
            return rlf::Degrees((*this));
        }

        Vec2 Radians() const
        {
            return rlf::Radians((*this));
        }

        Vec2 Midpoint(Vec2 const& rhs) const
        {
            return (*this + rhs) / 2;
        }

        // Normalize this Vec2
        constexpr Vec2& Normalize()
        {
            *this /= Length();
            return *this;
        }

        // Returns a copy of this Vec2 normalized
        constexpr Vec2 Normalized() const
        {
            Vec2 v = *this;
            v.Normalize();
            return v;
        }

        // Returns a distance between two Vec2
        constexpr T Distance(Vec2 const& rhs) const
        {
            return (rhs - *this).Length();
        }

        // Returns a vector rotated 90 degrees counter-clockwise
        constexpr Vec2 Perpendicular() const
        {
            return Vec2(-y, x);
        }

        constexpr T Dot(Vec2 const& rhs) const
        {
            return (x * rhs.x) + (y * rhs.y);
        }

        constexpr T Cross(Vec2 const& rhs) const
        {
            return (x * rhs.y) - (y * rhs.x);
        }

        // Reflects this vector along normal, assumes that normal is already normalized
        constexpr Vec2 Reflect(Vec2 const& Normal) const
        {
            return *this - (Normal * (2 * Dot(Normal)));
        }

        constexpr Vec2 Project(Vec2 const& Other) const
        {
            T other_len_sq = Other.LengthSq();
            if constexpr (std::is_floating_point_v<T>)
            {
                if (abs(other_len_sq) <= std::numeric_limits<T>::epsilon())
                {
                    return Zero();
                }
            }
            else
            {
                if (other_len_sq == 0)
                {
                    return Zero();
                }
            }
            return Other * (Dot(Other) / other_len_sq);
        }

        constexpr T Angle(Vec2 const& Rhs) const
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                if (LengthSq() <= std::numeric_limits<T>::epsilon() || Rhs.LengthSq() <= std::numeric_limits<T>::epsilon())
                {
                    return T{};
                }
            }
            else
            {
                if (LengthSq() == 0 || Rhs.LengthSq() == 0)
                {
                    return T{};
                }
            }
            return std::atan2(Cross(Rhs), Dot(Rhs));
        }

        friend inline void to_json(rlf::Json& j, Vec2 const& v)
        {
            j["x"] = v.x;
            j["y"] = v.y;
        }
        friend inline void from_json(rlf::Json const& j, Vec2& v)
        {
            rlf::JsonGetSafe(j, "x", v.x);
            rlf::JsonGetSafe(j, "y", v.y);
        }
    };

    // Scalar multiplication free function for `scalar * Vec3`
    template <class T>
    inline constexpr Vec2<T> operator*(T const t, Vec2<T> const& v)
    {
        return v * t;
    }

    template <class T>
    inline constexpr Vec2<T> operator/(T const t, Vec2<T> const& v)
    {
        return Vec2<T>{t, t} / v;
    }

    using Vec2b = Vec2<bool>;
    using Vec2c = Vec2<u8>;
    using Vec2i = Vec2<i32>;
    using Vec2u = Vec2<u32>;
    using Vec2f = Vec2<f32>;
    using Vec2d = Vec2<f64>;
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, rlf::Vec2<T> const& v)
{
    os << '[' << v.x << ", " << v.y << ']';
    return os;
}
