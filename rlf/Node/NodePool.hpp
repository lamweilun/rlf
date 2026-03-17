#pragma once

#include <boost/pool/object_pool.hpp>

namespace rlf::Node
{
    class BaseNode;

    class INodePool
    {
    public:
        INodePool()                            = default;
        virtual ~INodePool()                   = default;
        INodePool(INodePool const&)            = delete;
        INodePool(INodePool&&)                 = delete;
        INodePool& operator=(INodePool const&) = delete;
        INodePool& operator=(INodePool&&)      = delete;

        virtual BaseNode* construct()        = 0;
        virtual void      destroy(BaseNode*) = 0;

    private:
    };

    template <class T>
    class NodePool : public INodePool
    {
    public:
        BaseNode* construct() override
        {
            return static_cast<BaseNode*>(mPool.construct());
        }

        void destroy(BaseNode* node) override
        {
            T* n = static_cast<T*>(node);
            if (!mPool.is_from(n))
            {
                return;
            }
            mPool.destroy(n);
        }

    private:
        boost::object_pool<T> mPool;
    };
}
