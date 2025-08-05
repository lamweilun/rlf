#include <Node/Render/CircleRenderNode.hpp>

namespace rlf::Node {
    void CircleRenderNode::renderImpl() {
        DrawCircleLinesV(Vector2Zeros, 1.0f, getTint());
    }
}
