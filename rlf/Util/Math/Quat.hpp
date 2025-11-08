#pragma once

#include <array>
#include <cmath>
#include <limits>
#include <ostream>
#include <type_traits>

#include <Util/Math/Vec3.hpp>

namespace rlf
{
    template <class T>
    struct Quat
    {
        union
        {
            std::array<T, 4> data = {};
            struct
            {
                T x, y, z, w;
            };
        };

        // Constructor with components (x, y, z, w)
        Quat(T X = {}, T Y = {}, T Z = {}, T W = 1) : x{X}, y{Y}, z{Z}, w{W} {}

        // Constructor from an angle and axis
        // Axis must be normalized
        Quat(T const Angle_radians, Vec3<T> const& Axis)
        {
            T half_angle     = Angle_radians / static_cast<T>(2);
            T sin_half_angle = std::sin(half_angle);
            w                = std::cos(half_angle);
            x                = Axis.x * sin_half_angle;
            y                = Axis.y * sin_half_angle;
            z                = Axis.z * sin_half_angle;
        }

        // Default copy, move, assignment operators
        ~Quat()                      = default;
        Quat(Quat const&)            = default;
        Quat(Quat&&)                 = default;
        Quat& operator=(Quat const&) = default;
        Quat& operator=(Quat&&)      = default;

        // Static identity quaternion
        static inline constexpr Quat Identity() { return Quat(0, 0, 0, 1); }

        // Access operators
        inline constexpr T&       operator[](std::size_t const Index) { return data[Index]; }
        inline constexpr T const& operator[](std::size_t const Index) const { return data.at(Index); }

