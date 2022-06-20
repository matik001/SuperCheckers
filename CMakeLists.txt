cmake_minimum_required(VERSION 3.21)
project(CheckersAI)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lstdc++fs")

# sfml
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics window system network audio REQUIRED)

# tgui
set(TGUI_BACKEND "SFML_GRAPHICS")
set(CMAKE_BUILD_TYPE "Debug")
set(TGUI_CXX_STANDARD, "17")
set(TGUI_STATIC_LIBRARIES TRUE)
set(TGUI_DIR "C:/TGUI/lib/cmake/TGUI")
find_package(TGUI 0.10 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_SOURCE_DIR} "./src/*.cpp")
add_executable(CheckersAI ${SOURCE_FILES})
target_link_libraries(CheckersAI PRIVATE TGUI::TGUI sfml-graphics sfml-window sfml-system sfml-network sfml-audio stdc++fs)
