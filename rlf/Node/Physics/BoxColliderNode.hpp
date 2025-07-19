#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf {
    class BoxColliderNode : public ColliderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BoxColliderNode)

        BoundingBox getBoundingBox() const;

    protected:
        void initImpl() override;
        void shutdownImpl() override;
        void updateImpl() override;

    private:
    };
}
