#include <Event/EventManager.hpp>

namespace rlf
{
    void EventManager::UpdateIndex([[maybe_unused]] EventCodeT event_code, [[maybe_unused]] IndexT const i)
    {
        // for (auto &[addr, code_index] : mAddrCodeIndex)
        // {
        //     for (auto &[code, index] : code_index)
        //     {
        //         if (code != event_code)
        //         {
        //             continue;
        //         }
        //         if (index > i)
        //         {
        //             --index;
        //         }
        //     }
        // }
    }
}
