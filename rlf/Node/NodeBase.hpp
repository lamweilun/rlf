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

        std::list<Node> children;

        static Node&     getRootNode();
        static NodeBase& getRootNodeBase();

        template <class T>
        T& addChild() {
            T& child = std::get<T>(children.emplace_back(T{}));
            return child;
        }

        Matrix getLocalTransform() const;
        void   update();
        void   render();
    };
}
