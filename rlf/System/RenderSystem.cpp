#include <System/RenderSystem.hpp>

namespace rlf {
    void RenderSystem::addRenderNode(std::shared_ptr<RenderNode> renderNode) {
        mRenderNodes[renderNode->getLayer()].insert(renderNode);
    }
    void RenderSystem::removeRenderNode(std::shared_ptr<RenderNode> renderNode) {
        mRenderNodes[renderNode->getLayer()].erase(renderNode);
    }

    void RenderSystem::render() {
        for (auto& [layer, nodes] : mRenderNodes) {
            for (auto& node : nodes) {
                if (!node->getActive()) {
                    continue;
                }

                auto matF = MatrixToFloatV(node->getGlobalTransform());
                rlPushMatrix();
                rlMultMatrixf(matF.v);

                node->renderImpl();

                rlPopMatrix();
            }
        }
    }
}
