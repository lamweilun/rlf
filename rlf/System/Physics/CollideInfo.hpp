#pragma once

#include <memory>

namespace rlf {
    namespace Node {
        class ColliderNode;
    }

    struct CollideInfo {
        std::shared_ptr<rlf::Node::ColliderNode> self;
        std::shared_ptr<rlf::Node::ColliderNode> other;
        Vector2                                  collidedPoint   = Vector2Zeros;
        Vector2                                  collidedNormal  = Vector2Zeros;
        Vector2                                  collidedTangent = Vector2Zeros;
    };
}
