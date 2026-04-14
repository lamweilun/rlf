#include <Node/BaseNode.hpp>

#include <Engine/Engine.hpp>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <queue>

namespace rlf
{
    std::shared_ptr<BaseNode> BaseNode::addChild(std::string_view typeName)
    {
        auto newChild = rlf::Engine::getInstance().getNodeManager().create(typeName);
        if (!newChild.has_value())
        {
            return nullptr;
        }

        newChild.value()->mParent = weak_from_this();
        mNewChildren.push_back(newChild.value());
        return newChild.value();
    }

    std::optional<std::shared_ptr<BaseNode>> BaseNode::getFirstChildOfType(std::string_view typeName) const
    {
        for (auto const& child : getChildren())
        {
            if (child->getTypeNameImpl() == typeName)
            {
                return child;
            }
        }
        return std::nullopt;
    }

    std::shared_ptr<BaseNode> BaseNode::addOrGetFirstChildOfType(std::string_view typeName)
    {
        auto child = getFirstChildOfType(typeName);
        if (child.has_value())
        {
            return child.value();
        }
        child = addChild(typeName);
        return child.value();
    }

    rlf::Vec2f const& BaseNode::getPosition() const
    {
        return mPosition;
    }
    void BaseNode::setPosition(rlf::Vec2f const& position)
    {
        if (mPosition == position)
        {
            return;
        }
        mPosition   = position;
        mLocalDirty = true;
        markGlobalDirty();
    }

    rlf::Vec2f const& BaseNode::getScale() const
    {
        return mScale;
    }
    void BaseNode::setScale(rlf::Vec2f const& scale)
    {
        if (mScale == scale)
        {
            return;
        }
        mScale      = scale;
        mLocalDirty = true;
        markGlobalDirty();
    }

    f32 const& BaseNode::getRotation() const
    {
        return mRotation;
    }
    void BaseNode::setRotation(f32 const rotation)
    {
        if (FloatEquals(mRotation, rotation))
        {
            return;
        }
        mRotation   = rotation;
        mLocalDirty = true;
        markGlobalDirty();
    }
    f32 BaseNode::getRotationDeg() const
    {
        return getRotation() * RAD2DEG;
    }
    void BaseNode::setRotationDeg(f32 const rotationDeg)
    {
        setRotation(rotationDeg * DEG2RAD);
    }

    rlf::UUID const& BaseNode::getID() const
    {
        return mID;
    }

    std::string const& BaseNode::getName() const
    {
        return mName;
    }
    void BaseNode::setName(std::string const& name)
    {
        mName = name;
    }

    bool BaseNode::getActive() const
    {
        bool active = getActiveSelf();
        if (active)
        {
            if (auto parent = mParent.lock())
            {
                active = active && parent->getActive();
            }
        }
        return active;
    }
    bool BaseNode::getActiveSelf() const
    {
        return mActive;
    }
    void BaseNode::setActive(bool const active)
    {
        if (mActive != active)
        {
            mActive = active;
            setActiveImpl(active);
        }

        // Call it for all children as well
        for (auto& child : getAllChildren())
        {
            child->setActiveImpl(child->getActiveSelf());
        }
    }

    void BaseNode::setToDestroy(bool const toDestroy)
    {
        mToDestroy = toDestroy;
    }

    bool BaseNode::isRootNode() const
    {
        return !hasParent();
    }

    std::shared_ptr<BaseNode> BaseNode::getRootNode()
    {
        return rlf::Engine::getInstance().getRootNode();
    }

    Matrix const& BaseNode::getLocalTransform() const
    {
        if (mLocalDirty)
        {
            auto scaleMat     = MatrixScale(mScale.x, mScale.y, 1.0f);
            auto translateMat = MatrixTranslate(mPosition.x, mPosition.y, 0.0f);
            auto rotMat       = MatrixRotateZ(mRotation);
            mLocalTransform   = scaleMat * rotMat * translateMat;
            mLocalDirty       = false;
        }
        return mLocalTransform;
    }

