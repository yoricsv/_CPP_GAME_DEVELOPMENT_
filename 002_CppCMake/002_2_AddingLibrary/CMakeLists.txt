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

# add MathFunctions library optional
# [REMARK] It really isn't any need to do so,
# but for larger projects is a good way
option(
    USE_MY_MATH
        "Use tutorial provided math implementation"  ON
)

# add te if statement which checks the value of the option.
if(USE_MY_MATH)
    add_subdirectory(MathFunctions)
    list(
        APPEND
            EXTRA_LIBS                                  # to collect up any optional libraries to later be linked
                MathFunctions                           # Name of the including Library
    )
    list(
        APPEND
            EXTRA_INCLUDES                              # to collect up any optional header files
                ${PROJECT_SOURCE_DIR}/MathFunctions     # will find Library HEADERS here
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

# add the MathFunctions library to executable
target_link_libraries(
        Tutorial
    PUBLIC
        ${EXTRA_LIBS}                                   # Gather the Libraries
)

# add the binary tree to the search path for INCLUDE files
target_include_directories(
        ${PROJECT_NAME}
    PUBLIC
        ${PROJECT_BINARY_DIR}                           # will find TutorialConfig.h
        ${EXTRA_INCLUDES}                               # will find MathFunctions.h
)