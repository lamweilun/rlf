cmake_minimum_required(VERSION 3.31.0)

project(rlf)

# rlf dependencies
CPMAddPackage("gh:nlohmann/json@3.12.0") # nlohmann_json
CPMAddPackage("gh:raysan5/raylib#5.5") # raylib

if (RLF_EDITOR)
    # imgui
    CPMAddPackage("gh:ocornut/imgui@1.92.1-docking")
    add_library(
            imgui
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    )
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

    # rlImGui
    CPMAddPackage("gh:raylib-extras/rlImGui#main")
    add_library(
            rlImGui
            ${rlImGui_SOURCE_DIR}/rlImGui.cpp
    )
    target_include_directories(rlImGui PUBLIC ${rlImGui_SOURCE_DIR})
    target_link_libraries(rlImGui PUBLIC imgui raylib)
endif ()

add_library(
        ${PROJECT_NAME}

        Engine/Engine.cpp

        Manager/TypeManager.cpp

        Node/Audio/MusicNode.cpp
        Node/Audio/SoundNode.cpp

        Node/Physics/ColliderNode.cpp
        Node/Physics/LineColliderNode.cpp
        Node/Physics/BoxColliderNode.cpp
        Node/Physics/CircleColliderNode.cpp
        Node/Physics/RigidbodyNode.cpp

        Node/Render/RenderNode.cpp
        Node/Render/CameraNode.cpp
        Node/Render/LineRenderNode.cpp
        Node/Render/CircleRenderNode.cpp
        Node/Render/QuadRenderNode.cpp
        Node/Render/SpriteRenderNode.cpp
        Node/Render/ParticleRenderNode.cpp
        Node/Render/BurstParticleRenderNode.cpp

        Node/UI/UICameraNode.cpp
        Node/UI/UINode.cpp
        Node/UI/UIButtonNode.cpp
        Node/UI/UISpriteNode.cpp
        Node/UI/UITextNode.cpp
        Node/UI/UISliderNode.cpp

        Node/BaseNode.cpp

        Resource/IResource.cpp
        Resource/TextureResource.cpp
        Resource/MusicResource.cpp
        Resource/SoundResource.cpp
        Resource/FontResource.cpp

        System/ISystem.cpp
        System/Audio/AudioSystem.cpp
        System/Physics/PhysicsSystem.cpp
        System/Render/RenderSystem.cpp
        System/Resource/ResourceSystem.cpp

        Util/Accessor/JsonDeserializer.cpp
        Util/Accessor/JsonSerializer.cpp
        Util/Physics/CollisionDetection.cpp
        Util/Reflection/NamedValue.cpp
        Util/Color.cpp
        Util/Math.cpp
        Util/Util.cpp
)

if (RLF_EDITOR)
    target_sources(${PROJECT_NAME} PRIVATE
            System/Editor/EditorSystem.cpp
            System/Editor/EditorSystem_Gizmo.cpp
            System/Editor/EditorSystem_FileBrowser.cpp
            System/Editor/EditorSystem_Hierarchy.cpp
    )
endif ()

add_warning_flags(${PROJECT_NAME})
target_precompile_headers(${PROJECT_NAME} PUBLIC pch.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ./)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json raylib)
if (RLF_EDITOR)
    target_link_libraries(${PROJECT_NAME} PUBLIC imgui rlImGui)
    target_compile_definitions(${PROJECT_NAME} PUBLIC RLF_EDITOR)
endif ()
if (RLF_DEBUG)
    target_compile_definitions(${PROJECT_NAME} PUBLIC RLF_DEBUG)
endif ()
