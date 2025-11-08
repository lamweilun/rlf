#pragma once

#include <Manager/TypeManager.hpp>

#include <Util/Accessor/JsonSerializer.hpp>
#include <Util/Accessor/JsonDeserializer.hpp>
#ifdef RLF_EDITOR
#include <System/Editor/ImGuiAccessor.hpp>
#include <System/Editor/EditorSystem.hpp>
#endif

#include <memory>
#include <vector>

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

namespace rlf::Node
{
    class BaseNode : public std::enable_shared_from_this<BaseNode>
    {
    public:
        BaseNode()                           = default;
        virtual ~BaseNode()                  = default;
        BaseNode(BaseNode const&)            = default;
        BaseNode(BaseNode&&)                 = default;
        BaseNode& operator=(BaseNode const&) = default;
        BaseNode& operator=(BaseNode&&)      = default;

        static inline constexpr std::string_view getTypeName()
        {
            return "BaseNode";
        }
        inline virtual std::string_view getTypeNameImpl() const
        {
            return getTypeName();
        }

        template <class T>
        std::shared_ptr<T>        addChild();
        std::shared_ptr<BaseNode> addChild(std::string_view typeName);

        template <class T>
        std::optional<std::shared_ptr<T>>        getFirstChildOfType() const;
        std::optional<std::shared_ptr<BaseNode>> getFirstChildOfType(std::string_view typeName) const;

        template <class T>
        std::shared_ptr<T>        addOrGetFirstChildOfType();
        std::shared_ptr<BaseNode> addOrGetFirstChildOfType(std::string_view typeName);

        template <class T>
        std::optional<std::shared_ptr<T>> getFirstChildOfName(std::string_view childName) const;

        template <class T>
        bool is();

        template <class T>
        std::shared_ptr<T> as();
        template <class T>
        std::shared_ptr<T> as() const;

        rlf::Vec2f const& getPosition() const;
        void              setPosition(rlf::Vec2f const& position);
        rlf::Vec2f const& getScale() const;
        void              setScale(rlf::Vec2f const& scale);
        f32 const&        getRotation() const;
        void              setRotation(f32 const rotation);
        f32               getRotationDeg() const;
        void              setRotationDeg(f32 const rotationDeg);

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
        rlf::Vec2f                getGlobalRight() const;
        rlf::Vec2f                getGlobalPosition() const;
        rlf::Vec2f                getGlobalScale() const;
        Quaternion                getGlobalRotation() const;
        f32                       getGlobalRotationRad() const;
        f32                       getGlobalRotationDeg() const;

        bool                                          hasParent() const;
        std::weak_ptr<BaseNode>                       getParent() const;
        void                                          setParent(std::shared_ptr<BaseNode> newParent);
        std::vector<std::shared_ptr<BaseNode>>&       getChildren();
        std::vector<std::shared_ptr<BaseNode>> const& getChildren() const;
        std::vector<std::shared_ptr<BaseNode>>        getAllChildren();

        void setup();      // Meant for editor and systems
        void init();       // Meant for gameplay
        void uninit();     // Meant for gameplay
        void shutdown();   // Meant for editor and systems
        void preUpdate();  // Called before update
        void update();
        void postUpdate();  // Called right after update

        rlf::Json serialize();
        void      deserialize(rlf::Json const& j);

        void deserializeFromFile(std::string const& filePath);

        std::shared_ptr<BaseNode> clone();

    protected:
        virtual void setActiveImpl(bool const selfActive);
        virtual void setupImpl();
        virtual void initImpl();
        virtual void uninitImpl();
        virtual void shutdownImpl();
        virtual void preUpdateImpl();
        virtual void updateImpl();
        virtual void postUpdateImpl();

    private:
        void markGlobalDirty();
        void clearChildrenMarkedForDestruction();

        std::string mName;

        bool mActive    = true;
        bool mToDestroy = false;
        bool mHasSetup  = false;
        bool mHasInited = false;

        mutable Matrix mLocalTransform  = MatrixIdentity();
        mutable Matrix mGlobalTransform = MatrixIdentity();
        rlf::Vec2f     mPosition        = rlf::Vec2f::Zero();
        rlf::Vec2f     mScale           = rlf::Vec2f::One();
        f32            mRotation        = 0.0f;
        mutable bool   mLocalDirty      = true;
        mutable bool   mGlobalDirty     = true;

        std::weak_ptr<BaseNode>                mRootNode;
        std::weak_ptr<BaseNode>                mParent;
        std::vector<std::shared_ptr<BaseNode>> mChildren;
        std::vector<std::shared_ptr<BaseNode>> mNewChildren;

    protected:
        inline void access(auto& acc)
        {
            RLF_NODE_ACCESS_MEMBER_GET_SET("active", getActiveSelf, setActive);
            RLF_NODE_ACCESS_MEMBER_GET_SET("name", getName, setName);
            RLF_NODE_ACCESS_MEMBER_GET_SET("position", getPosition, setPosition);
            RLF_NODE_ACCESS_MEMBER_GET_SET("scale", getScale, setScale);
            RLF_NODE_ACCESS_MEMBER_GET_SET("rotation", getRotationDeg, setRotationDeg);
        }

        virtual rlf::Json serializeImpl();
        virtual void      deserializeImpl(rlf::Json const& j);
#ifdef RLF_EDITOR
        friend class rlf::System::EditorSystem;
        virtual void imguiAccessImpl();
        bool         mToShiftDown = false;
        bool         mToShiftUp   = false;
#endif
    };
}

#include <Node/BaseNodeImpl.hpp>
