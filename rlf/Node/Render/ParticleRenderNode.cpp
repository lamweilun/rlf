#include <Node/Render/ParticleRenderNode.hpp>

namespace rlf {
    void ParticleRenderNode::renderImpl() {
        for (auto const& index : mLiveIndices) {
            DrawCircleV({}, 10.0f * mScales[index], WHITE);
        }
    }

    void ParticleRenderNode::initImpl() {
        RenderNode::initImpl();

        mFreeIndices.resize(mMaxCount);
        for (u64 i = 0; i < mMaxCount; ++i) {
            mFreeIndices[i] = mMaxCount - i - 1;
        }

        mLiveIndices.clear();
        mLiveIndices.reserve(mMaxCount);
    }

    void ParticleRenderNode::updateImpl() {
        // Check if any particle needs to despawn
        u64 newSize = mLiveIndices.size();
        for (u64 i = 0; i < newSize;) {
            auto const index = mLiveIndices[i];

            mLifeTimes[index] -= GetFrameTime();
            if (mLifeTimes[index] <= 0.0f) {
                std::swap(mLiveIndices[i], mLiveIndices[newSize - 1]);
                mFreeIndices.push_back(index);
                --newSize;
                continue;
            }
            ++i;
        }
        mLiveIndices.resize(newSize);

        // Update particle params
        for (auto const& index : mLiveIndices) {
            mScales[index] += mScaleDeltas[index] * GetFrameTime();
        }

        // Check if we can spawn a new particle
        mCurrentSpawnRate -= GetFrameTime();
        if (mCurrentSpawnRate <= 0.0f) {
            spawnParticle();
            mCurrentSpawnRate = mSpawnRate;
        }
    }

    u32 ParticleRenderNode::getMaxCount() const {
        return mMaxCount;
    }
    void ParticleRenderNode::setMaxCount(u32 const maxCount) {
        if (maxCount == mMaxCount) {
            return;
        }
        mMaxCount = maxCount;
        resizeParams();
    }

    f32 ParticleRenderNode::getSpawnRate() const {
        return mSpawnRate;
    }
    void ParticleRenderNode::setSpawnRate(f32 const spawnRate) {
        mSpawnRate        = spawnRate;
        mCurrentSpawnRate = mSpawnRate;
    }

    void ParticleRenderNode::spawnParticle() {
        // Do not spawn particle if it reaches max count
        if (mLiveIndices.size() == mMaxCount) {
            return;
        }

        // Get the new particle index
        u64 const index = mFreeIndices.back();
        mFreeIndices.pop_back();
        mLiveIndices.push_back(index);

        // Set runtime params
        auto const lifeTime = mLifeTimeRange.getValue();
        mLifeTimes[index]   = lifeTime;

        auto const startScale = mStartScale.getValue();
        auto const endScale   = mEndScale.getValue();
        mScales[index]        = startScale;
        mScaleDeltas[index]   = (endScale - startScale) / lifeTime;
    }

    void ParticleRenderNode::resizeParams() {
        mLifeTimes.resize(mMaxCount);
        mScales.resize(mMaxCount);
        mScaleDeltas.resize(mMaxCount);
    }
}
