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
        ImGui::ShowDemoWindow();
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
        ImGui::SameLine();
        if (ImGui::Button("Save World")) {
            if (!mLoadedWorld.empty()) {
                auto          rootNode = rlf::Engine::getInstance().getRootNode();
                rlf::Json     j        = rootNode->serialize();
                std::ofstream ofs(mLoadedWorld, std::ios::trunc);
                ofs << j.dump(2) << std::endl;
            }
        }

        if (!mLoadedWorld.empty()) {
            ImGui::Text("Currently editing: %s", mLoadedWorld.filename().c_str());
        }

        ImGui::Separator();

        std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> drawChildrenTreeFunc = [&](std::shared_ptr<rlf::Node::BaseNode> node) {
            auto              rootNodePtr = node.get();
            std::stringstream ss;
            ss << rootNodePtr;
            std::string const arrowBtnID   = node->getName() + "##" + ss.str() + "arrow";
            std::string const selectableID = node->getName() + "##" + ss.str() + "selectable";

            // Display arrow button if there's children
            if (node->getChildren().size()) {
                // Change arrow direction based on whether its showing children
                ImGuiDir arrowDir = ImGuiDir_Right;
                if (mShowChildrenTable.contains(node)) {
                    arrowDir = mShowChildrenTable.at(node) ? ImGuiDir_Down : ImGuiDir_Right;
                }

                // Toggleable arrow button to show children
                if (ImGui::ArrowButton(arrowBtnID.c_str(), arrowDir)) {
                    if (mShowChildrenTable.contains(node)) {
                        mShowChildrenTable[node] = !mShowChildrenTable[node];
                    } else {
                        mShowChildrenTable[node] = true;
                    }
                }
                ImGui::SameLine();
            }

            // Set text color to grey if inactive
            ImColor activeColor = node->getActiveSelf() ? ImVec4(1.0f, 1.0f, 1.0f, 1.0f) : ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
            ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertFloat4ToU32(activeColor));
            // Draw a node selectable
            if (ImGui::Selectable(selectableID.c_str(), node == mSelectedNode)) {
                mSelectedNode = node;
            }
            ImGui::PopStyleColor();

            // Draw children if drop down arrow is toggled
            if (mShowChildrenTable.contains(node) && mShowChildrenTable.at(node)) {
                for (auto child : node->getChildren()) {
                    ImGui::TreePush(ss.str().c_str());
                    drawChildrenTreeFunc(child);
                    ImGui::TreePop();
                }
            }
        };
        drawChildrenTreeFunc(rlf::Engine::getInstance().getRootNode());

        ImGui::End();
    }

    void EditorSystem::displayInspectorWindow() {
        ImGui::Begin("Inspector");

        if (mSelectedNode) {
            mSelectedNode->imguiAccessImpl();
        }

        ImGui::End();
    }

    void EditorSystem::displayFileBrowserWindow() {
        mFileBrowser.Display();

        // Load new world
        if (mFileBrowser.HasSelected()) {
            mSelectedNode = nullptr;
            mShowChildrenTable.clear();

            if (mFileBrowser.GetSelected().extension() == ".json") {
                auto rootNode = rlf::Engine::getInstance().getRootNode();
                rootNode->deserializeFromFile(mFileBrowser.GetSelected());
                mLoadedWorld = mFileBrowser.GetSelected();
                mFileBrowser.ClearSelected();
            }
        }
    }
}
