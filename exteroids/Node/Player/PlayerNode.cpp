#include <Node/Player/PlayerNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace ext::Node
{

    void PlayerNode::initImpl()
    {
        mPlayerBulletNode = getRootNode()->getFirstChildOfName<ext::Node::PlayerBulletNode>("PlayerBulletNode").value();
        mFireSoudNode     = getFirstChildOfType<rlf::Node::SoundNode>().value();
    }

    void PlayerNode::updateImpl()
    {
        // Mouse Controls
        auto const mousePos  = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->getMousePosition();
        auto const direction = rlf::Vec2f(mousePos - getGlobalPosition()).Normalized();
        setRotation(std::atan2f(direction.y, direction.x));

        // Spawn bullet
        mCurrentFireRate -= GetFrameTime();
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            if (mCurrentFireRate < 0.0f)
            {
                mCurrentFireRate = mFireRate;

                // Play Sound
                mFireSoudNode->play();

                // Spawn a bullet
                auto newBullet = mPlayerBulletNode->clone()->as<ext::Node::PlayerBulletNode>();
                newBullet->setRotation(getRotation());
                newBullet->setPosition(getPosition());
                newBullet->setVelocity(direction);
                newBullet->setActive(true);
            }
        }

        // Movement controls
        rlf::Vec2f newVelocity = rlf::Vec2f::Zero();
        if (IsKeyDown(KEY_W))
        {
            newVelocity.y = -1.0f;
        }
        else if (IsKeyDown(KEY_S))
        {
            newVelocity.y = 1.0f;
        }
        if (IsKeyDown(KEY_A))
        {
            newVelocity.x = -1.0f;
        }
        else if (IsKeyDown(KEY_D))
        {
            newVelocity.x = 1.0f;
        }
        setVelocity(newVelocity.Normalized());

        rlf::Node::RigidbodyNode::updateImpl();
    }
}
