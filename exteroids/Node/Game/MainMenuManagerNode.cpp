#include <Node/Game/MainMenuManagerNode.hpp>

#include <Engine/Engine.hpp>

namespace ext
{
    void MainMenuManagerNode::initImpl()
    {
        mStartButton = getRootNode()->getFirstChildOfName<rlf::UIButtonNode>("Start Button").value();
        mExitButton  = getRootNode()->getFirstChildOfName<rlf::UIButtonNode>("Exit Button").value();

        mStartButton->setClickedCallback([]()
                                         {
                                             rlf::Engine::getInstance().setNextWorldToLoad("world/game.json");
                                         });

        mExitButton->setClickedCallback([]()
                                        {
                                            rlf::Engine::getInstance().setToQuit();
                                        });
    }

    void MainMenuManagerNode::updateImpl()
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            rlf::Engine::getInstance().setToQuit();
        }
    }

}
