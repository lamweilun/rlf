#include <Node/UI/UICameraNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node
{

    void UICameraNode::setupImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addUICameraNode(as<UICameraNode>());
    }
    void UICameraNode::shutdownImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->eraseUICameraNode(as<UICameraNode>());
    }

    rlf::Vec2f const& UICameraNode::getReferenceResolution() const
    {
        return mReferenceResolution;
    }
    void UICameraNode::setReferenceResolution(rlf::Vec2f const& referenceResolution)
    {
        mReferenceResolution = referenceResolution;
    }

    f32 UICameraNode::getZoom() const
    {
        return mZoom;
    }
    void UICameraNode::setZoom(f32 const zoom)
    {
        mZoom = zoom;
    }

    bool UICameraNode::getZoomToWindowSize() const
    {
        return mZoomToWindowSize;
    }
    void UICameraNode::setZoomToWindowSize(bool const zoomToWindowSize)
    {
        mZoomToWindowSize = zoomToWindowSize;
    }

    bool UICameraNode::getIsActiveUICamera() const
    {
        return mIsActiveUICamera;
    }
    void UICameraNode::setIsActiveUICamera(bool const isActiveCamera)
    {
        mIsActiveUICamera = isActiveCamera;
        auto renderSys    = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>();
        if (mIsActiveUICamera)
        {
            renderSys->setActiveUICameraNode(this);
        }
        else
        {
            renderSys->setActiveUICameraNode(nullptr);
        }
    }

    Camera2D UICameraNode::getAsCamera2DUI() const
    {
        Camera2D   camera = {};
        auto const offset = rlf::Vec2f{static_cast<f32>(GetScreenWidth()) * 0.5f, static_cast<f32>(GetScreenHeight()) * 0.5f} + getGlobalPosition();
        camera.offset     = {offset.x, offset.y};
        camera.target     = Vector2Zeros;
        camera.rotation   = QuaternionToEuler(getGlobalRotation()).z * RAD2DEG;
        if (mZoomToWindowSize)
        {
            auto const scale = rlf::Vec2f{static_cast<f32>(GetScreenWidth()), static_cast<f32>(GetScreenHeight())} / mReferenceResolution;
            camera.zoom      = std::min(scale.x, scale.y) * mZoom;
        }
        else
        {
            camera.zoom = mZoom;
        }
        return camera;
    }
}
