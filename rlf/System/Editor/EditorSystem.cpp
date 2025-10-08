#include <System/Editor/EditorSystem.hpp>

#include <Engine/Engine.hpp>

#include <Node/BaseNode.hpp>

#include <rlImGui.h>
#include <imgui.h>

namespace rlf::System {
    void EditorSystem::init() {
        rlImGuiSetup(true);
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    }

    void EditorSystem::render() {
        rlImGuiBegin();
        displayHierarchyWindow();
        displayInspectorWindow();
        displayFileBrowserWindow();
        // ImGui::ShowDemoWindow();
        rlImGuiEnd();
    }

    void EditorSystem::shutdown() {
        mSelectedNode = nullptr;
        mDraggedNode  = nullptr;
        mShowChildrenTable.clear();
        mShowPathTable.clear();
        rlImGuiShutdown();
    }

    void EditorSystem::setDraggedFilePath(std::filesystem::path const& p) {
        mDraggedPath = p;
    }
    std::filesystem::path const& EditorSystem::getDraggedFilePath() const {
        return mDraggedPath;
    }
    void EditorSystem::clearDraggedFilePath() {
        mDraggedPath.clear();
    }

    void EditorSystem::displayInspectorWindow() {
        ImGui::Begin("Inspector");
        if (mSelectedNode) {
            ImGui::Text("Node Type: %s", mSelectedNode->getTypeNameImpl().data());
            ImGui::Separator();
            mSelectedNode->imguiAccessImpl();
        }
        ImGui::End();
    }
}
