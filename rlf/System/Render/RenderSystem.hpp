#pragma once

#include <System/ISystem.hpp>
#include <Node/Render/RenderNode.hpp>
#include <Node/UI/UINode.hpp>
#include <Node/Render/CameraNode.hpp>

#include <map>
#include <memory>
#include <unordered_set>

namespace rlf::System {
    class RenderSystem : public ISystem {
    public:
        void addRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode);
        void removeRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode);

        void addUINode(std::shared_ptr<rlf::Node::UINode> uiNode);
        void removeUINode(std::shared_ptr<rlf::Node::UINode> uiNode);

        void                                   addCameraNode(std::shared_ptr<rlf::Node::CameraNode> cameraNode);
        void                                   eraseCameraNode(std::shared_ptr<rlf::Node::CameraNode> cameraNode);
        void                                   setActiveCameraNode(std::shared_ptr<rlf::Node::CameraNode> cameraNode);
        std::shared_ptr<rlf::Node::CameraNode> getActiveCameraNode() const;

        Vector2 getMousePosition() const;
        Vector2 getUIMousePosition() const;

        void render() override;

    private:
        std::map<int, std::unordered_set<std::shared_ptr<rlf::Node::RenderNode>>> mRenderNodes;
        std::map<int, std::unordered_set<std::shared_ptr<rlf::Node::UINode>>>     mUINodes;
        std::unordered_set<std::shared_ptr<rlf::Node::CameraNode>>                mCameraNodes;
        std::shared_ptr<rlf::Node::CameraNode>                                    mActiveCameraNode;
    };
}
