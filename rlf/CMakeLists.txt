cmake_minimum_required(VERSION 3.31.0)

project(rlf)

# rlf dependencies
CPMAddPackage("gh:nlohmann/json@3.12.0")
CPMAddPackage("gh:raysan5/raylib#5.5")

add_library(
    ${PROJECT_NAME}

    Engine/Engine.cpp

    Node/Audio/SoundNode.cpp

    Node/Physics/ColliderNode.cpp
    Node/Physics/LineColliderNode.cpp
    Node/Physics/SphereColliderNode.cpp
    Node/Physics/RigidbodyNode.cpp
    
    Node/Render/RenderNode.cpp
    Node/Render/LineRenderNode.cpp
    Node/Render/ParticleRenderNode.cpp
    Node/Render/SphereRenderNode.cpp
    Node/Render/SpriteRenderNode.cpp
    
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
target_precompile_headers(${PROJECT_NAME} PUBLIC precompiled.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ./)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_26)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json raylib)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC RLF_DEBUG)
endif()
