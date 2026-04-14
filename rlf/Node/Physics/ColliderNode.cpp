#include <Node/Physics/ColliderNode.hpp>

namespace rlf
{
    void ColliderNode::setCollidedCallback(std::function<void(rlf::CollideInfo const&)> const& callback)
    {
        mCollidedCallback = callback;
    }

    void ColliderNode::invokeCollidedCallback(rlf::CollideInfo const& info) const
    {
        if (mCollidedCallback)
        {
            mCollidedCallback(info);
        }
    }

    bool ColliderNode::hasCollidedCallback() const
    {
        return mCollidedCallback != nullptr;
    }

    std::string const& ColliderNode::getTag() const
    {
        return mTag;
    }
    void ColliderNode::setTag(std::string const& tag)
    {
        mTag = tag;
    }
}
