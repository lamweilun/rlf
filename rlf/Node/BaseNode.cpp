#include <Node/BaseNode.hpp>

namespace rlf {

    Vector3 const& BaseNode::getPosition() const {
        return mPosition;
    }
    void BaseNode::setPosition(Vector3 const& position) {
        mPosition = position;
        mDirty    = true;
    }

    Vector3 const& BaseNode::getScale() const {
        return mScale;
    }
    void BaseNode::setScale(Vector3 const& scale) {
        mScale = scale;
        mDirty = true;
    }

    bool BaseNode::getActive() const {
        return mActive;
    }
    void BaseNode::setActive(bool const active) {
        mActive = active;
    }

    void BaseNode::setToDestroy(bool const toDestroy) {
        mToDestroy = toDestroy;
    }

    std::shared_ptr<BaseNode> BaseNode::getRootNode() {
        std::shared_ptr<BaseNode> rootNode = shared_from_this();
        while (auto parentNode = rootNode->parent.lock()) {
            rootNode = parentNode;
        }
        return rootNode;
    }

    Matrix BaseNode::getLocalTransform() {
        if (mDirty) {
            mLocalTransform = MatrixScale(mScale.x, mScale.y, mScale.z) * MatrixTranslate(mPosition.x, mPosition.y, mPosition.z);
        }
        return mLocalTransform;
    }

    void BaseNode::init() {
        if (!mHasInited) {
            initImpl();
            mHasInited = true;
        }

        for (auto& child : children) {
            child->init();
        }
    }

    void BaseNode::update() {
        appendNewChildren();

        // Update self then updateImpl all other children
        updateImpl();
        for (auto& child : children) {
            child->update();
        }

        // Clears those child that are marked for destroy
        size_t newSize = children.size();
        for (size_t i = 0; i < newSize;) {
            if (children[i]->mToDestroy) {
                std::swap(children[i], children[newSize - 1]);
                --newSize;
            } else {
                ++i;
            }
        }
        // Nodes that are marked for destroy will call shutdown
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
        appendNewChildren();

        for (auto& child : children) {
            child->shutdown();
        }
        children.clear();

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

    void BaseNode::appendNewChildren() {
        // Append newly created children after calling init on them
        for (auto& newChild : newChildren) {
            newChild->init();
        }
        children.append_range(newChildren);
        newChildren.clear();
    }
}
