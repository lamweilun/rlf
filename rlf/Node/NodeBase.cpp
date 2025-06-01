#include <Node/NodeBase.hpp>
#include <Node/NodeInclude.hpp>

namespace rlf {

    Node& NodeBase::getRootNode() {
        static Node rootNode = rlf::NodeBase();
        return rootNode;
    }
    NodeBase& NodeBase::getRootNodeBase() {
        return std::get<NodeBase>(getRootNode());
    }

    NodeBase::NodeBase() {
        children.reserve(128);
    }

    Matrix NodeBase::getLocalTransform() const {
        return MatrixScale(scale.x, scale.y, scale.z) * MatrixTranslate(position.x, position.y, position.z);
    }

    void NodeBase::update() {
    }

    void NodeBase::render() {
    }
}
