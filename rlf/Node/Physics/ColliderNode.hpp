#pragma once

#include <Node/BaseNode.hpp>
#include <functional>
#include <set>

namespace rlf::Node {
    class ColliderNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(ColliderNode)
        void setCollidedCallback(std::function<void(std::shared_ptr<rlf::Node::ColliderNode>)> callback);

        void                         addTag(std::string const& tag);
        std::set<std::string> const& getTags() const;
        bool                         hasTag(std::string const& tag) const;
        bool                         hasAnyOfTags(std::set<std::string> const& tags) const;

    protected:
        void updateImpl() override;
        void shutdownImpl() override;

        std::vector<std::shared_ptr<ColliderNode>>                    mCollidedNodes;
        std::function<void(std::shared_ptr<rlf::Node::ColliderNode>)> mCollidedCallback;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER("tags", mTags)
        RLF_NODE_ACCESS_END

    private:
        std::set<std::string> mTags;
    };
}
