#pragma once

#include <Node/Physics/ColliderNode.hpp>

#ifdef RLF_DEBUG
#include <Node/Render/LineRenderNode.hpp>
#endif

namespace rlf {
    class LineColliderNode : public ColliderNode {
    public:
        RLF_TYPE_REGISTER_QUICK(LineColliderNode)

        Vector3 const& getStartPoint() const;
        void           setStartPoint(Vector3 const& startPoint);

        Vector3 const& getEndPoint() const;
        void           setEndPoint(Vector3 const& endPoint);

    protected:
        void initImpl() override;
        void shutdownImpl() override;
        void updateImpl() override;

    private:
        Vector3 mStartPoint = {0.0f, -0.5f, 0.0f};
        Vector3 mEndPoint   = {0.0f, 0.5f, 0.0f};

#ifdef RLF_DEBUG
        std::shared_ptr<LineRenderNode> mRenderNode;
#endif
    };
}
