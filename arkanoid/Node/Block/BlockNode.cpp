#include <Node/Block/BlockNode.hpp>

#include <Engine/Engine.hpp>

namespace ark::Node {

    void BlockNode::initImpl() {
        collider = getFirstChildOfType<rlf::Node::BoxColliderNode>().value();
        collider->setCollidedCallback([this](rlf::CollideInfo const& info) {
            if (info.other->hasTag("Ball")) {
                setToDestroy(true);
            }
        });
    }

    void BlockNode::updateImpl() {
        RigidbodyNode::updateImpl();
    }
}
