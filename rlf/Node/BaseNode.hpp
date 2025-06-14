#pragma once

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

        template <class T>
        std::shared_ptr<T> addChild() {
            std::shared_ptr<T> newChild = std::make_shared<T>();
            newChild->mParent           = weak_from_this();
            newChildren.push_back(newChild);
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

        void init();
        void update();
        void shutdown();

        virtual void initImpl();
        virtual void updateImpl();
        virtual void shutdownImpl();

    private:
        void appendNewChildren();
        void markGlobalDirty();
        void markChildrenActiveInHierarchy(bool activeInHierarchy);

        mutable Matrix mLocalTransform  = MatrixIdentity();
        mutable Matrix mGlobalTransform = MatrixIdentity();
        Vector3        mPosition        = Vector3Zeros;
        Quaternion     mRotation        = QuaternionUnitX;
        Vector3        mScale           = Vector3Ones;
        mutable bool   mLocalDirty      = true;
        mutable bool   mGlobalDirty     = true;

        bool mActive    = true;
        bool mToDestroy = false;
        bool mHasInited = false;

        std::weak_ptr<BaseNode>                mParent;
        std::vector<std::shared_ptr<BaseNode>> mChildren;
        std::vector<std::shared_ptr<BaseNode>> newChildren;
    };
}
