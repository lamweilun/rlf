#pragma once

#include <System/ISystem.hpp>

#include <System/SystemTable.hpp>

#include <Node/Render/RenderNode.hpp>
#include <Node/Render/ParticleRenderNode.hpp>
#include <Node/UI/UINode.hpp>
#include <Node/UI/UICameraNode.hpp>
#include <Node/Render/CameraNode.hpp>

#include <map>
#include <unordered_set>

namespace rlf
{
    class RenderSystem : public ISystem
    {
    public:
        void addRenderNode(std::shared_ptr<rlf::RenderNode> renderNode);
        void removeRenderNode(std::shared_ptr<rlf::RenderNode> renderNode);

        void addParticleRenderNode(std::shared_ptr<rlf::ParticleRenderNode> renderNode);
        void removeParticleRenderNode(std::shared_ptr<rlf::ParticleRenderNode> renderNode);

        void addUINode(std::shared_ptr<rlf::UINode> uiNode);
        void removeUINode(std::shared_ptr<rlf::UINode> uiNode);

        void                             addCameraNode(std::shared_ptr<rlf::CameraNode> cameraNode);
        void                             eraseCameraNode(std::shared_ptr<rlf::CameraNode> cameraNode);
        void                             setActiveCameraNode(std::shared_ptr<rlf::CameraNode> cameraNode);
        std::shared_ptr<rlf::CameraNode> getActiveCameraNode() const;

        void                               addUICameraNode(std::shared_ptr<rlf::UICameraNode> cameraNode);
        void                               eraseUICameraNode(std::shared_ptr<rlf::UICameraNode> cameraNode);
        void                               setActiveUICameraNode(std::shared_ptr<rlf::UICameraNode> cameraNode);
        std::shared_ptr<rlf::UICameraNode> getActiveUICameraNode() const;

        rlf::Vec2f getMousePosition() const;
        rlf::Vec2f getUIMousePosition() const;

        rlf::Vec2f getScreenSize() const;

        void init() override;
        void shutdown() override;
        void render() override;

    private:
        RenderTexture mBloomTexture;

        std::map<int, rlf::Table<std::shared_ptr<rlf::RenderNode>>>         mRenderNodes;
        std::map<int, rlf::Table<std::shared_ptr<rlf::ParticleRenderNode>>> mParticleRenderNodes;
        std::map<int, rlf::Table<std::shared_ptr<rlf::UINode>>>             mUINodes;

        std::unordered_set<std::shared_ptr<rlf::CameraNode>> mCameraNodes;
        std::shared_ptr<rlf::CameraNode>                     mActiveCameraNode;

        std::unordered_set<std::shared_ptr<rlf::UICameraNode>> mUICameraNodes;
        std::shared_ptr<rlf::UICameraNode>                     mActiveUICameraNode;
    };
}
