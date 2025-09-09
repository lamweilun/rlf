#include <Node/Game/GameManagerNode.hpp>

#include <Engine/Engine.hpp>

namespace ext::Node {
    void GameManagerNode::initImpl() {
        // Setup Main Menu UI
        mMainMenuUINode  = getFirstChildOfName<rlf::Node::BaseNode>("MainMenuUI").value();
        mStartButtonNode = mMainMenuUINode->getFirstChildOfName<rlf::Node::UIButtonNode>("StartButton").value();
        mStartButtonNode->setClickedCallback([this]() { startGameButtonCallback(); });
        mQuitButtonNode = mMainMenuUINode->getFirstChildOfName<rlf::Node::UIButtonNode>("QuitButton").value();
        mQuitButtonNode->setClickedCallback([]() { rlf::Engine::getInstance().setToQuit(); });

        // Setup Game UI
        mGameUINode = getFirstChildOfName<rlf::Node::BaseNode>("GameUI").value();
    }

    void GameManagerNode::startGameButtonCallback() {
        mMainMenuUINode->setActive(false);
        mGameUINode->setActive(true);
    }
}
