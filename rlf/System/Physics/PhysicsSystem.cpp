#include <System/Physics/PhysicsSystem.hpp>

#include <System/Physics/CollideInfo.hpp>
#include <Util/Physics/CollisionDetection.hpp>

namespace rlf
{
    void PhysicsSystem::addColliderNode(std::shared_ptr<rlf::BoxColliderNode> boxColliderNode)
    {
        mBoxColliderNodes.insert(boxColliderNode);
    }

    void PhysicsSystem::addColliderNode(std::shared_ptr<rlf::CircleColliderNode> circleCollider)
    {
        mCircleColliderNodes.insert(circleCollider);
    }

    void PhysicsSystem::removeColliderNode(std::shared_ptr<rlf::BoxColliderNode> boxColliderNode)
    {
        mBoxColliderNodes.erase(boxColliderNode);
    }

    void PhysicsSystem::removeColliderNode(std::shared_ptr<rlf::CircleColliderNode> circleCollider)
    {
        mCircleColliderNodes.erase(circleCollider);
    }

    void PhysicsSystem::update()
    {
        std::unordered_map<void*, std::set<void*>>                                            collidedMap;
        std::unordered_map<std::shared_ptr<rlf::ColliderNode>, std::vector<rlf::CollideInfo>> collideInfos;

        // For every CircleCollider
        for (auto const& cc1 : mCircleColliderNodes)
        {
            if (!cc1->getActive())
            {
                continue;
            }
            auto const cc1Pos    = cc1->getGlobalPosition();
            auto const cc1Scale  = cc1->getGlobalScale();
            f32 const  cc1Radius = std::min(cc1Scale.x, cc1Scale.y);

            // Check against other circle colliders
            for (auto const& cc2 : mCircleColliderNodes)
            {
                if (collidedMap[cc1.get()].contains(cc2.get()))
                {
                    continue;
                }
                if (cc1->getTag() == cc2->getTag())
                {
                    continue;
                }
                if (!cc2->getActive())
                {
                    continue;
                }
                if (cc1 == cc2)
                {
                    continue;
                }

                auto const cc2Pos    = cc2->getGlobalPosition();
                auto const cc2Scale  = cc2->getGlobalScale();
                f32 const  cc2Radius = std::min(cc2Scale.x, cc2Scale.y);

                if (CheckCollisionCircles({cc1Pos.x, cc1Pos.y}, cc1Radius, {cc2Pos.x, cc2Pos.y}, cc2Radius))
                {
                    rlf::CollideInfo info1;
                    info1.self            = cc1;
                    info1.other           = cc2;
                    info1.collidedNormal  = (cc1Pos - cc2Pos).Normalized();
                    info1.collidedPoint   = cc1Pos + info1.collidedNormal * cc1Radius;
                    info1.collidedTangent = info1.collidedNormal.RotateBy(std::numbers::pi_v<f32> * 0.5f);

                    rlf::CollideInfo info2;
                    info2.self            = cc2;
                    info2.other           = cc1;
                    info2.collidedNormal  = (cc2Pos - cc1Pos).Normalized();
                    info2.collidedPoint   = cc2Pos + info2.collidedNormal * cc2Radius;
                    info2.collidedTangent = info2.collidedNormal.RotateBy(std::numbers::pi_v<f32> * 0.5f);

                    collideInfos[cc1].push_back(info1);
                    collideInfos[cc2].push_back(info2);

                    collidedMap[cc1.get()].insert(cc2.get());
                    collidedMap[cc2.get()].insert(cc1.get());
                }
            }

            // Check against other BoxCollider
            for (auto const& bc : mBoxColliderNodes)
            {
                if (collidedMap[cc1.get()].contains(bc.get()))
                {
                    continue;
                }
                if (cc1->getTag() == bc->getTag())
                {
                    continue;
                }
                if (!bc->getActive())
                {
                    continue;
                }

                rlf::Vec2f const bcPos    = bc->getGlobalPosition();
                rlf::Vec2f const bcScale  = bc->getGlobalScale();
                f32 const        bcRotRad = bc->getGlobalRotationRad();
                rlf::Vec2f const boxMin   = bcPos - bcScale * 0.5f;
                rlf::Vec2f const boxMax   = bcPos + bcScale * 0.5f;
                BoundingBox      box{
                    {boxMin.x, boxMin.y, 0.0f},
                    {boxMax.x, boxMax.y, 0.0f}
                };

                rlf::Vec2f collidedPoint    = rlf::Vec2f::Zero();
                rlf::Vec2f collidedNormal   = rlf::Vec2f::Zero();
                rlf::Vec2f collidedTangent  = rlf::Vec2f::Zero();
                f32        penetratingDepth = 0.0f;
                if (rlf::phys::CheckCollisionBoxCircle(box, bcRotRad, cc1Pos, cc1Radius, collidedPoint, collidedNormal, collidedTangent, penetratingDepth))
                {
                    rlf::CollideInfo info1;
                    info1.self            = cc1;
                    info1.other           = bc;
                    info1.collidedPoint   = collidedPoint;
                    info1.collidedNormal  = collidedNormal;
                    info1.collidedTangent = collidedTangent;
                    info1.collidedDepth   = penetratingDepth;

                    rlf::CollideInfo info2;
                    info2.self            = bc;
                    info2.other           = cc1;
                    info2.collidedPoint   = collidedPoint;
                    info2.collidedNormal  = -collidedNormal;
                    info2.collidedTangent = -collidedTangent;
                    info2.collidedDepth   = penetratingDepth;

                    collideInfos[cc1].push_back(info1);
                    collideInfos[bc].push_back(info2);

                    collidedMap[cc1.get()].insert(bc.get());
                    collidedMap[bc.get()].insert(cc1.get());
                }
            }
        }

        // For every BoxCollider
        for (auto const& bc1 : mBoxColliderNodes)
        {
            if (!bc1->getActive())
            {
                continue;
            }
            rlf::Vec2f const bc1Pos         = bc1->getGlobalPosition();
            rlf::Vec2f const bc1Scale       = bc1->getGlobalScale();
            f32 const        bc1RotationRad = bc1->getGlobalRotationRad();
            rlf::Vec2f const box1Min        = bc1Pos - bc1Scale * 0.5f;
            rlf::Vec2f const box1Max        = bc1Pos + bc1Scale * 0.5f;
            BoundingBox      box1{
                {box1Min.x, box1Min.y, 0.0f},
                {box1Max.x, box1Max.y, 0.0f}
            };

            // Check against other BoxCollider
            for (auto const& bc2 : mBoxColliderNodes)
            {
                if (!bc2->getActive())
                {
                    continue;
                }
                if (bc1->getTag() == bc2->getTag())
                {
                    continue;
                }
                if (collidedMap[bc1.get()].contains(bc2.get()))
                {
                    continue;
                }
                if (bc1 == bc2)
                {
                    continue;
                }

                rlf::Vec2f const bc2Pos         = bc2->getGlobalPosition();
                rlf::Vec2f const bc2Scale       = bc2->getGlobalScale();
                f32 const        bc2RotationRad = bc2->getGlobalRotationRad();
                rlf::Vec2f const box2Min        = bc2Pos - bc2Scale * 0.5f;
                rlf::Vec2f const box2Max        = bc2Pos + bc2Scale * 0.5f;
                BoundingBox      box2{
                    {box2Min.x, box2Min.y, 0.0f},
                    {box2Max.x, box2Max.y, 0.0f}
                };

                rlf::Vec2f collidedPoint    = rlf::Vec2f::Zero();
                rlf::Vec2f collidedNormal   = rlf::Vec2f::Zero();
                rlf::Vec2f collidedTangent  = rlf::Vec2f::Zero();
                f32        penetratingDepth = 0.0f;
                if (rlf::phys::CheckCollisionBoxToBox(box1, bc1RotationRad,
                                                      box2, bc2RotationRad,
                                                      collidedPoint, collidedNormal, collidedTangent, penetratingDepth))
                {
                    collidedMap[bc1.get()].insert(bc2.get());
                    collidedMap[bc2.get()].insert(bc1.get());

                    rlf::CollideInfo info1;
                    info1.self            = bc1;
                    info1.other           = bc2;
                    info1.collidedPoint   = collidedPoint;
                    info1.collidedNormal  = collidedNormal;
                    info1.collidedTangent = collidedTangent;
                    info1.collidedDepth   = penetratingDepth;

                    rlf::CollideInfo info2;
                    info2.self            = bc2;
                    info2.other           = bc1;
                    info2.collidedPoint   = collidedPoint;
                    info2.collidedNormal  = -collidedNormal;
                    info2.collidedTangent = -collidedTangent;
                    info2.collidedDepth   = penetratingDepth;

                    collideInfos[bc1].push_back(info1);
                    collideInfos[bc2].push_back(info2);
                }
            }
        }

        for (auto const& [collider, infos] : collideInfos)
        {
            for (auto const& info : infos)
            {
                collider->invokeCollidedCallback(info);
            }
        }
    }

#ifdef RLF_EDITOR
    void PhysicsSystem::editorRender()
    {
        for (auto const& node : mBoxColliderNodes)
        {
            if (!node->getActive())
            {
                continue;
            }

            auto matF = MatrixToFloatV(node->getGlobalTransform());
            rlPushMatrix();
            rlMultMatrixf(matF.v);

            DrawBoundingBox(BoundingBox{
                                {-0.5f, -0.5f, 0.0f},
                                { 0.5f,  0.5f, 0.0f}
            },
                            GREEN);

            rlPopMatrix();
        }

        for (auto const& node : mCircleColliderNodes)
        {
            if (!node->getActive())
            {
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
