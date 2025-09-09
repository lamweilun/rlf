cmake_minimum_required(VERSION 3.31.0)

project(exteroids)

add_executable(
    ${PROJECT_NAME}

    Node/Game/GameManagerNode.cpp

    main.cpp
)
add_warning_flags(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ./)
target_link_libraries(${PROJECT_NAME} PUBLIC rlf)
