cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME TestFromRootScr)
project(${PROJECT_NAME} LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME})
