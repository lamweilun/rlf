#include <System/Editor/EditorSystem.hpp>

#include <Engine/Engine.hpp>

#include <rlImGui.h>
#include <imgui.h>
#include <imfilebrowser.h>

#include <Node/BaseNode.hpp>

#include <fstream>

static inline ImGui::FileBrowser mFileBrowser;

namespace rlf::System {
    void EditorSystem::init() {
        rlImGuiSetup(true);

        mFileBrowser.SetTitle("File Browser");
        mFileBrowser.SetTypeFilters({".json"});
        mFileBrowser.SetPwd();
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
        rlImGuiShutdown();
    }

    void EditorSystem::displayHierarchyWindow() {
        ImGui::Begin("Hierarchy");
        if (ImGui::Button("Open World")) {
            mFileBrowser.Open();
        }
        ImGui::Separator();

        std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> drawChildrenTreeFunc = [&](std::shared_ptr<rlf::Node::BaseNode> node) {
            auto              rootNodePtr = node.get();
            std::stringstream ss;
            ss << rootNodePtr;
            std::string treeNodeID = node->getTypeNameImpl().data();
            treeNodeID += "##";
            treeNodeID += ss.str();

            if (ImGui::TreeNode(treeNodeID.c_str())) {
                for (auto child : node->getChildren()) {
                    drawChildrenTreeFunc(child);
                }
                ImGui::TreePop();
            }
        };
        drawChildrenTreeFunc(rlf::Engine::getInstance().getRootNode());

        ImGui::End();
    }

    void EditorSystem::displayInspectorWindow() {
        ImGui::Begin("Inspector");
        ImGui::End();
    }

    void EditorSystem::displayFileBrowserWindow() {
        mFileBrowser.Display();
        if (mFileBrowser.HasSelected()) {
            auto rootNode = rlf::Engine::getInstance().getRootNode();
            rootNode->deserializeFromFile(mFileBrowser.GetSelected());

            mLoadedWorld = mFileBrowser.GetSelected();
            mFileBrowser.ClearSelected();
        }
    }
}
