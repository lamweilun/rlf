#pragma once

#include <Util/Singleton.hpp>
#include <Node/Physics/LineColliderNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

#include <unordered_set>

namespace rlf::System {
    class PhysicsSystem : public Singleton<PhysicsSystem> {
    public:
        void addColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode);
        void addColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode);

        void removeColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode);
        void removeColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode);

        std::vector<std::shared_ptr<rlf::Node::ColliderNode>> checkCollision(std::shared_ptr<rlf::Node::LineColliderNode> colliderNode);
        std::vector<std::shared_ptr<rlf::Node::ColliderNode>> checkCollision(std::shared_ptr<rlf::Node::CircleColliderNode> colliderNode);

    private:
        std::unordered_set<std::shared_ptr<rlf::Node::LineColliderNode>>   mLineColliderNodes;
        std::unordered_set<std::shared_ptr<rlf::Node::CircleColliderNode>> mSphereColliderNodes;
    };
}
