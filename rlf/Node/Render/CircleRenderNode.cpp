#include <Node/Render/CircleRenderNode.hpp>

namespace rlf::Node {
    void CircleRenderNode::renderImpl() {
        if (getDrawInWireframe()) {
            DrawCircleLinesV(Vector2Zeros, 1.0f, getTint());
        } else {
            DrawCircleV(Vector2Zeros, 1.0f, getTint());
        }
    }
}
