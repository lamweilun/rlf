#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

#include <Node/Ball/BallNode.hpp>

namespace ark::Node {
    class PlayerNode : public rlf::Node::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

    private:
        std::shared_ptr<BallNode> mBallNode;
        bool                      mHasStarted = false;
    };
}
