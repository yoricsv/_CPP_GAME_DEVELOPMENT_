cmake_minimum_required(VERSION 3.20)

    set( PROJECT_NAME
            CMakeBasicStartingPoint
    )

    set( PROJECT_PROPERTIES
            CMAKE_BUILD_TYPE            Debug
            CMAKE_CXX_FLAGS             -O3
            CMAKE_CXX_FLAGS             -Wall
            CMAKE_CXX_STANDARD          17
            CMAKE_CXX_STANDARD_REQUIRED ON
            RUNTIME_OUTPUT_DIRECTORY    ${CMAKE_SOURCE_DIR}/out

            # TO SET ADDITION FLAGS --> UNCOMMENT the lines below
#            COMPILE_DEFINITIONS         USE_GET_LENGTH_FUNCTION    # to use GET_STRING_LENGTH function
    )


project( ${PROJECT_NAME}
            LANGUAGES CXX
)

# Check is the project parent or subproject
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

    set( PROJECT_SOURCE_DIR
#            ${PROJECT_NAME}/inc
            ${PROJECT_NAME}/src
    )
    set( SOURCES
            main.cpp
    )
	set( HEADERS
            main.h
    )
target_sources()

target_include_directories(
		${PROJECT_NAME}
	PRIVATE
		${PROJECT_NAME}/inc
)

add_executable(
        ${PROJECT_NAME}
             ${PROJECT_SOURCE_DIR}/${SOURCES}
)

set_target_properties(
        ${PROJECT_NAME}
    PROPERTIES
        ${PROJECT_PROPERTIES}
)