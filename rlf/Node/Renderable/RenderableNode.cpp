#include <Node/Renderable/RenderableNode.hpp>

#include <System/RendererSystem.hpp>

namespace rlf {

    void RenderableNode::renderImpl() {
    }

    void RenderableNode::initImpl() {
        rlf::RendererSystem::getInstance().addRenderableNodes(std::static_pointer_cast<RenderableNode>(shared_from_this()));
    }
    void RenderableNode::shutdownImpl() {
        rlf::RendererSystem::getInstance().removeRenderableNodes(std::static_pointer_cast<RenderableNode>(shared_from_this()));
    }
}
