cmake_minimum_required(VERSION 3.31.0)

project(arkanoid)

add_executable(
        ${PROJECT_NAME}

        Node/Ball/BallNode.cpp
        Node/Block/BlockNode.cpp

        Node/Game/MainMenuManagerNode.cpp
        Node/Game/GameManagerNode.cpp

        Node/Player/PlayerNode.cpp

        main.cpp
)
add_warning_flags(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ./)
target_link_libraries(${PROJECT_NAME} PRIVATE rlf)
