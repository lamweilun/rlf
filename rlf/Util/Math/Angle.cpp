#include <Util/Math/Angle.hpp>

#include <Util/Math/Vec2.hpp>
#include <Util/Math/Vec3.hpp>
#include <Util/Math/Vec4.hpp>

#include <numbers>

namespace rlf
{
    template <>
    f32 Degrees(f32 const& angleRad)
    {
        return angleRad * (180.0f / std::numbers::pi_v<f32>);
    }
    template <>
    f64 Degrees(f64 const& angleRad)
    {
        return angleRad * (180.0 / std::numbers::pi_v<f64>);
    }

    template <>
    Vec2f Degrees(Vec2f const& v)
    {
        return Vec2f{Degrees(v.x), Degrees(v.y)};
    }
    template <>
    Vec2d Degrees(Vec2d const& v)
    {
        return Vec2d{Degrees(v.x), Degrees(v.y)};
    }

    template <>
    Vec3f Degrees(Vec3f const& v)
    {
        return Vec3f{Degrees(v.x), Degrees(v.y), Degrees(v.z)};
    }
    template <>
    Vec3d Degrees(Vec3d const& v)
    {
        return Vec3d{Degrees(v.x), Degrees(v.y), Degrees(v.z)};
    }

    template <>
    Vec4f Degrees(Vec4f const& v)
    {
        return Vec4f{Degrees(v.x), Degrees(v.y), Degrees(v.z), Degrees(v.w)};
    }
    template <>
    Vec4d Degrees(Vec4d const& v)
    {
        return Vec4d{Degrees(v.x), Degrees(v.y), Degrees(v.z), Degrees(v.w)};
    }

    template <>
    f32 Radians(f32 const& angleDeg)
    {
        return angleDeg * (std::numbers::pi_v<f32> / 180.0f);
    }
    template <>
    f64 Radians(f64 const& angleDeg)
    {
        return angleDeg * (std::numbers::pi_v<f64> / 180.0);
    }

    template <>
    Vec2f Radians(Vec2f const& v)
    {
        return Vec2f{Radians(v.x), Radians(v.y)};
    }
    template <>
    Vec2d Radians(Vec2d const& v)
    {
        return Vec2d{Radians(v.x), Radians(v.y)};
    }

    template <>
    Vec3f Radians(Vec3f const& v)
    {
        return Vec3f{Radians(v.x), Radians(v.y), Radians(v.z)};
    }
    template <>
    Vec3d Radians(Vec3d const& v)
    {
        return Vec3d{Radians(v.x), Radians(v.y), Radians(v.z)};
    }

    template <>
    Vec4f Radians(Vec4f const& v)
    {
        return Vec4f{Radians(v.x), Radians(v.y), Radians(v.z), Radians(v.w)};
    }
    template <>
    Vec4d Radians(Vec4d const& v)
    {
        return Vec4d{Radians(v.x), Radians(v.y), Radians(v.z), Radians(v.w)};
    }
}
