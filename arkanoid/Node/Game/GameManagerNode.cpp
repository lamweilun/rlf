#include <Node/Game/GameManagerNode.hpp>

#include <Util/Range.hpp>

#include <Engine/Engine.hpp>

#include <Node/Player/PlayerNode.hpp>
#include <Node/Ball/BallNode.hpp>

namespace ext::Node {
    void GameManagerNode::initImpl() {
        // Setup Game UI
        mGameOverText = getRootNode()->getFirstChildOfName<rlf::Node::UITextNode>("GameOverText").value();

        // Setup Player
        mPlayerNode = getRootNode()->getFirstChildOfName<ark::Node::PlayerNode>("PlayerNode").value();

        mBallNode = getRootNode()->getFirstChildOfName<ark::Node::BallNode>("BallNode").value();

        mBlockGroup = getRootNode()->getFirstChildOfName<rlf::Node::BaseNode>("BlockGroup").value();

        mPlayerNode->setActive(true);
        mBlockGroup->setActive(false);
    }

    void GameManagerNode::updateImpl() {
        if (IsKeyPressed(KEY_ESCAPE)) {
            rlf::Engine::getInstance().setNextWorldToLoad("world/MainMenu.json");
        }

        if (mBallNode->getPosition().y > 400.0f) {
            mGameOverText->setActive(true);
        }

        mCurrentTimer -= GetFrameTime();
        if (mCurrentTimer < 0.0f) {
            mCurrentTimer    = mTimer;
            auto clonedGroup = mBlockGroup->clone();
            clonedGroup->setActive(true);
            for (auto childBlock : mBlockGroups) {
                childBlock->setPosition(childBlock->getPosition() + Vector2{0.0f, 25.0f});
            }
            mBlockGroups.push_back(clonedGroup);
        }
    }
}
