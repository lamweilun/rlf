#include <Node/Physics/ColliderNode.hpp>

namespace rlf::Node {
    void ColliderNode::setCollidedCallback(std::function<void(rlf::CollideInfo const&)> const& callback) {
        mCollidedCallback = callback;
    }

    void ColliderNode::invokeCollidedCallback(rlf::CollideInfo const& info) const {
        if (mCollidedCallback) {
            mCollidedCallback(info);
        }
    }

    bool ColliderNode::hasCollidedCallback() const {
        return mCollidedCallback != nullptr;
    }

    void ColliderNode::addTag(std::string_view const tag) {
        auto tags = std::set(std::begin(mTags), std::end(mTags));
        tags.insert(tag.data());
        mTags = {std::begin(tags), std::end(tags)};
    }

    std::set<std::string> ColliderNode::getTags() const {
        return std::set(std::begin(mTags), std::end(mTags));
    }

    bool ColliderNode::hasTag(std::string_view const tag) const {
        return std::set(std::begin(mTags), std::end(mTags)).contains(tag.data());
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
