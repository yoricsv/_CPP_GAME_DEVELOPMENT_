cmake_minimum_required(VERSION 3.20)
project(Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(Game main.cpp)

add_subdirectory(Engine)

target_link_libraries(Game Engine)
