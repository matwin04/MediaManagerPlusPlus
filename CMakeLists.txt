cmake_minimum_required(VERSION 3.15)
project(MediaManager++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

# Try to find Qt6 first
find_package(Qt6 COMPONENTS Core Sql Widgets QUIET)

# If Qt6 is not found, fallback to Qt5
if (NOT Qt6_FOUND)
    message(STATUS "Qt6 not found, falling back to Qt5.")
    find_package(Qt5 COMPONENTS Core Sql Widgets REQUIRED)
    set(QT_LIBRARIES
        Qt5::Core
        Qt5::Sql
        Qt5::Widgets
    )
else()
    message(STATUS "Using Qt6.")
    set(QT_LIBRARIES
        Qt6::Core
        Qt6::Sql
        Qt6::Widgets
    )
endif()

# Include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
set(SOURCES
        main.cpp
        mainwindow.cpp
)

# Add header files
set(HEADERS
        mainwindow.h
)

# Add UI files
set(UI_FILES
        ui/mainwindow.ui
)

# Add executable
add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
)

# Link Qt libraries dynamically based on Qt version
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Copy SQL files after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/sql $<TARGET_FILE_DIR:${PROJECT_NAME}>/sql
)
