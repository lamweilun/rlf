#include <System/Render/RenderSystem.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

#ifdef RLF_EDITOR
#include <System/Editor/EditorSystem.hpp>
#endif

namespace rlf::System {
    void RenderSystem::addRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode) {
        mRenderNodes[renderNode->getLayer()].insert(renderNode);
    }
    void RenderSystem::removeRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode) {
        mRenderNodes[renderNode->getLayer()].erase(renderNode);
    }

    void RenderSystem::addParticleRenderNode(std::shared_ptr<rlf::Node::ParticleRenderNode> renderNode) {
        mParticleRenderNodes[renderNode->getLayer()].insert(renderNode);
    }
    void RenderSystem::removeParticleRenderNode(std::shared_ptr<rlf::Node::ParticleRenderNode> renderNode) {
        mParticleRenderNodes[renderNode->getLayer()].erase(renderNode);
    }

    void RenderSystem::addUINode(std::shared_ptr<rlf::Node::UINode> uiNode) {
        mUINodes[uiNode->getLayer()].insert(uiNode);
    }
    void RenderSystem::removeUINode(std::shared_ptr<rlf::Node::UINode> uiNode) {
        mUINodes[uiNode->getLayer()].erase(uiNode);
    }

    void RenderSystem::addCameraNode(std::shared_ptr<rlf::Node::CameraNode> cameraNode) {
        mCameraNodes.insert(cameraNode);
    }
    void RenderSystem::eraseCameraNode(std::shared_ptr<rlf::Node::CameraNode> cameraNode) {
        mCameraNodes.erase(cameraNode);
        if (mActiveCameraNode == cameraNode) {
            mActiveCameraNode = nullptr;
        }
    }
    void RenderSystem::setActiveCameraNode(std::shared_ptr<rlf::Node::CameraNode> cameraNode) {
        if (cameraNode == nullptr) {
            mActiveCameraNode = nullptr;
            return;
        }

        for (auto camNode : mCameraNodes) {
            if (camNode == cameraNode) {
                continue;
            }
            camNode->setIsActiveCamera(false);
        }
        mActiveCameraNode = cameraNode;
    }
    std::shared_ptr<rlf::Node::CameraNode> RenderSystem::getActiveCameraNode() const {
        return mActiveCameraNode;
    }

    void RenderSystem::addUICameraNode(std::shared_ptr<rlf::Node::UICameraNode> uiCameraNode) {
        mUICameraNodes.insert(uiCameraNode);
    }
    void RenderSystem::eraseUICameraNode(std::shared_ptr<rlf::Node::UICameraNode> uiCameraNode) {
        mUICameraNodes.erase(uiCameraNode);
        if (mActiveUICameraNode == uiCameraNode) {
            mActiveUICameraNode = nullptr;
        }
    }
    void RenderSystem::setActiveUICameraNode(std::shared_ptr<rlf::Node::UICameraNode> uiCameraNode) {
        if (uiCameraNode == nullptr) {
            mActiveUICameraNode = nullptr;
            return;
        }

        for (auto camNode : mUICameraNodes) {
            if (camNode == uiCameraNode) {
                continue;
            }
            camNode->setIsActiveUICamera(false);
        }
        mActiveUICameraNode = uiCameraNode;
    }
    std::shared_ptr<rlf::Node::UICameraNode> RenderSystem::getActiveUICameraNode() const {
        return mActiveUICameraNode;
    }

    Vector2 RenderSystem::getMousePosition() const {
        Camera2D camera;
        if (auto activeCameraNode = getActiveCameraNode()) {
            camera = activeCameraNode->getAsCamera2D();
        } else {
            camera.offset   = Vector2{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f};
            camera.target   = Vector2Zeros;
            camera.rotation = 0.0f;
            camera.zoom     = 1.0f;
        }
        auto const mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
        return mousePos;
    }

    Vector2 RenderSystem::getUIMousePosition() const {
        Camera2D camera;
        if (auto activeCameraNode = getActiveUICameraNode()) {
            camera = activeCameraNode->getAsCamera2DUI();
        } else {
            camera.offset   = Vector2{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f};
            camera.target   = Vector2Zeros;
            camera.rotation = 0.0f;
            camera.zoom     = 1.0f;
        }
        auto const mousePos = GetScreenToWorld2D(GetMousePosition(), camera);
        return mousePos;
    }

    void RenderSystem::render() {
        if (mActiveCameraNode && mActiveCameraNode->getActive()) {
            Camera2D camera = mActiveCameraNode->getAsCamera2D();
            BeginMode2D(camera);
            ClearBackground(mActiveCameraNode->getClearColor());
        }

        for (auto& [layer, nodes] : mRenderNodes) {
            for (auto& node : nodes) {
                // Not required, check RenderNode::setActiveImpl
                // if (!node->getActive()) {
                //     continue;
                // }

                auto matF = MatrixToFloatV(node->getGlobalTransform());
                rlPushMatrix();
                rlMultMatrixf(matF.v);

                node->renderImpl();

                rlPopMatrix();
            }
        }

        // Render Particles
        for (auto& [layer, nodes] : mParticleRenderNodes) {
            for (auto& node : nodes) {
                // Not required, check RenderNode::setActiveImpl
                // if (!node->getActive()) {
                //     continue;
                // }

                auto matF = MatrixToFloatV(node->getGlobalTransform());
                rlPushMatrix();
                rlMultMatrixf(matF.v);

                node->renderImpl();

                rlPopMatrix();
            }
        }

#ifdef RLF_EDITOR
        auto physicsSys = rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>();
        physicsSys->editorRender();
#endif

        if (mActiveCameraNode && mActiveCameraNode->getActive()) {
            EndMode2D();
        }

        // Render UI
        if (mActiveUICameraNode && mActiveUICameraNode->getActive()) {
            Camera2D camera = mActiveUICameraNode->getAsCamera2DUI();
            BeginMode2D(camera);
        }
        for (auto& [layer, nodes] : mUINodes) {
            for (auto& node : nodes) {
                // Not required, check UINode::setActiveImpl
                // if (!node->getActive()) {
                //     continue;
                // }

                auto matF = MatrixToFloatV(node->getGlobalTransform());
                rlPushMatrix();
                rlMultMatrixf(matF.v);

                node->renderImpl();

                rlPopMatrix();
            }
        }
        if (mActiveUICameraNode && mActiveUICameraNode->getActive()) {
            EndMode2D();
        }
    }
}
