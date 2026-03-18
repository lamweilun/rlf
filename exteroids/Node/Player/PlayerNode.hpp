#pragma once

#include <Node/Physics/RigidbodyNode.hpp>
#include <Node/Audio/SoundNode.hpp>
#include <Node/Player/PlayerBulletNode.hpp>

namespace ext::Node
{
    class PlayerNode : public rlf::Node::RigidbodyNode
    {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

    private:
        rlf::Node::SoundNode*        mFireSoudNode = nullptr;
        ext::Node::PlayerBulletNode* mPlayerBulletNode = nullptr;
        f32                          mFireRate        = 0.1f;
        f32                          mCurrentFireRate = 0.0f;
    };
}
