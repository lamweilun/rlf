#include <System/Physics/PhysicsSystem.hpp>

#include <Util/Physics/CollisionDetection.hpp>

namespace rlf::System {
    void PhysicsSystem::addColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode) {
        mLineColliderNodes.insert(lineColliderNode);
    }

    void PhysicsSystem::addColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode) {
        mSphereColliderNodes.insert(sphereColliderNode);
    }

    void PhysicsSystem::removeColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode) {
        mLineColliderNodes.erase(lineColliderNode);
    }

    void PhysicsSystem::removeColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode) {
        mSphereColliderNodes.erase(sphereColliderNode);
    }

    std::vector<std::shared_ptr<rlf::Node::ColliderNode>> PhysicsSystem::checkCollision(std::shared_ptr<rlf::Node::LineColliderNode> colliderNode) {
        // Initialize data
        std::vector<std::shared_ptr<rlf::Node::ColliderNode>> collided;

        auto const& globalTransform1 = colliderNode->getGlobalTransform();
        auto const  startPt1         = colliderNode->getStartPoint() * globalTransform1;
        auto const  endPt1           = colliderNode->getEndPoint() * globalTransform1;

        // Check against other line colliders
        for (auto const& cn : mLineColliderNodes) {
            if (cn->hasAnyOfTags(colliderNode->getTags())) {
                continue;
            }

            if (!cn->getActive()) {
                continue;
            }

            if (cn == colliderNode) {
                continue;
            }

            auto const& globalTransform2 = cn->getGlobalTransform();
            auto const  startPt2         = cn->getStartPoint() * globalTransform2;
            auto const  endPt2           = cn->getEndPoint() * globalTransform2;

            // Perform line to line collision here
            Vector2 collisionPt = Vector2Zeros;
            if (CheckCollisionLines(startPt1, endPt1, startPt2, endPt2, &collisionPt)) {
                collided.push_back(cn);
            }
        }

        // Check against sphere colliders
        for (auto const& cn : mSphereColliderNodes) {
            if (cn->hasAnyOfTags(colliderNode->getTags())) {
                continue;
            }

            if (!cn->getActive()) {
                continue;
            }

            Vector2 const cnGlobalPos   = cn->getGlobalPosition();
            Vector2 const cnGlobalScale = cn->getGlobalScale();
            float const   cnMaxScale    = std::max(cnGlobalScale.x, cnGlobalScale.y);

            if (CheckCollisionCircleLine(cnGlobalPos, cnMaxScale, startPt1, endPt1)) {
                collided.push_back(cn);
            }
        }

        return collided;
    }

    std::vector<std::shared_ptr<rlf::Node::ColliderNode>> PhysicsSystem::checkCollision(std::shared_ptr<rlf::Node::CircleColliderNode> colliderNode) {
        // Initialize data
        std::vector<std::shared_ptr<rlf::Node::ColliderNode>> collided;

        Vector2 colliderGlobalPosition = colliderNode->getGlobalPosition();
        Vector2 colliderGlobalScale    = colliderNode->getGlobalScale();
        f32     colliderMaxScale       = std::max(colliderGlobalScale.x, colliderGlobalScale.y);

        // Check against line colliders
        for (auto const& cn : mLineColliderNodes) {
            if (cn->hasAnyOfTags(colliderNode->getTags())) {
                continue;
            }

            if (!cn->getActive()) {
                continue;
            }

            auto const& globalTransform = cn->getGlobalTransform();
            auto const  startPt         = cn->getStartPoint() * globalTransform;
            auto const  endPt           = cn->getEndPoint() * globalTransform;
            if (CheckCollisionCircleLine(colliderGlobalPosition, colliderMaxScale, startPt, endPt)) {
                collided.push_back(cn);
            }
        }

        // Check against sphere colliders
        for (auto const& cn : mSphereColliderNodes) {
            if (cn->hasAnyOfTags(colliderNode->getTags())) {
                continue;
            }

            if (!cn->getActive()) {
                continue;
            }

            if (cn == colliderNode) {
                continue;
            }

            Vector2 const cnGlobalPos   = cn->getGlobalPosition();
            Vector2 const cnGlobalScale = cn->getGlobalScale();
            float const   cnMaxScale    = std::max(cnGlobalScale.x, cnGlobalScale.y);

            if (CheckCollisionCircles(colliderGlobalPosition, colliderMaxScale, cnGlobalPos, cnMaxScale)) {
                collided.push_back(cn);
            }
        }

        return collided;
    }
}
