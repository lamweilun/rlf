#pragma once

namespace rlf {
    class NodeRenderer {
    public:
        void operator()(auto& node) {
            if (!node.active) {
                return;
            }

            auto matF = MatrixToFloatV(node.getLocalTransform());

            rlPushMatrix();
            rlMultMatrixf(matF.v);

            node.render();
            for (auto& child : node.children) {
                child.visit(*this);
            }

            rlPopMatrix();
        }
    };
}
