#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class ColliderNode : public BaseNode {
    public:
        void updateImpl() override;
        void renderImpl() override;

        BoundingBox getBoundingBox();
        bool        collided = false;
    };
}
