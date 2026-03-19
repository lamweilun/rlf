#pragma once

#define RLF_TYPE_NAME(NAME)                                \
    inline static constexpr std::string_view getTypeName() \
    {                                                      \
        return NAME;                                       \
    }

#define RLF_TYPE_REGISTER(TYPE, NAME)                                \
    RLF_TYPE_NAME(NAME)                                              \
    inline virtual std::string_view getTypeNameImpl() const override \
    {                                                                \
        return getTypeName();                                        \
    }

#define RLF_TYPE_REGISTER_QUICK(TYPE) RLF_TYPE_REGISTER(TYPE, #TYPE)

#ifdef RLF_EDITOR
#define RLF_NODE_ACCESS_START                                        \
    inline virtual rlf::Json serializeImpl() override                \
    {                                                                \
        rlf::acc::JsonSerializer js;                                 \
        access(js);                                                  \
        return js.getJson();                                         \
    }                                                                \
    inline virtual void deserializeImpl(rlf::Json const& j) override \
    {                                                                \
        rlf::acc::JsonDeserializer jd;                               \
        jd.setJson(j);                                               \
        access(jd);                                                  \
    }                                                                \
    inline virtual void imguiAccessImpl() override                   \
    {                                                                \
        rlf::acc::ImGuiAccessor imguiAcc;                            \
        access(imguiAcc);                                            \
    }                                                                \
    inline void access(auto& acc)                                    \
    {
#else
#define RLF_NODE_ACCESS_START                                        \
    inline virtual rlf::Json serializeImpl() override                \
    {                                                                \
        rlf::acc::JsonSerializer js;                                 \
        access(js);                                                  \
        return js.getJson();                                         \
    }                                                                \
    inline virtual void deserializeImpl(rlf::Json const& j) override \
    {                                                                \
        rlf::acc::JsonDeserializer jd;                               \
        jd.setJson(j);                                               \
        access(jd);                                                  \
    }                                                                \
    inline void access(auto& acc)                                    \
    {
#endif

#define RLF_NODE_ACCESS_END }

#define RLF_NODE_ACCESS_PARENT(PARENT)       PARENT::access(acc);
#define RLF_NODE_ACCESS_MEMBER(NAME, MEMBER) acc(NAME, MEMBER);
#define RLF_NODE_ACCESS_MEMBER_GET_SET(NAME, GETTER, SETTER) \
    {                                                        \
        using T = typename std::decay_t<decltype(*this)>;    \
        acc(NAME, &T::GETTER, &T::SETTER, *this);            \
    }
    