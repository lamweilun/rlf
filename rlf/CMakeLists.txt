cmake_minimum_required(VERSION 3.31.0)

project(rlf)

# Define a build-time option to enable the editor mode
option(RLF_EDITOR_MODE "Build the rlf library with editor support" OFF)

# Build imgui
if (RLF_EDITOR_MODE)
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
endif()

# rlf dependencies
CPMAddPackage("gh:nlohmann/json@3.12.0")
CPMAddPackage("gh:raysan5/raylib#5.5")

add_library(
    ${PROJECT_NAME}

    Engine/Engine.cpp

    Node/Audio/SoundNode.cpp

    Node/Physics/ColliderNode.cpp
    Node/Physics/LineColliderNode.cpp
    Node/Physics/CircleColliderNode.cpp
    Node/Physics/RigidbodyNode.cpp
    
    Node/Render/RenderNode.cpp
    Node/Render/LineRenderNode.cpp
    Node/Render/CircleRenderNode.cpp
    Node/Render/SpriteRenderNode.cpp
    Node/Render/ParticleRenderNode.cpp
    Node/Render/BurstParticleRenderNode.cpp
    
    Node/BaseNode.cpp

    System/Audio/AudioSystem.cpp
    System/Physics/PhysicsSystem.cpp
    System/Render/RenderSystem.cpp
    System/Type/TypeSystem.cpp

    Util/Accessor/JsonDeserializer.cpp
    Util/Accessor/JsonSerializer.cpp
    Util/Physics/CollisionDetection.cpp
    Util/Reflection/NamedValue.cpp
    Util/Color.cpp
    Util/Math.cpp
)
add_warning_flags(${PROJECT_NAME})
target_precompile_headers(${PROJECT_NAME} PUBLIC pch.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ./)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json raylib)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC RLF_DEBUG)
endif()
if (RLF_EDITOR_MODE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC RLF_EDITOR)
    target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
endif()
