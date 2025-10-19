#include <memory>
#include <Util/Physics/CollisionDetection.hpp>

#ifndef SIGN
#define SIGN(x) ((x) > 0 ? 1.0f : ((x) < 0 ? -1.0f : 0.0f))
#endif

namespace {
    // Assuming BoundingBox is defined similar to raylib's BoundingBox,
    // but for 2D, or we can adapt it. Let's use a custom struct for 2D.
    // This assumes `min` and `max` define the AABB of the box *before* rotation.
    struct BoundingBox2D {
        Vector2 min;
        Vector2 max;
    };

    // Helper function to transform a point from world space to box's local space
    Vector2 WorldToLocal(Vector2 const& point,
                         Vector2 const& boxCenter,
                         f32 const      rotationRad) {
        // Translate point to origin
        Vector2 translatedPoint = Vector2Subtract(point, boxCenter);
        // Rotate point inversely
        f32 cosRot = cosf(-rotationRad);
        f32 sinRot = sinf(-rotationRad);
        return Vector2{
            translatedPoint.x * cosRot - translatedPoint.y * sinRot,
            translatedPoint.x * sinRot + translatedPoint.y * cosRot};
    }

    // Helper function to transform a point from box's local space to world space
    Vector2 LocalToWorld(Vector2 const& point,
                         Vector2 const& boxCenter,
                         f32 const      rotationRad) {
        // Rotate point
        f32     cosRot       = cosf(rotationRad);
        f32     sinRot       = sinf(rotationRad);
        Vector2 rotatedPoint = Vector2{
            point.x * cosRot - point.y * sinRot,
            point.x * sinRot + point.y * cosRot};
        // Translate point back
        return Vector2Add(rotatedPoint, boxCenter);
    }
}

namespace rlf::phys {
    bool CheckCollisionBoxCircle(BoundingBox const& box3D,
                                 f32 const          rotationRad,
                                 Vector2 const&     circlePosition,
                                 f32 const&         circleRadius,
                                 Vector2&           collidedPoint,
                                 Vector2&           collidedNormal,
                                 Vector2&           collidedTangent,
                                 f32&               penetratingDepth) {
        // For a 2D box, we'll use the x and y components of the 3D BoundingBox.
        // First, let's define the 2D box properties.
        Vector2 boxCenter = {
            (box3D.min.x + box3D.max.x) / 2.0f,
            (box3D.min.y + box3D.max.y) / 2.0f};
        Vector2 boxHalfSize = {
            (box3D.max.x - box3D.min.x) / 2.0f,
            (box3D.max.y - box3D.min.y) / 2.0f};

        // Transform the circle's position into the box's local space
        Vector2 localCirclePos = WorldToLocal(circlePosition, boxCenter, rotationRad);

        // Find the closest point on the AABB (in local space) to the circle center
        Vector2 closestPointLocal = localCirclePos;
        closestPointLocal.x       = fmaxf(-boxHalfSize.x, fminf(closestPointLocal.x, boxHalfSize.x));
        closestPointLocal.y       = fmaxf(-boxHalfSize.y, fminf(closestPointLocal.y, boxHalfSize.y));

        // Calculate the distance squared from the circle center to this closest point
        Vector2 diff       = Vector2Subtract(localCirclePos, closestPointLocal);
        f32     distanceSq = Vector2LengthSqr(diff);

        // Check if collision occurred
        if (distanceSq > (circleRadius * circleRadius)) {
            return false;  // No collision
        }

        // Collision detected!
        // Determine the collision details in local space first.

        // Collided point in local space is the closest point on the box
        collidedPoint = LocalToWorld(closestPointLocal, boxCenter, rotationRad);

        // Calculate the normal in local space
        Vector2 localNormal;
        if (FloatEquals(distanceSq, 0.0f)) {
            // Circle center is inside the box. We need to find the minimum penetration axis.
            // This is a special case: project circle center onto each face plane.
            f32 dx = fabsf(localCirclePos.x) - boxHalfSize.x;
            f32 dy = fabsf(localCirclePos.y) - boxHalfSize.y;

            if (dx > dy) {  // Penetrating more horizontally
                localNormal      = Vector2{SIGN(localCirclePos.x), 0.0f};
                penetratingDepth = circleRadius + dx;
            } else {  // Penetrating more vertically
                localNormal      = Vector2{0.0f, SIGN(localCirclePos.y)};
                penetratingDepth = circleRadius + dy;
            }
        } else {
            localNormal = Vector2Normalize(Vector2Subtract(localCirclePos, closestPointLocal));
            // Penetrating depth
            penetratingDepth = circleRadius - sqrtf(distanceSq);
        }

        // Transform local normal to world space
        collidedNormal = LocalToWorld(localNormal, {0, 0}, rotationRad);  // Only rotate the normal

        // Calculate tangent (perpendicular to normal)
        collidedTangent = Vector2{-collidedNormal.y, collidedNormal.x};

        return true;
    }

