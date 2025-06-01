#include <Node/NodeBase.hpp>

#include <Node/NodeBase.hpp>
#include <Node/Physics/RigidbodyNode.hpp>
#include <Node/Player/PlayerNode.hpp>
#include <Node/Player/PlayerBulletNode.hpp>

namespace rlf {

    Node& NodeBase::getRootNode() {
        static Node rootNode = rlf::NodeBase();
        return rootNode;
    }
    NodeBase& NodeBase::getRootNodeBase() {
        return std::get<NodeBase>(getRootNode());
    }

    Matrix NodeBase::getLocalTransform() const {
        return MatrixScale(scale.x, scale.y, scale.z) * MatrixTranslate(position.x, position.y, position.z);
    }

    void NodeBase::update() {
    }

    void NodeBase::render() {
    }
}
