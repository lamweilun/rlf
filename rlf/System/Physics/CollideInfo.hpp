#pragma once

namespace rlf
{
    class ColliderNode;

    struct CollideInfo
    {
        std::shared_ptr<rlf::ColliderNode> self            = nullptr;
        std::shared_ptr<rlf::ColliderNode> other           = nullptr;
        rlf::Vec2f                         collidedPoint   = rlf::Vec2f::Zero();
        rlf::Vec2f                         collidedNormal  = rlf::Vec2f::Zero();
        rlf::Vec2f                         collidedTangent = rlf::Vec2f::Zero();
        f32                                collidedDepth   = 0.0f;
    };
}
