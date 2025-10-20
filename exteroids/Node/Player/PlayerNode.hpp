#pragma once

#include <Node/Physics/RigidbodyNode.hpp>
#include <Node/Audio/SoundNode.hpp>
#include <Node/Player/PlayerBulletNode.hpp>

namespace ext::Node {
    class PlayerNode : public rlf::Node::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

    private:
        std::shared_ptr<rlf::Node::SoundNode>        mFireSoudNode;
        std::shared_ptr<ext::Node::PlayerBulletNode> mPlayerBulletNode;
        f32                                          mFireRate        = 0.1f;
        f32                                          mCurrentFireRate = 0.0f;
    };
}
