#pragma once

#include <Util/Range.hpp>

#include <Node/Render/RenderNode.hpp>

#include <vector>

namespace rlf {
    class ParticleRenderNode : public rlf::RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(ParticleRenderNode)

        void renderImpl() override;

        u32  getMaxCount() const;
        void setMaxCount(u32 const maxCount);

        f32  getSpawnRate() const;
        void setSpawnRate(f32 const spawnRate);

    protected:
        void initImpl() override;
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(rlf::RenderNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Max Count", getMaxCount, setMaxCount)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Spawn Rate", getSpawnRate, setSpawnRate)
        RLF_NODE_ACCESS_END

    private:
        void spawnParticle();
        void resizeParams();

        // Config params
        u32             mMaxCount      = 0;
        f32             mSpawnRate     = 1.0f;
        rlf::Range<f32> mLifeTimeRange = {0.0f, 1.0f};
        rlf::Range<f32> mStartScale    = {1.0f, 1.0f};
        rlf::Range<f32> mEndScale      = {0.0f, 0.0f};

        // Runtime params (Resize the vector params in resizeParams)
        f32              mCurrentSpawnRate = 1.0f;
        std::vector<f32> mLifeTimes;
        std::vector<f32> mScales;
        std::vector<f32> mScaleDeltas;

        std::vector<u64> mLiveIndices;
        std::vector<u64> mFreeIndices;
    };
}
