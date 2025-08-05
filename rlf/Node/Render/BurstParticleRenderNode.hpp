#pragma once

#include <Node/Render/ParticleRenderNode.hpp>

namespace rlf::Node {
    class BurstParticleRenderNode : public rlf::Node::ParticleRenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BurstParticleRenderNode)

        u64 getBurstCount() const;
        void setBurstCount(u64 const burstCount);

        bool getToDestroyAfterBurst() const;
        void setToDestroyAfterBurst(bool const toDestroyAfterBurst);

    protected:
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(rlf::Node::ParticleRenderNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Burst Count", getBurstCount, setBurstCount)
        RLF_NODE_ACCESS_MEMBER_GET_SET("To Destroy After Burst", getToDestroyAfterBurst, setToDestroyAfterBurst)
        RLF_NODE_ACCESS_END

    private:
        // Config params
        u64 mBurstCount = 1;
        bool mToDestroyAfterBurst = false;

        // Runtime params
        u64 mNumberOfBursts = 0;
        bool mHasBurstSpawned  = false;
    };
}
