#pragma once

#include <Util/Singleton.hpp>
#include <Node/Physics/ColliderNode.hpp>

#include <set>

namespace rlf {
    class PhysicsSystem : public Singleton<PhysicsSystem> {
    public:
        void addNode(std::shared_ptr<ColliderNode> colliderNode);
        void removeNode(std::shared_ptr<ColliderNode> colliderNode);

        std::vector<std::shared_ptr<ColliderNode>> checkCollision(std::shared_ptr<ColliderNode> colliderNode);

    private:
        std::set<std::shared_ptr<ColliderNode>> mColliderNodes;
    };
}
