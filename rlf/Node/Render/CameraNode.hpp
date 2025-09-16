#pragma once

#include <Node/BaseNode.hpp>

namespace rlf::Node {
    class CameraNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(CameraNode)

        bool getIsActiveCamera() const;
        void setIsActiveCamera(bool const isActiveCamera);

        bool getZoomToWindowSize() const;
        void setZoomToWindowSize(bool const zoomToWindowSize);

        Vector2 const& getReferenceResolution() const;
        void           setReferenceResolution(Vector2 const& referenceResolution);

        f32  getZoom() const;
        void setZoom(f32 const zoom);

        Camera2D getAsCamera2D() const;
        Camera2D getAsCamera2DUI() const;

    protected:
        void setupImpl() override;
        void shutdownImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Is Active Camera", getIsActiveCamera, setIsActiveCamera)
        RLF_NODE_ACCESS_MEMBER("Zoom To Window Size", mZoomToWindowSize)
        RLF_NODE_ACCESS_MEMBER("Reference Resolution", mReferenceResolution)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Zoom", getZoom, setZoom)
        RLF_NODE_ACCESS_END

    private:
        bool    mIsActiveCamera      = false;
        bool    mZoomToWindowSize    = false;
        Vector2 mReferenceResolution = Vector2{1280, 720};
        f32     mZoom                = 1.0f;
    };
}
