#pragma once

#include <System/ISystem.hpp>
#include <Node/Physics/LineColliderNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

#include <System/Physics/CollideInfo.hpp>

#include <unordered_set>

namespace rlf::System {
    class PhysicsSystem : public ISystem {
    public:
        void addColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode);
        void addColliderNode(std::shared_ptr<rlf::Node::BoxColliderNode> boxColliderNode);
        void addColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode);

        void removeColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode);
        void removeColliderNode(std::shared_ptr<rlf::Node::BoxColliderNode> boxColliderNode);
        void removeColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode);

        std::vector<rlf::CollideInfo> getCollisionInfos(std::shared_ptr<rlf::Node::LineColliderNode> colliderNode);
        std::vector<rlf::CollideInfo> getCollisionInfos(std::shared_ptr<rlf::Node::BoxColliderNode> colliderNode);
        std::vector<rlf::CollideInfo> getCollisionInfos(std::shared_ptr<rlf::Node::CircleColliderNode> colliderNode);

#ifdef RLF_EDITOR
        void editorRender();
#endif

    private:
        std::unordered_set<std::shared_ptr<rlf::Node::LineColliderNode>>   mLineColliderNodes;
        std::unordered_set<std::shared_ptr<rlf::Node::BoxColliderNode>>    mBoxColliderNodes;
        std::unordered_set<std::shared_ptr<rlf::Node::CircleColliderNode>> mCircleColliderNodes;
    };
}
