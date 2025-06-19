#include <System/TypeSystem.hpp>

#include <Node/BaseNode.hpp>

namespace rlf {
    std::optional<std::shared_ptr<BaseNode>> TypeSystem::createNode(std::string_view typeName) {
        auto itr = mCreator.find(typeName);
        if (itr == std::end(mCreator)) {
            return std::nullopt;
        }
        return itr->second();
    }
}
