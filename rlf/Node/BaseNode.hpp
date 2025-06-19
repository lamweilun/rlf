#pragma once

#include <System/TypeSystem.hpp>

#include <memory>
#include <vector>

namespace rlf {
    class BaseNode : public std::enable_shared_from_this<BaseNode> {
    public:
        BaseNode()                           = default;
        virtual ~BaseNode()                  = default;
        BaseNode(BaseNode const&)            = default;
        BaseNode(BaseNode&&)                 = default;
        BaseNode& operator=(BaseNode const&) = default;
        BaseNode& operator=(BaseNode&&)      = default;

        static inline constexpr std::string_view getTypeName() { return "BaseNode"; }
        inline virtual std::string_view          getTypeNameImpl() const { return getTypeName(); }
        static inline bool                       typeRegistered = rlf::TypeSystem::getInstance().registerType<BaseNode>();

        template <class T>
        std::shared_ptr<T> addChild() {
            std::shared_ptr<T> newChild = std::make_shared<T>();
            newChild->mParent           = weak_from_this();
            mNewChildren.push_back(newChild);
            return newChild;
        }

        Vector3 const&    getPosition() const;
        void              setPosition(Vector3 const& position);
        Vector3 const&    getScale() const;
        void              setScale(Vector3 const& scale);
        Quaternion const& getRotation() const;
        void              setRotation(Quaternion const& rotation);
        void              setRotationEulerRad(Vector3 const& angleRad);
        void              setRotationEulerDeg(Vector3 const& angleDeg);

        bool getActive() const;
        bool getActiveSelf() const;
        void setActive(bool const active);

        void setToDestroy(bool const toDestroy);

        std::shared_ptr<BaseNode> getRootNode();
        Matrix const&             getLocalTransform() const;
        Matrix const&             getGlobalTransform() const;
        Vector3                   getGlobalPosition() const;
        Vector3                   getGlobalScale() const;
        Quaternion                getGlobalRotation() const;
        Vector3                   getGlobalRotationEulerRad() const;
        Vector3                   getGlobalRotationEulerDeg() const;

        std::weak_ptr<BaseNode>                       getParent() const;
        std::vector<std::shared_ptr<BaseNode>> const& getChildren() const;

        void      init();
        void      shutdown();
        void      update();
        void      render();
        rlf::Json serialize() const;
        void      deserialize(rlf::Json const& j);

        virtual void      initImpl();
        virtual void      shutdownImpl();
        virtual void      updateImpl();
        virtual void      renderImpl();
        virtual rlf::Json serializeImpl() const;
        virtual void      deserializeImpl(rlf::Json const& j);

    private:
        void appendNewChildren();
        void markGlobalDirty();

        bool mActive    = true;
        bool mToDestroy = false;
        bool mHasInited = false;

        mutable Matrix mLocalTransform  = MatrixIdentity();
        mutable Matrix mGlobalTransform = MatrixIdentity();
        Vector3        mPosition        = Vector3Zeros;
        Quaternion     mRotation        = QuaternionUnitX;
        Vector3        mScale           = Vector3Ones;
        mutable bool   mLocalDirty      = true;
        mutable bool   mGlobalDirty     = true;

        std::weak_ptr<BaseNode>                mParent;
        std::vector<std::shared_ptr<BaseNode>> mChildren;
        std::vector<std::shared_ptr<BaseNode>> mNewChildren;
    };
}
