cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME CheckBuild)
project(${PROJECT_NAME} CXX)

    set(CMAKE_CXX_STANDARD          17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    set(SOURCES ${PROJECT_NAME}/src)

add_executable(
        ${PROJECT_NAME}
        ${SOURCES}/main.cpp
)
