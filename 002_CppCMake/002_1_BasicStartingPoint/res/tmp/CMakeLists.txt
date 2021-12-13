cmake_minimum_required(VERSION 3.20)

    set( PROJECT_NAME
            projectName
    )

    set( PROJECT_PROPERTIES
            CMAKE_BUILD_TYPE            Debug
            CMAKE_CXX_FLAGS             -O3
            CMAKE_CXX_FLAGS             -Wall
            CMAKE_CXX_STANDARD          17
            CMAKE_CXX_STANDARD_REQUIRED ON
            IS_SUBPROJECT               PARENT_DIRECTORY
            RUNTIME_OUTPUT_DIRECTORY    ${CMAKE_SOURCE_DIR}/out
    )

project( ${PROJECT_NAME}
            LANGUAGES CXX
)

# Check is the project parent or subproject
#get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

    set( PROJECT_SOURCE_DIR
#            ${PROJECT_NAME}/inc
            ${PROJECT_NAME}/src
    )
    set( SOURCES
            ${PROJECT_NAME}/src/main.cpp
    )
	set( HEADERS
            ${PROJECT_NAME}/inc/main.h
    )

#target_include_directories(
#		${PROJECT_NAME}
#	PRIVATE
#		${PROJECT_NAME}/inc
#)

add_executable(
        ${PROJECT_NAME}
             ${PROJECT_SOURCE_DIR}/${SOURCES}
)

set_target_properties(
        ${PROJECT_NAME}
    PROPERTIES
        ${PROJECT_PROPERTIES}
)