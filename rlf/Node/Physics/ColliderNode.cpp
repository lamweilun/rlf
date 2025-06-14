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

    void ColliderNode::addTag(std::string const& tag) {
        mTags.insert(tag);
    }

    std::set<std::string> const& ColliderNode::getTags() const {
        return mTags;
    }

    bool ColliderNode::hasAnyOfTags(std::set<std::string> const& tags) const {
        for (auto const& tag : mTags) {
            if (tags.contains(tag)) {
                return true;
            }
        }

        return false;
    }
}
