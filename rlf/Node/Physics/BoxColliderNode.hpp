#pragma once

#include <Node/Physics/ColliderNode.hpp>

namespace rlf::Node {
    class BoxColliderNode : public ColliderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(BoxColliderNode)

    protected:
        void setupImpl() override;
        void shutdownImpl() override;

    private:
    };
}
