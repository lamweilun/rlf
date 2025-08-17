#pragma once

#include <Node/Physics/ColliderNode.hpp>

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

        RLF_NODE_ACCESS_START
        RLF_NODE_ACCESS_PARENT(ColliderNode)
        RLF_NODE_ACCESS_MEMBER_GET_SET("Start Point", getStartPoint, setStartPoint)
        RLF_NODE_ACCESS_MEMBER_GET_SET("End Point", getEndPoint, setEndPoint)
        RLF_NODE_ACCESS_END

    private:
        Vector2 mStartPoint = {0.0f, -0.5f};
        Vector2 mEndPoint   = {0.0f, 0.5f};
    };
}
