#pragma once

#include <NodeManager/NodePool.hpp>

#include <unordered_map>
#include <optional>
#include <memory>

#ifdef RLF_EDITOR
#include <set>
#endif

namespace rlf
{
    class BaseNode;

    class NodeManager final
    {
    public:
        NodeManager()                              = default;
        ~NodeManager()                             = default;
        NodeManager(NodeManager const&)            = delete;
        NodeManager(NodeManager&&)                 = delete;
        NodeManager& operator=(NodeManager const&) = delete;
        NodeManager& operator=(NodeManager&&)      = delete;

        template <class T>
        bool registerNodeType()
        {
            static_assert(std::is_base_of_v<rlf::BaseNode, T>);
            mNodePools.insert({T::getTypeName(), std::make_unique<rlf::NodePool<T>>()});
            return true;
        }

        template <class T>
        std::optional<std::shared_ptr<T>> create()
        {
            if (auto result = create(T::getTypeName()))
            {
                return std::static_pointer_cast<T>(result.value());
            }
            return {};
        }
        std::optional<std::shared_ptr<BaseNode>> create(std::string_view typeName);

        template <class T>
        std::optional<std::weak_ptr<T>> getNode(rlf::UUID const& id)
        {
            if (auto result = getNode(T::getTypeName(), id))
            {
                return std::static_pointer_cast<T>(result.value().lock());
            }
            return {};
        }
        std::optional<std::weak_ptr<BaseNode>> getNode(std::string_view typeName, rlf::UUID const& id);

#ifdef RLF_EDITOR
        std::set<std::string_view> getNodePoolNames() const;
#endif

    private:
        std::unordered_map<std::string_view, std::unique_ptr<rlf::INodePool>> mNodePools;
        std::unordered_map<rlf::UUID, std::weak_ptr<BaseNode>>                mCreatedNodes;
    };
}
