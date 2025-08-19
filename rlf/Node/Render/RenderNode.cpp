#include <Node/Render/RenderNode.hpp>

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

    void RenderNode::initImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
    }
    void RenderNode::shutdownImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
    }

    void RenderNode::renderImpl() {
    }

    void RenderNode::setTint(Color const& tint) {
        mTint = tint;
    }

    Color const& RenderNode::getTint() const {
        return mTint;
    }

    void RenderNode::setLayer(i32 const layer) {
        if (mLayer == layer) {
            return;
        }
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        mLayer = layer;
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
    }
    i32 RenderNode::getLayer() const {
        return mLayer;
    }

    void RenderNode::setDrawInWireframe(bool const drawInWireframe) {
        mDrawInWireframe = drawInWireframe;
    }
    bool RenderNode::getDrawInWireframe() const {
        return mDrawInWireframe;
    }
}
