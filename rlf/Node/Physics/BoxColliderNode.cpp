#include <Node/Physics/BoxColliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

namespace rlf
{
    void BoxColliderNode::setupImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::PhysicsSystem>()->addColliderNode(as<BoxColliderNode>());
    }
    void BoxColliderNode::shutdownImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::PhysicsSystem>()->removeColliderNode(as<BoxColliderNode>());
    }
}
