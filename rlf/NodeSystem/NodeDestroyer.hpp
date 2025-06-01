#pragma once

#include <Node/NodeInclude.hpp>

#include <variant>

namespace rlf {
    class NodeDestroyer {
    public:
        void operator()(auto& node) {
            // Recursively performs this operation on every child node first
            for (size_t i = 0; i < node.children.size(); ++i) {
                std::visit(*this, node.children[i]);
            }

            // Early return if a node has no children
            if (node.children.empty()) {
                return;
            }

            // Swap to the back for those that are marked for destruction
            size_t newSize = node.children.size();
            for (size_t i = 0; i < newSize;) {
                bool marked = std::visit([](auto& child) { return child.markForDestroy; }, node.children[i]);
                if (marked) {
                    std::swap(node.children[i], node.children[newSize - 1]);
                    --newSize;
                } else {
                    ++i;
                }
            }

            node.children.resize(newSize);
        }
    };
}
