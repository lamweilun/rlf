#pragma once

#include <Util/Singleton.hpp>
#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/SphereColliderNode.hpp>

#include <unordered_set>

namespace rlf {
    class PhysicsSystem : public Singleton<PhysicsSystem> {
    public:
        void addColliderNode(std::shared_ptr<BoxColliderNode> boxColliderNode);
        void addColliderNode(std::shared_ptr<SphereColliderNode> sphereColliderNode);

        void removeColliderNode(std::shared_ptr<BoxColliderNode> boxColliderNode);
        void removeColliderNode(std::shared_ptr<SphereColliderNode> sphereColliderNode);

        std::vector<std::shared_ptr<ColliderNode>> checkCollision(std::shared_ptr<BoxColliderNode> colliderNode);
        std::vector<std::shared_ptr<ColliderNode>> checkCollision(std::shared_ptr<SphereColliderNode> colliderNode);

    private:
        std::unordered_set<std::shared_ptr<BoxColliderNode>>    mBoxColliderNodes;
        std::unordered_set<std::shared_ptr<SphereColliderNode>> mSphereColliderNodes;
    };
}
