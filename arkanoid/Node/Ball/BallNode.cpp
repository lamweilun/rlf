#include <Node/Ball/BallNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace ark::Node {

    void BallNode::initImpl() {
        mScoreText = getRootNode()->getFirstChildOfName<rlf::Node::UITextNode>("ScoreText").value();
        mScoreText->setText("Score: " + std::to_string(score));

        collider = getFirstChildOfType<rlf::Node::CircleColliderNode>().value();
        collider->setCollidedCallback([this](rlf::CollideInfo const& info) {
            if (info.other->hasTag("Player") || info.other->hasTag("Block")) {
                std::cout << info.collidedNormal << std::endl;
                auto reflected = Vector2Reflect(getVelocity(), info.collidedNormal);
                auto odds      = rlf::Range<f32>(0.0f, 1.0f).getValue();
                if (odds > 0.5f) {
                    reflected.x = -reflected.x;
                }
                setVelocity(reflected);

                ++score;
                mScoreText->setText("Score: " + std::to_string(score));
            }
        });
    }

    void BallNode::updateImpl() {
        // Check if out of bounds, if it is, bring it back
        auto const pos             = getGlobalPosition();
        auto const screenSize      = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->getScreenSize();
        auto const halfScreenWidth = screenSize.x * 0.5f;

        if (pos.x <= -halfScreenWidth || pos.x >= halfScreenWidth) {
            setPosition({-pos.x, pos.y});
        }

        RigidbodyNode::updateImpl();
    }
}
