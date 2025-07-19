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
        void      updateImpl() override;
        rlf::Json serializeImpl() const override;
        void      deserializeImpl(rlf::Json const& j) override;

        std::vector<std::shared_ptr<ColliderNode>> mCollidedNodes;

    private:
        std::set<std::string> mTags;

        std::function<void(std::shared_ptr<rlf::ColliderNode>)> mCollidedCallback;
    };
}
