#pragma once

#include <Util/Singleton.hpp>
#include <Node/Render/RenderNode.hpp>

#include <map>
#include <memory>
#include <unordered_set>

namespace rlf::system {
    class RenderSystem : public Singleton<RenderSystem> {
    public:
        void addRenderNode(std::shared_ptr<RenderNode> renderNode);
        void removeRenderNode(std::shared_ptr<RenderNode> renderNode);

        void render();

    private:
        std::map<int, std::unordered_set<std::shared_ptr<RenderNode>>> mRenderNodes;
    };
}
