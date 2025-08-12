#include <System/Editor/EditorSystem.hpp>

#include <rlImGui.h>
#include <imgui.h>

namespace rlf::System {
    void EditorSystem::init() {
        rlImGuiSetup(true);
    }

    void EditorSystem::render() {
        rlImGuiBegin();
        displayHierarchyWindow();
        ImGui::ShowDemoWindow();
        rlImGuiEnd();
    }

    void EditorSystem::shutdown() {
        rlImGuiShutdown();
    }

    void EditorSystem::displayHierarchyWindow() {
    }
}
