#pragma once

namespace rlf
{
    namespace Node
    {
        class ColliderNode;
    }

    struct CollideInfo
    {
        rlf::Node::ColliderNode* self            = nullptr;
        rlf::Node::ColliderNode* other           = nullptr;
        rlf::Vec2f               collidedPoint   = rlf::Vec2f::Zero();
        rlf::Vec2f               collidedNormal  = rlf::Vec2f::Zero();
        rlf::Vec2f               collidedTangent = rlf::Vec2f::Zero();
        f32                      collidedDepth   = 0.0f;
    };
}
