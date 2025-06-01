#pragma once

#include <Node/NodeBase.hpp>

namespace rlf {
    class RigidbodyNode : public NodeBase {
    public:
        Vector3 velocity = Vector3Zeros;
        f32     speed    = 1.0f;

        void update();
    };
}
