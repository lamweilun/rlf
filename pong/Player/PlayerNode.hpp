#pragma once

#include <Node/Physics/RigidbodyNode.hpp>

namespace rlf::Node {
    class PlayerNode : public RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerNode)

    protected:
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RigidbodyNode)
        RLF_NODE_ACCESS_MEMBER("Is Player One", mIsPlayerOne)
        RLF_NODE_ACCESS_END

    private:
        bool mIsPlayerOne = true;
    };
}
