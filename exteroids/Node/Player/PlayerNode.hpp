#pragma once

#include <Node/Physics/RigidbodyNode.hpp>
#include <Node/Audio/SoundNode.hpp>
#include <Node/Player/PlayerBulletNode.hpp>

namespace ext
{
    class PlayerNode : public rlf::RigidbodyNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(PlayerNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

    private:
        std::shared_ptr<rlf::SoundNode>        mFireSoudNode;
        std::shared_ptr<ext::PlayerBulletNode> mPlayerBulletNode;
        f32                                    mFireRate        = 0.1f;
        f32                                    mCurrentFireRate = 0.0f;
    };
}
