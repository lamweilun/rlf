#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf {
    class SphereColliderNode : public ColliderNode {
    public:
        void initImpl() override;
        void shutdownImpl() override;
        void updateImpl() override;

#ifdef RLF_DEBUG
        void renderImpl() override;
#endif

    private:
    };
}
