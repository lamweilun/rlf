#include <Node/Render/CircleRenderNode.hpp>

namespace rlf::Node {
    void CircleRenderNode::renderImpl() {
        DrawCircleV(Vector2Zeros, 0.5f, getTint());
    }
}
