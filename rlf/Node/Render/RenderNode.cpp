#include <Node/Render/RenderNode.hpp>

#include <System/Render/RenderSystem.hpp>

namespace rlf {
    void RenderNode::setActiveImpl(bool const selfActive) {
        if (selfActive) {
            rlf::system::RenderSystem::getInstance().addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        } else {
            rlf::system::RenderSystem::getInstance().removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        }
    }

    void RenderNode::initImpl() {
        rlf::system::RenderSystem::getInstance().addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
    }
    void RenderNode::shutdownImpl() {
        rlf::system::RenderSystem::getInstance().removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
    }

    void RenderNode::renderImpl() {
    }

    void RenderNode::setTint(Color const& tint) {
        mTint = tint;
    }

    Color const& RenderNode::getTint() const {
        return mTint;
    }

    void RenderNode::setLayer(int const layer) {
        if (mLayer == layer) {
            return;
        }
        rlf::system::RenderSystem::getInstance().removeRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
        mLayer = layer;
        rlf::system::RenderSystem::getInstance().addRenderNode(std::static_pointer_cast<RenderNode>(shared_from_this()));
    }
    int RenderNode::getLayer() const {
        return mLayer;
    }
}
