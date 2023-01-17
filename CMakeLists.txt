cmake_minimum_required(VERSION 3.0.0)
project(Corners VERSION 1.0.0)

# might come in handy: audio network
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(game)

file(GLOB SRCS "*.cpp")
add_executable(Corners ${SRCS})

#target_link_libraries(Corners -lsfml-graphics -lsfml-window -lsfml-system)
target_link_libraries(Corners PUBLIC -lsfml-graphics -lsfml-window -lsfml-system game)