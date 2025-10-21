#include <Node/Render/RenderNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node {
    void RenderNode::setActiveImpl([[maybe_unused]] bool const selfActive) {
        if (getActive()) {
            rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        } else {
            rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        }
    }

    void RenderNode::setupImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addRenderNode(as<RenderNode>());
    }
    void RenderNode::shutdownImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeRenderNode(as<RenderNode>());
    }

    void RenderNode::renderImpl() {
    }

    Color const& RenderNode::getTint() const {
        return mTint;
    }
    void RenderNode::setTint(Color const& tint) {
        mTint = tint;
    }

    i32 RenderNode::getLayer() const {
        return mLayer;
    }
    void RenderNode::setLayer(i32 const layer) {
        if (mLayer == layer) {
            return;
        }
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        mLayer = layer;
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
    }

}
