#include <Node/Game/MainMenuManagerNode.hpp>

#include <Engine/Engine.hpp>

namespace ext::Node {
    void MainMenuManagerNode::initImpl() {
        mStartButton = getRootNode()->getFirstChildOfName<rlf::Node::UIButtonNode>("Start Button").value();
        mExitButton  = getRootNode()->getFirstChildOfName<rlf::Node::UIButtonNode>("Exit Button").value();

        mStartButton->setClickedCallback([]() {
            rlf::Engine::getInstance().setNextWorldToLoad("world/game.json");
        });

        mExitButton->setClickedCallback([]() {
            rlf::Engine::getInstance().setToQuit();
        });
    }

    void MainMenuManagerNode::updateImpl() {
        if (IsKeyPressed(KEY_ESCAPE)) {
            rlf::Engine::getInstance().setToQuit();
        }
    }

}
