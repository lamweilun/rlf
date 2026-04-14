#include <Node/Render/QuadRenderNode.hpp>

namespace rlf
{
    void QuadRenderNode::renderImpl()
    {
        // Can't draw wireframe for now
        // if (getDrawInWireframe()) {
        // } else {
        //     rawRectangleV({-0.5f, -0.5f}, Vector2Ones, getTint());
        // }

        DrawRectangleV({-0.5f, -0.5f}, Vector2Ones, getTint());
    }
}
