#pragma once

#include <Node/BaseNode.hpp>

namespace rlf::Node {
    class RigidbodyNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(RigidbodyNode)

        void           setVelocity(Vector2 const& velocity);
        Vector2 const& getVelocity() const;

        void setSpeed(f32 const speed);
        f32  getSpeed() const;

    protected:
        void updateImpl() override;

        Vector2 mVelocity = Vector2Zeros;
        f32     mSpeed    = 0.0f;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("velocity", getVelocity, setVelocity)
        RLF_NODE_ACCESS_MEMBER_GET_SET("speed", getSpeed, setSpeed)
        RLF_NODE_ACCESS_END
    };
}
