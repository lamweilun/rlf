#pragma once

#include <Node/BaseNode.hpp>
#include <functional>

namespace rlf {
    class ColliderNode : public BaseNode {
    public:
        void updateImpl() override;
        void setCollidedCallback(std::function<void(std::shared_ptr<rlf::ColliderNode>)> callback);

    protected:
        std::vector<std::shared_ptr<ColliderNode>> mCollidedNodes;

    private:
        std::function<void(std::shared_ptr<rlf::ColliderNode>)> mCollidedCallback;
    };
}
