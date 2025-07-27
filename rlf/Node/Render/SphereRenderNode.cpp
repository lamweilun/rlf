#include <Node/Render/SphereRenderNode.hpp>

namespace rlf {
    void SphereRenderNode::renderImpl() {
        DrawCircle3D(Vector3Zeros, 1.0f, Vector3Ones, 0.0f, getTint());
    }
}
