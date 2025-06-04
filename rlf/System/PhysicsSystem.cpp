#include <System/PhysicsSystem.hpp>

namespace rlf {
    void PhysicsSystem::addNode(std::shared_ptr<ColliderNode> colliderNode) {
        mColliderNodes.insert(colliderNode);
    }

    void PhysicsSystem::removeNode(std::shared_ptr<ColliderNode> colliderNode) {
        mColliderNodes.erase(colliderNode);
    }

    std::vector<std::shared_ptr<ColliderNode>> PhysicsSystem::checkCollision(std::shared_ptr<ColliderNode> colliderNode) {
        // TODO: Finish this function
        std::vector<std::shared_ptr<ColliderNode>> collided;
        for (auto const& cn : mColliderNodes) {
            if (cn == colliderNode) {
                continue;
            }

            // TODO: Check collision
        }
        return collided;
    }
}
