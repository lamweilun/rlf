#include <Node/Render/CameraNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node {
    void CameraNode::initImpl() {
        auto renderSys = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>();
        renderSys->addCameraNode(std::static_pointer_cast<CameraNode>(shared_from_this()));
    }
    void CameraNode::shutdownImpl() {
        auto renderSys = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>();
        renderSys->eraseCameraNode(std::static_pointer_cast<CameraNode>(shared_from_this()));
    }

    bool CameraNode::getIsActiveCamera() const {
        return mIsActiveCamera;
    }
    void CameraNode::setIsActiveCamera(bool const isActiveCamera) {
        mIsActiveCamera = isActiveCamera;
        if (mIsActiveCamera) {
            auto renderSys = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>();
            renderSys->setActiveCameraNode(std::static_pointer_cast<CameraNode>(shared_from_this()));
        }
    }

    f32 CameraNode::getZoom() const {
        return mZoom;
    }
    void CameraNode::setZoom(f32 const zoom) {
        mZoom = zoom;
    }
}
