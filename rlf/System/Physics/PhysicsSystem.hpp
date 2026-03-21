#pragma once

#include <System/ISystem.hpp>
#include <System/SystemTable.hpp>

#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

namespace rlf::System
{
    class PhysicsSystem : public ISystem
    {
    public:
        void addColliderNode(rlf::Node::BoxColliderNode* boxColliderNode);
        void addColliderNode(rlf::Node::CircleColliderNode* circleCollider);

        void removeColliderNode(rlf::Node::BoxColliderNode* boxColliderNode);
        void removeColliderNode(rlf::Node::CircleColliderNode* circleCollider);

        void update() override;

#ifdef RLF_EDITOR
        void editorRender();
#endif

    private:
        rlf::System::Table<rlf::Node::BoxColliderNode*>    mBoxColliderNodes;
        rlf::System::Table<rlf::Node::CircleColliderNode*> mCircleColliderNodes;
    };
}
