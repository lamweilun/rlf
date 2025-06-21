#include <Node/BaseNode.hpp>

#include <algorithm>

namespace rlf {

    std::shared_ptr<BaseNode> BaseNode::addChild(std::string_view typeName) {
        auto newChild = rlf::TypeSystem::getInstance().createNode(typeName);
        if (!newChild.has_value()) {
            return nullptr;
        }

        newChild.value()->mParent = weak_from_this();
        mNewChildren.push_back(newChild.value());
        return newChild.value();
    }

    std::optional<std::shared_ptr<BaseNode>> BaseNode::getFirstChildOfType(std::string_view typeName) const {
        for (auto const& child : mChildren) {
            if (child->getTypeNameImpl() == typeName) {
                return child;
            }
        }
        for (auto const& child : mNewChildren) {
            if (child->getTypeNameImpl() == typeName) {
                return child;
            }
        }
        return std::nullopt;
    }

    std::shared_ptr<BaseNode> BaseNode::getOrAddFirstChildOfType(std::string_view typeName) {
        auto child = getFirstChildOfType(typeName);
        if (child.has_value()) {
            return child.value();
        }
        child = addChild(typeName);
        return child.value();
    }

    Vector3 const& BaseNode::getPosition() const {
        return mPosition;
    }
    void BaseNode::setPosition(Vector3 const& position) {
        if (Vector3Equals(mPosition, position)) {
            return;
        }
        mPosition   = position;
        mLocalDirty = true;
        markGlobalDirty();
    }

    Vector3 const& BaseNode::getScale() const {
        return mScale;
    }
    void BaseNode::setScale(Vector3 const& scale) {
        if (Vector3Equals(mScale, scale)) {
            return;
        }
        mScale      = scale;
        mLocalDirty = true;
        markGlobalDirty();
    }

    Quaternion const& BaseNode::getRotation() const {
        return mRotation;
    }
    void BaseNode::setRotation(Quaternion const& rotation) {
        if (QuaternionEquals(mRotation, rotation)) {
            return;
        }
        mRotation   = rotation;
        mLocalDirty = true;
        markGlobalDirty();
    }
    void BaseNode::setRotationEulerRad(Vector3 const& eulerDeg) {
        setRotation(QuaternionFromEuler(eulerDeg.x, eulerDeg.y, eulerDeg.z));
    }
    void BaseNode::setRotationEulerDeg(Vector3 const& eulerDeg) {
        setRotationEulerRad(eulerDeg * DEG2RAD);
    }

    bool BaseNode::getActive() const {
        bool active = getActiveSelf();
        if (active) {
            if (auto parent = mParent.lock()) {
                active |= parent->getActive();
            }
        }
        return active;
    }
    bool BaseNode::getActiveSelf() const {
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
        while (auto parentNode = rootNode->mParent.lock()) {
            rootNode = parentNode;
        }
        return rootNode;
    }

    Matrix const& BaseNode::getLocalTransform() const {
        if (mLocalDirty) {
            auto scaleMat     = MatrixScale(mScale.x, mScale.y, mScale.z);
            auto translateMat = MatrixTranslate(mPosition.x, mPosition.y, mPosition.z);
            auto rotMat       = QuaternionToMatrix(mRotation);
            mLocalTransform   = scaleMat * rotMat * translateMat;
            mLocalDirty       = false;
        }
        return mLocalTransform;
    }

    Matrix const& BaseNode::getGlobalTransform() const {
        if (mGlobalDirty) {
            mGlobalTransform = getLocalTransform();
            if (auto parentNode = mParent.lock()) {
                mGlobalTransform = mGlobalTransform * parentNode->getGlobalTransform();
            }
            mGlobalDirty = false;
        }
        return mGlobalTransform;
    }

    Vector3 BaseNode::getGlobalPosition() const {
        auto const& globalMat = getGlobalTransform();
        return Vector3{globalMat.m12, globalMat.m13, globalMat.m14};
    }

    Vector3 BaseNode::getGlobalScale() const {
        auto const& globalMat    = getGlobalTransform();
        auto        globalScaleX = Vector3Length(Vector3{globalMat.m0, globalMat.m1, globalMat.m2});
        auto        globalScaleY = Vector3Length(Vector3{globalMat.m4, globalMat.m5, globalMat.m6});
        auto        globalScaleZ = Vector3Length(Vector3{globalMat.m7, globalMat.m8, globalMat.m9});
        return Vector3{globalScaleX, globalScaleY, globalScaleZ};
    }

