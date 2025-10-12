#include <Node/UI/UICameraNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node {
    Vector2 const& UICameraNode::getReferenceResolution() const {
        return mReferenceResolution;
    }
    void UICameraNode::setReferenceResolution(Vector2 const& referenceResolution) {
        mReferenceResolution = referenceResolution;
    }

    f32 UICameraNode::getZoom() const {
        return mZoom;
    }
    void UICameraNode::setZoom(f32 const zoom) {
        mZoom = zoom;
    }

    bool UICameraNode::getZoomToWindowSize() const {
        return mZoomToWindowSize;
    }
    void UICameraNode::setZoomToWindowSize(bool const zoomToWindowSize) {
        mZoomToWindowSize = zoomToWindowSize;
    }

    bool UICameraNode::getIsActiveUICamera() const {
        return mIsActiveUICamera;
    }
    void UICameraNode::setIsActiveUICamera(bool const isActiveCamera) {
        mIsActiveUICamera = isActiveCamera;
        auto renderSys    = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>();
        if (mIsActiveUICamera) {
            renderSys->setActiveUICameraNode(std::static_pointer_cast<UICameraNode>(shared_from_this()));
        } else {
            renderSys->setActiveUICameraNode(nullptr);
        }
    }

    Camera2D UICameraNode::getAsCamera2DUI() const {
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
}
