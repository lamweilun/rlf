#pragma once

#include <System/ISystem.hpp>
#include <Node/Physics/LineColliderNode.hpp>
#include <Node/Physics/BoxColliderNode.hpp>
#include <Node/Physics/CircleColliderNode.hpp>

#include <unordered_set>

namespace rlf::System {
    class PhysicsSystem : public ISystem {
    public:
        void addColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode);
        void addColliderNode(std::shared_ptr<rlf::Node::BoxColliderNode> boxColliderNode);
        void addColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode);

        void removeColliderNode(std::shared_ptr<rlf::Node::LineColliderNode> lineColliderNode);
        void removeColliderNode(std::shared_ptr<rlf::Node::BoxColliderNode> boxColliderNode);
        void removeColliderNode(std::shared_ptr<rlf::Node::CircleColliderNode> sphereColliderNode);

        void update() override;

#ifdef RLF_EDITOR
        void editorRender();
#endif

    private:
        template <class T>
        struct Table {
            std::vector<std::shared_ptr<T>>             mData;
            std::unordered_map<std::shared_ptr<T>, u64> mIndexLookup;

            void insert(std::shared_ptr<T> const& p) {
                if (mIndexLookup.contains(p)) {
                    return;
                }
                mIndexLookup[p] = mData.size();
                mData.push_back(p);
            }

            void erase(std::shared_ptr<T> const& p) {
                auto itr = mIndexLookup.find(p);
                if (itr == mIndexLookup.end()) {
                    return;
                }
                auto const index = itr->second;
                if (index == mData.size() - 1) {
                    mIndexLookup.erase(itr);
                    mData.pop_back();
                    return;
                }
                std::swap(mData[index], mData.back());
                mIndexLookup[mData[index]] = index;
                mIndexLookup.erase(p);
                mData.pop_back();
            }

            auto size() const {
                return mData.size();
            }

            auto begin() const {
                return std::begin(mData);
            }
            auto end() const {
                return std::end(mData);
            }
        };

        Table<rlf::Node::LineColliderNode>   mLineColliderNodes;
        Table<rlf::Node::BoxColliderNode>    mBoxColliderNodes;
        Table<rlf::Node::CircleColliderNode> mCircleColliderNodes;
    };
}
