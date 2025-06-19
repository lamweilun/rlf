#pragma once

#include <Util/Singleton.hpp>

#include <unordered_map>
#include <functional>

namespace rlf {
    class BaseNode;

    class TypeSystem : public Singleton<TypeSystem> {
        std::unordered_map<std::string_view, std::function<std::shared_ptr<BaseNode>()>> mCreator;

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
        std::optional<std::shared_ptr<BaseNode>> createNode(std::string_view typeName);
    };
}

#define RLF_TYPE_REGISTER(TYPE, NAME)                                  \
    inline static constexpr std::string_view getTypeName() {           \
        return NAME;                                                   \
    }                                                                  \
    inline virtual std::string_view getTypeNameImpl() const override { \
        return getTypeName();                                          \
    }                                                                  \
    inline static bool typeRegistered = rlf::TypeSystem::getInstance().registerType<TYPE>();

#define RLF_TYPE_REGISTER_QUICK(TYPE) RLF_TYPE_REGISTER(TYPE, #TYPE)
