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
        return itr->second->destroy(node);
    }

    std::optional<std::shared_ptr<rlf::Node::BaseNode>> NodeManager::createNode(std::string_view typeName)
    {
        auto itr = mCreator.find(typeName);
        if (itr == std::end(mCreator))
        {
            return std::nullopt;
        }
        return itr->second();
    }

#ifdef RLF_EDITOR
    std::map<std::string_view, std::function<std::shared_ptr<rlf::Node::BaseNode>()>> NodeManager::getCreatorFuncs() const
    {
        std::map<std::string_view, std::function<std::shared_ptr<rlf::Node::BaseNode>()>> sortedCreators;
        for (auto const& [name, func] : mCreator)
        {
            sortedCreators[name] = func;
        }
        return sortedCreators;
    }
#endif
}
