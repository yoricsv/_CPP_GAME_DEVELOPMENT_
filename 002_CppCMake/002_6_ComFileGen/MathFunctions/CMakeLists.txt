# first we add the executable that generates the table
add_executable(
    MakeTable
        MakeTable.cxx
)

# add the command to generate the source code
add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND
        MakeTable
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS
        MakeTable
)

# add the binary tree directory to the search path for include files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add MakeTable headers to the main library
add_library(
    MathFunctions
        mysqrt.cxx
        ${CMAKE_CURRENT_BINARY_DIR}/Table.h         # add MakeTable header to the search path
)

target_include_directories(
        MathFunctions
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE                                         # add the current binary directory that Table.h
        ${CMAKE_CURRENT_BINARY_DIR}                 # can be found and included by mysqrt.cxx.
)

install(
    TARGETS
        MathFunctions
    DESTINATION
        lib
)
install(
    FILES
        MathFunctions.h
    DESTINATION
        include
)