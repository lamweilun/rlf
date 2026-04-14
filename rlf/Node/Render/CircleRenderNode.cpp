#include <Node/Render/CircleRenderNode.hpp>

namespace rlf
{
    void CircleRenderNode::renderImpl()
    {
        DrawCircleV(Vector2Zeros, 1.0f, getTint());
    }
}
