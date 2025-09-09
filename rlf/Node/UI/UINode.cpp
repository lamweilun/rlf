#include <Node/UI/UINode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node {
    void UINode::setActiveImpl([[maybe_unused]] bool const selfActive) {
        if (getActive()) {
            rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addUINode(std::static_pointer_cast<UINode>(shared_from_this()));
        } else {
            rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeUINode(std::static_pointer_cast<UINode>(shared_from_this()));
        }
    }
    void UINode::setupImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addUINode(std::static_pointer_cast<UINode>(shared_from_this()));
    }
    void UINode::shutdownImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeUINode(std::static_pointer_cast<UINode>(shared_from_this()));
    }

    void UINode::setLayer(i32 const layer) {
        if (mLayer == layer) {
            return;
        }
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeUINode(std::static_pointer_cast<UINode>(shared_from_this()));
        mLayer = layer;
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addUINode(std::static_pointer_cast<UINode>(shared_from_this()));
    }
}
