#pragma once

namespace rlf::phys {

    // 2D BoundingBox and Circle Collision
    bool CheckCollisionBoxCircle(BoundingBox const& box,
                                 f32 const          rotationRad,
                                 Vector2 const&     circlePosition,
                                 f32 const&         circleRadius,
                                 Vector2&           collidedPoint,
                                 Vector2&           collidedNormal,
                                 Vector2&           collidedTangent,
                                 f32&               penetratingDepth);

    bool CheckCollisionBoxToBox(BoundingBox const& box1,
                                BoundingBox const& box2,
                                Vector2&           collidedPoint,
                                Vector2&           collidedNormal,
                                Vector2&           collidedTangent,
                                f32&               penetratingDepth);

    // 3D Lines Collision
    bool CheckCollisionLines(Vector3 const& l1Start, Vector3 const& l1End, Vector3 const& l2Start, Vector3 const& l2End);

    // 3D Line and Sphere Collision
    bool CheckCollisionLineSphere(Vector3 const& startPt, Vector3 const& endPt, Vector3 const& spherePos, f32 const sphereRadius);
}
