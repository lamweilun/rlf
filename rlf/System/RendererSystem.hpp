#pragma once

#include <Node/Renderable/RenderableNode.hpp>
#include <Util/Singleton.hpp>

#include <unordered_set>

namespace rlf {
    class RendererSystem : public Singleton<RendererSystem> {
    public:
        void addRenderableNodes(std::shared_ptr<RenderableNode> renderableNode);
        void removeRenderableNodes(std::shared_ptr<RenderableNode> renderableNode);

        void render();

    private:
        std::unordered_set<std::shared_ptr<RenderableNode>> mRenderableNodes;
    };
}
