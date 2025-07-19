#include <Node/Player/PlayerBulletRenderNode.hpp>

namespace rlf {
    void PlayerBulletRenderNode::initImpl() {
        RenderNode::initImpl();
        setTint(BLUE);
    }
}
