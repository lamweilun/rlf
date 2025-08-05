#pragma once

#include <Util/Range.hpp>

#include <Node/Render/RenderNode.hpp>

#include <vector>

namespace rlf {
    class ParticleRenderNode : public rlf::RenderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(ParticleRenderNode)

        void renderImpl() override;

        u64  getMaxCount() const;
        void setMaxCount(u64 const maxCount);

        f32  getSpawnRate() const;
        void setSpawnRate(f32 const spawnRate);

        rlf::Range<f32> const& getLifeTimeRange() const;
        void                   setLifeTimeRange(rlf::Range<f32> const& lifeTimeRange);

        rlf::Range<f32> const& getStartScaleRange() const;
        void                   setStartScaleRange(rlf::Range<f32> const& startScaleRange);

        rlf::Range<f32> const& getEndScaleRange() const;
        void                   setEndScaleRange(rlf::Range<f32> const& endScaleRange);

        rlf::Range<f32> const& getStartSpeedRange() const;
        void                   setStartSpeedRange(rlf::Range<f32> const& startSpeedRange);

        rlf::Range<f32> const& getEndSpeedRange() const;
        void                   setEndSpeedRange(rlf::Range<f32> const& endSpeedRange);

        rlf::Range<Vector2> const& getDirectionRange() const;
        void                       setDirectionRange(rlf::Range<Vector2> const& directionRange);

    protected:
        void updateLiveParticles();
        bool anyParticleAlive() const;
        void spawnParticle();

        void initImpl() override;
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(rlf::RenderNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Max Count", getMaxCount, setMaxCount)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Spawn Rate", getSpawnRate, setSpawnRate)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Lifetime Range", getLifeTimeRange, setLifeTimeRange)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Start Scale Range", getStartScaleRange, setStartScaleRange)
        RLF_NODE_ACCESS_MEMBER_GET_SET("End Scale Range", getEndScaleRange, setEndScaleRange)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Start Speed Range", getStartSpeedRange, setStartSpeedRange)
        RLF_NODE_ACCESS_MEMBER_GET_SET("End Speed Range", getEndSpeedRange, setEndSpeedRange)
        RLF_NODE_ACCESS_END

    private:
        void resizeParams();

        // Config params
        u64                 mMaxCount            = 0;
        f32                 mSpawnRate           = 1.0f;
        rlf::Range<f32>     mLifeTimeRange       = {0.0f, 1.0f};
        rlf::Range<f32>     mStartScaleRange     = {1.0f, 1.0f};
        rlf::Range<f32>     mEndScaleRange       = {0.0f, 0.0f};
        rlf::Range<f32>     mStartSpeedRange     = {1.0f, 1.0f};
        rlf::Range<f32>     mEndSpeedRange       = {0.0f, 0.0f};
        rlf::Range<Vector2> mDirectionRange      = {
            Vector2{-1.0f, -1.0f},
            Vector2{ 1.0f,  1.0f}
        };

        // Runtime params (Resize the vector params in resizeParams)
        f32                  mCurrentSpawnRate = 1.0f;
        std::vector<f32>     mLifeTimes;
        std::vector<f32>     mScales;
        std::vector<f32>     mScaleDeltas;
        std::vector<f32>     mSpeeds;
        std::vector<f32>     mSpeedDeltas;
        std::vector<Vector2> mPositions;
        std::vector<Vector2> mDirections;

        std::vector<u64> mLiveIndices;
        std::vector<u64> mFreeIndices;
    };
}
