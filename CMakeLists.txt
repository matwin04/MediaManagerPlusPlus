cmake_minimum_required(VERSION 3.10)
project(terminalaudacity)

# Enable automatic handling of UI files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the installed Qt package
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

# Add the executable and specify the UI file
add_executable(${PROJECT_NAME} main.cpp audioplayer.ui)

# Link the Qt Widgets library
target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Multimedia)