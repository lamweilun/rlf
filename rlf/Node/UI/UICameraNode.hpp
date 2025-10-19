#pragma once

#include <Node/BaseNode.hpp>

namespace rlf::Node {
    class UICameraNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(UICameraNode)

        Vector2 const& getReferenceResolution() const;
        void           setReferenceResolution(Vector2 const& referenceResolution);

        f32  getZoom() const;
        void setZoom(f32 const zoom);

        bool getZoomToWindowSize() const;
        void setZoomToWindowSize(bool const zoomToWindowSize);

        bool getIsActiveUICamera() const;
        void setIsActiveUICamera(bool const isActiveCamera);

        Camera2D getAsCamera2DUI() const;

    protected:
        void setupImpl() override;
        void shutdownImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Reference Resolution", getReferenceResolution, setReferenceResolution)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Zoom", getZoom, setZoom)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Zoom To Window Size", getZoomToWindowSize, setZoomToWindowSize)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Is Active UI Camera", getIsActiveUICamera, setIsActiveUICamera)
        RLF_NODE_ACCESS_END

    private:
        Vector2 mReferenceResolution = Vector2{1280, 720};
        f32     mZoom                = 1.0f;
        bool    mZoomToWindowSize    = false;
        bool    mIsActiveUICamera    = false;
    };
}
