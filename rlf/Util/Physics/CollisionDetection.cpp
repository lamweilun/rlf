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
        Vector2 const translatedPoint = point - boxCenter;
        // Rotate point inversely
        f32 const cosRot = std::cosf(-rotationRad);
        f32 const sinRot = std::sinf(-rotationRad);
        return Vector2{translatedPoint.x * cosRot - translatedPoint.y * sinRot, translatedPoint.x * sinRot + translatedPoint.y * cosRot};
    }

    // Helper function to transform a point from box's local space to world space
    Vector2 LocalToWorld(Vector2 const& point,
                         Vector2 const& boxCenter,
                         f32 const      rotationRad) {
        // Rotate and Translate
        f32 const     cosRot       = std::cosf(rotationRad);
        f32 const     sinRot       = std::sinf(rotationRad);
        Vector2 const rotatedPoint = Vector2{point.x * cosRot - point.y * sinRot, point.x * sinRot + point.y * cosRot};
        return rotatedPoint + boxCenter;
    }

    std::vector<Vector2> GetRotatedBoxCorners(BoundingBox const& box,
                                              f32 const          rotationRad) {
        Vector2 const center   = {(box.min.x + box.max.x) * 0.5f, (box.min.y + box.max.y) * 0.5f};
        Vector2 const halfSize = {(box.max.x - box.min.x) * 0.5f, (box.max.y - box.min.y) * 0.5f};

        std::vector<Vector2> corners(4);
        // Local coordinates of corners relative to center
        std::array const localCorners = {
            Vector2{-halfSize.x, -halfSize.y},
            Vector2{ halfSize.x, -halfSize.y},
            Vector2{ halfSize.x,  halfSize.y},
            Vector2{-halfSize.x,  halfSize.y}
        };

        f32 const cosRot = std::cosf(rotationRad);
        f32 const sinRot = std::sinf(rotationRad);

        for (size_t i = 0; i < 4; ++i) {
            // Rotate and translate to world space
            corners[i].x = center.x + (localCorners[i].x * cosRot - localCorners[i].y * sinRot);
            corners[i].y = center.y + (localCorners[i].x * sinRot + localCorners[i].y * cosRot);
        }
        return corners;
    }

    // Helper function to project a polygon onto an axis
    void ProjectPolygon(std::vector<Vector2> const& corners,
                        Vector2 const&              axis,
                        f32&                        minProjection,
                        f32&                        maxProjection) {
        minProjection = Vector2DotProduct(corners[0], axis);
        maxProjection = minProjection;

        for (size_t i = 1; i < corners.size(); ++i) {
            f32 const projection = Vector2DotProduct(corners[i], axis);
            if (projection < minProjection) {
                minProjection = projection;
            }
            if (projection > maxProjection) {
                maxProjection = projection;
            }
        }
    }

    // Helper function to check for overlap of two 1D intervals
    bool CheckOverlap(f32 const min1, f32 const max1, f32 const min2, f32 const max2, f32& overlap) {
        if (max1 < min2 || max2 < min1) {
            return false;  // No overlap
        }
        overlap = std::min(max1, max2) - std::max(min1, min2);
        return true;
    }

    // Helper to get the 4 normalized edge normals (axes of separation) for a box
    std::vector<Vector2> GetBoxNormals(std::vector<Vector2> const& corners) {
        std::vector<Vector2> normals;
        for (size_t i = 0; i < 4; ++i) {
            Vector2 const p1     = corners[i];
            Vector2 const p2     = corners[(i + 1) % 4];
            Vector2 const edge   = p2 - p1;
            Vector2       normal = Vector2Normalize(Vector2{-edge.y, edge.x});
            normals.push_back(normal);
        }
        return normals;
    }
}

namespace rlf::phys {
    bool CheckCollisionBoxCircle(BoundingBox const& box,
                                 f32 const          rotationRad,
                                 Vector2 const&     circlePosition,
                                 f32 const&         circleRadius,
                                 Vector2&           collidedPoint,
                                 Vector2&           collidedNormal,
                                 Vector2&           collidedTangent,
                                 f32&               penetratingDepth) {
        Vector2 const boxCenter   = {(box.min.x + box.max.x) * 0.5f, (box.min.y + box.max.y) * 0.5f};
        Vector2 const boxHalfSize = {(box.max.x - box.min.x) * 0.5f, (box.max.y - box.min.y) * 0.5f};

        // Transform the circle's position into the box's local space
        Vector2 const localCirclePos = WorldToLocal(circlePosition, boxCenter, rotationRad);

        // Find the closest point on the AABB (in local space) to the circle center
        Vector2 closestPointLocal = localCirclePos;
        closestPointLocal.x       = std::max(-boxHalfSize.x, std::min(closestPointLocal.x, boxHalfSize.x));
        closestPointLocal.y       = std::max(-boxHalfSize.y, std::min(closestPointLocal.y, boxHalfSize.y));

        // Calculate the distance squared from the circle center to this closest point
        Vector2 const diff       = localCirclePos - closestPointLocal;
        f32 const     distanceSq = Vector2LengthSqr(diff);

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
            f32 const dx = std::abs(localCirclePos.x) - boxHalfSize.x;
            f32 const dy = std::abs(localCirclePos.y) - boxHalfSize.y;

            if (dx > dy) {  // Penetrating more horizontally
                localNormal      = Vector2{SIGN(localCirclePos.x), 0.0f};
                penetratingDepth = circleRadius + dx;
            } else {  // Penetrating more vertically
                localNormal      = Vector2{0.0f, SIGN(localCirclePos.y)};
                penetratingDepth = circleRadius + dy;
            }
        } else {
            localNormal = Vector2Normalize(localCirclePos - closestPointLocal);
            // Penetrating depth
            penetratingDepth = circleRadius - std::sqrtf(distanceSq);
        }

