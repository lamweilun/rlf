#include <Node/Game/GameManagerNode.hpp>

#include <Engine/Engine.hpp>

namespace ext::Node {
    void GameManagerNode::initImpl() {
        // Setup Game UI
        mGameUINode = getFirstChildOfName<rlf::Node::BaseNode>("GameUI").value();

        // Setup Player
        mPlayerNode = getRootNode()->getFirstChildOfName<ext::Node::PlayerNode>("PlayerNode").value();

        mGameUINode->setActive(true);
        mPlayerNode->setActive(true);
    }

    void GameManagerNode::updateImpl() {
        if (IsKeyPressed(KEY_ESCAPE)) {
            rlf::Engine::getInstance().setNextWorldToLoad("world/MainMenu.json");
        }
    }
}
