#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <ostream>
#include <type_traits>

#include <Util/Math/Vec3.hpp>
#include <Util/Math/Vec4.hpp>
#include <Util/Math/Quat.hpp>

// Assuming these types are defined in val namespace or globally
// For demonstration, defining them here if not already available.
namespace rlf
{
    template <class T>
    struct Mat4
    {
        // Column-major storage: vecs[column_index] is a Vec4 representing that column
        union
        {
            std::array<T, 16>      data;  // For raw data access when needed (e.g., passing to GPU)
            std::array<Vec4<T>, 4> vecs;  // Array of column vectors
        };

        // Default constructor: Identity matrix
        // Constructor with a single scalar value for all diagonal elements
        explicit Mat4(T const s = T{1}) : vecs{}
        {                   // Initialize vecs (all components to 0 by default)
            vecs[0].x = s;  // vecs[0] is the first column, x is m00
            vecs[1].y = s;  // vecs[1] is the second column, y is m11
            vecs[2].z = s;  // vecs[2] is the third column, z is m22
            vecs[3].w = s;  // vecs[3] is the fourth column, w is m33
        }

        // Constructor with 16 components (column-major order expected)
        Mat4(T m00, T m10, T m20, T m30,  // Col 0
             T m01, T m11, T m21, T m31,  // Col 1
             T m02, T m12, T m22, T m32,  // Col 2
             T m03, T m13, T m23, T m33   // Col 3
             ) : vecs{Vec4<T>(m00, m10, m20, m30),
                      Vec4<T>(m01, m11, m21, m31),
                      Vec4<T>(m02, m12, m22, m32),
                      Vec4<T>(m03, m13, m23, m33)}
        {
        }

        // Constructor from an array of 16 elements (converts to Vec4 array implicitly)
        explicit Mat4(std::array<T, 16> const& arr) : data(arr) {}

        // Constructor from an array of vec4s
        explicit Mat4(std::array<Vec4<T>, 4> const& v_arr) : vecs(v_arr) {}

        // Default copy, move, assignment
        ~Mat4()                      = default;
        Mat4(Mat4 const&)            = default;
        Mat4(Mat4&&)                 = default;
        Mat4& operator=(Mat4 const&) = default;
        Mat4& operator=(Mat4&&)      = default;

        // Static identity matrix
        static inline constexpr Mat4 identity() { return Mat4(T{1}); }

        // Column access operator
        inline constexpr Vec4<T>&       operator[](std::size_t index) { return vecs[index]; }
        inline constexpr Vec4<T> const& operator[](std::size_t index) const { return vecs[index]; }

        // Row access (returns a Vec4 representing the row)
        // Note: This returns a copy, not a reference to the underlying storage directly
        // This now correctly accesses components of each column vector.
        inline constexpr rlf::Vec4<T> row(std::size_t const r) const
        {
            return rlf::Vec4<T>(vecs[0][r], vecs[1][r], vecs[2][r], vecs[3][r]);
        }