    Matrix const& BaseNode::getGlobalTransform() const
    {
        if (mGlobalDirty)
        {
            mGlobalTransform = getLocalTransform();
            if (auto parentNode = mParent.lock())
            {
                mGlobalTransform = mGlobalTransform * parentNode->getGlobalTransform();
            }
            mGlobalDirty = false;
        }
        return mGlobalTransform;
    }

    rlf::Vec2f BaseNode::getGlobalRight() const
    {
        Matrix const& globalMat = getGlobalTransform();
        return rlf::Vec2f{globalMat.m0, globalMat.m4};
    }

    rlf::Vec2f BaseNode::getGlobalPosition() const
    {
        auto const& globalMat = getGlobalTransform();
        return rlf::Vec2f{globalMat.m12, globalMat.m13};
    }

    rlf::Vec2f BaseNode::getGlobalScale() const
    {
        auto const& globalMat    = getGlobalTransform();
        auto        globalScaleX = rlf::Vec3f{globalMat.m0, globalMat.m1, globalMat.m2}.Length();
        auto        globalScaleY = rlf::Vec3f{globalMat.m4, globalMat.m5, globalMat.m6}.Length();
        return rlf::Vec2f{globalScaleX, globalScaleY};
    }

    Quaternion BaseNode::getGlobalRotation() const
    {
        auto globalMat = getGlobalTransform();

        auto globalScaleX = rlf::Vec3f{globalMat.m0, globalMat.m1, globalMat.m2}.Length();
        auto globalScaleY = rlf::Vec3f{globalMat.m4, globalMat.m5, globalMat.m6}.Length();
        auto globalScaleZ = rlf::Vec3f{globalMat.m8, globalMat.m9, globalMat.m10}.Length();

        auto invScale = 1.0f / rlf::Vec3f{globalScaleX, globalScaleY, globalScaleZ};
        invScale.x    = std::min(invScale.x, 1.0f);
        invScale.y    = std::min(invScale.y, 1.0f);
        invScale.z    = std::min(invScale.z, 1.0f);

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

    f32 BaseNode::getGlobalRotationRad() const
    {
        auto const& globalRot = getGlobalRotation();
        return QuaternionToEuler(globalRot).z;
    }
    f32 BaseNode::getGlobalRotationDeg() const
    {
        return getGlobalRotationRad() * RAD2DEG;
    }

    bool BaseNode::hasParent() const
    {
        return !mParent.expired();
    }

    std::weak_ptr<BaseNode> BaseNode::getParent() const
    {
        return mParent;
    }

    void BaseNode::setParent(std::shared_ptr<BaseNode> newParent)
    {
        // Return if im the root node
        if (isRootNode())
        {
            return;
        }
        // Return if the new parent is myself
        if (newParent == shared_from_this())
        {
            return;
        }

        // Return if the new parent is the same as the current parent
        {
            auto currParent = mParent.lock();
            if (currParent == newParent)
            {
                return;
            }
        }

        // Add this node to the new parent
        newParent->mNewChildren.push_back(shared_from_this());
        // Remove this node from the old parent
        {
            if (auto currParent = mParent.lock())
            {
                auto& currParentChildren = currParent->getChildren();
                for (size_t i = 0; i < currParentChildren.size(); ++i)
                {
                    if (currParentChildren[i] == shared_from_this())
                    {
                        currParentChildren.erase(std::begin(currParentChildren) + static_cast<i32>(i));
                        break;
                    }
                }
            }
        }

        // Set new parent
        mParent = newParent;

        markGlobalDirty();
    }

    std::vector<std::shared_ptr<BaseNode>>& BaseNode::getChildren()
    {
        // Append newly created children and call init on them
        if (!mNewChildren.empty())
        {
            size_t const oldSize = mChildren.size();
            size_t const newSize = oldSize + mNewChildren.size();
            mChildren.append_range(mNewChildren);
            mNewChildren.clear();
            for (size_t i = oldSize; i < newSize; ++i)
            {
                mChildren[i]->setup();
                mChildren[i]->init();
                mChildren[i]->setActiveImpl(mChildren[i]->getActiveSelf());
            }
        }

#ifdef RLF_EDITOR
        // Check if any children needs to be shifted
        {
            for (size_t i = 0; i < mChildren.size(); ++i)
            {
                if (mChildren[i]->mToShiftDown && i < mChildren.size() - 1)
                {
                    mChildren[i]->mToShiftDown = false;
                    std::swap(mChildren[i], mChildren[i + 1]);
                }
                else if (mChildren[i]->mToShiftUp && i > 0)
                {
                    mChildren[i]->mToShiftUp = false;
                    std::swap(mChildren[i], mChildren[i - 1]);
                }
            }
        }
#endif

        return mChildren;
    }

    std::vector<std::shared_ptr<BaseNode>> const& BaseNode::getChildren() const
    {
        return const_cast<BaseNode&>(*this).getChildren();
    }

    std::vector<std::shared_ptr<BaseNode>> BaseNode::getAllChildren()
    {
        std::vector<std::shared_ptr<BaseNode>> allChildren;
        std::queue<std::shared_ptr<BaseNode>>  childQueue;
        for (auto const& child : getChildren())
        {
            childQueue.push(child);
        }
        while (!childQueue.empty())
        {
            auto child = childQueue.front();
            allChildren.push_back(child);
            childQueue.pop();
            for (auto const& grandChild : child->getChildren())
            {
                childQueue.push(grandChild);
            }
        }
        return allChildren;
    }

    void BaseNode::setActiveImpl([[maybe_unused]] bool const active)
    {
    }

    void BaseNode::setup()
    {
        if (!mHasSetup)
        {
            setupImpl();
            mHasSetup = true;
        }

        for (auto& child : getChildren())
        {
            child->setup();
        }
    }

    void BaseNode::init()
    {
        if (!mHasInited)
        {
#ifndef RLF_EDITOR
            initImpl();
#endif
            mHasInited = true;
        }

        for (auto& child : getChildren())
        {
            child->init();
        }
    }

    void BaseNode::uninit()
    {
#ifndef RLF_EDITOR
        // Shutdown all children first
        for (auto& child : getChildren())
        {
            child->uninit();
        }
#endif

        // Calls uninit on self
        if (!mHasInited)
        {
            return;
        }
        uninitImpl();
        mHasInited = false;
    }

    void BaseNode::shutdown()
    {
        // Do NOT call clearChildrenMarkedForDestruction() here - it will call shutdown() again recursively
        // Mark all children for destruction only - actual clearing/destruction happens in clearChildrenMarkedForDestruction()
        auto allChildren = getAllChildren();
        for (auto& child : allChildren)
        {
            child->setToDestroy(true);
        }

        // Calls shutdown on self
        if (!mHasSetup)
        {
            return;
        }
        shutdownImpl();
        mHasSetup = false;
    }

    void BaseNode::preUpdate()
    {
        clearChildrenMarkedForDestruction();

        // If inactive just return
        if (!mActive)
        {
            return;
        }

#ifndef RLF_EDITOR
        preUpdateImpl();
#endif

        for (auto& child : getChildren())
        {
            child->preUpdate();
        }
    }

    void BaseNode::update()
    {
        // If inactive just return
        if (!mActive)
        {
            return;
        }

#ifndef RLF_EDITOR
        updateImpl();
#endif

        for (auto& child : getChildren())
        {
            child->update();
        }
    }

    void BaseNode::postUpdate()
    {
        // If inactive just return
        if (!mActive)
        {
            return;
        }

#ifndef RLF_EDITOR
        postUpdateImpl();
#endif

        for (auto& child : getChildren())
        {
            child->postUpdate();
        }
    }

    rlf::Json BaseNode::serialize()
    {
        rlf::Json j;
        j["type"] = getTypeNameImpl();
        j["data"] = serializeImpl();
        for (auto const& child : getChildren())
        {
            j["data"]["children"].push_back(child->serialize());
        }
        return j;
    }
    void BaseNode::deserialize(rlf::Json const& j)
    {
        deserializeImpl(j["data"]);

        std::vector<std::shared_ptr<BaseNode>> newChildren;
        if (j["data"].contains("children"))
        {
            for (auto const& entry : j["data"]["children"])
            {
                // Try to create a node of type
                auto childNodeOpt = rlf::Engine::getInstance().getNodeManager().create(entry["type"].get<std::string_view>());
                if (!childNodeOpt.has_value())
                {
                    // If for whatever reason the node type is not registered, replace it with a base node
                    childNodeOpt = rlf::Engine::getInstance().getNodeManager().create(rlf::BaseNode::getTypeName());
                }
                std::shared_ptr<BaseNode> childNode = childNodeOpt.value();
                childNode->deserialize(entry);
                childNode->mParent = weak_from_this();
                newChildren.push_back(childNode);
            }
        }

        for (auto& child : getChildren())
        {
            child->setToDestroy(true);
        }
        mNewChildren = std::move(newChildren);
        mToDestroy   = false;
        mHasSetup    = false;
        mHasInited   = false;
        mLocalDirty  = true;
        mGlobalDirty = true;
    }

    void BaseNode::deserializeFromFile(std::string const& filePath)
    {
        std::ifstream ifs(filePath);
        if (!ifs.is_open())
        {
            return;
        }
        std::stringstream ss;
        ss << ifs.rdbuf();
        rlf::Json j = rlf::Json::parse(ss.str());
        deserialize(j);
    }

    std::shared_ptr<BaseNode> BaseNode::clone()
    {
        // Should not be able to clone the root node, only its contents
        if (isRootNode())
        {
            return nullptr;
        }

        auto const nodeJson = serialize();
        auto const nodeType = getTypeNameImpl();
        auto       newChild = getParent().lock()->addChild(nodeType);
        newChild->deserialize(nodeJson);
        return newChild;
    }

    void BaseNode::setupImpl()
    {
    }

    void BaseNode::initImpl()
    {
    }

    void BaseNode::uninitImpl()
    {
    }

    void BaseNode::shutdownImpl()
    {
    }

    void BaseNode::preUpdateImpl()
    {
    }

    void BaseNode::updateImpl()
    {
    }

    void BaseNode::postUpdateImpl()
    {
    }

    rlf::Json BaseNode::serializeImpl()
    {
        rlf::acc::JsonSerializer js;
        access(js);
        return js.getJson();
    }

    void BaseNode::deserializeImpl(rlf::Json const& j)
    {
        rlf::acc::JsonDeserializer jd;
        jd.setJson(j);
        access(jd);
    }

#ifdef RLF_EDITOR
    void BaseNode::imguiAccessImpl()
    {
        rlf::acc::ImGuiAccessor imguiAcc;
        access(imguiAcc);
    }
#endif

    void BaseNode::markGlobalDirty()
    {
        mGlobalDirty = true;
        for (auto& child : getChildren())
        {
            child->markGlobalDirty();
        }
    }

    void BaseNode::clearChildrenMarkedForDestruction()
    {
        // For children that are marked for destroy, swap to back, call shutdown, resize to newSize
        size_t newSize = getChildren().size();
        for (size_t i = 0; i < newSize;)
        {
            if (mChildren[i]->mToDestroy)
            {
                std::swap(mChildren[i], mChildren[newSize - 1]);
                --newSize;
            }
            else
            {
                ++i;
            }
        }
        for (size_t i = newSize; i < mChildren.size(); ++i)
        {
            for (auto& child : mChildren[i]->getChildren())
            {
                child->setToDestroy(true);
            }
            mChildren[i]->clearChildrenMarkedForDestruction();
            mChildren[i]->uninit();
            mChildren[i]->shutdown();
        }
        mChildren.resize(newSize);
    }
}
