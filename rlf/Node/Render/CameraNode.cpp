#include <Node/Render/CameraNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node {
    void CameraNode::setupImpl() {
        auto renderSys = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>();
        renderSys->addCameraNode(std::static_pointer_cast<CameraNode>(shared_from_this()));
    }
    void CameraNode::shutdownImpl() {
        auto renderSys = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>();
        renderSys->eraseCameraNode(std::static_pointer_cast<CameraNode>(shared_from_this()));
    }

    Color const& CameraNode::getClearColor() const {
        return mClearColor;
    }
    void CameraNode::setClearColor(Color const& color) {
        mClearColor = color;
    }

    Vector2 const& CameraNode::getReferenceResolution() const {
        return mReferenceResolution;
    }
    void CameraNode::setReferenceResolution(Vector2 const& referenceResolution) {
        mReferenceResolution = referenceResolution;
    }

    f32 CameraNode::getZoom() const {
        return mZoom;
    }
    void CameraNode::setZoom(f32 const zoom) {
        mZoom = zoom;
    }

    bool CameraNode::getZoomToWindowSize() const {
        return mZoomToWindowSize;
    }
    void CameraNode::setZoomToWindowSize(bool const zoomToWindowSize) {
        mZoomToWindowSize = zoomToWindowSize;
    }

    bool CameraNode::getIsActiveCamera() const {
        return mIsActiveCamera;
    }
    void CameraNode::setIsActiveCamera(bool const isActiveCamera) {
        mIsActiveCamera = isActiveCamera;
        auto renderSys  = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>();
        if (mIsActiveCamera) {
            renderSys->setActiveCameraNode(std::static_pointer_cast<CameraNode>(shared_from_this()));
        } else {
            renderSys->setActiveCameraNode(nullptr);
        }
    }

    Camera2D CameraNode::getAsCamera2D() const {
        Camera2D camera = {};
        camera.offset   = Vector2{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f} + getGlobalPosition();
        camera.target   = Vector2Zeros;
        camera.rotation = QuaternionToEuler(getGlobalRotation()).z * RAD2DEG;
        if (mZoomToWindowSize) {
            auto const scale = Vector2{static_cast<f32>(GetScreenWidth()), static_cast<f32>(GetScreenHeight())} / mReferenceResolution;
            camera.zoom      = std::min(scale.x, scale.y) * mZoom;
        } else {
            camera.zoom = mZoom;
        }
        return camera;
    }
    Camera2D CameraNode::getAsCamera2DUI() const {
        Camera2D camera = {};
        camera.offset   = Vector2{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f};
        camera.target   = Vector2Zeros;
        camera.rotation = 0.0f;
        if (mZoomToWindowSize) {
            auto const scale = Vector2{static_cast<f32>(GetScreenWidth()), static_cast<f32>(GetScreenHeight())} / mReferenceResolution;
            camera.zoom      = std::min(scale.x, scale.y) * mZoom;
        } else {
            camera.zoom = mZoom;
        }
        return camera;
    }
}
