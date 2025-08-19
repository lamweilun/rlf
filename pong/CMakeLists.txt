cmake_minimum_required(VERSION 3.31.0)

project(rlf_pong)

add_executable(
    ${PROJECT_NAME}

    # Game Related Stuffs
    Player/PlayerNode.cpp
    
    Environment/WallNode.cpp
    
    Ball/BallNode.cpp

    main.cpp
)
add_warning_flags(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ./)
target_link_libraries(${PROJECT_NAME} PUBLIC rlf)
