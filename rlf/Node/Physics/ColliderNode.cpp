#include <Node/Physics/ColliderNode.hpp>

#include <System/PhysicsSystem.hpp>

namespace rlf {
    void ColliderNode::updateImpl() {
        for (auto& cn : mCollidedNodes) {
            if (mCollidedCallback) {
                mCollidedCallback(cn);
            }
        }
    }

    void ColliderNode::setCollidedCallback(std::function<void(std::shared_ptr<rlf::ColliderNode>)> callback) {
        mCollidedCallback = callback;
    }
}
