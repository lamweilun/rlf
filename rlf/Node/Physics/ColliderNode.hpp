#pragma once

#include <Node/BaseNode.hpp>
#include <functional>
#include <set>

namespace rlf {
    class ColliderNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(ColliderNode)

        void      updateImpl() override;
        rlf::Json serializeImpl() const override;
        void      setCollidedCallback(std::function<void(std::shared_ptr<rlf::ColliderNode>)> callback);

        void                         addTag(std::string const& tag);
        std::set<std::string> const& getTags() const;
        bool                         hasAnyOfTags(std::set<std::string> const& tags) const;

    protected:
        std::vector<std::shared_ptr<ColliderNode>> mCollidedNodes;

    private:
        std::set<std::string> mTags;

        std::function<void(std::shared_ptr<rlf::ColliderNode>)> mCollidedCallback;
    };
}
