cmake_minimum_required(VERSION 3.20)

project(SdlLink)

    set(CMAKE_CXX_STANDARD 17)

    add_library(SdlLink src/Engine.cpp)

# SDL
if(NOT IOS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2)
    set(SDL2MAIN_LIBRARY SDL2main)
    set(SDL2_LIBRARY SDL2-static)
endif()


include_directories(
        SdlLink
    PUBLIC        
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
)

target_link_libraries(
        SdlLink
    PRIVATE
        ${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY}
)