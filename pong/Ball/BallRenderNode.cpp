#include <Ball/BallRenderNode.hpp>

namespace rlf {
    void BallRenderNode::renderImpl() {
        DrawSphere({}, 1.0f, getTint());
    }
}
