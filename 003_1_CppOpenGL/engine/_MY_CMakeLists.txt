cmake_minimum_required(VERSION 3.20)

    set(SDL_LIBRARY
            SdlLink
    )

project(${SDL_LIBRARY})

    set(CMAKE_CXX_STANDARD 17)



    set( PROJECT_SOURCE_DIR
            ${SDL_LINK}/src
    )

add_library(${SDL_LINK}
                src/Engine.cpp
)

include_directories(${PROJECT_SOURCE_DIR})

# SDL
if(NOT IOS)
    add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2 )
    set(SDL2MAIN_LIBRARY
            SDL2main
    )
    set(SDL2_LIBRARY
            SDL2-static
    )
endif()

## GLEW
#if(NOT APPLE AND NOT ANDROID AND (UNIX OR MINGW))
#    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/GLEW)
#    set(GLEW_LIBRARY libglew_static)
#endif()
#
#find_package(OpenGL REQUIRED)

target_include_directories(
        ${SDL_LINK}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
)

include_directories(
        ${SDL_LINK}
    PUBLIC        
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
)

target_link_libraries(
        ${SDL_LINK}
    PRIVATE
        ${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY}
)