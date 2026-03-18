#include <Node/Render/ParticleRenderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node
{

    void ParticleRenderNode::setupImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addParticleRenderNode(this);
        unspawnAllParticle();
    }

    void ParticleRenderNode::shutdownImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeParticleRenderNode(this);
    }

    void ParticleRenderNode::setActiveImpl([[maybe_unused]] bool const selfActive)
    {
        if (getActive())
        {
            rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addParticleRenderNode(this);
        }
        else
        {
            rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeParticleRenderNode(this);
        }
    }

    void ParticleRenderNode::renderImpl()
    {
#ifdef RLF_EDITOR
        updateImpl();
#endif

        auto const renderTint = getTint();
        rlf::Vec4f tint{
            static_cast<f32>(renderTint.r) / 255.0f,
            static_cast<f32>(renderTint.g) / 255.0f,
            static_cast<f32>(renderTint.b) / 255.0f,
            static_cast<f32>(renderTint.a) / 255.0f};

        rlSetBlendMode(BlendMode::BLEND_ADD_COLORS);
        for (auto const& index : mLiveIndices)
        {
            rlPushMatrix();

            auto const& position = mPositions[index];
            rlTranslatef(position.x, position.y, 0.0f);

            auto const& rotation = mRotations[index];
            rlRotatef(rotation, 0.0f, 0.0f, 1.0f);

            Color            finalColor = {};
            rlf::Vec4f const finalTint  = tint * mColors[index] * 255.0f;
            finalColor.r                = static_cast<u8>(std::clamp(finalTint.r, 0.0f, 255.0f));
            finalColor.g                = static_cast<u8>(std::clamp(finalTint.g, 0.0f, 255.0f));
            finalColor.b                = static_cast<u8>(std::clamp(finalTint.b, 0.0f, 255.0f));
            finalColor.a                = static_cast<u8>(std::clamp(finalTint.a, 0.0f, 255.0f));
            DrawCircleV(Vector2Zeros, mScales[index], finalColor);

            rlPopMatrix();
        }
        rlSetBlendMode(BlendMode::BLEND_ALPHA);
    }

    void ParticleRenderNode::updateLiveParticles()
    {
        // Check if any particle needs to despawn
        u64 newSize = mLiveIndices.size();
        for (u64 i = 0; i < newSize;)
        {
            auto const index = mLiveIndices[i];

            mLifeTimes[index] -= GetFrameTime();
            if (mLifeTimes[index] <= 0.0f)
            {
                std::swap(mLiveIndices[i], mLiveIndices[newSize - 1]);
                mFreeIndices.push_back(index);
                --newSize;
                continue;
            }
            ++i;
        }
        mLiveIndices.resize(newSize);

        // Update particle params
        for (auto const& index : mLiveIndices)
        {
            mScales[index] += mScaleDeltas[index] * GetFrameTime();
            mSpeeds[index] += mSpeedDeltas[index] * GetFrameTime();
            mPositions[index] += mDirections[index] * mSpeeds[index] * GetFrameTime();
            mRotations[index] += mRotationDeltas[index] * GetFrameTime();
            mColors[index] += mColorDeltas[index] * GetFrameTime();
        }
    }

    void ParticleRenderNode::updateImpl()
    {
        updateLiveParticles();

        // Check if we can spawn a new particle
        mCurrentSpawnRate -= GetFrameTime();
        if (mCurrentSpawnRate <= 0.0f)
        {
            spawnParticle();
            mCurrentSpawnRate = mSpawnRate;
        }
    }

    u64 ParticleRenderNode::getMaxCount() const
    {
        return mMaxCount;
    }
    void ParticleRenderNode::setMaxCount(u64 const maxCount)
    {
        if (maxCount == mMaxCount)
        {
            return;
        }
        mMaxCount = maxCount;
        unspawnAllParticle();
        resizeParams();
    }

    f32 ParticleRenderNode::getSpawnRate() const
    {
        return mSpawnRate;
    }
    void ParticleRenderNode::setSpawnRate(f32 const spawnRate)
    {
        mSpawnRate        = spawnRate;
        mCurrentSpawnRate = mSpawnRate;
    }

    rlf::Range<f32> const& ParticleRenderNode::getLifeTimeRange() const
    {
        return mLifeTimeRange;
    }
    void ParticleRenderNode::setLifeTimeRange(rlf::Range<f32> const& lifeTimeRange)
    {
        mLifeTimeRange = lifeTimeRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getStartScaleRange() const
    {
        return mStartScaleRange;
    }
    void ParticleRenderNode::setStartScaleRange(rlf::Range<f32> const& startScaleRange)
    {
        mStartScaleRange = startScaleRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getEndScaleRange() const
    {
        return mEndScaleRange;
    }
    void ParticleRenderNode::setEndScaleRange(rlf::Range<f32> const& endScaleRange)
    {
        mEndScaleRange = endScaleRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getStartSpeedRange() const
    {
        return mStartSpeedRange;
    }
    void ParticleRenderNode::setStartSpeedRange(rlf::Range<f32> const& startSpeedRange)
    {
        mStartSpeedRange = startSpeedRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getEndSpeedRange() const
    {
        return mEndSpeedRange;
    }
    void ParticleRenderNode::setEndSpeedRange(rlf::Range<f32> const& endSpeedRange)
    {
        mEndSpeedRange = endSpeedRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getStartRotationRange() const
    {
        return mStartRotationRange;
    }
    void ParticleRenderNode::setStartRotationRange(rlf::Range<f32> const& startRotationRange)
    {
        mStartRotationRange = startRotationRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getEndRotationRange() const
    {
        return mEndRotationRange;
    }
    void ParticleRenderNode::setEndRotationRange(rlf::Range<f32> const& endRotationRange)
    {
        mEndRotationRange = endRotationRange;
    }

    rlf::Range<f32> const& ParticleRenderNode::getSpawnAngleDegRange() const
    {
        return mSpawnAngleDegRange;
    }
    void ParticleRenderNode::setSpawnAngleDegRange(rlf::Range<f32> const& spawnAngleDegRange)
    {
        mSpawnAngleDegRange = spawnAngleDegRange;
    }

    rlf::Range<rlf::Color4F> const& ParticleRenderNode::getStartColorRange() const
    {
        return mStartColorRange;
    }
    void ParticleRenderNode::setStartColorRange(rlf::Range<rlf::Color4F> const& startColorRange)
    {
        mStartColorRange = startColorRange;
    }

    rlf::Range<rlf::Color4F> const& ParticleRenderNode::getEndColorRange() const
    {
        return mEndColorRange;
    }
    void ParticleRenderNode::setEndColorRange(rlf::Range<rlf::Color4F> const& endColorRange)
    {
        mEndColorRange = endColorRange;
    }

    bool ParticleRenderNode::anyParticleAlive() const
    {
        return !mLiveIndices.empty();
    }

    void ParticleRenderNode::spawnParticle()
    {
        // Do not spawn particle if it reaches max count
        if (mLiveIndices.size() == mMaxCount)
        {
            return;
        }

        // Get the new particle index
        u64 const index = mFreeIndices.back();
        mFreeIndices.pop_back();
        mLiveIndices.push_back(index);

        // Set runtime params
        auto const lifeTime = std::max(EPSILON, mLifeTimeRange.getValue());
        mLifeTimes[index]   = lifeTime;

        // Setup scale
        auto const startScale = mStartScaleRange.getValue();
        auto const endScale   = mEndScaleRange.getValue();
        mScales[index]        = startScale;
        mScaleDeltas[index]   = (endScale - startScale) / lifeTime;

        // Setup speed
        auto const startSpeed = mStartSpeedRange.getValue();
        auto const endSpeed   = mEndSpeedRange.getValue();
        mSpeeds[index]        = startSpeed;
        mSpeedDeltas[index]   = (endSpeed - startSpeed) / lifeTime;

        // Setup direction
        auto const spawnAngle = mSpawnAngleDegRange.getValue();
        mDirections[index]    = rlf::Vec2f::FromAngle(rlf::Radians(spawnAngle));

        mPositions[index] = rlf::Vec2f::Zero();

        // Setup rotation
        auto const startRotation = mStartRotationRange.getValue();
        auto const endRotation   = mEndRotationRange.getValue();
        mRotationDeltas[index]   = (endRotation - startRotation) / lifeTime;
        mRotations[index]        = startRotation;

        // Setup color
        auto const startColor = mStartColorRange.getValue();
        auto const endColor   = mEndColorRange.getValue();
        mColors[index]        = startColor;
        mColorDeltas[index]   = (endColor - startColor) / lifeTime;
    }

    void ParticleRenderNode::unspawnAllParticle()
    {
        // Clear all live indices
        mLiveIndices.clear();

        // Ensure enough free indices are available
        mFreeIndices.resize(mMaxCount);
        for (u64 i = 0; i < mMaxCount; ++i)
        {
            mFreeIndices[i] = mMaxCount - i - 1;
        }
    }

    void ParticleRenderNode::resizeParams()
    {
        mLifeTimes.resize(mMaxCount);
        mScales.resize(mMaxCount);
        mScaleDeltas.resize(mMaxCount);
        mSpeeds.resize(mMaxCount);
        mSpeedDeltas.resize(mMaxCount);
        mRotations.resize(mMaxCount);
        mRotationDeltas.resize(mMaxCount);
        mPositions.resize(mMaxCount);
        mDirections.resize(mMaxCount);
        mColors.resize(mMaxCount);
        mColorDeltas.resize(mMaxCount);
    }
}
