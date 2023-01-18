cmake_minimum_required(VERSION 3.22.1)
project(Corners VERSION 1.0.0)

# might come in handy: audio network
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(game)
add_executable(Corners main.cpp)
target_link_libraries(Corners PUBLIC -lsfml-graphics -lsfml-window -lsfml-system game)