        // Equality operators (with epsilon for floating points)
        constexpr bool operator==(Quat const& rhs) const
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                return std::abs(data[0] - rhs.data[0]) <= std::numeric_limits<T>::epsilon() &&
                       std::abs(data[1] - rhs.data[1]) <= std::numeric_limits<T>::epsilon() &&
                       std::abs(data[2] - rhs.data[2]) <= std::numeric_limits<T>::epsilon() &&
                       std::abs(data[3] - rhs.data[3]) <= std::numeric_limits<T>::epsilon();
            }
            else
            {
                return data == rhs.data;
            }
        }
        constexpr bool operator!=(Quat const& rhs) const
        {
            return !((*this) == rhs);
        }

        // Unary negation (negates all components)
        constexpr Quat operator-() const
        {
            return Quat(-x, -y, -z, -w);
        }

        // Addition
        Quat operator+(Quat const& rhs) const
        {
            return Quat(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
        }
        Quat& operator+=(Quat const& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }

        // Subtraction
        Quat operator-(Quat const& rhs) const
        {
            return Quat(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
        }
        Quat& operator-=(Quat const& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }

        // Scalar Multiplication
        Quat operator*(T const T_scalar) const
        {
            return Quat(x * T_scalar, y * T_scalar, z * T_scalar, w * T_scalar);
        }
        Quat& operator*=(T const T_scalar)
        {
            x *= T_scalar;
            y *= T_scalar;
            z *= T_scalar;
            w *= T_scalar;
            return *this;
        }

        // Scalar Division
        Quat operator/(T const T_scalar) const
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                if (std::abs(T_scalar) <= std::numeric_limits<T>::epsilon())
                {
                    return *this;  // Or throw, or return Identity/zero
                }
            }
            else
            {
                if (T_scalar == 0)
                {
                    return *this;  // Or throw
                }
            }
            return Quat(x / T_scalar, y / T_scalar, z / T_scalar, w / T_scalar);
        }
        Quat& operator/=(T const T_scalar)
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                if (std::abs(T_scalar) <= std::numeric_limits<T>::epsilon())
                {
                    return *this;  // Or throw, or set to Identity/zero
                }
            }
            else
            {
                if (T_scalar == 0)
                {
                    return *this;  // Or throw
                }
            }
            x /= T_scalar;
            y /= T_scalar;
            z /= T_scalar;
            w /= T_scalar;
            return *this;
        }

        // Quaternion Multiplication (composition of rotations)
        // (q1 * q2) means applying q2 then q1
        Quat operator*(Quat const& rhs) const
        {
            return Quat(
                w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,  // New x
                w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,  // New y
                w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w,  // New z
                w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z   // New w
            );
        }
        Quat& operator*=(Quat const& rhs)
        {
            *this = (*this) * rhs;
            return *this;
        }

        // Dot product
        constexpr T Dot(Quat const& rhs) const
        {
            return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
        }

        // Length squared
        constexpr T LengthSq() const
        {
            return Dot(*this);
        }

        // Length (magnitude)
        constexpr T Length() const
        {
            return std::sqrt(LengthSq());
        }

        // Normalize this quaternion (mutating)
        constexpr Quat& Normalize()
        {
            T len = Length();
            if constexpr (std::is_floating_point_v<T>)
            {
                if (std::abs(len) <= std::numeric_limits<T>::epsilon())
                {
                    return *this;  // Cannot Normalize zero-length quaternion
                }
            }
            else
            {
                if (len == static_cast<T>(0))
                {
                    return *this;
                }
            }
            *this /= len;
            return *this;
        }

        // Returns a copy of this quaternion normalized
        constexpr Quat Normalized() const
        {
            Quat q = *this;
            q.Normalize();
            return q;
        }

        // Conjugate of the quaternion
        constexpr Quat Conjugate() const
        {
            return Quat(-x, -y, -z, w);
        }

        // Inverse of the quaternion
        // For unit quaternions, inverse is just the Conjugate.
        // For non-unit quaternions, inverse = Conjugate / LengthSq
        constexpr Quat Inverse() const
        {
            T len_sq = LengthSq();
            if constexpr (std::is_floating_point_v<T>)
            {
                if (std::abs(len_sq) <= std::numeric_limits<T>::epsilon())
                {
                    return Identity();  // Cannot invert zero-length quaternion
                }
            }
            else
            {
                if (len_sq == static_cast<T>(0))
                {
                    return Identity();
                }
            }
            return Conjugate() / len_sq;
        }

        // Rotate a 3D vector by this quaternion
        // Requires Vec3 definition
        Vec3<T> Rotate(Vec3<T> const& V) const
        {
            // Equivalent to q * Vec4(V.x, V.y, V.z, 0) * q.Inverse()
            // For unit quaternions, inverse is Conjugate.
            // The optimized formula: t = 2 * cross(q.xyz, V); V_rotated = V + w * t + cross(q.xyz, t);

            // Create a quaternion from the vector, with w=0
            Quat<T> p(V.x, V.y, V.z, static_cast<T>(0));

            // Perform the rotation: q * p * q_inverse
            Quat<T> rotated_q = (*this) * p * this->Conjugate();

            return rlf::Vec3<T>(rotated_q.x, rotated_q.y, rotated_q.z);
        }

        // Convert quaternion to Euler angles (roll, pitch, yaw) in radians
        // Yaw (Z-axis), Pitch (Y-axis), Roll (X-axis)
        // Beware of gimbal lock for certain rotations.
        // Returns a Vec3 where x=roll, y=pitch, z=yaw
        Vec3<T> ToEulerAngles() const
        {
            rlf::Vec3<T> angles;

            // roll (x-axis rotation)
            T sinr_cosp = static_cast<T>(2) * (w * x + y * z);
            T cosr_cosp = static_cast<T>(1) - static_cast<T>(2) * (x * x + y * y);
            angles.x    = std::atan2(sinr_cosp, cosr_cosp);

            // pitch (y-axis rotation)
            T sinp = static_cast<T>(2) * (w * y - z * x);
            if (std::abs(sinp) >= static_cast<T>(1))
            {
                angles.y = std::copysign(M_PI_2, sinp);  // Use 90 degrees if out of range
            }
            else
            {
                angles.y = std::asin(sinp);
            }

            // yaw (z-axis rotation)
            T siny_cosp = static_cast<T>(2) * (w * z + x * y);
            T cosy_cosp = static_cast<T>(1) - static_cast<T>(2) * (y * y + z * z);
            angles.z    = std::atan2(siny_cosp, cosy_cosp);

            return angles;
        }

        static Quat FromEulerAngles(T const Roll_rad, T const Pitch_rad, T const Yaw_rad)
        {
            T cy = std::cos(Yaw_rad * static_cast<T>(0.5));
            T sy = std::sin(Yaw_rad * static_cast<T>(0.5));
            T cp = std::cos(Pitch_rad * static_cast<T>(0.5));
            T sp = std::sin(Pitch_rad * static_cast<T>(0.5));
            T cr = std::cos(Roll_rad * static_cast<T>(0.5));
            T sr = std::sin(Roll_rad * static_cast<T>(0.5));

            Quat q;
            q.w = cr * cp * cy + sr * sp * sy;
            q.x = sr * cp * cy - cr * sp * sy;
            q.y = cr * sp * cy + sr * cp * sy;
            q.z = cr * cp * sy - sr * sp * cy;

            return q;
        }

        static Quat FromEulerAngles(Vec3<T> const& Euler_angles_rad)
        {
            return FromEulerAngles(Euler_angles_rad.x, Euler_angles_rad.y, Euler_angles_rad.z);
        }

        // Convert quaternion to a 4x4 rotation matrix
        // (assuming column-major or row-major as per common graphics APIs)
        // Returns std::array<T, 16> for a 4x4 matrix
        std::array<T, 16> ToMatrix() const
        {
            std::array<T, 16> m = {
                static_cast<T>(0)};  // Initialize to zero

            T x2 = x * x;
            T y2 = y * y;
            T z2 = z * z;
            T xy = x * y;
            T xz = x * z;
            T yz = y * z;
            T wx = w * x;
            T wy = w * y;
            T wz = w * z;

            // Column-major order (OpenGL/GLSL style)
            m[0] = static_cast<T>(1) - static_cast<T>(2) * (y2 + z2);
            m[1] = static_cast<T>(2) * (xy + wz);
            m[2] = static_cast<T>(2) * (xz - wy);
            m[3] = static_cast<T>(0);

            m[4] = static_cast<T>(2) * (xy - wz);
            m[5] = static_cast<T>(1) - static_cast<T>(2) * (x2 + z2);
            m[6] = static_cast<T>(2) * (yz + wx);
            m[7] = static_cast<T>(0);

            m[8]  = static_cast<T>(2) * (xz + wy);
            m[9]  = static_cast<T>(2) * (yz - wx);
            m[10] = static_cast<T>(1) - static_cast<T>(2) * (x2 + y2);
            m[11] = static_cast<T>(0);

            m[12] = static_cast<T>(0);
            m[13] = static_cast<T>(0);
            m[14] = static_cast<T>(0);
            m[15] = static_cast<T>(1);

            return m;
        }

        friend inline void to_json(rlf::Json& j, Quat const& v)
        {
            j["x"] = v.x;
            j["y"] = v.y;
            j["z"] = v.z;
            j["w"] = v.w;
        }
        friend inline void from_json(rlf::Json const& j, Quat& v)
        {
            rlf::JsonGetSafe(j, "x", v.x);
            rlf::JsonGetSafe(j, "y", v.y);
            rlf::JsonGetSafe(j, "z", v.z);
            rlf::JsonGetSafe(j, "w", v.w);
        }
    };

    // Scalar multiplication free function for `scalar * Quat`
    template <class T>
    inline constexpr Quat<T> operator*(T const t, Quat<T> const& q)
    {
        return q * t;
    }

    // Type aliases
    using quatf = Quat<f32>;
    using quatd = Quat<f64>;
}

// Stream output for Quat
template <class T>
inline std::ostream& operator<<(std::ostream& os, rlf::Quat<T> const& q)
{
    os << '[' << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ']';
    return os;
}