        // Equality operators (with epsilon for floating points)
        constexpr bool operator==(Mat4 const& rhs) const
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                // Compare each Vec4 (column) using its operator== if available and uses epsilon
                // Otherwise, iterate data as before
                for (std::size_t i = 0; i < 4; ++i)
                {
                    if (!(vecs[i] == rhs.vecs[i]))
                    {  // Assumes Vec4::operator== handles epsilon
                        return false;
                    }
                }
                return true;
            }
            else
            {
                return vecs == rhs.vecs;  // Default array comparison (component-wise ==)
            }
        }
        constexpr bool operator!=(Mat4 const& rhs) const
        {
            return !((*this) == rhs);
        }

        // Unary negation
        constexpr Mat4 operator-() const
        {
            Mat4 result;
            for (std::size_t i = 0; i < 4; ++i)
            {
                result.vecs[i] = -vecs[i];  // Assumes Vec4::operator-()
            }
            return result;
        }

        // Matrix-Matrix Addition
        Mat4 operator+(Mat4 const& rhs) const
        {
            Mat4 result;
            for (std::size_t i = 0; i < 4; ++i)
            {
                result.vecs[i] = vecs[i] + rhs.vecs[i];  // Assumes Vec4::operator+
            }
            return result;
        }
        Mat4& operator+=(Mat4 const& rhs)
        {
            for (std::size_t i = 0; i < 4; ++i)
            {
                vecs[i] += rhs.vecs[i];  // Assumes Vec4::operator+=
            }
            return *this;
        }

        // Matrix-Matrix Subtraction
        Mat4 operator-(Mat4 const& rhs) const
        {
            Mat4 result;
            for (std::size_t i = 0; i < 4; ++i)
            {
                result.vecs[i] = vecs[i] - rhs.vecs[i];  // Assumes Vec4::operator-
            }
            return result;
        }
        Mat4& operator-=(Mat4 const& rhs)
        {
            for (std::size_t i = 0; i < 4; ++i)
            {
                vecs[i] -= rhs.vecs[i];  // Assumes Vec4::operator-=
            }
            return *this;
        }

        // Matrix-Scalar Multiplication
        Mat4 operator*(T const t) const
        {
            Mat4 result;
            for (std::size_t i = 0; i < 4; ++i)
            {
                result.vecs[i] = vecs[i] * t;  // Assumes Vec4::operator* (scalar)
            }
            return result;
        }
        Mat4& operator*=(T const t)
        {
            for (std::size_t i = 0; i < 4; ++i)
            {
                vecs[i] *= t;  // Assumes Vec4::operator*= (scalar)
            }
            return *this;
        }

        // Matrix-Scalar Division
        Mat4 operator/(T const t) const
        {
            Mat4 result;
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
            for (std::size_t i = 0; i < 4; ++i)
            {
                result.vecs[i] = vecs[i] / t;  // Assumes Vec4::operator/ (scalar)
            }
            return result;
        }
        Mat4& operator/=(T const t)
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
            for (std::size_t i = 0; i < 4; ++i)
            {
                vecs[i] /= t;  // Assumes Vec4::operator/= (scalar)
            }
            return *this;
        }

        // Matrix-Matrix Multiplication
        // C[col_idx] = A * B[col_idx]
        Mat4 operator*(Mat4 const& rhs) const
        {
            Mat4 result;
            for (std::size_t c = 0; c < 4; ++c)
            {                                            // For each column of the result matrix
                result.vecs[c] = (*this) * rhs.vecs[c];  // This calls Mat4 * Vec4
            }
            return result;
        }
        Mat4& operator*=(Mat4 const& rhs)
        {
            *this = (*this) * rhs;
            return *this;
        }

        // Matrix-Vector Multiplication (Vec4)
        // M * V = [ R0.V, R1.V, R2.V, R3.V ]
        rlf::Vec4<T> operator*(rlf::Vec4<T> const& v) const
        {
            return rlf::Vec4<T>(
                row(0).dot(v),  // R0 . V
                row(1).dot(v),  // R1 . V
                row(2).dot(v),  // R2 . V
                row(3).dot(v)   // R3 . V
            );
        }

        // Transpose (mutating)
        Mat4& transpose()
        {
            for (std::size_t r = 0; r < 4; ++r)
            {
                for (std::size_t c = r + 1; c < 4; ++c)
                {
                    std::swap(vecs[c][r], vecs[r][c]);  // Swap (r,c) with (c,r)
                }
            }
            return *this;
        }

        // Returns a transposed copy
        constexpr Mat4 transposed() const
        {
            Mat4 result;  // Default constructs to identity, we'll overwrite
            for (std::size_t r = 0; r < 4; ++r)
            {
                for (std::size_t c = 0; c < 4; ++c)
                {
                    result.vecs[r][c] = vecs[c][r];  // result(r,c) = this(c,r)
                }
            }
            return result;
        }

        // Determinant (using Laplace expansion/cofactor method)
        // This remains mostly the same, but access pattern is updated to vecs[col][row]
        constexpr T determinant() const
        {
            // Access: vecs[column][row]
            // This makes (row, col) = vecs[col][row]

            T C00 = vecs[2][2] * vecs[3][3] - vecs[2][3] * vecs[3][2];
            T C01 = vecs[1][2] * vecs[3][3] - vecs[1][3] * vecs[3][2];
            T C02 = vecs[1][2] * vecs[2][3] - vecs[1][3] * vecs[2][2];  // Fixed: C02 should be (2,1)(3,2) - (2,2)(3,1)

            T C10 = vecs[2][1] * vecs[3][3] - vecs[2][3] * vecs[3][1];
            T C11 = vecs[1][1] * vecs[3][3] - vecs[1][3] * vecs[3][1];
            T C12 = vecs[1][1] * vecs[2][3] - vecs[1][3] * vecs[2][1];

            T C20 = vecs[2][0] * vecs[3][3] - vecs[2][3] * vecs[3][0];
            T C21 = vecs[1][0] * vecs[3][3] - vecs[1][3] * vecs[3][0];
            T C22 = vecs[1][0] * vecs[2][3] - vecs[1][3] * vecs[2][0];

            T C30 = vecs[2][0] * vecs[3][2] - vecs[2][2] * vecs[3][0];
            T C31 = vecs[1][0] * vecs[3][2] - vecs[1][2] * vecs[3][0];
            T C32 = vecs[1][0] * vecs[2][2] - vecs[1][2] * vecs[2][0];

            // Compute 3x3 determinants from the first column (col 0)
            // determinant = vecs[0][0] * cofactor(0,0) - vecs[0][1] * cofactor(1,0) + ...
            // Using `vecs[col][row]` for the access
            return vecs[0][0] * (vecs[1][1] * (vecs[2][2] * vecs[3][3] - vecs[2][3] * vecs[3][2]) -   // + m11 * (m22 m33 - m23 m32)
                                 vecs[1][2] * (vecs[2][1] * vecs[3][3] - vecs[2][3] * vecs[3][1]) +   // - m12 * (m21 m33 - m23 m31)
                                 vecs[1][3] * (vecs[2][1] * vecs[3][2] - vecs[2][2] * vecs[3][1])) -  // + m13 * (m21 m32 - m22 m31)
                   vecs[0][1] * (vecs[1][0] * (vecs[2][2] * vecs[3][3] - vecs[2][3] * vecs[3][2]) -
                                 vecs[1][2] * (vecs[2][0] * vecs[3][3] - vecs[2][3] * vecs[3][0]) +
                                 vecs[1][3] * (vecs[2][0] * vecs[3][2] - vecs[2][2] * vecs[3][0])) +
                   vecs[0][2] * (vecs[1][0] * (vecs[2][1] * vecs[3][3] - vecs[2][3] * vecs[3][1]) -
                                 vecs[1][1] * (vecs[2][0] * vecs[3][3] - vecs[2][3] * vecs[3][0]) +
                                 vecs[1][3] * (vecs[2][0] * vecs[3][1] - vecs[2][1] * vecs[3][0])) -
                   vecs[0][3] * (vecs[1][0] * (vecs[2][1] * vecs[3][2] - vecs[2][2] * vecs[3][1]) -
                                 vecs[1][1] * (vecs[2][0] * vecs[3][2] - vecs[2][2] * vecs[3][0]) +
                                 vecs[1][2] * (vecs[2][0] * vecs[3][1] - vecs[2][1] * vecs[3][0]));
        }

        // Inverse of the matrix (using adjugate matrix and determinant)
        constexpr Mat4 inverse() const
        {
            if constexpr (std::is_floating_point_v<T>)
            {
                T det = determinant();
                if (std::abs(det) <= std::numeric_limits<T>::epsilon())
                {
                    return identity();
                }

                Mat4 result;
                T    inv_det = static_cast<T>(1) / det;

                // Using the full data array for convenience in this complex calculation
                // to minimize changes from the original (correct) inverse logic.
                // This is equivalent to data[col * 4 + row] in the previous version.
                std::array<T, 16> const& d = data;

                // Row 0 of inverse (Column 0 of adjugate)
                result.vecs[0][0] = inv_det * (d[5] * (d[10] * d[15] - d[11] * d[14]) - d[9] * (d[6] * d[15] - d[7] * d[14]) + d[13] * (d[6] * d[11] - d[7] * d[10]));
                result.vecs[0][1] = inv_det * (d[9] * (d[2] * d[15] - d[3] * d[14]) - d[1] * (d[10] * d[15] - d[11] * d[14]) - d[13] * (d[2] * d[11] - d[3] * d[10]));
                result.vecs[0][2] = inv_det * (d[1] * (d[6] * d[15] - d[7] * d[14]) - d[5] * (d[2] * d[15] - d[3] * d[14]) + d[13] * (d[2] * d[7] - d[3] * d[6]));
                result.vecs[0][3] = inv_det * (d[5] * (d[2] * d[11] - d[3] * d[10]) - d[1] * (d[6] * d[11] - d[7] * d[10]) - d[9] * (d[2] * d[7] - d[3] * d[6]));

                // Row 1 of inverse (Column 1 of adjugate)
                result.vecs[1][0] = inv_det * (d[8] * (d[6] * d[15] - d[7] * d[14]) - d[4] * (d[10] * d[15] - d[11] * d[14]) - d[12] * (d[6] * d[11] - d[7] * d[10]));
                result.vecs[1][1] = inv_det * (d[0] * (d[10] * d[15] - d[11] * d[14]) - d[8] * (d[2] * d[15] - d[3] * d[14]) + d[12] * (d[2] * d[11] - d[3] * d[10]));
                result.vecs[1][2] = inv_det * (d[4] * (d[2] * d[15] - d[3] * d[14]) - d[0] * (d[6] * d[15] - d[7] * d[14]) - d[12] * (d[2] * d[7] - d[3] * d[6]));
                result.vecs[1][3] = inv_det * (d[0] * (d[6] * d[11] - d[7] * d[10]) - d[4] * (d[2] * d[11] - d[3] * d[10]) + d[8] * (d[2] * d[7] - d[3] * d[6]));

                // Row 2 of inverse (Column 2 of adjugate)
                result.vecs[2][0] = inv_det * (d[4] * (d[10] * d[15] - d[11] * d[14]) - d[8] * (d[6] * d[15] - d[7] * d[14]) + d[12] * (d[6] * d[11] - d[7] * d[10]));  // Fix: C02 was used for row(2,0)
                result.vecs[2][1] = inv_det * (d[8] * (d[2] * d[15] - d[3] * d[14]) - d[0] * (d[10] * d[15] - d[11] * d[14]) - d[12] * (d[2] * d[11] - d[3] * d[10]));  // Fix: C12 was used for row(2,1)
                result.vecs[2][2] = inv_det * (d[0] * (d[6] * d[15] - d[7] * d[14]) - d[4] * (d[2] * d[15] - d[3] * d[14]) + d[12] * (d[2] * d[7] - d[3] * d[6]));      // Fix: C22 was used for row(2,2)
                result.vecs[2][3] = inv_det * (d[4] * (d[2] * d[11] - d[3] * d[10]) - d[0] * (d[6] * d[11] - d[7] * d[10]) + d[8] * (d[2] * d[7] - d[3] * d[6]));       // Fix: C32 was used for row(2,3)

                // Row 3 of inverse (Column 3 of adjugate)
                result.vecs[3][0] = inv_det * (d[8] * (d[6] * d[11] - d[7] * d[10]) - d[4] * (d[10] * d[15] - d[11] * d[14]) - d[12] * (d[6] * d[11] - d[7] * d[10]));  // Fix: This was result(0,3)
                result.vecs[3][1] = inv_det * (d[0] * (d[10] * d[15] - d[11] * d[14]) - d[8] * (d[2] * d[15] - d[3] * d[14]) + d[12] * (d[2] * d[11] - d[3] * d[10]));  // Fix: This was result(1,3)
                result.vecs[3][2] = inv_det * (d[4] * (d[2] * d[15] - d[3] * d[14]) - d[0] * (d[6] * d[15] - d[7] * d[14]) - d[12] * (d[2] * d[7] - d[3] * d[6]));      // Fix: This was result(2,3)
                result.vecs[3][3] = inv_det * (d[0] * (d[6] * d[11] - d[7] * d[10]) - d[4] * (d[2] * d[11] - d[3] * d[10]) + d[8] * (d[2] * d[7] - d[3] * d[6]));       // Fix: This was result(3,3)

                return result;
            }
            else
            {
                return identity();
            }
        }

        // --- Static Transformation Matrix Creators ---

        // Translation Matrix
        static constexpr Mat4 translation(T const x, T const y, T const z)
        {
            Mat4 m;  // Starts as identity
            m.vecs[3].x = x;
            m.vecs[3].y = y;
            m.vecs[3].z = z;
            return m;
        }
        static constexpr Mat4 translation(rlf::Vec3<T> const& v)
        {
            return translation(v.x, v.y, v.z);
        }

        // Scaling Matrix
        static constexpr Mat4 scale(T const x, T const y, T const z)
        {
            Mat4 m;  // Starts as identity
            m.vecs[0].x = x;
            m.vecs[1].y = y;
            m.vecs[2].z = z;
            return m;
        }
        static constexpr Mat4 scale(rlf::Vec3<T> const& v)
        {
            return scale(v.x, v.y, v.z);
        }

        // Rotation Matrix from Euler Angles (roll, pitch, yaw) in radians
        // Order of application: Z (yaw), then Y (pitch), then X (roll)
        static Mat4 rotation(T const roll_rad, T const pitch_rad, T const yaw_rad)
        {
            Mat4 rx, ry, rz;
            T    cos_r = std::cos(roll_rad);
            T    sin_r = std::sin(roll_rad);
            T    cos_p = std::cos(pitch_rad);
            T    sin_p = std::sin(pitch_rad);
            T    cos_y = std::cos(yaw_rad);
            T    sin_y = std::sin(yaw_rad);

            // Rotation around X-axis (Roll)
            rx.vecs[1].y = cos_r;
            rx.vecs[2].y = -sin_r;
            rx.vecs[1].z = sin_r;
            rx.vecs[2].z = cos_r;

            // Rotation around Y-axis (Pitch)
            ry.vecs[0].x = cos_p;
            ry.vecs[2].x = sin_p;
            ry.vecs[0].z = -sin_p;
            ry.vecs[2].z = cos_p;

            // Rotation around Z-axis (Yaw)
            rz.vecs[0].x = cos_y;
            rz.vecs[1].x = -sin_y;
            rz.vecs[0].y = sin_y;
            rz.vecs[1].y = cos_y;

            // Combine rotations: Z then Y then X (R = Rx * Ry * Rz)
            return rx * ry * rz;
        }
        static Mat4 rotation(rlf::Vec3<T> const& euler_angles_rad)
        {
            return rotation(euler_angles_rad.x, euler_angles_rad.y,
                            euler_angles_rad.z);
        }

        // Rotation Matrix from an axis and angle
        // Axis must be normalized! Angle in radians.
        static Mat4 rotation(T const angle_rad, rlf::Vec3<T> const& axis)
        {
            Mat4 m;  // Starts as identity
            T    c   = std::cos(angle_rad);
            T    s   = std::sin(angle_rad);
            T    omc = static_cast<T>(1) - c;

            T x = axis.x;
            T y = axis.y;
            T z = axis.z;

            m.vecs[0].x = x * x * omc + c;
            m.vecs[0].y = y * x * omc + z * s;
            m.vecs[0].z = z * x * omc - y * s;
            m.vecs[0].w = static_cast<T>(0);  // Explicitly set if not default 0

            m.vecs[1].x = x * y * omc - z * s;
            m.vecs[1].y = y * y * omc + c;
            m.vecs[1].z = z * y * omc + x * s;
            m.vecs[1].w = static_cast<T>(0);

            m.vecs[2].x = x * z * omc + y * s;
            m.vecs[2].y = y * z * omc - x * s;
            m.vecs[2].z = z * z * omc + c;
            m.vecs[2].w = static_cast<T>(0);

            m.vecs[3].x = static_cast<T>(0);
            m.vecs[3].y = static_cast<T>(0);
            m.vecs[3].z = static_cast<T>(0);
            m.vecs[3].w = static_cast<T>(1);

            return m;
        }

        // Rotation Matrix from a Quaternion
        // Assumes Quat::toMatrix() exists and returns a 4x4 array in column-major.
        static Mat4 rotation(rlf::Quat<T> const& q)
        {
            return Mat4(q.to_matrix());
        }

        // Perspective Projection Matrix
        // fov_y_rad: vertical field of view in radians
        // aspect_ratio: width / height
        // near_plane: distance to near clipping plane (positive value)
        // far_plane: distance to far clipping plane (positive value)
        static Mat4 perspective(T const fov_y_rad, T const aspect_ratio, T const near_plane, T const far_plane)
        {
            Mat4 m{};  // Starts as zero matrix
            T    tan_half_fov_y = std::tan(fov_y_rad / static_cast<T>(2));
            T    f              = static_cast<T>(1) / tan_half_fov_y;

            m.vecs[0].x = f / aspect_ratio;
            m.vecs[1].y = f;
            m.vecs[2].z = (far_plane + near_plane) / (near_plane - far_plane);
            m.vecs[3].z = (static_cast<T>(2) * far_plane * near_plane) /
                          (near_plane - far_plane);
            m.vecs[2].w = static_cast<T>(-1);
            m.vecs[3].w = static_cast<T>(0);  // Explicitly set homogeneous component
            return m;
        }

        // Orthographic Projection Matrix
        static Mat4 orthographic(T const left, T const right, T const bottom,
                                 T const top, T const near_plane, T const far_plane)
        {
            Mat4 m(static_cast<T>(1));  // Start with identity
            m.vecs[0].x = static_cast<T>(2) / (right - left);
            m.vecs[1].y = static_cast<T>(2) / (top - bottom);
            m.vecs[2].z = static_cast<T>(-2) / (far_plane - near_plane);
            m.vecs[3].x = -(right + left) / (right - left);
            m.vecs[3].y = -(top + bottom) / (top - bottom);
            m.vecs[3].z = -(far_plane + near_plane) / (far_plane - near_plane);
            m.vecs[3].w = static_cast<T>(1);  // Ensure last component is 1
            return m;
        }

        // View Matrix (LookAt)
        // eye: Position of the camera
        // center: Point the camera is looking at
        // up: Up direction of the camera (should be normalized)
        static Mat4 lookAt(rlf::Vec3<T> const& eye, rlf::Vec3<T> const& center,
                           rlf::Vec3<T> const& up)
        {
            // Calculate camera's coordinate system axes
            rlf::Vec3<T> f =
                (center - eye) * static_cast<T>(-1);  // Forward vector (opposite of target-eye)
            f.normalize();

            rlf::Vec3<T> s = f.cross(up);  // Side vector
            s.normalize();

            rlf::Vec3<T> u = s.cross(f);  // Up vector (orthogonalized)

            Mat4 result;  // Starts as identity, will be overwritten
            // First, create a rotation matrix from the camera's axes
            // (transposed, as we're converting world to camera space)
            result.vecs[0].x = s.x;
            result.vecs[0].y = u.x;
            result.vecs[0].z = -f.x;  // Negative f for right-handed coordinate system in OpenGL

            result.vecs[1].x = s.y;
            result.vecs[1].y = u.y;
            result.vecs[1].z = -f.y;

            result.vecs[2].x = s.z;
            result.vecs[2].y = u.z;
            result.vecs[2].z = -f.z;

            // Then, apply translation for the camera's position (negative eye coordinates)
            result.vecs[3].x = -s.dot(eye);
            result.vecs[3].y = -u.dot(eye);
            result.vecs[3].z = f.dot(eye);         // This is -(-f).dot(eye) which is f.dot(eye)
            result.vecs[3].w = static_cast<T>(1);  // Ensure this is 1 for homogeneous coordinates

            return result;
        }
    };

    // Scalar multiplication free function for `scalar * Mat4`
    template <class T>
    inline constexpr Mat4<T> operator*(T const t, Mat4<T> const& m)
    {
        return m * t;
    }

    // Type aliases
    using Mat4f = rlf::Mat4<f32>;
    using Mat4d = rlf::Mat4<f64>;
}

// Stream output for Mat4 (formatted for readability)
template <class T>
inline std::ostream& operator<<(std::ostream& os, rlf::Mat4<T> const& m)
{
    os << "[\n";
    for (std::size_t r = 0; r < 4; ++r)
    {
        os << "  [";
        for (std::size_t c = 0; c < 4; ++c)
        {
            os << m[c][r] << (c == 3 ? "" : ", ");
        }
        os << "]" << (r == 3 ? "" : ",") << "\n";
    }
    os << "]";
    return os;
}
