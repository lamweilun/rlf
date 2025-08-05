#include <Ball/BallRenderNode.hpp>

namespace rlf::Node {
    void BallRenderNode::renderImpl() {
        DrawSphere({}, 1.0f, getTint());
    }
}
