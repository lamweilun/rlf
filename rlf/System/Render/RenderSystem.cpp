#include <System/Render/RenderSystem.hpp>

#include <Engine/Engine.hpp>
#include <System/Physics/PhysicsSystem.hpp>

namespace rlf::System {
    void RenderSystem::addRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode) {
        mRenderNodes[renderNode->getLayer()].insert(renderNode);
    }
    void RenderSystem::removeRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode) {
        mRenderNodes[renderNode->getLayer()].erase(renderNode);
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

    void RenderSystem::render() {
        if (mActiveCameraNode && mActiveCameraNode->getActive()) {
            Camera2D camera = {};
            camera.offset   = Vector2{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f} + mActiveCameraNode->getGlobalPosition();
            camera.target   = Vector2Zeros;
            camera.rotation = QuaternionToEuler(mActiveCameraNode->getGlobalRotation()).z * RAD2DEG;
            camera.zoom     = mActiveCameraNode->getZoom();
            BeginMode2D(camera);
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

#ifdef RLF_EDITOR
        auto physicsSys = rlf::Engine::getInstance().getSystem<rlf::System::PhysicsSystem>();
        physicsSys->editorRender();
#endif

        if (mActiveCameraNode && mActiveCameraNode->getActive()) {
            EndMode2D();
        }

        // Render UI
        if (mActiveCameraNode && mActiveCameraNode->getActive()) {
            Camera2D camera = {};
            camera.offset   = Vector2{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f};
            camera.target   = Vector2Zeros;
            camera.rotation = 0.0f;
            camera.zoom     = mActiveCameraNode->getZoom();
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
        if (mActiveCameraNode && mActiveCameraNode->getActive()) {
            EndMode2D();
        }
    }
}
