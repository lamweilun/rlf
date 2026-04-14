#pragma once

#include <Node/BaseNode.hpp>

namespace rlf
{
    class UICameraNode : public BaseNode
    {
    public:
        RLF_NODE_TYPE_REGISTER_QUICK(UICameraNode)

        rlf::Vec2f const& getReferenceResolution() const;
        void              setReferenceResolution(rlf::Vec2f const& referenceResolution);

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
        rlf::Vec2f mReferenceResolution = rlf::Vec2f{1280, 720};
        f32        mZoom                = 1.0f;
        bool       mZoomToWindowSize    = false;
        bool       mIsActiveUICamera    = false;
    };
}
