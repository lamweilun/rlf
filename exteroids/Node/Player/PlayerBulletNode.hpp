#pragma once

#include <Node/Render/BurstParticleRenderNode.hpp>

#include <Node/Physics/RigidbodyNode.hpp>

namespace ext::Node {
    class PlayerBulletNode : public rlf::Node::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(PlayerBulletNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

    private:
        std::shared_ptr<rlf::Node::BurstParticleRenderNode> mBulletParticle;
    };
}
