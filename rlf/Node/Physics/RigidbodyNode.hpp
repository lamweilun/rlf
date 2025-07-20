#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class RigidbodyNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(RigidbodyNode)

        Vector3 mVelocity = Vector3Zeros;
        f32     mSpeed    = 0.0f;

    protected:
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER("velocity", mVelocity)
        RLF_NODE_ACCESS_MEMBER("speed", mSpeed)
        RLF_NODE_ACCESS_END
    };
}
