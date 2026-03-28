#pragma once

#include <System/ISystem.hpp>

#include <memory>
#include <unordered_map>

namespace rlf
{
    class SystemManager
    {
    public:
        template <class T>
        void registerSystem()
        {
            static_assert(std::is_base_of_v<rlf::ISystem, T>);
            std::string const runtimeTypeName = typeid(T).name();
            if (mSystemLUT.contains(runtimeTypeName))
            {
                return;
            }
            mSystemLUT.insert({typeid(T).name(), mSystems.size()});
            mSystems.push_back(std::make_shared<T>());
        }

        template <class T>
        std::shared_ptr<T> getSystem() const
        {
            static_assert(std::is_base_of_v<rlf::ISystem, T>);
            std::string const runtimeTypeName = typeid(T).name();
            if (!mSystemLUT.contains(runtimeTypeName))
            {
                return nullptr;
            }
            return std::static_pointer_cast<T>(mSystems.at(mSystemLUT.at(runtimeTypeName)));
        }

        std::vector<std::shared_ptr<ISystem>>&       getSystems();
        std::vector<std::shared_ptr<ISystem>> const& getSystems() const;

    private:
        std::vector<std::shared_ptr<ISystem>> mSystems;
        std::unordered_map<std::string, u64>  mSystemLUT;
    };
}
