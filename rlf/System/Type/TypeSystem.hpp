#pragma once

#include <Util/Singleton.hpp>

#include <unordered_map>
#include <functional>
#include <memory>

namespace rlf::Node {
    class BaseNode;
}

namespace rlf::System {

    class TypeSystem : public Singleton<TypeSystem> {
    public:
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

    private:
        std::unordered_map<std::string_view, std::function<std::shared_ptr<rlf::Node::BaseNode>()>> mCreator;
    };
}

#define RLF_TYPE_REGISTER(TYPE, NAME)                                  \
    inline static constexpr std::string_view getTypeName() {           \
        return NAME;                                                   \
    }                                                                  \
    inline virtual std::string_view getTypeNameImpl() const override { \
        return getTypeName();                                          \
    }                                                                  \
    inline static bool typeRegistered = rlf::System::TypeSystem::getInstance().registerType<TYPE>();

#define RLF_TYPE_REGISTER_QUICK(TYPE) RLF_TYPE_REGISTER(TYPE, #TYPE)
