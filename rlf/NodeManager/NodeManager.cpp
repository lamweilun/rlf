#include <NodeManager/NodeManager.hpp>

#include <Node/BaseNode.hpp>

namespace rlf
{
    std::optional<std::shared_ptr<BaseNode>> NodeManager::create(std::string_view typeName)
    {
        auto itr = mNodePools.find(typeName);
        if (itr == std::end(mNodePools))
        {
            return {};
        }

        // Create id and node
        auto id   = rlf::generateUUID();
        auto node = std::shared_ptr<BaseNode>(itr->second->construct(), [this, node_type_name = typeName](rlf::BaseNode* n)
                                              {
                                                  mCreatedNodes.erase(n->getID());
                                                  auto nodepool = mNodePools.find(node_type_name);
                                                  if (nodepool != std::end(mNodePools))
                                                  {
                                                      nodepool->second->destroy(n);
                                                  }
                                              });
        mCreatedNodes.insert({id, node});
        node->mID = id;
        return node;
    }

    std::optional<std::weak_ptr<BaseNode>> NodeManager::getNode(std::string_view typeName, rlf::UUID const& id)
    {
        // Check if node type has been registered
        auto nodepool_itr = mNodePools.find(typeName);
        if (nodepool_itr == std::end(mNodePools))
        {
            return {};
        }

        // Check if node of this ID still exists
        auto created_node_itr = mCreatedNodes.find(id);
        if (created_node_itr == std::end(mCreatedNodes))
        {
            return {};
        }

        // Check if there are still any strong references to this node
        if (created_node_itr->second.expired())
        {
            mCreatedNodes.erase(created_node_itr);
            return {};
        }

        return created_node_itr->second;
    }

#ifdef RLF_EDITOR
    std::set<std::string_view> NodeManager::getNodePoolNames() const
    {
        std::set<std::string_view> sortedNames;
        for (auto const& [name, _] : mNodePools)
        {
            sortedNames.insert(name);
        }
        return sortedNames;
    }
#endif
}
