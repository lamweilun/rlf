#pragma once

#include <variant>

namespace rlf {
    class NodeDestroyer {
    public:
        void operator()(auto& node) {
            if (!node.markForDestroy) {
                return;
            }

            for (auto& child : node.children) {
                std::visit(*this, child);
            }

            node.children.clear();
        }
    };
}
