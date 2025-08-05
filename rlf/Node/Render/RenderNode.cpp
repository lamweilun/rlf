#include <Node/Render/RenderNode.hpp>

#include <System/Render/RenderSystem.hpp>

namespace rlf::Node {
    void RenderNode::setActiveImpl(bool const selfActive) {
        if (selfActive) {
            rlf::System::RenderSystem::getInstance().addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        } else {
            rlf::System::RenderSystem::getInstance().removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        }
    }

    void RenderNode::initImpl() {
        rlf::System::RenderSystem::getInstance().addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
    }
    void RenderNode::shutdownImpl() {
        rlf::System::RenderSystem::getInstance().removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
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
        rlf::System::RenderSystem::getInstance().removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        mLayer = layer;
        rlf::System::RenderSystem::getInstance().addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
    }
    i32 RenderNode::getLayer() const {
        return mLayer;
    }
}
