#include <Util/Physics/CollisionDetection.hpp>

namespace rlf::phys {
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
