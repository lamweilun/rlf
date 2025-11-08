#pragma once

#include <Node/BaseNode.hpp>

namespace rlf::Node
{
    class RigidbodyNode : public BaseNode
    {
    public:
        RLF_TYPE_REGISTER_QUICK(RigidbodyNode)

        void              setVelocity(rlf::Vec2f const& velocity);
        rlf::Vec2f const& getVelocity() const;
        void              setVelocityFromAngleRad(f32 const angleRad);
        void              setVelocityFromAngleDeg(f32 const angleDeg);

        void setSpeed(f32 const speed);
        f32  getSpeed() const;

    protected:
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("speed", getSpeed, setSpeed)
        RLF_NODE_ACCESS_END

    private:
        rlf::Vec2f mVelocity = rlf::Vec2f::Zero();
        f32        mSpeed    = 0.0f;
    };
}
