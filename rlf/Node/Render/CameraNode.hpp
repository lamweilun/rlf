#pragma once

#include <Node/BaseNode.hpp>

namespace rlf::Node {
    class CameraNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(CameraNode)

        Color const& getClearColor() const;
        void         setClearColor(Color const& color);

        Vector2 const& getReferenceResolution() const;
        void           setReferenceResolution(Vector2 const& referenceResolution);

        f32  getZoom() const;
        void setZoom(f32 const zoom);

        bool getZoomToWindowSize() const;
        void setZoomToWindowSize(bool const zoomToWindowSize);

        bool getIsActiveCamera() const;
        void setIsActiveCamera(bool const isActiveCamera);

        Camera2D getAsCamera2D() const;
        Camera2D getAsCamera2DUI() const;

    protected:
        void setupImpl() override;
        void shutdownImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Clear Color", getClearColor, setClearColor)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Reference Resolution", getReferenceResolution, setReferenceResolution)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Zoom", getZoom, setZoom)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Zoom To Window Size", getZoomToWindowSize, setZoomToWindowSize)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Is Active Camera", getIsActiveCamera, setIsActiveCamera)
        RLF_NODE_ACCESS_END

    private:
        Color   mClearColor          = BLACK;
        Vector2 mReferenceResolution = Vector2{1280, 720};
        f32     mZoom                = 1.0f;
        bool    mZoomToWindowSize    = false;
        bool    mIsActiveCamera      = false;
    };
}
