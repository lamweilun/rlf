#include <Node/Player/PlayerNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace ext::Node {

    void PlayerNode::initImpl() {
        mPlayerBulletNode = getRootNode()->getFirstChildOfName<ext::Node::PlayerBulletNode>("PlayerBulletNode").value();
    }

    void PlayerNode::updateImpl() {
        // Mouse Controls
        auto const mousePos  = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->getMousePosition();
        auto const direction = Vector2Normalize(mousePos - getGlobalPosition());
        setRotation(std::atan2f(direction.y, direction.x));

        // Spawn bullet
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            auto newBullet = mPlayerBulletNode->clone()->as<ext::Node::PlayerBulletNode>();
            newBullet->setPosition(getPosition());
            newBullet->setVelocity(direction);
            newBullet->setActive(true);
        }

        // Movement controls
        Vector2 newVelocity = Vector2Zeros;
        if (IsKeyDown(KEY_W)) {
            newVelocity.y = -1.0f;
        } else if (IsKeyDown(KEY_S)) {
            newVelocity.y = 1.0f;
        }
        if (IsKeyDown(KEY_A)) {
            newVelocity.x = -1.0f;
        } else if (IsKeyDown(KEY_D)) {
            newVelocity.x = 1.0f;
        }
        setVelocity(Vector2Normalize(newVelocity));

        rlf::Node::RigidbodyNode::updateImpl();
    }
}
