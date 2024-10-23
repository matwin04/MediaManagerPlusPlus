cmake_minimum_required(VERSION 3.29)
project(midi++)

set(CMAKE_CXX_STANDARD 20)

find_package(ftxui REQUIRED)
add_executable(${PROJECT_NAME} main.cpp
        main.cpp)
target_link_libraries(${PROJECT_NAME}
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
)