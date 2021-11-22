cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME Maker)

    project(${PROJECT_NAME}
        LANGUAGES
        CXX
)

    set(CMAKE_CXX_STANDARD          17)

    add_subdirectory(engine)

    add_executable(game src/main.cpp)

    target_link_LIBRARIES(game SdlLink)