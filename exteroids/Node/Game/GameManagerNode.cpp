#include <Node/Game/GameManagerNode.hpp>

#include <Util/Range.hpp>

#include <Engine/Engine.hpp>

namespace ext::Node {
    void GameManagerNode::initImpl() {
        // Setup Game UI
        mGameUINode = getFirstChildOfName<rlf::Node::BaseNode>("GameUI").value();

        // Setup Player
        mPlayerNode = getRootNode()->getFirstChildOfName<ext::Node::PlayerNode>("PlayerNode").value();

        // Setup Asteroids
        mBigAsteroidNode    = getRootNode()->getFirstChildOfName<ext::Node::AsteroidNode>("BigAsteroid").value();
        mMediumAsteroidNode = getRootNode()->getFirstChildOfName<ext::Node::AsteroidNode>("MediumAsteroid").value();
        mSmallAsteroidNode  = getRootNode()->getFirstChildOfName<ext::Node::AsteroidNode>("SmallAsteroid").value();

        mGameUINode->setActive(true);
        mPlayerNode->setActive(true);
    }

    void GameManagerNode::spawnBigAsteroid() const {
        auto asteroid = mBigAsteroidNode->clone()->as<ext::Node::AsteroidNode>();
        asteroid->setHP(rlf::Range(10u, 12u).getValue());

        asteroid->setActive(true);
    }

    void GameManagerNode::spawnMediumAsteroid() const {
        auto asteroid = mMediumAsteroidNode->clone()->as<ext::Node::AsteroidNode>();
        asteroid->setHP(rlf::Range(7u, 9u).getValue());

        asteroid->setActive(true);
    }
    void GameManagerNode::spawnSmallAsteroid() const {
        auto asteroid = mSmallAsteroidNode->clone()->as<ext::Node::AsteroidNode>();
        asteroid->setHP(rlf::Range(3u, 5u).getValue());

        asteroid->setActive(true);
    }

    void GameManagerNode::updateImpl() {
        if (IsKeyPressed(KEY_ESCAPE)) {
            rlf::Engine::getInstance().setNextWorldToLoad("world/MainMenu.json");
        }

        mCurrentAsteroidSpawnTimer -= GetFrameTime();
        if (mCurrentAsteroidSpawnTimer <= 0.0f) {
            mCurrentAsteroidSpawnTimer = mAsteroidSpawnTimer;
            auto const asteroidRange   = rlf::Range(1, 3);
            switch (asteroidRange.getValue()) {
                case 1:
                    spawnBigAsteroid();
                    break;

                case 2:
                    spawnMediumAsteroid();
                    break;

                case 3:
                    spawnSmallAsteroid();
                    break;

                default:
                    break;
            }
        }
    }
}
