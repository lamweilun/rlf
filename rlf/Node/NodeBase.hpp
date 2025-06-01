#pragma once

#include <Node/Node.hpp>
#include <list>

namespace rlf {
    class NodeBase {
    public:
        Vector3 position       = Vector3Zeros;
        Vector3 scale          = Vector3Ones;
        bool    active         = true;
        bool    markForDestroy = false;

        NodeBase*       parent = nullptr;
        std::list<Node> children;

        template <class T>
        T& addChild() {
            T& child     = std::get<T>(children.emplace_back(T{}));
            child.parent = this;
            return child;
        }

        NodeBase* getRootNode();
        Matrix    getLocalTransform() const;

        void update();
        void render();
    };
}
