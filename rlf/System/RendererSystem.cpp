#include <System/RendererSystem.hpp>

namespace rlf {
    void RendererSystem::addRenderableNodes(std::shared_ptr<RenderableNode> renderableNode) {
        mRenderableNodes.insert(renderableNode);
    }
    void RendererSystem::removeRenderableNodes(std::shared_ptr<RenderableNode> renderableNode) {
        mRenderableNodes.erase(renderableNode);
    }

    void RendererSystem::render() {
        for (auto& rn : mRenderableNodes) {
            auto const& globalTransform = rn->getGlobalTransform();
            auto        matF            = MatrixToFloatV(globalTransform);

            rlPushMatrix();
            rlMultMatrixf(matF.v);
            rn->renderImpl();

            rlPopMatrix();
        }
    }
}