    Quaternion BaseNode::getGlobalRotation() const {
        auto globalMat = getGlobalTransform();
        auto invScale  = Vector3Invert(getGlobalScale());
        invScale.x     = std::min(invScale.x, 1.0f);
        invScale.y     = std::min(invScale.y, 1.0f);
        invScale.z     = std::min(invScale.z, 1.0f);

        globalMat.m12 = 0.0f;
        globalMat.m13 = 0.0f;
        globalMat.m14 = 0.0f;

        globalMat.m0 *= invScale.x;
        globalMat.m1 *= invScale.x;
        globalMat.m2 *= invScale.x;

        globalMat.m4 *= invScale.y;
        globalMat.m5 *= invScale.y;
        globalMat.m6 *= invScale.y;

        globalMat.m8 *= invScale.z;
        globalMat.m9 *= invScale.z;
        globalMat.m10 *= invScale.z;

        return QuaternionFromMatrix(globalMat);
    }

    Vector3 BaseNode::getGlobalRotationEulerRad() const {
        return QuaternionToEuler(getGlobalRotation());
    }
    Vector3 BaseNode::getGlobalRotationEulerDeg() const {
        return getGlobalRotationEulerRad() * RAD2DEG;
    }

    std::weak_ptr<BaseNode> BaseNode::getParent() const {
        return mParent;
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

    void BaseNode::shutdown() {
        // Shutdown all children first
        for (auto& child : mChildren) {
            child->shutdown();
        }
        mChildren.clear();

        // Calls shutdown on self
        shutdownImpl();
    }

    void BaseNode::update() {
        // If inactive just return
        if (!mActive) {
            return;
        }

        // Append any newly created nodes
        appendNewChildren();

        // Update self then updateImpl all other mChildren
        updateImpl();
        for (auto& child : mChildren) {
            child->update();
        }

        // For children that are marked for destroy, swap to back, call shutdown, resize to newSize
        size_t newSize = mChildren.size();
        for (size_t i = 0; i < newSize;) {
            if (mChildren[i]->mToDestroy) {
                std::swap(mChildren[i], mChildren[newSize - 1]);
                --newSize;
            } else {
                ++i;
            }
        }
        for (size_t i = newSize; i < mChildren.size(); ++i) {
            mChildren[i]->shutdown();
        }
        mChildren.resize(newSize);
    }

    void BaseNode::render() {
        if (!mActive) {
            return;
        }

        auto matF = MatrixToFloatV(getLocalTransform());
        rlPushMatrix();
        rlMultMatrixf(matF.v);

        renderImpl();
        for (auto& child : mChildren) {
            child->render();
        }

        rlPopMatrix();
    }

    rlf::Json BaseNode::serialize() const {
        rlf::Json j;
        j["type"] = getTypeNameImpl();
        j["data"] = serializeImpl();
        for (auto const& child : mChildren) {
            j["data"]["children"].push_back(child->serialize());
        }
        return j;
    }
    void BaseNode::deserialize(rlf::Json const& j) {
        deserializeImpl(j["data"]);

        std::vector<std::shared_ptr<BaseNode>> newChildren;
        if (j["data"].contains("children")) {
            for (auto const& entry : j["data"]["children"]) {
                auto childNodeOpt = rlf::TypeSystem::getInstance().createNode(entry["type"].get<std::string_view>());
                if (!childNodeOpt.has_value()) {
                    continue;
                }
                std::shared_ptr<BaseNode> childNode = childNodeOpt.value();
                childNode->deserialize(entry);
                childNode->mParent = shared_from_this();
                newChildren.push_back(childNode);
            }
        }

        mChildren.clear();
        mNewChildren = std::move(newChildren);
        mToDestroy   = false;
        mHasInited   = false;
        mLocalDirty  = true;
        mGlobalDirty = true;
    }

    void BaseNode::initImpl() {
    }

    void BaseNode::shutdownImpl() {
    }

    void BaseNode::updateImpl() {
    }

    void BaseNode::renderImpl() {
    }

    rlf::Json BaseNode::serializeImpl() const {
        rlf::Json j;
        j["active"]   = mActive;
        j["position"] = mPosition;
        j["rotation"] = mRotation;
        j["scale"]    = mScale;
        return j;
    }

    void BaseNode::deserializeImpl(rlf::Json const& j) {
        mActive   = j["active"];
        mPosition = j["position"];
        mRotation = j["rotation"];
        mScale    = j["scale"];
    }

    void BaseNode::appendNewChildren() {
        if (mNewChildren.empty()) {
            return;
        }

        // Append newly created children and call init on them
        size_t const oldSize = mChildren.size();
        size_t const newSize = oldSize + mNewChildren.size();
        mChildren.append_range(mNewChildren);
        mNewChildren.clear();
        for (size_t i = oldSize; i < newSize; ++i) {
            mChildren[i]->init();
        }
    }

    void BaseNode::markGlobalDirty() {
        mGlobalDirty = true;
        for (auto& child : mChildren) {
            child->mGlobalDirty = true;
        }
    }
}
