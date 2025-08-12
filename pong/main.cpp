#include <Engine/Engine.hpp>

#include <Player/PlayerNode.hpp>
#include <Environment/WallNode.hpp>
#include <Ball/BallNode.hpp>

int main() {
    auto& engine = rlf::Engine::getInstance();

    engine.run([](std::shared_ptr<rlf::Node::BaseNode> rootNode) {
        // Add new children here
        auto playerNode = rootNode->addChild<rlf::Node::PlayerNode>();
        playerNode->setPosition({50.0f, 360.0f});

        auto topWallNode = rootNode->addChild<rlf::Node::WallNode>();
        topWallNode->setPosition({640.0f, 20.0f});
        topWallNode->setScale({10.0f, 1200.0f});
        topWallNode->setRotationDeg(90.0f);

        auto bottomWallNode = rootNode->addChild<rlf::Node::WallNode>();
        bottomWallNode->setPosition({640.0f, 700.0f});
        bottomWallNode->setScale({10.0f, 1200.0f});
        bottomWallNode->setRotationDeg(-90.0f);

        auto backWallNode = rootNode->addChild<rlf::Node::WallNode>();
        backWallNode->setPosition({1200.0f, 360.0f});
        backWallNode->setScale({10.0f, 700.0f});
        backWallNode->setRotationDeg(180.0f);

        auto ballNode = rootNode->addChild<rlf::Node::BallNode>();
        ballNode->setPosition({640.0f, 360.0f});
    });
}
