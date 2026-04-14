#pragma once

#define RLF_TYPE_NAME(NAME)                                \
    inline static constexpr std::string_view getTypeName() \
    {                                                      \
        return NAME;                                       \
    }

#define RLF_TYPE_NAME_QUICK(TYPE) RLF_TYPE_NAME(#TYPE)
