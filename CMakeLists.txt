cmake_minimum_required(VERSION 3.21)
project(CheckersAI)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics window system network audio REQUIRED)

file(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_SOURCE_DIR} "./src/*.cpp")
add_executable(CheckersAI ${SOURCE_FILES} src/ui/CheckersWidget.cpp src/ui/CheckersWidget.h src/ui/TexturesManager.cpp src/ui/TexturesManager.h src/utils/TextureResources.h src/ui/UIConfig.h src/ui/UIConfig.cpp src/ui/UserUIAgent.h src/ui/UserUIAgent.cpp src/utils/SfmlUtils.h)

target_link_libraries(CheckersAI sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
