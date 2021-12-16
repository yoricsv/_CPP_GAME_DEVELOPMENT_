cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME
            OpenGLGame
    )
project(${PROJECT_NAME})

    set(CMAKE_CXX_STANDARD      17)

add_executable(
    ${PROJECT_NAME}
        main.cpp
)

add_subdirectory(engine)

# add SDL2 Library
target_link_libraries(
    ${PROJECT_NAME}
        GameEngine
)