    bool CheckCollisionBoxToBox(BoundingBox const& box1,
                                BoundingBox const& box2,
                                Vector2&           collidedPoint,
                                Vector2&           collidedNormal,
                                Vector2&           collidedTangent,
                                f32&               penetratingDepth) {
        Vector2 const center1 = {(box1.min.x + box1.max.x) * 0.5f, (box1.min.y + box1.max.y) * 0.5f};
        Vector2 const center2 = {(box2.min.x + box2.max.x) * 0.5f, (box2.min.y + box2.max.y) * 0.5f};

        Vector2 const halfSize1 = {(box1.max.x - box1.min.x) * 0.5f, (box1.max.y - box1.min.y) * 0.5f};
        Vector2 const halfSize2 = {(box2.max.x - box2.min.x) * 0.5f, (box2.max.y - box2.min.y) * 0.5f};

        Vector2 const distance    = Vector2Subtract(center2, center1);
        Vector2 const absDistance = {fabsf(distance.x), fabsf(distance.y)};

        Vector2 const overlap = {
            halfSize1.x + halfSize2.x - absDistance.x,
            halfSize1.y + halfSize2.y - absDistance.y};

        if (overlap.x <= 0 || overlap.y <= 0) {
            return false;  // No collision
        }

        // Determine the axis of least penetration (Minimum Translation Vector)
        if (overlap.x < overlap.y) {
            penetratingDepth = overlap.x;
            collidedNormal.y = 0.0f;
            collidedNormal.x = (distance.x < 0) ? -1.0f : 1.0f;
        } else {
            penetratingDepth = overlap.y;
            collidedNormal.x = 0.0f;
            collidedNormal.y = (distance.y < 0) ? -1.0f : 1.0f;
        }

        collidedPoint   = Vector2Add(center1, Vector2Scale(collidedNormal, halfSize1.x * fabsf(collidedNormal.x) + halfSize1.y * fabsf(collidedNormal.y)));
        collidedTangent = Vector2Rotate(collidedNormal, rlf::pi * 0.5f);

        return true;
    }

