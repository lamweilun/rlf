cmake_minimum_required(VERSION 3.30)

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
add_executable(
    ${PROJECT_NAME}
    
    rlf/Node/Enemy/EnemyNode.cpp
    
    rlf/Node/Physics/RigidbodyNode.cpp
    
    rlf/Node/Player/PlayerBulletNode.cpp
    rlf/Node/Player/PlayerNode.cpp
    
    rlf/Node/BaseNode.cpp

    main.cpp
)
target_precompile_headers(${PROJECT_NAME} PRIVATE rlf/precompiled.hpp)
target_include_directories(${PROJECT_NAME} PRIVATE rlf ./)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_26)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json raylib)
add_warning_flags(${PROJECT_NAME})
