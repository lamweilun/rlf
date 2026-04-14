#pragma once

#include <Node/Render/BurstParticleRenderNode.hpp>

#include <Node/Physics/RigidbodyNode.hpp>

namespace ext
{
    class PlayerBulletNode : public rlf::RigidbodyNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(PlayerBulletNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

    private:
        std::shared_ptr<rlf::BurstParticleRenderNode> mBulletParticle = nullptr;
    };
}
