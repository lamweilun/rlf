#include <Game/Environment/WallNode.hpp>
#include <Game/Environment/WallRenderNode.hpp>

#include <Node/Physics/LineColliderNode.hpp>

namespace rlf {
    void WallNode::initImpl() {
        addChild<WallRenderNode>();

        auto colliderNode = addChild<rlf::LineColliderNode>();
        colliderNode->addTag("Wall");
        colliderNode->setStartPoint({0.5f, -0.5f, 0.0f});
        colliderNode->setEndPoint({0.5f, 0.5f, 0.0f});
    }
}
