#include <Node/NodeManager.hpp>

#include <Node/BaseNode.hpp>

namespace rlf
{
    std::optional<rlf::Node::BaseNode*> NodeManager::create(std::string_view typeName)
    {
        auto itr = mNodePools.find(typeName);
        if (itr == std::end(mNodePools))
        {
            return {};
        }
        return itr->second->construct();
    }

    void NodeManager::destroy(rlf::Node::BaseNode* node)
    {
        auto typeName = node->getTypeNameImpl();
        auto itr      = mNodePools.find(typeName);
        if (itr == std::end(mNodePools))
        {
            return;
        }
        itr->second->destroy(node);
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
