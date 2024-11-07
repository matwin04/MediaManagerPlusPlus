cmake_minimum_required(VERSION 3.10)
project(MediaManagerPlusPlus)

# Enable automatic handling of MOC, UIC, and RCC files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Specify the Qt version to use
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# Set the source directory for UI files
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src/ui)

# Define the executable and its source files
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/browser.cpp
        src/databasehandler.cpp
        src/filemanager.cpp
)

# Add the UI files
set(UIS
        src/ui/browser.ui
)

# Add the include directories
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/ui
)

# Link the required Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt6::Widgets
        Qt6::Sql
)

# Ensure the init.sql file is in the resources folder
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)

# Copy the init.sql file to the build directory
configure_file(${CMAKE_SOURCE_DIR}/resources/init.sql ${CMAKE_BINARY_DIR}/init.sql COPYONLY)
# Enable C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)