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

    Matrix const& BaseNode::getLocalTransform() {
        if (mDirty) {
            mLocalTransform = MatrixScale(mScale.x, mScale.y, mScale.z) * MatrixTranslate(mPosition.x, mPosition.y, mPosition.z);
        }
        return mLocalTransform;
    }

    Matrix BaseNode::getGlobalTransform() {
        Matrix globalTransform = getLocalTransform();
        if (auto parentNode = parent.lock()) {
            globalTransform = parentNode->getGlobalTransform() * globalTransform;
        }
        return globalTransform;
    }

    std::vector<std::shared_ptr<BaseNode>> const& BaseNode::getChildren() const {
        return mChildren;
    }

    void BaseNode::init() {
        if (!mHasInited) {
            initImpl();
            mHasInited = true;
        }

        for (auto& child : mChildren) {
            child->init();
        }
    }

    void BaseNode::update() {
        appendNewChildren();

        // Update self then updateImpl all other mChildren
        updateImpl();
        for (auto& child : mChildren) {
            child->update();
        }

        // Clears those child that are marked for destroy
        size_t newSize = mChildren.size();
        for (size_t i = 0; i < newSize;) {
            if (mChildren[i]->mToDestroy) {
                std::swap(mChildren[i], mChildren[newSize - 1]);
                --newSize;
            } else {
                ++i;
            }
        }
        // Nodes that are marked for destroy will call shutdown
        for (size_t i = newSize; i < mChildren.size(); ++i) {
            mChildren[i]->shutdown();
        }
        mChildren.resize(newSize);
    }

    void BaseNode::render() {
        auto localTransform = getLocalTransform();
        auto matF           = MatrixToFloatV(localTransform);

        rlPushMatrix();
        rlMultMatrixf(matF.v);
        renderImpl();

        for (auto& child : mChildren) {
            child->render();
        }

        rlPopMatrix();
    }

    void BaseNode::shutdown() {
        appendNewChildren();

        for (auto& child : mChildren) {
            child->shutdown();
        }
        mChildren.clear();

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
        // Append newly created mChildren after calling init on them
        for (auto& newChild : newChildren) {
            newChild->init();
        }
        mChildren.append_range(newChildren);
        newChildren.clear();
    }
}
