cmake_minimum_required(VERSION 3.20)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

add_library(Engine
        src/Engine.cpp
        src/Engine.hpp
        src/Window.hpp
        src/SDL/SdlWindow.cpp
        src/SDL/SdlWindow.hpp
        src/EventsManager.cpp
        src/Renderer.hpp
        src/SDL/SdlRenderer.cpp
        src/SDL/SdlRenderer.hpp
        src/Mesh.cpp
        src/Mesh.hpp
        src/ShaderProgram.hpp
        src/SDL/SdlMorphProgram.cpp
        src/SDL/SdlMorphProgram.hpp
        src/SDL/SdlShaderProgram.hpp
        src/Node.cpp
        src/Node.hpp
        src/MeshData.hpp
        src/SDL/SdlMesh.cpp
        src/SDL/SdlMesh.hpp
        src/GL/GlRenderer.cpp
        src/GL/GlRenderer.hpp
        src/GL/GlMesh.cpp
        src/GL/GlMesh.hpp
        src/GL/GlHeaders.hpp
        src/GL/GlProgram.hpp
        src/GL/GlMorphProgram.cpp
        src/GL/GlMorphProgram.hpp
        src/GL/GlProgram.cpp)

#SDL
if (NOT IOS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2)
    set(SDL2MAIN_LIBRARY SDL2main)
    set(SDL2_LIBRARY SDL2-static)
endif()

find_library(OPENGL_LIBRARY OpenGL)

target_link_libraries(Engine PRIVATE
        ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY} )#${OPENGL_LIBRARY})

target_include_directories(Engine
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include)