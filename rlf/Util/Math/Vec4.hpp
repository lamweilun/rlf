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
    struct Vec4
    {
        union
        {
            std::array<T, 4> data = {};
            struct
            {
                T r, g, b, a;
            };
            struct
            {
                T x, y, z, w;
            };
            struct
            {
                T u, v, s, t;
            };
        };

        Vec4(T X = {}, T Y = {}, T Z = {}, T W = {}) : x{X}, y{Y}, z{Z}, w{W} {}
        ~Vec4()                      = default;
        Vec4(Vec4 const&)            = default;
        Vec4(Vec4&&)                 = default;
        Vec4& operator=(Vec4 const&) = default;
        Vec4& operator=(Vec4&&)      = default;

        static inline constexpr Vec4 Zero() { return Vec4(0, 0, 0, 0); }
        static inline constexpr Vec4 One() { return Vec4(1, 1, 1, 1); }
        static inline constexpr Vec4 ColorOne() { return Vec4(255, 255, 255, 255); }

        inline constexpr auto& operator[](std::size_t const index) { return data[index]; }

        inline constexpr auto const& operator[](std::size_t const Index) const { return data.at(Index); }

        constexpr bool operator==(Vec4 const& Rhs) const
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                return std::abs(data[0] - Rhs.data[0]) <= std::numeric_limits<T>::epsilon() &&
                       std::abs(data[1] - Rhs.data[1]) <= std::numeric_limits<T>::epsilon() &&
                       std::abs(data[2] - Rhs.data[2]) <= std::numeric_limits<T>::epsilon() &&
                       std::abs(data[3] - Rhs.data[3]) <= std::numeric_limits<T>::epsilon();
            }
            else
            {
                return data == Rhs.data;
            }
        }
        constexpr bool operator!=(Vec4 const& Rhs) const
        {
            return !((*this) == Rhs);
        }

        constexpr Vec4 operator-() const
        {
            return Vec4(-x, -y, -z, -w);
        }

        // Addition operators
        Vec4 operator+(Vec4 const& Rhs) const
        {
            Vec4 v = *this;
            v += Rhs;
            return v;
        }
        Vec4& operator+=(Vec4 const& Rhs)
        {
            x += Rhs.x;
            y += Rhs.y;
            z += Rhs.z;
            w += Rhs.w;
            return *this;
        }

        // Subtraction operators
        Vec4 operator-(Vec4 const& Rhs) const
        {
            Vec4 v = *this;
            v -= Rhs;
            return v;
        }
        Vec4& operator-=(Vec4 const& Rhs)
        {
            x -= Rhs.x;
            y -= Rhs.y;
            z -= Rhs.z;
            w -= Rhs.w;
            return *this;
        }

        // Multiply operators (component-wise)
        Vec4 operator*(Vec4 const& Rhs) const
        {
            Vec4 v = *this;
            v *= Rhs;
            return v;
        }
        Vec4& operator*=(Vec4 const& Rhs)
        {
            x *= Rhs.x;
            y *= Rhs.y;
            z *= Rhs.z;
            w *= Rhs.w;
            return *this;
        }
        Vec4 operator*(T const T_scalar) const
        {
            Vec4 v = *this;
            v *= T_scalar;
            return v;
        }
        Vec4& operator*=(T const T_scalar)
        {
            x *= T_scalar;
            y *= T_scalar;
            z *= T_scalar;
            w *= T_scalar;
            return *this;
        }

        // Division operators (component-wise)
        Vec4 operator/(Vec4 const& Rhs) const
        {
            Vec4 v = *this;
            v /= Rhs;
            return v;
        }
        Vec4& operator/=(Vec4 const& Rhs)
        {
            x /= Rhs.x;
            y /= Rhs.y;
            z /= Rhs.z;
            w /= Rhs.w;
            return *this;
        }
        Vec4 operator/(T const T_scalar) const
        {
            Vec4 v = *this;
            v /= T_scalar;
            return v;
        }
        Vec4& operator/=(T const T_scalar)
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                if (std::abs(T_scalar) <= std::numeric_limits<T>::epsilon())
                {
                    // For floating points, division by (near) zero typically results
                    // in infinity or NaN. Returning *this (no change) is one strategy,
                    // another might be to return zero() or throw an exception.
                    return *this;
                }
            }
            else
            {
                if (T_scalar == 0)
                {
                    // For integers, division by zero is undefined behavior.
                    // Returning *this (no change) is one strategy, another might
                    // be to throw an exception.
                    return *this;
                }
            }
            x /= T_scalar;
            y /= T_scalar;
            z /= T_scalar;
            w /= T_scalar;
            return *this;
        }

        constexpr T LengthSq() const
        {
            return (x * x) + (y * y) + (z * z) + (w * w);
        }

        constexpr T Length() const
        {
            return std::sqrt(LengthSq());
        }

        Vec4 Degrees() const
        {
            return rlf::Degrees((*this));
        }

        Vec4 Radians() const
        {
            return rlf::Radians((*this));
        }

        Vec4 Midpoint(Vec4 const& Rhs) const
        {
            return (*this + Rhs) / T{2};
        }

        // Normalize this Vec4
        constexpr Vec4& Normalize()
        {
            *this /= Length();
            return *this;
        }

        // Returns a copy of this Vec4 normalized
        constexpr Vec4 Normalized() const
        {
            Vec4 v = *this;
            v.Normalize();
            return v;
        }

        // Returns a distance between two Vec4
        constexpr T Distance(Vec4 const& Rhs) const
        {
            return (Rhs - *this).Length();
        }

        // Dot product (scalar)
        constexpr T Dot(Vec4 const& Rhs) const
        {
            return (x * Rhs.x) + (y * Rhs.y) + (z * Rhs.z) + (w * Rhs.w);
        }

        // Cross product is not typically defined for 4D vectors in the same way
        // as 3D (which produces a single perpendicular vector).
        // Removed to avoid misrepresenting its meaning.
        // If you need a generalized exterior product, it's a different concept.
        // constexpr Vec4 Cross(Vec4 const& Rhs) const { ... }

        // Reflects this vector along normal, assumes that normal is already normalized
        constexpr Vec4 Reflect(Vec4 const& Normal) const
        {
            return *this - (Normal * (T{2} * Dot(Normal)));
        }

        // Projects this vector onto another vector
        constexpr Vec4 Project(Vec4 const& Other) const
        {
            T other_len_sq = Other.LengthSq();
            if constexpr (std::is_floating_point_v<T>)
            {
                if (std::abs(other_len_sq) <= std::numeric_limits<T>::epsilon())
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

        constexpr T Angle(Vec4 const& Rhs) const
        {
            T d  = Dot(Rhs);
            T l1 = Length();
            T l2 = Rhs.Length();

            if constexpr (std::is_floating_point_v<T>)
            {
                if (std::abs(l1) < std::numeric_limits<T>::epsilon() ||
                    std::abs(l2) < std::numeric_limits<T>::epsilon())
                {
                    return Zero();
                }
            }
            else
            {
                if (l1 == 0 || l2 == 0)
                {
                    return Zero();
                }
            }

            T cos_theta = std::clamp(d / (l1 * l2), T{-1}, T{1});
            return std::acos(cos_theta);
        }

        friend inline void to_json(rlf::Json& j, Vec4 const& v)
        {
            j["x"] = v.x;
            j["y"] = v.y;
            j["z"] = v.z;
            j["w"] = v.w;
        }
        friend inline void from_json(rlf::Json const& j, Vec4& v)
        {
            rlf::JsonGetSafe(j, "x", v.x);
            rlf::JsonGetSafe(j, "y", v.y);
            rlf::JsonGetSafe(j, "z", v.z);
            rlf::JsonGetSafe(j, "w", v.w);
        }
    };

    // Scalar multiplication free function for `scalar * Vec4`
    template <class T>
    inline constexpr Vec4<T> operator*(T const t, Vec4<T> const& v)
    {
        return v * t;
    }

    template <class T>
    inline constexpr Vec4<T> operator/(T const t, Vec4<T> const& v)
    {
        return Vec2<T>{t, t, t, t} / v;
    }

    using Vec4b   = Vec4<bool>;
    using Vec4c   = Vec4<u8>;
    using Vec4i   = Vec4<i32>;
    using Vec4u   = Vec4<u32>;
    using Vec4f   = Vec4<f32>;
    using Vec4d   = Vec4<f64>;
    using Color4F = Vec4<f32>;
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, rlf::Vec4<T> const& v)
{
    os << '[' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ']';
    return os;
}
