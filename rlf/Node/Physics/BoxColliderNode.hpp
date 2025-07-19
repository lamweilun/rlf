#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf {
    class BoxColliderNode : public ColliderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BoxColliderNode)

        void initImpl() override;
        void shutdownImpl() override;

        void updateImpl() override;

        BoundingBox getBoundingBox() const;

    private:
    };
}
