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

namespace rlf::System
{
    class RenderSystem : public ISystem
    {
    public:
        void addRenderNode(rlf::Node::RenderNode* const& renderNode);
        void removeRenderNode(rlf::Node::RenderNode* const& renderNode);

        void addParticleRenderNode(rlf::Node::ParticleRenderNode* const& renderNode);
        void removeParticleRenderNode(rlf::Node::ParticleRenderNode* const& renderNode);

        void addUINode(rlf::Node::UINode* const& uiNode);
        void removeUINode(rlf::Node::UINode* const& uiNode);

        void                   addCameraNode(rlf::Node::CameraNode* const& cameraNode);
        void                   eraseCameraNode(rlf::Node::CameraNode* const& cameraNode);
        void                   setActiveCameraNode(rlf::Node::CameraNode* const& cameraNode);
        rlf::Node::CameraNode* getActiveCameraNode() const;

        void                     addUICameraNode(rlf::Node::UICameraNode* const& cameraNode);
        void                     eraseUICameraNode(rlf::Node::UICameraNode* const& cameraNode);
        void                     setActiveUICameraNode(rlf::Node::UICameraNode* const& cameraNode);
        rlf::Node::UICameraNode* getActiveUICameraNode() const;

        rlf::Vec2f getMousePosition() const;
        rlf::Vec2f getUIMousePosition() const;

        rlf::Vec2f getScreenSize() const;

        void render() override;

    private:
        std::map<int, rlf::System::Table<rlf::Node::RenderNode*>>         mRenderNodes;
        std::map<int, rlf::System::Table<rlf::Node::ParticleRenderNode*>> mParticleRenderNodes;
        std::map<int, rlf::System::Table<rlf::Node::UINode*>>             mUINodes;

        std::unordered_set<rlf::Node::CameraNode*> mCameraNodes;
        rlf::Node::CameraNode*                     mActiveCameraNode;

        std::unordered_set<rlf::Node::UICameraNode*> mUICameraNodes;
        rlf::Node::UICameraNode*                     mActiveUICameraNode;
    };
}
