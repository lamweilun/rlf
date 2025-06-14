#include <System/PhysicsSystem.hpp>

namespace rlf {
    void PhysicsSystem::addColliderNode(std::shared_ptr<BoxColliderNode> boxColliderNode) {
        mBoxColliderNodes.insert(boxColliderNode);
    }

    void PhysicsSystem::addColliderNode(std::shared_ptr<SphereColliderNode> sphereColliderNode) {
        mSphereColliderNodes.insert(sphereColliderNode);
    }

    void PhysicsSystem::removeColliderNode(std::shared_ptr<BoxColliderNode> boxColliderNode) {
        mBoxColliderNodes.erase(boxColliderNode);
    }

    void PhysicsSystem::removeColliderNode(std::shared_ptr<SphereColliderNode> sphereColliderNode) {
        mSphereColliderNodes.erase(sphereColliderNode);
    }

    std::vector<std::shared_ptr<ColliderNode>> PhysicsSystem::checkCollision(std::shared_ptr<BoxColliderNode> colliderNode) {
        // Initialize data
        std::vector<std::shared_ptr<ColliderNode>> collided;
        BoundingBox                                colliderBB = colliderNode->getBoundingBox();

        // Check against box colliders
        for (auto const& cn : mBoxColliderNodes) {
            if (!cn->getActive()) {
                continue;
            }

            if (cn == colliderNode) {
                continue;
            }

            if (CheckCollisionBoxes(colliderBB, cn->getBoundingBox())) {
                collided.push_back(cn);
            }
        }

        // Check against sphere colliders
        for (auto const& cn : mSphereColliderNodes) {
            if (!cn->getActive()) {
                continue;
            }

            Vector3 const cnGlobalPos   = cn->getGlobalPosition();
            Vector3 const cnGlobalScale = cn->getGlobalScale();
            float const   cnMaxScale    = std::max(cnGlobalScale.x, std::max(cnGlobalScale.y, cnGlobalScale.z));

            if (CheckCollisionBoxSphere(colliderBB, cnGlobalPos, cnMaxScale)) {
                collided.push_back(cn);
            }
        }

        return collided;
    }

    std::vector<std::shared_ptr<ColliderNode>> PhysicsSystem::checkCollision(std::shared_ptr<SphereColliderNode> colliderNode) {
        // Initialize data
        std::vector<std::shared_ptr<ColliderNode>> collided;
        Vector3                                    colliderGlobalPosition = colliderNode->getGlobalPosition();
        Vector3                                    colliderGlobalScale    = colliderNode->getGlobalScale();
        float                                      colliderMaxScale       = std::max(colliderGlobalScale.x, std::max(colliderGlobalScale.y, colliderGlobalScale.z));

        // Check against box colliders
        for (auto const& cn : mBoxColliderNodes) {
            if (!cn->getActive()) {
                continue;
            }

            if (CheckCollisionBoxSphere(cn->getBoundingBox(), colliderGlobalPosition, colliderMaxScale)) {
                collided.push_back(cn);
            }
        }

        // Check against sphere colliders
        for (auto const& cn : mSphereColliderNodes) {
            if (!cn->getActive()) {
                continue;
            }

            if (cn == colliderNode) {
                continue;
            }

            Vector3 const cnGlobalPos   = cn->getGlobalPosition();
            Vector3 const cnGlobalScale = cn->getGlobalScale();
            float const   cnMaxScale    = std::max(cnGlobalScale.x, std::max(cnGlobalScale.y, cnGlobalScale.z));

            if (CheckCollisionSpheres(colliderGlobalPosition, colliderMaxScale, cnGlobalPos, cnMaxScale)) {
                collided.push_back(cn);
            }
        }

        return collided;
    }
}
