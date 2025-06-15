#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf {
    class BoxColliderNode : public ColliderNode {
    public:
        void initImpl() override;
        void shutdownImpl() override;

        void updateImpl() override;

        BoundingBox getBoundingBox() const;

#ifdef RLF_DEBUG
        void renderImpl() override;
#endif

    private:
    };
}
