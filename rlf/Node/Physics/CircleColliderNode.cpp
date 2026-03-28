#include <Node/Physics/CircleColliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

namespace rlf::Node
{
    void CircleColliderNode::setupImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::PhysicsSystem>()->addColliderNode(as<CircleColliderNode>());
    }
    void CircleColliderNode::shutdownImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::PhysicsSystem>()->removeColliderNode(as<CircleColliderNode>());
    }
}
