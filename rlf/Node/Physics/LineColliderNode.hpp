#pragma once

#include <Node/Physics/ColliderNode.hpp>

#ifdef RLF_DEBUG
#include <Node/Render/LineRenderNode.hpp>
#endif

namespace rlf::Node {
    class LineColliderNode : public ColliderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(LineColliderNode)

        Vector2 const& getStartPoint() const;
        void           setStartPoint(Vector2 const& startPoint);

        Vector2 const& getEndPoint() const;
        void           setEndPoint(Vector2 const& endPoint);

    protected:
        void initImpl() override;
        void shutdownImpl() override;
        void updateImpl() override;

    private:
        Vector2 mStartPoint = {0.0f, -0.5f};
        Vector2 mEndPoint   = {0.0f, 0.5f};

#ifdef RLF_DEBUG
        std::shared_ptr<LineRenderNode> mRenderNode;
#endif
    };
}
