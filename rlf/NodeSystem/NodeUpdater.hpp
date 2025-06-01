#pragma once

namespace rlf {
    class NodeUpdater {
    public:
        void operator()(auto& node) {
            if (!node.active) {
                return;
            }

            node.update();
            for (auto& child : node.children) {
                child.visit(*this);
            }
        }
    };
}