    bool CheckCollisionLines(Vector3 const& l1Start, Vector3 const& l1End, Vector3 const& l2Start, Vector3 const& l2End) {
        Vector3 D1 = l1End - l1Start;    // Direction vector of segment 1
        Vector3 D2 = l2End - l2Start;    // Direction vector of segment 2
        Vector3 R  = l1Start - l2Start;  // Vector between segment start points

        f32 a = Vector3LengthSqr(D1);
        f32 b = Vector3DotProduct(D1, D2);
        f32 c = Vector3LengthSqr(D2);
        f32 d = Vector3DotProduct(D1, R);
        f32 e = Vector3DotProduct(D2, R);

        f32 denom = a * c - b * b;  // Determinant of the system

        f32 s, t;  // Parameters for closest points on infinite lines

        // Handle parallel or degenerated lines
        if (std::fabs(denom) < EPSILON) {
            // Lines are parallel or (one or both) are points

            // Case 1: Both segments are points
            if (a < EPSILON && c < EPSILON) {
                s = 0.0f;
                t = 0.0f;
            }
            // Case 2: Segment 1 is a point (l1Start == l1End)
            else if (a < EPSILON) {  // l1Start is a point
                s = 0.0f;
                // Find closest point on segment 2 to l1Start
                t = std::clamp(Vector3DotProduct(R, D2) / c, 0.0f, 1.0f);
            }
            // Case 3: Segment 2 is a point (l2Start == l2End)
            else if (c < EPSILON) {  // l2Start is a point
                t = 0.0f;
                // Find closest point on segment 1 to l2Start
                s = std::clamp(Vector3DotProduct(Vector3Negate(R), D1) / a, 0.0f, 1.0f);
            }
            // Case 4: Parallel lines (non-degenerate segments)
            else {
                // Project segment 2's start point onto segment 1
                // Choose an arbitrary point on one line to project onto the other
                // Here, we try to align based on 's' from the first equation (sa - tb = d)
                s = std::clamp(-d / a, 0.0f, 1.0f);  // Assuming b is not zero (lines are not perpendicular)
                // Then calculate t based on the calculated s, or check proximity
                // For truly parallel lines, any t will work if they overlap.
                // A more robust parallel segment overlap test would be needed for true intersection
                // Here, we'll just fall through to calculate the distance with s and t, which might be non-zero

                // For truly parallel lines, the shortest distance is constant.
                // Find t for the point on D2 closest to A + s*D1
                // Use the same s as calculated for the general case if denom was non-zero
                // For practical collision, if parallel, we need to check if they overlap
                // and if the perpendicular distance is zero. This approach simplifies
                // to finding a point of closest approach based on clamping.
                t = 0.0f;  // Default or calculate based on chosen s for line 1
            }
        } else {
            // Skew lines or lines that intersect
            s = (b * e - c * d) / denom;
            t = (a * e - b * d) / denom;

            // Clamp s and t to the [0, 1] range of the segments
            s = std::clamp(s, 0.0f, 1.0f);
            t = std::clamp(t, 0.0f, 1.0f);
        }

        // Calculate the closest points on the segments using the clamped s and t
        Vector3 closestPt1 = l1Start + D1 * s;
        Vector3 closestPt2 = l2Start + D2 * t;

        // Calculate the distance between the closest points
        f32 distanceSq = Vector3LengthSqr(closestPt1 - closestPt2);

        // Collision occurs if the distance between closest points is effectively zero
        return distanceSq < (EPSILON * EPSILON);
    }

    bool CheckCollisionLineSphere(Vector3 const& startPt, Vector3 const& endPt, Vector3 const& spherePos, f32 const sphereRadius) {
        // Vector representing the line segment
        Vector3 lineVec = endPt - startPt;

        // Vector from the startPt of the line segment to the sphere's center
        Vector3 startToCenter = spherePos - startPt;

        // Calculate the projection of startToCenter onto lineVec
        // This gives us the parameter t along the infinite line
        f32 t = Vector3DotProduct(startToCenter, lineVec) / Vector3LengthSqr(lineVec);

        // Clamp t to the [0, 1] range to find the closest point on the segment
        t = std::max(0.0f, std::min(1.0f, t));

        // Calculate the closest point on the line segment to the sphere's center
        Vector3 closestPointOnSegment = startPt + lineVec * t;

        // Calculate the distance squared from the sphere's center to this closest point
        f32 distSq = Vector3LengthSqr(spherePos - closestPointOnSegment);

        // Check if this distance is less than or equal to the sphere's radius squared
        return distSq <= (sphereRadius * sphereRadius);
    }
}
