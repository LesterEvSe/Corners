cmake_minimum_required(VERSION 3.0.0)
project(Corners)

# might come in handy: audio network
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

add_executable(Corners Corners.cpp Field.cpp)

target_link_libraries(Corners -lsfml-graphics -lsfml-window -lsfml-system)