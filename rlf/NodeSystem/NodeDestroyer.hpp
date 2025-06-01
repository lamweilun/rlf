#pragma once

namespace rlf {
    class NodeDestroyer {
    public:
        void operator()(auto& node) {
            if (!node.markForDestroy) {
                return;
            }

            for (auto& child : node.children) {
                child.visit(*this);
            }

            node.children.clear();
        }
    };
}
