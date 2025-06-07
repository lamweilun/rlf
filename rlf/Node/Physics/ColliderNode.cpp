#include <Node/Physics/ColliderNode.hpp>

#include <System/PhysicsSystem.hpp>

#include <stack>

namespace rlf {
    void ColliderNode::updateImpl() {
        collided      = false;
        auto rootNode = getRootNode();

        std::stack<std::shared_ptr<rlf::BaseNode>> childrenStack;

        for (auto const& child : rootNode->getChildren()) {
            childrenStack.push(child);
        }

        while (!childrenStack.empty()) {
            auto child = childrenStack.top();
            childrenStack.pop();

            for (auto grandChild : child->getChildren()) {
                childrenStack.push(grandChild);
            }

            if (child == shared_from_this()) {
                continue;
            }

            auto colliderNode = std::dynamic_pointer_cast<rlf::ColliderNode>(child);
            if (colliderNode == nullptr) {
                continue;
            }

            auto bb1 = getBoundingBox();
            auto bb2 = colliderNode->getBoundingBox();
            if (CheckCollisionBoxes(bb1, bb2)) {
                collided = true;
            }
        }
    }

    void ColliderNode::renderImpl() {
        BoundingBox bb;
        bb.min = Vector3Zeros - Vector3Ones;
        bb.max = Vector3Zeros + Vector3Ones;
        DrawBoundingBox(bb, collided ? GREEN : RED);
    }

    BoundingBox ColliderNode::getBoundingBox() {
        BoundingBox bb;
        auto        globalTransform = getGlobalTransform();
        auto        globalPos       = getPosition() * globalTransform;

        auto globalX     = Vector3Length(Vector3{globalTransform.m0, globalTransform.m4, globalTransform.m8});
        auto globalY     = Vector3Length(Vector3{globalTransform.m1, globalTransform.m5, globalTransform.m9});
        auto globalZ     = Vector3Length(Vector3{globalTransform.m2, globalTransform.m6, globalTransform.m10});
        auto globalScale = Vector3{globalX, globalY, globalZ};

        bb.min = globalPos - globalScale;
        bb.max = globalPos + globalScale;
        return bb;
    }
}
