#include <Node/Physics/ColliderNode.hpp>

#include <System/PhysicsSystem.hpp>

namespace rlf {
    void ColliderNode::initImpl() {
        rlf::PhysicsSystem::getInstance().addNode(std::static_pointer_cast<ColliderNode>(shared_from_this()));
    }

    void ColliderNode::shutdownImpl() {
        rlf::PhysicsSystem::getInstance().removeNode(std::static_pointer_cast<ColliderNode>(shared_from_this()));
    }
}
