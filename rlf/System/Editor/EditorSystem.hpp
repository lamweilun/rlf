#pragma once

#include <System/ISystem.hpp>

namespace rlf::Node {
    class BaseNode;
}

namespace rlf::System {
    class EditorSystem : public ISystem {
    public:
        void init() override;
        void render() override;
        void shutdown() override;

    private:
        void displayHierarchyWindow();
        void displayInspectorWindow();
        void displayFileBrowserWindow();

        std::filesystem::path                                     mLoadedWorld;
        std::shared_ptr<rlf::Node::BaseNode>                      mSelectedNode;
        std::unordered_map<std::shared_ptr<Node::BaseNode>, bool> mShowChildrenTable;
    };
}
