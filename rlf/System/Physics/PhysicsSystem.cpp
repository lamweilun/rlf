#include <System/Physics/PhysicsSystem.hpp>

#include <Util/Physics/CollisionDetection.hpp>

namespace rlf::System {
    void PhysicsSystem::addColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode) {
        mLineColliderNodes.insert(lineColliderNode);
    }
    void PhysicsSystem::addColliderNode(std::shared_ptr<rlf::Node::BoxColliderNode> boxColliderNode) {
        mBoxColliderNodes.insert(boxColliderNode);
    }

    void PhysicsSystem::addColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode) {
        mCircleColliderNodes.insert(sphereColliderNode);
    }

    void PhysicsSystem::removeColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode) {
        mLineColliderNodes.erase(lineColliderNode);
    }

    void PhysicsSystem::removeColliderNode(std::shared_ptr<rlf::Node::BoxColliderNode> boxColliderNode) {
        mBoxColliderNodes.erase(boxColliderNode);
    }

    void PhysicsSystem::removeColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode) {
        mCircleColliderNodes.erase(sphereColliderNode);
    }

    std::vector<rlf::CollideInfo> PhysicsSystem::getCollisionInfos(std::shared_ptr<rlf::Node::LineColliderNode> colliderNode) {
        (void)colliderNode;
        std::vector<rlf::CollideInfo> infos;
        return infos;
    }

    std::vector<rlf::CollideInfo> PhysicsSystem::getCollisionInfos(std::shared_ptr<rlf::Node::BoxColliderNode> colliderNode) {
        std::vector<rlf::CollideInfo> collidedInfos;

        Vector2 const     globalPos1   = colliderNode->getGlobalPosition();
        Vector2 const     globalScale1 = colliderNode->getGlobalScale();
        Vector2 const     boxMin       = globalPos1 - globalScale1 * 0.5f;
        Vector2 const     boxMax       = globalPos1 + globalScale1 * 0.5f;
        BoundingBox const box{
            {boxMin.x, boxMin.y, 0.0f},
            {boxMax.x, boxMax.y, 0.0f}
        };

        for (auto const& circleCollider : mCircleColliderNodes) {
            if (!circleCollider->getActive()) {
                continue;
            }

            Vector2 const circlePos    = circleCollider->getGlobalPosition();
            Vector2 const globalScale2 = circleCollider->getGlobalScale();
            f32 const     circleRadius = std::min(globalScale2.x * 0.5f, globalScale2.y * 0.5f);

            Vector2 collidedPoint    = Vector2Zeros;
            Vector2 collidedNormal   = Vector2Zeros;
            Vector2 collidedTangent  = Vector2Zeros;
            f32     penetratingDepth = 0.0f;
            if (rlf::phys::CheckCollisionBoxCircle(box, circlePos, circleRadius, collidedPoint, collidedNormal, collidedTangent, penetratingDepth)) {
                rlf::CollideInfo info;
                info.self            = colliderNode;
                info.other           = circleCollider;
                info.collidedPoint   = collidedPoint;
                info.collidedNormal  = collidedNormal;
                info.collidedTangent = collidedTangent;
                info.collidedDepth   = penetratingDepth;
                collidedInfos.push_back(info);
            }
        }
        return collidedInfos;
    }

    std::vector<rlf::CollideInfo> PhysicsSystem::getCollisionInfos(std::shared_ptr<rlf::Node::CircleColliderNode> colliderNode) {
        std::vector<rlf::CollideInfo> collidedInfos;

        Vector2 const globalPos1      = colliderNode->getGlobalPosition();
        Vector2 const globalScale1    = colliderNode->getGlobalScale();
        f32 const     colliderRadius1 = std::min(globalScale1.x, globalScale1.y);

        // Check collision with other box colliders
        for (auto const& boxCollider : mBoxColliderNodes) {
            if (!boxCollider->getActive()) {
                continue;
            }

            Vector2 const globalPos2   = boxCollider->getGlobalPosition();
            Vector2 const globalScale2 = boxCollider->getGlobalScale();
            Vector2 const boxMin       = globalPos2 - globalScale2 * 0.5f;
            Vector2 const boxMax       = globalPos2 + globalScale2 * 0.5f;
            BoundingBox   box;
            box.min = Vector3{boxMin.x, boxMin.y, 0.0f};
            box.max = Vector3{boxMax.x, boxMax.y, 0.0f};

            Vector2 collidedPoint    = Vector2Zeros;
            Vector2 collidedNormal   = Vector2Zeros;
            Vector2 collidedTangent  = Vector2Zeros;
            f32     penetratingDepth = 0.0f;
            if (rlf::phys::CheckCollisionBoxCircle(box, globalPos1, colliderRadius1, collidedPoint, collidedNormal, collidedTangent, penetratingDepth)) {
                rlf::CollideInfo info;
                info.self            = colliderNode;
                info.other           = boxCollider;
                info.collidedPoint   = collidedPoint;
                info.collidedNormal  = collidedNormal;
                info.collidedTangent = collidedTangent;
                info.collidedDepth   = penetratingDepth;
                collidedInfos.push_back(info);
            }
        }

        // Check collision with other circle colliders
        for (auto const& circleCollider : mCircleColliderNodes) {
            if (circleCollider == colliderNode) {
                continue;
            }
            if (!circleCollider->getActive()) {
                continue;
            }

            Vector2 const globalPos2      = circleCollider->getGlobalPosition();
            Vector2 const globalScale2    = circleCollider->getGlobalScale();
            f32 const     colliderRadius2 = std::min(globalScale2.x, globalScale2.y);
            if (CheckCollisionCircles(globalPos1, colliderRadius1, globalPos2, colliderRadius2)) {
                rlf::CollideInfo info;
                info.self            = colliderNode;
                info.other           = circleCollider;
                info.collidedNormal  = Vector2Normalize(globalPos2 - globalPos1);
                info.collidedPoint   = globalPos1 + info.collidedNormal * colliderRadius1;
                info.collidedTangent = Vector2Rotate(info.collidedNormal, std::numbers::pi_v<f32> * 0.5f);
                collidedInfos.push_back(info);
            }
        }

        return collidedInfos;
    }

#ifdef RLF_EDITOR
    void PhysicsSystem::editorRender() {
        for (auto const& node : mLineColliderNodes) {
            if (!node->getActive()) {
                continue;
            }

            auto matF = MatrixToFloatV(node->getGlobalTransform());
            rlPushMatrix();
            rlMultMatrixf(matF.v);

            DrawLineEx(node->getStartPoint(), node->getEndPoint(), 1.0f, GREEN);

            rlPopMatrix();
        }

        for (auto const& node : mBoxColliderNodes) {
            if (!node->getActive()) {
                continue;
            }

            auto matF = MatrixToFloatV(node->getGlobalTransform());
            rlPushMatrix();
            rlMultMatrixf(matF.v);

            DrawBoundingBox(BoundingBox{
                                Vector3{-0.5f, -0.5f, 0.0f},
                                Vector3{ 0.5f,  0.5f, 0.0f}
            },
                            GREEN);

            rlPopMatrix();
        }

        for (auto const& node : mCircleColliderNodes) {
            if (!node->getActive()) {
                continue;
            }

            auto matF = MatrixToFloatV(node->getGlobalTransform());
            rlPushMatrix();
            rlMultMatrixf(matF.v);

            DrawCircleLinesV(Vector2Zeros, 1.0f, GREEN);

            rlPopMatrix();
        }
    }
#endif
}
