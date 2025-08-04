#include <Engine/Engine.hpp>

#include <Player/PlayerNode.hpp>
#include <Environment/WallNode.hpp>
#include <Ball/BallNode.hpp>

int main() {
    rlf::Engine engine;

    engine.run([](std::shared_ptr<rlf::BaseNode> rootNode) {
        // Add new children here
        auto playerNode = rootNode->addChild<rlf::PlayerNode>();
        playerNode->setPosition({50.0f, 360.0f});

        auto topWallNode = rootNode->addChild<rlf::WallNode>();
        topWallNode->setPosition({640.0f, 20.0f});
        topWallNode->setScale({10.0f, 1200.0f});
        topWallNode->setRotationDeg(90.0f);

        auto bottomWallNode = rootNode->addChild<rlf::WallNode>();
        bottomWallNode->setPosition({640.0f, 700.0f});
        bottomWallNode->setScale({10.0f, 1200.0f});
        bottomWallNode->setRotationDeg(-90.0f);

        auto backWallNode = rootNode->addChild<rlf::WallNode>();
        backWallNode->setPosition({1200.0f, 360.0f});
        backWallNode->setScale({10.0f, 700.0f});
        backWallNode->setRotationDeg(180.0f);

        auto ballNode = rootNode->addChild<rlf::BallNode>();
        ballNode->setPosition({640.0f, 360.0f});
    });
}
