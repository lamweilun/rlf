cmake_minimum_required(VERSION 3.31.0)

# Setup CPM
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.0/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CompilerFlags.cmake)

# Add the subdirectories of what we want to build
add_subdirectory(rlf)
add_subdirectory(pong)
