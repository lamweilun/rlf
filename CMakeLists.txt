cmake_minimum_required(VERSION 3.31.0)

# Setup CPM
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.41.0/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CompilerFlags.cmake)

# rlf dependencies
CPMAddPackage("gh:nlohmann/json@3.12.0")
CPMAddPackage("gh:raysan5/raylib#5.5")

project(rlf)

# rlf environment variables
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(RLF_DEBUG ON)
else()
    set(RLF_DEBUG OFF)
endif()
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/rlf/Config/Config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/rlf/Config/Config.h
    @ONLY
)

add_library(
    ${PROJECT_NAME}

    # Engine Related Stuffs
    rlf/Node/Physics/ColliderNode.cpp
    rlf/Node/Physics/LineColliderNode.cpp
    rlf/Node/Physics/SphereColliderNode.cpp
    rlf/Node/Physics/RigidbodyNode.cpp
    
    rlf/Node/Render/RenderNode.cpp
    rlf/Node/Render/LineRenderNode.cpp
    rlf/Node/Render/SphereRenderNode.cpp
    rlf/Node/Render/SpriteRenderNode.cpp
    
    rlf/Node/BaseNode.cpp

    rlf/System/PhysicsSystem.cpp
    rlf/System/RenderSystem.cpp
    rlf/System/TypeSystem.cpp

    rlf/Util/Accessor/JsonDeserializer.cpp
    rlf/Util/Accessor/JsonSerializer.cpp
    rlf/Util/Physics/CollisionDetection.cpp
    rlf/Util/Reflection/NamedValue.cpp
    rlf/Util/Color.cpp
    rlf/Util/Math.cpp
)
target_precompile_headers(${PROJECT_NAME} PUBLIC rlf/precompiled.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC rlf ./)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json raylib)
add_warning_flags(${PROJECT_NAME})

add_executable(
    ${PROJECT_NAME}_game

    # Game Related Stuffs
    game/Player/PlayerNode.cpp
    game/Player/PlayerRenderNode.cpp
    game/Environment/WallNode.cpp
    game/Environment/WallRenderNode.cpp
    game/Ball/BallNode.cpp
    game/Ball/BallRenderNode.cpp

    main.cpp
)
target_include_directories(${PROJECT_NAME}_game PUBLIC game)
target_link_libraries(${PROJECT_NAME}_game PUBLIC rlf)
add_warning_flags(${PROJECT_NAME}_game)
