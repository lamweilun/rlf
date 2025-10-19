#pragma once

#include <Node/BaseNode.hpp>
#include <functional>
#include <set>

#include <System/Physics/CollideInfo.hpp>

namespace rlf::Node {
    class ColliderNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(ColliderNode)

        void setCollidedCallback(std::function<void(rlf::CollideInfo const&)> const& callback);
        void invokeCollidedCallback(rlf::CollideInfo const& info) const;
        bool hasCollidedCallback() const;

        void                  addTag(std::string_view const tag);
        std::set<std::string> getTags() const;
        bool                  hasTag(std::string_view const tag) const;
        bool                  hasAnyOfTags(std::set<std::string> const& tags) const;

    protected:
        std::function<void(rlf::CollideInfo const&)> mCollidedCallback;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER("tags", mTags)
        RLF_NODE_ACCESS_END

    private:
        std::vector<std::string> mTags;
    };
}
