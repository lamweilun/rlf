#pragma once

#include <System/ISystem.hpp>
#include <Node/Render/RenderNode.hpp>
#include <Node/Render/ParticleRenderNode.hpp>
#include <Node/UI/UINode.hpp>
#include <Node/UI/UICameraNode.hpp>
#include <Node/Render/CameraNode.hpp>

#include <map>
#include <memory>
#include <unordered_set>

namespace rlf::System {
    class RenderSystem : public ISystem {
    public:
        void addRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode);
        void removeRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode);

        void addParticleRenderNode(std::shared_ptr<rlf::Node::ParticleRenderNode> renderNode);
        void removeParticleRenderNode(std::shared_ptr<rlf::Node::ParticleRenderNode> renderNode);

        void addUINode(std::shared_ptr<rlf::Node::UINode> uiNode);
        void removeUINode(std::shared_ptr<rlf::Node::UINode> uiNode);

        void                                   addCameraNode(std::shared_ptr<rlf::Node::CameraNode> cameraNode);
        void                                   eraseCameraNode(std::shared_ptr<rlf::Node::CameraNode> cameraNode);
        void                                   setActiveCameraNode(std::shared_ptr<rlf::Node::CameraNode> cameraNode);
        std::shared_ptr<rlf::Node::CameraNode> getActiveCameraNode() const;

        void                                     addUICameraNode(std::shared_ptr<rlf::Node::UICameraNode> cameraNode);
        void                                     eraseUICameraNode(std::shared_ptr<rlf::Node::UICameraNode> cameraNode);
        void                                     setActiveUICameraNode(std::shared_ptr<rlf::Node::UICameraNode> cameraNode);
        std::shared_ptr<rlf::Node::UICameraNode> getActiveUICameraNode() const;

        Vector2 getMousePosition() const;
        Vector2 getUIMousePosition() const;

        void render() override;

    private:
        std::map<int, std::unordered_set<std::shared_ptr<rlf::Node::RenderNode>>>         mRenderNodes;
        std::map<int, std::unordered_set<std::shared_ptr<rlf::Node::ParticleRenderNode>>> mParticleRenderNodes;
        std::map<int, std::unordered_set<std::shared_ptr<rlf::Node::UINode>>>             mUINodes;

        std::unordered_set<std::shared_ptr<rlf::Node::CameraNode>> mCameraNodes;
        std::shared_ptr<rlf::Node::CameraNode>                     mActiveCameraNode;

        std::unordered_set<std::shared_ptr<rlf::Node::UICameraNode>> mUICameraNodes;
        std::shared_ptr<rlf::Node::UICameraNode>                     mActiveUICameraNode;
    };
}
