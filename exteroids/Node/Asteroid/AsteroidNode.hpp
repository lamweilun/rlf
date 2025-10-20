#pragma once

#include <Node/Physics/RigidbodyNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

namespace ext::Node {
    class AsteroidNode : public rlf::Node::RigidbodyNode {
    public:
        RLF_TYPE_REGISTER_QUICK(AsteroidNode)

        void setHP(u32 const hp);
        u32  getHP() const;

    protected:
        void initImpl() override;
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(RigidbodyNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("HP", getHP, setHP)
        RLF_NODE_ACCESS_END

    private:
        std::shared_ptr<rlf::Node::CircleColliderNode> mAsteroidCollider;

        u32 mHP             = 1;
        f32 mAnglePerSecond = 0.0f;
    };
}
