#pragma once

#include <System/ISystem.hpp>

namespace rlf
{
    class BaseNode;

    class EditorSystem : public ISystem
    {
    public:
        void init() override;
        void render() override;
        void shutdown() override;

        void                         setDraggedFilePath(std::filesystem::path const& p);
        std::filesystem::path const& getDraggedFilePath() const;
        void                         clearDraggedFilePath();

    private:
        void displayHierarchyWindow();
        void displayInspectorWindow();
        void displayFileBrowserWindow();

        // File Browser
        std::filesystem::path                           mSelectedPath;
        std::filesystem::path                           mDraggedPath;
        std::filesystem::path                           mLoadedWorld;
        std::unordered_map<std::filesystem::path, bool> mShowPathTable;

        // Hierarchy
        std::shared_ptr<rlf::BaseNode>                      mSelectedNode;
        std::shared_ptr<rlf::BaseNode>                      mDraggedNode;
        std::unordered_map<std::shared_ptr<BaseNode>, bool> mShowChildrenTable;
    };
}
