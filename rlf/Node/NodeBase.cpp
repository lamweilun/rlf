#include <Node/NodeBase.hpp>

namespace rlf {

    NodeBase* NodeBase::getRootNode() {
        NodeBase* currNode = this;
        while (currNode->parent) {
            currNode = currNode->parent;
        }
        return currNode;
    }

    Matrix NodeBase::getLocalTransform() const {
        return MatrixScale(scale.x, scale.y, scale.z) * MatrixTranslate(position.x, position.y, position.z);
    }

    void NodeBase::update() {
    }

    void NodeBase::render() {
    }
}
