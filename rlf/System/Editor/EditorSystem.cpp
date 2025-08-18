#include <System/Editor/EditorSystem.hpp>

#include <Engine/Engine.hpp>

#include <rlImGui.h>
#include <imgui.h>
#include <imfilebrowser.h>

#include <Node/BaseNode.hpp>

#include <fstream>
#include <sstream>

namespace rlf::Editor {
    static inline constexpr char const* id_ToggleChildrenButton = "ToggleChildrenButton";
    static inline constexpr char const* id_ShiftDownButton      = "ShiftDownButton";
    static inline constexpr char const* id_ShiftUpButton        = "ShiftUpButton";
    static inline constexpr char const* id_DeleteButton         = "DeleteButton";
}

namespace rlf::System {
    void EditorSystem::init() {
        rlImGuiSetup(true);

        mLoadFileBrowser = new ImGui::FileBrowser();
        mLoadFileBrowser->SetTitle("File Browser");
        mLoadFileBrowser->SetTypeFilters({".json"});
        mLoadFileBrowser->SetPwd();
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
        delete mLoadFileBrowser;
        rlImGuiShutdown();
    }

    void EditorSystem::displayHierarchyWindow() {
        ImGui::Begin("Hierarchy");
        if (ImGui::Button("Open World")) {
            mLoadFileBrowser->Open();
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

        // Add new child node button
        if (mSelectedNode) {
            if (ImGui::BeginCombo("Add Child Node", "")) {
                for (auto const& [typeName, creatorFunc] : rlf::System::TypeSystem::getInstance().getCreatorFuncs()) {
                    if (ImGui::Selectable(typeName.data())) {
                        auto newChildNode = mSelectedNode->addChild(typeName);
                        newChildNode->setName(std::string("New ") + typeName.data());
                        mShowChildrenTable[mSelectedNode] = true;
                        mSelectedNode                     = newChildNode;
                    }
                }
                ImGui::EndCombo();
            }
        }

        // Show what we are currently editing
        if (!mLoadedWorld.empty()) {
            ImGui::Text("Currently editing: %s", mLoadedWorld.filename().c_str());
        }

        ImGui::Separator();

        std::function<void(std::shared_ptr<rlf::Node::BaseNode>)> drawChildrenTreeFunc = [&](std::shared_ptr<rlf::Node::BaseNode> node) {
            // Setup unique IDs based on pointer address
            auto              rootNodePtr = node.get();
            std::stringstream ss;
            ss << rootNodePtr;
            std::string const  nodeUniqueID = std::string("##") + ss.str();
            std::string const& nodeName     = node->getName();

            // Display arrow button if there's children
            if (node->getChildren().size()) {
                // Change arrow direction based on whether its showing children
                ImGuiDir arrowDir = ImGuiDir_Right;
                if (mShowChildrenTable.contains(node)) {
                    arrowDir = mShowChildrenTable.at(node) ? ImGuiDir_Down : ImGuiDir_Right;
                }

                // Toggleable arrow button to show children
                std::string const arrowBtnID = nodeUniqueID + rlf::Editor::id_ToggleChildrenButton;
                if (ImGui::ArrowButton(arrowBtnID.c_str(), arrowDir)) {
                    if (mShowChildrenTable.contains(node)) {
                        mShowChildrenTable[node] = !mShowChildrenTable[node];
                    } else {
                        mShowChildrenTable[node] = true;
                    }
                }
                ImGui::SameLine();
            }

            // Set text color to grey if self is inactive
            ImColor activeColor = node->getActiveSelf() ? ImVec4(1.0f, 1.0f, 1.0f, 1.0f) : ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
            ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertFloat4ToU32(activeColor));
            // Draw a node selectable
            std::string const selectableID = nodeName + nodeUniqueID;
            if (ImGui::Selectable(selectableID.c_str(), node == mSelectedNode, 0, ImGui::CalcTextSize(nodeName.c_str()))) {
                mSelectedNode = node;
            }
            ImGui::PopStyleColor();

            // Drag-drop to set parent
            if (ImGui::BeginDragDropSource()) {
                mDraggedNode = node;
                ImGui::SetDragDropPayload("NodeSetParent", nullptr, 0);
                ImGui::EndDragDropSource();
            }
            if (ImGui::BeginDragDropTarget()) {
                if (ImGui::AcceptDragDropPayload("NodeSetParent")) {
                    mDraggedNode->setParent(node);
                    mDraggedNode = nullptr;
                }
                ImGui::EndDragDropTarget();
            }

            // Shift Up/Down Buttons for rearrangement
            if (node->hasParent()) {
                ImGui::SameLine();
                std::string const shiftDownButtonID = nodeUniqueID + rlf::Editor::id_ShiftDownButton;
                if (ImGui::ArrowButton(shiftDownButtonID.c_str(), ImGuiDir_Down)) {
                    node->mToShiftDown = true;
                }
                ImGui::SameLine();
                std::string const shiftUpButtonID = nodeUniqueID + rlf::Editor::id_ShiftUpButton;
                if (ImGui::ArrowButton(shiftUpButtonID.c_str(), ImGuiDir_Up)) {
                    node->mToShiftUp = true;
                }
            }

            // Delete Button
            ImGui::SameLine();
            std::string const deleteID = std::string("X") + nodeUniqueID + rlf::Editor::id_DeleteButton;
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.25f, 0.25f, 1.0f)));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.5f, 0.5f, 1.0f)));
            if (ImGui::Button(deleteID.c_str())) {
                if (node->isRootNode()) {
                    for (auto& child : node->getChildren()) {
                        child->setToDestroy(true);
                    }
                } else {
                    node->setToDestroy(true);
                }
            }
            ImGui::PopStyleColor();
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
        mLoadFileBrowser->Display();

        // Load new world
        if (mLoadFileBrowser->HasSelected()) {
            mSelectedNode = nullptr;
            mShowChildrenTable.clear();

            if (mLoadFileBrowser->GetSelected().extension() == ".json") {
                auto rootNode = rlf::Engine::getInstance().getRootNode();
                rootNode->deserializeFromFile(mLoadFileBrowser->GetSelected());
                mLoadedWorld = mLoadFileBrowser->GetSelected();
                mLoadFileBrowser->ClearSelected();
            }
        }
    }
}
