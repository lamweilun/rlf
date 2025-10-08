#include "System/Render/RenderSystem.hpp"

#include <System/Editor/EditorSystem.hpp>

#include <Engine/Engine.hpp>
#include <Node/BaseNode.hpp>

namespace rlf::System {
    void EditorSystem::renderGizmo() {
        if (mSelectedNode) {
            auto globalPosition = mSelectedNode->getGlobalPosition();
            auto zoom = 1.0f;
            auto renderSys = rlf::Engine::getInstance().getSystem<rlf::System::RenderSystem>();
            if (auto activeCamera = renderSys->getActiveCameraNode()) {
                zoom = activeCamera->getAsCamera2D().zoom;
            }
            DrawLineEx(globalPosition * zoom, (globalPosition + Vector2(50.0f, 0.0f)) * zoom, 5.0f, RED);
            DrawLineEx(globalPosition* zoom, (globalPosition + Vector2(0.0f, 50.0f)) * zoom, 5.0f, GREEN);
            DrawRectanglePro(Rectangle{-5, -5, 10, 10}, -globalPosition* zoom, 0.0f, DARKBLUE);
        }
    }

}