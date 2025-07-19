#include <Node/Enemy/EnemyRenderNode.hpp>

namespace rlf {
    void EnemyRenderNode::initImpl() {
        RenderNode::initImpl();
        setTint(RED);
    }
}
