#pragma once

#include <Node/NodePool.hpp>

#include <unordered_map>
#include <set>
#include <optional>
#include <memory>

namespace rlf::Node
{
    class BaseNode;
}

namespace rlf
{
    class NodeManager
    {
    public:
        static NodeManager& getInstance()
        {
            static NodeManager instance;
            return instance;
        }

        template <class T>
        bool registerType()
        {
            mNodePools.insert({T::getTypeName(), std::make_unique<rlf::Node::NodePool<T>>()});

            return true;
        }

        template <class T>
        std::optional<T*> create()
        {
            if (auto result = create(T::getTypeName()))
            {
                return static_cast<T*>(result.value());
            }
            return {};
        }
        std::optional<rlf::Node::BaseNode*> create(std::string_view typeName);

        void destroy(rlf::Node::BaseNode* node);

#ifdef RLF_EDITOR
        std::set<std::string_view> getNodePoolNames() const;
#endif

    private:
        std::unordered_map<std::string_view, std::unique_ptr<rlf::Node::INodePool>> mNodePools;
    };
}
