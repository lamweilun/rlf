#include <System/Editor/EditorSystem.hpp>

#include <Engine/Engine.hpp>
#include <Node/BaseNode.hpp>

#include <imgui.h>

namespace rlf
{
    void EditorSystem::displayFileBrowserWindow()
    {
        ImGui::Begin("Explorer");

        std::function<void(std::filesystem::path const&)> drawChildPathFunc = [&](std::filesystem::path const& p)
        {
            for (auto entry : std::filesystem::directory_iterator(p))
            {
                // Show drop down arrow to show children in this path
                if (entry.is_directory())
                {
                    auto     dropdownArrowID = std::string("##") + entry.path().string();
                    ImGuiDir arrowDir        = mShowPathTable[entry.path()] ? ImGuiDir_Down : ImGuiDir_Right;
                    if (ImGui::ArrowButton(dropdownArrowID.c_str(), arrowDir))
                    {
                        mShowPathTable[entry.path()] = !mShowPathTable[entry.path()];
                    }
                    ImGui::SameLine();
                }

                // Draw the path as a selectable
                if (ImGui::Selectable(entry.path().filename().c_str(), mSelectedPath == entry.path()))
                {
                    mSelectedPath = entry.path();
                }

                // Double click check
                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    // Load the world if its json
                    if (mSelectedPath.extension() == ".json")
                    {
                        if (mLoadedWorld != mSelectedPath)
                        {
                            mSelectedNode = nullptr;
                            auto rootNode = rlf::Engine::getInstance().getRootNode();
                            rootNode->deserializeFromFile(mSelectedPath);
                            mLoadedWorld = mSelectedPath;
                        }
                    }
                }

                // Drag drop for resources
                if (ImGui::BeginDragDropSource())
                {
                    setDraggedFilePath(std::filesystem::relative(entry.path(), std::filesystem::current_path()));
                    ImGui::SetDragDropPayload("DragFromFileBrowser", nullptr, 0);
                    ImGui::EndDragDropSource();
                }

                // Draw the children in this selectable
                if (entry.is_directory() && mShowPathTable.at(entry.path()))
                {
                    ImGui::TreePush(entry.path().c_str());
                    drawChildPathFunc(entry.path());
                    ImGui::TreePop();
                }
            }
        };
        drawChildPathFunc(std::filesystem::current_path());

        ImGui::End();
    }
}
