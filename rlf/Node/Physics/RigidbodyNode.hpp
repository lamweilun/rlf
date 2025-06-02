#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class RigidbodyNode : public BaseNode {
    public:
        Vector3 velocity = Vector3Zeros;
        f32     speed    = 1.0f;

        void updateImpl() override;
    };
}
