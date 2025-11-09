#include <Node/Asteroid/AsteroidNode.hpp>

#include <Util/Range.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace ext::Node
{
    void AsteroidNode::initImpl()
    {
        mAsteroidCollider = getFirstChildOfType<rlf::Node::CircleColliderNode>().value();
        mAsteroidCollider->setCollidedCallback([this](rlf::CollideInfo const& info)
                                               {
            if (info.other && info.other->getTag() == "PlayerBullet") {
                setHP(getHP() - 1);
            } });

        setSpeed(rlf::Range(50.0f, 100.0f).getValue());
        setVelocityFromAngleDeg(rlf::Range(0.0f, 359.0f).getValue());
        mAnglePerSecond = rlf::Range(-30.0f, 30.0f).getValue();
    }
    void AsteroidNode::updateImpl()
    {
        // Rotate
        setRotationDeg(getRotationDeg() + mAnglePerSecond * GetFrameTime());

        // Check if out of bounds, if it is, bring it back
        auto const pos              = getGlobalPosition();
        auto const screenSize       = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->getScreenSize();
        auto const halfScreenWidth  = screenSize.x * 0.5f;
        auto const halfScreenHeight = screenSize.y * 0.5f;

        if (pos.x <= -halfScreenWidth || pos.x >= halfScreenWidth)
        {
            setPosition({-pos.x, pos.y});
        }
        if (pos.y <= -halfScreenHeight || pos.y >= halfScreenHeight)
        {
            setPosition({pos.x, -pos.y});
        }

        RigidbodyNode::updateImpl();
    }

    void AsteroidNode::setHP(u32 const hp)
    {
        mHP = hp;
        if (mHP == 0)
        {
            setToDestroy(true);
        }
    }
    u32 AsteroidNode::getHP() const
    {
        return mHP;
    }
}
