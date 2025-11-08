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
    struct Vec3
    {
        union
        {
            std::array<T, 3> data = {};
            struct
            {
                T r, g, b;
            };
            struct
            {
                T x, y, z;
            };
            struct
            {
                T u, v, s;
            };
        };

        Vec3(T X = {}, T Y = {}, T Z = {}) : x{X}, y{Y}, z{Z} {}
        ~Vec3()                      = default;
        Vec3(Vec3 const&)            = default;
        Vec3(Vec3&&)                 = default;
        Vec3& operator=(Vec3 const&) = default;
        Vec3& operator=(Vec3&&)      = default;

        static inline constexpr Vec3 Zero() { return Vec3(0, 0, 0); }
        static inline constexpr Vec3 One() { return Vec3(1, 1, 1); }

        // Common directional vectors
        static inline constexpr Vec3 Forward() { return Vec3(0, 0, 1); }
        static inline constexpr Vec3 Back() { return Vec3(0, 0, -1); }
        static inline constexpr Vec3 Up() { return Vec3(0, 1, 0); }
        static inline constexpr Vec3 Down() { return Vec3(0, -1, 0); }
        static inline constexpr Vec3 Left() { return Vec3(-1, 0, 0); }
        static inline constexpr Vec3 Right() { return Vec3(1, 0, 0); }

        inline constexpr auto& operator[](std::size_t const index)
        {
            return data[index];
        }

        inline constexpr auto const& operator[](std::size_t const Index) const
        {
            return data.at(Index);
        }

        constexpr bool operator==(Vec3 const& rhs) const
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                return std::abs(data[0] - rhs.data[0]) <= std::numeric_limits<T>::epsilon() &&
                       std::abs(data[1] - rhs.data[1]) <= std::numeric_limits<T>::epsilon() &&
                       std::abs(data[2] - rhs.data[2]) <= std::numeric_limits<T>::epsilon();
            }
            else
            {
                return data == rhs.data;
            }
        }
        constexpr bool operator!=(Vec3 const& rhs) const
        {
            return !((*this) == rhs);
        }

        constexpr Vec3 operator-() const
        {
            return Vec3(-x, -y, -z);
        }

        // Addition operators
        Vec3 operator+(Vec3 const& rhs) const
        {
            Vec3 v = *this;
            v += rhs;
            return v;
        }
        Vec3& operator+=(Vec3 const& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        // Subtraction operators
        Vec3 operator-(Vec3 const& rhs) const
        {
            Vec3 v = *this;
            v -= rhs;
            return v;
        }
        Vec3& operator-=(Vec3 const& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        // Multiply operators (component-wise)
        Vec3 operator*(Vec3 const& rhs) const
        {
            Vec3 v = *this;
            v *= rhs;
            return v;
        }
        Vec3& operator*=(Vec3 const& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }
        Vec3 operator*(T const t) const
        {
            Vec3 v = *this;
            v *= t;
            return v;
        }
        Vec3& operator*=(T const t)
        {
            x *= t;
            y *= t;
            z *= t;
            return *this;
        }

        // Division operators (component-wise)
        Vec3 operator/(Vec3 const& rhs) const
        {
            Vec3 v = *this;
            v /= rhs;
            return v;
        }
        Vec3& operator/=(Vec3 const& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            return *this;
        }
        Vec3 operator/(T const t) const
        {
            Vec3 v = *this;
            v /= t;
            return v;
        }
        Vec3& operator/=(T const t)
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
            z /= t;
            return *this;
        }

        constexpr T LengthSq() const
        {
            return (x * x) + (y * y) + (z * z);
        }

        constexpr T Length() const
        {
            return std::sqrt(LengthSq());
        }

        Vec3 Degrees() const
        {
            return rlf::Degrees((*this));
        }

        Vec3 Radians() const
        {
            return rlf::Radians((*this));
        }

        Vec3 Midpoint(Vec3 const& rhs) const
        {
            return (*this + rhs) / 2;
        }

        // Normalize this Vec3
        constexpr Vec3& Normalize()
        {
            *this /= Length();
            return *this;
        }

        // Returns a copy of this Vec3 normalized
        constexpr Vec3 Normalized() const
        {
            Vec3 v = *this;
            v.Normalize();
            return v;
        }

        // Returns a distance between two Vec3
        constexpr T Distance(Vec3 const& rhs) const
        {
            return (rhs - *this).Length();
        }

        // Dot product (scalar)
        constexpr T Dot(Vec3 const& rhs) const
        {
            return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
        }

        // Cross product (returns a Vec3, perpendicular to both)
        constexpr Vec3 Cross(Vec3 const& rhs) const
        {
            return Vec3(
                (y * rhs.z) - (z * rhs.y),
                (z * rhs.x) - (x * rhs.z),
                (x * rhs.y) - (y * rhs.x));
        }

        // Reflects this vector along normal, assumes that normal is already normalized
        constexpr Vec3 Reflect(Vec3 const& Normal) const
        {
            return *this - (Normal * (2 * Dot(Normal)));
        }

        // Projects this vector onto another vector
        constexpr Vec3 Project(Vec3 const& Other) const
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

        constexpr T Angle(Vec3 const& rhs) const
        {
            T d  = Dot(rhs);
            T l1 = Length();
            T l2 = rhs.Length();

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

            T cos_theta = std::clamp(d / (l1 * l2), -1, 1);
            return std::acos(cos_theta);
        }

        friend inline void to_json(rlf::Json& j, Vec3 const& v)
        {
            j["x"] = v.x;
            j["y"] = v.y;
            j["z"] = v.z;
        }
        friend inline void from_json(rlf::Json const& j, Vec3& v)
        {
            rlf::JsonGetSafe(j, "x", v.x);
            rlf::JsonGetSafe(j, "y", v.y);
            rlf::JsonGetSafe(j, "z", v.z);
        }
    };

    // Scalar multiplication free function for `scalar * Vec3`
    template <class T>
    inline constexpr Vec3<T> operator*(T const t, Vec3<T> const& v)
    {
        return v * t;
    }

    template <class T>
    inline constexpr Vec3<T> operator/(T const t, Vec3<T> const& v)
    {
        return Vec3<T>{t, t, t} / v;
    }

    using Vec3b = Vec3<bool>;
    using Vec3c = Vec3<u8>;
    using Vec3i = Vec3<i32>;
    using Vec3u = Vec3<u32>;
    using Vec3f = Vec3<f32>;
    using Vec3d = Vec3<f64>;
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, rlf::Vec3<T> const& v)
{
    os << '[' << v.x << ", " << v.y << ", " << v.z << ']';
    return os;
}
