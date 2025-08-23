#pragma once

#include <Node/BaseNode.hpp>

namespace rlf::Node {
    class CameraNode : public BaseNode {
    public:
        RLF_TYPE_REGISTER_QUICK(CameraNode)

        bool getIsActiveCamera() const;
        void setIsActiveCamera(bool const isActiveCamera);

        f32  getZoom() const;
        void setZoom(f32 const zoom);

    protected:
        void initImpl() override;
        void shutdownImpl() override;

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(BaseNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Is Active Camera", getIsActiveCamera, setIsActiveCamera)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Zoom", getZoom, setZoom)
        RLF_NODE_ACCESS_END

    private:
        bool mIsActiveCamera = false;
        f32  mZoom           = 1.0f;
    };
}
