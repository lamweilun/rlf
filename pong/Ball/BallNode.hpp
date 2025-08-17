#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

#include <Util/Range.hpp>

namespace rlf::Node {
    class BallNode : public RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BallNode)

        void initImpl() override;

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RigidbodyNode)
        RLF_NODE_ACCESS_MEMBER("Velocity Range", mVelocityRange)
        RLF_NODE_ACCESS_END

    private:
        rlf::Range<f32> mVelocityRange = {-100.0f, 100.0f};
    };
}
