#include <System/SystemManager.hpp>

namespace rlf
{
    std::vector<std::shared_ptr<ISystem>>& SystemManager::getSystems()
    {
        return mSystems;
    }
    std::vector<std::shared_ptr<ISystem>> const& SystemManager::getSystems() const
    {
        return mSystems;
    }
}
