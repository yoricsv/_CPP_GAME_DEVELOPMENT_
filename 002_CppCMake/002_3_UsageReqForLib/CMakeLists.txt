cmake_minimum_required(VERSION 3.20)

    set(PROJECT_NAME
            Tutorial
    )

project(
    ${PROJECT_NAME}
        VERSION 1.0
)

    set(CMAKE_CXX_STANDARD          17  )
    set(CMAKE_CXX_STANDARD_REQUIRED True)

option(
    USE_MY_MATH
        "Use tutorial provided math implementation"  ON
)

if(USE_MY_MATH)
    add_subdirectory(MathFunctions)
    list(
        APPEND
            EXTRA_LIBS                                  # to collect up any optional libraries to later be linked
                MathFunctions                           # Name of the including Library
    )
endif()

configure_file(
    ${PROJECT_NAME}Config.h.in
        ${PROJECT_NAME}Config.h
)

add_executable(
    ${PROJECT_NAME}
        tutorial.cxx
)

target_link_libraries(
        Tutorial
    PUBLIC
        ${EXTRA_LIBS}                                   # Gather the Libraries
)

target_include_directories(
        ${PROJECT_NAME}
    PUBLIC
        ${PROJECT_BINARY_DIR}                           # will find TutorialConfig.h
)