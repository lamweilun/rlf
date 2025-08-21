#pragma once

#include <unordered_map>
#include <functional>
#include <optional>
#include <memory>

namespace rlf::Node {
    class BaseNode;
}

namespace rlf {
    class TypeManager {
    public:
        static TypeManager& getInstance() {
            static TypeManager instance;
            return instance;
        }

        template <class T>
        bool registerType() {
            mCreator.insert({T::getTypeName(), []() {
                                 return std::make_shared<T>();
                             }});
            return true;
        }

        template <class T>
        std::optional<std::shared_ptr<T>> createNode() const {
            return createNode(T::getTypeName());
        }
        std::optional<std::shared_ptr<rlf::Node::BaseNode>> createNode(std::string_view typeName);

#ifdef RLF_EDITOR
        std::map<std::string_view, std::function<std::shared_ptr<rlf::Node::BaseNode>()>> getCreatorFuncs() const;
#endif

    private:
        std::unordered_map<std::string_view, std::function<std::shared_ptr<rlf::Node::BaseNode>()>> mCreator;
    };
}

#define RLF_TYPE_NAME(NAME)                                  \
    inline static constexpr std::string_view getTypeName() { \
        return NAME;                                         \
    }

#define RLF_TYPE_REGISTER(TYPE, NAME)                                  \
    RLF_TYPE_NAME(NAME)                                                \
    inline virtual std::string_view getTypeNameImpl() const override { \
        return getTypeName();                                          \
    }

#define RLF_TYPE_REGISTER_QUICK(TYPE) RLF_TYPE_REGISTER(TYPE, #TYPE)
