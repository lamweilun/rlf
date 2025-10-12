#pragma once

#include <Node/BaseNode.hpp>
#include <functional>
#include <set>

#include <System/Physics/CollideInfo.hpp>

namespace rlf::Node {
    class ColliderNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(ColliderNode)
        void setCollidedCallback(std::function<void(std::vector<rlf::CollideInfo> const&)> callback);

        void                         addTag(std::string_view tag);
        std::set<std::string> const& getTags() const;
        bool                         hasTag(std::string_view tag) const;
        bool                         hasAnyOfTags(std::set<std::string> const& tags) const;

    protected:
        void updateImpl() override;

        std::vector<rlf::CollideInfo>                             mCollisionInfos;
        std::function<void(std::vector<rlf::CollideInfo> const&)> mCollidedCallback;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER("tags", mTags)
        RLF_NODE_ACCESS_END

    private:
        std::set<std::string> mTags;
    };
}
