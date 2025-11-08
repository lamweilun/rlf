#pragma once

#include <memory>

namespace rlf
{
    namespace Node
    {
        class ColliderNode;
    }

    struct CollideInfo
    {
        std::shared_ptr<rlf::Node::ColliderNode> self;
        std::shared_ptr<rlf::Node::ColliderNode> other;
        rlf::Vec2f                               collidedPoint   = rlf::Vec2f::Zero();
        rlf::Vec2f                               collidedNormal  = rlf::Vec2f::Zero();
        rlf::Vec2f                               collidedTangent = rlf::Vec2f::Zero();
        f32                                      collidedDepth   = 0.0f;
    };
}
