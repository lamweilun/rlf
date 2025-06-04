#include <Node/BaseNode.hpp>

namespace rlf {

    std::shared_ptr<BaseNode> BaseNode::getRootNode() {
        std::shared_ptr<BaseNode> rootNode = shared_from_this();
        while (auto parentNode = rootNode->parent.lock()) {
            rootNode = parentNode;
        }
        return rootNode;
    }

    Matrix BaseNode::getLocalTransform() const {
        return MatrixScale(scale.x, scale.y, scale.z) * MatrixTranslate(position.x, position.y, position.z);
    }

    void BaseNode::init() {
        if (!hasInited) {
            initImpl();
            hasInited = true;
        }

        for (auto& child : children) {
            child->init();
        }
    }

    void BaseNode::update() {
        // Append newly created children
        children.append_range(newChildren);
        newChildren.clear();

        init();

        // Update self then updateImpl all other children
        updateImpl();
        for (auto& child : children) {
            child->update();
        }

        // Clears those child that are marked for destroy
        size_t newSize = children.size();
        for (size_t i = 0; i < newSize;) {
            if (children[i]->markForDestroy) {
                std::swap(children[i], children[newSize - 1]);
                --newSize;
            } else {
                ++i;
            }
        }
        for (size_t i = newSize; i < children.size(); ++i) {
            children[i]->shutdown();
        }
        children.resize(newSize);
    }

    void BaseNode::render() {
        auto localTransform = getLocalTransform();
        auto matF           = MatrixToFloatV(localTransform);

        rlPushMatrix();
        rlMultMatrixf(matF.v);
        renderImpl();

        for (auto& child : children) {
            child->render();
        }

        rlPopMatrix();
    }

    void BaseNode::shutdown() {
        // Append newly created children
        children.append_range(newChildren);
        newChildren.clear();

        init();

        for (auto& child : children) {
            child->shutdown();
        }

        shutdownImpl();
    }

    void BaseNode::initImpl() {
    }

    void BaseNode::updateImpl() {
    }

    void BaseNode::renderImpl() {
    }

    void BaseNode::shutdownImpl() {
    }
}
