#pragma once

namespace rlf::phys
{

    // 2D BoundingBox and Circle Collision
    bool CheckCollisionBoxCircle(BoundingBox const& box,
                                 f32 const          rotationRad,
                                 rlf::Vec2f const&  circlePosition,
                                 f32 const&         circleRadius,
                                 rlf::Vec2f&        collidedPoint,
                                 rlf::Vec2f&        collidedNormal,
                                 rlf::Vec2f&        collidedTangent,
                                 f32&               penetratingDepth);

    bool CheckCollisionBoxToBox(BoundingBox const& box1,
                                f32 const          box1RotationRad,
                                BoundingBox const& box2,
                                f32 const          box2RotationRad,
                                rlf::Vec2f&        collidedPoint,
                                rlf::Vec2f&        collidedNormal,
                                rlf::Vec2f&        collidedTangent,
                                f32&               penetratingDepth);

    // 3D Lines Collision
    bool CheckCollisionLines(rlf::Vec3f const& l1Start, rlf::Vec3f const& l1End, rlf::Vec3f const& l2Start, rlf::Vec3f const& l2End);

    // 3D Line and Sphere Collision
    bool CheckCollisionLineSphere(rlf::Vec3f const& startPt, rlf::Vec3f const& endPt, rlf::Vec3f const& spherePos, f32 const sphereRadius);
}
