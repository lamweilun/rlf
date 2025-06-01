#pragma once

#include <Node/Node.hpp>
#include <vector>

namespace rlf {
    class NodeBase {
    public:
        Vector3 position       = Vector3Zeros;
        Vector3 scale          = Vector3Ones;
        bool    active         = true;
        bool    markForDestroy = false;

        std::vector<Node> children;

        NodeBase();
        ~NodeBase()                          = default;
        NodeBase(NodeBase const&)            = default;
        NodeBase(NodeBase&&)                 = default;
        NodeBase& operator=(NodeBase const&) = default;
        NodeBase& operator=(NodeBase&&)      = default;

        static Node&     getRootNode();
        static NodeBase& getRootNodeBase();

        template <class T>
        T& addChild() {
            return std::get<T>(children.emplace_back(T{}));
        }

        Matrix getLocalTransform() const;
        void   update();
        void   render();
    };
}