        // Transform local normal to world space
        collidedNormal = LocalToWorld(localNormal, {0, 0}, rotationRad);  // Only rotate the normal

        // Calculate tangent (perpendicular to normal)
        collidedTangent = Vector2{-collidedNormal.y, collidedNormal.x};

        return true;
    }

    bool CheckCollisionBoxToBox(BoundingBox const& box1,
                                f32 const          box1RotationRad,
                                BoundingBox const& box2,
                                f32 const          box2RotationRad,
                                Vector2&           collidedPoint,
                                Vector2&           collidedNormal,
                                Vector2&           collidedTangent,
                                f32&               penetratingDepth) {
        // Get the corners of both rotated boxes in world space
        std::vector<Vector2> const corners1 = GetRotatedBoxCorners(box1, box1RotationRad);
        std::vector<Vector2> const corners2 = GetRotatedBoxCorners(box2, box2RotationRad);

        // Get the potential separation axes (normals of each box's edges)
        std::vector<Vector2> axes;
        std::vector<Vector2> normals1 = GetBoxNormals(corners1);
        std::vector<Vector2> normals2 = GetBoxNormals(corners2);
        axes.insert(axes.end(), normals1.begin(), normals1.end());
        axes.insert(axes.end(), normals2.begin(), normals2.end());

        f32     minOverlap     = std::numeric_limits<f32>::max();
        Vector2 minOverlapAxis = {0.0f, 0.0f};
        bool    collisionFound = true;  // Assume collision until a separating axis is found

        // Use SAT (Separating Axis Theorem)
        for (auto const& axis : axes) {
            f32 min1, max1, min2, max2;
            ProjectPolygon(corners1, axis, min1, max1);
            ProjectPolygon(corners2, axis, min2, max2);

            f32 overlap;
            if (!CheckOverlap(min1, max1, min2, max2, overlap)) {
                collisionFound = false;  // Found a separating axis
                break;
            }

            // If the axis points away from the other shape's center,
            // we might need to flip the axis for consistent normal direction.
            // We ensure the normal always points from box2 *to* box1 in terms
            // of calculating the overlap distance.
            Vector2 const box1Center = {(box1.min.x + box1.max.x) * 0.5f, (box1.min.y + box1.max.y) * 0.5f};
            Vector2 const box2Center = {(box2.min.x + box2.max.x) * 0.5f, (box2.min.y + box2.max.y) * 0.5f};
            Vector2 const centerVec  = box1Center - box2Center;
            if (Vector2DotProduct(centerVec, axis) < 0.0f) {
                overlap *= -1.0f;  // This is a trick to make overlap positive for penetration
                                   // and simplify calculation later.
            }

            // Ensure overlap is positive (magnitude of penetration)
            overlap = std::abs(overlap);

            if (overlap < minOverlap) {
                minOverlap     = overlap;
                minOverlapAxis = axis;
            }
        }

        if (!collisionFound) {
            return false;  // No collision
        }

        // Collision occurred!
        penetratingDepth = minOverlap;

        // Determine the collision normal (the axis of least penetration)
        // The direction of the normal should point from box2 to box1.
        Vector2 const box1Center   = {(box1.min.x + box1.max.x) * 0.5f, (box1.min.y + box1.max.y) * 0.5f};
        Vector2 const box2Center   = {(box2.min.x + box2.max.x) * 0.5f, (box2.min.y + box2.max.y) * 0.5f};
        Vector2 const centerVector = box1Center - box2Center;

        // If the dot product is negative, it means minOverlapAxis points
        // from box1 to box2, so we need to reverse it for the normal.
        if (Vector2DotProduct(centerVector, minOverlapAxis) < 0.0f) {
            collidedNormal = Vector2Scale(minOverlapAxis, -1.0f);
        } else {
            collidedNormal = minOverlapAxis;
        }

        // Collision point: this is harder for two rotated boxes.
        // A common approach is to find the vertex of one box that penetrates
        // the most into the other box, or the face of one box that is
        // most deeply penetrated by the other.
        // For simplicity, let's find the deepest penetrating vertex from box2 into box1.
        // This is an approximation and might not be perfectly accurate for all cases,
        // especially for edge-on-edge collisions.
        f32     maxPenetration = -std::numeric_limits<f32>::max();
        Vector2 deepVertex     = {0.0f, 0.0f};

        // Check corners of box2 against box1
        for (Vector2 const& vertex : corners2) {
            // Project the vertex onto the normal
            f32 const projection = Vector2DotProduct(vertex, collidedNormal);

            // Project box1 onto the normal
            f32 min1, max1;
            ProjectPolygon(corners1, collidedNormal, min1, max1);

            // Calculate penetration depth for this vertex
            // If the normal points from box2 to box1, a vertex from box2
            // would penetrate if its projection is greater than box1's max projection.
            f32 const currentPenetration = projection - max1;  // How far beyond box1's "back" face
                                                               // the vertex is. Negative means inside.

            if (currentPenetration > maxPenetration) {
                maxPenetration = currentPenetration;
                deepVertex     = vertex;
            }
        }
        // The point on the surface of box1 where deepVertex from box2 would collide.
        // This is `deepVertex - collidedNormal * maxPenetration`
        collidedPoint = Vector2Subtract(deepVertex, Vector2Scale(collidedNormal, maxPenetration));

        // Calculate tangent (perpendicular to normal)
        collidedTangent = Vector2{-collidedNormal.y, collidedNormal.x};

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
