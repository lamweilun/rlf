#include <UIManagerNode.hpp>

#include <Node/UI/UIButtonNode.hpp>

namespace rlf::Node {
    void UIManagerNode::initImpl() {
        auto buttonNode = addOrGetFirstChildOfType<rlf::Node::UIButtonNode>();
        buttonNode->setClickedCallback([](std::shared_ptr<UIButtonNode>) {
            std::cout << "Button Clicked" << std::endl;
        });
    }
}
