#pragma once

#include <System/ISystem.hpp>
#include <System/SystemTable.hpp>

#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

namespace rlf
{
    class PhysicsSystem : public ISystem
    {
    public:
        void addColliderNode(std::shared_ptr<rlf::BoxColliderNode> boxColliderNode);
        void addColliderNode(std::shared_ptr<rlf::CircleColliderNode> circleCollider);

        void removeColliderNode(std::shared_ptr<rlf::BoxColliderNode> boxColliderNode);
        void removeColliderNode(std::shared_ptr<rlf::CircleColliderNode> circleCollider);

        void update() override;

#ifdef RLF_EDITOR
        void editorRender();
#endif

    private:
        rlf::Table<std::shared_ptr<rlf::BoxColliderNode>>    mBoxColliderNodes;
        rlf::Table<std::shared_ptr<rlf::CircleColliderNode>> mCircleColliderNodes;
    };
}
