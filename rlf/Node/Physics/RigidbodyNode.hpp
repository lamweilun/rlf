#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class RigidbodyNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(RigidbodyNode)

        void      updateImpl() override;
        rlf::Json serializeImpl() const override;
        void      deserializeImpl(rlf::Json const& j) override;

        Vector3 mVelocity = Vector3Zeros;
        f32     mSpeed    = 0.0f;
    };
}
