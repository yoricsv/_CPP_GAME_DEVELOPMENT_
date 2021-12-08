cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME Game)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Engine)

target_link_libraries(${PROJECT_NAME} Engine)
