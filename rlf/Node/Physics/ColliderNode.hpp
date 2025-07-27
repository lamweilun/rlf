#pragma once

#include <Node/BaseNode.hpp>
#include <functional>
#include <set>

namespace rlf {
    class ColliderNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(ColliderNode)
        void setCollidedCallback(std::function<void(std::shared_ptr<rlf::ColliderNode>)> callback);

        void                         addTag(std::string const& tag);
        std::set<std::string> const& getTags() const;
        bool                         hasTag(std::string const& tag) const;
        bool                         hasAnyOfTags(std::set<std::string> const& tags) const;

    protected:
        void updateImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER("tags", mTags)
        RLF_NODE_ACCESS_END

        std::vector<std::shared_ptr<ColliderNode>>              mCollidedNodes;
        std::function<void(std::shared_ptr<rlf::ColliderNode>)> mCollidedCallback;

    private:
        std::set<std::string> mTags;
    };
}
