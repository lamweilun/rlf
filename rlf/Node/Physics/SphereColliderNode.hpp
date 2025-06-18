#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf {
    class SphereColliderNode : public ColliderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(SphereColliderNode)

        void initImpl() override;
        void shutdownImpl() override;
        void updateImpl() override;

#ifdef RLF_DEBUG
        void renderImpl() override;
#endif

    private:
    };
}
