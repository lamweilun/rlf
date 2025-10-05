#include <Node/Physics/ColliderNode.hpp>

#include <System/Physics/PhysicsSystem.hpp>

namespace rlf::Node {
    void ColliderNode::updateImpl() {
        for (auto& cn : mCollidedNodes) {
            if (mCollidedCallback) {
                mCollidedCallback(cn);
            }
        }
    }

    void ColliderNode::shutdownImpl() {
        mCollidedCallback = nullptr;
    }

    void ColliderNode::setCollidedCallback(std::function<void(std::shared_ptr<rlf::Node::ColliderNode>)> callback) {
        mCollidedCallback = callback;
    }

    void ColliderNode::addTag(std::string_view tag) {
        mTags.insert(tag.data());
    }

    std::set<std::string> const& ColliderNode::getTags() const {
        return mTags;
    }

    bool ColliderNode::hasTag(std::string_view tag) const {
        return mTags.contains(tag.data());
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
