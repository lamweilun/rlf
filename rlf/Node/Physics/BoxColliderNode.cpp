#include <Node/Physics/BoxColliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

namespace rlf::Node {
    void BoxColliderNode::setupImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->addColliderNode(as<BoxColliderNode>());
    }
    void BoxColliderNode::shutdownImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>()->removeColliderNode(as<BoxColliderNode>());
    }
}
