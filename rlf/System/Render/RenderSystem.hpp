#pragma once

#include <Util/Singleton.hpp>
#include <Node/Render/RenderNode.hpp>

#include <map>
#include <memory>
#include <unordered_set>

namespace rlf::System {
    class RenderSystem : public Singleton<RenderSystem> {
    public:
        void addRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode);
        void removeRenderNode(std::shared_ptr<rlf::Node::RenderNode> renderNode);

        void render();

    private:
        std::map<int, std::unordered_set<std::shared_ptr<rlf::Node::RenderNode>>> mRenderNodes;
    };
}
