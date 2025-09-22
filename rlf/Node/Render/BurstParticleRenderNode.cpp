#include <Node/Render/BurstParticleRenderNode.hpp>

namespace rlf::Node {

    u64 BurstParticleRenderNode::getBurstCount() const {
        return mBurstCount;
    }
    void BurstParticleRenderNode::setBurstCount(u64 const burstCount) {
        if (mBurstCount == burstCount) {
            return;
        }
        mBurstCount     = burstCount;
        mNumberOfBursts = 0;
        unspawnAllParticle();
    }

    u64 BurstParticleRenderNode::getBurstParticleCount() const {
        return mBurstParticleCount;
    }
    void BurstParticleRenderNode::setBurstParticleCount(u64 const burstParticleCount) {
        if (mBurstParticleCount == burstParticleCount) {
            return;
        }
        mBurstParticleCount = burstParticleCount;
        mNumberOfBursts     = 0;
        unspawnAllParticle();
    }

    bool BurstParticleRenderNode::getToDestroyAfterBurst() const {
        return mToDestroyAfterBurst;
    }
    void BurstParticleRenderNode::setToDestroyAfterBurst(bool const toDestroyAfterBurst) {
        mToDestroyAfterBurst = toDestroyAfterBurst;
    }

    void BurstParticleRenderNode::updateImpl() {
        updateLiveParticles();

        // Check if we can spawn a new particle
        if (!mHasBurstSpawned && (mNumberOfBursts < mBurstCount)) {
            mCurrentSpawnRate -= GetFrameTime();
            if (mCurrentSpawnRate <= 0.0f) {
                for (u64 i = 0; i < mBurstParticleCount; ++i) {
                    spawnParticle();
                }
                mNumberOfBursts++;
                if (mNumberOfBursts == mBurstCount) {
                    mHasBurstSpawned = true;
                }

                mCurrentSpawnRate = getSpawnRate();
            }
        }

#ifdef RLF_EDITOR
        // Checks if it needs to be destroyed
        if (mHasBurstSpawned && !anyParticleAlive()) {
            mHasBurstSpawned = false;
            mNumberOfBursts  = 0;
        }
#else
        // Checks if it needs to be destroyed
        if (mHasBurstSpawned && !anyParticleAlive()) {
            if (mToDestroyAfterBurst && (mNumberOfBursts == mBurstCount)) {
                setToDestroy(true);
            } else {
                mHasBurstSpawned = false;
            }
        }
#endif
    }
}
