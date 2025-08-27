#include <Node/Render/CircleRenderNode.hpp>

namespace rlf::Node {
    void CircleRenderNode::renderImpl() {
        DrawCircleV(Vector2Zeros, 1.0f, getTint());
    }
}
