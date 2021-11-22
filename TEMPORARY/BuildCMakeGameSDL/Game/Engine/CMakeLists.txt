cmake_minimum_required(VERSION 3.20)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

add_library(Engine src/Engine.cpp src/Engine.hpp)

#SDL
if (NOT IOS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2)
    set(SDL2MAIN_LIBRARY SDL2main)
    set(SDL2_LIBRARY SDL2-static)
endif()

target_link_libraries(Engine PRIVATE
        ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY})

target_include_directories(Engine
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include)