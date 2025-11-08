#include <Node/Player/PlayerBulletNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace ext::Node
{

    void PlayerBulletNode::initImpl()
    {
        mBulletParticle = getFirstChildOfType<rlf::Node::BurstParticleRenderNode>().value();

        if (auto const bulletCollider = getFirstChildOfType<rlf::Node::CircleColliderNode>())
        {
            bulletCollider.value()->setCollidedCallback([this](rlf::CollideInfo const& info)
                                                        {
                if (info.other && info.other->getTag() == "Asteroid") {
                    mBulletParticle->setParent(getRootNode());
                    mBulletParticle->setPosition(info.self->getGlobalPosition());

                    auto const angleDeg = rlf::Degrees(info.collidedNormal.Angle(rlf::Vec2f::Right()));
                    std::cout << angleDeg << std::endl;
                    mBulletParticle->setSpawnAngleDegRange({angleDeg - 45.0f, angleDeg + 45.0f});

                    mBulletParticle->setActive(true);

                    setToDestroy(true);
                } });
        }
    }

    void PlayerBulletNode::updateImpl()
    {
        auto const pos              = getGlobalPosition();
        auto const screenSize       = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->getScreenSize();
        auto const halfScreenWidth  = screenSize.x * 0.5f;
        auto const halfScreenHeight = screenSize.y * 0.5f;
        if (pos.x <= -halfScreenWidth || pos.x >= halfScreenWidth)
        {
            setToDestroy(true);
        }
        if (pos.y <= -halfScreenHeight || pos.y >= halfScreenHeight)
        {
            setToDestroy(true);
        }

        rlf::Node::RigidbodyNode::updateImpl();
    }
}
