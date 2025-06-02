#pragma once

#include <memory>
#include <vector>

namespace rlf {
    class BaseNode : public std::enable_shared_from_this<BaseNode> {
    public:
        Vector3 position       = Vector3Zeros;
        Vector3 scale          = Vector3Ones;
        bool    active         = true;
        bool    markForDestroy = false;

        std::weak_ptr<BaseNode>                parent;
        std::vector<std::shared_ptr<BaseNode>> children;
        std::vector<std::shared_ptr<BaseNode>> newChildren;

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

        std::shared_ptr<BaseNode> getRootNode();
        Matrix                    getLocalTransform() const;

        void update();
        void render();

        virtual void updateImpl();
        virtual void renderImpl();
    };
}
