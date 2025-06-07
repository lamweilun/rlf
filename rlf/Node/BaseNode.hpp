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
            newChild->parent            = weak_from_this();
            newChildren.push_back(newChild);
            return newChild;
        }

        Vector3 const& getPosition() const;
        void           setPosition(Vector3 const& position);

        Vector3 const& getScale() const;
        void           setScale(Vector3 const& scale);

        bool getActive() const;
        void setActive(bool const active);

        void setToDestroy(bool const toDestroy);

        std::shared_ptr<BaseNode> getRootNode();
        Matrix const&             getLocalTransform();
        Matrix                    getGlobalTransform();

        std::vector<std::shared_ptr<BaseNode>> const&
        getChildren() const;

        void init();
        void update();
        void render();
        void shutdown();

        virtual void initImpl();
        virtual void updateImpl();
        virtual void renderImpl();
        virtual void shutdownImpl();

    private:
        void appendNewChildren();

        Matrix  mLocalTransform = MatrixIdentity();
        Vector3 mPosition       = Vector3Zeros;
        Vector3 mScale          = Vector3Ones;
        bool    mDirty          = true;

        bool mActive    = true;
        bool mToDestroy = false;
        bool mHasInited = false;

        std::weak_ptr<BaseNode>                parent;
        std::vector<std::shared_ptr<BaseNode>> mChildren;
        std::vector<std::shared_ptr<BaseNode>> newChildren;
    };
}
