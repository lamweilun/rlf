#pragma once

#include <Node/BaseNode.hpp>

namespace rlf {
    class RigidbodyNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(RigidbodyNode)

        void           setVelocity(Vector3 const& velocity);
        Vector3 const& getVelocity() const;

        void setSpeed(f32 const speed);
        f32  getSpeed() const;

    protected:
        void updateImpl() override;

        Vector3 mVelocity = Vector3Zeros;
        f32     mSpeed    = 0.0f;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("velocity", getVelocity, setVelocity)
        RLF_NODE_ACCESS_MEMBER_GET_SET("speed", getSpeed, setSpeed)
        RLF_NODE_ACCESS_END
    };
}
