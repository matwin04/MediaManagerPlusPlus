cmake_minimum_required(VERSION 3.10)
project(MediaManagerPlusPlus)

# Enable automatic handling of UI files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src/ui)

# Use vcpkg to find Qt6 and TagLib
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# Add the executable
add_executable(${PROJECT_NAME}
        src/main.cpp
)

# Link the required libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Widgets
        Qt6::Sql
)
configure_file(${CMAKE_SOURCE_DIR}/src/init.sql ${CMAKE_BINARY_DIR}/init.sql COPYONLY)