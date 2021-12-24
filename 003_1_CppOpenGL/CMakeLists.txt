cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME
            OpenGLGame
    )
project(${PROJECT_NAME})

    set(CMAKE_CXX_STANDARD  17)

add_executable(
    ${PROJECT_NAME}
        main.cpp
)

#GAME_ENGINE_INCLUDE
add_subdirectory(engine)

target_link_libraries(
    ${PROJECT_NAME}
        GameEngine
)
