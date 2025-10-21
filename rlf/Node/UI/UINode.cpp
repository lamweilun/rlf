#include <Node/UI/UINode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf::Node {
    void UINode::setActiveImpl([[maybe_unused]] bool const selfActive) {
        if (getActive()) {
            rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addUINode(as<UINode>());
        } else {
            rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeUINode(as<UINode>());
        }
    }
    void UINode::setupImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addUINode(as<UINode>());
    }
    void UINode::shutdownImpl() {
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeUINode(as<UINode>());
    }

    void UINode::setLayer(i32 const layer) {
        if (mLayer == layer) {
            return;
        }
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->removeUINode(as<UINode>());
        mLayer = layer;
        rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>()->addUINode(as<UINode>());
    }
}
