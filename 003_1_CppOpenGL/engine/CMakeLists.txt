cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME
            GameEngine
    )
project(${PROJECT_NAME})

    set(CMAKE_CXX_STANDARD  17)

add_library(
    ${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.h
)


#SDL_INCLUDE
if (NOT IOS)
    add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2
    )
        set(SDL2MAIN_LIBRARY
                SDL2main
        )
        set(SDL2_LIBRARY
                SDL2-static
        )
endif()


#GLEW_INCLUDE
set(
        GLEW_LIB_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/GLEW
)
set(
        GLEW_LIBRARY
        libglew_static
)

add_subdirectory(
        ${GLEW_LIB_DIR}
)


#OpenGL_INCLUDE
find_package(OpenGL REQUIRED)

find_library(
    OPENGL_LIBRARY
        OpenGL
)


target_link_libraries(
        ${PROJECT_NAME}
    PRIVATE
        ${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY}
        ${GLEW_LIBRARY}
        ${OPENGL_LIBRARY}
)

target_include_directories(
        ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/GLEW/include
)