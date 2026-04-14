#pragma once

#include <Node/BaseNode.hpp>
#include <functional>
#include <set>

#include <System/Physics/CollideInfo.hpp>

namespace rlf
{
    class ColliderNode : public BaseNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(ColliderNode)

        void setCollidedCallback(std::function<void(rlf::CollideInfo const&)> const& callback);
        void invokeCollidedCallback(rlf::CollideInfo const& info) const;
        bool hasCollidedCallback() const;

        std::string const& getTag() const;
        void               setTag(std::string const& tag);

    protected:
        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Tag", getTag, setTag);
        RLF_NODE_ACCESS_END

    private:
        std::function<void(rlf::CollideInfo const&)> mCollidedCallback;
        std::string                                  mTag;
    };
}
