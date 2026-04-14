#pragma once

#include <Event/BaseEvent.hpp>

#include <functional>     // std::function
#include <mutex>          // std::recursive_mutex
#include <thread>         // std::jthread
#include <unordered_map>  // std::unordered_map

namespace rlf
{
    enum class EVENT_DISPATCH_TYPE : u8
    {
        SEQUENTIAL = 0,
        PARALLEL
    };

    class EventManager final
    {
        using InvokedT   = std::function<void(rlf::BaseEvent *)>;
        using EventCodeT = u64;
        using IndexT     = u64;
        using AddrT      = std::uintptr_t;

    public:
        EventManager()                                = default;
        ~EventManager()                               = default;
        EventManager(EventManager const &)            = delete;
        EventManager(EventManager &&)                 = delete;
        EventManager &operator=(EventManager const &) = delete;
        EventManager &operator=(EventManager &&)      = delete;

        template <class T, class EventType>
        void subscribe([[maybe_unused]] T *t, [[maybe_unused]] void (T::*mem_fn)(EventType *))
        {
            // static_assert(std::is_base_of_v<rlf::BaseEvent, EventType>, "EventType does not inherit from rlf::BaseEvent");

            // EventCodeT const event_code = typeid(EventType).hash_code();
            // AddrT const      addr       = reinterpret_cast<AddrT>(t);

            // std::lock_guard<decltype(mDataMutex)> lock(mDataMutex);

            // auto &subbed_funcs               = mSubbedFuncs[event_code];
            // mAddrCodeIndex[addr][event_code] = subbed_funcs.size();
            // subbed_funcs.push_back([=](rlf::BaseEvent *e)
            //                        {
            //                            (t->*mem_fn)(static_cast<EventType *>(e));
            //                        });
        }

        template <class EventType, class T>
        void unsubscribe([[maybe_unused]] T *t)
        {
            // static_assert(std::is_base_of_v<rlf::BaseEvent, EventType>, "EventType does not inherit from rlf::BaseEvent");

            // EventCodeT const event_code = typeid(EventType).hash_code();
            // AddrT const      addr       = reinterpret_cast<AddrT>(t);

            // std::lock_guard<decltype(mDataMutex)> lock(mDataMutex);

            // if (mAddrCodeIndex[addr].contains(event_code))
            // {
            //     IndexT const index = mAddrCodeIndex[addr][event_code];

            //     auto &subbed_funcs = mSubbedFuncs[event_code];
            //     subbed_funcs[event_code].erase(std::begin(subbed_funcs) + static_cast<i64>(index));
            //     mAddrCodeIndex[addr].erase(event_code);

            //     UpdateIndex(event_code, index);
            // }
        }

        template <class T>
        void unsubscribeAll([[maybe_unused]] T *t)
        {
            // AddrT const addr = reinterpret_cast<AddrT>(t);

            // std::lock_guard<decltype(mDataMutex)> lock(mDataMutex);

            // for (auto &[a, code_index] : mAddrCodeIndex)
            // {
            //     if (a != addr)
            //     {
            //         continue;
            //     }
            //     for (auto &[event_code, index] : code_index)
            //     {
            //         auto &subbed_funcs = mSubbedFuncs[event_code];
            //         subbed_funcs.erase(std::begin(subbed_funcs) + static_cast<i64>(index));

            //         UpdateIndex(event_code, index);
            //     }
            // }
            // mAddrCodeIndex.erase(addr);
        }

        template <class EventType, EVENT_DISPATCH_TYPE dispatchType = EVENT_DISPATCH_TYPE::SEQUENTIAL, class... EventArgs>
        void dispatch([[maybe_unused]] EventArgs &&...args)
        {
            // static_assert(std::is_base_of_v<rlf::BaseEvent, EventType>, "EventType does not inherit from rlf::BaseEvent");

            // EventCodeT const event_code = typeid(EventType).hash_code();
            // EventType        e(std::forward<EventArgs>(args)...);

            // std::lock_guard<decltype(mDataMutex)> lock(mDataMutex);

            // if constexpr (dispatchType == EVENT_DISPATCH_TYPE::SEQUENTIAL)
            // {
            //     for (auto &func : mSubbedFuncs[event_code])
            //     {
            //         func(&e);
            //     }
            // }
            // else if constexpr (dispatchType == EVENT_DISPATCH_TYPE::PARALLEL)
            // {
            //     std::vector<std::thread> jthreads;
            //     for (auto &func : mSubbedFuncs[event_code])
            //     {
            //         jthreads.push_back(func, &e);
            //     }
            //     for (auto &t : jthreads)
            //     {
            //         t.join();
            //     }
            // }
        }

    private:
        void UpdateIndex(EventCodeT event_code, IndexT const i);

        std::recursive_mutex mDataMutex;

        std::unordered_map<EventCodeT, std::vector<InvokedT>>             mSubbedFuncs;
        std::unordered_map<AddrT, std::unordered_map<EventCodeT, IndexT>> mAddrCodeIndex;
    };
}
