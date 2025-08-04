#pragma once

namespace rlf::phys {
    // 3D Lines Collision
    bool CheckCollisionLines(Vector3 const& l1Start, Vector3 const& l1End, Vector3 const& l2Start, Vector3 const& l2End);

    // 3D Line and Sphere Collision
    bool CheckCollisionLineSphere(Vector3 const& startPt, Vector3 const& endPt, Vector3 const& spherePos, f32 const sphereRadius);
}
