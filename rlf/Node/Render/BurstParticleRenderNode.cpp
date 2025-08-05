#include <Node/Render/BurstParticleRenderNode.hpp>

namespace rlf {

    u64 BurstParticleRenderNode::getBurstCount() const {
        return mBurstCount;
    }
    void BurstParticleRenderNode::setBurstCount(u64 const burstCount) {
        mBurstCount = burstCount;
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
            for (size_t i = 0; i < getMaxCount(); ++i) {
                spawnParticle();
            }
            mHasBurstSpawned = true;
            mNumberOfBursts++;
        }

        if (mHasBurstSpawned && !anyParticleAlive()) {
            if (mToDestroyAfterBurst && (mNumberOfBursts == mBurstCount)) {
                std::cout << "Destroy Burst Particles" << std::endl;
                setToDestroy(true);
            }
            else {
                mHasBurstSpawned = false;
            }
        }
    }
}
