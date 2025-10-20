#pragma once

#include <Node/BaseNode.hpp>
#include <Node/UI/UIButtonNode.hpp>

#include <Node/Player/PlayerNode.hpp>
#include <Node/Asteroid/AsteroidNode.hpp>

namespace ext::Node {
    class GameManagerNode : public rlf::Node::BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(GameManagerNode)

    protected:
        void initImpl() override;
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER("Asteroid Spawn Timer", mAsteroidSpawnTimer)
        RLF_NODE_ACCESS_END

    private:
        // Game UI
        std::shared_ptr<rlf::Node::BaseNode> mGameUINode;

        // Player
        std::shared_ptr<ext::Node::PlayerNode> mPlayerNode;

        // Asteroids
        void                                     spawnBigAsteroid() const;
        void                                     spawnMediumAsteroid() const;
        void                                     spawnSmallAsteroid() const;
        std::shared_ptr<ext::Node::AsteroidNode> mBigAsteroidNode;
        std::shared_ptr<ext::Node::AsteroidNode> mMediumAsteroidNode;
        std::shared_ptr<ext::Node::AsteroidNode> mSmallAsteroidNode;
        f32                                      mAsteroidSpawnTimer        = 1.0f;
        f32                                      mCurrentAsteroidSpawnTimer = 0.0f;
    };
}
