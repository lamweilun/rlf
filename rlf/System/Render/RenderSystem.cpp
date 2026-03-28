#include <System/Render/RenderSystem.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

#ifdef RLF_EDITOR
#include <System/Editor/EditorSystem.hpp>
#endif

namespace rlf
{
    void RenderSystem::addRenderNode(rlf::Node::RenderNode* const& renderNode)
    {
        mRenderNodes[renderNode->getLayer()].insert(renderNode);
    }
    void RenderSystem::removeRenderNode(rlf::Node::RenderNode* const& renderNode)
    {
        mRenderNodes[renderNode->getLayer()].erase(renderNode);
    }

    void RenderSystem::addParticleRenderNode(rlf::Node::ParticleRenderNode* const& renderNode)
    {
        mParticleRenderNodes[renderNode->getLayer()].insert(renderNode);
    }
    void RenderSystem::removeParticleRenderNode(rlf::Node::ParticleRenderNode* const& renderNode)
    {
        mParticleRenderNodes[renderNode->getLayer()].erase(renderNode);
    }

    void RenderSystem::addUINode(rlf::Node::UINode* const& uiNode)
    {
        mUINodes[uiNode->getLayer()].insert(uiNode);
    }
    void RenderSystem::removeUINode(rlf::Node::UINode* const& uiNode)
    {
        mUINodes[uiNode->getLayer()].erase(uiNode);
    }

    void RenderSystem::addCameraNode(rlf::Node::CameraNode* const& cameraNode)
    {
        mCameraNodes.insert(cameraNode);
    }
    void RenderSystem::eraseCameraNode(rlf::Node::CameraNode* const& cameraNode)
    {
        mCameraNodes.erase(cameraNode);
        if (mActiveCameraNode == cameraNode)
        {
            mActiveCameraNode = nullptr;
        }
    }
    void RenderSystem::setActiveCameraNode(rlf::Node::CameraNode* const& cameraNode)
    {
        if (cameraNode == nullptr)
        {
            mActiveCameraNode = nullptr;
            return;
        }

        for (auto camNode : mCameraNodes)
        {
            if (camNode == cameraNode)
            {
                continue;
            }
            camNode->setIsActiveCamera(false);
        }
        mActiveCameraNode = cameraNode;
    }
    rlf::Node::CameraNode* RenderSystem::getActiveCameraNode() const
    {
        return mActiveCameraNode;
    }

    void RenderSystem::addUICameraNode(rlf::Node::UICameraNode* const& uiCameraNode)
    {
        mUICameraNodes.insert(uiCameraNode);
    }
    void RenderSystem::eraseUICameraNode(rlf::Node::UICameraNode* const& uiCameraNode)
    {
        mUICameraNodes.erase(uiCameraNode);
        if (mActiveUICameraNode == uiCameraNode)
        {
            mActiveUICameraNode = nullptr;
        }
    }
    void RenderSystem::setActiveUICameraNode(rlf::Node::UICameraNode* const& uiCameraNode)
    {
        if (uiCameraNode == nullptr)
        {
            mActiveUICameraNode = nullptr;
            return;
        }

        for (auto camNode : mUICameraNodes)
        {
            if (camNode == uiCameraNode)
            {
                continue;
            }
            camNode->setIsActiveUICamera(false);
        }
        mActiveUICameraNode = uiCameraNode;
    }
    rlf::Node::UICameraNode* RenderSystem::getActiveUICameraNode() const
    {
        return mActiveUICameraNode;
    }

    rlf::Vec2f RenderSystem::getMousePosition() const
    {
        Camera2D camera;
        if (auto activeCameraNode = getActiveCameraNode())
        {
            camera = activeCameraNode->getAsCamera2D();
        }
        else
        {
            auto const offset = rlf::Vec2f{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f};
            camera.offset     = {offset.x, offset.y};
            camera.target     = Vector2Zeros;
            camera.rotation   = 0.0f;
            camera.zoom       = 1.0f;
        }
        auto const mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
        return rlf::Vec2f{mousePos.x, mousePos.y};
    }

    rlf::Vec2f RenderSystem::getUIMousePosition() const
    {
        Camera2D camera;
        if (auto activeCameraNode = getActiveUICameraNode())
        {
            camera = activeCameraNode->getAsCamera2DUI();
        }
        else
        {
            auto const offset = rlf::Vec2f{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f};
            camera.offset     = {offset.x, offset.y};
            camera.target     = Vector2Zeros;
            camera.rotation   = 0.0f;
            camera.zoom       = 1.0f;
        }
        auto const mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
        return rlf::Vec2f{mousePos.x, mousePos.y};
    }

    rlf::Vec2f RenderSystem::getScreenSize() const
    {
        if (auto activeCameraNode = getActiveCameraNode())
        {
            return activeCameraNode->getReferenceResolution();
        }
        return rlf::Vec2f{static_cast<f32>(GetScreenWidth()), static_cast<f32>(GetScreenHeight())};
    }

    void RenderSystem::render()
    {
        if (mActiveCameraNode && mActiveCameraNode->getActive())
        {
            Camera2D camera = mActiveCameraNode->getAsCamera2D();
            BeginMode2D(camera);
            ClearBackground(mActiveCameraNode->getClearColor());
        }

        for (auto& [layer, nodes] : mRenderNodes)
        {
            for (auto& node : nodes)
            {
                auto matF = MatrixToFloatV(node->getGlobalTransform());
                rlPushMatrix();
                rlMultMatrixf(matF.v);

                node->renderImpl();

                rlPopMatrix();
            }
        }

        // Render Particles
        for (auto& [layer, nodes] : mParticleRenderNodes)
        {
            for (auto& node : nodes)
            {
                auto matF = MatrixToFloatV(node->getGlobalTransform());
                rlPushMatrix();
                rlMultMatrixf(matF.v);

                node->renderImpl();

                rlPopMatrix();
            }
        }

#ifdef RLF_EDITOR
        auto physicsSys = rlf::Engine::getInstance().getSystem<rlf::PhysicsSystem>();
        physicsSys->editorRender();
#endif

        if (mActiveCameraNode && mActiveCameraNode->getActive())
        {
            EndMode2D();
        }

        // Render UI
        if (mActiveUICameraNode && mActiveUICameraNode->getActive())
        {
            Camera2D camera = mActiveUICameraNode->getAsCamera2DUI();
            BeginMode2D(camera);
        }
        for (auto& [layer, nodes] : mUINodes)
        {
            for (auto& node : nodes)
            {
                auto matF = MatrixToFloatV(node->getGlobalTransform());
                rlPushMatrix();
                rlMultMatrixf(matF.v);

                node->renderImpl();

                rlPopMatrix();
            }
        }
        if (mActiveUICameraNode && mActiveUICameraNode->getActive())
        {
            EndMode2D();
        }
    }
}
