#include <System/Type/TypeSystem.hpp>

#include <Node/BaseNode.hpp>

namespace rlf::System {
    std::optional<std::shared_ptr<rlf::Node::BaseNode>> TypeSystem::createNode(std::string_view typeName) {
        auto itr = mCreator.find(typeName);
        if (itr == std::end(mCreator)) {
            return std::nullopt;
        }
        return itr->second();
    }

#ifdef RLF_EDITOR
    std::map<std::string_view, std::function<std::shared_ptr<rlf::Node::BaseNode>()>> TypeSystem::getCreatorFuncs() const {
        std::map<std::string_view, std::function<std::shared_ptr<rlf::Node::BaseNode>()>> sortedCreators;
        for (auto const& [name, func] : mCreator) {
            sortedCreators[name] = func;
        }
        return sortedCreators;
    }
#endif
}
