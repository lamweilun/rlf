#include <Node/Render/RenderNode.hpp>

#include <Engine/Engine.hpp>
#include <System/Render/RenderSystem.hpp>

namespace rlf
{
    void RenderNode::setActiveImpl([[maybe_unused]] bool const selfActive)
    {
        if (getActive())
        {
            rlf::Engine::getInstance().getSystem<rlf::RenderSystem>()->addRenderNode(as<RenderNode>());
        }
        else
        {
            rlf::Engine::getInstance().getSystem<rlf::RenderSystem>()->removeRenderNode(as<RenderNode>());
        }
    }

    void RenderNode::setupImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::RenderSystem>()->addRenderNode(as<RenderNode>());
    }
    void RenderNode::shutdownImpl()
    {
        rlf::Engine::getInstance().getSystem<rlf::RenderSystem>()->removeRenderNode(as<RenderNode>());
    }

    void RenderNode::renderImpl()
    {
    }

    i32 RenderNode::getLayer() const
    {
        return mLayer;
    }
    void RenderNode::setLayer(i32 const layer)
    {
        if (mLayer == layer)
        {
            return;
        }
        rlf::Engine::getInstance().getSystem<rlf::RenderSystem>()->removeRenderNode(as<RenderNode>());
        mLayer = layer;
        rlf::Engine::getInstance().getSystem<rlf::RenderSystem>()->addRenderNode(as<RenderNode>());
    }

    Color const& RenderNode::getTint() const
    {
        return mTint;
    }
    void RenderNode::setTint(Color const& tint)
    {
        mTint = tint;
    }

    bool RenderNode::getBloom() const
    {
        return mBloom;
    }
    void RenderNode::setBloom(bool const bloom)
    {
        if (mBloom == bloom)
        {
            return;
        }
        mBloom = bloom;
    }

}
