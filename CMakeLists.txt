cmake_minimum_required(VERSION 3.15)
project(MediaManager++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# Find Qt5 or Qt6
find_package(Qt5 COMPONENTS Core Sql Widgets REQUIRED)

#include dir
include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
# Add the source files
set(SOURCES
        main.cpp
        mainwindow.cpp
        #src/dbhandler.cpp
        #src/shift.cpp
        )
#Add Header Files
set(HEADERS
        mainwindow.h
        #include/dbhandler.h
        #include/shift.h
        )

#set(UI_FILES
#        ui/mainwindow.ui
 #       )

#set(RESOURCE_FILES
#        resources/init.sql
#)
# Add executable
add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
        ${RESOURCE_FILES}
        )

# Link Qt libraries
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Sql
        Qt5::Widgets
        )

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)
