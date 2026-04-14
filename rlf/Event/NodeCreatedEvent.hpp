#pragma once

#include <Event/BaseEvent.hpp>

namespace rlf
{
    class NodeCreatedEvent : public BaseEvent
    {
    public:
        RLF_TYPE_NAME_QUICK(NodeCreatedEvent)

    private:
    };
}
