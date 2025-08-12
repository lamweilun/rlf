#pragma once

#include <Engine/Engine.hpp>

namespace rlf {
    template <class T>
    void Engine::addSystem() {
        static_assert(std::is_base_of_v<rlf::System::ISystem, T>);
        std::string const runtimeTypeName = typeid(T).name();
        if (mSystemLUT.contains(runtimeTypeName)) {
            return;
        }
        mSystemLUT.insert({typeid(T).name(), mSystems.size()});
        mSystems.push_back(std::make_shared<T>());
    }

    template <class T>
    std::shared_ptr<T> Engine::getSystem() const {
        static_assert(std::is_base_of_v<rlf::System::ISystem, T>);
        std::string const runtimeTypeName = typeid(T).name();
        if (!mSystemLUT.contains(runtimeTypeName)) {
            return nullptr;
        }
        return std::static_pointer_cast<T>(mSystems.at(mSystemLUT.at(runtimeTypeName)));
    }
}
