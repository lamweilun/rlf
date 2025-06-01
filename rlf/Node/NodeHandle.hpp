#pragma once

#include <Node/Node.hpp>

#include <list>

namespace rlf {
    class NodeHandle {
    public:
        Node                  nodeData;
        std::list<NodeHandle> children;

        NodeHandle(auto const& t)
            : nodeData{t} {
        }

        template <class T>
        NodeHandle& addChild() {
            return children.emplace_back(NodeHandle(T{}));
        }

        template <class T>
        T& get() {
            return std::get<T>(nodeData);
        }

        void update(auto& updater) {
            nodeData.visit(updater);
            for (auto& childHandle : children) {
                childHandle.update(updater);
            }
        }

        void render(auto& renderer) {
        }
    };
}
