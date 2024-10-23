cmake_minimum_required(VERSION 3.29)

project(TerminalAudacity)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch Raylib using CMake's FetchContent
include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
)

# Make Raylib available
FetchContent_MakeAvailable(raylib)

# Include directories for Raylib and Raygui
include_directories(${raylib_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Project sources
add_executable(TerminalAudacity main.cpp)

# Link Raylib to the project
target_link_libraries(TerminalAudacity PRIVATE raylib)
