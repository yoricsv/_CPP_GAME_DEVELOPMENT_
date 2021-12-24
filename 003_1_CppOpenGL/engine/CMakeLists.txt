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
#        src/Engine.hpp
#        src/Window.hpp
#        src/SDL/SdlWindow.cpp
#        src/SDL/SdlWindow.hpp
#        src/EventsManager.cpp
#        src/Renderer.hpp
#        src/SDL/SdlRenderer.cpp
#        src/SDL/SdlRenderer.hpp
#        src/Mesh.cpp
#        src/Mesh.hpp
#        src/ShaderProgram.hpp
#        src/SDL/SdlMorphProgram.cpp
#        src/SDL/SdlMorphProgram.hpp
#        src/SDL/SdlShaderProgram.hpp
#        src/Node.cpp
#        src/Node.hpp
#        src/MeshData.hpp
#        src/SDL/SdlMesh.cpp
#        src/SDL/SdlMesh.hpp
#        src/GL/GlRenderer.cpp
#        src/GL/GlRenderer.hpp
#        src/GL/GlMesh.cpp
#        src/GL/GlMesh.hpp
#        src/GL/GlHeaders.hpp
#        src/GL/GlProgram.hpp
#        src/GL/GlMorphProgram.cpp
#        src/GL/GlMorphProgram.hpp
#        src/GL/GlProgram.cpp
)

#SDL
#find_package(SDL2 REQUIRED)      # DON'T USE IT FOR SOURCE CODE (ONLY FOR BINARY)!

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


#OpenGL
find_package(OpenGL REQUIRED)

find_library(
    OPENGL_LIBRARY
        OpenGL
)


#GLEW
#find_package(GLEW   REQUIRED)      # DON'T USE IT FOR SOURCE CODE (ONLY FOR BINARY)!
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
#    set(
#        CMAKE_CXX_FLAGS
#            "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static"
#    )
#    set(
#        CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS
#            "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s"
#    )

target_link_libraries(
        ${PROJECT_NAME}
    PRIVATE
        ${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY}
        ${OPENGL_LIBRARY}
        ${GLEW_LIBRARY}
#        "-lmingw32 ${OPENGL_LIBRARY}"
#        "-mwindows ${GLEW_LIBRARY}"
)

target_include_directories(
        ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/GLEW/include
)