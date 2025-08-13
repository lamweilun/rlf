#include <Environment/WallNode.hpp>
#include <Environment/WallRenderNode.hpp>

#include <Node/Physics/LineColliderNode.hpp>

namespace rlf::Node {
    void WallNode::initImpl() {
        addOrGetFirstChildOfType<WallRenderNode>();

        auto colliderNode = addOrGetFirstChildOfType<rlf::Node::LineColliderNode>();
        colliderNode->addTag("Wall");
        colliderNode->setStartPoint({0.5f, -0.5f});
        colliderNode->setEndPoint({0.5f, 0.5f});
    }
}
