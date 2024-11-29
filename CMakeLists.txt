cmake_minimum_required(VERSION 3.15)
project(MediaManager++)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ftxui 5 REQUIRED)
include_directories(/usr/include)
link_directories(/usr/lib)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources/MediaServer.xml"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/MediaServer.cpp
    src/UUIDGen.cpp
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component 
  PRIVATE upnp# Not needed for this example.
)