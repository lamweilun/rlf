#pragma once

#include <System/Type/TypeSystem.hpp>

#include <Util/Accessor/JsonSerializer.hpp>
#include <Util/Accessor/JsonDeserializer.hpp>
#ifdef RLF_EDITOR
#include <System/Editor/ImGuiAccessor.hpp>
#include <System/Editor/EditorSystem.hpp>
#endif

#include <memory>
#include <vector>

#ifdef RLF_EDITOR
#define RLF_NODE_ACCESS_START                                          \
    inline virtual rlf::Json serializeImpl() override {                \
        rlf::acc::JsonSerializer js;                                   \
        access(js);                                                    \
        return js.getJson();                                           \
    }                                                                  \
    inline virtual void deserializeImpl(rlf::Json const& j) override { \
        rlf::acc::JsonDeserializer jd;                                 \
        jd.setJson(j);                                                 \
        access(jd);                                                    \
    }                                                                  \
    inline virtual void imguiAccessImpl() override {                   \
        rlf::acc::ImGuiAccessor imguiAcc;                              \
        access(imguiAcc);                                              \
    }                                                                  \
    inline void access(auto& acc) {
#else
#define RLF_NODE_ACCESS_START                                          \
    inline virtual rlf::Json serializeImpl() override {                \
        rlf::acc::JsonSerializer js;                                   \
        access(js);                                                    \
        return js.getJson();                                           \
    }                                                                  \
    inline virtual void deserializeImpl(rlf::Json const& j) override { \
        rlf::acc::JsonDeserializer jd;                                 \
        jd.setJson(j);                                                 \
        access(jd);                                                    \
    }                                                                  \
    inline void access(auto& acc) {
#endif

#define RLF_NODE_ACCESS_END }

#define RLF_NODE_ACCESS_PARENT(PARENT)       PARENT::access(acc);
#define RLF_NODE_ACCESS_MEMBER(NAME, MEMBER) acc(NAME, MEMBER);
#define RLF_NODE_ACCESS_MEMBER_GET_SET(NAME, GETTER, SETTER) \
    {                                                        \
        using T = typename std::decay_t<decltype(*this)>;    \
        acc(NAME, &T::GETTER, &T::SETTER, *this);            \
    }

namespace rlf::Node {
    class BaseNode : public std::enable_shared_from_this<BaseNode> {
    public:
        BaseNode()                           = default;
        virtual ~BaseNode()                  = default;
        BaseNode(BaseNode const&)            = default;
        BaseNode(BaseNode&&)                 = default;
        BaseNode& operator=(BaseNode const&) = default;
        BaseNode& operator=(BaseNode&&)      = default;

        static inline constexpr std::string_view getTypeName() {
            return "BaseNode";
        }
        inline virtual std::string_view getTypeNameImpl() const {
            return getTypeName();
        }
        static inline bool typeRegistered = rlf::System::TypeSystem::getInstance().registerType<BaseNode>();

        template <class T>
        std::shared_ptr<T>        addChild();
        std::shared_ptr<BaseNode> addChild(std::string_view typeName);

        template <class T>
        std::optional<std::shared_ptr<T>>        getFirstChildOfType() const;
        std::optional<std::shared_ptr<BaseNode>> getFirstChildOfType(std::string_view typeName) const;

        template <class T>
        std::shared_ptr<T>        addOrGetFirstChildOfType();
        std::shared_ptr<BaseNode> addOrGetFirstChildOfType(std::string_view typeName);

        Vector2 const& getPosition() const;
        void           setPosition(Vector2 const& position);
        Vector2 const& getScale() const;
        void           setScale(Vector2 const& scale);
        f32 const&     getRotation() const;
        void           setRotation(f32 const rotation);
        f32            getRotationDeg() const;
        void           setRotationDeg(f32 const rotationDeg);

        std::string const& getName() const;
        void               setName(std::string const& name);

        bool getActive() const;
        bool getActiveSelf() const;
        void setActive(bool const active);

        void setToDestroy(bool const toDestroy);

        bool                      isRootNode() const;
        std::shared_ptr<BaseNode> getRootNode();
        Matrix const&             getLocalTransform() const;
        Matrix const&             getGlobalTransform() const;
        Vector2                   getGlobalRight() const;
        Vector2                   getGlobalPosition() const;
        Vector2                   getGlobalScale() const;
        Quaternion                getGlobalRotation() const;

        bool                                          hasParent() const;
        std::weak_ptr<BaseNode>                       getParent() const;
        void                                          setParent(std::shared_ptr<BaseNode> newParent);
        std::vector<std::shared_ptr<BaseNode>>&       getChildren();
        std::vector<std::shared_ptr<BaseNode>> const& getChildren() const;
        std::vector<std::shared_ptr<BaseNode>>        getAllChildren();

        void      init();
        void      shutdown();
        void      update();
        rlf::Json serialize();
        void      deserialize(rlf::Json const& j);

        void deserializeFromFile(std::string const& filePath);

    protected:
        virtual void setActiveImpl(bool const selfActive);
        virtual void initImpl();
        virtual void shutdownImpl();
        virtual void updateImpl();

    private:
        void markGlobalDirty();

        std::string mName;

        bool mActive    = true;
        bool mToDestroy = false;
        bool mHasInited = false;

        mutable Matrix mLocalTransform  = MatrixIdentity();
        mutable Matrix mGlobalTransform = MatrixIdentity();
        Vector2        mPosition        = Vector2Zeros;
        Vector2        mScale           = Vector2Ones;
        f32            mRotation        = 0.0f;
        mutable bool   mLocalDirty      = true;
        mutable bool   mGlobalDirty     = true;

        std::weak_ptr<BaseNode>                mRootNode;
        std::weak_ptr<BaseNode>                mParent;
        std::vector<std::shared_ptr<BaseNode>> mChildren;
        std::vector<std::shared_ptr<BaseNode>> mNewChildren;

    protected:
        inline void access(auto& acc) {
            RLF_NODE_ACCESS_MEMBER_GET_SET("active", getActiveSelf, setActive);
            RLF_NODE_ACCESS_MEMBER_GET_SET("name", getName, setName);
            RLF_NODE_ACCESS_MEMBER_GET_SET("position", getPosition, setPosition);
            RLF_NODE_ACCESS_MEMBER_GET_SET("scale", getScale, setScale);
            RLF_NODE_ACCESS_MEMBER_GET_SET("rotation", getRotationDeg, setRotationDeg);
        }

        inline virtual rlf::Json serializeImpl() {
            rlf::acc::JsonSerializer js;
            access(js);
            return js.getJson();
        }
        inline virtual void deserializeImpl(rlf::Json const& j) {
            rlf::acc::JsonDeserializer jd;
            jd.setJson(j);
            access(jd);
        }
#ifdef RLF_EDITOR
        friend class rlf::System::EditorSystem;
        inline virtual void imguiAccessImpl() {
            rlf::acc::ImGuiAccessor imguiAcc;
            access(imguiAcc);
        }
        bool mToShiftDown = false;
        bool mToShiftUp   = false;
#endif
    };
}

#include <Node/BaseNodeImpl.hpp>
