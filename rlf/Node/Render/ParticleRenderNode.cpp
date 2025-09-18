#include <Node/Render/ParticleRenderNode.hpp>

namespace rlf::Node {
    void ParticleRenderNode::renderImpl() {
        for (auto const& index : mLiveIndices) {
            rlPushMatrix();

            auto const& position = mPositions[index];
            rlTranslatef(position.x, position.y, 0.0f);

            DrawRectangleV(Vector2Zeros, {mScales[index], mScales[index]},
                           Vector4ToColor(ColorToVector4(getTint()) * ColorToVector4(mColors[index])));

            rlPopMatrix();
        }
    }

    void ParticleRenderNode::updateLiveParticles() {
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
            mSpeeds[index] += mSpeedDeltas[index] * GetFrameTime();
            mPositions[index] += mDirections[index] * mSpeeds[index] * GetFrameTime();
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
        updateLiveParticles();

        // Check if we can spawn a new particle
        mCurrentSpawnRate -= GetFrameTime();
        if (mCurrentSpawnRate <= 0.0f) {
            spawnParticle();
            mCurrentSpawnRate = mSpawnRate;
        }
    }

    u64 ParticleRenderNode::getMaxCount() const {
        return mMaxCount;
    }
    void ParticleRenderNode::setMaxCount(u64 const maxCount) {
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

    rlf::Range<f32> const& ParticleRenderNode::getLifeTimeRange() const {
        return mLifeTimeRange;
    }
    void ParticleRenderNode::setLifeTimeRange(rlf::Range<f32> const& lifeTimeRange) {
        mLifeTimeRange = lifeTimeRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getStartScaleRange() const {
        return mStartScaleRange;
    }
    void ParticleRenderNode::setStartScaleRange(rlf::Range<f32> const& startScaleRange) {
        mStartScaleRange = startScaleRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getEndScaleRange() const {
        return mEndScaleRange;
    }
    void ParticleRenderNode::setEndScaleRange(rlf::Range<f32> const& endScaleRange) {
        mEndScaleRange = endScaleRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getStartSpeedRange() const {
        return mStartSpeedRange;
    }
    void ParticleRenderNode::setStartSpeedRange(rlf::Range<f32> const& startSpeedRange) {
        mStartSpeedRange = startSpeedRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getEndSpeedRange() const {
        return mEndSpeedRange;
    }
    void ParticleRenderNode::setEndSpeedRange(rlf::Range<f32> const& endSpeedRange) {
        mEndSpeedRange = endSpeedRange;
    }

    rlf::Range<Vector2> const& ParticleRenderNode::getDirectionRange() const {
        return mDirectionRange;
    }
    void ParticleRenderNode::setDirectionRange(rlf::Range<Vector2> const& directionRange) {
        mDirectionRange = directionRange;
    }

    rlf::Range<Color> const& ParticleRenderNode::getStartColorRange() const {
        return mStartColorRange;
    }
    void ParticleRenderNode::setStartColorRange(rlf::Range<Color> const& startColorRange) {
        mStartColorRange = startColorRange;
    }

    rlf::Range<Color> const& ParticleRenderNode::getEndColorRange() const {
        return mEndColorRange;
    }
    void ParticleRenderNode::setEndColorRange(rlf::Range<Color> const& endColorRange) {
        mEndColorRange = endColorRange;
    }

    bool ParticleRenderNode::anyParticleAlive() const {
        return !mLiveIndices.empty();
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
        auto const lifeTime = std::max(EPSILON, mLifeTimeRange.getValue());
        mLifeTimes[index]   = lifeTime;

        auto const startScale = mStartScaleRange.getValue();
        auto const endScale   = mEndScaleRange.getValue();
        mScales[index]        = startScale;
        mScaleDeltas[index]   = (endScale - startScale) / lifeTime;

        auto const startSpeed = mStartSpeedRange.getValue();
        auto const endSpeed   = mEndSpeedRange.getValue();
        mSpeeds[index]        = startSpeed;
        mSpeedDeltas[index]   = (endSpeed - startSpeed) / lifeTime;

        auto const direction = mDirectionRange.getValue();
        mDirections[index]   = direction;

        mPositions[index] = Vector2Zeros;

        auto const startColor = mStartColorRange.getValue();
        auto const endColor   = mEndColorRange.getValue();
        mColors[index]        = startColor;
        mColorDeltas[index]   = (endColor - startColor) / lifeTime;
    }

    void ParticleRenderNode::resizeParams() {
        mLifeTimes.resize(mMaxCount);
        mScales.resize(mMaxCount);
        mScaleDeltas.resize(mMaxCount);
        mSpeeds.resize(mMaxCount);
        mSpeedDeltas.resize(mMaxCount);
        mPositions.resize(mMaxCount);
        mDirections.resize(mMaxCount);
        mColors.resize(mMaxCount);
        mColorDeltas.resize(mMaxCount);
    }
}
