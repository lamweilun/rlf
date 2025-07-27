#pragma once

#include <Util/Singleton.hpp>
#include <Node/Physics/LineColliderNode.hpp>
#include <Node/Physics/SphereColliderNode.hpp>

#include <unordered_set>

namespace rlf {
    class PhysicsSystem : public Singleton<PhysicsSystem> {
    public:
        void addColliderNode(std::shared_ptr<LineColliderNode> lineColliderNode);
        void addColliderNode(std::shared_ptr<SphereColliderNode> sphereColliderNode);

        void removeColliderNode(std::shared_ptr<LineColliderNode> lineColliderNode);
        void removeColliderNode(std::shared_ptr<SphereColliderNode> sphereColliderNode);

        std::vector<std::shared_ptr<ColliderNode>> checkCollision(std::shared_ptr<LineColliderNode> colliderNode);
        std::vector<std::shared_ptr<ColliderNode>> checkCollision(std::shared_ptr<SphereColliderNode> colliderNode);

    private:
        std::unordered_set<std::shared_ptr<LineColliderNode>>   mLineColliderNodes;
        std::unordered_set<std::shared_ptr<SphereColliderNode>> mSphereColliderNodes;
    };
}
